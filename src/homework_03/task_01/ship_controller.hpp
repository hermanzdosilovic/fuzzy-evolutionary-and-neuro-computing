#pragma once

#include <fuzzy/inference/engine.hpp>
#include <fuzzy/inference/rule.hpp>

#include <cstdint>
#include <utility>

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
    {}

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
    fuzzy::Engine accelerationEngine_;
    fuzzy::Engine rudderEngine_;
    fuzzy::Rules  accelerationRules_;
    fuzzy::Rules  rudderRules_;
};
