/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting -lcppunit -ldl
    % clang++ -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting -lcppunit -ldl
    % valgrind ./TestVoting >& TestVoting.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <vector>   // vector

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

using namespace std;

// ----------
// TestVoting
// ----------

struct TestVoting : CppUnit::TestFixture {

    // -----
    // solve
    // -----
    void test_solve_1 () {
        istringstream r("1\n\n1\nJohn Doe\n1\n");
        ostringstream w;
        voting_solve(r,w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
    }

    void test_solve_2 () {
        istringstream r("1\n\n2\nJohn Doe\nJane Smith\n1 2\n2 1\n");
        ostringstream w;
        voting_solve(r,w);
        CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\n");
    }


    void test_solve_3 () {
        istringstream r("2\n\n1\nJohn Doe\n1\n\n2\nJohn Doe\nJane Smith\n1 2\n2 1\n");
        ostringstream w;
        voting_solve(r,w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n\nJohn Doe\nJane Smith\n");
    }

    // ---------
    // read_name
    // ---------

    void test_read_name_1 () {
        vector<Candidate> candidate_store;
        string r = "John Doe";
        voting_read_name(r, candidate_store);
        CPPUNIT_ASSERT(candidate_store.size() == 1);
        CPPUNIT_ASSERT(candidate_store[0].name == "John Doe" && !candidate_store[0].is_eliminated);
    }

    void test_read_name_2 () {
        vector<Candidate> candidate_store;
        string r1 = "John Doe";
        voting_read_name(r1, candidate_store);
        string r2 = "Jane Smith";
        voting_read_name(r2, candidate_store);
        string r3 = "Sirhan Sirhan";
        voting_read_name(r3, candidate_store);
        CPPUNIT_ASSERT(candidate_store.size() == 3);
        CPPUNIT_ASSERT(candidate_store[0].name == "John Doe" && !candidate_store[0].is_eliminated);
        CPPUNIT_ASSERT(candidate_store[1].name == "Jane Smith" && !candidate_store[1].is_eliminated);
        CPPUNIT_ASSERT(candidate_store[2].name == "Sirhan Sirhan" && !candidate_store[2].is_eliminated);
    }

    void test_read_name_3 () {
        vector<Candidate> candidate_store;
        string r1 = "Red";
        voting_read_name(r1, candidate_store);
        string r2 = "Green";
        voting_read_name(r2, candidate_store);
        string r3 = "Blue";
        voting_read_name(r3, candidate_store);
        string r4 = "Orange";
        voting_read_name(r4, candidate_store);
        CPPUNIT_ASSERT(candidate_store.size() == 4);
        CPPUNIT_ASSERT(candidate_store[0].name == "Red" && !candidate_store[0].is_eliminated);
        CPPUNIT_ASSERT(candidate_store[1].name == "Green" && !candidate_store[1].is_eliminated);
        CPPUNIT_ASSERT(candidate_store[2].name == "Blue" && !candidate_store[2].is_eliminated);
        CPPUNIT_ASSERT(candidate_store[3].name == "Orange" && !candidate_store[3].is_eliminated);
    }

    // ------------
    // read_ballot
    // ------------

    void test_read_ballot_1 () {
        int num_candidates = 10;
        vector<vector<int> > ballot_store;
        string r = "7 10 1 6 8 3 5 2 4 9";
        voting_read_ballot(r, num_candidates, ballot_store);
        CPPUNIT_ASSERT(ballot_store.size() == 1 && ballot_store[0].size() == 10);
        CPPUNIT_ASSERT(ballot_store[0][0] == 6); 
        CPPUNIT_ASSERT(ballot_store[0][1] == 9);
	CPPUNIT_ASSERT(ballot_store[0][2] == 0); 
        CPPUNIT_ASSERT(ballot_store[0][3] == 5);
        CPPUNIT_ASSERT(ballot_store[0][4] == 7);
        CPPUNIT_ASSERT(ballot_store[0][5] == 2);
        CPPUNIT_ASSERT(ballot_store[0][6] == 4);
        CPPUNIT_ASSERT(ballot_store[0][7] == 1);
        CPPUNIT_ASSERT(ballot_store[0][8] == 3);
	CPPUNIT_ASSERT(ballot_store[0][9] == 8);
    }

    void test_read_ballot_2 () {
        int num_candidates = 1;
        vector<vector<int> > ballot_store;
        string r = "1";
        voting_read_ballot(r, num_candidates, ballot_store);
        CPPUNIT_ASSERT(ballot_store.size() == 1 && ballot_store[0].size() == 1);
        CPPUNIT_ASSERT(ballot_store[0][0] == 0);
    }

    void test_read_ballot_3 () {
        int num_candidates = 4;
        vector<vector<int> > ballot_store;
        string r1 = "1 2 3 4";
        voting_read_ballot(r1, num_candidates, ballot_store);
        string r2 = "2 1 3 4";
        voting_read_ballot(r2, num_candidates, ballot_store);
        string r3 = "2 3 1 4";
        voting_read_ballot(r3, num_candidates, ballot_store);
        string r4 = "1 2 3 4";
        voting_read_ballot(r4, num_candidates, ballot_store);
        string r5 = "3 4 1 2";
        voting_read_ballot(r5, num_candidates, ballot_store);
        string r6 = "4 3 2 1";
        voting_read_ballot(r6, num_candidates, ballot_store);
        CPPUNIT_ASSERT(ballot_store.size() == 6 && ballot_store[0].size() == 4 && ballot_store[1].size() == 4
                && ballot_store[2].size() == 4 && ballot_store[3].size() == 4 && ballot_store[4].size() == 4
                       && ballot_store[5].size() == 4);
        CPPUNIT_ASSERT(ballot_store[0][0] == 0 && ballot_store[0][1] == 1 && ballot_store[0][2] == 2 && ballot_store[0][3] == 3);
        CPPUNIT_ASSERT(ballot_store[1][0] == 1 && ballot_store[1][1] == 0 && ballot_store[1][2] == 2 && ballot_store[1][3] == 3);
        CPPUNIT_ASSERT(ballot_store[2][0] == 1 && ballot_store[2][1] == 2 && ballot_store[2][2] == 0 && ballot_store[2][3] == 3);
        CPPUNIT_ASSERT(ballot_store[3][0] == 0 && ballot_store[3][1] == 1 && ballot_store[3][2] == 2 && ballot_store[3][3] == 3);
        CPPUNIT_ASSERT(ballot_store[4][0] == 2 && ballot_store[4][1] == 3 && ballot_store[4][2] == 0 && ballot_store[4][3] == 1);
        CPPUNIT_ASSERT(ballot_store[5][0] == 3 && ballot_store[5][1] == 2 && ballot_store[5][2] == 1 && ballot_store[5][3] == 0);
    }

    // ----
    // eval
    // ----

    void test_eval_1 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        set<int> result_set = voting_eval(ballot_store, candidate_store);
        CPPUNIT_ASSERT(result_set.size() == 1 && result_set.find(0) != result_set.end());
    }

    void test_eval_2 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        struct Candidate c2;
        c2.name = "Jane Smith";
        c2.is_eliminated = false;
        candidate_store.push_back(c2);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot.push_back(1);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        set<int> result_set = voting_eval(ballot_store, candidate_store);
        CPPUNIT_ASSERT(result_set.size() == 2 && result_set.find(0) != result_set.end()
                                                              && result_set.find(1) != result_set.end());
    }

