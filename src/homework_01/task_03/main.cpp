#include <fuzzy/function.hpp>
#include <fuzzy/set.hpp>

#include <iostream>

int main()
{
    fuzzy::Domain d1{ 0, 11 };
    fuzzy::Domain d2{ -5, 5 };

    fuzzy::Set s1{ d1 };
    fuzzy::Set s2{ d2 };
    std::cout << "s1 == s2 -> " << std::boolalpha << ( s1 == s2 ) << '\n';

    s1[ { 1 } ] = s2[ { 1 } ] = 0.45;
    std::cout << "s1 == s2 -> " << std::boolalpha << ( s1 == s2 ) << '\n';

    s1[ { 4 } ] = s2[ { 4 } ] = 0.38;
    std::cout << "s1 == s2 -> " << std::boolalpha << ( s1 == s2 ) << '\n';

    s2[ { -5 } ] = 0.84;
    std::cout << "s1 == s2 -> " << std::boolalpha << ( s1 == s2 ) << '\n';

    return 0;
}
