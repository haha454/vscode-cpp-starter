#include <iostream>
#include <thread>
#include <mutex>
#include <format>

using Job = std::function<void()>;
using JobQueue = std::queue<Job>;

void work(const bool &should_stop,
          uint8_t worker_idx,
          JobQueue& jq,
          std::condition_variable& cv,
          std::mutex& mtx) {
    std::cout << std::format("Worker {} started\n", worker_idx);
    while (true) {
        std::unique_lock lk(mtx);
        std::cout << std::format("Worker {} going to sleep\n", worker_idx);
        cv.wait(lk, [&] {return !jq.empty() || should_stop; });

        std::cout << std::format("Worker {} is waken up\n", worker_idx);

        if (should_stop && jq.empty()) {
            break;
        }

        Job job;
        if (!jq.empty()) {
            job = jq.front();
            jq.pop();
        }
        lk.unlock();

        if (job) {
            std::cout << std::format("Worker {} working...\n", worker_idx);
            job();
            std::cout << std::format("Worker {} has done working\n", worker_idx);
        }
    }
    std::cout << std::format("Worker {} ending...\n", worker_idx);
}

int main() {
    uint worker_count{0};
    std::cout << "Input number of workers: \n";
    std::cin >> worker_count;

    auto should_stop{false};
    JobQueue jq;
    std::condition_variable cv;
    std::mutex mtx;

    std::vector<std::thread> threads;
    threads.reserve(worker_count);

    for (auto idx{0}; idx < worker_count; idx++) {
        threads.emplace_back(work, std::cref(should_stop), idx, std::ref(jq), std::ref(cv), std::ref(mtx));
    }

    constexpr auto job_count{5};

    for (auto idx{0}; idx < job_count; idx++) {
        static constexpr auto add_job_interval_ms{20};
        static constexpr auto work_duration_ms{500};
        std::cout << std::format("Adding job {}\n", idx);
        {
            std::lock_guard lk(mtx);
            jq.emplace([] {
                std::this_thread::sleep_for(std::chrono::milliseconds(work_duration_ms));
            });
        }
        cv.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(add_job_interval_ms));
    }

    std::cout << "Setting should_stop to true\n";
    should_stop=true;
    cv.notify_all();

    for (auto& thread : threads) {
        thread.join();
    }
}
