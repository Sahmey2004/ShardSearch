#include "ir/index.hpp"
#include <filesystem>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 2) { std::cerr << "usage: index_demo <docs_dir>\n"; return 1; }
    std::vector<std::string> paths;
    for (auto& p : std::filesystem::directory_iterator(argv[1]))
        if (p.is_regular_file()) paths.push_back(p.path().string());

    auto idx = build_index(paths);
    std::cout << "Docs: " << idx.N << "\n";
    std::cout << "Avg length: " << idx.avgdl << "\n";
    std::cout << "Unique terms: " << idx.inv.size() << "\n";
    if (idx.N > 0) std::cout << "Doc0 length: " << idx.docLen[0] << "\n";
    return 0;
}
