#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

struct TrainExample
{
    double x1;
    double x2;
    double y;
};

using Rule = std::array< double, 7 >;
using Parameters = std::vector< Rule >;
using TrainingSet = std::vector< TrainExample >;

double sigmoid( double const a, double const b, double const x )
{
    auto const ret{ 1 / ( 1 + std::exp( a * ( x - b ) ) ) };
    return ret;
}

double nua( Rule const & ruleParameters, TrainExample const & trainExample )
{
    auto const ret{ sigmoid( ruleParameters[ 0 ], ruleParameters[ 1 ], trainExample.x1 ) };
    return ret;
}

double nub( Rule const & ruleParameters, TrainExample const & trainExample )
{
    auto const ret{ sigmoid( ruleParameters[ 2 ], ruleParameters[ 3 ], trainExample.x2 ) };
    return ret;
}

double consequent( Rule const & ruleParameters, TrainExample const & trainExample )
{
    auto const ret{ ruleParameters[ 4 ] * trainExample.x1 + ruleParameters[ 5 ] * trainExample.x2 + ruleParameters[ 6 ] };
    return ret;
}

double alpha( Rule const & ruleParameters, TrainExample const & trainExample )
{
    auto const ret{ nua( ruleParameters, trainExample ) * nub( ruleParameters, trainExample ) };
    return ret;
}

double alphaSum( Parameters const & parametersForRules, TrainExample const & trainExample )
{
    auto const ret
    {
        std::accumulate
        (
            std::begin( parametersForRules ),
            std::end  ( parametersForRules ),
            double{},
            [ & trainExample ]( auto const & s, auto const & x )
            {
                return s + alpha( x, trainExample );
            }
        )
    };
    return ret;
}

double alphaA( Rule const & ruleParameters, TrainExample const & trainExample )
{
    auto const ret
    {
        -1 * nub( ruleParameters, trainExample ) * ( trainExample.x1 - ruleParameters[ 1 ] ) *
        nua( ruleParameters, trainExample ) * ( 1 - nua( ruleParameters, trainExample ) )
    };
    return ret;
}

double alphaC( Rule const & ruleParameters, TrainExample const & trainExample )
{
    auto const ret
    {
        -1 * nua( ruleParameters, trainExample ) * ( trainExample.x2 - ruleParameters[ 3 ] ) *
        nub( ruleParameters, trainExample ) * ( 1 - nub( ruleParameters, trainExample ) )
    };
    return ret;
}

double alphaB( Rule const & ruleParameters, TrainExample const & trainExample )
{
    auto const ret
    {
        ruleParameters[ 0 ] * nub( ruleParameters, trainExample ) *
        nua( ruleParameters, trainExample ) * ( 1 - nua( ruleParameters, trainExample ) )
    };
    return ret;
}

double alphaD( Rule const & ruleParameters, TrainExample const & trainExample )
{
    auto const ret
    {
        ruleParameters[ 2 ] * nua( ruleParameters, trainExample ) *
        nub( ruleParameters, trainExample ) * ( 1 - nub( ruleParameters, trainExample ) )
    };
    return ret;
}

double alphaP( TrainExample const & trainExample )
{
    return trainExample.x1;
}

double alphaQ( TrainExample const & trainExample )
{
    return trainExample.x2;
}

double alphaR()
{
    return 1;
}

double forward( Parameters const & parametersForRules, TrainExample const & trainExample )
{
    auto const ret
    {
        std::accumulate
        (
            std::begin( parametersForRules ),
            std::end  ( parametersForRules ),
            double{},
            [ & trainExample ]( auto const & current, auto const & ruleParameters )
            {
                return current + alpha( ruleParameters, trainExample ) * consequent( ruleParameters, trainExample );
            }
        )
        /
        alphaSum( parametersForRules, trainExample )
    };
    return ret;
}

double shiftedAlphaSum( Parameters const & parametersForRules, Rule const & ruleParameters, TrainExample const & trainExample )
{
    auto const z{ consequent( ruleParameters, trainExample ) };
    auto const ret1
    {
        std::accumulate
        (
            std::begin( parametersForRules ),
            std::end  ( parametersForRules ),
            double{},
            [ z, & trainExample ]( auto const & current, auto const & ruleParameters )
            {
                return current + alpha( ruleParameters, trainExample ) * ( z - consequent( ruleParameters, trainExample ) );
            }
        )
    };
    auto const ret2
    {
        std::pow( alphaSum( parametersForRules, trainExample ), 2 )
    };
    return ret1 / ret2;
}

