#pragma once

#include "set.hpp"

#include <algorithm>

namespace fuzzy::zadeh
{

Set operator|( Set const & first, Set const & second )
{
    Set set{ first.domain() + second.domain() };
    for ( auto & e : set )
    {
        set[ e ] = std::max( first[ e ], second[ e ] );
    }
    return set;
}

Set operator&( Set const & first, Set const & second )
{
    Set set{ first.domain() + second.domain() };
    for ( auto & e : set )
    {
        set[ e ] = std::min( first[ e ], second[ e ] );
    }
    return set;
}

Set operator!( Set const & set )
{
    Set copy{ set };
    for ( auto const & e : copy )
    {
        copy[ e ] = 1 - copy[ e ];
    }
    return copy;
}

}
