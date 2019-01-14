#include <dataset.hpp>
#include <neural/resembling.hpp>
#include <neural/trainer.hpp>

#include <ecfcpp/ecfcpp.hpp>

#include <cstdint>
#include <iostream>
#include <iterator>

int main()
{
    Dataset< double, std::uint16_t > dataset{ 2, 3, "files/homework_07/dataset.txt" };
    nn::ResemblingNetwork< double > neuralNetwork{ { 2, 8, 3 } };

    constexpr std::size_t numberOfComponents{ 40 };
    constexpr std::size_t populationSize{ 30 };

    constexpr bool        enableElitism{ true };
    constexpr std::size_t maxGenerations{ 1000000 };
    constexpr double      desiredFitness{ 0 };
    constexpr double      precision{ 1e-5 };

    constexpr std::size_t tournamentSize{ 3 };

    constexpr float alpha{ 0.5 };

    constexpr float mutationProbability{ 0.1 };
    constexpr bool  forceMutation{ true };
    constexpr float sigma{ 1 };

    constexpr auto logFrequency{ 100 };

    using Chromosome = ecfcpp::Array< double, numberOfComponents >;

    nn::NetworkTrainer trainer{ neuralNetwork, dataset };

    auto const result
    {
        ecfcpp::ga::generational
        (
            enableElitism,
            maxGenerations,
            desiredFitness,
            precision,
            trainer,
            ecfcpp::selection::Tournament{ tournamentSize },
            ecfcpp::crossover::BlxAlpha{ alpha },
            ecfcpp::mutation::Gaussian{ mutationProbability, forceMutation, sigma },
            ecfcpp::factory::create
            (
                Chromosome{ -1, 1 },
                populationSize,
                []{ return ecfcpp::random::uniform( 0, 1 ); }
            ),
            logFrequency
        )
    };

    return 0;
}
