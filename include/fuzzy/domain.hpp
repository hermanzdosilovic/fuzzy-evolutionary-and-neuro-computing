#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <vector>

namespace fuzzy
{

class Domain
{
public:
    using value_type = std::int32_t;
    using element_type = std::vector< value_type >;
    using elements = std::vector< element_type >;

    Domain( value_type const lowerBound, value_type const upperBound )
    {
        assert( lowerBound <= upperBound );
        elements_.reserve( std::abs( upperBound - lowerBound ) );
        for ( value_type i{ lowerBound }; i < upperBound; ++i )
        {
            elements_.push_back( { i } );
        }
    }

    Domain( Domain const & first, Domain const & second )
    {
        elements_.reserve( std::size( first ) * std::size( second ) );
        for ( auto const & a : first )
        {
            for ( auto const & b : second )
            {
                element_type e;
                e.reserve( std::size( a ) + std::size( b ) );
                for ( auto const & v : a ) { e.emplace_back( v ); }
                for ( auto const & v : b ) { e.emplace_back( v ); }
                elements_.emplace_back( e );
            }
        }
    }

    static Domain const Empty() { return {}; }

    element_type const & operator[]( std::size_t const index ) const
    {
        assert( index < size() );
        return elements_[ index ];
    }

    std::size_t index( element_type const & element ) const
    {
        return std::distance
        (
            std::begin( elements_ ),
            std::find( std::begin( elements_ ), std::end( elements_ ), element )
        );
    }

    Domain operator*( Domain const & other ) const { return Domain{ *this, other }; }

    bool operator==( Domain const & other ) const { return elements_ == other.elements_; }
    bool operator!=( Domain const & other ) const { return !( *this == other ); }

    std::size_t size() const { return std::size( elements_ ); }

    elements::const_iterator begin() const { return std::begin( elements_ ); }
    elements::const_iterator end()   const { return std::end  ( elements_ ); }

private:
    Domain() = default;

    elements elements_;
};

}

template< typename T >
std::ostream & operator<<( std::ostream & ostream, std::vector< T > const & vector )
{
    std::size_t i{ 0 };
    ostream << '(';
    for ( auto & e : vector )
    {
        ostream << e;
        if ( ++i < std::size( vector ) )
        {
            ostream << ", ";
        }
    }
    ostream << ')';
    return ostream;
}

std::ostream & operator<<( std::ostream & ostream, fuzzy::Domain const & domain )
{
    std::size_t i{ 0 };
    ostream << "{\n";
    for ( auto const & e : domain )
    {
        ostream << "  " << e;
        if ( ++i < std::size( domain ) )
        {
            ostream << ",\n";
        }
    }
    ostream << "\n}";
    return ostream;
}
