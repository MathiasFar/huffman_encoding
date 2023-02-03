#include <iostream>
#include "Huffman.h"

int main() {
    Huffman hf;
    std::string data("Hello");
    std::unordered_map<std::string, std::string> codes = hf.encode(data);

    for(auto &ch : data) {
        std::cout<<codes[std::string(1, ch)];
    }

    return 0;
}
