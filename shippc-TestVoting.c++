// --------------------------------
// projects/voting/TestVoting.c++
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
    % g++ -lcppunit -ldl -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz.c++.app
    % valgrind TestCollatz.c++.app >& TestCollatz.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read () {
        std::istringstream r("1\nMichael Williams\n1\n1\n1\n");
        std::ostringstream w;
        std::vector<std::string> winners = voting_read(r, w);
        CPPUNIT_ASSERT(winners[0].compare("Michael Williams") == 0);
    }

    void test_read2 () {
        std::istringstream r("2\nMichael Williams\nAbby Smith\n1 2\n2 1\n1 2\n");
        std::ostringstream w;
        std::vector<std::string> winners = voting_read(r, w);
        CPPUNIT_ASSERT(winners[0].compare("Michael Williams") == 0);
    }

    void test_read3 () {
        std::istringstream r("0\n");
        std::ostringstream w;
        std::vector<std::string> winners = voting_read(r, w);
        CPPUNIT_ASSERT(winners[0].compare("no candidates") == 0);
    }

    // ----
    // maxmin
    // ----

    void test_maxmin () {
        std::vector<int> totals;
        for (int i = 1; i <= 5; ++i) {
            totals.push_back(i);
        }
        std::vector<int> result = voting_maxmin(totals);
        std::vector<int> correct = {5, 1};
        CPPUNIT_ASSERT(std::equal(result.begin(), result.begin() + 2, correct.begin()));
    }

    void test_maxmin2 () {
        std::vector<int> totals;
        totals.push_back(-1);
        for (int i = 2; i <= 5; ++i) {
            totals.push_back(i);
        }
        std::vector<int> result = voting_maxmin(totals);
        std::vector<int> correct = {5, 2};
        CPPUNIT_ASSERT(std::equal(result.begin(), result.begin() + 2, correct.begin()));
    }

    void test_maxmin3 () {
        std::vector<int> totals;
        for (int i = 1; i <= 5; ++i) {
            totals.push_back(1);
        }
        std::vector<int> result = voting_maxmin(totals);
        std::vector<int> correct = {1, 1};
        CPPUNIT_ASSERT(std::equal(result.begin(), result.begin() + 2, correct.begin()));
    }

    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        std::vector<std::string> winners;
        winners.push_back("Michael White");
        voting_print(w, winners);
        CPPUNIT_ASSERT(w.str() == "Michael White");
    }

    void test_print2 () {
        std::ostringstream w;
        std::vector<std::string> winners;
        winners.push_back("no candidates");
        voting_print(w, winners);
        CPPUNIT_ASSERT(w.str() == "no candidates");
    }

    void test_print3 () {
        std::ostringstream w;
        std::vector<std::string> winners;
        winners.push_back("Michael White");
        winners.push_back("Jacob Tenberg");
        voting_print(w, winners);
        CPPUNIT_ASSERT(w.str() == "Michael White\nJacob Tenberg");
    }

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1\n\n2\nJohn Smith\nLily Smith\n1 2\n1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Mitch");
    }

    void test_solve2 () {
        std::istringstream r("1\n\n2\nJohn Smith\nLily Smith\n1 2\n2 1\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Smith\nLily Smith");
    }

    void test_solve3 () {
        std::istringstream r("1\n\n3\nJohn Smith\nLily Smith\nJames Smith\n1 2 3\n2 1 3\n3 1 2\n1 2 3\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Smith");
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);

    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read2);
    CPPUNIT_TEST(test_read3);

    CPPUNIT_TEST(test_maxmin);
    CPPUNIT_TEST(test_maxmin2);
    CPPUNIT_TEST(test_maxmin3);


    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);

    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve2);
    CPPUNIT_TEST(test_solve3);

    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
