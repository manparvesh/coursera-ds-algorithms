#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <set>
#include <utility>
#include <vector>

#include <ext/pb_ds/priority_queue.hpp>

using std::vector;
using std::map;
using std::pair;

typedef std::pair< int, int > Node;

struct Double {
    Double() : isinf(true), val(0.0) {}
    explicit Double(double val) : isinf(false), val(val) {}
    bool isinf;
    double val;
};

bool operator>( const Double &l, const Double &r ) {
    if ( !l.isinf && !r.isinf )
    { return l.val > r.val; }
    else if ( l.isinf && !r.isinf )
    { return true; }
    else
    { return false; }
}

Double dist( const pair< int, int > &l, const pair< int, int > &r ) {
    double xdiff = static_cast< double >( l.first ) - r.first;
    double ydiff = static_cast< double >( l.second ) - r.second;
    return Double( std::sqrt( xdiff * xdiff + ydiff * ydiff ) );
}

double minimum_distance( const vector< Node > &nodes ) {
    double result = 0.;

    map< Node, Double > cost;
    auto hashcomp = [&cost]( const Node & l, const Node & r ) {
        return cost[ l ] > cost[ r ];
    };
    __gnu_pbds::priority_queue< Node, decltype( hashcomp ),
               __gnu_pbds::binomial_heap_tag >
               prioq( hashcomp );

    for ( size_t i = 0; i < nodes.size(); ++i ) {
        cost[ nodes[ i ] ] = Double();
    }

    const Node &u0 = nodes[ 0 ];
    cost[ u0 ] = Double( 0.0 );

    std::set< Node > qs;
    for ( size_t i = 0; i < nodes.size(); ++i ) {
        prioq.push( nodes[ i ] );
        qs.insert( nodes[ i ] );
    }

    while ( !prioq.empty() ) {
        Node v = prioq.top();
        prioq.pop();
        qs.erase( v );

        for ( const auto &z : nodes ) {
            if ( z != v && ( qs.find( z ) != qs.end() ) ) {
                if ( cost[ z ] > dist( v, z ) ) {
                    cost[ z ] = dist( v, z );
                    prioq.push( z );
                }
            }
        }
    }

    for ( const auto &n : nodes ) {
        Double d = cost[ n ];
        if ( !d.isinf )
        { result += d.val; }
    }

    return result;
}

int main() {
    size_t n;
    std::cin >> n;
    vector< Node > ns;
    for ( size_t i = 0; i < n; i++ ) {
        Node n;
        std::cin >> n.first >> n.second;
        ns.push_back( n );
    }
    std::cout << std::setprecision( 10 ) << minimum_distance( ns ) << std::endl;
}