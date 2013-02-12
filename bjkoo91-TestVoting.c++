// -----------------------
// cs371p-voting/Voting.h 
// @authors: Bon Koo & Bulat Bazarbayev
// -----------------------

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

// ----------
// TestVoting
// ----------

struct TestVoting : CppUnit::TestFixture {
    // -------------
    // solve_problem
    // -------------
    
    void test_solve_problem_1 () {
        std::istringstream r("1\nRed\n1\n");
        std::ostringstream w;
        bool done = voting_solve_problem (r, w);
        CPPUNIT_ASSERT (done);
        CPPUNIT_ASSERT (w.str() == "Red\n");
    }
    
    void test_solve_problem_2 () {
        std::istringstream r("3\nRed\nBlue\nYello\n1 2 3\n1 2 3\n1 2 3\n");
        std::ostringstream w;
        bool done = voting_solve_problem (r, w);
        CPPUNIT_ASSERT (done);
        CPPUNIT_ASSERT (w.str() == "Red\n");
    }
    
    void test_solve_problem_3 () {
        std::istringstream r("10\nA\nB\nC\nD\nE\nF\nG\nH\nI\nJ\n1 2 3 4 5 6 7 8 9 10\n");
        std::ostringstream w;
        bool done = voting_solve_problem (r, w);
        CPPUNIT_ASSERT (done);
        CPPUNIT_ASSERT (w.str() == "A\n");
    }
    
    void test_solve_problem_4 () {
        std::istringstream r("3\nRed\nBlue\nYello\n1 2 3\n2 1 2\n3 2 1\n");
        std::ostringstream w;
        bool done = voting_solve_problem (r, w);
        CPPUNIT_ASSERT (done);
        CPPUNIT_ASSERT (w.str() == "Red\nBlue\nYello\n");
    }
    
    void test_solve_problem_5 () {
        std::istringstream r("4\nRed\nBlue\nYello\nGreen\n1 2 3 4"
                             "\n2 1 4 3\n1 4 3 2\n2 1 4 3\n3 4 1 2\n4 3 2 1\n");
        std::ostringstream w;
        bool done = voting_solve_problem (r, w);
        CPPUNIT_ASSERT (done);
        CPPUNIT_ASSERT (w.str() == "Red\nBlue\n");
    }
    
    // ---------------
    // populate_ballot
    // ---------------
    
    void test_populate_ballot_1 () {
        std::vector <int> c_rank = {1};
        std::string rank = "1";
        struct ballot vote;
        vote.pos = 0;
        voting_populate_ballot (rank, vote);
        CPPUNIT_ASSERT (vote.ranks.size () == 1);
        CPPUNIT_ASSERT (vote.pos == 0);
        for (unsigned int i = 0; i < vote.ranks.size (); ++i) {
            CPPUNIT_ASSERT (vote.ranks.at (i) == c_rank.at(i));
        }
    }
    
    void test_populate_ballot_2 () {
        std::vector <int> c_rank = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        std::string rank = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15";
        struct ballot vote;
        vote.pos = 0;
        voting_populate_ballot (rank, vote);
        CPPUNIT_ASSERT (vote.ranks.size () == 15);
        CPPUNIT_ASSERT (vote.pos == 0);
        for (unsigned int i = 0; i < vote.ranks.size (); ++i) {
            CPPUNIT_ASSERT (vote.ranks.at (i) == c_rank.at(i));
        }
    }
    
    void test_populate_ballot_3 () {
        std::vector <int> c_rank = {0, -1, -2, -3};
        std::string rank = "0 -1 -2 -3";
        struct ballot vote;
        vote.pos = 0;
        voting_populate_ballot (rank, vote);
        CPPUNIT_ASSERT (vote.ranks.size () == 4);
        CPPUNIT_ASSERT (vote.pos == 0);
        for (unsigned int i = 0; i < vote.ranks.size (); ++i) {
            CPPUNIT_ASSERT (vote.ranks.at (i) == c_rank.at(i));
        }
    }
    
