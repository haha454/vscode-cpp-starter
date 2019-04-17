#include <bits/stdc++.h>

#define str(a) #a, " = ", a
#define DELIM " | "
#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define VA_NUM_ARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N

#define CONCAT_IMPL(x, y) x##y
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)

// to verify, run the preprocessor alone (g++ -E):
#define PREPEND_EACH_ARG_WITH_HASH_ARG_1(a) str(a)
#define PREPEND_EACH_ARG_WITH_HASH_ARG_2(a, ...) str(a), DELIM, PREPEND_EACH_ARG_WITH_HASH_ARG_1(__VA_ARGS__)
#define PREPEND_EACH_ARG_WITH_HASH_ARG_3(a, ...) str(a), DELIM, PREPEND_EACH_ARG_WITH_HASH_ARG_2(__VA_ARGS__)
#define PREPEND_EACH_ARG_WITH_HASH_ARG_4(a, ...) str(a), DELIM, PREPEND_EACH_ARG_WITH_HASH_ARG_3(__VA_ARGS__)
#define PREPEND_EACH_ARG_WITH_HASH_ARG_5(a, ...) str(a), DELIM, PREPEND_EACH_ARG_WITH_HASH_ARG_4(__VA_ARGS__)
#define PREPEND_EACH_ARG_WITH_HASH_ARG_6(a, ...) str(a), DELIM, PREPEND_EACH_ARG_WITH_HASH_ARG_5(__VA_ARGS__)
#define PREPEND_EACH_ARG_WITH_HASH_ARG_7(a, ...) str(a), DELIM, PREPEND_EACH_ARG_WITH_HASH_ARG_6(__VA_ARGS__)
#define PREPEND_EACH_ARG_WITH_HASH_ARG_8(a, ...) str(a), DELIM, PREPEND_EACH_ARG_WITH_HASH_ARG_7(__VA_ARGS__)
#define PREPEND_EACH_ARG_WITH_HASH_ARG_9(a, ...) str(a), DELIM, PREPEND_EACH_ARG_WITH_HASH_ARG_8(__VA_ARGS__)
#define PREPEND_EACH_ARG_WITH_HASH_ARG(...)                                 \
    MACRO_CONCAT(PREPEND_EACH_ARG_WITH_HASH_ARG_, VA_NUM_ARGS(__VA_ARGS__)) \
    (__VA_ARGS__)
#define PRINT(...) print(PREPEND_EACH_ARG_WITH_HASH_ARG(__VA_ARGS__))
#define TRACE(...) trace(PREPEND_EACH_ARG_WITH_HASH_ARG(__VA_ARGS__))

template <typename F, typename S>
std::ostream &operator<<(std::ostream &os, const std::pair<F, S> &p)
{
    return os << "(" << p.first << ", " << p.second << ")";
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    os << "{";
    for (auto it = v.begin(); it != v.end(); it++)
    {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "}";
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::unordered_set<T> &v)
{
    os << "{";
    for (auto it = v.begin(); it != v.end(); it++)
    {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "}";
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &v)
{
    os << "{";
    for (auto it = v.begin(); it != v.end(); it++)
    {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "}";
}

template <typename F, typename S>
std::ostream &operator<<(std::ostream &os, const std::map<F, S> &v)
{
    os << "{";
    for (auto it = v.begin(); it != v.end(); it++)
    {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "}";
}

template <typename F, typename S>
std::ostream &operator<<(std::ostream &os, const std::unordered_map<F, S> &v)
{
    os << "{";
    for (auto it = v.begin(); it != v.end(); it++)
    {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "}";
}

template <typename T, typename... Targs>
void print_to_os(std::ostream &os, const T &value)
{
    os << value;
}

template <typename T, typename... Targs>
void print_to_os(std::ostream &os, const T &value, const Targs &... Fargs)
{
    print_to_os(os, value);
    print_to_os(os, Fargs...);
}

template <typename... Targs>
void trace(const Targs &... Fargs)
{
    print_to_os(std::cerr, Fargs...);
    std::cerr << std::endl;
}

template <typename... Targs>
void print(const Targs &... Fargs)
{
    print_to_os(std::cout, Fargs...);
    std::cout << std::endl;
}

struct pairhash
{
  public:
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U> &x) const
    {
        return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
    }
};