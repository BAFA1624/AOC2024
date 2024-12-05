#include "day1.hpp"
#include "util/simple_csv.hpp"

int
main() {
    const std::filesystem::path base_path{ ".." };

    const std::string           delim{ "   " };
    const std::filesystem::path input{ base_path / "src" / "input"
                                       / "day_1_1.txt" };
    const std::filesystem::path test_input{ base_path / "tests" / "sources"
                                            / "test1.txt" };

    auto id_pair = get_input( input, delim );

    const auto distance{ total_distance( id_pair ) };
    std::cout << std::format( "distance: {}.\n", distance );

    const auto score{ similarity_score( id_pair ) };
    std::cout << std::format( "similarity score: {}.\n", score );
}
