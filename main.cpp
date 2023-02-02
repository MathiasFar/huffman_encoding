#include <iostream>
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
    Node *left;
    Node *right;
};

std::vector<Node*> termFreq(std::string data) {
    std::vector<Node*> terms;
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
            Node *new_node = new Node{1, sch};
            terms.push_back(new_node);
        }
    }
    return terms;
}

struct compare_nodes {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

Node* generateTree(std::vector<Node*> pq) {
    while(pq.size() > 1) {
        Node *left = pq.back();
        pq.pop_back();
        Node *right = pq.back();
        pq.pop_back();
        Node *new_node = new Node{left->freq+right->freq, left->chr+right->chr, left, right};
        pq.push_back(new_node);
        std::sort(pq.begin(), pq.end(), compare_nodes());
    }
    return pq.front();
}

void printCodes(Node *node, std::string code, std::unordered_map<std::string, std::string> &m) {
    if(node->left == nullptr) {
        /* std::cout<<node->chr<<": "<<code<<std::endl; */
        m[node->chr] = code;
        return;
    }
    printCodes(node->right,code+"1", m);
    printCodes(node->left,code+"0", m);
}


int main() {
    std::string data = "hel loeoasdfasdfasdfo";
    std::vector<Node*> cf = termFreq(data);
    std::vector<Node*> pq;
    for(auto &leaf : cf) {
        pq.push_back(leaf);
    }
    std::sort(pq.begin(), pq.end(), compare_nodes());

    Node *root = generateTree(pq);
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
