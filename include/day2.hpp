#pragma once

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <map>
#include <ranges>
#include <regex>
#include <sstream>
#include <string>
#include <utility>

enum class safety_level { unsafe, safe };
enum class direction : std::int64_t { down = -1, constant = 0, up = 1 };

std::vector<std::vector<std::int64_t>>
parse_input( const std::filesystem::directory_entry & file );

std::string report_string( const std::vector<std::int64_t> & report );

std::vector<safety_level>
check_reports( const std::vector<std::vector<std::int64_t>> & safety_reports );
