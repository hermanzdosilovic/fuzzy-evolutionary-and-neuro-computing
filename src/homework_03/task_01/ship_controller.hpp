#pragma once

#include <fuzzy/defuzzyfication.hpp>
#include <fuzzy/domain.hpp>
#include <fuzzy/inference/engine.hpp>
#include <fuzzy/inference/rule.hpp>
#include <fuzzy/operation.hpp>
#include <fuzzy/relation.hpp>

#include <cstdint>
#include <iostream>
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
    }

    std::pair< std::int16_t, std::int16_t > maneuver
    (
        std::int16_t leftDistance,
        std::int16_t rightDistance,
        std::int16_t upperLeftDistance,
        std::int16_t upperRightDistance,
        std::int16_t speed,
        std::int16_t direction
    )
    {
        fuzzy::Element input;
        input += { leftDistance       };
        input += { rightDistance      };
        input += { upperLeftDistance  };
        input += { upperRightDistance };
        input += { speed              };
        input += { direction          };

        std::cerr << input << std::endl;

        auto const accelerationOutput{ accelerationEngine_.predict( input, accelerationRelations_ ) };
        auto const rudderOutput      { rudderEngine_      .predict( input, rudderRelations_       ) };

        double accelerationCenterOfArea{ fuzzy::centerOfArea( accelerationOutput ) };
        double rudderCenterOfArea      { fuzzy::centerOfArea( rudderOutput       ) };

        std::cerr << accelerationCenterOfArea << " " << rudderCenterOfArea << std::endl;

        return { std::floor( accelerationCenterOfArea ), std::floor( rudderCenterOfArea ) };
    }

private:
    fuzzy::Engine    accelerationEngine_;
    fuzzy::Engine    rudderEngine_;
    fuzzy::Relations accelerationRelations_;
    fuzzy::Relations rudderRelations_;
};
