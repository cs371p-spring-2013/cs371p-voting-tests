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
    % g++ -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz.c++.app -lcppunit -ldl
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
// TestCollatz
// -----------

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_1 () {
        std::istringstream r("1\nTom\n1\n");
        std::vector<Candidate> v;
        std::pair<int, int> p;
        voting_read(r, v, p);

        CPPUNIT_ASSERT(v.size() ==  1);
        CPPUNIT_ASSERT(p.first  ==  1);
        CPPUNIT_ASSERT(p.second ==  1);}

    void test_read_2 () {
        std::istringstream r("2\nTom\nLorena\n1 2\n2 1\n1 2\n");
        std::vector<Candidate> v;
        std::pair<int, int> p;
        voting_read(r, v, p);

        CPPUNIT_ASSERT(v.size() ==  2);
        CPPUNIT_ASSERT(p.first  ==  2);
        CPPUNIT_ASSERT(p.second ==  3);}

    void test_read_3 () {
        std::istringstream r("2\nTom\nLorena\n1 2\n2 1\n1 2\n\n1\nMarilu\n1\n");
        std::vector<Candidate> v;
        std::pair<int, int> p;
        voting_read(r, v, p);

        CPPUNIT_ASSERT(v.size() ==  2);
        CPPUNIT_ASSERT(p.first  ==  2);
        CPPUNIT_ASSERT(p.second ==  3);}

    // ----
    // eval
    // ----

    void test_eval_1 () {
        std::istringstream r("2\nTom\nLorena\n1 2\n2 1\n1 2\n\n1\nMarilu\n1\n");
        std::ostringstream w;

        std::vector<Candidate> v;
        std::pair<int, int> p;

        voting_read (r, v, p);
        voting_eval (v, p);
        voting_print (w, v);

        CPPUNIT_ASSERT(w.str() == "Tom\n");}

    void test_eval_2 () {
        std::istringstream r("3\nTom\nLorena\nMarilu\n1 2 3\n2 1 3\n1 2 3\n3 2 1\n3 1 2\n3 1 2\n");
        std::ostringstream w;

        std::vector<Candidate> v;
        std::pair<int, int> p;

        voting_read (r, v, p);
        voting_eval (v, p);
        voting_print (w, v);

        CPPUNIT_ASSERT(w.str() == "Tom\nMarilu\n");}

    void test_eval_3 () {
        std::istringstream r("3\nTom\nLorena\nMarilu\n1 2 3\n2 1 3\n1 2 3\n3 2 1\n3 1 2\n");
        std::ostringstream w;

        std::vector<Candidate> v;
        std::pair<int, int> p;

        voting_read (r, v, p);
        voting_eval (v, p);
        voting_print (w, v);

        CPPUNIT_ASSERT(w.str() == "Tom\n");}

    // -----
    // print
    // -----
    void test_print_1 () {
        std::ostringstream w;
        std::vector<Candidate> v(3);
 
        for(size_t i = 0; i < v.size(); ++i) {
            if(!(i % 2)) {
                v[i].valid = true;
            }
        }

        v[0].name = "Jack";
        v[2].name = "Lucy";

        voting_print(w, v);
        CPPUNIT_ASSERT(w.str() == "Jack\nLucy\n");}

    void test_print_2 () {
        std::ostringstream w;
        std::vector<Candidate> v(30);

        voting_print(w, v);
        CPPUNIT_ASSERT(w.str() == "");}

    void test_print_3 () {
        std::ostringstream w;
        std::vector<Candidate> v(3);

       v[0].valid = true;
       v[0].name = "a";

       for(size_t i = 1; i < v.size(); ++i) {
           v[i].valid = true;
           v[i].name = "a" + v[i - 1].name;
        }

        voting_print(w, v);

        CPPUNIT_ASSERT(w.str() == "a\naa\naaa\n");}


    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1\n\n3\nTom\nLorena\nMarilu\n1 2 3\n2 1 3\n1 2 3\n3 2 1\n3 1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Tom\n");}

    void test_solve_2 () {
        std::istringstream r("1\n\n3\nTom\nLorena\nMarilu\n1 2 3\n2 1 3\n1 2 3\n3 2 1\n3 1 2\n3 1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Tom\nMarilu\n");}

    void test_solve_3 () {
        std::istringstream r("2\n\n1\nTom\n1\n\n1\nLorena\n1\n\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Tom\n\nLorena\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
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