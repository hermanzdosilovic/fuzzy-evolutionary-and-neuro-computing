#pragma once

#include <fuzzy/element.hpp>
#include <fuzzy/set.hpp>

#include <iterator>
#include <numeric>

namespace fuzzy
{

double centerOfArea( Set const & s )
{
    return std::accumulate
    (
        std::begin( s ),
        std::end  ( s ),
        0.0,
        [ & s ]( double const & current, Element const & e )
        {
            assert( std::size( e ) == 1 );
            return current + e[ 0 ] * s[ e ];
        }
    ) /
    std::accumulate
    (
        std::begin( s ),
        std::end  ( s ),
        0.0,
        [ & s ]( double const & current, Element const & e )
        {
            return current + s[ e ];
        }
    );
}

}