int main( int argc, char ** argv )
{
    if ( argc != 3 )
    {
        std::cout << "Expecting 2 arguments: numberOfRules and pathToDataset\n";
        return -1;
    }

    auto numberOfRules{ std::stoi( argv[ 1 ] ) };

    std::mt19937 randomGenerator{ std::random_device{}() };
    std::normal_distribution< double > normalDistribution{ 0, 1 };

    Parameters parametersForRules( numberOfRules );
    for ( auto & ruleParameters : parametersForRules )
    {
        for ( auto & parameter : ruleParameters )
        {
            parameter = normalDistribution( randomGenerator );
        }
    }

    TrainingSet trainingSet;
    trainingSet.reserve( 100 );

    if ( std::freopen( argv[ 2 ], "r", stdin ) == nullptr )
    {
        std::cout << "Cannot open file " << argv[ 2 ] << '\n';
        return -1;
    }


    while ( true )
    {
        TrainExample example;
        std::cin >> example.x1 >> example.x2 >> example.y;
        if ( std::cin.eof() )
        {
            break;
        }
        trainingSet.emplace_back( example );
    }

    constexpr auto epochs{ 100000 };
    constexpr auto logFrequency{ 100 };
    constexpr auto antecedentRate{ 5 * 1e-4 };
    constexpr auto consequentRate{ 5 * 1e-4 };

    Parameters tmpParameters( numberOfRules );

    for ( auto epoch{ 1 }; epoch <= epochs; ++epoch )
    {
        for ( auto const & trainExample : trainingSet )
        {
            auto i{ 0 };
            for ( auto const & ruleParameters : parametersForRules )
            {
                auto const sum{ shiftedAlphaSum( parametersForRules, ruleParameters, trainExample ) };
                auto const z{ alpha( ruleParameters, trainExample ) / alphaSum( parametersForRules, trainExample ) };
                auto const der{ forward( parametersForRules, trainExample ) - trainExample.y };
                auto const a{ antecedentRate * der * sum * alphaA( ruleParameters, trainExample ) };
                auto const b{ antecedentRate * der * sum * alphaB( ruleParameters, trainExample ) };
                auto const c{ antecedentRate * der * sum * alphaC( ruleParameters, trainExample ) };
                auto const d{ antecedentRate * der * sum * alphaD( ruleParameters, trainExample ) };

                auto const p{ consequentRate * der * z * alphaP( trainExample ) };
                auto const q{ consequentRate * der * z * alphaQ( trainExample ) };
                auto const r{ consequentRate * der * z * alphaR() };

                tmpParameters[ i ][ 0 ] = a;
                tmpParameters[ i ][ 1 ] = b;
                tmpParameters[ i ][ 2 ] = c;
                tmpParameters[ i ][ 3 ] = d;
                tmpParameters[ i ][ 4 ] = p;
                tmpParameters[ i ][ 5 ] = q;
                tmpParameters[ i ][ 6 ] = r;

                ++i;
            }

            i = 0;
            for ( auto & ruleParameters : parametersForRules )
            {
                ruleParameters[ 0 ] -= tmpParameters[ i ][ 0 ];
                ruleParameters[ 1 ] -= tmpParameters[ i ][ 1 ];
                ruleParameters[ 2 ] -= tmpParameters[ i ][ 2 ];
                ruleParameters[ 3 ] -= tmpParameters[ i ][ 3 ];
                ruleParameters[ 4 ] -= tmpParameters[ i ][ 4 ];
                ruleParameters[ 5 ] -= tmpParameters[ i ][ 5 ];
                ruleParameters[ 6 ] -= tmpParameters[ i ][ 6 ];
                ++i;
            }
        }

        double error{ 0 };
        for ( auto const & trainExample : trainingSet )
        {
            auto const e{ ( forward( parametersForRules, trainExample ) - trainExample.y ) };
            error += e * e;
        }

        error /= std::size( trainingSet );

        if ( logFrequency > 0 && epoch % logFrequency == 0 )
        {
            std::cout << "Epoch #" << epoch << ": MSE = " << error << '\n';
        }
    }

    return 0;
}
