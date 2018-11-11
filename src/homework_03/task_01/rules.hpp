#pragma once

#include <fuzzy/domain.hpp>
#include <fuzzy/function.hpp>
#include <fuzzy/inference/rule.hpp>
#include <fuzzy/set.hpp>

fuzzy::Rules accelerationRules()
{
    fuzzy::Rules rules;

    fuzzy::Domain const u{ fuzzy::Domain::Range(   0, 100 ) };
    fuzzy::Domain const v{ fuzzy::Domain::Range( -10,  10 ) };

    fuzzy::Rule r1
    {
        {
            fuzzy::Set{ u, fuzzy::lambda( 0, 50, 100 ) }
        },
        fuzzy::Set{ v, fuzzy::lambda( 0, 5, 10 ) }
    };
    rules.emplace_back( r1 );

    return rules;
}

fuzzy::Rules rudderRules()
{
    fuzzy::Rules rules;

    fuzzy::Domain const u{ fuzzy::Domain::Range(   0, 100 ) };
    fuzzy::Domain const v{ fuzzy::Domain::Range( -90,  90 ) };

    fuzzy::Rule r1
    {
        {
            fuzzy::Set{ u, fuzzy::lambda( 0, 50, 100 ) }
        },
        fuzzy::Set{ v, fuzzy::lambda( 0, 45, 90 ) }
    };
    rules.emplace_back( r1 );

    return rules;
}
