#pragma once
#include "ir/index.hpp"
#include <string>
#include <utility>
#include <vector>

std::vector<std::pair<int,double>> bm25_query(const Index& I, const std::string& q, int k = 10);
