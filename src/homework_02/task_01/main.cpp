#include <fuzzy/domain.hpp>
#include <fuzzy/relation.hpp>
#include <fuzzy/set.hpp>

#include <iostream>

int main()
{
    fuzzy::Domain u = fuzzy::Domain::Range( 1, 6 );
    auto u2 = u * u;

    fuzzy::Set r1{ u2 };
    r1[ { 1, 1 } ] = 1.0;
    r1[ { 2, 2 } ] = 1.0;
    r1[ { 3, 3 } ] = 1.0;
    r1[ { 4, 4 } ] = 1.0;
    r1[ { 5, 5 } ] = 1.0;
    r1[ { 3, 1 } ] = 0.5;
    r1[ { 1, 3 } ] = 0.5;

    fuzzy::Set r2{ u2 };
    r2[ { 1, 1 } ] = 1.0;
    r2[ { 2, 2 } ] = 1.0;
    r2[ { 3, 3 } ] = 1.0;
    r2[ { 4, 4 } ] = 1.0;
    r2[ { 5, 5 } ] = 1.0;
    r2[ { 3, 1 } ] = 0.5;
    r2[ { 1, 3 } ] = 0.1;

    fuzzy::Set r3{ u2 };
    r3[ { 1, 1 } ] = 1.0;
    r3[ { 2, 2 } ] = 1.0;
    r3[ { 3, 3 } ] = 0.3;
    r3[ { 4, 4 } ] = 1.0;
    r3[ { 5, 5 } ] = 1.0;
    r3[ { 1, 2 } ] = 0.6;
    r3[ { 2, 1 } ] = 0.6;
    r3[ { 2, 3 } ] = 0.7;
    r3[ { 3, 2 } ] = 0.7;
    r3[ { 3, 1 } ] = 0.5;
    r3[ { 1, 3 } ] = 0.5;

    fuzzy::Set r4{ u2 };
    r4[ { 1, 1 } ] = 1.0;
    r4[ { 2, 2 } ] = 1.0;
    r4[ { 3, 3 } ] = 1.0;
    r4[ { 4, 4 } ] = 1.0;
    r4[ { 5, 5 } ] = 1.0;
    r4[ { 1, 2 } ] = 0.4;
    r4[ { 2, 1 } ] = 0.4;
    r4[ { 2, 3 } ] = 0.5;
    r4[ { 3, 2 } ] = 0.5;
    r4[ { 3, 1 } ] = 0.4;
    r4[ { 1, 3 } ] = 0.4;

    std::cout << "r1 je definiran nad UxU? " << std::boolalpha << fuzzy::relation::isUxURelation( r1 ) << '\n';
    std::cout << "r1 je simetrična? " << std::boolalpha << fuzzy::relation::isSimetric( r1 ) << '\n';
    std::cout << "r2 je simetrična? " << std::boolalpha << fuzzy::relation::isSimetric( r2 ) << '\n';
    std::cout << "r1 je refleksivna? " << std::boolalpha << fuzzy::relation::isReflexive( r1 ) << '\n';
    std::cout << "r3 je refleksivna? " << std::boolalpha << fuzzy::relation::isReflexive( r3 ) << '\n';
    std::cout << "r3 je max-min tranzitivna? " << std::boolalpha << fuzzy::relation::isMaxMinTransitive( r3 ) << '\n';
    std::cout << "r4 je max-min tranzitivna? " << std::boolalpha << fuzzy::relation::isMaxMinTransitive( r4 ) << '\n';

    return 0;
}
