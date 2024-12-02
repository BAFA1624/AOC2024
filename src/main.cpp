#include "day1.hpp"
#include "util/simple_csv.hpp"

int
main() {
    const std::filesystem::path base_path{
        "/Users/ben/Documents/gitrepos.nosync/AOC2024/"
    };

    const std::string           delim{ "   " };
    const std::filesystem::path input{ base_path / "src" / "input"
                                       / "day_1_1.txt" };
    const std::filesystem::path test_input{ base_path / "tests" / "sources"
                                            / "test1.txt" };

    auto id_pair = get_input( input, delim );

    const auto distance{ total_distance( id_pair ) };
    std::cout << std::format( "distance: {}.\n", distance );

    for ( const auto [l, r] : std::views::zip( id_pair.first, id_pair.second ) )
        std::cout << l << "\t" << r << std::endl;

    const auto score{ similarity_score( id_pair ) };
    std::cout << std::format( "similarity score: {}.\n", score );
}
