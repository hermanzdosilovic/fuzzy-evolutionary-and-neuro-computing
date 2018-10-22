#pragma once

#include "set.hpp"

#include <algorithm>

namespace fuzzy::relation
{

bool isBinary( Set const & set )
{
    return std::size( set.domain().components() ) == 2;
}

bool isUxURelation( Set const & set )
{
    if ( !isBinary( set ) )
    {
        return false;
    }

    auto const & components = set.domain().components();

    return components[ 0 ] == components[ 1 ];
}

bool isSimetric( Set const & set )
{
    if ( !isUxURelation( set ) )
    {
        return false;
    }

    auto const & domain = set.domain().components()[ 0 ];

    for ( auto const & x : domain )
    {
        for ( auto const & y : domain )
        {
            if ( !( set[ { x[ 0 ], y[ 0 ] } ] == set[ { y[ 0 ], x[ 0 ] } ] ) )
            {
                return false;
            }
        }
    }

    return true;
}

bool isReflexive( Set const & set )
{
    if ( !isUxURelation( set ) )
    {
        return false;
    }

    auto const & domain = set.domain().components()[ 0 ];

    for ( auto const & x : domain )
    {
        for ( auto const & y : domain )
        {
            if ( x != y )
            {
                continue;
            }
            else if ( !( set[ { x[ 0 ], x[ 0 ] } ] == 1.0 ) )
            {
                return false;
            }
        }
    }

    return true;
}

bool isMaxMinTransitive( Set const & set )
{
    if ( !isUxURelation( set ) )
    {
        return false;
    }

    auto const & domain = set.domain().components()[ 0 ];

    for ( auto const & x : domain )
    {
        for ( auto const & z : domain )
        {
            for ( auto const & y : domain )
            {
                if
                (
                    !(
                        set[ { x[ 0 ], z[ 0 ] } ] >=
                        std::min
                        (
                            set[ { x[ 0 ], y[ 0 ] } ],
                            set[ { y[ 0 ], z[ 0 ] } ]
                        )
                    )
                )
                {
                    return false;
                }
            }
        }
    }

    return true;
}

}
