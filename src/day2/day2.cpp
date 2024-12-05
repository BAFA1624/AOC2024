#include "day2.hpp"

#include <iostream>

std::vector<std::vector<std::int64_t>>
parse_input( const std::filesystem::directory_entry & file ) {
    if ( !file.exists() ) {
        std::cerr << std::format( "{} does not exist.\n",
                                  file.path().string() );
        exit( EXIT_FAILURE );
    }

    std::ifstream file_stream( file.path(),
                               std::ifstream::ate | std::ifstream::binary );

    const auto file_sz{ file_stream.tellg() };
    file_stream.seekg( file_stream.beg );

    std::string file_data( file_sz, '\0' );

    if ( !file_stream.read( file_data.data(), file_sz ) ) {
        std::cerr << std::format( "Failed to read file data.\n" );
    }

    std::vector<std::vector<std::int64_t>> safety_reports;
    for ( const auto line : std::views::split( file_data, '\n' ) ) {
        safety_reports.push_back( std::vector<std::int64_t>{} );

        for ( const auto value_str : std::views::split( line, ' ' ) ) {
            safety_reports.back().push_back( std::stoll(
                std::string( value_str.data(), value_str.size() ) ) );
        }

        if ( safety_reports.back().empty() ) {
            safety_reports.pop_back();
        }
    }

    return safety_reports;
}

std::string
report_string( const std::vector<std::int64_t> & report ) {
    std::string output{};

    for ( const auto x : report ) { output += std::to_string( x ) + " "; }
    output.pop_back();

    return output;
}

// std::vector<safety_level>
// check_reports( const std::vector<std::vector<std::int64_t>> & safety_reports
// ) {
//     std::vector<safety_level> safety_levels( safety_reports.size() );
//
//     for ( const auto & [i, report] : safety_reports | std::views::enumerate )
//     {
//         std::int64_t unsafe_count{ 0 };
//         std::int64_t diff{ 0 };
//
//         // Unsafe if:
//         // - Direction has changed
//         // - Difference outside the range [1,3]
//         for ( const auto [i, level] : report | std::views::enumerate ) {
//             // If first level
//             if ( i == 0 ) {
//                 // Check against 1 ahead
//
//             }
//             // If last level
//             if ( i == report.size() - 1 ) {}
//         }
//     }
//
//     return safety_levels;
// }

std::vector<safety_level>
check_reports( const std::vector<std::vector<std::int64_t>> & safety_reports ) {
    std::vector<safety_level> safety_levels( safety_reports.size() );

    for ( const auto & [i, report] : safety_reports | std::views::enumerate ) {
        // Analyze report:
        std::vector<std::int64_t> level_differences( report.size() - 1 );
        std::vector<direction>    level_directions( report.size() - 1 );
        std::vector<safety_level> window_safeties( report.size() - 1 );
        std::vector<std::string>  level_status( report.size(), "\u2713" );

        // First pass, check all differences & directions
        //
        for ( const auto & [j, window] :
              report | std::views::slide( 2 ) | std::views::enumerate ) {
            level_differences[j] = window[1] - window[0];
            level_directions[j] =
                level_differences[j] == 0 ?
                    direction::constant :
                    ( level_differences[j] > 0 ? direction::up :
                                                 direction::down );
            if ( std::abs( level_differences[j] ) > 3
                 || level_differences[j] == 0 ) {
                level_status[j] = "\u2717";
                level_status[j + 1] = "\u2717";
            }
            else if ( ( j != 0
                        && static_cast<std::size_t>( j ) != report.size() - 2 )
                      && level_directions[j] != level_directions[j - 1] ) {
                level_status[j] = "\u2717";
                level_status[j + 1] = "\u2717";
            }
        }

        std::cout << std::format( "Report: {}\n", report_string( report ) );
        std::cout << "Status: ";
        for ( const auto & status : level_status ) {
            std::cout << status << " ";
        }
        std::cout << std::format( "\nDifferences: {}\n",
                                  report_string( level_differences ) );
        std::cout << "Directions: ";
        for ( const auto [j, direction] :
              level_directions | std::views::enumerate ) {
            switch ( direction ) {
            case direction::down: {
                std::cout << "\u2193";
            } break;
            case direction::constant: {
                std::cout << "-";
            } break;
            case direction::up: {
                std::cout << "\u2191";
            } break;
            }

            if ( j != level_directions.size() - 1 )
                std::cout << " ";
        }
        std::cout << "\n\n";

        // If no unsafe data was found...
        safety_levels[i] = safety_level::safe;

    unsafe_detected:
        safety_levels[i] = safety_level::unsafe;
    }

    return safety_levels;
}

