#include <fuzzy/function.hpp>
#include <fuzzy/hamacher.hpp>
#include <fuzzy/set.hpp>
#include <fuzzy/zadeh.hpp>

#include <iostream>

int main()
{
    fuzzy::Domain d = fuzzy::Domain::Range( 0, 11 );

    // Scope for unrelated stuff of actual task.
    {
        fuzzy::Domain d2 = fuzzy::Domain::Range( -5, 5 );

        fuzzy::Set s1{ d };
        fuzzy::Set s2{ d2 };
        assert( s1 == s2 );

        s1[ { 1 } ] = s2[ { 1 } ] = 0.45;
        assert( s1 == s2 );

        s1[ { 4 } ] = s2[ { 4 } ] = 0.38;
        assert( s1 == s2 );

        s2[ { -5 } ] = 0.84;
        assert( s1 != s2 );

        assert( s1 <= s2 );
        assert( s2 >= s1 );

        s2[ { -5 } ] = 0;
        s1[ { 1 }  ] = 0.65;
        assert( s2 <= s1 );
        assert( s1 >= s2 );

        fuzzy::Set s3 = fuzzy::Set::Universal();
        assert( s3.isUniversal() == true );

        assert( s1.isUniversal() == false );
        assert( s2.isUniversal() == false );

        fuzzy::Set s4 = fuzzy::Set::Empty();
        assert( s1.empty() == false );
        assert( s2.empty() == false );
        assert( s3.empty() == false );

        assert( s4.empty() == true );
        assert( s4.isUniversal() == false );
    }

    fuzzy::Set set1{ d };
    set1[ { 0 } ] = 1.0;
    set1[ { 1 } ] = 0.8;
    set1[ { 2 } ] = 0.6;
    set1[ { 3 } ] = 0.4;
    set1[ { 4 } ] = 0.2;
    std::cout << "Set1:\n" << set1 << '\n';

    std::cout << '\n';

    fuzzy::Set notSet1 = fuzzy::zadeh::operator!( set1 );
    std::cout << "notSet1:\n" << notSet1 << '\n';

    std::cout << '\n';

    fuzzy::Set unionSet{ fuzzy::zadeh::operator|( set1, notSet1 ) };
    std::cout << "Set1 union notSet1:\n" << unionSet << '\n';

    std::cout << '\n';

    fuzzy::Set intersectionSet{ fuzzy::zadeh::operator&( set1, notSet1 ) };
    std::cout << "Set1 intersection notSet1:\n" << intersectionSet << '\n';

    std::cout << '\n';

    fuzzy::Set hinters{ fuzzy::hamacher::tNorm( set1, notSet1, 1.0 ) };
    std::cout << "Set1 intersection with notSet1 using parametrised Hamacher T norm with parameter 1.0:\n" << hinters << '\n';

    std::cout << '\n';

    fuzzy::Set hinters2{ fuzzy::hamacher::sNorm( set1, notSet1, 1.0 ) };
    std::cout << "Set1 union with notSet1 using parametrised Hamacher S norm with parameter 1.0:\n" << hinters2 << '\n';
    return 0;
}

