#include "ir/tokenize.hpp"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    std::string text;
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            if (i > 1) text += ' ';
            text += argv[i];
        }
    } else {
        text = "Hello, C++ World!!";
    }
    auto toks = tokenize(text);
    std::cout << "TOKENS(" << toks.size() << "):\n";
    for (const auto& t : toks) std::cout << t << "\n";
    return 0;
}
