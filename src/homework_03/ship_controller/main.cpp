#include "rules.hpp"
#include <fuzzy/inference/engine.hpp>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    int a;
    std::cin >> a;
    auto rules = accelerationRules( a == 0 ? fuzzy::ImplicationType::MAMDANI_MIN : fuzzy::ImplicationType::MAMDANI_PRODUCT );

    for ( std::string line; std::getline( std::cin, line ); )
    {
        if ( line == "KRAJ" )
        {
            break;
        }

        std::istringstream stream{ line };
        std::uint16_t leftDistance, rightDistance, upperLeftDistance, upperRightDistance, speed, direction;

        stream >> leftDistance >> rightDistance >> upperLeftDistance >> upperRightDistance >> speed >> direction;
    }
    return 0;
}
