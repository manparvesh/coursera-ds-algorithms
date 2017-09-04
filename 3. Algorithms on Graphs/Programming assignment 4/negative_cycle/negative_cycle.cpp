#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

using std::vector;
using std::unordered_map;

bool relax( int u, int v, vector< long long > &prev,
            unordered_map< int, long long > &dist,
            const vector< vector< int > > &cost ) {
    long long new_w = dist[ u ] + cost[ u ][ v ];
    if ( dist[ v ] > new_w ) {
        dist[ v ] = new_w;
        prev[ v ] = u;
        return true;
    }
    return false;
}

int negative_cycle( vector< vector< int > > &adj,
                    vector< vector< int > > &cost ) {
    std::unordered_map< int, long long > dist;
    std::vector< long long > prev( adj.size(), -1 );
    for ( size_t i = 0; i < adj.size(); ++i ) {
        dist[ i ] = std::numeric_limits< int >::max();
    }

    dist[ 0 ] = 0;

    int V = adj.size();
    for ( int i = 0; i < V - 1; ++i ) {
        for ( size_t j = 0; j < adj.size(); ++j ) {
            int u = j;
            const auto &es = adj[ u ];
            for ( int v : es ) {
                relax( u, v, prev, dist, cost );
            }
        }
    }

    for ( size_t j = 0; j < adj.size(); ++j ) {
        int u = j;
        const auto &es = adj[ u ];
        for ( int v : es ) {
            if ( relax( u, v, prev, dist, cost ) )
            { return 1; }
        }
    }
    return 0;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector< vector< int > > adj( n, vector< int >() );
    vector< vector< int > > cost( n, vector< int >( n, -1 ) );
    for ( int i = 0; i < m; i++ ) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[ x - 1 ].push_back( y - 1 );
        cost[ x - 1 ][ y - 1 ] = w;
    }
    std::cout << negative_cycle( adj, cost );

    return 0;
}