#include <fuzzy/domain.hpp>

int main()
{
    constexpr fuzzy::Domain d1{ 0, 2 };
    static_assert( std::size( d1 ) == 2 );
    static_assert( d1[ 0 ] == std::make_tuple( 0 ) );
    static_assert( d1[ 1 ] == std::make_tuple( 1 ) );

    constexpr fuzzy::Domain d2{ 0, 3 };
    static_assert( std::size( d2 ) == 3 );
    static_assert( d2[ 0 ] == std::make_tuple( 0 ) );
    static_assert( d2[ 1 ] == std::make_tuple( 1 ) );
    static_assert( d2[ 2 ] == std::make_tuple( 2 ) );

    constexpr auto it1{ std::begin( d1 ) };
    static_assert( *it1 == d1[ 0 ] );

    auto it2{ std::begin( d2 ) };
    assert( *it2 == d2[ 0 ] );
    assert( *( it2++ ) == d2[ 0 ] );
    assert( *it2 == d2[ 1 ] );
    assert( *( ++it2 ) == d2[ 2 ] );

    return 0;
}
