#pragma once

#include <fuzzy/domain.hpp>
#include <fuzzy/function.hpp>
#include <fuzzy/inference/rule.hpp>
#include <fuzzy/relation.hpp>
#include <fuzzy/implication.hpp>

#include <vector>

std::vector< fuzzy::Rule > accelerationRules( fuzzy::ImplicationType const implicationType )
{
    std::vector< fuzzy::Rule > rules;

    fuzzy::Domain const u{ fuzzy::Domain::Range( 0, 1301 ) };
    fuzzy::Domain const v{ fuzzy::Domain::Range( -1000, 1000 ) };

    fuzzy::Rule r1
    {
        fuzzy::implication
        (
            fuzzy::Relation{ u, fuzzy::lambda( 25, 50, 100 ) } *
            fuzzy::Relation{ u, fuzzy::lambda( 25, 50, 100 ) } *
            fuzzy::Relation{ u, fuzzy::lambda( 25, 50, 100 ) } *
            fuzzy::Relation{ u, fuzzy::lambda( 25, 50, 100 ) },
            fuzzy::Relation{ v, fuzzy::lambda( 25, 50, 100 ) },
            implicationType
        )
    };

    rules.emplace_back( r1 );
    return rules;
}

std::vector< fuzzy::Rule > rudderRules()
{
    std::vector< fuzzy::Rule > rules;
    return rules;
}
