#pragma once

#include <cmath>
#include <cstdint>

namespace fuzzy
{

enum class TNormType : std::uint8_t
{
    ZADEH_MIN,
    HAMACHER_PRODUCT,
    ALGEBRAIC_PRODUCT,
    EINSTEIN_PRODUCT,
    CONSTAINED_PRODUCT,
    DRASTIC_PRODUCT
};

template< TNormType tNormType = TNormType::ZADEH_MIN >
double tnorm( double const x, double const y );

template<>
double tnorm< TNormType::ZADEH_MIN >( double const x, double const y )
{
    return std::min( x, y );
}

template<>
double tnorm< TNormType::HAMACHER_PRODUCT >( double const x, double const y )
{
    return ( x * y ) / ( x + y - x * y );
}

template<>
double tnorm< TNormType::ALGEBRAIC_PRODUCT >( double const x, double const y )
{
    return x * y;
}

template<>
double tnorm< TNormType::EINSTEIN_PRODUCT >( double const x, double const y )
{
    return ( x * y ) / ( 2.0 - ( x + y - x * y ) );
}

template<>
double tnorm< TNormType::CONSTAINED_PRODUCT >( double const x, double const y )
{
    return std::max( 0.0, x + y - 1.0 );
}

template<>
double tnorm< TNormType::DRASTIC_PRODUCT >( double const x, double const y )
{
    return std::max( x, y ) == 1.0 ? std::min( x, y ) : 0.0;
}

auto tnorm( TNormType const tNormType = TNormType::ZADEH_MIN )
{
    switch ( tNormType )
    {
        case TNormType::ZADEH_MIN:
            return tnorm< TNormType::ZADEH_MIN >;
        case TNormType::HAMACHER_PRODUCT:
            return tnorm< TNormType::HAMACHER_PRODUCT >;
        case TNormType::ALGEBRAIC_PRODUCT:
            return tnorm< TNormType::ALGEBRAIC_PRODUCT >;
        case TNormType::EINSTEIN_PRODUCT:
            return tnorm< TNormType::EINSTEIN_PRODUCT >;
        case TNormType::CONSTAINED_PRODUCT:
            return tnorm< TNormType::CONSTAINED_PRODUCT >;
        case TNormType::DRASTIC_PRODUCT:
            return tnorm< TNormType::DRASTIC_PRODUCT >;
    }

#ifdef __GNUC__
    __builtin_unreachable();
#endif
}

double tnorm( double const x, double const y, TNormType const tNormType = TNormType::ZADEH_MIN )
{
    return tnorm( tNormType )( x, y );
}

}
