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

    Domain() = default;

    Domain( Domain const & other ) : elements_{ other.elements_ } {}

    Domain( Domain && other ) : elements_{ std::move( other.elements_ ) } {}

    Domain( elements const & elements ) : elements_{ elements }
    {
        std::sort( std::begin( elements_ ), std::end( elements_ ) );
        elements_.erase( std::unique( std::begin( elements_ ), std::end( elements_ ) ), std::end( elements_ ) );
    }

    static Domain Range( value_type const lowerBound, value_type const upperBound )
    {
        Domain domain;
        assert( lowerBound <= upperBound );
        domain.elements_.reserve( std::abs( upperBound - lowerBound ) );
        for ( value_type i{ lowerBound }; i < upperBound; ++i )
        {
            domain.elements_.push_back( { i } );
        }
        return domain;
    }

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

    Domain operator*( Domain const & other ) const
    {
        Domain result;
        result.elements_.reserve( size() * other.size() );
        for ( auto const & a : *this )
        {
            for ( auto const & b : other )
            {
                element_type e;
                e.reserve( std::size( a ) + std::size( b ) );
                e.insert( std::end( e ), std::begin( a ), std::end( a ) );
                e.insert( std::end( e ), std::begin( b ), std::end( b ) );
                result.elements_.emplace_back( e );
            }
        }
        return result;
    }

    bool operator==( Domain const & other ) const { return elements_ == other.elements_; }
    bool operator!=( Domain const & other ) const { return !( *this == other ); }

    Domain operator+( Domain const & other ) const
    {
        elements e{ std::begin( other ), std::end( other ) };
        e.insert( std::end( e ), begin(), end() );
        return e;
    }

    std::size_t size() const { return std::size( elements_ ); }

    elements::const_iterator begin() const { return std::begin( elements_ ); }
    elements::const_iterator end()   const { return std::end  ( elements_ ); }

private:
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
