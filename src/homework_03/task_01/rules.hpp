#pragma once

#include <fuzzy/domain.hpp>
#include <fuzzy/function.hpp>
#include <fuzzy/inference/rule.hpp>
#include <fuzzy/set.hpp>

fuzzy::Rules accelerationRules()
{
    fuzzy::Rules rules;

    fuzzy::Domain const u{ fuzzy::Domain::Range(   0, 2 ) };
    fuzzy::Domain const v{ fuzzy::Domain::Range( -10, 10 ) };

    fuzzy::Rule r1
    {
        {
            fuzzy::Set{ u, fuzzy::lambda( 25, 50, 100 ) },
            fuzzy::Set::Universal(),
            fuzzy::Set::Universal(),
            fuzzy::Set::Universal(),
            fuzzy::Set{ u, fuzzy::lambda( 5, 10, 10 ) },
            fuzzy::Set::Universal(),
        },
        fuzzy::Set{ v, fuzzy::lambda( -10, -5, 0 ) }
    };
    rules.emplace_back( r1 );

    fuzzy::Rule r2
    {
        {
            fuzzy::Set::Universal(),
            fuzzy::Set{ u, fuzzy::lambda( 25, 50, 100 ) },
            fuzzy::Set::Universal(),
            fuzzy::Set::Universal(),
            fuzzy::Set{ u, fuzzy::lambda( 5, 10, 10 ) },
            fuzzy::Set::Universal(),
        },
        fuzzy::Set{ v, fuzzy::lambda( -10, -5, 0 ) }
    };
    rules.emplace_back( r2 );

    return rules;
}

fuzzy::Rules rudderRules()
{
    fuzzy::Rules rules;

    fuzzy::Domain const u{ fuzzy::Domain::Range(   0, 1301 ) };
    fuzzy::Domain const v{ fuzzy::Domain::Range( -90,   90 ) };

    fuzzy::Rule r1
    {
        {
            fuzzy::Set{ u, fuzzy::lambda( 25, 50, 100 ) },
            fuzzy::Set::Universal(),
            fuzzy::Set::Universal(),
            fuzzy::Set::Universal(),
            fuzzy::Set::Universal(),
            fuzzy::Set::Universal(),
        },
        fuzzy::Set{ v, fuzzy::lambda( -90, -45, 0 ) }
    };
    rules.emplace_back( r1 );

    fuzzy::Rule r2
    {
        {
            fuzzy::Set::Universal(),
            fuzzy::Set{ u, fuzzy::lambda( 25, 50, 100 ) },
            fuzzy::Set::Universal(),
            fuzzy::Set::Universal(),
            fuzzy::Set::Universal(),
            fuzzy::Set::Universal(),
        },
        fuzzy::Set{ v, fuzzy::lambda( 0, 45, 90 ) }
    };
    rules.emplace_back( r2 );

    return rules;
}
