#include <bits/stdc++.h>

class SuffixTree
{
private:
    static const int INF = 1000000007;
    static const int RADIX = 256;
    struct Node
    {
        int left;
        const int right;
        Node *suffix_link;
        std::array<Node *, RADIX> next;

        Node(const int left = 0, const int right = INF)
            : left(left), right(right), suffix_link(nullptr), next({{}}) {}
    };

    Node *root, *active_node;
    int remainder, active_length, total_length, active_edge;
    std::string whole;

    void add_suffix_link(Node *&prev, Node *cur) const
    {
        if (prev)
        {
            prev->suffix_link = cur;
        }
        prev = cur;
    }

    void walk_down_active_node()
    {
        while (true)
        {
            if (!active_length || !get_active_edge())
                return;
            int edge_length = std::min(total_length, get_active_edge()->right) - get_active_edge()->left;
            if (active_length < edge_length)
                return;
            Node *next_active_node = get_active_edge();
            active_edge += edge_length;
            active_length -= edge_length;
            active_node = next_active_node;
        }
    }

    void print(const Node *node, std::vector<const Node *> &nodes)
    {
        if (node->suffix_link)
        {
            auto target = node->suffix_link;
            printf("[%d,%d)%s - - > [%d,%d)%s\n", node->left, node->right, whole.substr(node->left, node->right - node->left).c_str(), target->left, target->right, whole.substr(target->left, target->right - target->left).c_str());
        }
        if (node->right == INF)
        {
            for (auto const &node : nodes)
                printf("[%d,%d)%s->", node->left, node->right, whole.substr(node->left, node->right - node->left).c_str());
            printf("[%d, INF)%s\n", node->left, whole.substr(node->left).c_str());
            return;
        }
        nodes.push_back(node);
        for (int i = 0; i < RADIX; i++)
            if (node->next[i])
                print(node->next[i], nodes);
        nodes.pop_back();
    }

    const Node *find_next_node(std::pair<const Node *, int> &cur)
    {
        Node *result = nullptr;
        for (; cur.second < RADIX; cur.second++)
        {
            if (cur.first->next[cur.second])
            {
                result = cur.first->next[cur.second];
                break;
            }
        }
        return result;
    }

    void search(Node *const &root, int &cur_depth, int &best_depth, int &best_depth_right)
    {
        std::stack<std::pair<const Node *, int>> s;
        s.emplace(root, 0);
        while (!s.empty())
        {
            std::pair<const Node *, int> &cur = s.top();
            auto next_node = find_next_node(cur);
            if (next_node)
            {
                if (next_node->right == INF)
                {
                    if (cur_depth > best_depth)
                    {
                        best_depth = cur_depth;
                        best_depth_right = next_node->left;
                    }
                }
                else
                {
                    cur_depth += next_node->right - next_node->left;
                    s.emplace(next_node, 0);
                }
                cur.second++;
            }
            else
            {
                cur_depth -= cur.first->right - cur.first->left;
                s.pop();
            }
        }
    }

    inline Node *get_active_edge()
    {
        return active_node->next[whole[active_edge]];
    }

public:
    SuffixTree()
    {
        root = new Node(0, 0);
        active_node = root;
        active_edge = 0;
        remainder = 0;
        active_length = 0;
        total_length = 0;
    }

    SuffixTree(const std::string &s) : SuffixTree()
    {
        for (auto const &ch : s)
            extend(ch);
    }

    void extend(const char &c)
    {
        remainder++;
        total_length++;
        whole += c;
        Node *prev = nullptr;
        while (remainder)
        {
            if (!active_length)
                active_edge = total_length - 1;
            if ((get_active_edge() && whole[get_active_edge()->left + active_length] == c) || (!get_active_edge() && active_node->next[c]))
            {
                if (!get_active_edge())
                    active_edge = total_length - 1;
                active_length++;
                add_suffix_link(prev, active_node); //observation 3
                walk_down_active_node();
                break;
            }
            if (!get_active_edge()) // !get_active_edge() && !active_node->next[c]
            {
                auto leaf = new Node(total_length - 1);
                active_node->next[c] = leaf;
                add_suffix_link(prev, active_node); // rule 2
            }
            else // get_active_edge() && whole[get_active_edge()->left + active_length] != c
            {
                auto leaf1 = get_active_edge();
                auto node = new Node(leaf1->left, leaf1->left + active_length);
                leaf1->left += active_length;
                active_node->next[whole[active_edge]] = node;
                auto leaf0 = new Node(total_length - 1);
                node->next[whole[leaf0->left]] = leaf0;
                node->next[whole[leaf1->left]] = leaf1;
                add_suffix_link(prev, node); // rule 2
            }
            remainder--;
            if (active_node == root && active_length) //rule 1
            {
                active_length--;
                active_edge = total_length - remainder;
            }
            else if (active_node != root) //rule 3
            {
                active_node = active_node->suffix_link ? active_node->suffix_link : root;
            }
            walk_down_active_node();
        }
    }

    void print()
    {
        std::vector<const Node *> nodes;
        print(root, nodes);
    }

    std::string get_deepest_internal_node()
    {
        int cur_depth = 0, best_depth = 0, best_depth_right;
        search(root, cur_depth, best_depth, best_depth_right);
        return best_depth ? whole.substr(best_depth_right - best_depth, best_depth) : "";
    }
};