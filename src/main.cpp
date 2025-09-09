// /shardsearch/src/main.cpp
#include "ir/index.hpp"
#include "ir/bm25.hpp"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "usage: searchd <docs_dir> \"<query>\"\n";
        return 1;
    }
    std::vector<std::string> paths;
    for (auto& p : std::filesystem::directory_iterator(argv[1]))
        if (p.is_regular_file()) paths.push_back(p.path().string());

    auto idx = build_index(paths);
    auto res = bm25_query(idx, argv[2], 10);

    for (auto& [doc, score] : res)
        std::cout << idx.paths[doc] << "\t" << score << "\n";
}
