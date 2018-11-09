#pragma once

#include <cstdint>
#include <vector>

namespace fuzzy
{

using Element  = std::vector< std::int32_t >;
using Elements = std::vector< Element >;

namespace element
{

Element join( Element const & a, Element const & b )
{
    Element e;
    e.reserve( std::size( a ) + std::size( b ) );
    e.insert( std::end( e ), std::begin( a ), std::end( a ) );
    e.insert( std::end( e ), std::begin( b ), std::end( b ) );
    return e;
}

}

}
