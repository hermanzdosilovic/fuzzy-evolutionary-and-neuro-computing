#include "rules.hpp"
#include "ship_controller.hpp"

#include <fuzzy/inference/engine.hpp>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    ShipController shipController
    {
        fuzzy::Engine::MinimumInferenceEngine(),
        fuzzy::Engine::MinimumInferenceEngine(),
        accelerationRules(),
        rudderRules()
    };

    for ( std::string line; std::getline( std::cin, line ); )
    {
        if ( line == "KRAJ" )
        {
            break;
        }

        std::istringstream stream{ line };

        std::int16_t leftDistance, rightDistance, upperLeftDistance, upperRightDistance, speed, direction;

        stream >> leftDistance >> rightDistance >> upperLeftDistance >> upperRightDistance >> speed >> direction;

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
    }

    return 0;
}
