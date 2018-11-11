#pragma once

#include <fuzzy/set.hpp>
#include <fuzzy/tnorm.hpp>

namespace fuzzy
{

template< typename TNorm >
Set conjunction( Set const & s1, Set const & s2, TNorm && t )
{
    Set result;

    for ( auto const & [ k, v ] : s1 )
    {
        result[ k ] = t( v, s2[ k ] );
    }

    for ( auto const & [ k, v ] : s2 )
    {
        result[ k ] = t( s1[ k ], v );
    }

    return result;
}

Set conjunction( Set const & s1, Set const & s2, TNormType const tNormType = TNormType::ZADEH_MIN )
{
    return conjunction( s1, s2, tnorm( tNormType ) );
}

template< typename TNorm >
Set conjunction( Sets const & sets, TNorm && t )
{
    assert( std::size( sets ) > 0 );

    Set result{ sets[ 0 ] };
    for ( std::size_t i{ 1 }; i < std::size( sets ); ++i )
    {
        result = conjunction( result, sets[ i ], t );
    }
    return result;
}

Set conjunction( Sets const & sets, TNormType const tNormType = TNormType::ZADEH_MIN )
{
    return conjunction( sets, tnorm( tNormType ) );
}

}
