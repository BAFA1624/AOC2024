#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <string_view>
#include <utility>

enum class direction_t { n, ne, e, se, s, sw, w, nw };

std::string parse_input( const std::filesystem::path & file_path );

std::pair<std::int64_t, std::int64_t>
find_width_height( const std::string_view word_search );

std::uint64_t coord_2_index( const std::int64_t width,
                             const std::int64_t height, const std::int64_t i,
                             const std::int64_t j );

std::pair<std::int64_t, std::int64_t> index_2_coord( const std::int64_t  width,
                                                     const std::int64_t  height,
                                                     const std::uint64_t idx );

bool check_valid_direction( const std::string_view word_search,
                            const direction_t direction, const std::int64_t i,
                            const std::int64_t j, const std::uint64_t length );

std::string get_word( const std::string_view word_search,
                      const std::int64_t width, const std::int64_t height,
                      const direction_t direction, const std::int64_t i,
                      const std::int64_t j, const std::uint64_t length );

std::uint64_t search( const std::string_view word_search,
                      const std::string_view keyword );

std::string gen_random_grid( const std::uint64_t    width,
                             const std::uint64_t    height,
                             const std::string_view character_set );
