#include "day4.hpp"

#include <iostream>

int
main() {
    const std::filesystem::path base_path{ ".." };

    const auto test_input{ base_path / "tests" / "sources" / "day_4.txt" };
    const auto input{ base_path / "src" / "input" / "day_4.txt" };

    // const auto word_search{ parse_input( input ) };
    const auto keyword{ "XMAS" };
    const auto word_search{ gen_random_grid( 100, 100, keyword ) };
    std::cout << word_search << std::endl;

    const auto word_count{ search( word_search, keyword ) };

    std::cout << std::format( "{} count: {}.\n", keyword, word_count );
}
