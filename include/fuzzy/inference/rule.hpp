#pragma once

#include <fuzzy/implication.hpp>
#include <fuzzy/operation.hpp>
#include <fuzzy/set.hpp>
#include <fuzzy/tnorm.hpp>

#include <iterator>
#include <vector>

namespace fuzzy
{

class Rule
{
public:
    Rule( Sets antecedent, Set consequent ) : antecedent_{ antecedent }, consequent_{ consequent } {}

    auto const & antecedent() const { return antecedent_; }
    auto const & consequent() const { return consequent_; }

    Relation relation( TNormType const tNormType, ImplicationType const implicationType ) const
    {
        return implication( cross( antecedent_, tNormType ), consequent_, implicationType );
    }

private:
    Sets antecedent_;
    Set  consequent_;
};

using Rules = std::vector< Rule >;

namespace rule
{

Relations relations( Rules const & rules, TNormType const tNormType, ImplicationType const implicationType )
{
    Relations results;
    results.reserve( std::size( rules ) );
    for ( auto const & rule : rules )
    {
        results.emplace_back( rule.relation( tNormType, implicationType ) );
    }
    return results;
}

}

}
