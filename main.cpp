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
//
struct Node {
    int freq;
    std::string chr;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
};

std::vector<std::shared_ptr<Node>> termFreq(std::string data) {
    std::vector<std::shared_ptr<Node>> terms;
    for(auto &ch : data) {
        std::string sch(1, ch);
        bool found = false;
        for(auto &node : terms) {
            if(node->chr == sch) {
                ++node->freq;
                found = true;
                break;
            }
        }
        if(!found) {
            terms.push_back(std::make_unique<Node>(Node{1, sch}));
        }
    }
    return terms;
}

struct compare_nodes {
    bool operator()(std::shared_ptr<Node> &a, std::shared_ptr<Node> &b) {
        return a->freq > b->freq;
    }
};

std::shared_ptr<Node> generateTree(std::vector<std::shared_ptr<Node>> pq) {
    while(pq.size() > 1) {
        auto left = std::move(pq.back());
        pq.pop_back();
        auto right = std::move(pq.back());
        pq.pop_back();
        pq.push_back(std::make_shared<Node>(Node{left->freq+right->freq, left->chr+right->chr, left, right}));
        std::sort(pq.begin(), pq.end(), compare_nodes());
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
    std::string data = "hel loeoasdfasdfasdfo";
    std::vector<std::shared_ptr<Node>> cf = termFreq(data);
    std::vector<std::shared_ptr<Node>> pq;
    for(auto &leaf : cf) {
        pq.push_back(leaf);
    }
    std::sort(pq.begin(), pq.end(), compare_nodes());

    auto root = generateTree(pq);
    std::unordered_map<std::string, std::string> codes;
    printCodes(root, "", codes);

    for(auto &ch : data) {
        std::string sch(1, ch);
        auto it = codes.find(sch);
        std::cout<<it->second;
    }
    std::cout<<std::endl;
    return 0;
}
