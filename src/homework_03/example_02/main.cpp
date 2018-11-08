#include <fuzzy/domain.hpp>
#include <fuzzy/implication.hpp>
#include <fuzzy/set.hpp>

#include <iostream>

int main()
{
    fuzzy::Domain const d{ fuzzy::Domain::Range( 1, 4 ) };

    fuzzy::Set smallCurrent{ d };
    smallCurrent[ { 1 } ] = 1.0;
    smallCurrent[ { 2 } ] = 0.6;
    smallCurrent[ { 3 } ] = 0.0;

    fuzzy::Set highVoltage{ d };
    highVoltage[ { 1 } ] = 0.1;
    highVoltage[ { 2 } ] = 0.5;
    highVoltage[ { 3 } ] = 1.0;

    auto result{ fuzzy::implication< fuzzy::ImplicationType::ZADEH >( smallCurrent, highVoltage ) };
    std::cout << result << '\n';

    return 0;
}
