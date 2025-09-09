// /shardsearch/src/ir/bm25.cpp
#include "ir/bm25.hpp"
#include "ir/tokenize.hpp"
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <vector>

static inline double idf_bm25(int N, int df) {
    return std::log(((N - df + 0.5) / (df + 0.5)) + 1.0);
}

std::vector<std::pair<int,double>> bm25_query(const Index& I, const std::string& q, int k) {
    const double k1 = 1.2;
    const double b  = 0.75;

    std::unordered_map<int,double> score; // doc -> score

    for (const auto& term : tokenize(q)) {
        auto it = I.inv.find(term);
        if (it == I.inv.end()) continue;
        int df = static_cast<int>(it->second.size());
        double idf = idf_bm25(I.N, df);
        for (const Posting& p : it->second) {
            int d  = p.doc;
            int tf = p.tf;
            double denom = tf + k1 * (1.0 - b + b * (double(I.docLen[d]) / I.avgdl));
            score[d] += idf * (tf * (k1 + 1.0)) / denom;
        }
    }

    // Convert to vector and keep only top-k (faster than sorting all)
    std::vector<std::pair<int,double>> out(score.begin(), score.end());
    if ((int)out.size() > k) {
        std::nth_element(out.begin(), out.begin() + k, out.end(),
                         [](auto& a, auto& b){ return a.second > b.second; });
        out.resize(k);
    }
    std::sort(out.begin(), out.end(),
              [](auto& a, auto& b){ return a.second > b.second; });
    return out;
}
