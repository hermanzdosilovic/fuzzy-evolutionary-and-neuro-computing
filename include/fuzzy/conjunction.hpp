#pragma once

#include <fuzzy/set.hpp>
#include <fuzzy/tnorm.hpp>

namespace fuzzy
{

template< typename TNorm >
Set conjunction( Set const & s1, Set const & s2, TNorm && t )
{
    Set result{ s1.domain() + s2.domain() };

    for ( auto const & e : result )
    {
        result[ e ] = t( s1[ e ], s2[ e ] );
    }

    return result;
}

Set conjunction( Set const & s1, Set const & s2, TNormType const tNormType = TNormType::ZADEH_MIN )
{
    return conjunction( s1, s2, tnorm( tNormType ) );
}

}
