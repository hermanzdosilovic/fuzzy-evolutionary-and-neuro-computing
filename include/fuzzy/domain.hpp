#pragma once

#include <fuzzy/element.hpp>

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <vector>

namespace fuzzy
{

class Domain;
using Domains = std::vector< Domain >;

class Domain
{
public:
    Domain() = default;

    Domain( Domain const & other ) : elements_{ other.elements_ }, components_{ other.components_ } {}

    Domain( Domain && other ) :
        elements_{ std::move( other.elements_ ) },
        components_{ std::move( other.components_ ) }
    {}

    Domain( Element const & element )
    {
        elements_.emplace_back( element );
    }

    Domain( Elements const & elements ) : elements_{ elements }
    {
        std::sort( std::begin( elements_ ), std::end( elements_ ) );
        elements_.erase( std::unique( std::begin( elements_ ), std::end( elements_ ) ), std::end( elements_ ) );
    }

    static Domain Range( Element::value_type const lowerBound, Element::value_type const upperBound )
    {
        assert( lowerBound <= upperBound );

        Domain domain;
        domain.elements_.reserve( std::abs( upperBound - lowerBound ) );

        for ( auto i{ lowerBound }; i < upperBound; ++i )
        {
            domain.elements_.push_back( { i } );
        }

        return domain;
    }

    static Domain const & Empty()
    {
        static const Domain empty{ Range( 0, 0 ) };
        return empty;
    }

    Element const & operator[]( std::size_t const index ) const
    {
        assert( index < size() );
        return elements_[ index ];
    }

    std::size_t index( Element const & element ) const
    {
        return std::distance
        (
            std::begin( elements_ ),
            std::find( std::begin( elements_ ), std::end( elements_ ), element )
        );
    }

    Domain operator*( Domain const & other ) const
    {
        if ( other.size() == 0 )
        {
            return *this;
        }

        Domain const & tmp{ other };

        Domain result;
        result.elements_.reserve( size() * tmp.size() );

        for ( auto const & a : *this )
        {
            for ( auto const & b : tmp )
            {
                result.elements_.emplace_back( a + b );
            }
        }

        if ( std::empty( components_ ) )
        {
            result.components_.emplace_back( *this );
        }
        else
        {
            result.components_.insert
            (
                std::end( result.components_ ),
                std::begin( components_ ), std::end( components_ )
            );
        }

        if ( std::empty( other.components_ ) )
        {
            result.components_.emplace_back( other );
        }
        else
        {
            result.components_.insert
            (
                std::end( result.components_ ),
                std::begin( other.components_ ), std::end( other.components_ )
            );
        }

        return result;
    }

    bool operator==( Domain const & other ) const { return elements_ == other.elements_; }
    bool operator!=( Domain const & other ) const { return !( *this == other ); }

    Domain & operator=( Domain other )
    {
        std::swap( elements_, other.elements_ );
        std::swap( components_, other.components_ );
        return *this;
    }

    Domain operator+( Domain const & other ) const
    {
        Elements e{ std::begin( other ), std::end( other ) };
        e.insert( std::end( e ), begin(), end() );
        return e;
    }

    std::size_t size() const { return std::size( elements_ ); }

    Elements::const_iterator begin() const { return std::begin( elements_ ); }
    Elements::const_iterator end()   const { return std::end  ( elements_ ); }

    auto const & components() const { return components_; }

private:
    Elements elements_;
    Domains  components_;
};

}

template< typename T >
std::ostream & operator<<( std::ostream & ostream, std::vector< T > const & vector )
{
    auto i{ 0u };

    ostream << '(';
    for ( auto const & e : vector )
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
    auto i{ 0u };

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
