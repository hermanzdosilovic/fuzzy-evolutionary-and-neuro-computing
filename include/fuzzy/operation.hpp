#pragma once

#include <fuzzy/implication.hpp>
#include <fuzzy/relation.hpp>

namespace fuzzy
{

Relation cross( Relation const & r1, Relation const & r2 )
{
    return implication< ImplicationType::ZADEH >( r1, r2 );
}

}
