#pragma once

#include "domain.hpp"

#include <cstddef>
#include <ostream>
#include <vector>

namespace fuzzy
{

class Set
{
public:
    Set( Domain const & domain ) : domain_{ domain }, membership_( std::size( domain ) ) {}

    template< typename MembershipFunction >
    Set( Domain const & domain, MembershipFunction && f ) : Set( domain )
    {
        for ( std::size_t i{ 0 }; i < std::size( domain ); ++i )
        {
            membership_[ i ] = f( domain[ i ] );
        }
    }

    double & operator[]( Domain::element_type const & element )
    {
        auto index{ domain_.index( element ) };
        assert( index < std::size( membership_ ) );
        return membership_[ index ];
    }

    double operator[]( Domain::element_type const & element ) const
    {
        auto index{ domain_.index( element ) };
        if ( index >= std::size( membership_ ) ) { return 0; }
        return membership_[ index ];
    }

    bool operator==( Set const & other ) const
    {
        for ( auto const & e : *this )
        {
            if ( other[ e ] != ( *this )[ e ] )
            {
                return false;
            }
        }

        for ( auto const & e : other )
        {
            if ( other[ e ] != ( *this )[ e ] )
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=( Set const & other ) const { return !( *this == other ); }

    std::size_t size() const { return std::size( domain_ ); }

    Domain::elements::const_iterator begin() const { return std::begin( domain_ ); }
    Domain::elements::const_iterator end()   const { return std::end  ( domain_ ); }

private:
    Domain domain_;
    std::vector< double > membership_;
};

}

std::ostream & operator<<( std::ostream & ostream, fuzzy::Set const & set )
{
    std::size_t i{ 0 };
    ostream << "{\n";
    for ( auto const & e : set )
    {
        ostream << "  " << e << " -> " << set[ e ];
        if ( ++i < std::size( set ) )
        {
            ostream << ",\n";
        }
    }
    ostream << "\n}";
    return ostream;
}
