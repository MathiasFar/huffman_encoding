#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>

// References:
//     https://resources.nerdfirst.net/huffman

// TODO:
//     [+] Priority Queue
//     [+] Word Frequency
//     [] Huffman Algorithm

std::vector<Node*> termFreq(std::string data) {
    std::vector<Node*> terms;
    for(auto &ch : data) {
        bool found = false;
        for(auto &node : terms) {
            if(node->chr == ch) {
                ++node->freq;
                found = true;
                break;
            }
        }
        if(!found) {
            Node *new_node = new Node{1, ch};
            terms.push_back(new_node);
        }
    }
    return terms;
}

int main() {

    std::string data = "hello world hello";
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

    for(auto &n : pQueue) {
        std::cout<<"Char: "<<"'"<<n->chr<<"'"<<std::endl;
        std::cout<<"Freq: "<<n->freq<<std::endl;
        std::cout<<std::endl;
    }

    
    return 0;
}
