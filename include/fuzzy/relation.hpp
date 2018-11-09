#pragma once

#include <fuzzy/set.hpp>

#include <algorithm>
#include <cassert>
#include <iterator>

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

double height( Relation const & r )
{
    assert( isBinary( r ) );
    return r.height();
}

}

}
