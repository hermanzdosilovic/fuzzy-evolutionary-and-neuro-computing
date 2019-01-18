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
    nn::ResemblingNetwork< double > neuralNetwork{ 2, 8, 3 };

    constexpr std::size_t numberOfComponents{ 40 };
    constexpr std::size_t populationSize{ 30 };

    constexpr bool        enableElitism{ true };
    constexpr std::size_t maxGenerations{ 1000000 };
    constexpr double      desiredFitness{ 0 };
    constexpr double      precision{ 1e-5 };

    constexpr std::size_t tournamentSize{ 3 };

    constexpr float alpha { 0.4 };
    constexpr float lambda{ 0.5 };

    constexpr float mutationProbability1{ 0.03 };
    constexpr float mutationProbability2{ 0.02 };
    constexpr float mutationProbability3{ 0.01 };
    constexpr bool  forceMutation{ true };
    constexpr float sigma1{ 0.1 };
    constexpr float sigma2{ 0.3 };
    constexpr float sigma3{ 0.5 };

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
            ecfcpp::crossover::Composite< Chromosome >
            {
                ecfcpp::crossover::BlxAlpha{ alpha },
                ecfcpp::crossover::Arithmetical{ lambda },
                ecfcpp::crossover::SinglePoint{},
            },
            ecfcpp::mutation::Composite< Chromosome >
            {
                { ecfcpp::mutation::Gaussian{ mutationProbability1, forceMutation, sigma1, ecfcpp::mutation::Gaussian::Type::Add }, 4 },
                { ecfcpp::mutation::Gaussian{ mutationProbability2, forceMutation, sigma2, ecfcpp::mutation::Gaussian::Type::Add }, 4 },
                { ecfcpp::mutation::Gaussian{ mutationProbability3, forceMutation, sigma3, ecfcpp::mutation::Gaussian::Type::Set }, 1 }
            },
            ecfcpp::factory::create
            (
                Chromosome{ -2, 2 },
                populationSize,
                []{ return ecfcpp::random::uniform( -1, 1 ); }
            ),
            logFrequency
        )
    };

    return 0;
}
