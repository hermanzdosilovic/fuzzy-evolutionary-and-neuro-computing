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
    Relation result;
    for ( auto const & [ x, vx ] : r1 )
    {
        for ( auto const & [ y, vy ] : r2 )
        {
            result[ x + y ] = f( vx, vy );
        }
    }
    return result;
}

}

template< ImplicationType implicationType >
Relation implication( Relation const & r1, Relation const & r2 );

template<>
Relation implication< ImplicationType::KLEENE_DIENS >( Relation const & r1, Relation const & r2 )
{
    return detail::implication( r1, r2, []( double const x, double const y ){ return std::max( 1.0 - x, y ); } );
}

template<>
Relation implication< ImplicationType::LUKASIEWICZ >( Relation const & r1, Relation const & r2 )
{
    return detail::implication( r1, r2, []( double const x, double const y ){ return std::max( std::min( x, y ), 1.0 - x ); } );
}

template<>
Relation implication< ImplicationType::ZADEH >( Relation const & r1, Relation const & r2 )
{
    return detail::implication( r1, r2, []( double const x, double const y ){ return std::max( std::min( x, y ), 1.0 - x ); } );
}

template<>
Relation implication< ImplicationType::GODEL >( Relation const & r1, Relation const & r2 )
{
    return detail::implication( r1, r2, []( double const x, double const y ){ return x <= y ? 1.0 : y; } );
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

template< typename TNorm >
Relation implication( Relation const & r1, Relation const & r2, TNorm && t )
{
    return detail::implication( r1, r2, t );
}

auto implication( ImplicationType const implicationType = ImplicationType::ZADEH )
{
    switch ( implicationType )
    {
        case ImplicationType::KLEENE_DIENS:
            return implication< ImplicationType::KLEENE_DIENS >;
        case ImplicationType::LUKASIEWICZ:
            return implication< ImplicationType::LUKASIEWICZ >;
        case ImplicationType::ZADEH:
            return implication< ImplicationType::ZADEH >;
        case ImplicationType::GODEL:
            return implication< ImplicationType::GODEL >;
        case ImplicationType::MAMDANI_MIN:
            return implication< ImplicationType::MAMDANI_MIN >;
        case ImplicationType::MAMDANI_PRODUCT:
            return implication< ImplicationType::MAMDANI_PRODUCT >;
    }

#ifdef __GNUC__
    __builtin_unreachable();
#endif
}

Relation implication( Relation const & r1, Relation const & r2, ImplicationType const implicationType = ImplicationType::ZADEH )
{
    return implication( implicationType )( r1, r2 );
}

}
