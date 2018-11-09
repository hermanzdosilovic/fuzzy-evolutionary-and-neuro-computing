#pragma once

#include <fuzzy/implication.hpp>
#include <fuzzy/relation.hpp>
#include <fuzzy/snorm.hpp>
#include <fuzzy/tnorm.hpp>

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
                result[ r1IsUnary ? Domain::element_type{ z } : Domain::element_type{ x, z } ] =
                    s
                    (
                        result[ r1IsUnary ? Domain::element_type{ z } : Domain::element_type{ x, z } ],
                        t
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

Relation composition( Relation const & r1, Relation const & r2, SNormType sNormType = SNormType::ZADEH_MAX, TNormType tNormType = TNormType::ZADEH_MIN )
{
    return composition( r1, r2, snorm( sNormType ), tnorm( tNormType ) );
}

}
