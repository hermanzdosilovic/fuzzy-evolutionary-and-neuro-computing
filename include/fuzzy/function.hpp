#pragma once

#include "domain.hpp"

namespace fuzzy
{

auto gamma( Domain::value_type const alpha, Domain::value_type const beta )
{
    return [ alpha, beta ]
           ( Domain::element_type const & element ) -> double
           {
               if ( std::size( element ) == 0 ) { return 0; }

               auto const & x{ element[ 0 ] };

               if ( x < alpha ) { return 0; }
               if ( x < beta  ) { return ( x - alpha ) / static_cast< double >( beta - alpha ); }

               return 1;
           };
}

auto lambda( Domain::value_type const alpha, Domain::value_type const beta, Domain::value_type const gamma )
{
    return [ alpha, beta, gamma ]
           ( Domain::element_type const & element ) -> double
           {
               if ( std::size( element ) == 0 ) { return 0; }

               auto const & x{ element[ 0 ] };

               if ( x < alpha ) { return 0; }
               if ( x < beta  ) { return ( x - alpha ) / static_cast< double >( beta - alpha ); }
               if ( x < gamma ) { return ( gamma - x ) / static_cast< double >( gamma - beta ); }

               return 0;
           };
}

auto l( Domain::value_type const alpha, Domain::value_type const beta )
{
    return [ alpha, beta ]
           ( Domain::element_type const & element ) -> double
           {
               if ( std::size( element ) == 0 ) { return 0; }

               auto const & x{ element[ 0 ] };

               if ( x < alpha ) { return 1; }
               if ( x < beta  ) { return ( beta - x ) / static_cast< double >( beta - alpha ); }

               return 0;
           };
}

auto pi( Domain::value_type const alpha, Domain::value_type const beta, Domain::value_type const gamma, Domain::value_type const delta )
{
    return [ alpha, beta, gamma, delta ]
           ( Domain::element_type const & element ) -> double
           {
               if ( std::size( element ) == 0 ) { return 0; }

               auto const & x{ element[ 0 ] };

               if ( x < alpha  ) { return 0; }
               if ( x < beta   ) { return ( x - alpha ) / static_cast< double >( beta - alpha ); }
               if ( x < gamma  ) { return 1; }
               if ( x < delta  ) { return ( delta - x ) / static_cast< double >( delta - gamma ); }

               return 0;
           };
}

}
