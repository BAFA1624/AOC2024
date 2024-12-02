#include "day1.hpp"
#include "tests.hpp"

int
main( const int argc, const char * const argv[] ) {
    const std::string prog_name( argv[0] );

    const std::filesystem::path base_path{
        "/Users/ben/Documents/gitrepos.nosync/AOC2024/"
    };

    const auto test_sources{ base_path / "tests" / "sources" };

    const std::string delim{ "   " };

    const auto test{ test_sources / ( prog_name + ".txt" ) };
    const auto result{ test_sources / ( prog_name + "results.txt" ) };

    const auto data_csv{ CSV::SimpleCSV<std::int64_t>(
        /*filename*/ test, /*col_titles*/ false,
        /*skip_header*/ 0, /*delim*/ delim,
        /*max_line_size*/ 256 ) };

    std::ifstream result_file( result,
                               std::ifstream::ate | std::ifstream::binary );

    const auto left_ids{ data_csv.col( 0 ) };
    const auto right_ids{ data_csv.col( 1 ) };

    for ( int i{ 0 }; i < left_ids.size(); ++i ) {
        std::cout << std::format( "{} {}\n", left_ids[i], right_ids[i] );
    }
}
