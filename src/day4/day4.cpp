#include "day4.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>

const std::map<direction_t, std::pair<std::int64_t, std::int64_t>>
    direction_vectors{
        { direction_t::n, { 0, 1 } },  { direction_t::ne, { 1, 1 } },
        { direction_t::e, { 1, 0 } },  { direction_t::se, { 1, -1 } },
        { direction_t::s, { 0, -1 } }, { direction_t::sw, { -1, -1 } },
        { direction_t::w, { -1, 0 } }, { direction_t::nw, { -1, 1 } }
    };

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

std::pair<std::int64_t, std::int64_t>
find_width_height( const std::string_view word_search ) {
    const auto height{ static_cast<std::int64_t>(
        std::count_if( word_search.cbegin(), word_search.cend(),
                       []( const char c ) { return c == '\n'; } ) ) };
    if ( height == 0 ) {
        std::cerr << std::format( "Invalid word search. height = 0.\n" );
        exit( EXIT_FAILURE );
    }

    if ( static_cast<std::int64_t>( word_search.size() ) % height != 0 ) {
        std::cerr << std::format(
            "Invalid word search. All rows must be the same length.\n" );
        exit( EXIT_FAILURE );
    }

    // - height to remove newline characters
    const auto width{ static_cast<std::int64_t>(
        ( static_cast<std::int64_t>( word_search.size() ) - height )
        / height ) };

    return std::make_pair( width, height );
}

std::uint64_t
coord_2_index( const std::int64_t                  width,
               [[maybe_unused]] const std::int64_t height, const std::int64_t i,
               const std::int64_t j ) {
    // width + 1 to account for newlines
    return static_cast<std::uint64_t>( j * ( width + 1 ) + i );
}

std::pair<std::int64_t, std::int64_t>
index_2_coord( const std::int64_t                  width,
               [[maybe_unused]] const std::int64_t height,
               const std::uint64_t                 idx ) {
    return { static_cast<std::int64_t>( idx ) % ( width + 1 ),
             static_cast<std::int64_t>( idx ) / ( width + 1 ) };
}

bool
check_valid_direction( const std::int64_t width, std::int64_t height,
                       const direction_t direction, const std::int64_t i,
                       const std::int64_t j, const std::uint64_t length ) {
    const auto mapping{ direction_vectors.at( direction ) };

    for ( std::int64_t n{ 1 }; n < static_cast<std::int64_t>( length ); ++n ) {
        const auto new_i{ i + n * mapping.first },
            new_j{ j + n * mapping.second };

        // Check if out of bounds
        if ( new_i >= width || new_j >= height )
            return false;
    }

    return true;
}

std::string
get_word( const std::string_view word_search, const std::int64_t width,
          const std::int64_t height, const direction_t direction,
          const std::int64_t i, const std::int64_t j,
          const std::uint64_t length ) {
    // Assumes direction is valid
    const auto mapping{ direction_vectors.at( direction ) };

    std::string word( length, '\0' );
    for ( std::uint64_t n{ 0 }; n < length; ++n ) {
        const auto index{ coord_2_index(
            width, height, i + static_cast<std::int64_t>( n ) * mapping.first,
            j + static_cast<std::int64_t>( n ) * mapping.second ) };
        word[n] = word_search[index];
    }

    return word;
}

std::uint64_t
search( const std::string_view word_search, const std::string_view keyword ) {
    // Determine width & height of word search
    const auto [width, height] = find_width_height( word_search );

    // Finding all occurences of first letter.
    using direction_mask_t = typename std::map<direction_t, bool>;
    const direction_mask_t default_mask{
        { direction_t::n, true }, { direction_t::ne, true },
        { direction_t::e, true }, { direction_t::se, true },
        { direction_t::s, true }, { direction_t::sw, true },
        { direction_t::w, true }, { direction_t::nw, true }
    };

    // First pass: Determine positions of all first letters
    std::map<std::uint64_t, direction_mask_t> first_letters;
    for ( std::int64_t j{ 0 }; j < height; ++j ) {
        for ( std::int64_t i{ 0 }; i < width; ++i ) {
            const auto index{ coord_2_index( width, height, i, j ) };
            if ( word_search[index] == keyword[0] )
                first_letters[index] = default_mask;
        }
    }

    // Second pass: Determine valid directions around all first letters
    for ( auto & [index, direction_mask] : first_letters ) {
        for ( auto & [direction, is_valid] : direction_mask ) {
            const auto [i, j] = index_2_coord( width, height, index );
            is_valid = check_valid_direction( width, height, direction, i, j,
                                              keyword.size() );
        }
    }

    // Third pass: Determine which directions match keyword
    std::uint64_t word_count{ 0 };
    for ( const auto & [index, direction_mask] : first_letters ) {
        for ( const auto & [direction, is_valid] : direction_mask ) {
            if ( is_valid ) {
                const auto [i, j] = index_2_coord( width, height, index );
                const auto word{ get_word( word_search, width, height,
                                           direction, i, j, keyword.size() ) };
                if ( word == keyword )
                    word_count++;
            }
        }
    }

    return word_count;
}

std::string
gen_random_grid( const std::uint64_t width, const std::uint64_t height,
                 const std::string_view character_set ) {
    std::string grid( ( width + 1 ) * height, '\n' );

    std::random_device              rd;
    std::mt19937                    gen( rd() );
    std::uniform_int_distribution<> distrib(
        0, static_cast<int>( character_set.size() - 1 ) );

    for ( std::uint64_t j{ 0 }; j < height; ++j ) {
        for ( std::uint64_t i{ 0 }; i < width; ++i ) {
            const auto index{ coord_2_index(
                static_cast<std::int64_t>( width ),
                static_cast<std::int64_t>( height ),
                static_cast<std::int64_t>( i ),
                static_cast<std::int64_t>( j ) ) };

            grid[index] =
                character_set[static_cast<std::size_t>( distrib( gen ) )];
        }
    }

    return grid;
}
