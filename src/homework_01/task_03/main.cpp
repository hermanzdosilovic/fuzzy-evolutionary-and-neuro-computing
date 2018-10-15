#include <fuzzy/function.hpp>
#include <fuzzy/set.hpp>

#include <iostream>

int main()
{
    fuzzy::Domain d1{ 0, 11 };
    fuzzy::Domain d2{ -5, 5 };

    fuzzy::Set s1{ d1 };
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
    assert( s3.is_universal() == true );

    assert( s1.is_universal() == false );
    assert( s2.is_universal() == false );

    fuzzy::Set s4 = fuzzy::Set::Empty();
    assert( s1.is_empty() == false );
    assert( s2.is_empty() == false );
    assert( s3.is_empty() == false );
    assert( s4.is_empty() == true );
    assert( s4.is_universal() == false );

    return 0;
}
