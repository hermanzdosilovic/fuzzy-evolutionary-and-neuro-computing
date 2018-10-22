#include <fuzzy/domain.hpp>
#include <fuzzy/set.hpp>

#include <iostream>

int main()
{
    fuzzy::Domain u1 = fuzzy::Domain::Range( 1, 5 );
    fuzzy::Domain u2 = fuzzy::Domain::Range( 1, 4 );
    fuzzy::Domain u3 = fuzzy::Domain::Range( 1, 5 );

    fuzzy::Set r1{ u1 * u2 };
    r1[ { 1, 1 } ] = 0.3;
    r1[ { 1, 2 } ] = 1.0;
    r1[ { 3, 3 } ] = 0.5;
    r1[ { 4, 3 } ] = 0.5;

    fuzzy::Set r2{ u2 * u3 };
    r2[ { 1, 1 } ] = 1.0;
    r2[ { 2, 1 } ] = 0.5;
    r2[ { 2, 2 } ] = 0.7;
    r2[ { 3, 3 } ] = 1.0;
    r2[ { 3, 4 } ] = 0.4;

    std::cout << r1 * r2 << '\n';

    return 0;
}
