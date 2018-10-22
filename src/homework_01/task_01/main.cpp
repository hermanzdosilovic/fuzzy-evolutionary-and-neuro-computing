#include <fuzzy/domain.hpp>

#include <iostream>

int main()
{
    fuzzy::Domain d1 = fuzzy::Domain::Range( 0, 5 );
    std::cout << "Elements of domain d1:\n" << d1 << '\n';
    std::cout << "Cardinality of domain d1: " << std::size( d1 ) << '\n';

    std::cout << '\n';

    fuzzy::Domain d2 = fuzzy::Domain::Range( 0, 3 );
    std::cout << "Elements of domain d2:\n" << d2 << '\n';
    std::cout << "Cardinality of domain d2: " << std::size( d2 ) << '\n';

    std::cout << '\n';

    auto d3 = d1 * d2;
    std::cout << "Elements of domain d3:\n" << d3 << '\n';
    std::cout << "Cardinality of domain d3: " << std::size( d3 ) << '\n';

    std::cout << '\n';

    std::cout << d3[ 0  ] << '\n';
    std::cout << d3[ 5  ] << '\n';
    std::cout << d3[ 14 ] << '\n';
    std::cout << d3.index( { 4, 1 } ) << '\n';

    return 0;
}
