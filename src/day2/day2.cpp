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

std::vector<safety_level>
check_reports( const std::vector<std::vector<std::int64_t>> & safety_reports ) {
    std::vector<safety_level> safety_levels( safety_reports.size() );

    for ( const auto & [i, report] : safety_reports | std::views::enumerate ) {
        std::int64_t diff{ 0 };

        for ( const auto & window : report | std::views::slide( 2 ) ) {
            // Unsafe if:
            // - Direction has changed -> unsafe
            // - Difference outside the range [1,3]
            if ( const int64_t new_diff{ window[0] - window[1] };
                 diff * new_diff < 0 || std::abs( new_diff ) < 1
                 || std::abs( new_diff ) > 3 ) {
                safety_levels[i] = safety_level::unsafe;

                // Does removing bad level fix?
                goto unsafe_detected;
            }
            else
                diff = new_diff;
        }

        // If no unsafe data was found...
        safety_levels[i] = safety_level::safe;

    unsafe_detected:
    }

    return safety_levels;
}

