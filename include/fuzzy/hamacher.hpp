#pragma once

#include "set.hpp"

namespace fuzzy::hamacher
{

Set tNorm( Set const & first, Set const & second, double const nu )
{
    Set set{ first.domain() + second.domain() };
    for ( auto const & e : set )
    {
        auto const & a{ first[ e ] };
        auto const & b{ second[ e ] };

        set[ e ] = ( a * b ) / static_cast< double >( nu + ( 1 - nu ) * ( a + b - a * b ) );
    }
    return set;
}

Set sNorm( Set const & first, Set const & second, double const nu )
{
    Set set{ first.domain() + second.domain() };
    for ( auto const & e : set )
    {
        auto const & a{ first[ e ] };
        auto const & b{ second[ e ] };

        set[ e ] = ( a + b - ( 2 - nu ) * a * b ) / static_cast< double >( 1 - ( 1 - nu ) * a * b );
    }
    return set;
}

}
