#pragma once

#include <crisp/set.hpp>
#include <fuzzy/domain.hpp>

#include <algorithm>
#include <cstddef>
#include <numeric>
#include <ostream>
#include <vector>
#include <map>
#include <tuple>

namespace fuzzy
{

class Set
{
public:
    Set( Domain const & domain ) : domain_{ domain } {}

    template< typename MembershipFunction >
    Set( Domain const & domain, MembershipFunction && f ) : Set( domain )
    {
        for ( auto const & e : domain )
        {
            membership_[ e ] = f( e );
        }
    }

    Set( Set const & set ) :
        domain_{ set.domain_ },
        membership_{ set.membership_ },
        isUniversal_{ set.isUniversal_ }
    {}

    Set( Set && set ) :
        domain_{ std::move( set.domain_ ) },
        membership_{ std::move( set.membership_ ) },
        isUniversal_{ set.isUniversal_ }
    {}

    static Set const & Universal()
    {
        static Set set;
        set.isUniversal_ = true;
        return set;
    }

    static Set const Empty()
    {
        static Set empty;
        return empty;
    }

    static Set Singleton( Element const & element )
    {
        Set s{ element };
        s[ element ] = 1.0;
        return s;
    }

    double & operator[]( Element const & element )
    {
        return membership_[ element ];
    }

    double operator[]( Element const & element ) const
    {
        if ( membership_.find( element ) == std::end( membership_ ) )
        {
            return isUniversal_ ? 1 : 0;
        }
        return membership_.at( element );
    }

    bool operator==( Set const & other ) const
    {
        auto const & self{ *this };

        for ( auto const & [ k, v ] : membership_ )
        {
            if ( other[ k ] != v )
            {
                return false;
            }
        }

        for ( auto const & [ k, v ] : other.membership_ )
        {
            if ( v != self[ k ] )
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=( Set const & other ) const { return !( *this == other ); }

    bool operator<=( Set const & other ) const
    {
        auto const & self{ *this };

        for ( auto const & [ k, v ] : membership_ )
        {
            if ( other[ k ] < v )
            {
                return false;
            }
        }

        for ( auto const & [ k, v ] : other.membership_ )
        {
            if ( v < self[ k ] )
            {
                return false;
            }
        }

        return true;
    }

    bool operator>=( Set const & other ) const
    {
        if ( *this == other ) { return true; }
        return !( *this <= other );
    }

    Set & operator=( Set other )
    {
        std::swap( domain_, other.domain_ );
        std::swap( membership_, other.membership_ );
        std::swap( isUniversal_, other.isUniversal_ );
        return *this;
    }

    Set & operator*=( Set const & other )
    {
        auto const & self{ *this };

        Set result{ domain_ * other.domain_ };
        for ( auto const & x : domain_ )
        {
            for ( auto const & y : other.domain_ )
            {
                result[ x + y ] = std::min( self[ x ], other[ y ] );
            }
        }

        *this = std::move( result );

        return *this;
    }

    Set operator*( Set const & other )
    {
        Set result{ *this };
        result *= other;
        return result;
    }

    bool isUniversal() const { return isUniversal_; }

    bool empty() const { return std::size( domain_ ) == 0 && !isUniversal_; }

    crisp::Set core() const
    {
        crisp::Set core;
        for ( auto const & [ k, v ] : membership_ )
        {
            if ( v == 1.0 )
            {
                core << k;
            }
        }

        return core;
    }

    crisp::Set support() const
    {
        crisp::Set support;
        for ( auto const & [ k, v ] : membership_ )
        {
            if ( v > 0 )
            {
                support << k;
            }
        }

        return support;
    }

    crisp::Set alphaCut( double const alpha )
    {
        crisp::Set cut;
        for ( auto const & [ k, v ] : membership_ )
        {
            if ( v >= alpha )
            {
                cut << k;
            }
        }

        return cut;
    }

    static Set product( double const alpha, crisp::Set set )
    {
        return { set, [ alpha ]( Element const & ) { return alpha; } };
    }

    double height() const
    {
        if ( size() == 0 )
        {
            return 0;
        }

        return std::max_element
        (
            std::begin( membership_ ),
            std::end  ( membership_ ),
            []( auto const & a, auto const & b ){ return a.second < b.second; }
        )->second;
    }

    double is_normal() const { return height() == 1.0; }

    std::size_t size() const { return std::size( membership_ ); }

    double cardinality() const {
        return std::accumulate( std::begin( membership_ ), std::end( membership_ ), 0, []( double const & c, auto const & e ){ return c + e.second; } );
    }

    auto const & domain() const { return domain_; }

    auto begin() const { return std::begin( membership_ ); }
    auto end()   const { return std::end  ( membership_ ); }

private:
    Set() = default;

    Domain domain_;
    std::map< Element, double > membership_;
    bool isUniversal_{ false };
};

using Sets = std::vector< Set >;

}

std::ostream & operator<<( std::ostream & ostream, fuzzy::Set const & set )
{
    std::size_t i{ 0 };
    ostream << "{\n";
    for ( auto const & [ k, v ] : set )
    {
        ostream << "  " << k << " -> " << v;
        if ( ++i < std::size( set ) )
        {
            ostream << ",\n";
        }
    }
    ostream << "\n}";
    return ostream;
}
