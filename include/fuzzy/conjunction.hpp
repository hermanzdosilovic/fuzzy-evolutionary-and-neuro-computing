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

}
