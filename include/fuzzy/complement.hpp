#pragma once

#include <fuzzy/set.hpp>

namespace fuzzy
{

template< typename UnaryFunction >
Set complement( Set const & s, UnaryFunction && f )
{
    Set result{ s };

    for ( auto const & [ k, v ] : result )
    {
        result[ k ] = f( v );
    }

    return result;
}

Set complement( Set const & s )
{
    return complement( s, []( double const x ){ return 1 - x; } );
}

}
