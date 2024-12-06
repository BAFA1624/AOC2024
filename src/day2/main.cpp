#include "day2.hpp"

#include <iostream>

int
main() {
    const std::filesystem::path base_path{ ".." };

    const auto input{ base_path / "src" / "input" / "day_2.txt" };
    const auto test_input{ base_path / "tests" / "sources" / "day_2.txt" };

    const auto safety_reports{ parse_input(
        std::filesystem::directory_entry{ test_input } ) };

    const auto safety_levels{ check_reports( safety_reports ) };

    const auto safe_count{ std::count_if(
        safety_levels.cbegin(), safety_levels.cend(),
        []( const auto level ) { return level == safety_level::safe; } ) };

    std::cout << std::format( "Safe reports: {} / {}.\n", safe_count,
                              safety_levels.size() );

    // for ( const auto & [report, safe_unsafe] :
    //       std::views::zip( safety_reports, safety_levels ) ) {
    //     std::cout << std::format(
    //         "{}: {}\n", report_string( report ),
    //         ( safe_unsafe == safety_level::safe ? "Safe" : "Unsafe" ) );
    // }
}
