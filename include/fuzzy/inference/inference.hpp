#pragma once

#include <cstdint>

namespace fuzzy
{

enum class InferenceType : std::uint8_t
{
    COMPOSITION,
    INDIVIDUAL_RULE
};

}
