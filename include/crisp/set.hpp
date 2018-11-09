#pragma once

#include <fuzzy/domain.hpp>

#include <vector>

namespace crisp
{

using Set = std::vector< fuzzy::Domain::element_type >;

}

crisp::Set & operator<<( crisp::Set & set, crisp::Set::value_type const & element )
{
    set.push_back( element );
    return set;
}
