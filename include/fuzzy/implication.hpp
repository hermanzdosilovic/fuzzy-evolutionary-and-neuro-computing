#pragma once

#include <fuzzy/domain.hpp>
#include <fuzzy/relation.hpp>

#include <cstdint>
#include <cmath>
#include <stdexcept>

namespace fuzzy
{

enum class ImplicationType : std::uint8_t
{
    KLEENE_DIENS,
    LUKASIEWICZ,
    ZADEH,
    GODEL,
    MAMDANI_MIN,
    MAMDANI_PRODUCT
};

namespace detail
{

template< typename Function >
Relation implication( Relation const & r1, Relation const & r2, Function && f )
{
    Relation result{ r1.domain() * r2.domain() };

    for ( auto const & x : r1.domain() )
    {
        for ( auto const & y : r2.domain() )
        {
            result[ domain::join_elements( x, y ) ] = f( r1[ x ], r2[ y ] );
        }
    }

    return result;
}

}

template< ImplicationType >
Relation implication( Relation const & r1, Relation const & r2 );

template<>
Relation implication< ImplicationType::KLEENE_DIENS >( Relation const & r1, Relation const & r2 )
{
    return detail::implication( r1, r2, []( double const x, double const y ){ return std::max( 1 - x, y ); } );
}

template<>
Relation implication< ImplicationType::LUKASIEWICZ >( Relation const & r1, Relation const & r2 )
{
    return detail::implication( r1, r2, []( double const x, double const y ){ return std::max( std::min( x, y ), 1 - x ); } );
}

template<>
Relation implication< ImplicationType::ZADEH >( Relation const & r1, Relation const & r2 )
{
    return detail::implication( r1, r2, []( double const x, double const y ){ return std::max( std::min( x, y ), 1 - x ); } );
}

template<>
Relation implication< ImplicationType::GODEL >( Relation const & r1, Relation const & r2 )
{
    return detail::implication( r1, r2, []( double const x, double const y ){ return x <= y ? 1 : y; } );
}

template<>
Relation implication< ImplicationType::MAMDANI_MIN >( Relation const & r1, Relation const & r2 )
{
    return detail::implication( r1, r2, []( double const x, double const y ){ return std::min( x, y ); } );
}

template<>
Relation implication< ImplicationType::MAMDANI_PRODUCT >( Relation const & r1, Relation const & r2 )
{
    return detail::implication( r1, r2, []( double const x, double const y ){ return x * y; } );
}

Relation implication( Relation const & r1, Relation const & r2, ImplicationType const implicationType = ImplicationType::ZADEH )
{
    switch ( implicationType )
    {
        case ImplicationType::KLEENE_DIENS:
            return implication< ImplicationType::KLEENE_DIENS >( r1, r2 );
        case ImplicationType::LUKASIEWICZ:
            return implication< ImplicationType::LUKASIEWICZ >( r1, r2 );
        case ImplicationType::ZADEH:
            return implication< ImplicationType::ZADEH >( r1, r2 );
        case ImplicationType::GODEL:
            return implication< ImplicationType::GODEL >( r1, r2 );
        case ImplicationType::MAMDANI_MIN:
            return implication< ImplicationType::MAMDANI_MIN >( r1, r2 );
        case ImplicationType::MAMDANI_PRODUCT:
            return implication< ImplicationType::MAMDANI_PRODUCT >( r1, r2 );
    }

#ifdef __GNUC__
    __builtin_unreachable();
#endif
}

}
