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
        []( double const & current, auto const & e )
        {
            assert( std::size( e.first ) == 1 );
            return current + e.first[ 0 ] * e.second;
        }
    ) /
    std::accumulate
    (
        std::begin( s ),
        std::end  ( s ),
        0.0,
        []( double const & current, auto const & e )
        {
            return current + e.second;
        }
    );
}

}
