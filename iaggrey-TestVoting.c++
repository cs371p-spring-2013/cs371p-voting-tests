/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting.c++.app -lcppunit -ldl
    % valgrind TestVoting.c++.app >& TestVoting.c++.out
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
        string input = "1\n";
        input += "\n";
        input += "3\n";
        input += "John Doe\n";
        input += "Jane Smith\n";
        input += "Sirhan Sirhan\n";
        input += "1 2 3\n";
        input += "2 1 3\n";
        input += "2 3 1\n";
        input += "1 2 3\n";
        input += "3 1 2\n";

        std::istringstream r(input);

        int num_cases;
        vector<int> num_candidates;
        vector<int> num_ballots;
        vector<vector<string>> names;
        vector<vector<vector<int> > > ballots;

        const bool b = voting_read(r, num_cases, num_candidates, num_ballots, names, ballots);

        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(num_cases == 1);
        CPPUNIT_ASSERT(num_candidates[0] == 3);
        CPPUNIT_ASSERT(names[0][0] == "John Doe");
        CPPUNIT_ASSERT(names[0][1] == "Jane Smith");
        CPPUNIT_ASSERT(names[0][2] == "Sirhan Sirhan");
        CPPUNIT_ASSERT(ballots[0][0][0] == 1);
        CPPUNIT_ASSERT(ballots[0][0][1] == 2);
        CPPUNIT_ASSERT(ballots[0][0][2] == 3);
        CPPUNIT_ASSERT(ballots[0][1][0] == 2);
        CPPUNIT_ASSERT(ballots[0][1][1] == 1);
        CPPUNIT_ASSERT(ballots[0][1][2] == 3);
        CPPUNIT_ASSERT(ballots[0][2][0] == 2);
        CPPUNIT_ASSERT(ballots[0][2][1] == 3);
        CPPUNIT_ASSERT(ballots[0][2][2] == 1);
        CPPUNIT_ASSERT(ballots[0][3][0] == 1);
        CPPUNIT_ASSERT(ballots[0][3][1] == 2);
        CPPUNIT_ASSERT(ballots[0][3][2] == 3);
        CPPUNIT_ASSERT(ballots[0][4][0] == 3);
        CPPUNIT_ASSERT(ballots[0][4][1] == 1);
        CPPUNIT_ASSERT(ballots[0][4][2] == 2);
    }

    void test_read_2 () {
        string input = "2\n";
        input += "\n";
        input += "3\n";
        input += "John Doe\n";
        input += "Jane Smith\n";
        input += "Sirhan Sirhan\n";
        input += "1 2 3\n";
        input += "2 1 3\n";
        input += "2 3 1\n";
        input += "1 2 3\n";
        input += "3 1 2\n";
        input += "\n";
        input += "3\n";
        input += "John Doe\n";
        input += "Jane Smith\n";
        input += "Sirhan Sirhan\n";
        input += "1 2 3\n";
        input += "2 1 3\n";
        input += "2 3 1\n";
        input += "1 2 3\n";

        std::istringstream r(input);

        int num_cases;
        vector<int> num_candidates;
        vector<int> num_ballots;
        vector<vector<string>> names;
        vector<vector<vector<int> > > ballots;

        const bool b = voting_read(r, num_cases, num_candidates, num_ballots, names, ballots);

        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(num_cases == 2);
        CPPUNIT_ASSERT(num_candidates[0] == 3);
        CPPUNIT_ASSERT(num_candidates[1] == 3);
        CPPUNIT_ASSERT(names[0][0] == "John Doe");
        CPPUNIT_ASSERT(names[0][1] == "Jane Smith");
        CPPUNIT_ASSERT(names[0][2] == "Sirhan Sirhan");
        CPPUNIT_ASSERT(names[1][0] == "John Doe");
        CPPUNIT_ASSERT(names[1][1] == "Jane Smith");
        CPPUNIT_ASSERT(names[1][2] == "Sirhan Sirhan");
        CPPUNIT_ASSERT(ballots[0][0][0] == 1);
        CPPUNIT_ASSERT(ballots[0][0][1] == 2);
        CPPUNIT_ASSERT(ballots[0][0][2] == 3);
        CPPUNIT_ASSERT(ballots[0][1][0] == 2);
        CPPUNIT_ASSERT(ballots[0][1][1] == 1);
        CPPUNIT_ASSERT(ballots[0][1][2] == 3);
        CPPUNIT_ASSERT(ballots[0][2][0] == 2);
        CPPUNIT_ASSERT(ballots[0][2][1] == 3);
        CPPUNIT_ASSERT(ballots[0][2][2] == 1);
        CPPUNIT_ASSERT(ballots[0][3][0] == 1);
        CPPUNIT_ASSERT(ballots[0][3][1] == 2);
        CPPUNIT_ASSERT(ballots[0][3][2] == 3);
        CPPUNIT_ASSERT(ballots[0][4][0] == 3);
        CPPUNIT_ASSERT(ballots[0][4][1] == 1);
        CPPUNIT_ASSERT(ballots[0][4][2] == 2);
        CPPUNIT_ASSERT(ballots[1][0][0] == 1);
        CPPUNIT_ASSERT(ballots[1][0][1] == 2);
        CPPUNIT_ASSERT(ballots[1][0][2] == 3);
        CPPUNIT_ASSERT(ballots[1][1][0] == 2);
        CPPUNIT_ASSERT(ballots[1][1][1] == 1);
        CPPUNIT_ASSERT(ballots[1][1][2] == 3);
        CPPUNIT_ASSERT(ballots[1][2][0] == 2);
        CPPUNIT_ASSERT(ballots[1][2][1] == 3);
        CPPUNIT_ASSERT(ballots[1][2][2] == 1);
        CPPUNIT_ASSERT(ballots[1][3][0] == 1);
        CPPUNIT_ASSERT(ballots[1][3][1] == 2);
        CPPUNIT_ASSERT(ballots[1][3][2] == 3);
    }

    void test_read_3 () {
        string input = "3\n";
        input += "\n";
        input += "3\n";
        input += "John Doe\n";
        input += "Jane Smith\n";
        input += "Sirhan Sirhan\n";
        input += "1 2 3\n";
        input += "2 1 3\n";
        input += "2 3 1\n";
        input += "1 2 3\n";
        input += "3 1 2\n";
        input += "\n";
        input += "3\n";
        input += "John Doe\n";
        input += "Jane Smith\n";
        input += "Sirhan Sirhan\n";
        input += "1 2 3\n";
        input += "2 1 3\n";
        input += "2 3 1\n";
        input += "1 2 3\n";
        input += "\n";
        input += "2\n";
        input += "John Doe\n";
        input += "Jane Smith\n";
        input += "1 2\n";
        input += "2 1\n";
        input += "2 1\n";
        input += "1 2\n";
        input += "1 2\n";
        input += "2 1\n";
        input += "2 1\n";
        input += "1 2\n";
        input += "1 2\n";
        input += "1 2\n";

        std::istringstream r(input);

        int num_cases;
        vector<int> num_candidates;
        vector<int> num_ballots;
        vector<vector<string>> names;
        vector<vector<vector<int> > > ballots;

        const bool b = voting_read(r, num_cases, num_candidates, num_ballots, names, ballots);

        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(num_cases == 3);
        CPPUNIT_ASSERT(num_candidates[0] == 3);
        CPPUNIT_ASSERT(num_candidates[1] == 3);
        CPPUNIT_ASSERT(names[0][0] == "John Doe");
        CPPUNIT_ASSERT(names[0][1] == "Jane Smith");
        CPPUNIT_ASSERT(names[0][2] == "Sirhan Sirhan");
        CPPUNIT_ASSERT(names[1][0] == "John Doe");
        CPPUNIT_ASSERT(names[1][1] == "Jane Smith");
        CPPUNIT_ASSERT(names[1][2] == "Sirhan Sirhan");
        CPPUNIT_ASSERT(names[2][0] == "John Doe");
        CPPUNIT_ASSERT(names[2][1] == "Jane Smith");
        CPPUNIT_ASSERT(ballots[0][0][0] == 1);
        CPPUNIT_ASSERT(ballots[0][0][1] == 2);
        CPPUNIT_ASSERT(ballots[0][0][2] == 3);
        CPPUNIT_ASSERT(ballots[0][1][0] == 2);
        CPPUNIT_ASSERT(ballots[0][1][1] == 1);
        CPPUNIT_ASSERT(ballots[0][1][2] == 3);
        CPPUNIT_ASSERT(ballots[0][2][0] == 2);
        CPPUNIT_ASSERT(ballots[0][2][1] == 3);
        CPPUNIT_ASSERT(ballots[0][2][2] == 1);
        CPPUNIT_ASSERT(ballots[0][3][0] == 1);
        CPPUNIT_ASSERT(ballots[0][3][1] == 2);
        CPPUNIT_ASSERT(ballots[0][3][2] == 3);
        CPPUNIT_ASSERT(ballots[0][4][0] == 3);
        CPPUNIT_ASSERT(ballots[0][4][1] == 1);
        CPPUNIT_ASSERT(ballots[0][4][2] == 2);
        CPPUNIT_ASSERT(ballots[1][0][0] == 1);
        CPPUNIT_ASSERT(ballots[1][0][1] == 2);
        CPPUNIT_ASSERT(ballots[1][0][2] == 3);
        CPPUNIT_ASSERT(ballots[1][1][0] == 2);
        CPPUNIT_ASSERT(ballots[1][1][1] == 1);
        CPPUNIT_ASSERT(ballots[1][1][2] == 3);
        CPPUNIT_ASSERT(ballots[1][2][0] == 2);
        CPPUNIT_ASSERT(ballots[1][2][1] == 3);
        CPPUNIT_ASSERT(ballots[1][2][2] == 1);
        CPPUNIT_ASSERT(ballots[1][3][0] == 1);
        CPPUNIT_ASSERT(ballots[1][3][1] == 2);
        CPPUNIT_ASSERT(ballots[1][3][2] == 3);
        CPPUNIT_ASSERT(ballots[2][0][0] == 1);
        CPPUNIT_ASSERT(ballots[2][0][1] == 2);
        CPPUNIT_ASSERT(ballots[2][1][0] == 2);
        CPPUNIT_ASSERT(ballots[2][1][1] == 1);
        CPPUNIT_ASSERT(ballots[2][2][0] == 2);
        CPPUNIT_ASSERT(ballots[2][2][1] == 1);
        CPPUNIT_ASSERT(ballots[2][3][0] == 1);
        CPPUNIT_ASSERT(ballots[2][3][1] == 2);
        CPPUNIT_ASSERT(ballots[2][4][0] == 1);
        CPPUNIT_ASSERT(ballots[2][4][1] == 2);
        CPPUNIT_ASSERT(ballots[2][5][0] == 2);
        CPPUNIT_ASSERT(ballots[2][5][1] == 1);
        CPPUNIT_ASSERT(ballots[2][6][0] == 2);
        CPPUNIT_ASSERT(ballots[2][6][1] == 1);
        CPPUNIT_ASSERT(ballots[2][7][0] == 1);
        CPPUNIT_ASSERT(ballots[2][7][1] == 2);
        CPPUNIT_ASSERT(ballots[2][8][0] == 1);
        CPPUNIT_ASSERT(ballots[2][8][1] == 2);
        CPPUNIT_ASSERT(ballots[2][9][0] == 1);
        CPPUNIT_ASSERT(ballots[2][9][1] == 2);
    }

    // ----
    // eval
    // ----

    void test_eval_single_winner () {
        int ballots[1000][20] = {
            {1, 2, 3},
            {2, 1, 3},
            {2, 3, 1},
            {1, 2, 3},
            {3, 1, 2}};
        int winners[20] = {0};
        voting_eval(ballots, 5, 3, winners);

        CPPUNIT_ASSERT(winners[0] == 1);
        for(int i = 1; i < 20; ++i){ 
          CPPUNIT_ASSERT(winners[i] == 0);
        }
    };

    void test_eval_tie () {
        int ballots[1000][20] = {
            {1, 2, 3},
            {2, 1, 3},
            {2, 3, 1},
            {1, 2, 3}};
        int winners[20] = {0};
        voting_eval(ballots, 4, 3, winners);
        
        CPPUNIT_ASSERT(winners[0] == 1);
        CPPUNIT_ASSERT(winners[1] == 2);
        for(int i = 2; i < 20; ++i){
          CPPUNIT_ASSERT(winners[i] == 0);
        }
    };

    void test_eval_single_winner_2 () {
        int ballots[1000][20] = {
            {1, 2, 3, 4},
            {1, 2, 3, 4},
            {1, 2, 3, 4},
            {1, 2, 3, 4},
            {2, 1, 3, 4},
            {2, 3, 4, 1},
            {3, 2, 4, 1},
            {3, 4, 1, 2},
            {4, 2, 3, 1},
            {4, 2, 3, 1},
            {4, 2, 3, 1},
            {4, 2, 3, 1}};
        int winners[20] = {0};
        voting_eval(ballots, 13, 4, winners);
        
        CPPUNIT_ASSERT(winners[0] == 4);
        for(int i = 1; i < 20; ++i){ 
          CPPUNIT_ASSERT(winners[i] == 0);
        }
    };

     void test_eval_tie_2 () {
        int ballots[1000][20] = {
            {1, 2, 3, 4},
            {1, 2, 3, 4},
            {1, 2, 3, 4},
            {1, 2, 3, 4},
            {2, 1, 3, 4},
            {2, 3, 1, 4},
            {3, 2, 4, 1},
            {3, 4, 1, 2},
            {4, 2, 3, 1},
            {4, 2, 3, 1},
            {4, 2, 3, 1},
            {4, 2, 3, 1}};
        int winners[20] = {0};
        voting_eval(ballots, 13, 4, winners);
        
        CPPUNIT_ASSERT(winners[0] == 1);
        CPPUNIT_ASSERT(winners[1] == 4);
        for(int i = 2; i < 20; ++i){ 
          CPPUNIT_ASSERT(winners[i] == 0);
        }
    };

    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        vector<string> winners = {"John Doe"};
        voting_print(w, winners);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}

    void test_print_2 () {
        std::ostringstream w;
        vector<string> winners = {"John Doe", "Jane Smith"};
        voting_print(w, winners);
        CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\n");}

    void test_print_3 () {
        std::ostringstream w;
        vector<string> winners = {"John Doe", "Jane Smith", "Sirhan Sirhan"};
        voting_print(w, winners);
        CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");}


    // -----
    // solve
    // -----
    void test_solve_1 () {
        string input = "1\n";
        input += "\n";
        input += "3\n";
        input += "John Doe\n";
        input += "Jane Smith\n";
        input += "Sirhan Sirhan\n";
        input += "1 2 3\n";
        input += "2 1 3\n";
        input += "2 3 1\n";
        input += "1 2 3\n";
        input += "3 1 2\n";
        std::istringstream r(input);
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}

    void test_solve_2 () {
        string input = "2\n";
        input += "\n";
        input += "3\n";
        input += "John Doe\n";
        input += "Jane Smith\n";
        input += "Sirhan Sirhan\n";
        input += "1 2 3\n";
        input += "2 1 3\n";
        input += "2 3 1\n";
        input += "1 2 3\n";
        input += "3 1 2\n";
        input += "\n";
        input += "3\n";
        input += "John Doe\n";
        input += "Jane Smith\n";
        input += "Sirhan Sirhan\n";
        input += "1 2 3\n";
        input += "2 1 3\n";
        input += "2 3 1\n";
        input += "1 2 3\n";
        std::istringstream r(input);
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n\nJohn Doe\nJane Smith\n");}

    void test_solve_3 () {
        string input = "3\n";
        input += "\n";
        input += "3\n";
        input += "John Doe\n";
        input += "Jane Smith\n";
        input += "Sirhan Sirhan\n";
        input += "1 2 3\n";
        input += "2 1 3\n";
        input += "2 3 1\n";
        input += "1 2 3\n";
        input += "3 1 2\n";
        input += "\n";
        input += "3\n";
        input += "John Doe\n";
        input += "Jane Smith\n";
        input += "Sirhan Sirhan\n";
        input += "1 2 3\n";
        input += "2 1 3\n";
        input += "2 3 1\n";
        input += "1 2 3\n";
        input += "\n";
        input += "2\n";
        input += "John Doe\n";
        input += "Jane Smith\n";
        input += "1 2\n";
        input += "2 1\n";
        input += "2 1\n";
        input += "1 2\n";
        input += "1 2\n";
        input += "2 1\n";
        input += "2 1\n";
        input += "1 2\n";
        input += "1 2\n";
        input += "1 2\n";
        std::istringstream r(input);
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n\nJohn Doe\nJane Smith\n\nJohn Doe\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_eval_single_winner);
    CPPUNIT_TEST(test_eval_tie);
    CPPUNIT_TEST(test_eval_single_winner_2);
    CPPUNIT_TEST(test_eval_tie_2);
    CPPUNIT_TEST(test_eval_tie);
    CPPUNIT_TEST(test_eval_single_winner_2);
    CPPUNIT_TEST(test_eval_tie);
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

// vim: ts=4 sts=4 sw=4
