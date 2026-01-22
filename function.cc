#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include <stdexcept>

template<typename>
class function; // Forward declaration

template<typename Ret, typename... Args>
class function<Ret(Args...)> {
private:
    // Type-erased interface
    struct callable_base {
        virtual ~callable_base() = default;
        virtual Ret invoke(Args... args) = 0;
        virtual callable_base* clone() const = 0;
    };

    // Concrete wrapper for any callable
    template<typename F>
    struct callable_impl : callable_base {
        F func_;

        callable_impl(F f) : func_(std::move(f)) {}

        Ret invoke(Args... args) override {
            return func_(args...);
        }

        callable_base* clone() const override {
            return new callable_impl(func_);
        }
    };

    callable_base* callable_ = nullptr;

public:
    // Default constructor
    function() = default;

    // Nullptr constructor
    function(std::nullptr_t) : callable_(nullptr) {}

    // Constructor from callable
    template<typename F>
    function(F f) : callable_(new callable_impl<F>(std::move(f))) {}

    // Copy constructor
    function(const function& other)
        : callable_(other.callable_ ? other.callable_->clone() : nullptr) {}

    // Move constructor
    function(function&& other) noexcept
        : callable_(other.callable_) {
        other.callable_ = nullptr;
    }

    // Destructor
    ~function() {
        delete callable_;
    }

    // Copy assignment
    function& operator=(const function& other) {
        if (this != &other) {
            delete callable_;
            callable_ = other.callable_ ? other.callable_->clone() : nullptr;
        }
        return *this;
    }

    // Move assignment
    function& operator=(function&& other) noexcept {
        if (this != &other) {
            delete callable_;
            callable_ = other.callable_;
            other.callable_ = nullptr;
        }
        return *this;
    }

    // Assign from callable
    template<typename F>
    function& operator=(F f) {
        function(std::move(f)).swap(*this);
        return *this;
    }

    // Invoke
    Ret operator()(Args... args) const {
        if (!callable_) {
            throw std::bad_function_call();
        }
        return callable_->invoke(std::forward<Args>(args)...);
    }

    // Check if callable
    explicit operator bool() const noexcept {
        return callable_ != nullptr;
    }

    // Swap
    void swap(function& other) noexcept {
        std::swap(callable_, other.callable_);
    }
};

int gogogo(const std::string& s) {
    std::cout << s << std::endl;
    return 4321;
}

int main() {
    function<int(std::string)> fn{gogogo};
    std::cout << fn("something") << std::endl;
    auto fn3{std::move(fn)};
}