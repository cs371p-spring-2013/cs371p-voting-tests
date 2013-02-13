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
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_1 () {
        std::istringstream r("2\nA\nB\n1 2\n1 2\n 2 1");
        std::vector<std::string> names;
        std::vector<std::vector<int> > ballots;

        const bool b = voting_read(r, names, ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(names.size() == 2);
        CPPUNIT_ASSERT(ballots.size() == 3);
        CPPUNIT_ASSERT(names[0] == "A");
        CPPUNIT_ASSERT(names[1] == "B");
    }

    void test_read_2() {
        std::istringstream r("1\nA\n1");
        std::vector<std::string> names;
        std::vector<std::vector<int> > ballots;

        const bool b = voting_read(r, names, ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(names.size() == 1);
        CPPUNIT_ASSERT(ballots.size() == 1);
        CPPUNIT_ASSERT(names[0] == "A");
    }

    void test_read_3() {
        std::istringstream r("5\nA\nB\nC\nD\nE\n1 2 3 4 5\n1 2 3 4 5\n 5 4 3 2 1");
        std::vector<std::string> names;
        std::vector<std::vector<int> > ballots;

        const bool b = voting_read(r, names, ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(names.size() == 5);
        CPPUNIT_ASSERT(ballots.size() == 3);
        CPPUNIT_ASSERT(names[0] == "A");
        CPPUNIT_ASSERT(names[1] == "B");
        CPPUNIT_ASSERT(names[2] == "C");
        CPPUNIT_ASSERT(names[3] == "D");
        CPPUNIT_ASSERT(names[4] == "E");

    }

    // ----
    // eval
    // ----

   void test_eval_1 () {
        std::vector<std::string> names;
        std::vector<std::vector<int> > ballots;

        names.push_back("John Doe");
        names.push_back("Jane Smith");
        names.push_back("Sirhan Sirhan");

        std::vector<int> b1 = {1, 2, 3};
        std::vector<int> b2 = {2, 1, 3};
        std::vector<int> b3 = {2, 3, 1};
        std::vector<int> b4 = {1, 2, 3};
        std::vector<int> b5 = {3, 1, 2};

        ballots = {b1, b2, b3, b4, b5};

        std::vector<int> winners = voting_eval(names, ballots);
        CPPUNIT_ASSERT(winners.size() == 1);
        CPPUNIT_ASSERT(winners[0] == 0);
     }

   void test_eval_2 () {
        std::vector<std::string> names;
        std::vector<std::vector<int> > ballots;

        names.push_back("A");
        names.push_back("B");

        std::vector<int> b1 = {1, 2};
        std::vector<int> b2 = {2, 1};
        std::vector<int> b3 = {2, 1};
        std::vector<int> b4 = {1, 2};

        ballots = {b1, b2, b3, b4};

        std::vector<int> winners = voting_eval(names, ballots);
        CPPUNIT_ASSERT(winners.size() == 2);
        CPPUNIT_ASSERT(winners[0] == 0);
        CPPUNIT_ASSERT(winners[1] == 1);
     }

   void test_eval_3 () {
        std::vector<std::string> names;
        std::vector<std::vector<int> > ballots;

        names.push_back("A");
        names.push_back("B");
        names.push_back("C");
        names.push_back("D");

        std::vector<int> b1 = {1, 2, 3, 4};
        std::vector<int> b2 = {2, 1, 3, 4};
        std::vector<int> b3 = {2, 3, 1, 4};
        std::vector<int> b4 = {1, 2, 3, 4};
        std::vector<int> b5 = {3, 1, 2, 4};
        std::vector<int> b6 = {1, 4, 2, 3};
        std::vector<int> b7 = {2, 1, 4, 3};
        std::vector<int> b8 = {3, 1, 2, 4};
        std::vector<int> b9 = {4, 3, 2, 1};

       ballots = {b1, b2, b3, b4, b5, b6, b7, b8, b9};

        std::vector<int> winners = voting_eval(names, ballots);
        CPPUNIT_ASSERT(winners.size() == 3);
        CPPUNIT_ASSERT(names[winners[0]] == "A");
        CPPUNIT_ASSERT(names[winners[1]] == "B");
        CPPUNIT_ASSERT(names[winners[2]] == "C");
     }

    //-------------
    // remove_front
    //-------------
    void test_remove_front_1() {
        std::vector<int> r = {0};
        remove_front(r);

        CPPUNIT_ASSERT(r.size() == 0);
    }

    void test_remove_front_2() {
        std::vector<int> r = {0, 1};
        remove_front(r);

        CPPUNIT_ASSERT(r.size() == 1);
        CPPUNIT_ASSERT(r[0] == 1);
    }

    void test_remove_front_3() {
        std::vector<int> r = {0, 1, 2, 3};
        remove_front(r);

        CPPUNIT_ASSERT(r.size() == 3);
        CPPUNIT_ASSERT(r[0] == 1);
        CPPUNIT_ASSERT(r[1] == 2);
        CPPUNIT_ASSERT(r[2] == 3);
    }

    //---------------------------
    // voting_find_winners_losers
    //---------------------------
    
    void test_voting_find_winners_losers_1() {
       //candidate index -> ballots for that candidate -> preferences
       std::vector<std::vector<std::vector<int>>> votes;
       std::vector<int> winners;
       std::vector<int> losers;
       
       std::vector<int> b1 = {1, 2, 3};
       std::vector<int> b2 = {1, 2, 3};
       std::vector<int> b3 = {2, 1, 3};
       std::vector<int> b4 = {2, 1, 3};
       std::vector<int> b5 = {3, 2, 1};
       std::vector<int> b6 = {3, 2, 1};
       std::vector<int> b7 = {3, 2, 1};
      
       std::vector<std::vector<int>> c1 = {b1, b2};
       std::vector<std::vector<int>> c2 = {b3, b4};
       std::vector<std::vector<int>> c3 = {b5, b6, b7};

       votes.push_back(c1);
       votes.push_back(c2);
       votes.push_back(c3);

       voting_find_winners_losers(votes, winners, losers, 7);
       CPPUNIT_ASSERT(winners.size() == 1);
       CPPUNIT_ASSERT(winners[0] == 2);
       CPPUNIT_ASSERT(losers.size() == 2);
       CPPUNIT_ASSERT(losers[0] == 0);
       CPPUNIT_ASSERT(losers[1] == 1);
    }
    
    void test_voting_find_winners_losers_2() {
       //candidate index -> ballots for that candidate -> preferences
       std::vector<std::vector<std::vector<int>>> votes;
       std::vector<int> winners;
       std::vector<int> losers;
       
       std::vector<int> b1 = {1, 2, 3};
       std::vector<int> b2 = {1, 2, 3};
       std::vector<int> b3 = {2, 1, 3};
       std::vector<int> b4 = {2, 1, 3};
       std::vector<int> b5 = {3, 2, 1};
       std::vector<int> b6 = {3, 2, 1};
       std::vector<int> b7 = {3, 2, 1};
       std::vector<int> b8 = {1, 2, 3};
       std::vector<int> b9 = {2, 1, 3};
      
       std::vector<std::vector<int>> c1 = {b1, b2, b8};
       std::vector<std::vector<int>> c2 = {b3, b4, b9};
       std::vector<std::vector<int>> c3 = {b5, b6, b7};

       votes.push_back(c1);
       votes.push_back(c2);
       votes.push_back(c3);

       voting_find_winners_losers(votes, winners, losers, 9);
       CPPUNIT_ASSERT(winners.size() == 3);
       CPPUNIT_ASSERT(winners[0] == 0);
       CPPUNIT_ASSERT(winners[1] == 1);
       CPPUNIT_ASSERT(winners[2] == 2);
       CPPUNIT_ASSERT(losers.size() == 3);
       CPPUNIT_ASSERT(losers[0] == 0);
       CPPUNIT_ASSERT(losers[1] == 1);
       CPPUNIT_ASSERT(losers[2] == 2);
    }
    
    void test_voting_find_winners_losers_3() {
       //candidate index -> ballots for that candidate -> preferences
       std::vector<std::vector<std::vector<int>>> votes;
       std::vector<int> winners;
       std::vector<int> losers;
       
       std::vector<int> b1 = {1, 2, 3};
       std::vector<int> b2 = {2, 1, 3};
       std::vector<int> b3 = {2, 1, 3};
       std::vector<int> b4 = {3, 2, 1};
       std::vector<int> b5 = {3, 2, 1};
       std::vector<int> b6 = {3, 2, 1};
      
       std::vector<std::vector<int>> c1 = {b1};
       std::vector<std::vector<int>> c2 = {b2, b3};
       std::vector<std::vector<int>> c3 = {b4, b5, b6};

       votes.push_back(c1);
       votes.push_back(c2);
       votes.push_back(c3);

       voting_find_winners_losers(votes, winners, losers, 7);
       CPPUNIT_ASSERT(winners.size() == 1);
       CPPUNIT_ASSERT(winners[0] == 2);
       CPPUNIT_ASSERT(losers.size() == 1);
       CPPUNIT_ASSERT(losers[0] == 0);
    }
    
    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        std::vector<std::string> names = {"A", "B", "C", "D", "E"};
        std::vector<int> winners = {0};
        voting_print(w, winners, names);
        CPPUNIT_ASSERT(w.str() == ("A\n"));}


    void test_print_2 () {
        std::ostringstream w;
        std::vector<std::string> names = {"A", "B", "C", "D", "E"};
        std::vector<int> winners = {0, 1, 2, 3, 4};
        voting_print(w, winners, names);
        CPPUNIT_ASSERT(w.str() == ("A\nB\nC\nD\nE\n"));}


    void test_print_3 () {
        std::ostringstream w;
        std::vector<std::string> names = {"A", "B", "C", "D", "E"};
        std::vector<int> winners = {0, 3};
        voting_print(w, winners, names);
        CPPUNIT_ASSERT(w.str() == ("A\nD\n"));}

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");} 
    
    void test_solve_2 () {
        std::istringstream r("2\n\n3\nA\nB\nC\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n2\nY\nZ\n1 2\n2 1\n1 2\n2 1");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "A\n\nY\nZ\n");} 
    
    void test_solve_3 () {
        std::istringstream r("1\n\n4\nA\nB\nC\nD\n1 2 3 4\n2 1 3 4\n3 1 2 4\n4 1 2 3\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "A\nB\nC\nD\n");} 
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
    CPPUNIT_TEST(test_remove_front_1);
    CPPUNIT_TEST(test_remove_front_2);
    CPPUNIT_TEST(test_remove_front_3);
    CPPUNIT_TEST(test_voting_find_winners_losers_1);
    CPPUNIT_TEST(test_voting_find_winners_losers_2);
    CPPUNIT_TEST(test_voting_find_winners_losers_3);
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
