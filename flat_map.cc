#include <format>
#include <format>
#include <iostream>
#include <vector>

template<typename Key, typename Value>
class FlatMap {
    using kv_type = std::pair<Key, Value>;
    using vector_iter = typename std::vector<kv_type>::iterator;
    std::vector<kv_type> kvs_;


public:
    class iterator {
        vector_iter it_;

    public:
        explicit iterator(vector_iter vit) : it_(vit) {}

        kv_type& operator*() {
            return *it_;
        }

        kv_type* operator->() {
            return &*it_;
        }

        iterator& operator++() {
            ++it_;
            return *this;
        }

        iterator operator++(int) {
            auto tmp = *this;
            ++it_;
            return tmp;
        }

        bool operator==(const iterator& other_it) {
            return it_ == other_it.it_;
        }

        bool operator!=(const iterator& other_it) {
            return it_ != other_it.it_;
        }
    };
private:
    std::pair<vector_iter, bool> findImpl(const Key& key) {
        auto it = std::lower_bound(kvs_.begin(), kvs_.end(), key, [](const std::pair<const Key, Value>& e, Key v) {
            return e.first < v;
        });
        return std::make_pair(it, it != kvs_.end() && it->first == key);
    }
public:
    std::pair<iterator, bool> insert(const Key& key, const Value& value) {
        auto [it, found] = findImpl(key);
        if (found) {
            return std::make_pair(iterator(it), false);
        }
        auto idx{it - kvs_.begin()};
        kvs_.insert(it, std::make_pair(key, value));
        return std::make_pair(iterator(kvs_.begin() + idx), true);
    }

    Value& at(const Key& key) {
        auto [it, found] = findImpl(key);
        if (!found)
            throw std::out_of_range(std::format("{} not found", key));
        return it->second;
    }

    Value& operator[](const Key& key) {
        auto [it, found] = findImpl(key);
        if (found) {
           return it->second;
        }

        auto idx{it - kvs_.begin()};
        kvs_.insert(it, std::make_pair(key, Value()));
        return kvs_[idx].second;
    }


    iterator find(const Key& key) {
        return iterator(findImpl(key).first);
    }


    bool contains(const Key& key) {
        return find(key) != end();
    }

    std::size_t count(const Key& key) {
        return contains(key);
    }

    iterator begin() {
        return iterator(kvs_.begin());
    }

    iterator end() {
        return iterator(kvs_.end());
    }

    std::size_t erase(const Key& key) {
        auto [it, found] = findImpl(key);
        if (!found) {
            return 0;
        }

        kvs_.erase(it);
        return 1;
    }
};

template <typename Key, typename Value>
std::ostream &operator<<(std::ostream &os, FlatMap<Key, Value> &fm)
{
    os << "{";
    for (auto it = fm.begin(); it != fm.end(); ++it)
    {
        if (it != fm.begin())
            os << ", ";
        os << std::format("[{},{}]", it->first, it->second);
    }
    return os << "}";
}

int main () {
    FlatMap<int, std::string> fm;
    fm.insert(1, "abc");
    fm.insert(1, "abd");
    std::cout << fm << std::endl;
    fm[1] = "abe";
    fm[2] += 'x';
    std::cout << fm << std::endl;
    fm.erase(2);
    fm.erase(3);
    std::cout << fm << std::endl;
    fm[0] = "gg";
    std::cout << fm << std::endl;
}