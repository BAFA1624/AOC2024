#pragma once

#include <filesystem>
#include <fstream>
#include <regex>
#include <string>
#include <string_view>

std::string parse_input( const std::filesystem::directory_entry & input_file );

std::int64_t scan_input( const std::string & corrupt_data );
