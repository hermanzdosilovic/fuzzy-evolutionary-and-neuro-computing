#pragma once

#include <fuzzy/implication.hpp>
#include <fuzzy/relation.hpp>
#include <fuzzy/snorm.hpp>
#include <fuzzy/tnorm.hpp>
#include <fuzzy/set.hpp>

#include <cassert>
#include <cmath>
#include <iterator>

namespace fuzzy
{

template< typename TNorm >
Relation cross( Relation const & r1, Relation const & r2, TNorm && t )
{
    return implication( r1, r2, t );
}

Relation cross( Relation const & r1, Relation const & r2, TNormType const tNormType = TNormType::ZADEH_MIN )
{
    return implication( r1, r2, tnorm( tNormType ) );
}

template< typename TNorm >
Relation cross( Relations const & relations, TNorm && t )
{
    assert( std::size( relations ) > 0 );

    Relation result{ relations[ 0 ] };
    for ( std::size_t i{ 1 }; i < std::size( relations ); ++i )
    {
        result = cross( result, relations[ i ], t );
    }
    return result;
}

Relation cross( Relations const & relations, TNormType const tNormType = TNormType::ZADEH_MIN )
{
    return cross( relations, tnorm( tNormType ) );
}

template< typename SNorm, typename TNorm >
Relation composition( Relation const & r1, Relation const & r2, SNorm && s, TNorm && t )
{
    auto const r1IsUnary{ relation::isUnary( r1 ) };

    assert( r1IsUnary || relation::isBinary( r1 ) );
    assert( relation::isBinary( r2 ) );
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
                result[ r1IsUnary ? Element{ z } : Element{ x, z } ] =
                    s
                    (
                        result[ r1IsUnary ? Element{ z } : Element{ x, z } ],
                        t
                        (
                            r1[ r1IsUnary ? Element{ y } : Element{ x, y } ],
                            r2[ { y, z } ]
                        )
                    );
            }
        }
    }

    return result;
}

Relation composition( Relation const & r1, Relation const & r2, SNormType sNormType = SNormType::ZADEH_MAX, TNormType tNormType = TNormType::ZADEH_MIN )
{
    return composition( r1, r2, snorm( sNormType ), tnorm( tNormType ) );
}

template< typename Function >
Set transform( Set const & s, Function && f )
{
    Set result{ s };
    for ( auto & e : result )
    {
        result[ e ] = f( result[ e ] );
    }
    return result;
}

Set concentration( Set const & s )
{
    return transform( s, []( double const x ){ return std::pow( x, 2 ); } );
}

Set dilatation( Set const & s )
{
    return transform( s, []( double const x ){ return std::sqrt( x ); } );
}

Set intensification( Set const & s )
{
    return transform
    (
        s,
        []( double const x )
        {
            return ( ( x >= 0 && x <= 0.5 ) ? ( 2 * std::pow( x, 2 ) ) : ( 1 - 2 * std::pow( 1 - x, 2 ) ) );
        }
    );
}

}
