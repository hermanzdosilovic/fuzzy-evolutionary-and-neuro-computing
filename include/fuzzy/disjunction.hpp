#pragma once

#include <fuzzy/set.hpp>
#include <fuzzy/snorm.hpp>

#include <cassert>
#include <iterator>

namespace fuzzy
{

template< typename SNorm >
Set disjunction( Set const & s1, Set const & s2, SNorm && s )
{
    Set result;

    for ( auto const & [ k, v ] : s1 )
    {
        result[ k ] = s( v, s2[ k ] );
    }

    for ( auto const & [ k, v ] : s2 )
    {
        result[ k ] = s( s1[ k ], v );
    }

    return result;
}

Set disjunction( Set const & s1, Set const & s2, SNormType const sNormType = SNormType::ZADEH_MAX )
{
    return disjunction( s1, s2, snorm( sNormType ) );
}

template< typename SNorm >
Set disjunction( Sets const & sets, SNorm && s )
{
    assert( std::size( sets ) > 0 );

    Set result{ sets[ 0 ] };
    for ( std::size_t i{ 1 }; i < std::size( sets ); ++i )
    {
        result = disjunction( result, sets[ i ], s );
    }
    return result;
}

Set disjunction( Sets const & sets, SNormType const sNormType = SNormType::ZADEH_MAX )
{
    return disjunction( sets, snorm( sNormType ) );
}

}
