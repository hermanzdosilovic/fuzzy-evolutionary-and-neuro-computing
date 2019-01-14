#include <cmath>
#include <iostream>

int main()
{
    constexpr auto f
    {
        []( auto const x, auto const y )
        {
            auto xSquared{ ( x - 1 ) * ( x - 1 ) };
            auto ySquared{ ( y + 2 ) * ( y + 2 ) };
            auto cosineFactor{ std::cos( x / 5.0 ) };

            return ( xSquared + ySquared - 5 * x * y + 3 ) * cosineFactor * cosineFactor;
        }
    };

   constexpr auto minX{ -4 };
   constexpr auto maxX{  4 };

   constexpr auto minY{ -4 };
   constexpr auto maxY{  4 };

   constexpr auto stepX{ 1 };
   constexpr auto stepY{ 1 };

   for ( auto x{ minX }; x <= maxX; x += stepX )
   {
       for ( auto y{ minY }; y <= maxY; y += stepY )
       {
           std::cout << x << ' ' << y << ' ' << f( x, y ) << '\n';
       }
   }

    return 0;
}
