#pragma once

#include <fuzzy/inference/engine.hpp>
#include <fuzzy/inference/rule.hpp>
#include <fuzzy/relation.hpp>
#include <fuzzy/operation.hpp>

#include <cstdint>
#include <iterator>
#include <numeric>
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
        std::int16_t leftDistance,
        std::int16_t rightDistance,
        std::int16_t upperLeftDistance,
        std::int16_t upperRightDistance,
        std::int16_t speed,
        std::int8_t  direction
    )
    {
        fuzzy::Sets const inputs
        {
            fuzzy::Set::Singleton( { rightDistance      } ),
            fuzzy::Set::Singleton( { upperLeftDistance  } ),
            fuzzy::Set::Singleton( { upperRightDistance } ),
            fuzzy::Set::Singleton( { speed              } ),
            fuzzy::Set::Singleton( { direction          } )
        };

        fuzzy::Relation accelerationInput{ fuzzy::Set::Singleton( { leftDistance } ) };
        fuzzy::Relation rudderInput{ accelerationInput };
        for ( auto const & i : inputs )
        {
            accelerationInput = cross( accelerationInput, i, accelerationEngine_.tNormType() );
            rudderInput       = cross( rudderInput      , i, rudderEngine_      .tNormType() );
        }

        auto const accelerationOutput{ accelerationEngine_.predict( accelerationInput, accelerationRelations_ ) };
        auto const rudderOutput      { rudderEngine_      .predict( rudderInput      , rudderRelations_       ) };

        double accelerationCenterOfArea
        {
            std::accumulate
            (
                std::begin( accelerationOutput ),
                std::end  ( accelerationOutput ),
                0.0,
                [ & accelerationOutput ]( double const & current, fuzzy::Domain::element_type const & element )
                {
                    assert( std::size( element ) == 1 );
                    return current + element[ 0 ] * accelerationOutput[ element ];
                }
            ) /
            std::accumulate
            (
                std::begin( accelerationOutput ),
                std::end  ( accelerationOutput ),
                0.0,
                [ & accelerationOutput ]( double const & current, fuzzy::Domain::element_type const & element )
                {
                    return current + accelerationOutput[ element ];
                }
            )
        };

        double rudderCenterOfArea
        {
            std::accumulate
            (
                std::begin( rudderOutput ),
                std::end  ( rudderOutput ),
                0.0,
                [ & rudderOutput ]( double const & current, fuzzy::Domain::element_type const & element )
                {
                    assert( std::size( element ) == 1 );
                    return current + element[ 0 ] * rudderOutput[ element ];
                }
            ) /
            std::accumulate
            (
                std::begin( rudderOutput ),
                std::end  ( rudderOutput ),
                0.0,
                [ & rudderOutput ]( double const & current, fuzzy::Domain::element_type const & element )
                {
                    return current + rudderOutput[ element ];
                }
            )
        };

        return { std::floor( accelerationCenterOfArea ), std::floor( rudderCenterOfArea ) };
    }

private:
    fuzzy::Engine    accelerationEngine_;
    fuzzy::Engine    rudderEngine_;
    fuzzy::Rules     accelerationRules_;
    fuzzy::Rules     rudderRules_;
    fuzzy::Relations accelerationRelations_;
    fuzzy::Relations rudderRelations_;
};
