// --------------------------------
// TestVoting 
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
#include <sstream> // istringtstream, ostringstream
#include <string> // ==
#include <vector>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "Voting.h"

using namespace std;

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_1 () {
        istringstream r("\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        vector<string> candidates;
        vector<Ballot> ballots;
        int numBal = 0;
        const int numc = 3;
        voting_read(r, candidates, numc, ballots, numBal);
        CPPUNIT_ASSERT(numBal > 0);
        CPPUNIT_ASSERT(numBal == 5);
        CPPUNIT_ASSERT(&ballots[0] != NULL);
        CPPUNIT_ASSERT(ballots[0].votes[0] == 1);
        CPPUNIT_ASSERT(ballots[0].votes[1] == 2);
        CPPUNIT_ASSERT(ballots[0].votes[2] == 3);
    }

    void test_read_2 () {
        istringstream r("");
        vector<string> candidates;
        vector<Ballot> ballots;
        int numBal = 0;
        const int numc = 0;
        voting_read(r, candidates, numc, ballots, numBal);
        CPPUNIT_ASSERT(numBal == 0);
    }

    void test_read_3 () {
        istringstream r("\nJohn Doe\n1\n1\n1\n");
        vector<string> candidates;
        vector<Ballot> ballots;
        int numBal = 0;
        const int numc = 1;
        voting_read(r, candidates, numc, ballots, numBal);
        CPPUNIT_ASSERT(numBal > 0);
        CPPUNIT_ASSERT(numBal == 3);
	CPPUNIT_ASSERT(&ballots[0] != NULL);
        CPPUNIT_ASSERT(ballots[0].votes[0] == 1);
        CPPUNIT_ASSERT(ballots[1].votes[0] == 1);
        CPPUNIT_ASSERT(ballots[2].votes[0] == 1);
    }

    // ----
    // eval 
    // ----

    void test_eval_1 () {
        istringstream r("\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        vector<string> candidates;
        vector<Ballot> bs;
        int numBal = 0;
        const int numc = 3;
        voting_read(r, candidates, numc, bs, numBal);
        
        int winners[20];
        int wins = 0;   
        voting_eval(numc, bs, 5, winners, wins);
        CPPUNIT_ASSERT(wins == 1);
        CPPUNIT_ASSERT(winners[0] == 0);
    }

    void test_eval_2 () {
        istringstream r("\nJohn Doe\n1\n1\n1");
        vector<string> candidates;
        vector<Ballot> bs;
        int numBal = 0;
        const int numc = 1;
        voting_read(r, candidates, numc, bs, numBal);
        
        int winners[20];
        int wins = 0;   
        voting_eval(numc, bs, 3, winners, wins);
        CPPUNIT_ASSERT(wins == 1);
        CPPUNIT_ASSERT(winners[0] == 0);
    }

    void test_eval_3 () {
        istringstream r("\nred\ngreen\nblue\nyellow\n");
        vector<string> candidates;
        vector<Ballot> bs;
        int numBal = 0;
        const int numc = 4;
        voting_read(r, candidates, numc, bs, numBal);
        
        int winners[20];
        int wins = 0;   
        voting_eval(numc, bs, 0, winners, wins);
        CPPUNIT_ASSERT(wins == 4);
        CPPUNIT_ASSERT(winners[0] == 0);
        CPPUNIT_ASSERT(winners[1] == 1);
        CPPUNIT_ASSERT(winners[2] == 2);
        CPPUNIT_ASSERT(winners[3] == 3);
    }

    // -----
    // print
    // -----

    void test_print_1 () {
        ostringstream w;
        vector<string> candidates {"John Doe", "Jane Smith", "Sirhan Sirhan"};
        int winners[] = {0, 2};
        voting_print(w, candidates, winners, 2);
        CPPUNIT_ASSERT(w.str() != "John Doe\nSirhan Sirhan");
        CPPUNIT_ASSERT(w.str() == "John Doe\nSirhan Sirhan\n");
    }

    void test_print_2 () {
        ostringstream w;
        vector<string> candidates;
        int winners[20];
        voting_print(w, candidates, winners, 0);
        CPPUNIT_ASSERT(w.str().length() == 0);
    }

    void test_print_3 () {
        ostringstream w;
        vector<string> candidates {"John Doe"};
        int winners[] = {0};
        voting_print(w, candidates, winners, 1);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
    }



    // -----
    // solve
    // -----

    void test_solve_1 () {
        istringstream r("2\n\n1\nJohn Doe\n1\n\n3\nJane Smith\nJohn Doe\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n\nJane Smith\n");
    }
   
    void test_solve_2 () {
        istringstream r("1\n\n1\nJohn Doe\n1\n1\n1\n1\n");
        ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
    }

    void test_solve_3 () {
        istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
    }
  
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
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
