#pragma once

#include <crisp/set.hpp>
#include <fuzzy/domain.hpp>

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
        auto index{ domain_.index( element ) };
        assert( index < std::size( membership_ ) );
        return membership_[ index ];
    }

    double operator[]( Element const & element ) const
    {
        auto index{ domain_.index( element ) };
        if ( index >= std::size( membership_ ) ) { return isUniversal_; }
        return membership_[ index ];
    }

    bool operator==( Set const & other ) const
    {
        auto const & self{ *this };

        for ( auto const & e : self )
        {
            if ( other[ e ] != self[ e ] )
            {
                return false;
            }
        }

        for ( auto const & e : other )
        {
            if ( other[ e ] != self[ e ] )
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

        for ( auto const & e : self )
        {
            if ( other[ e ] < self[ e ] )
            {
                return false;
            }
        }

        for ( auto const & e : other )
        {
            if ( other[ e ] < self[ e ] )
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
        auto const & self{ *this };

        crisp::Set core;
        for ( auto const & e : self )
        {
            if ( self[ e ] == 1.0 )
            {
                core << e;
            }
        }

        return core;
    }

    crisp::Set support() const
    {
        auto const & self{ *this };

        crisp::Set support;
        for ( auto const & e : self )
        {
            if ( self[ e ] > 0 )
            {
                support << e;
            }
        }

        return support;
    }

    crisp::Set alphaCut( double const alpha )
    {
        auto const & self{ *this };

        crisp::Set cut;
        for ( auto const & e : self )
        {
            if ( self[ e ] >= alpha )
            {
                cut << e;
            }
        }

        return cut;
    }

    static Set product( double const alpha, crisp::Set set )
    {
        return { set, [ alpha ]( Element const & ) { return alpha; } };
    }

    double height() const { return size() == 0 ? 0 : *std::max_element( std::begin( membership_ ), std::end( membership_ ) ); }

    double is_normal() const { return height() == 1.0; }

    std::size_t size() const { return std::size( domain_ ); }

    double cardinality() const { return std::accumulate( std::begin( membership_ ), std::end( membership_ ), 0 ); }

    auto const & domain() const { return domain_; }

    Elements::const_iterator begin() const { return std::begin( domain_ ); }
    Elements::const_iterator end()   const { return std::end  ( domain_ ); }

private:
    Set() = default;

    Domain domain_;
    std::vector< double > membership_;
    bool isUniversal_{ false };
};

using Sets = std::vector< Set >;

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
