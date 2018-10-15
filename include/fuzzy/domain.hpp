#pragma once

#include <cassert>
#include <cstdint>
#include <tuple>
#include <vector>
#include <algorithm>
#include <ostream>

namespace fuzzy
{

using value_type = std::int32_t;
using element_type = std::vector< value_type >;
using elements = std::vector< element_type >;

class Domain
{
public:
    Domain( value_type const lowerBound, value_type const upperBound )
    {
        for ( value_type i{ lowerBound }; i < upperBound; ++i )
        {
            elements_.push_back( { i } );
        }
    }

    Domain( Domain & first, Domain & second )
    {
        for ( auto & a : first )
        {
            for ( auto & b : second )
            {
                element_type e;
                for ( auto & v : a ) { e.emplace_back( v ); }
                for ( auto & v : b ) { e.emplace_back( v ); }
                elements_.emplace_back( e );
            }
        }
    }

    element_type operator[]( std::size_t const index )
    {
        assert( index < size() );
        return elements_[ index ];
    }

    std::size_t index( element_type const & element )
    {
        return std::distance
        (
            std::begin( elements_ ),
            std::find( std::begin( elements_ ), std::end( elements_ ), element )
        );
    }

    Domain operator*( Domain & other ) { return Domain{ *this, other }; }

    std::size_t size() { return std::size( elements_ ); }

    elements::iterator begin() { return std::begin( elements_ ); }
    elements::iterator end()   { return std::end  ( elements_ ); }

private:
    elements elements_;
};

}

template< typename T >
std::ostream & operator<<( std::ostream & ostream, std::vector< T > const & vector )
{
    std::size_t i{ 0 };
    ostream << '(';
    for ( auto & v : vector )
    {
        ostream << v;
        if ( ++i < std::size( vector ) )
        {
            ostream << ", ";
        }
    }
    ostream << ')';
    return ostream;
}

std::ostream & operator<<( std::ostream & stream, fuzzy::Domain & domain )
{
    std::size_t i{ 0 };
    stream << "{\n";
    for ( auto & v : domain )
    {
        stream << "  " << v;
        if ( ++i < domain.size() )
        {
            stream << ",\n";
        }
    }
    stream << "\n}";
    return stream;
}
