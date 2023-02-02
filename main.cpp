#include <iostream>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
// References:
//     https://resources.nerdfirst.net/huffman

// TODO:
//     [+] Priority Queue
//     [+] Word Frequency
//     [+] Huffman Algorithm
//     [] Use STL priority queue instead of constantly sorting

struct Node {
    int freq;
    std::string chr;
    std::shared_ptr<Node> left, right;
};
std::shared_ptr<Node> generateTree(std::vector<std::shared_ptr<Node>> pq) {
    auto compare = [](const auto &a, const auto &b) { return a->freq > b->freq;};
    while(pq.size() > 1) {
        auto left = std::move(pq.back());
        pq.pop_back();
        auto right = std::move(pq.back());
        pq.pop_back();
        pq.push_back(std::make_shared<Node>(Node{left->freq+right->freq, left->chr+right->chr, left, right}));
        std::sort(pq.begin(), pq.end(), compare);
    }
    return std::move(pq.front());
}

void printCodes(std::shared_ptr<Node> &node, std::string code, std::unordered_map<std::string, std::string> &m) {
    if(!node->left) {
        m[node->chr] = code;
        return;
    }
    printCodes(node->right,code+"1", m);
    printCodes(node->left,code+"0", m);
}

int main() {
    std::string data = "hej med dig";
    std::unordered_map<std::string, int> freq;
    for(auto &ch : data) {
        freq[std::string(1,ch)]++;
    }
    std::vector<std::shared_ptr<Node>> pq;
    for(const auto &kv : freq) {
        std::string kvfirst(kv.first);
        pq.push_back(std::make_shared<Node>(Node{kv.second, kvfirst}));
    }
    auto root = generateTree(pq);
    std::unordered_map<std::string, std::string> codes;
    printCodes(root, "", codes);
    for(auto &ch : data) {
        std::cout<<codes[std::string(1, ch)];
    }
    std::cout<<std::endl;
    return 0;
}
