#pragma once

#include <dataset.hpp>

namespace nn
{

template< typename Network, typename Dataset >
class NetworkTrainer
{
public:
    NetworkTrainer
    (
        Network       & neuralNetwork,
        Dataset const & dataset
    ) :
        neuralNetwork_{ neuralNetwork },
        dataset_      { dataset       }
    {}

    constexpr inline double fitness( double const penalty ) const { return -1 * penalty; }

    template< typename Point, typename = std::enable_if_t< !std::is_floating_point_v< Point > >  >
    constexpr inline double fitness( Point const & p ) const { return fitness( penalty( p ) ); }

    template< typename Point >
    constexpr inline double penalty( Point const & p ) const
    {
        neuralNetwork_.weights( std::begin( p ), std::end( p ) );

        double error{ 0 };
        for ( auto const & entry : dataset_ )
        {
            auto const result{ neuralNetwork_( std::begin( entry.first ), std::end( entry.first ) ) };

            assert( std::size( result ) == std::size( entry.second ) );

            for ( std::size_t i{ 0 }; i < std::size( result ); ++i )
            {
                error += ( result[ i ] - entry.second[ i ] ) * ( result[ i ] - entry.second[ i ] );
            }
        }

        return error / std::size( dataset_ );
    }

    template< typename Population >
    constexpr void evaluate( Population & population ) const
    {
        for ( auto & individual : population )
        {
            individual.penalty = penalty( individual         );
            individual.fitness = fitness( individual.penalty );
        }
    }

private:
    Network       & neuralNetwork_;
    Dataset const & dataset_;
};

}
