// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*
To test the program:
% ls /usr/include/cppunit/
...
TestFixture.h
...
% locate libcppunit.a
/usr/lib/libcppunit.a
%g++ -ldl -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lcppunit
% valgrind TestVoting.c++.app >& TestVoting.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "Voting.h"

// -----------
// TestCollatz
// -----------

struct TestVoting : CppUnit::TestFixture {
 
    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}  
    void test_solve_2 () {
            std::istringstream r("1\n\n6\nJohn Doe\nJane Smith\nSirhan Sirhan\nCliff\nMicah\nDowning\n2 1 3 6 4 5\n2 1 3 6 5 4\n2 3 1 4 5 6\n1 2 3 5 4 6\n3 2 1 6 4 5\n6 1 4 2 3 5\n5 6 2 4 1 2\n1 2 3 4 5 6\n6 5 4 3 2 1\n\n");            std::ostringstream w;
            voting_solve(r, w);
            CPPUNIT_ASSERT(w.str() == "Jane Smith\n");}  
    void test_solve_3 () {
                std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 2 1\n");                std::ostringstream w;
                voting_solve(r, w);
                CPPUNIT_ASSERT(w.str() == "Jane Smith\n");}  




    // -----
    // suite
    // -----
    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
