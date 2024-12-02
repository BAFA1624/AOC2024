#pragma once

#include "util/simple_csv.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string_view>
#include <utility>
#include <vector>



std::pair<std::vector<std::int64_t>, std::vector<std::int64_t>>
get_input( const std::filesystem::path & path,
           const std::string_view        delim = "   " );

std::int64_t total_distance(
    std::pair<std::vector<std::int64_t>, std::vector<std::int64_t>> & data );

std::int64_t
similarity_score( std::pair<std::vector<std::int64_t>,
                            std::vector<std::int64_t>> & sorted_data );

