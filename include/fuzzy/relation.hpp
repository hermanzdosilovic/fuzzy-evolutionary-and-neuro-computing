#pragma once

#include "set.hpp"

#include <algorithm>
#include <cassert>

namespace fuzzy
{

using Relation = Set;

namespace relation
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

    auto const & components{ set.domain().components() };

    return components[ 0 ] == components[ 1 ];
}

bool isSymmetric( Set const & set )
{
    if ( !isUxURelation( set ) )
    {
        return false;
    }

    auto const & domain{ set.domain().components()[ 0 ] };

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

    auto const & domain{ set.domain().components()[ 0 ] };

    for ( auto const & x : domain )
    {
        if ( !( set[ { x[ 0 ], x[ 0 ] } ] == 1.0 ) )
        {
            return false;
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

    for ( auto const & a : domain )
    {
        auto const & x{ a[ 0 ] };
        for ( auto const & c : domain )
        {
            auto const & z{ c[ 0 ] };
            for ( auto const & b : domain )
            {
                auto const & y{ b[ 0 ] };
                if ( !( set[ { x, z } ] >= std::min( set[ { x, y } ], set[ { y, z } ] ) ) )
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool isEquivalence( Set const & set )
{
    return isReflexive( set ) && isSymmetric( set ) && isMaxMinTransitive( set );
}

Relation composition( Relation const & r1, Relation const & r2 )
{
    assert( std::size( r1.domain().components() ) == 2 );
    assert( std::size( r2.domain().components() ) == 2 );
    assert( r1.domain().components()[ 1 ] == r2.domain().components()[ 0 ] );

    auto const & X{ r1.domain().components()[ 0 ] };
    auto const & Y{ r1.domain().components()[ 1 ] };
    auto const & Z{ r2.domain().components()[ 1 ] };

    Relation result{ X * Z };

    for ( auto const & a : X )
    {
        auto const & x{ a[ 0 ] };
        for ( auto const & c : Z )
        {
            auto const & z{ c[ 0 ] };
            for ( auto const & b : Y )
            {
                auto const & y{ b[ 0 ] };
                result[ { x, z } ] = std::max( result[ { x, z } ], std::min( r1[ { x, y } ], r2[ { y, z } ] ) );
            }
        }
    }

    return result;
}

double height( Relation const & r )
{
    assert( isBinary( r ) );
    return r.height();
}

}

}
