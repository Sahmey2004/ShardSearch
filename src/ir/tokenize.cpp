#include "ir/tokenize.hpp"
#include <cctype>
#include <string>
#include <vector>

std::vector<std::string> tokenize(const std::string& text){
    std::vector<std::string> out;
    std::string cur;
    out.reserve(text.size() / 5);

    for(unsigned char uc : text){
        if(std::isalpha(uc)){
            cur.push_back(char(std::tolower(uc)));

        }
        else if (!cur.empty()){
            out.push_back(cur);
            cur.clear();
        }
     
    }
    if(!cur.empty()) out.push_back(cur);
    return out;
}