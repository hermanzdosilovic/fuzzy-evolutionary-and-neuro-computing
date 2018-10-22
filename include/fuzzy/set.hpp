#pragma once

#include "crisp/set.hpp"
#include "domain.hpp"

#include <algorithm>
#include <cstddef>
#include <numeric>
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

    static Set const Universal()
    {
        Set set;
        set.is_universal_ = true;
        return set;
    }

    static Set const Empty() { return {}; }

    double & operator[]( Domain::element_type const & element )
    {
        auto index{ domain_.index( element ) };
        assert( index < std::size( membership_ ) );
        return membership_[ index ];
    }

    double operator[]( Domain::element_type const & element ) const
    {
        auto index{ domain_.index( element ) };
        if ( index >= std::size( membership_ ) ) { return is_universal_; }
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

    bool operator<=( Set const & other ) const
    {
        for ( auto const & e : *this )
        {
            if ( other[ e ] < ( *this )[ e ] )
            {
                return false;
            }
        }

        for ( auto const & e : other )
        {
            if ( other[ e ] < ( *this )[ e ] )
            {
                return false;
            }
        }

        return true;
    }

    bool operator>=( Set const & other ) const
    {
        if ( other == *this ) { return true; }
        return !( *this <= other );
    }

    Set operator*( Set const & other ) const
    {
        assert( std::size( domain_.components() ) == 2 );
        assert( std::size( other.domain_.components() ) == 2 );
        assert( domain_.components()[ 1 ] == other.domain_.components()[ 0 ] );

        auto const & X = domain_.components()[ 0 ];
        auto const & Y = domain_.components()[ 1 ];
        auto const & Z = other.domain_.components()[ 1 ];

        Set result{ X * Z };

        for ( auto const & x : X )
        {
            for ( auto const & z : Z )
            {
                for ( auto const & y : Y )
                {
                    result[ { x[ 0 ], z[ 0 ] } ] = std::max
                    (
                        result[ { x[ 0 ], z[ 0 ] } ],
                        std::min
                        (
                            ( *this )[ { x[ 0 ], y[ 0 ] } ],
                            other[ { y[ 0 ], z[ 0 ] } ]
                        )
                    );
                }
            }
        }

        return result;
    }

    bool is_universal() const { return is_universal_; }

    bool is_empty() const { return std::size( domain_ ) == 0 && !is_universal_; }

    crisp::Set core() const
    {
        crisp::Set core;
        for ( auto const & e : *this )
        {
            if ( ( *this )[ e ] == 1.0 )
            {
                core << e;
            }
        }
        return core;
    }

    crisp::Set support() const
    {
        crisp::Set support;
        for ( auto const & e : *this )
        {
            if ( ( *this )[ e ] > 0 )
            {
                support << e;
            }
        }
        return support;
    }

    crisp::Set alphaCut( double const alpha )
    {
        crisp::Set cut;
        for ( auto const & e : *this )
        {
            if ( ( *this )[ e ] >= alpha )
            {
                cut << e;
            }
        }
        return cut;
    }

    static Set product( double const alpha, crisp::Set set )
    {
        return { set, [ alpha ]( Domain::element_type const & ) { return alpha; } };
    }

    double height() const { return size() == 0 ? 0 : *std::max_element( std::begin( membership_ ), std::end( membership_ ) ); }

    double is_normal() const { return height() == 1.0; }

    std::size_t size() const { return std::size( domain_ ); }

    double cardinality() const { return std::accumulate( std::begin( membership_ ), std::end( membership_ ), 0 ); }

    Domain const & domain() const { return domain_; }

    Domain::elements::const_iterator begin() const { return std::begin( domain_ ); }
    Domain::elements::const_iterator end()   const { return std::end  ( domain_ ); }

private:
    Set() = default;

    Domain domain_;
    std::vector< double > membership_;
    bool is_universal_{ false };
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
