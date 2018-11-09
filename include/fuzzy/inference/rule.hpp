#pragma once

#include <fuzzy/set.hpp>

#include <vector>

namespace fuzzy
{

class Rule
{
public:
    Rule
    (
        std::vector< Set > antecedent,
        Set                consequent
    ) :
        antecedent_{ antecedent },
        consequent_{ consequent }
    {}

    auto const & antecedent() const { return antecedent_; }
    auto const & consequent() const { return consequent_; }

private:
    std::vector< Set > antecedent_;
    Set                consequent_;
};

using Rules = std::vector< Rule >;

}
