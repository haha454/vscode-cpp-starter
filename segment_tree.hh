#include <bits/stdc++.h>

// problem-specific struct
struct segment {
    int value, count;

    segment(int v = 0, int c = 0) : value(v), count(c) {}

    void join(const segment &other) {
        if (value == other.value) {
            count += other.count;
            return;
        }

        if (count >= other.count) {
            count -= other.count;
        } else {
            value = other.value;
            count = other.count - count;
        }
    }

    void join(const segment &a, const segment &b) {
        *this = a;
        join(b);
    }
};

struct seg_tree {
    int leaf_n = 0;
    std::vector<segment> tree;

    seg_tree(int n = 0) {
        if (n > 0)
            init(n);
    }

    void init(int n) {
        leaf_n = 1;

        while (leaf_n < n)
            leaf_n *= 2;

        tree.assign(2 * leaf_n, segment());
    }

    // Builds our tree from an array in O(n).
    void build(const std::vector<segment> &initial) {
        int n = initial.size();
        assert(n <= leaf_n);

        for (int i = 0; i < n; i++)
            tree[leaf_n + i] = initial[i];

        for (int position = leaf_n - 1; position >= 1; position--)
            tree[position].join(tree[2 * position], tree[2 * position + 1]);
    }

    template<typename T_range_op>
    void process_range(int position, int start, int end, int a, int b, bool needs_join, T_range_op &&range_op) {
        if (a <= start && end <= b) {
            range_op(position);
            return;
        }

        if (position >= tree_n)
            return;

        int mid = (start + end) / 2;
        if (a < mid) 
            process_range(2 * position, start, mid, a, b, needs_join, range_op);
        if (b > mid) 
            process_range(2 * position + 1, mid, end, a, b, needs_join, range_op);
        if (needs_join) 
            tree[position].join(tree[2 * position], tree[2 * position + 1]);
    }

    segment query(int a, int b) {
        assert(0 <= a && a <= b && b <= leaf_n);
        segment answer;

        process_range(1, 0, leaf_n, a, b, false, [&](int position) {
            answer.join(tree[position]);
        });

        return answer;
    }
};