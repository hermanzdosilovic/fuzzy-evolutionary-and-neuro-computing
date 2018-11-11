#pragma once

#include <fuzzy/defuzzyfication.hpp>
#include <fuzzy/domain.hpp>
#include <fuzzy/inference/engine.hpp>
#include <fuzzy/inference/rule.hpp>
#include <fuzzy/operation.hpp>
#include <fuzzy/relation.hpp>

#include <cstdint>
#include <iterator>
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
        rudderEngine_{ rudderEngine }
    {
        accelerationRelations_ = std::move
        (
            fuzzy::rule::relations
            (
                accelerationRules,
                accelerationEngine_.tNormType(),
                accelerationEngine_.implicationType()
            )
        );

        rudderRelations_ = std::move
        (
            fuzzy::rule::relations
            (
                rudderRules,
                rudderEngine_.tNormType(),
                rudderEngine_.implicationType()
            )
        );

        accelerationResultDomain_ = accelerationRules[ 0 ].consequent().domain();
        rudderResultDomain_       = rudderRules      [ 0 ].consequent().domain();
    }

    std::pair< std::int16_t, std::int16_t > maneuver
    (
        [[ maybe_unused ]] std::int16_t leftDistance,
        [[ maybe_unused ]] std::int16_t rightDistance,
        [[ maybe_unused ]] std::int16_t upperLeftDistance,
        [[ maybe_unused ]] std::int16_t upperRightDistance,
        [[ maybe_unused ]] std::int16_t speed,
        [[ maybe_unused ]] std::int16_t direction
    )
    {
        fuzzy::Element input;
        input += { leftDistance       };
        //input += { rightDistance      };
        //input += { upperLeftDistance  };
        //input += { upperRightDistance };
        //input += { speed              };
        //input += { direction          };

        auto const accelerationOutput{ accelerationEngine_.predict( input, accelerationRelations_, accelerationResultDomain_ ) };
        auto const rudderOutput      { rudderEngine_      .predict( input, rudderRelations_      , rudderResultDomain_       ) };

        double accelerationCenterOfArea{ fuzzy::centerOfArea( accelerationOutput ) };
        double rudderCenterOfArea      { fuzzy::centerOfArea( rudderOutput       ) };

        return { std::floor( accelerationCenterOfArea ), std::floor( rudderCenterOfArea ) };
    }

private:
    fuzzy::Engine    accelerationEngine_;
    fuzzy::Engine    rudderEngine_;
    fuzzy::Relations accelerationRelations_;
    fuzzy::Relations rudderRelations_;
    fuzzy::Domain    accelerationResultDomain_;
    fuzzy::Domain    rudderResultDomain_;
};
