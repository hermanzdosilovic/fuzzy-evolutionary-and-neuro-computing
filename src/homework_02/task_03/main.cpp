#include <fuzzy/set.hpp>
#include <fuzzy/relation.hpp>

#include <cstdint>
#include <iostream>

int main()
{
    fuzzy::Domain u = fuzzy::Domain::Range( 1, 5 );

    fuzzy::Set r{ u * u };
    r[ { 1, 1 } ] = 1.0;
    r[ { 2, 2 } ] = 1.0;
    r[ { 3, 3 } ] = 1.0;
    r[ { 4, 4 } ] = 1.0;
    r[ { 1, 2 } ] = 0.3;
    r[ { 2, 1 } ] = 0.3;
    r[ { 2, 3 } ] = 0.5;
    r[ { 3, 2 } ] = 0.5;
    r[ { 3, 4 } ] = 0.2;
    r[ { 4, 3 } ] = 0.2;

    fuzzy::Set r2 = r;

    std::cout << "Početna relacija je neizrazita relacija ekvivalencije? " << std::boolalpha << fuzzy::relation::isEquivalence( r2 ) << '\n';
    std::cout << '\n';

    for ( std::uint16_t i{ 1 }; i <= 3; ++i )
    {
        r2 *= r;

        std::cout << "Broj odrađenih kompozicija: " << i << ". Relacija je:\n";
        std::cout << r2 << '\n';

        std::cout << "Ova relacija je neizrazita relacija ekvivalencije? " << std::boolalpha << fuzzy::relation::isEquivalence( r2 ) << '\n';
        std::cout << '\n';
    }

    return 0;
}
