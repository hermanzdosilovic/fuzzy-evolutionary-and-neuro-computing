#include "../task_01/rules.hpp"
#include "../task_01/ship_controller.hpp"

#include <fuzzy/inference/engine.hpp>

#include <iostream>

int main()
{
    ShipController shipController
    {
        fuzzy::Engine::MinimumInferenceEngine(),
        fuzzy::Engine::MinimumInferenceEngine(),
        accelerationRules(),
        rudderRules()
    };

    std::int16_t leftDistance, rightDistance, upperLeftDistance, upperRightDistance, speed, direction;

    std::cin >> leftDistance >> rightDistance >> upperLeftDistance >> upperRightDistance >> speed >> direction;

    auto const [ acceleration, angle ] = shipController.maneuver
    (
        leftDistance,
        rightDistance,
        upperLeftDistance,
        upperRightDistance,
        speed,
        direction
    );

    std::cout << acceleration << " " << angle << std::endl;

    return 0;
}
