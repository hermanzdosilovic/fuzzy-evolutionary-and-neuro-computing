#pragma once

#include <fuzzy/element.hpp>

namespace fuzzy
{

auto gamma( Element::value_type const alpha, Element::value_type const beta )
{
    return [ alpha, beta ]
           ( Element const & element ) -> double
           {
               if ( std::size( element ) == 0 ) { return 0; }

               auto const & x{ element[ 0 ] };

               if ( x < alpha ) { return 0; }
               if ( x < beta  ) { return ( x - alpha ) / static_cast< double >( beta - alpha ); }

               return 1;
           };
}

auto lambda( Element::value_type const alpha, Element::value_type const beta, Element::value_type const gamma )
{
    return [ alpha, beta, gamma ]
           ( Element const & element ) -> double
           {
               if ( std::size( element ) == 0 ) { return 0; }

               auto const & x{ element[ 0 ] };

               if ( x < alpha ) { return 0; }
               if ( x < beta  ) { return ( x - alpha ) / static_cast< double >( beta - alpha ); }
               if ( x < gamma ) { return ( gamma - x ) / static_cast< double >( gamma - beta ); }

               return 0;
           };
}

auto l( Element::value_type const alpha, Element::value_type const beta )
{
    return [ alpha, beta ]
           ( Element const & element ) -> double
           {
               if ( std::size( element ) == 0 ) { return 0; }

               auto const & x{ element[ 0 ] };

               if ( x < alpha ) { return 1; }
               if ( x < beta  ) { return ( beta - x ) / static_cast< double >( beta - alpha ); }

               return 0;
           };
}

auto pi( Element::value_type const alpha, Element::value_type const beta, Element::value_type const gamma, Element::value_type const delta )
{
    return [ alpha, beta, gamma, delta ]
           ( Element const & element ) -> double
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
