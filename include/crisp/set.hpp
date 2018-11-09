#pragma once

#include <fuzzy/element.hpp>

#include <vector>

namespace crisp
{

using Set = std::vector< fuzzy::Element >;

}

crisp::Set & operator<<( crisp::Set & set, crisp::Set::value_type const & element )
{
    set.push_back( element );
    return set;
}
