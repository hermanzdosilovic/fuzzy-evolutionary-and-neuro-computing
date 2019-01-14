#pragma once

#include <cstdint>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

template< typename InputType, typename OutputType >
class Dataset
{
public:
    using InputEntry  = std::vector< InputType  >;
    using OutputEntry = std::vector< OutputType >;
    using Entry       = std::pair< InputEntry, OutputEntry >;

    Dataset
    (
        std::uint16_t const   numOfInputs,
        std::uint16_t const   numOfOutputs,
        std::string   const & filePath
    ) :
        numOfInputs_ { numOfInputs  },
        numOfOutputs_{ numOfOutputs }
    {
        std::ifstream inputFile{ filePath, std::ios_base::in };

        for ( std::string line; std::getline( inputFile, line ); )
        {
            std::istringstream lineStream{ line };

            InputEntry inputEntry( numOfInputs );
            for ( auto i{ 0 }; i < numOfInputs; ++i )
            {
                lineStream >> inputEntry[ i ];
            }

            OutputEntry outputEntry( numOfOutputs );
            for ( auto i{ 0 }; i < numOfOutputs; ++i )
            {
                lineStream >> outputEntry[ i ];
            }

            entries_.emplace_back( inputEntry, outputEntry );
        }

        inputFile.close();
    }

    auto size() const { return std::size( entries_ ); }

    auto begin() { return std::begin( entries_ ); }
    auto end  () { return std::end  ( entries_ ); }

    auto begin() const { return std::begin( entries_ ); }
    auto end  () const { return std::end  ( entries_ ); }

private:
    std::uint16_t numOfInputs_;
    std::uint16_t numOfOutputs_;
    std::vector< Entry > entries_;
};
