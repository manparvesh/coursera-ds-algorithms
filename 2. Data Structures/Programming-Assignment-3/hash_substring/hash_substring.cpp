#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;

static const size_t multiplier = 263;
static const size_t prime = 1000000007;

unsigned long long poly_hash( const string& s ) {
    unsigned long long hash = 0;
    for ( int i = static_cast< int >( s.size() ) - 1; i >= 0; --i ) hash = ( hash * multiplier + s[i] ) % prime;
    return hash;
}

std::vector< unsigned long long > precompute_hashes( const std::string& T, const std::string& P, long long p,
        long long x ) {
    std::vector< unsigned long long > H( T.size() - P.size() + 1 );
    std::string sub = T.substr( T.size() - P.size(), P.size() );
    H[T.size() - P.size()] = poly_hash( sub );

    unsigned long long y = 1;
    for ( size_t i = 1; i <= P.size(); ++i ) {
        y = ( y * x ) % p;
    }

    for ( int i = static_cast< int >( T.size() - P.size() - 1 ); i >= 0; --i ) {
        H[i] = ( ( x * H[i + 1] + T[i] - ( y * T[i + P.size()] % p ) ) + p ) % p;
    }

    return H;
}

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences( const std::vector< int >& output ) {
    for ( size_t i = 0; i < output.size(); ++i ) std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector< int > get_occurrences( const Data& input ) {
    const string &s = input.pattern, t = input.text;
    std::vector< int > ans;
    unsigned long long pHash = poly_hash( s );
    auto H = precompute_hashes( t, s, prime, multiplier );

    for ( size_t i = 0; i + s.size() <= t.size(); ++i ) {
        //if ( pHash != poly_hash( t.substr( i, s.size() ) ) ) continue;
        if ( pHash != H[i] ) continue;
        if ( t.substr( i, s.size() ) == s ) ans.push_back( i );
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio( false );
    print_occurrences( get_occurrences( read_input() ) );
    return 0;
}