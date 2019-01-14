#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <type_traits>
#include <vector>

namespace nn
{

template
<
    typename T = double,
    typename   = std::enable_if_t< std::is_arithmetic_v< T > >
>
class ResemblingNetwork
{
public:
    ResemblingNetwork( std::vector< std::uint16_t > const & architecture ) : architecture_{ architecture }
    {
        assert( std::size( architecture ) > 0 );
        for ( [[ maybe_unused ]] auto const numOfNeurons : architecture )
        {
            assert( numOfNeurons > 0 );
        }

        inputSize_  = architecture[ 0 ];
        outputSize_ = architecture[ std::size( architecture ) - 1 ];

        std::size_t numOfWeights{ 0 };
        if ( std::size( architecture ) > 1 )
        {
            numOfWeights += 2 * architecture[ 1 ];
        }

        for ( std::size_t i{ 2 }; i < std::size( architecture ); ++i )
        {
            numOfWeights += architecture[ i ] * architecture[ i - 1 ];
        }

        weights_.resize( numOfWeights );

        layerInput_ .resize( *std::max_element( std::begin( architecture ), std::end( architecture ) ) );
        layerOutput_.resize( *std::max_element( std::begin( architecture ), std::end( architecture ) ) );

        networkOutput_.resize( outputSize_ );
    }

    template< typename InputIt >
    void weights( InputIt first, InputIt last )
    {
        assert( std::size( weights_ ) == static_cast< std::size_t >( std::distance( first, last ) ) );
        weights_.assign( first, last );
    }

    template< typename InputIt >
    auto operator()( InputIt first, InputIt last )
    {
        assert( inputSize_ == std::distance( first, last ) );

        std::for_each
        (
            first,
            last,
            [ this, i = 0 ]( auto const & x ) mutable
            {
                layerInput_[ i++ ] = x;
            }
        );

        layerOutput_.assign( std::begin( layerInput_ ), std::end( layerInput_ ) );

        std::size_t weightsOffset{ 0 };

        if ( std::size( architecture_ ) > 1 )
        {
            for ( auto i{ 0 }; i < architecture_[ 1 ]; ++i )
            {
                layerOutput_[ i ] = 1 /
                (
                    1 +
                    std::accumulate
                    (
                        std::begin( layerInput_ ),
                        std::next ( std::begin( layerInput_), architecture_[ 0 ] ),
                        T{},
                        [ w = weights_[ 2 * i ], s = weights_[ 2 * i + 1 ] ]( auto const current, auto const & x )
                        {
                            return current + std::abs( x - w ) / std::abs( s );
                        }
                    )
                );
            }

            weightsOffset += 2 * architecture_[ 1 ];

            layerInput_.assign( std::begin( layerOutput_ ), std::end( layerOutput_ ) );
        }

        for ( std::size_t i{ 2 }; i < std::size( architecture_ ); ++i )
        {
            for ( auto k{ 0 }; k < architecture_[ i ]; ++k )
            {
                layerOutput_[ k ] = 1 /
                (
                    1 + std::exp
                    (
                        -1 * std::accumulate
                        (
                            std::begin( layerInput_ ),
                            std::next ( std::begin( layerInput_ ), architecture_[ i - 1 ] ),
                            T{},
                            [ this, weightsOffset, i = 0 ]
                            ( auto const current, auto const & x ) mutable
                            {
                                return current + x * weights_[ weightsOffset + i++ ];
                            }
                        )
                    )
                );
                weightsOffset += architecture_[ i - 1 ];
            }

            layerInput_.assign( std::begin( layerOutput_ ), std::end( layerOutput_ ) );
        }

        networkOutput_.assign( std::begin( layerOutput_ ), std::next( std::begin( layerOutput_ ), outputSize_ ) );

        return networkOutput_;
    }

    auto size() const { return std::size( weights_ ); }

private:
    std::uint16_t inputSize_;
    std::uint16_t outputSize_;
    std::vector< std::uint16_t > architecture_;
    std::vector< T > weights_;

    std::vector< T > layerInput_;
    std::vector< T > layerOutput_;
    std::vector< T > networkOutput_;
};

}
