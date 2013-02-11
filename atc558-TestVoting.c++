
// --------
// includes
// --------

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"

#include "Voting.h"

// ----------
// TestVoting
// ----------
struct TestVoting : CppUnit::TestFixture {

    // ------------
    // load_ballots
    // ------------

    void test_load_ballots_1() {
        std::istringstream r("1 2 3\n");
        std::vector<std::queue<std::queue<int>>> b(4);
        int n = voting_load_ballots(r, b);
        CPPUNIT_ASSERT(n == 1);
        CPPUNIT_ASSERT(b[1].front().front() == 1);
        b[1].front().pop();
        CPPUNIT_ASSERT(b[1].front().front() == 2);
        b[1].front().pop();
        CPPUNIT_ASSERT(b[1].front().front() == 3);
        b[1].front().pop();
        CPPUNIT_ASSERT(b[1].front().empty());
    } 

    void test_load_ballots_2() {
        std::istringstream r("\n");
        std::vector<std::queue<std::queue<int>>> b(4);
        int n = voting_load_ballots(r, b);
        CPPUNIT_ASSERT(n == 0);
        CPPUNIT_ASSERT(b[1].empty());
    } 

    void test_load_ballots_3() {
        std::istringstream r("1 2 3\n3 2 1\n2 1 3\n");
        std::vector<std::queue<std::queue<int>>> b(4);
        int n = voting_load_ballots(r, b);
        CPPUNIT_ASSERT(n == 3);
        CPPUNIT_ASSERT(b[1].front().front() == 1);
        CPPUNIT_ASSERT(b[2].front().front() == 2);
        CPPUNIT_ASSERT(b[3].front().front() == 3);
    } 

    void test_load_ballots_4() {
        std::istringstream r("1 2 3\n1 3 2\n2 1 3\n");
        std::vector<std::queue<std::queue<int>>> b(4);
        int n = voting_load_ballots(r, b);
        CPPUNIT_ASSERT(n == 3);
        CPPUNIT_ASSERT(b[1].front().front() == 1);
        CPPUNIT_ASSERT(b[2].front().front() == 2);
        CPPUNIT_ASSERT(b[3].empty());
        CPPUNIT_ASSERT(b[1].size() == 2);
    } 

    // -----------
    // find_winner
    // -----------
    void test_find_winner_1() {
        std::istringstream ballots("1 2 3\n2 1 3\n2 3 1\n1 2 3\n1 3 2\n");
        std::vector<std::string> n(4);
        n[1] = "John Smith";
        n[2] = "Sue Jones";
        n[3] = "Sirhan Sirhan";
        std::vector<std::queue<std::queue<int>>> b(4);
        int total = voting_load_ballots(ballots, b);
        std::ostringstream w;
        bool win = voting_find_winner(total/2, b, n, w);
        CPPUNIT_ASSERT(win == true);
        CPPUNIT_ASSERT(w.str() == "John Smith\n");
    }

    void test_find_winner_2() {
        std::istringstream ballots("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        std::vector<std::string> n(4);
        n[1] = "John Smith";
        n[2] = "Sue Jones";
        n[3] = "Sirhan Sirhan";
        std::vector<std::queue<std::queue<int>>> b(4);
        int total = voting_load_ballots(ballots, b);
        std::ostringstream w;
        bool win = voting_find_winner(total/2, b, n, w);
        CPPUNIT_ASSERT(win == false);
    }

    void test_find_winner_3() {
        std::istringstream ballots("1 2 3\n2 1 3\n2 3 1\n1 2 3\n");
        std::vector<std::string> n(4);
        n[1] = "John Smith";
        n[2] = "Sue Jones";
        std::vector<std::queue<std::queue<int>>> b(4);
        int total = voting_load_ballots(ballots, b);
        std::ostringstream w;
        bool win = voting_find_winner(total/2, b, n, w);
        CPPUNIT_ASSERT(win == true);
        CPPUNIT_ASSERT(w.str() == "John Smith\nSue Jones\n");
    }

    // --------------
    // reassign_loser
    // -------------
    void test_reassign_loser_1() {
        std::istringstream ballots("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        std::vector<std::queue<std::queue<int>>> b(4);
        std::vector<std::string> n(4);
        n[1] = "John Smith";
        n[2] = "Sue Jones";
        n[3] = "";
        int total = voting_load_ballots(ballots, b);
        CPPUNIT_ASSERT(b[1].size() == 2);
        voting_reassign_loser(b, n);
        CPPUNIT_ASSERT(b[1].size() == 3);
    }

    void test_reassign_loser_2() {
        std::istringstream ballots("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        std::vector<std::queue<std::queue<int>>> b(4);
        std::vector<std::string> n(4);
        n[1] = "John Smith";
        n[2] = "Sue Jones";
        n[3] = "Sirhan Sirhan";
        int total = voting_load_ballots(ballots, b);
        CPPUNIT_ASSERT(b[1].size() == 2);
        voting_reassign_loser(b, n);
        CPPUNIT_ASSERT(b[1].size() == 2);
    }

    void test_reassign_loser_3() {
        std::istringstream ballots("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        std::vector<std::queue<std::queue<int>>> b(4);
        std::vector<std::string> n(4);
        n[1] = "John Smith";
        n[2] = "";
        n[3] = "";
        int total = voting_load_ballots(ballots, b);
        CPPUNIT_ASSERT(b[1].size() == 2);
        voting_reassign_loser(b, n);
        CPPUNIT_ASSERT(b[1].size() == 5);
    }

    // -----------
    // handle_case
    // -----------

    void test_handle_case_1() {
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 \
                2 3\n2 1 3\n2 3 1\n1 2 3\n 3 1 2\n");
        std::ostringstream w;
        voting_handle_case(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
    }

    void test_handle_case_2() {
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 \
                2 3\n2 1 3\n2 3 1\n1 2 3\n1 3 2\n2 3 1\n");
        std::ostringstream w;
        voting_handle_case(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\n");
    }


    void test_handle_case_3() {
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n\n");
        std::ostringstream w;
        voting_handle_case(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");
    }

    // -----
    // solve
    // -----

    void test_solve_1() {
        std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan \
                Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n 3 1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
    }

    void test_solve_2() {
        std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan \
                Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n 3 1 2\n\n4\nJohn \
                Doe\nJane Smith\nSirhan Sirhan\nDark Horse\n1 2 3 4\n\
                2 4 3 1\n3 2 4 1\n4 1 2 3\n1 2 3 4\n4 1 2 3\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n\nDark Horse\n");
    }

    void test_solve_3() {
        std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan \
                Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n 3 1 2\n\n1\nJohn \
Unopposed\n1\n1\n1\n1\n1\n1\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n\nJohn Unopposed\n");
    }


    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_load_ballots_1);
    CPPUNIT_TEST(test_load_ballots_2);
    CPPUNIT_TEST(test_load_ballots_3);
    CPPUNIT_TEST(test_load_ballots_4);
    CPPUNIT_TEST(test_find_winner_1);
    CPPUNIT_TEST(test_find_winner_2);
    CPPUNIT_TEST(test_find_winner_3);
    CPPUNIT_TEST(test_reassign_loser_1);
    CPPUNIT_TEST(test_reassign_loser_2);
    CPPUNIT_TEST(test_reassign_loser_3);
    CPPUNIT_TEST(test_handle_case_1);
    CPPUNIT_TEST(test_handle_case_2);
    CPPUNIT_TEST(test_handle_case_3);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false);
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
