#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include "tree.h"

// References:
//     https://resources.nerdfirst.net/huffman

// TODO:
//     [+] Priority Queue
//     [+] Word Frequency
//     [+] Huffman Algorithm
//     [] make it work with spaces idk why it doesnt
//
struct Node {
    int freq;
    std::string chr;
    Node *left;
    Node *right;
};

struct Code {
    std::string ch;
    std::string code;
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
        /* std::cout<<left->chr<<": "<<left->freq<<std::endl; */
        /* std::cout<<right->chr<<": "<<right->freq<<std::endl; */
        pq.push_back(new_node);
        std::sort(pq.begin(), pq.end(), compare_nodes());
    }
    return pq.front();
}

void printCodes(Node *node, std::string code, std::vector<Code*> &vectorCodes) {
    if(node->left == nullptr) {
        std::cout<<node->chr<<": "<<code<<std::endl;
        Code *c = new Code{node->chr, code};
        vectorCodes.push_back(c);
        return;
    }
    printCodes(node->right,code+"1", vectorCodes);
    printCodes(node->left,code+"0", vectorCodes);

}


int main() {
    std::string data = "helloeoasdfasdfasdfo";
    std::vector<Node*> cf = termFreq(data);
    std::vector<Node*> pQueue;
    for(auto &leaf : cf) {
        int i = 0;
        if(pQueue.size() > 0) {
            while(i < pQueue.size() and leaf->freq < pQueue[i]->freq) {
                ++i;
            }
            pQueue.insert(pQueue.begin()+i, leaf);
        } else {
            pQueue.push_back(leaf);
        }
    }

    /* for(auto &n : pQueue) { */
    /*     std::cout<<n->chr<<": "<<n->freq<<std::endl; */
    /* } */

    Node *root = generateTree(pQueue);
    /* std::cout<<root->left->chr<<std::endl; */
    /* std::cout<<root->right->chr<<std::endl; */
    std::vector<Code*> codes;
    printCodes(root, "", codes);

    for(auto &ch : data) {
        std::string sch(1, ch);    
        for(auto &x : codes) {
            if(sch == x->ch) {
                std::cout<<x->code;
            }
        }
    }
    return 0;
}
