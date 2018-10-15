#include <fuzzy/function.hpp>
#include <fuzzy/set.hpp>

#include <iostream>

int main()
{
    fuzzy::Domain d{ 0, 11 };
    fuzzy::Set set1{ d };
    set1[ { 0 } ] = 1.0;
    set1[ { 1 } ] = 0.8;
    set1[ { 2 } ] = 0.6;
    set1[ { 3 } ] = 0.4;
    set1[ { 4 } ] = 0.2;
    std::cout << "Set1:\n" << set1 << '\n';

    std::cout << '\n';

    fuzzy::Domain d2{ -5, 6 };
    fuzzy::Set set2{ d2, fuzzy::lambda( d2.index( { -4 } ), d2.index( { 0 } ), d2.index( { 4 } ) ) };
    // I think there is an error in homework instructions.
    // Following lamda parameters give output from instructions.
    // fuzzy::Set set2{ d2, fuzzy::lambda( -4, 0, 4 ) };
    std::cout << "Set2:\n" << set2 << '\n';

    return 0;
}
