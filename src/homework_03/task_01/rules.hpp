#pragma once

#include <fuzzy/domain.hpp>
#include <fuzzy/function.hpp>
#include <fuzzy/inference/rule.hpp>
#include <fuzzy/set.hpp>

fuzzy::Rules accelerationRules()
{
    fuzzy::Rules rules;

    fuzzy::Domain const u{ fuzzy::Domain::Range(   0, 100 ) };
    fuzzy::Domain const v{ fuzzy::Domain::Range( -50,  50 ) };
    fuzzy::Domain const d{ fuzzy::Domain::Range(   0,   2 ) };

    fuzzy::Rule r1
    {
        {
            fuzzy::Set{ u, fuzzy::lambda(  0,  50, 100 ) },
            fuzzy::Set{ u, fuzzy::lambda( 50, 100, 150 ) },
            fuzzy::Set{ d, fuzzy::universal }
        },
        fuzzy::Set{ v, fuzzy::lambda( 2, 5, 7 ) }
    };
    rules.emplace_back( r1 );

    fuzzy::Rule r2
    {
        {
            fuzzy::Set{ u, fuzzy::lambda( 50, 100, 150 ) },
            fuzzy::Set{ u, fuzzy::lambda(  0,  50, 100 ) },
            fuzzy::Set{ d, fuzzy::universal }
        },
        fuzzy::Set{ v, fuzzy::lambda( 2, 5, 7 ) }
    };
    rules.emplace_back( r2 );

    fuzzy::Rule r3
    {
        {
            fuzzy::Set{ u, fuzzy::universal },
            fuzzy::Set{ u, fuzzy::universal },
            fuzzy::Set{ d, fuzzy::universal }
        },
        fuzzy::Set{ v, fuzzy::lambda( -1, 0, 1 ) }
    };
    rules.emplace_back( r3 );

    return rules;
}

fuzzy::Rules rudderRules()
{
    fuzzy::Rules rules;

    fuzzy::Domain const u{ fuzzy::Domain::Range(   0, 100 ) };
    fuzzy::Domain const v{ fuzzy::Domain::Range( -90,  90 ) };
    fuzzy::Domain const d{ fuzzy::Domain::Range(   0,   2 ) };

    fuzzy::Rule r1
    {
        {
            fuzzy::Set{ u, fuzzy::lambda( 0, 50, 100 ) },
            fuzzy::Set{ u, fuzzy::universal },
            fuzzy::Set{ d, fuzzy::universal }
        },
        fuzzy::Set{ v, fuzzy::lambda( -90, -45, -30 ) }
    };
    rules.emplace_back( r1 );

    fuzzy::Rule r2
    {
        {
            fuzzy::Set{ u, fuzzy::universal },
            fuzzy::Set{ u, fuzzy::lambda( 0, 50, 100 ) },
            fuzzy::Set{ d, fuzzy::universal }
        },
        fuzzy::Set{ v, fuzzy::lambda( 30, 45, 90 ) }
    };
    rules.emplace_back( r2 );

    fuzzy::Rule r3
    {
        {
            fuzzy::Set{ u, fuzzy::universal },
            fuzzy::Set{ u, fuzzy::universal },
            fuzzy::Set{ d, fuzzy::universal }
        },
        fuzzy::Set{ v, fuzzy::lambda( -1, 0, 1 ) }
    };
    rules.emplace_back( r3 );

    fuzzy::Rule r4
    {
        {
            fuzzy::Set{ u, fuzzy::universal },
            fuzzy::Set{ u, fuzzy::universal },
            fuzzy::Set{ d, fuzzy::singleton( 0 ) }
        },
        fuzzy::Set{ v, fuzzy::lambda( 0, 20, 30 ) }
    };
    rules.emplace_back( r3 );

    return rules;
}
