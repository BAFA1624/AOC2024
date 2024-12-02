#include "day1.hpp"

std::pair<std::vector<std::int64_t>, std::vector<std::int64_t>>
get_input( const std::filesystem::path & path, const std::string_view delim ) {
    const auto csv_data{ CSV::SimpleCSV<std::int64_t>( path, false, 0, delim,
                                                       256 ) };

    return std::make_pair( csv_data.col( 0 ), csv_data.col( 1 ) );
}

std::int64_t
total_distance(
    std::pair<std::vector<std::int64_t>, std::vector<std::int64_t>> & data ) {
    auto & [left_ids, right_ids] = data;

    // Sort inputs
    std::sort( left_ids.begin(), left_ids.end() );
    std::sort( right_ids.begin(), right_ids.end() );

    // Calculate distances
    std::int64_t distance{ 0 };
    for ( auto [l, r] : std::views::zip( left_ids, right_ids ) ) {
        distance += std::abs( l - r );
    }

    return distance;
}

std::int64_t
similarity_score( std::pair<std::vector<std::int64_t>,
                            std::vector<std::int64_t>> & sorted_data ) {
    //  Reference to the lists
    auto & [left_ids, right_ids] = sorted_data;

    std::map<std::int64_t, std::pair<std::int64_t, std::int64_t>> id_list_count;
    for ( const auto key : left_ids ) {
        if ( id_list_count.contains( key ) )
            id_list_count[key].first++;
        else
            id_list_count.insert( std::pair( key, std::pair{ 1, 0 } ) );
    }

    // Iter. through keys, search right_ids for occurence of keys.
    // ids are sorted -> new key when right_ids[rpos] > key
    std::size_t rpos{ 0 };
    for ( const auto & key : id_list_count | std::views::keys ) {
        std::cout << std::format( "Scanning key: {}\n", key );
        while ( right_ids[rpos] <= key ) {
            if ( right_ids[rpos] == key ) {
                id_list_count[key].second++;
                std::cout << std::format( "\tcount: {}\n",
                                          id_list_count[key].second );
            }
            rpos++;
        }

        // if ( id_list_count[key].second == 0 ) {
        //     std::cout << std::format( "No instances found in rlist: {}\n",
        //                               key );
        //     id_list_count[key].first = 0;
        // }
    }

    std::int64_t similarity_score{ 0 };
    for ( const auto [key, occurences] : id_list_count ) {
        std::cout << std::format( "{} * {} * {} -> {}\n", key, occurences.first,
                                  occurences.second,
                                  key * occurences.first * occurences.second );
        similarity_score += ( key * occurences.first * occurences.second );
    }

    return similarity_score;
}
