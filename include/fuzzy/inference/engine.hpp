#pragma once

#include <fuzzy/disjunction.hpp>
#include <fuzzy/implication.hpp>
#include <fuzzy/operation.hpp>
#include <fuzzy/snorm.hpp>
#include <fuzzy/tnorm.hpp>

#include <iterator>

namespace fuzzy
{

class Engine
{
public:
    constexpr Engine
    (
        ImplicationType const implicationType,
        SNormType       const sNormType,
        TNormType       const tNormType
    ) :
        implicationType_{ implicationType },
        sNormType_{ sNormType },
        tNormType_{ tNormType }
    {}

    static Engine MinimumInferenceEngine()
    {
        static Engine minimumInferenceEngine
        {
            ImplicationType::MAMDANI_MIN,
            SNormType::ZADEH_MAX,
            TNormType::ZADEH_MIN
        };
        return minimumInferenceEngine;
    };

    static Engine ProductInferenceEngine()
    {
        static Engine productInferenceEngine
        {
            ImplicationType::MAMDANI_PRODUCT,
            SNormType::ZADEH_MAX,
            TNormType::ALGEBRAIC_PRODUCT
        };
        return productInferenceEngine;
    }

    auto implicationType() { return implicationType_; }
    auto sNormType()       { return sNormType_;       }
    auto tNormType()       { return tNormType_;       }

    Relation predict( Element const & input, Relations const & relations, Domain const & domain ) const
    {
        Relations results;
        for ( auto const & relation : relations )
        {
            Relation result;
            for ( auto const & e : domain )
            {
                result[ e ] = relation[ input + e ];
            }
            results.emplace_back( result );
        }

        return disjunction( results, sNormType_ );
    }

private:
    ImplicationType implicationType_;
    SNormType       sNormType_;
    TNormType       tNormType_;
};

}
