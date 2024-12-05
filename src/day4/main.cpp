#include "day4.hpp"

#include <iostream>

int
main() {
    const std::filesystem::path base_path{ ".." };

    const auto test_input{ base_path / "tests" / "sources" / "day_4.txt" };
    const auto input{ base_path / "src" / "input" / "day_4.txt" };

    const auto word_search{ parse_input( test_input ) };
}
