#include "day4.hpp"

#include <fstream>
#include <iostream>

std::string
parse_input( const std::filesystem::path & file_path ) {
    if ( !std::filesystem::directory_entry{ file_path }.exists() ) {
        std::cerr << std::format( "{} does not exist.\n", file_path.string() );
        exit( EXIT_FAILURE );
    }

    std::ifstream file_stream( file_path,
                               std::ifstream::ate | std::ifstream::binary );
    if ( !file_stream.is_open() ) {
        std::cerr << std::format( "Failed to open {}.\n", file_path.string() );
        exit( EXIT_FAILURE );
    }

    const auto file_sz{ file_stream.tellg() };
    file_stream.seekg( file_stream.beg );

    std::string file_data( static_cast<std::uint64_t>( file_sz ), '\0' );
    if ( !file_stream.read( file_data.data(),
                            static_cast<std::int64_t>( file_data.size() ) ) ) {
        std::cerr << std::format( "Failed to read {}.\n", file_path.string() );
        exit( EXIT_FAILURE );
    }

    return file_data;
}

