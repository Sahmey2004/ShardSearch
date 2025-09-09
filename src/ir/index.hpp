// /shardsearch/src/ir/index.hpp
#pragma once
#include <string>
#include <unordered_map>
#include <vector>

struct Posting { int doc; int tf; };

struct Index {
    // term -> postings (doc-sorted)
    std::unordered_map<std::string, std::vector<Posting>> inv;
    std::vector<int> docLen;           // tokens per doc
    int N = 0;                         // number of docs
    double avgdl = 1.0;                // average doc length
    std::vector<std::string> paths;    // docId -> file path
};

Index build_index(const std::vector<std::string>& paths);