    void test_eval_3 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        struct Candidate c2;
        c2.name = "Jane Smith";
        c2.is_eliminated = false;
        candidate_store.push_back(c2);
        struct Candidate c3;
        c3.name = "Sirhan Sirhan";
        c3.is_eliminated = false;
        candidate_store.push_back(c3);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(0);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(2);
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(2);
        ballot.push_back(0);
        ballot.push_back(1);
        ballot_store.push_back(ballot);
        set<int> result_set = voting_eval(ballot_store, candidate_store);
        CPPUNIT_ASSERT(result_set.size() == 1 && result_set.find(0) != result_set.end());
    }

    // ----------------
    // allocate_ballots
    // ----------------

    void test_allocate_ballots_1 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        voting_allocate_ballots(ballot_store, candidate_store);
        CPPUNIT_ASSERT(candidate_store[0].my_ballots.size() == 1 && candidate_store[0].my_ballots[0] == 0);
    }

    void test_allocate_ballots_2 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        struct Candidate c2;
        c2.name = "Jane Smith";
        c2.is_eliminated = false;
        candidate_store.push_back(c2);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot.push_back(1);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        voting_allocate_ballots(ballot_store, candidate_store);
        CPPUNIT_ASSERT(candidate_store[0].my_ballots.size() == 1 && candidate_store[0].my_ballots[0] == 0);
        CPPUNIT_ASSERT(candidate_store[1].my_ballots.size() == 1 && candidate_store[1].my_ballots[0] == 1);
    }

    void test_allocate_ballots_3 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        struct Candidate c2;
        c2.name = "Jane Smith";
        c2.is_eliminated = false;
        candidate_store.push_back(c2);
        struct Candidate c3;
        c3.name = "Sirhan Sirhan";
        c3.is_eliminated = false;
        candidate_store.push_back(c3);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(0);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(2);
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(2);
        ballot.push_back(0);
        ballot.push_back(1);
        ballot_store.push_back(ballot);
        voting_allocate_ballots(ballot_store, candidate_store);
        CPPUNIT_ASSERT(candidate_store[0].my_ballots.size() == 2 && candidate_store[0].my_ballots[0] == 0
                           && candidate_store[0].my_ballots[1] == 3);
        CPPUNIT_ASSERT(candidate_store[1].my_ballots.size() == 2 && candidate_store[1].my_ballots[0] == 1
                           && candidate_store[1].my_ballots[1] == 2);
        CPPUNIT_ASSERT(candidate_store[2].my_ballots.size() == 1 && candidate_store[2].my_ballots[0] == 4);
    }

    // ------------------
    // find_single_winner
    // ------------------

    void test_find_single_winner_1 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        voting_allocate_ballots(ballot_store, candidate_store);
        CPPUNIT_ASSERT(voting_find_single_winner(1, candidate_store) == 0);
    }

    void test_find_single_winner_2 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        struct Candidate c2;
        c2.name = "Jane Smith";
        c2.is_eliminated = false;
        candidate_store.push_back(c2);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(1);
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        voting_allocate_ballots(ballot_store, candidate_store);
        CPPUNIT_ASSERT(voting_find_single_winner(2, candidate_store) == 1);
    }

    void test_find_single_winner_3 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        struct Candidate c2;
        c2.name = "Jane Smith";
        c2.is_eliminated = false;
        candidate_store.push_back(c2);
        struct Candidate c3;
        c3.name = "Sirhan Sirhan";
        c3.is_eliminated = false;
        candidate_store.push_back(c3);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(0);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(2);
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(2);
        ballot.push_back(0);
        ballot.push_back(1);
        ballot_store.push_back(ballot);
        voting_allocate_ballots(ballot_store, candidate_store);
        CPPUNIT_ASSERT(voting_find_single_winner(5, candidate_store) == -1);
    }

    // -----------
    // find_losers
    // -----------
    
    void test_find_losers_1 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        voting_allocate_ballots(ballot_store, candidate_store);
        set<int> loser_set;
        voting_find_losers(loser_set, candidate_store);
        CPPUNIT_ASSERT(loser_set.size() == 1 && loser_set.find(0) != loser_set.end());
    }

    void test_find_losers_2 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        struct Candidate c2;
        c2.name = "Jane Smith";
        c2.is_eliminated = false;
        candidate_store.push_back(c2);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot.push_back(1);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        voting_allocate_ballots(ballot_store, candidate_store);
        set<int> loser_set;
        voting_find_losers(loser_set, candidate_store);
        CPPUNIT_ASSERT(loser_set.size() == 2 && loser_set.find(0) != loser_set.end()
                                                              && loser_set.find(1) != loser_set.end());
    }

    void test_find_losers_3 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        struct Candidate c2;
        c2.name = "Jane Smith";
        c2.is_eliminated = false;
        candidate_store.push_back(c2);
        struct Candidate c3;
        c3.name = "Sirhan Sirhan";
        c3.is_eliminated = false;
        candidate_store.push_back(c3);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(0);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(2);
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(2);
        ballot.push_back(0);
        ballot.push_back(1);
        ballot_store.push_back(ballot);
        voting_allocate_ballots(ballot_store, candidate_store);
        set<int> loser_set;
        voting_find_losers(loser_set, candidate_store);
        CPPUNIT_ASSERT(loser_set.size() == 1 && loser_set.find(2) != loser_set.end());
    }

    // --------------------
    // eliminate_candidates
    // --------------------

    void test_eliminate_candidates_1 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        voting_allocate_ballots(ballot_store, candidate_store);
        set<int> loser_set;
        voting_find_losers(loser_set, candidate_store);
        voting_eliminate_candidates(loser_set, candidate_store);
        CPPUNIT_ASSERT(candidate_store[0].is_eliminated);
    }

    void test_eliminate_candidates_2 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        struct Candidate c2;
        c2.name = "Jane Smith";
        c2.is_eliminated = false;
        candidate_store.push_back(c2);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot.push_back(1);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        voting_allocate_ballots(ballot_store, candidate_store);
        set<int> loser_set;
        voting_find_losers(loser_set, candidate_store);
        voting_eliminate_candidates(loser_set, candidate_store);
        CPPUNIT_ASSERT(candidate_store[0].is_eliminated && candidate_store[1].is_eliminated);
    }

    void test_eliminate_candidates_3 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        struct Candidate c2;
        c2.name = "Jane Smith";
        c2.is_eliminated = false;
        candidate_store.push_back(c2);
        struct Candidate c3;
        c3.name = "Sirhan Sirhan";
        c3.is_eliminated = false;
        candidate_store.push_back(c3);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(0);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(2);
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(2);
        ballot.push_back(0);
        ballot.push_back(1);
        ballot_store.push_back(ballot);
        voting_allocate_ballots(ballot_store, candidate_store);
        set<int> loser_set;
        voting_find_losers(loser_set, candidate_store);
        voting_eliminate_candidates(loser_set, candidate_store);
        CPPUNIT_ASSERT(!candidate_store[0].is_eliminated && !candidate_store[1].is_eliminated
                                                                && candidate_store[2].is_eliminated);
    }

    // -----------------------
    // reassign_losing_ballots
    // -----------------------

    void test_reassign_losing_ballots_1 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "Red";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        struct Candidate c2;
        c2.name = "Green";
        c2.is_eliminated = false;
        candidate_store.push_back(c2);
        struct Candidate c3;
        c3.name = "Blue";
        c3.is_eliminated = false;
        candidate_store.push_back(c3);
        struct Candidate c4;
        c4.name = "Orange";
        c4.is_eliminated = false;
        candidate_store.push_back(c4);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot.push_back(3);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(0);
        ballot.push_back(2);
        ballot.push_back(3);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(2);
        ballot.push_back(0);
        ballot.push_back(3);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot.push_back(3);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(2);
        ballot.push_back(3);
        ballot.push_back(0);
        ballot.push_back(1);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(3);
        ballot.push_back(2);
        ballot.push_back(1);
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        voting_allocate_ballots(ballot_store, candidate_store);
        set<int> loser_set;
        voting_find_losers(loser_set, candidate_store);
        voting_eliminate_candidates(loser_set, candidate_store);
        voting_reassign_losing_ballots(ballot_store, candidate_store);
        CPPUNIT_ASSERT(candidate_store[0].my_ballots.size() == 3 && candidate_store[0].my_ballots[0] == 0
                           && candidate_store[0].my_ballots[1] == 3 && candidate_store[0].my_ballots[2] == 4);
        CPPUNIT_ASSERT(candidate_store[1].my_ballots.size() == 3 && candidate_store[1].my_ballots[0] == 1
                           && candidate_store[1].my_ballots[1] == 2 && candidate_store[1].my_ballots[2] == 5);
    }

    void test_reassign_losing_ballots_2 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        struct Candidate c2;
        c2.name = "Jane Smith";
        c2.is_eliminated = false;
        candidate_store.push_back(c2);
        struct Candidate c3;
        c3.name = "Sirhan Sirhan";
        c3.is_eliminated = false;
        candidate_store.push_back(c3);
        struct Candidate c4;
        c4.name = "George Bush";
        c4.is_eliminated = false;
        candidate_store.push_back(c4);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot.push_back(3);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(0);
        ballot.push_back(2);
        ballot.push_back(3);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(2);
        ballot.push_back(0);
        ballot.push_back(3);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot.push_back(3);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(2);
        ballot.push_back(3);
        ballot.push_back(0);
        ballot.push_back(1);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(3);
        ballot.push_back(2);
        ballot.push_back(0);
        ballot.push_back(1);
        ballot_store.push_back(ballot);
        voting_allocate_ballots(ballot_store, candidate_store);
        set<int> loser_set;
        voting_find_losers(loser_set, candidate_store);
        voting_eliminate_candidates(loser_set, candidate_store);
        voting_reassign_losing_ballots(ballot_store, candidate_store);
        CPPUNIT_ASSERT(candidate_store[0].my_ballots.size() == 4 && candidate_store[0].my_ballots[0] == 0
                           && candidate_store[0].my_ballots[1] == 3 && candidate_store[0].my_ballots[2] == 4
                                    && candidate_store[0].my_ballots[3] == 5);
        CPPUNIT_ASSERT(candidate_store[1].my_ballots.size() == 2 && candidate_store[1].my_ballots[0] == 1
                           && candidate_store[1].my_ballots[1] == 2);
    }

    void test_reassign_losing_ballots_3 () {
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        struct Candidate c2;
        c2.name = "Jane Smith";
        c2.is_eliminated = false;
        candidate_store.push_back(c2);
        struct Candidate c3;
        c3.name = "Sirhan Sirhan";
        c3.is_eliminated = false;
        candidate_store.push_back(c3);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(0);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(2);
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(2);
        ballot.push_back(0);
        ballot.push_back(1);
        ballot_store.push_back(ballot);
        voting_allocate_ballots(ballot_store, candidate_store);
        set<int> loser_set;
        voting_find_losers(loser_set, candidate_store);
        voting_eliminate_candidates(loser_set, candidate_store);
        voting_reassign_losing_ballots(ballot_store, candidate_store);
        CPPUNIT_ASSERT(candidate_store[0].my_ballots.size() == 3 && candidate_store[0].my_ballots[0] == 0
                           && candidate_store[0].my_ballots[1] == 3 && candidate_store[0].my_ballots[2] == 4);
        CPPUNIT_ASSERT(candidate_store[1].my_ballots.size() == 2 && candidate_store[1].my_ballots[0] == 1
                           && candidate_store[1].my_ballots[1] == 2);
    }

    // ------------------------
    // print_winning_candidates
    // ------------------------
    
    void test_print_winning_candidates_1 () {
        ostringstream w;
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        set<int> winners = voting_eval(ballot_store, candidate_store);
        voting_print_winning_candidates(w, winners, candidate_store);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
    }

    void test_print_winning_candidates_2 () {
        ostringstream w;
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        struct Candidate c2;
        c2.name = "Jane Smith";
        c2.is_eliminated = false;
        candidate_store.push_back(c2);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot.push_back(1);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        set<int> winners = voting_eval(ballot_store, candidate_store);
        voting_print_winning_candidates(w, winners, candidate_store);
        CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\n");
    }

    void test_print_winning_candidates_3 () {
        ostringstream w;
        vector<Candidate> candidate_store;
        struct Candidate c1;
        c1.name = "John Doe";
        c1.is_eliminated = false;
        candidate_store.push_back(c1);
        struct Candidate c2;
        c2.name = "Jane Smith";
        c2.is_eliminated = false;
        candidate_store.push_back(c2);
        struct Candidate c3;
        c3.name = "Sirhan Sirhan";
        c3.is_eliminated = false;
        candidate_store.push_back(c3);
        vector<vector<int> > ballot_store;
        vector<int> ballot;
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(0);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(2);
        ballot.push_back(0);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        ballot_store.push_back(ballot);
        ballot.clear();
        ballot.push_back(2);
        ballot.push_back(0);
        ballot.push_back(1);
        ballot_store.push_back(ballot);
        set<int> winners = voting_eval(ballot_store, candidate_store);
        voting_print_winning_candidates(w, winners, candidate_store);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_read_name_1);
    CPPUNIT_TEST(test_read_name_2);
    CPPUNIT_TEST(test_read_name_3);
    CPPUNIT_TEST(test_read_ballot_1);
    CPPUNIT_TEST(test_read_ballot_2);
    CPPUNIT_TEST(test_read_ballot_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_allocate_ballots_1);
    CPPUNIT_TEST(test_allocate_ballots_2);
    CPPUNIT_TEST(test_allocate_ballots_3);
    CPPUNIT_TEST(test_find_single_winner_1);
    CPPUNIT_TEST(test_find_single_winner_2);
    CPPUNIT_TEST(test_find_single_winner_3);
    CPPUNIT_TEST(test_find_losers_1);
    CPPUNIT_TEST(test_find_losers_2);
    CPPUNIT_TEST(test_find_losers_3);
    CPPUNIT_TEST(test_eliminate_candidates_1);
    CPPUNIT_TEST(test_eliminate_candidates_2);
    CPPUNIT_TEST(test_eliminate_candidates_3);
    CPPUNIT_TEST(test_reassign_losing_ballots_1);
    CPPUNIT_TEST(test_reassign_losing_ballots_2);
    CPPUNIT_TEST(test_reassign_losing_ballots_3);
    CPPUNIT_TEST(test_print_winning_candidates_1);
    CPPUNIT_TEST(test_print_winning_candidates_2);
    CPPUNIT_TEST(test_print_winning_candidates_3);
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

