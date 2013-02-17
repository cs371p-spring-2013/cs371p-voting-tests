/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -Wl,--no-as-needed -lcppunit -ldl -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting.c++.app
    % valgrind TestVoting.c++.app >& TestVoting.c++.out
*/

//--------------------
// includes
//---------------------
#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <map>

#include <cppunit/extensions/HelperMacros.h> // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include <cppunit/TestFixture.h>             // TestFixture
#include <cppunit/TextTestRunner.h>
#include <cppunit/ui/text/TestRunner.h>          // TextTestRunner
#include <cppunit/CompilerOutputter.h>

#include "Voting.h"


// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {
    // ----
    // is_loser
    // ----

    void test_is_loser_1 () {
        std::vector<std::string> v(3);
        v[0] = "Alice";
        v[1] = "Avicci";
        v[2] = "Akmen";
        std::string s = "Alice";
        bool b = is_loser(v, s);
        CPPUNIT_ASSERT(b == true);}

    void test_is_loser_2 () {
        std::vector<std::string> v(3);
        v[0] = "Alice";
        v[1] = "Avicci";
        v[2] = "Akmen";
        std::string s = "Corey";
        bool b = is_loser(v, s);
        CPPUNIT_ASSERT(b == false);}

    void test_is_loser_3 () {
        std::vector<std::string> v(0);
        std::string s = "Alice";
        bool b = is_loser(v, s);
        CPPUNIT_ASSERT(b == false);}
    // ---------------
    // print_winners
    // ---------------

    void test_print_winners_1 () {
        std::ostringstream w;
        std::vector<std::string> v(3);
        std::vector<std::string> n(4);
        v[0] = "Alice";
        v[1] = "Madeon";
        v[2] = "Zedd";

        n[0] = "Zedd";
        n[1] = "Madeon";
        n[2] = "Caspa";
        n[3] = "Alice";
        print_winners(w, v, n);
        CPPUNIT_ASSERT(w.str() == "Zedd\nMadeon\nAlice\n");}

    void test_print_winners_2 () {
        std::ostringstream w;
        std::vector<std::string> v(1);
        std::vector<std::string> n(2);
        v[0] = "Zedd";

        n[0] = "Zedd";
        n[1] = "Madeon";

        print_winners(w, v, n);
        CPPUNIT_ASSERT(w.str() == "Zedd\n");}

    void test_print_winners_3 () {
        std::ostringstream w;
        std::vector<std::string> v(1);
        std::vector<std::string> n(4);

        n[0] = "Zedd";
        n[1] = "Madeon";
        n[2] = "Caspa";
        n[3] = "Alice";

        v[0] = "Bob";

        print_winners(w, v, n);
        CPPUNIT_ASSERT(w.str() == "");}

    // --------------
    // find_winners
    // --------------

    void test_find_winner_1 () {
        std::ostringstream w;
        std::vector<std::string> c(2);
        std::vector<std::vector<int> > b(2);
        std::vector<int> v1(2);
        int i = 1;
        int j = 2;
        v1[0] = i;
        v1[1] = j;
        std::vector<int> v2(2);
        v2[0] = i;
        v2[1] = j;
        c[0] = "Alice";
        c[1] = "Zedd";
        b[0] = v1;
        b[1] = v2;
        find_winner(w, c, b);
        CPPUNIT_ASSERT(w.str() == "Alice\n");}

    void test_find_winner_2 () {
        std::ostringstream w;
        std::vector<std::string> c(4);
        std::vector<std::vector<int> > b(6);
        std::vector<int> v1(4);
        v1[0] = 1;
        v1[1] = 2;
        v1[2] = 3;
        v1[3] = 4;
        std::vector<int> v2(4);
        v2[0] = 1;
        v2[1] = 2;
        v2[2] = 3;
        v2[3] = 4;
        std::vector<int> v3(4);
        v3[0] = 2;
        v3[1] = 1;
        v3[2] = 3;
        v3[3] = 4;
        std::vector<int> v4(4);
        v4[0] = 2;
        v4[1] = 3;
        v4[2] = 1;
        v4[3] = 4;
        std::vector<int> v5(4);
        v5[0] = 3;
        v5[1] = 4;
        v5[2] = 2;
        v5[3] = 1;
        std::vector<int> v6(4);
        v6[0] = 4;
        v6[1] = 3;
        v6[2] = 2;
        v6[3] = 1;
        c[0] = "Alan";
        c[1] = "Bob";
        c[2] = "Caspa";
        c[3] = "Don";
        b[0] = v1;
        b[1] = v2;
        b[2] = v3;
        b[3] = v4;
        b[4] = v5;
        b[5] = v6;
        find_winner(w, c, b);
        CPPUNIT_ASSERT(w.str() == "Bob\n");}

    void test_find_winner_3 () {
        std::ostringstream w;
        std::vector<std::string> c(1);
        std::vector<std::vector<int> > b(1);
        std::vector<int> v1(1);
        v1[0] = 1;
        c[0] = "Alice";
        b[0] = v1;
        find_winner(w, c, b);
        CPPUNIT_ASSERT(w.str() == "Alice\n");}


    // ---------
    // handle_IO
    // ---------

    void test_handle_IO_1 () {
        std::istringstream r("1\n\n2\nAlice\nZedd\n1 2\n2 1\n");
        std::ostringstream w;
        int i, j;
        std::vector<std::string> c;
        std::vector<std::vector<int> > b;
        handle_IO(r, w, i, j, c, b);
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 2);
        CPPUNIT_ASSERT(b[0].size() == 2);
        CPPUNIT_ASSERT(b[1].size() == 2);
        CPPUNIT_ASSERT(w.str() == "Alice\nZedd\n");}

    void test_handle_IO_2 () {
        std::istringstream r("1\n\n4\nAlan\nBob\nCaspa\nDon\n1 2 3 4\n1 2 3 4\n2 1 3 4\n2 1 3 4\n3 4 1 2\n");
        std::ostringstream w;
        int i, j;
        std::vector<std::string> c;
        std::vector<std::vector<int> > b;
        handle_IO(r, w, i, j, c, b);
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 4);
        CPPUNIT_ASSERT(b[0].size() == 4);
        CPPUNIT_ASSERT(b[1].size() == 4);
        CPPUNIT_ASSERT(w.str() == "Alan\n");}

    void test_handle_IO_3 () {
        std::istringstream r("1\n\n1\nJoe\n1 1 1 1\n");
        std::ostringstream w;
        int i, j;
        std::vector<std::string> c;
        std::vector<std::vector<int> > b;
        handle_IO(r, w, i, j, c, b);
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 1);
        CPPUNIT_ASSERT(b[0].size() == 4);
        CPPUNIT_ASSERT(w.str() == "Joe\n");}


    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1\n\n2\nAlice\nZedd\n1 2\n2 1\n");
        std::ostringstream w;
        solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Alice\nZedd\n");}

    void test_solve_2 () {
        std::istringstream r("2\n\n2\nAlan\nBob\n1 1 1 1\n2 2 2 2\n\n1\nAlan\n1 1 1 1\n");
        std::ostringstream w;
        solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Alan\nBob\n\nAlan\n");}

    void test_solve_3 () {
        std::istringstream r("1\n\n8\nAlan\nBob\nCaspa\nDon\nEoto\nFlux\nGovinda\nHeyoka\n3 6 1 2 8 7 5 4\n8 7 2 6 4 1 5 3\n3 4 1 2 6 5 8 7\n1 2 7 3 6 8 4 5\n");
        std::ostringstream w;
        solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Caspa\n");}


    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);

    CPPUNIT_TEST(test_is_loser_1);
    CPPUNIT_TEST(test_is_loser_2);
    CPPUNIT_TEST(test_is_loser_3);

    CPPUNIT_TEST(test_print_winners_1);
    CPPUNIT_TEST(test_print_winners_2);
    CPPUNIT_TEST(test_print_winners_3);

    CPPUNIT_TEST(test_find_winner_1);
    CPPUNIT_TEST(test_find_winner_2);
    CPPUNIT_TEST(test_find_winner_3);

    CPPUNIT_TEST(test_handle_IO_1);
    CPPUNIT_TEST(test_handle_IO_2);
    CPPUNIT_TEST(test_handle_IO_3);

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
    return 0;
}
