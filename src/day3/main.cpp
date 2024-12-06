#include "day3.hpp"

#include <iostream>

int
main() {
    const std::filesystem::path base_path{ ".." };

    const auto test_input{ base_path / "tests" / "sources" / "day_3.txt" };
    const auto input{ base_path / "src" / "input" / "day_3.txt" };

    const auto file{ parse_input( std::filesystem::directory_entry{ input } ) };

    const auto result{ scan_input( file ) };
    std::cout << result << std::endl;
}
