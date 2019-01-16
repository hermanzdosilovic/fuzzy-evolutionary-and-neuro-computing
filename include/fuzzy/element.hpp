#pragma once

#include <cstdint>
#include <iterator>
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

fuzzy::Element operator+( fuzzy::Element const & a, fuzzy::Element const & b )
{
    return fuzzy::element::join( a, b );
}

fuzzy::Element & operator+=( fuzzy::Element & a, fuzzy::Element const & b )
{
    a = std::move( a + b );
    return a;
}
