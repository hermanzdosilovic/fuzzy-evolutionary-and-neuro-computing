#include <fuzzy/domain.hpp>

#include <iostream>

int main()
{
    fuzzy::Domain u{ 1, 6 };
    auto u2 = u * u;
    std::cout << u2 << '\n';

    return 0;
}
