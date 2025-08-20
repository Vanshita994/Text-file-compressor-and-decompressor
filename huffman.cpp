#include "huffman.h"
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare { bool operator()(Node* a, Node* b) { return a->freq > b->freq; } };

void buildCodes(Node *root, const std::string &str, std::unordered_map<char, std::string> &codes) {
    if (!root) return;
    if (!root->left && !root->right) codes[root->ch] = str;
    buildCodes(root->left, str + "0", codes);
    buildCodes(root->right, str + "1", codes);
}

void releaseTree(Node *root) {
    if (root) {
        releaseTree(root->left);
        releaseTree(root->right);
        delete root;
    }
}

void HuffmanCoding::compress(const std::string &inputFile, const std::string &outputFile) {
    std::ifstream fin(inputFile, std::ios::binary);
    if (!fin.is_open()) return;
    std::string text((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    fin.close();

    std::unordered_map<char, int> freq;
    for (char ch : text) freq[ch]++;
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (auto p : freq) pq.push(new Node(p.first, p.second));
    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        Node *parent = new Node('\0', left->freq + right->freq);
        parent->left = left; parent->right = right;
        pq.push(parent);
    }
    Node *root = pq.top();

    std::unordered_map<char, std::string> codes;
    buildCodes(root, "", codes);

    std::ofstream fout(outputFile, std::ios::binary);
    fout << codes.size() << '\n';
    for(auto c : codes) fout << (int)c.first << ' ' << c.second << '\n';
    std::string encoded;
    for (char ch : text) encoded += codes[ch];
    fout << encoded;
    fout.close();

    releaseTree(root);
}

void HuffmanCoding::decompress(const std::string &inputFile, const std::string &outputFile) {
    std::ifstream fin(inputFile, std::ios::binary);
    if (!fin.is_open()) return;
    size_t codeSize; fin >> codeSize;
    std::unordered_map<std::string, char> decodeMap;
    for (size_t i=0; i<codeSize; ++i) {
        int chInt;
        std::string code;
        fin >> chInt >> code;
        char ch = (char)chInt;
        decodeMap[code] = ch;
    }
    std::string encoded;
    fin >> encoded;
    fin.close();

    std::ofstream fout(outputFile, std::ios::binary);
    std::string cur;
    for (char bit : encoded) {
        cur += bit;
        if (decodeMap.count(cur)) {
            fout.put(decodeMap[cur]);
            cur.clear();
        }
    }
    fout.close();
}
