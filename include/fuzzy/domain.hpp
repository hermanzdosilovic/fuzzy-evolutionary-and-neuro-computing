#pragma once

#include <cassert>
#include <cstdint>
#include <tuple>
#include <vector>
#include <algorithm>

namespace fuzzy
{

namespace internal
{

template< typename T >
constexpr T abs( T const n ) { return n < 0 ? -n : n; }

}

class Domain
{
public:
    using element_type = std::int32_t;
    using value_type   = std::tuple< std::int32_t >;

    class iterator : public std::iterator< std::input_iterator_tag, value_type, std::size_t, value_type const *, value_type const >
    {
    public:
        constexpr explicit iterator( element_type const value ) : value_{ value } {}

        iterator & operator++()
        {
            value_++;
            return *this;
        }

        iterator operator++( int )
        {
            iterator copy{ *this };
            ++( *this );
            return copy;
        }

        constexpr bool operator==( iterator const & other ) const { return value_ == other.value_; }

        constexpr bool operator!=( iterator const & other ) const { return !( *this == other ); }

        constexpr reference operator*() const { return value_; }

    private:
        element_type value_;
    };

    constexpr Domain
    (
        element_type lowerBound,
        element_type upperBound
    ) :
        lowerBound_{ lowerBound },
        upperBound_{ upperBound },
        size_{ static_cast< std::size_t >( internal::abs( upperBound - lowerBound ) ) }
    {
        assert( lowerBound <= upperBound );
    }

    constexpr value_type operator[]( std::size_t const index ) const
    {
        assert( index < size_ );
        return lowerBound_ + index;
    }

    constexpr std::size_t size() const { return size_; }

    constexpr iterator begin() const { return iterator{ lowerBound_ }; }
    constexpr iterator end()   const { return iterator{ upperBound_ }; }

private:
    element_type lowerBound_{ 0 };
    element_type upperBound_{ 0 };
    std::size_t size_{ 0 };
};

}
