#pragma once

#include <fuzzy/inference/engine.hpp>
#include <fuzzy/inference/rule.hpp>
#include <fuzzy/relation.hpp>
#include <fuzzy/operation.hpp>

#include <cstdint>
#include <utility>
#include <vector>

class ShipController
{
public:
    ShipController
    (
        fuzzy::Engine accelerationEngine,
        fuzzy::Engine rudderEngine,
        fuzzy::Rules  accelerationRules,
        fuzzy::Rules  rudderRules
    ) :
        accelerationEngine_{ accelerationEngine },
        rudderEngine_{ rudderEngine },
        accelerationRules_{ accelerationRules },
        rudderRules_{ rudderRules }
    {
        for ( auto const & rule : accelerationRules_ )
        {
            fuzzy::Relation relation{ rule.antecedent()[ 0 ] };
            for ( std::size_t i{ 1 }; i < std::size( rule.antecedent() ); ++i )
            {
                relation = fuzzy::cross( relation, rule.antecedent()[ i ], accelerationEngine_.tNormType() );
            }
            relation = fuzzy::implication( relation, rule.consequent(), accelerationEngine_.implicationType() );
            accelerationRelations_.emplace_back( relation );
        }

        for ( auto const & rule : rudderRules_ )
        {
            fuzzy::Relation relation{ rule.antecedent()[ 0 ] };
            for ( std::size_t i{ 1 }; i < std::size( rule.antecedent() ); ++i )
            {
                relation = fuzzy::cross( relation, rule.antecedent()[ i ], rudderEngine_.tNormType() );
            }
            relation = fuzzy::implication( relation, rule.consequent(), rudderEngine_.implicationType() );
            rudderRelations_.emplace_back( relation );
        }
    }

    std::pair< std::int16_t, std::int16_t > maneuver
    (
        [[ maybe_unused ]] std::int16_t leftDistance,
        [[ maybe_unused ]] std::int16_t rightDistance,
        [[ maybe_unused ]] std::int16_t upperLeftDistance,
        [[ maybe_unused ]] std::int16_t upperRightDistance,
        [[ maybe_unused ]] std::int16_t speed,
        [[ maybe_unused ]] std::int8_t  direction
    )
    {
        return { 0, 10 };
    }

private:
    fuzzy::Engine    accelerationEngine_;
    fuzzy::Engine    rudderEngine_;
    fuzzy::Rules     accelerationRules_;
    fuzzy::Rules     rudderRules_;
    fuzzy::Relations accelerationRelations_;
    fuzzy::Relations rudderRelations_;
};
