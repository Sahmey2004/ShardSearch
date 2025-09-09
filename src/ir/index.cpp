// /shardsearch/src/ir/index.cpp
#include "ir/index.hpp"
#include "ir/tokenize.hpp"

#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

Index build_index(const std::vector<std::string>& paths) {
    Index I;
    I.N = static_cast<int>(paths.size());
    I.paths = paths;

    // 1) tokenize each doc, record lengths
    std::vector<std::vector<std::string>> docTokens(I.N);
    I.docLen.reserve(I.N);
    for (int d = 0; d < I.N; ++d) {
        std::ifstream in(paths[d]);                    // open file
        std::string s((std::istreambuf_iterator<char>(in)), {}); // slurp file
        docTokens[d] = tokenize(s);                    // tokenize
        I.docLen.push_back(static_cast<int>(docTokens[d].size()));
    }

    // 2) compute average doc length
    long long sum = 0;
    for (int L : I.docLen) sum += L;
    I.avgdl = (I.N > 0) ? std::max(1.0, double(sum) / double(I.N)) : 1.0;

    // 3) term -> (doc -> tf)
    std::unordered_map<std::string, std::unordered_map<int,int>> tf;
    for (int d = 0; d < I.N; ++d) {
        for (const auto& t : docTokens[d]) tf[t][d]++; // count
    }

    // 4) finalize term -> postings (sorted by doc id)
    I.inv.reserve(tf.size());
    for (auto& [term, mp] : tf) {
        auto& vec = I.inv[term];
        vec.reserve(mp.size());
        for (auto& [doc, freq] : mp) vec.push_back({doc, freq});
        std::sort(vec.begin(), vec.end(),
                  [](const Posting& a, const Posting& b){ return a.doc < b.doc; });
    }
    return I;
}
