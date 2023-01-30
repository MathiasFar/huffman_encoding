#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
/* #include "pQueue.h" */
#include "tree.h"

// References:
//     https://resources.nerdfirst.net/huffman

// TODO:
//     [+] Priority Queue
//     [] Word Frequency
//     [] Huffman Algorithm




std::vector<std::string> splitStr(std::string &s, char del) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string token;
    while(getline(ss, token, del)) {
        tokens.push_back(token);
    }
    return tokens;
}


std::vector<Node*> termFreq(std::string data) {
    std::vector<std::string> words = splitStr(data, ' ');
    std::vector<Node*> terms;
    for(auto &word : words) {
        if(terms.empty()) {
            Node *new_node = new Node();
            new_node->word = word;
            new_node->freq = 1;
            terms.push_back(new_node);
        } else {
            for(int j = 0; j < terms.size(); ++j) {
                if(std::strcmp(terms[j]->word.c_str(), word.c_str()) == 0) {
                    terms[j]->freq += 1; 
                } else {
                    Node *new_node = new Node();
                    new_node->word = word;
                    new_node->freq = 1;
                    terms.push_back(new_node);
                }
            }
        }
    }
    return terms;
}

int main() {

    std::string data = "hello world hello";
    std::vector<Node*> q = termFreq(data);

    for(auto &n : q) {
        std::cout<<"Word: "<<n->word<<std::endl;
        std::cout<<"Freq: "<<n->freq<<std::endl;
        std::cout<<std::endl;
    }

    
    return 0;
}
