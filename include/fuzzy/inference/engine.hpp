#pragma once

#include <fuzzy/inference/inference.hpp>
#include <fuzzy/implication.hpp>
#include <fuzzy/snorm.hpp>
#include <fuzzy/tnorm.hpp>

namespace fuzzy
{

class Engine
{
    constexpr Engine
    (
        InferenceType   const inferenceType,
        ImplicationType const implicationType,
        SNormType       const sNormType,
        TNormType       const tNormType
    ) :
        inferenceType_{ inferenceType },
        implicationType_{ implicationType },
        sNormType_{ sNormType },
        tNormType_{ tNormType }
    {}

    static Engine MinimumInferenceEngine()
    {
        static Engine minimumInferenceEngine
        {
            InferenceType::INDIVIDUAL_RULE,
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
            InferenceType::INDIVIDUAL_RULE,
            ImplicationType::MAMDANI_PRODUCT,
            SNormType::ZADEH_MAX,
            TNormType::ALGEBRAIC_PRODUCT
        };
        return productInferenceEngine;
    }

    Relation predict( Relation const & input ) const
    {
        return input;
    }

private:
    InferenceType   inferenceType_;
    ImplicationType implicationType_;
    SNormType       sNormType_;
    TNormType       tNormType_;
};

}
