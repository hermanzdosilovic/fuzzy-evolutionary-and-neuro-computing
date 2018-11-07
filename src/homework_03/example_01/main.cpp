#include <fuzzy/domain.hpp>
#include <fuzzy/relation.hpp>
#include <fuzzy/set.hpp>

#include <iostream>

int main()
{
    fuzzy::Domain const inputVoltage{ fuzzy::Domain::Range( 1, 6 ) };
    fuzzy::Domain const outputVoltage{ fuzzy::Domain::Range( 1, 6 ) };

    fuzzy::Relation voltageRelation{ inputVoltage * outputVoltage };
    voltageRelation[ { 1, 1 } ] = 1.0;
    voltageRelation[ { 2, 3 } ] = 1.0;
    voltageRelation[ { 3, 4 } ] = 1.0;
    voltageRelation[ { 4, 2 } ] = 1.0;
    voltageRelation[ { 5, 1 } ] = 1.0;

    fuzzy::Set x{ inputVoltage };
    x[ { 3 } ] = 1.0;

    auto result{ fuzzy::relation::composition( x, voltageRelation ) };
    std::cout << result << '\n';

    return 0;
}
