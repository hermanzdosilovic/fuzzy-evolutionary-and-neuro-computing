#pragma once

#include "set.hpp"

#include <algorithm>
#include <cassert>

namespace fuzzy
{

using Relation = Set;

namespace relation
{

bool isUnary( Relation const & r )
{
    return std::size( r.domain().components() ) == 0;
}

bool isBinary( Relation const & r )
{
    return std::size( r.domain().components() ) == 2;
}

bool isUxURelation( Relation const & r )
{
    if ( !isBinary( r ) )
    {
        return false;
    }

    auto const & components{ r.domain().components() };

    return components[ 0 ] == components[ 1 ];
}

bool isSymmetric( Relation const & r )
{
    if ( !isUxURelation( r ) )
    {
        return false;
    }

    auto const & domain{ r.domain().components()[ 0 ] };

    for ( auto const & a : domain )
    {
        auto const & x{ a[ 0 ] };
        for ( auto const & b : domain )
        {
            auto const & y{ b[ 0 ] };
            if ( !( r[ { x, y } ] == r[ { y, x } ] ) )
            {
                return false;
            }
        }
    }

    return true;
}

bool isReflexive( Relation const & r )
{
    if ( !isUxURelation( r ) )
    {
        return false;
    }

    auto const & domain{ r.domain().components()[ 0 ] };

    for ( auto const & a : domain )
    {
        auto const & x{ a[ 0 ] };
        if ( !( r[ { x, x } ] == 1.0 ) )
        {
            return false;
        }
    }

    return true;
}

bool isMaxMinTransitive( Relation const & r )
{
    if ( !isUxURelation( r ) )
    {
        return false;
    }

    auto const & domain = r.domain().components()[ 0 ];

    for ( auto const & a : domain )
    {
        auto const & x{ a[ 0 ] };
        for ( auto const & c : domain )
        {
            auto const & z{ c[ 0 ] };
            for ( auto const & b : domain )
            {
                auto const & y{ b[ 0 ] };
                if ( !( r[ { x, z } ] >= std::min( r[ { x, y } ], r[ { y, z } ] ) ) )
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool isEquivalence( Relation const & r )
{
    return isReflexive( r ) && isSymmetric( r ) && isMaxMinTransitive( r );
}

Relation composition( Relation const & r1, Relation const & r2 )
{
    auto const r1IsUnary{ isUnary( r1 ) };

    assert( r1IsUnary || isBinary( r1 ) );
    assert( isBinary( r2 ) );
    assert( ( r1IsUnary ? r1.domain() : r1.domain().components()[ 1 ] ) == r2.domain().components()[ 0 ] );

    auto const & X{ r1IsUnary ? r1.domain() : r1.domain().components()[ 0 ] };
    auto const & Y{ r2.domain().components()[ 0 ] };
    auto const & Z{ r2.domain().components()[ 1 ] };

    Relation result{ r1IsUnary ? Z : X * Z };

    for ( auto const & a : X )
    {
        auto const & x{ a[ 0 ] };
        for ( auto const & c : Z )
        {
            auto const & z{ c[ 0 ] };
            for ( auto const & b : Y )
            {
                auto const & y{ b[ 0 ] };
                result[ r1IsUnary ? Domain::element_type{ z } : Domain::element_type{ x, z } ] =
                    std::max
                    (
                        result[ r1IsUnary ? Domain::element_type{ z } : Domain::element_type{ x, z } ],
                        std::min
                        (
                            r1[ r1IsUnary ? Domain::element_type{ y } : Domain::element_type{ x, y } ],
                            r2[ { y, z } ]
                        )
                    );
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
