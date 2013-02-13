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
    % g++ -lcppunit -ldl -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting.c++.app
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
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <vector>

using namespace std;

typedef vector<vector<queue<int>>> CandBallotMap;
typedef vector<string> NumCandNameMap;
typedef vector<int> VotesForMap;

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {

    // ----------------
    // voting_get_cands
    // ----------------

    void test_voting_get_cands_1 () {
        std::istringstream r("Name1\nName2\n1 2\n2 1\n");

        NumCandNameMap cand_number_name;
        int num_cands = 2;

        cand_number_name.push_back("");
        
        voting_get_cands(r, cand_number_name, num_cands);
        CPPUNIT_ASSERT((int)cand_number_name.size() ==   3);
    }
    
    void test_voting_get_cands_2 () {
        std::istringstream r("Name1\nName2\nName 3\n");

        NumCandNameMap cand_number_name;
        int num_cands = 3;

        cand_number_name.push_back("");
        
        voting_get_cands(r, cand_number_name, num_cands);
        CPPUNIT_ASSERT((int)cand_number_name.size() ==   4);
    }
    
    void test_voting_get_cands_3 () {
        std::istringstream r("Name1\n");

        NumCandNameMap cand_number_name;
        int num_cands = 1;

        cand_number_name.push_back("");
        
        voting_get_cands(r, cand_number_name, num_cands);
        CPPUNIT_ASSERT((int)cand_number_name.size() == 2);
    }
    
    // -------------------
    // voting_read_ballots
    // -------------------

    void test_voting_read_ballots_1 () {
        istringstream r("1 2\n2 1");
        
        CandBallotMap cand_ballot_map;
        VotesForMap votes;
        
        vector<queue<int>> empty;
        cand_ballot_map.push_back(empty);
        cand_ballot_map.push_back(empty);
        cand_ballot_map.push_back(empty);
        votes.push_back(0);
        votes.push_back(0);
        votes.push_back(0);
        
        const int ballots = voting_read_ballots(r, cand_ballot_map, 2, votes);
        CPPUNIT_ASSERT(ballots == 2);
        CPPUNIT_ASSERT((int)cand_ballot_map[1].size() == 1);
    }
    
    void test_voting_read_ballots_2 () {
        istringstream r("1 2\n");
        
        CandBallotMap cand_ballot_map;
        VotesForMap votes;
        
        vector<queue<int>> empty;
        cand_ballot_map.push_back(empty);
        cand_ballot_map.push_back(empty);
        cand_ballot_map.push_back(empty);
        votes.push_back(0);
        votes.push_back(0);
        votes.push_back(0);
        
        const int ballots = voting_read_ballots(r, cand_ballot_map, 2, votes);
        CPPUNIT_ASSERT(ballots == 1);
        CPPUNIT_ASSERT((int)cand_ballot_map[1].size() == 1);
    }
    
    void test_voting_read_ballots_3 () {
        istringstream r("1 2 3 4\n1 2 3 4\n1 2 3 4\n1 2 3 4\n");
        
        CandBallotMap cand_ballot_map;
        VotesForMap votes;
        
        vector<queue<int>> empty;
        cand_ballot_map.push_back(empty);
        cand_ballot_map.push_back(empty);
        cand_ballot_map.push_back(empty);
        cand_ballot_map.push_back(empty);
        cand_ballot_map.push_back(empty);
        votes.push_back(0);
        votes.push_back(0);
        votes.push_back(0);
        votes.push_back(0);
        votes.push_back(0);
        
        const int ballots = voting_read_ballots(r, cand_ballot_map, 4, votes);
        CPPUNIT_ASSERT(ballots == 4);
        CPPUNIT_ASSERT((int)cand_ballot_map[1].size() == 4);
    }
    
    // -----------
    // voting_read
    // -----------

    void test_voting_read_1 () {
        istringstream r("2\nName 1\nName 2\n1 2");
        
        CandBallotMap cand_ballot_map;
        NumCandNameMap name_map;
        VotesForMap votes;
        
        vector<queue<int>> empty;
        cand_ballot_map.push_back(empty);
        name_map.push_back("");
        votes.push_back(0);
        
        const int ballots = voting_read(r, cand_ballot_map, name_map, votes);
        CPPUNIT_ASSERT(ballots == 1);
        CPPUNIT_ASSERT((int)cand_ballot_map[1].size() == 1);
        CPPUNIT_ASSERT((int)name_map.size() == 3);
        CPPUNIT_ASSERT((int)votes.size() == 3);
    }
    
    void test_voting_read_2 () {
        istringstream r("2\nName 1\nName 2\n1 2\n1 2\n2 1");
        
        CandBallotMap cand_ballot_map;
        NumCandNameMap name_map;
        VotesForMap votes;
        
        vector<queue<int>> empty;
        cand_ballot_map.push_back(empty);
        name_map.push_back("");
        votes.push_back(0);
        
        const int ballots = voting_read(r, cand_ballot_map, name_map, votes);
        CPPUNIT_ASSERT(ballots == 3);
        CPPUNIT_ASSERT((int)cand_ballot_map[1].size() == 2);
        CPPUNIT_ASSERT((int)name_map.size() == 3);
        CPPUNIT_ASSERT((int)votes.size() == 3);
    }
    
    void test_voting_read_3 () {
        istringstream r("4\nName 1\nName 2\nName 3\nName 4\n1 2 3 4\n1 2 3 4\n1 2 3 4");
        
        CandBallotMap cand_ballot_map;
        NumCandNameMap name_map;
        VotesForMap votes;
        
        vector<queue<int>> empty;
        cand_ballot_map.push_back(empty);
        name_map.push_back("");
        votes.push_back(0);
        
        const int ballots = voting_read(r, cand_ballot_map, name_map, votes);
        CPPUNIT_ASSERT(ballots == 3);
        CPPUNIT_ASSERT((int)cand_ballot_map[1].size() == 3);
        CPPUNIT_ASSERT((int)name_map.size() == 5);
        CPPUNIT_ASSERT((int)votes.size() == 5);
        CPPUNIT_ASSERT((int)votes[1] == 3);
    }
    
    // ------------------
    // voting_find_winner
    // ------------------
    void test_voting_find_winners_1 () {
        int num_ballots = 2;
        VotesForMap votes;
        bool is_winner;
        
        votes.push_back(0);
        votes.push_back(2);
        votes.push_back(0);
        
        vector<int> winner = voting_find_winners(num_ballots, votes, is_winner);
        CPPUNIT_ASSERT(is_winner == true);
        CPPUNIT_ASSERT((int)winner.size() == 1);
        CPPUNIT_ASSERT(winner[0] = 1);
    }
    
    void test_voting_find_winners_2 () {
        int num_ballots = 4;
        VotesForMap votes;
        bool is_winner;
        
        votes.push_back(0);
        votes.push_back(2);
        votes.push_back(2);
        
        vector<int> winner = voting_find_winners(num_ballots, votes, is_winner);
        CPPUNIT_ASSERT(is_winner == true);
        CPPUNIT_ASSERT((int)winner.size() == 2);
        CPPUNIT_ASSERT(winner[0] = 1);
        CPPUNIT_ASSERT(winner[1] = 2);
    }
    
    void test_voting_find_winners_3 () {
        int num_ballots = 4;
        VotesForMap votes;
        bool is_winner;
        
        votes.push_back(0);
        votes.push_back(2);
        votes.push_back(1);
        votes.push_back(1);
        
        vector<int> winner = voting_find_winners(num_ballots, votes, is_winner);
        CPPUNIT_ASSERT(is_winner == false);
        CPPUNIT_ASSERT((int)winner.size() == 2);
        CPPUNIT_ASSERT(winner[0] = 2);
        CPPUNIT_ASSERT(winner[1] = 3);
    }
    
    // ----
    // eval
    // ----

    void test_eval_1 () {
        int num_ballots = 2;
        CandBallotMap map;
        VotesForMap votes;
        
        queue<int> ballot;
        ballot.push(2);
        vector<queue<int>> empty;
        vector<queue<int>> list_ballots;
        list_ballots.push_back(ballot);
        list_ballots.push_back(ballot);
        map.push_back(empty);
        map.push_back(list_ballots);
        map.push_back(empty);
        
        votes.push_back(0);
        votes.push_back(2);
        votes.push_back(0);
        
        vector<int> result = voting_eval(map, num_ballots, votes);
        
        CPPUNIT_ASSERT((int)result.size() == 1);
        CPPUNIT_ASSERT(result[0] == 1);
        
    }
    
    void test_eval_2 () {
        int num_ballots = 2;
        CandBallotMap map;
        VotesForMap votes;
        
        queue<int> ballot1;
        ballot1.push(2);
        queue<int> ballot2;
        ballot2.push(1);
        vector<queue<int>> empty;
        vector<queue<int>> list_ballots1;
        list_ballots1.push_back(ballot1);
        vector<queue<int>> list_ballots2;
        list_ballots2.push_back(ballot2);
        map.push_back(empty);
        map.push_back(list_ballots1);
        map.push_back(list_ballots2);
        
        votes.push_back(0);
        votes.push_back(1);
        votes.push_back(1);
        
        vector<int> result = voting_eval(map, num_ballots, votes);
        
        CPPUNIT_ASSERT((int)result.size() == 2);
        CPPUNIT_ASSERT(result[0] == 1);
        CPPUNIT_ASSERT(result[1] == 2);
    }
    
    void test_eval_3 () {
        int num_ballots = 5;
        CandBallotMap map;
        VotesForMap votes;
        
        queue<int> ballot1;
        ballot1.push(2);
        ballot1.push(3);
        queue<int> ballot2;
        ballot2.push(1);
        ballot2.push(3);
        queue<int> ballot3;
        ballot3.push(1);
        ballot3.push(2);
        
        vector<queue<int>> empty;
        vector<queue<int>> list_ballots1;
        list_ballots1.push_back(ballot1);
        list_ballots1.push_back(ballot1);
        vector<queue<int>> list_ballots2;
        list_ballots2.push_back(ballot2);
        list_ballots2.push_back(ballot2);
        vector<queue<int>> list_ballots3;
        list_ballots3.push_back(ballot3);
        
        map.push_back(empty);
        map.push_back(list_ballots1);
        map.push_back(list_ballots2);
        map.push_back(list_ballots3);
        
        votes.push_back(0);
        votes.push_back(2);
        votes.push_back(2);
        votes.push_back(1);
        
        vector<int> result = voting_eval(map, num_ballots, votes);
        CPPUNIT_ASSERT((int)result.size() == 1);
        CPPUNIT_ASSERT(result[0] == 1);
    }
    
    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        vector<int> winners;
        NumCandNameMap names;
        
        winners.push_back(1);
        names.push_back("");
        names.push_back("Name 1");
        voting_print(w, winners, names, true);
        CPPUNIT_ASSERT(w.str() == "Name 1\n");
        
    }
    
    void test_print_2 () {
        std::ostringstream w;
        vector<int> winners;
        NumCandNameMap names;
        
        winners.push_back(1);
        winners.push_back(2);
        names.push_back("");
        names.push_back("Name 1");
        names.push_back("Name 2");
        voting_print(w, winners, names, true);
        CPPUNIT_ASSERT(w.str() == "Name 1\nName 2\n");
    }
    
    void test_print_3 () {
        std::ostringstream w;
        vector<int> winners;
        NumCandNameMap names;
        
        winners.push_back(1);
        winners.push_back(2);
        winners.push_back(3);
        names.push_back("");
        names.push_back("Name 1");
        names.push_back("Name 2");
        names.push_back("Name 3");
        voting_print(w, winners, names, true);
        CPPUNIT_ASSERT(w.str() == "Name 1\nName 2\nName 3\n");
    }

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1\n\n1\nName 1\n1\n1\n");
        std::ostringstream w;
        
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Name 1\n");
    }
    
    void test_solve_2 () {
        std::istringstream r("1\n\n2\nName 1\nName 2\n2 1\n2 1\n2 1\n");
        std::ostringstream w;
        
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Name 2\n");
    }
    
    void test_solve_3 () {
        std::istringstream r("2\n\n2\nName 1\nName 2\n2 1\n2 1\n2 1\n\n3\nName 1\nName 2\nName 3\n1 2 3\n1 2 3\n2 1 3\n2 1 3\n3 2 1\n");
        std::ostringstream w;
        
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Name 2\n\nName 2\n");
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_voting_get_cands_1);
    CPPUNIT_TEST(test_voting_get_cands_2);
    CPPUNIT_TEST(test_voting_get_cands_3);
    CPPUNIT_TEST(test_voting_read_ballots_1);
    CPPUNIT_TEST(test_voting_read_ballots_2);
    CPPUNIT_TEST(test_voting_read_ballots_3);
    CPPUNIT_TEST(test_voting_read_1);
    CPPUNIT_TEST(test_voting_read_2);
    CPPUNIT_TEST(test_voting_read_3);
    CPPUNIT_TEST(test_voting_find_winners_1);
    CPPUNIT_TEST(test_voting_find_winners_2);
    CPPUNIT_TEST(test_voting_find_winners_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST_SUITE_END();
    };

// ----
// main
// ----

int main () {
    using namespace std;
    //ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
