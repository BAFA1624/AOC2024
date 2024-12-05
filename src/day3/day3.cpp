#include "day3.hpp"

#include <iostream>

std::string
parse_input( const std::filesystem::directory_entry & input_file ) {
    if ( !input_file.exists() ) {
        std::cerr << std::format( "{} does not exist.\n",
                                  input_file.path().string() );
        exit( EXIT_FAILURE );
    }

    std::ifstream file_stream( input_file.path(),
                               std::ifstream::ate | std::ifstream::binary );

    if ( !file_stream.is_open() ) {
        std::cerr << std::format( "Failed to open {}.\n",
                                  input_file.path().string() );
        exit( EXIT_FAILURE );
    }

    const auto file_sz{ file_stream.tellg() };
    file_stream.seekg( file_stream.beg );

    std::string file_data( static_cast<std::uint64_t>( file_sz ), '\0' );

    if ( !file_stream.read( file_data.data(), file_data.size() ) ) {
        std::cerr << std::format( "Unable to read {}.\n",
                                  input_file.path().string() );
        exit( EXIT_FAILURE );
    }

    return file_data;
}

std::int64_t
scan_input( const std::string & corrupt_data ) {
    const std::regex pattern{
        "(do\\(\\)|mul\\(\\d{1,3},\\d{1,3}\\)|don't\\(\\))"
    };
    const std::regex enable_pattern{ "do\\(\\)" };
    const std::regex disable_pattern{ "don't\\(\\)" };
    const std::regex calculation_pattern{ "mul\\((\\d{1,3}),(\\d{1,3})\\)" };

    std::string search_string{ corrupt_data };

    bool enable{ true };

    std::int64_t sum{ 0 };

    std::smatch outer_match, inner_match;
    for ( ; std::regex_search( search_string, outer_match, pattern ); ) {
        const std::string substring{ outer_match[1] };
        search_string = outer_match.suffix();

        if ( enable ) {
            // Check if it matches "don't()"
            if ( std::regex_search( substring, inner_match,
                                    disable_pattern ) ) {
                enable = false;
            }
            // Add to the sum
            else if ( std::regex_search( substring, inner_match,
                                         calculation_pattern ) ) {
                sum += ( std::stoll( inner_match[1] )
                         * std::stoll( inner_match[2] ) );
            }
        }
        else {
            // Check for "do()"
            if ( std::regex_search( substring, inner_match, enable_pattern ) ) {
                enable = true;
            }
        }
    }

    return sum;
}
