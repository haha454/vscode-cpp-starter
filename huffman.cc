#include <bits/stdc++.h>
#include "binary_std_io.hh"
using namespace std;

class Huffman
{
private:
    static const int R = 256;
    BinaryStdIn binaryStdIn;
    BinaryStdOut binaryStdOut;

    class Node
    {
    private:
        const char ch;
        const int freq;
        const Node *left, *right;

    public:
        Node(char ch, int freq, const Node *left, const Node *right) : ch(ch), freq(freq), left(left), right(right)
        {
        }

        const bool isLeaf() const
        {
            assert(((left == nullptr) && (right == nullptr)) || ((left != nullptr) && (right != nullptr)));
            return (left == nullptr) && (right == nullptr);
        }

        const char &get_char() const
        {
            return ch;
        }

        const Node *get_left() const
        {
            return left;
        }

        const Node *get_right() const
        {
            return right;
        }

        const int &get_freq() const
        {
            return freq;
        }
    };

    const Node *buildTrie(const array<int, R> &freq) const
    {
        auto comp = [](const Node *a, const Node *b) { return a->get_freq() > b->get_freq(); };
        priority_queue<Node *, vector<Node *>, decltype(comp)> pq(comp);
        for (int i = 0; i < R; i++)
            if (freq[i] > 0)
                pq.push(new Node(i, freq[i], nullptr, nullptr));

        // add a virtual node (char == 0 || 1) if there is only elements
        if (pq.size() == 1)
        {
            if (freq[0] == 0)
                pq.push(new Node(0, 0, nullptr, nullptr));
            else
                pq.push(new Node(1, 0, nullptr, nullptr));
        }

        // merge two smallest trees
        while (pq.size() > 1)
        {
            Node *left = pq.top();
            pq.pop();
            Node *right = pq.top();
            pq.pop();
            pq.push(new Node(0, left->get_freq() + right->get_freq(), left, right));
        }
        return pq.top();
    }

    // write bitstring-encoded trie to standard output
    void writeTrie(const Node *x)
    {
        if (x->isLeaf())
        {
            binaryStdOut.put_bit(true);
            binaryStdOut.put_char(x->get_char());
            return;
        }
        binaryStdOut.put_bit(false);
        writeTrie(x->get_left());
        writeTrie(x->get_right());
    }

    // make a lookup table from symbols and their encodings
    const void buildCode(array<string, R> &st, const Node *x, string cur) const
    {
        if (!x->isLeaf())
        {
            buildCode(st, x->get_left(), cur + '0');
            buildCode(st, x->get_right(), cur + '1');
        }
        else
        {
            st[x->get_char()] = cur;
        }
    }

    const Node *readTrie()
    {
        bool isLeaf = binaryStdIn.read_bit();
        if (isLeaf)
        {
            return new Node(binaryStdIn.read_char(), -1, nullptr, nullptr);
        }
        else
        {
            return new Node(0, -1, readTrie(), readTrie());
        }
    }

    static void release(const Node *node)
    {
        if (!node)
            return;
        release(node->get_left());
        release(node->get_right());
        delete node;
    }

public:
    Huffman() : binaryStdIn(BinaryStdIn()), binaryStdOut(BinaryStdOut()) {}
    /**
     * Reads a sequence of bits that represents a Huffman-compressed message from
     * standard input; expands them; and writes the results to standard output.
     */
    void expand()
    {
        // read in Huffman trie from input stream
        const Node *root = readTrie();

        // number of bytes to write
        int length = binaryStdIn.read_int();

        // decode using the Huffman trie
        for (int i = 0; i < length; i++)
        {
            const Node *x = root;
            while (!x->isLeaf())
            {
                bool bit = binaryStdIn.read_bit();
                if (bit)
                    x = x->get_right();
                else
                    x = x->get_left();
            }
            binaryStdOut.put_char(x->get_char());
        }
        binaryStdOut.close();
        release(root);
    }

    const void compress()
    {
        string input;
        getline(cin, input);

        array<int, R> freq{};
        for (auto const &ch : input)
            freq[ch]++;

        // build Huffman trie
        const Node *root = buildTrie(freq);

        // print trie for decoder
        writeTrie(root);

        // build code table
        array<string, R> st;
        buildCode(st, root, "");

        // print number of bytes in original uncompressed message
        binaryStdOut.put_int(input.length());

        // use Huffman code to encode input
        for (auto const &ch : input)
        {
            auto code = st.at(ch);
            for (auto const &c : code)
            {
                if (c == '0')
                {
                    binaryStdOut.put_bit(false);
                }
                else if (c == '1')
                {
                    binaryStdOut.put_bit(true);
                }
                else
                    throw exception();
            }
        }

        // close output stream
        binaryStdOut.close();
        release(root);
    }
};

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;
    const char &op = argv[1][0];
    Huffman hm;
    if (op == '-')
        hm.compress();
    else if (op == '+')
        hm.expand();
    else
        throw exception();
    return 0;
}