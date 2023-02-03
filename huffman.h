#include <memory>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>

class Huffman {
public:
    std::unordered_map<std::string, std::string> encode(std::string data);   

private:
    struct Node {
        int freq;
        std::string chr;
        std::shared_ptr<Node> left, right;
    };
    std::shared_ptr<Node> generateTree(std::vector<std::shared_ptr<Node>> pq);
    void generateCodes(std::shared_ptr<Node> &node, std::string code, std::unordered_map<std::string, std::string> &m);
};

std::unordered_map<std::string, std::string> Huffman::encode(std::string data) {
    std::unordered_map<std::string, int> freq;
    for(auto &ch : data) {
        ++freq[std::string(1, ch)];
    }
    std::vector<std::shared_ptr<Huffman::Node>> pq;
    for(const auto &kv : freq) {
        std::string kvfirst(kv.first);
        pq.push_back(std::make_shared<Huffman::Node>(Huffman::Node{kv.second, kvfirst}));
    }
    auto root = generateTree(pq);
    std::unordered_map<std::string, std::string> codes;
    generateCodes(root, "", codes);
    return codes;
}

void Huffman::generateCodes(std::shared_ptr<Huffman::Node> &node, std::string code, std::unordered_map<std::string, std::string> &m) {
    if(!node->left) {
        m[node->chr] = code;
        return;
    }
    generateCodes(node->right, code+"1", m);
    generateCodes(node->left, code+"0", m);
}

std::shared_ptr<Huffman::Node> Huffman::generateTree(std::vector<std::shared_ptr<Huffman::Node>> pq) {
    auto compare = [](const auto &a, const auto &b) { return a->freq > b->freq;};
    while(pq.size() > 1) {
        auto left = std::move(pq.back());
        pq.pop_back();
        auto right = std::move(pq.back());
        pq.pop_back();
        pq.push_back(std::make_shared<Huffman::Node>(Huffman::Node{left->freq+right->freq, left->chr+right->chr, left, right}));
        std::sort(pq.begin(), pq.end(), compare);
    }
    return std::move(pq.front());
}
