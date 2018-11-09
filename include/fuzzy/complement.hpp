#pragma once

#include <fuzzy/set.hpp>

namespace fuzzy
{

template< typename UnaryFunction >
Set complement( Set const & s1, Set const & s2, UnaryFunction && f )
{
    Set result{ s1.domain() + s2.domain() };

    for ( auto const & e : result )
    {
        result[ e ] = f( result[ e ] );
    }

    return result;
}

Set complement( Set const & s1, Set const & s2 )
{
    return complement( s1, s2, []( double const x ){ return 1 - x; } );
}

}
