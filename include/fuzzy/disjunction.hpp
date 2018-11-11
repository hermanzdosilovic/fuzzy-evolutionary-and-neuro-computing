#pragma once

#include <fuzzy/set.hpp>
#include <fuzzy/snorm.hpp>

namespace fuzzy
{

template< typename SNorm >
Set disjunction( Set const & s1, Set const & s2, SNorm && s )
{
    Set result{ s1.domain() + s2.domain() };

    for ( auto const & [ k, v ] : result )
    {
        result[ k ] = s( s1[ k ], s2[ k ] );
    }

    return result;
}

Set disjunction( Set const & s1, Set const & s2, SNormType const sNormType = SNormType::ZADEH_MAX )
{
    return disjunction( s1, s2, snorm( sNormType ) );
}

}
