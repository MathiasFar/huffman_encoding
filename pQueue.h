#include "tree.h"
#include <vector>

class PQueue {
public:
    Node* add(Node *leaf) {
        int i = 0;
        if(q.size() > 0) {
            while(leaf->freq < q[i]->freq) {
                ++i;
            }
            q.insert(q.begin()+i, leaf);
        } else {
            q.push_back(leaf);
        }
    }
    Node* remove(Node *leaf) {
        
    }
    void printQ() {
        for(auto &n : q) {
            std::cout<<"Freq: "<<n->freq<<std::endl;
        }
    }
private:
    std::vector<Node*> q{};
};
