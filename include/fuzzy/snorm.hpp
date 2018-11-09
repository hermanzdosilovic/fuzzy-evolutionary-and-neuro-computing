#pragma once

#include <cmath>
#include <cstdint>

namespace fuzzy
{

enum class SNormType : std::uint8_t
{
    ZADEH_MAX,
    HAMACHER_SUM,
    ALGEBRAIC_SUM,
    EINSTEIN_SUM,
    CONSTAINED_SUM,
    DRASTIC_SUM
};

template< SNormType sNormType >
double snorm( double const x, double const y );

template<>
double snorm< SNormType::ZADEH_MAX >( double const x, double const y )
{
    return std::max( x, y );
}

template<>
double snorm< SNormType::HAMACHER_SUM >( double const x, double const y )
{
    return ( x + y - 2.0 * x * y ) / ( 1.0 - x * y );
}

template<>
double snorm< SNormType::ALGEBRAIC_SUM >( double const x, double const y )
{
    return x + y - x * y;
}

template<>
double snorm< SNormType::EINSTEIN_SUM >( double const x, double const y )
{
    return ( x + y ) / ( 1.0 + x * y );
}

template<>
double snorm< SNormType::CONSTAINED_SUM >( double const x, double const y )
{
    return std::min( 1.0, x + y );
}

template<>
double snorm< SNormType::DRASTIC_SUM >( double const x, double const y )
{
    return std::min( x, y ) == 0.0 ? std::max( x, y ) : 1.0;
}

auto snorm( SNormType const sNormType = SNormType::ZADEH_MAX )
{
    switch ( sNormType )
    {
        case SNormType::ZADEH_MAX:
            return snorm< SNormType::ZADEH_MAX >;
        case SNormType::HAMACHER_SUM:
            return snorm< SNormType::HAMACHER_SUM >;
        case SNormType::ALGEBRAIC_SUM:
            return snorm< SNormType::ALGEBRAIC_SUM >;
        case SNormType::EINSTEIN_SUM:
            return snorm< SNormType::EINSTEIN_SUM >;
        case SNormType::CONSTAINED_SUM:
            return snorm< SNormType::CONSTAINED_SUM >;
        case SNormType::DRASTIC_SUM:
            return snorm< SNormType::DRASTIC_SUM >;
    }

#ifdef __GNUC__
    __builtin_unreachable();
#endif
}

double snorm( double const x, double const y, SNormType const sNormType = SNormType::ZADEH_MAX )
{
    return snorm( sNormType )( x, y );
}

}
