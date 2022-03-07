using namespace std;

class FairSemaphore
{
private:
    conditional_variable cv;
    mutex mx;
    long long qhead, qtail;

public:
    FairSemaphore() : qhead(0), qtail(0)
    {
    }

    void acquire()
    {
        unique_lock<mutex> lk(mx);
        long long cur = qtail++;
        cv.wait(mx, [&cur, this]()
                { return cur == this->qhead; });
    }

    void release()
    {
        lock_guard<mutex> lk(mx);
        qhead++;
        cv.notify_all();
    }
};

// starve reader
class RWLock
{
private:
    mutex rmtx;
    binary_semaphore resource;
    FairSemaphore fs;
    int rctr;

public:
    void RLock()
    {
        lock_guard<mutex> lg(this->rmtx);
        fs.acquire();
        rctr++;
        if (rctr == 1)
        {
            resource.lock();
        }
        fs.release();
    }

    void RUnlock()
    {
        lock_guard<mutex> lg(this->rmtx);
        rctr--;
        if (rctr == 0)
        {
            resource.Unlock();
        }
    }

    void WLock()
    {
        fs.acquire();
        resource.acquire();
        fs.release();
    }

    void WUnlock()
    {
        resource.release();
    }
};