    void test_populate_ballot_4 () {
        std::vector <int> c_rank = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2};
        std::string rank = "1 1 1 1 1 2 2 2 2 2";
        struct ballot vote;
        vote.pos = 0;
        voting_populate_ballot (rank, vote);
        CPPUNIT_ASSERT (vote.ranks.size () == 10);
        CPPUNIT_ASSERT (vote.pos == 0);
        for (unsigned int i = 0; i < vote.ranks.size (); ++i) {
            CPPUNIT_ASSERT (vote.ranks.at (i) == c_rank.at(i));
        }
    }
    
    void test_populate_ballot_5 () {
        std::vector <int> c_rank = {1, 20, 2, 19, 3, 18, 4, 17, 5, 16, 6, 15, 7, 14, 8, 13, 9, 12, 10, 11};
        std::string rank = "1 20 2 19 3 18 4 17 5 16 6 15 7 14 8 13 9 12 10 11";
        struct ballot vote;
        vote.pos = 0;
        voting_populate_ballot (rank, vote);
        CPPUNIT_ASSERT (vote.ranks.size () == 20);
        CPPUNIT_ASSERT (vote.pos == 0);
        for (unsigned int i = 0; i < vote.ranks.size (); ++i) {
            CPPUNIT_ASSERT (vote.ranks.at (i) == c_rank.at(i));
        }
    }
    
    // -----
    // print
    // -----
    
    void test_print_1 () {
        std::string name = "Hello, World";
        std::ostringstream w;
        voting_print (w, name);
        CPPUNIT_ASSERT (w.str() == "Hello, World\n");
    }
    
    void test_print_2 () {
        std::string name = "-1 0 1";
        std::ostringstream w;
        voting_print (w, name);
        CPPUNIT_ASSERT (w.str() == "-1 0 1\n");
    }
    
    void test_print_3 () {
        std::string name = "~!@#$%^&*()_+";
        std::ostringstream w;
        voting_print (w, name);
        CPPUNIT_ASSERT (w.str() == "~!@#$%^&*()_+\n");
    }
    
    void test_print_4 () {
        std::string name = "Glenn Downing";
        std::ostringstream w;
        voting_print (w, name);
        CPPUNIT_ASSERT (w.str() == "Glenn Downing\n");
    }
    
    void test_print_5 () {
        std::string name = "A\nB\nC\nD\nE";
        std::ostringstream w;
        voting_print (w, name);
        CPPUNIT_ASSERT (w.str() == "A\nB\nC\nD\nE\n");
    }
    
    // ------------
    // count_ballot
    // ------------
    
    void test_count_ballot_1 () {
        std::vector<struct candidate> candidates;
        struct candidate empty;
        struct candidate cand_1;
        cand_1.running = true;
        candidates.push_back (empty);
        candidates.push_back (cand_1);
        std::vector<struct ballot> all_ballots;
        voting_count_ballot (candidates, all_ballots);
        CPPUNIT_ASSERT (candidates.size () == 2);
        CPPUNIT_ASSERT (all_ballots.size () == 0);
        CPPUNIT_ASSERT (candidates.at(1).running);
        CPPUNIT_ASSERT (candidates.at(1).votes.size () == 0);
    }
    
    void test_count_ballot_2 () {
        std::vector<struct candidate> candidates;
        struct candidate empty;
        struct candidate cand_1;
        cand_1.running = true;
        candidates.push_back (empty);
        candidates.push_back (cand_1);
        std::vector<struct ballot> all_ballots;
        struct ballot ballot_1;
        ballot_1.pos = 0; ballot_1.ranks.push_back (1);
        all_ballots.push_back (ballot_1);
        voting_count_ballot (candidates, all_ballots);
        CPPUNIT_ASSERT (candidates.size () == 2);
        CPPUNIT_ASSERT (all_ballots.size () == 1);
        CPPUNIT_ASSERT (candidates.at(1).running);
        CPPUNIT_ASSERT (candidates.at(1).votes.size () == 1);
    }
    
    void test_count_ballot_3 () {
        std::vector<struct candidate> candidates;
        struct candidate empty;
        struct candidate cand_1;
        cand_1.running = true;
        candidates.push_back (empty);
        candidates.push_back (cand_1);
        std::vector<struct ballot> all_ballots;
        struct ballot ballot_1;
        ballot_1.pos = 0; ballot_1.ranks.push_back (1);
        struct ballot ballot_2;
        ballot_2.pos = 0; ballot_2.ranks.push_back (1);
        struct ballot ballot_3;
        ballot_2.pos = 0; ballot_3.ranks.push_back (1);
        all_ballots.push_back (ballot_1);
        all_ballots.push_back (ballot_2);
        all_ballots.push_back (ballot_3);
        voting_count_ballot (candidates, all_ballots);
        CPPUNIT_ASSERT (candidates.size () == 2);
        CPPUNIT_ASSERT (all_ballots.size () == 3);
        CPPUNIT_ASSERT (candidates.at(1).running);
        CPPUNIT_ASSERT (candidates.at(1).votes.size () == 3);
    }
    
    void test_count_ballot_4 () {
        std::vector<struct candidate> candidates;
        struct candidate empty;
        candidates.push_back (empty);
        for (int i = 1; i <= 5; ++i) {
            struct candidate cand;
            cand.running = true;
            candidates.push_back (cand);
        }
        std::vector<struct ballot> all_ballots;
        for (int i = 0; i < 10; ++i) {
            struct ballot vote;
            vote.pos = 0;
            vote.ranks.push_back (1);
            vote.ranks.push_back (2);
            vote.ranks.push_back (3);
            vote.ranks.push_back (4);
            vote.ranks.push_back (5);
            all_ballots.push_back (vote);
        }
        voting_count_ballot (candidates, all_ballots);
        CPPUNIT_ASSERT (candidates.size () == 6);
        CPPUNIT_ASSERT (all_ballots.size () == 10);
        CPPUNIT_ASSERT (candidates.at (1).votes.size () == 10);
        CPPUNIT_ASSERT (candidates.at (2).votes.size () == 0);
        CPPUNIT_ASSERT (candidates.at (3).votes.size () == 0);
        CPPUNIT_ASSERT (candidates.at (4).votes.size () == 0);
        CPPUNIT_ASSERT (candidates.at (5).votes.size () == 0);
    }
    
    void test_count_ballot_5 () {
        std::vector<struct candidate> candidates;
        struct candidate empty;
        candidates.push_back (empty);
        for (int i = 1; i <= 20; ++i) {
            struct candidate cand;
            cand.running = true;
            candidates.push_back (cand);
        }
        std::vector<struct ballot> all_ballots;
        for (int i = 1; i <= 20; ++i) {
            struct ballot vote;
            vote.pos = 0;
            for (int j = 0; j < 20; ++j) {
                vote.ranks.push_back (i);
            }
            all_ballots.push_back (vote);
        }
        voting_count_ballot (candidates, all_ballots);
        CPPUNIT_ASSERT (candidates.size () == 21);
        CPPUNIT_ASSERT (all_ballots.size () == 20);
        for (int i = 1; i <= 20; ++i)
            CPPUNIT_ASSERT (candidates.at (i).votes.size () == 1);
    }
    
    // -----
    // round
    // -----

    void test_round_1 () {
        std::ostringstream w;
        std::vector<struct candidate> candidates;
        struct candidate empty;
        struct candidate cand_1;
        cand_1.name = "Winner";
        cand_1.running = true;
        candidates.push_back (empty);
        candidates.push_back (cand_1);
        unsigned int r = 1;
        bool done = voting_round (1, 1, r, candidates, w);
        CPPUNIT_ASSERT (done);
        CPPUNIT_ASSERT (candidates.at (1).running);
        CPPUNIT_ASSERT (candidates.at (1).votes.size () == 0);
        CPPUNIT_ASSERT (w.str() == "Winner\n");
    }
    
    void test_round_2 () {
        std::ostringstream w;
        std::ostringstream temp;
        std::vector<struct candidate> candidates;
        struct candidate empty;
        candidates.push_back (empty);
        for (int i = 1; i <= 20; ++i) {
            struct candidate cand;
            temp.str("");
            temp << "Name " << i;
            cand.name = temp.str();
            cand.running = true;
            candidates.push_back (cand);
        }
        unsigned int r = 20;
        bool done = voting_round (20, 1, r, candidates, w);
        CPPUNIT_ASSERT (done);
        for (int i = 1; i <= 20; ++i) {
            CPPUNIT_ASSERT (candidates.at (i).running);
            CPPUNIT_ASSERT (candidates.at (i).votes.size () == 0);
        }
        CPPUNIT_ASSERT (w.str() == "Name 1\nName 2\nName 3\nName 4\nName 5\n"
                                   "Name 6\nName 7\nName 8\nName 9\nName 10\n"
                                   "Name 11\nName 12\nName 13\nName 14\nName 15\n"
                                   "Name 16\nName 17\nName 18\nName 19\nName 20\n");
    }
    
    void test_round_3 () {
        std::ostringstream w;
        std::vector<struct candidate> candidates;
        struct ballot vote;
        vote.pos = 0;
        vote.ranks.push_back (1);
        vote.ranks.push_back (2);
        struct candidate empty;
        struct candidate cand_1;
        cand_1.name = "Winner";
        cand_1.running = true;
        cand_1.votes.push_back (&vote);
        struct candidate cand_2;
        cand_2.name = "Loser";
        cand_2.running = true;
        candidates.push_back (empty);
        candidates.push_back (cand_1);
        candidates.push_back (cand_2);
        unsigned int r = 2;
        bool done = voting_round (2, 1, r, candidates, w);
        CPPUNIT_ASSERT (done);
        CPPUNIT_ASSERT (candidates.at (1).running);
        CPPUNIT_ASSERT (candidates.at (1).votes.size () == 1);
        CPPUNIT_ASSERT (candidates.at (2).votes.size () == 0);
        CPPUNIT_ASSERT (w.str() == "Winner\n");
    }
    
    void test_round_4 () {
        std::ostringstream w;
        std::vector<struct candidate> candidates;
        struct ballot one;
        one.pos = 0; one.ranks.push_back (1); one.ranks.push_back (2); one.ranks.push_back (3);
        struct ballot two;
        two.pos = 0; two.ranks.push_back (2); two.ranks.push_back (1); two.ranks.push_back (3);
        struct ballot three;
        three.pos = 0; three.ranks.push_back (3); three.ranks.push_back (1); three.ranks.push_back (2);
        struct ballot four;
        four.pos = 0; four.ranks.push_back (1); four.ranks.push_back (2); four.ranks.push_back (3);
        struct candidate empty;
        struct candidate cand_1;
        cand_1.running = true;
        cand_1.votes.push_back (&one);
        cand_1.votes.push_back (&four);
        struct candidate cand_2;
        cand_2.running = true;
        cand_2.votes.push_back (&two);
        struct candidate cand_3;
        cand_3.running = true;
        cand_3.votes.push_back (&three);
        candidates.push_back (empty);
        candidates.push_back (cand_1);
        candidates.push_back (cand_2);
        candidates.push_back (cand_3);
        unsigned int r = 3;
        bool done = voting_round (3, 4, r, candidates, w);
        CPPUNIT_ASSERT (!done);
        CPPUNIT_ASSERT (r == 1);
        CPPUNIT_ASSERT (candidates.at (1).running);
        CPPUNIT_ASSERT (!candidates.at (2).running);
        CPPUNIT_ASSERT (!candidates.at (3).running);
        CPPUNIT_ASSERT (candidates.at (1).votes.size () == 4);
        CPPUNIT_ASSERT (w.str() == "");
    }
    
    void test_round_5 () {
        std::ostringstream w;
        std::vector<struct candidate> candidates;
        struct candidate empty;
        candidates.push_back (empty);
        struct candidate loser;
        loser.running = true;
        struct ballot vote;
        vote.pos = 0;
        for (int i = 1; i <= 10; ++i)
            vote.ranks.push_back (i);
        loser.votes.push_back (&vote);
        candidates.push_back (loser);
        for (int i = 1; i < 10; ++i) {
            struct candidate cand;
            cand.running = true;
            struct ballot vote_1;
            struct ballot vote_2;
            vote_1.pos = 0;
            vote_2.pos = 0;
            cand.votes.push_back (&vote_1);
            cand.votes.push_back (&vote_2);
            candidates.push_back (cand);
        }
        unsigned int r = 10;
        bool done = voting_round (10, 10, r, candidates, w);
        CPPUNIT_ASSERT (!done);
        CPPUNIT_ASSERT (r == 9);
        CPPUNIT_ASSERT (!candidates.at (1).running);
        CPPUNIT_ASSERT (candidates.at (1).votes.size () == 0);
        CPPUNIT_ASSERT (candidates.at (2).running);
        CPPUNIT_ASSERT (candidates.at (2).votes.size () == 3);
        for (int i = 3; i <= 10; ++i) {
            CPPUNIT_ASSERT (candidates.at (i).running);
            CPPUNIT_ASSERT (candidates.at (i).votes.size () == 2);
        }
        CPPUNIT_ASSERT (w.str() == "");
    }
    
    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1\n\n1\nA\n1\n");
        std::ostringstream w;
        voting_solve (r, w);
        CPPUNIT_ASSERT ("A\n");
    }
    
    void test_solve_2 () {
        std::istringstream r("5\n\n1\nA\n1\n\n1\nB\n1\n\n1\nC\n1\n\n1\nD\n1\n\n1\nE\n1\n");
        std::ostringstream w;
        voting_solve (r, w);
        CPPUNIT_ASSERT ("A\n\nB\n\nC\n\nD\n\nE\n");
    }
    
    void test_solve_3 () {
        std::istringstream r("1\n\n2\nA\nB\n1 2\n2 1\n");
        std::ostringstream w;
        voting_solve (r, w);
        CPPUNIT_ASSERT ("A\nB");
    }
    
    void test_solve_4 () {
        std::istringstream r("2\n\n2\nA\nB\n1 2\n2 1\n\n2\nC\nD\n1 2\n");
        std::ostringstream w;
        voting_solve (r, w);
        CPPUNIT_ASSERT ("A\nB\n\nC\n");
    }
    
    void test_solve_5 () {
        std::istringstream r("6\n\n"
                             "1\nThe Project 2 Voting\n1\n\n"
                             "3\nRed\nBlue\nYellow\n1 2 3\n2 1 3\n\n"
                             "2\n1\n2\n1 2\n1 2\n2 1\n\n"
                             "1\nUnit Tests\n1\n\n"
                             "2\nJohn\nJane\n1 2\n2 1\n\n"
                             "5\nA\nB\nC\nD\nE\n1 2 3 4 5\n2 1 3 4 5\n\n");
        std::ostringstream w;
        voting_solve (r, w);
        CPPUNIT_ASSERT ("The Project 2 Voting\n\nRed\nBlue\n\n1\n\nUnit Tests\n\nJohn\nJane\n\nA\nB\n");
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE (TestVoting);
    
    CPPUNIT_TEST (test_solve_problem_1);
    CPPUNIT_TEST (test_solve_problem_2);
    CPPUNIT_TEST (test_solve_problem_3);
    CPPUNIT_TEST (test_solve_problem_4);
    CPPUNIT_TEST (test_solve_problem_5);

    CPPUNIT_TEST (test_populate_ballot_1);
    CPPUNIT_TEST (test_populate_ballot_2);
    CPPUNIT_TEST (test_populate_ballot_3);
    CPPUNIT_TEST (test_populate_ballot_4);
    CPPUNIT_TEST (test_populate_ballot_5);
    
    CPPUNIT_TEST (test_print_1);
    CPPUNIT_TEST (test_print_2);
    CPPUNIT_TEST (test_print_3);
    CPPUNIT_TEST (test_print_4);
    CPPUNIT_TEST (test_print_5);


    CPPUNIT_TEST (test_count_ballot_1);
    CPPUNIT_TEST (test_count_ballot_2);
    CPPUNIT_TEST (test_count_ballot_3);
    CPPUNIT_TEST (test_count_ballot_4);
    CPPUNIT_TEST (test_count_ballot_5);
    
    CPPUNIT_TEST (test_round_1);
    CPPUNIT_TEST (test_round_2);
    CPPUNIT_TEST (test_round_3);
    CPPUNIT_TEST (test_round_4);
    CPPUNIT_TEST (test_round_5);
    
    CPPUNIT_TEST (test_solve_1);
    CPPUNIT_TEST (test_solve_2);
    CPPUNIT_TEST (test_solve_3);
    CPPUNIT_TEST (test_solve_4);
    CPPUNIT_TEST (test_solve_5);

    CPPUNIT_TEST_SUITE_END ();
};

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
