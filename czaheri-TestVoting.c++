// --------------------------------
// TestVoting.c++
// Copyright (C) 2013
// Comyar Zaheri, Sudheesh Katkam
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

#include "SolveVoting.h"
#include "ReadVoting.h"
#include "Voting.h"

// -----------
// TestCollatz
// -----------

struct TestVoting : CppUnit::TestFixture {
    /**********************************************************************************/
    // read voting
    /**********************************************************************************/

    void read_ballot_test_1() {
        std::string s = "1 2 3 4 5 6 7 8 9\n";
        Ballot ballot;
        read_ballot(s, ballot);
        CPPUNIT_ASSERT(ballot.votes[0] == 0);
        CPPUNIT_ASSERT(ballot.votes[1] == 1);
        CPPUNIT_ASSERT(ballot.votes[2] == 2);
        CPPUNIT_ASSERT(ballot.votes[3] == 3);
        CPPUNIT_ASSERT(ballot.votes[4] == 4);
        CPPUNIT_ASSERT(ballot.votes[5] == 5);
        CPPUNIT_ASSERT(ballot.votes[6] == 6);
        CPPUNIT_ASSERT(ballot.votes[7] == 7);
        CPPUNIT_ASSERT(ballot.votes[8] == 8);
    }

    void read_ballot_test_2() {
        std::string s = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20\n";
        Ballot ballot;
        read_ballot(s, ballot);
        CPPUNIT_ASSERT(ballot.votes[0] == 0);
        CPPUNIT_ASSERT(ballot.votes[1] == 1);
        CPPUNIT_ASSERT(ballot.votes[2] == 2);
        CPPUNIT_ASSERT(ballot.votes[3] == 3);
        CPPUNIT_ASSERT(ballot.votes[4] == 4);
        CPPUNIT_ASSERT(ballot.votes[5] == 5);
        CPPUNIT_ASSERT(ballot.votes[6] == 6);
        CPPUNIT_ASSERT(ballot.votes[7] == 7);
        CPPUNIT_ASSERT(ballot.votes[8] == 8);
        CPPUNIT_ASSERT(ballot.votes[9] == 9);
        CPPUNIT_ASSERT(ballot.votes[10] == 10);
        CPPUNIT_ASSERT(ballot.votes[11] == 11);
        CPPUNIT_ASSERT(ballot.votes[12] == 12);
        CPPUNIT_ASSERT(ballot.votes[13] == 13);
        CPPUNIT_ASSERT(ballot.votes[14] == 14);
        CPPUNIT_ASSERT(ballot.votes[15] == 15);
        CPPUNIT_ASSERT(ballot.votes[16] == 16);
        CPPUNIT_ASSERT(ballot.votes[17] == 17);
        CPPUNIT_ASSERT(ballot.votes[18] == 18);
        CPPUNIT_ASSERT(ballot.votes[19] == 19);
    }

    void read_ballot_test_3() {
        std::string s = "15 \n";
        Ballot ballot;
        read_ballot(s, ballot);
        CPPUNIT_ASSERT(ballot.votes[0] == 14);
    }

    void read_election_test_1() {
        std::string s =     "3\n"
                            "Sudheesh Katkam\n"
                            "Sheerhan Sheerhan\n"
                            "Shamlam Shikash\n"
                            "1 2 3\n"
                            "2 3 1\n"
                            "3 2 1\n"
                            "3 1 2\n"
                            "2 1 3\n"
                            "1 3 2";
        std::stringstream r;
        r << s;
        Election election;
        bool b = voting_read_election(r, election);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(election.number_of_candidates == 3);
        CPPUNIT_ASSERT(election.number_of_ballots == 6);

        CPPUNIT_ASSERT(election.candidates[0].name == "Sudheesh Katkam");
        CPPUNIT_ASSERT(election.candidates[1].name == "Sheerhan Sheerhan");
        CPPUNIT_ASSERT(election.candidates[2].name == "Shamlam Shikash");

        CPPUNIT_ASSERT(election.candidates[0].eliminated == false);
        CPPUNIT_ASSERT(election.candidates[1].eliminated == false);
        CPPUNIT_ASSERT(election.candidates[2].eliminated == false);
    }

    void read_election_test_2() {
        std::string s =     "4\n"
                            "Sudheesh Katkam\n"
                            "Sheerhan Sheerhan\n"
                            "Shamlam Shikash\n"
                            "Shruti Shakrum\n"
                            "1 2 3 4\n"
                            "2 3 1 4\n"
                            "3 2 1 4\n"
                            "3 1 2 4\n"
                            "2 1 3 4\n"
                            "1 3 2 4";
        std::stringstream r;
        r << s;
        Election election;
        bool b = voting_read_election(r, election);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(election.number_of_candidates == 4);
        CPPUNIT_ASSERT(election.number_of_ballots == 6);

        CPPUNIT_ASSERT(election.candidates[0].name == "Sudheesh Katkam");
        CPPUNIT_ASSERT(election.candidates[1].name == "Sheerhan Sheerhan");
        CPPUNIT_ASSERT(election.candidates[2].name == "Shamlam Shikash");
        CPPUNIT_ASSERT(election.candidates[3].name == "Shruti Shakrum");

        CPPUNIT_ASSERT(election.candidates[0].eliminated == false);
        CPPUNIT_ASSERT(election.candidates[1].eliminated == false);
        CPPUNIT_ASSERT(election.candidates[2].eliminated == false);
        CPPUNIT_ASSERT(election.candidates[3].eliminated == false);
    }

    void read_election_test_3() {
        std::string s =     "2\n"
                            "Sudheesh Katkam\n"
                            "Sheerhan Sheerhan\n"
                            "1 2\n"
                            "2 1\n"
                            "1 2\n"
                            "2 1\n"
                            "2 1\n"
                            "1 2";
        std::stringstream r;
        r << s;
        Election election;
        bool b = voting_read_election(r, election);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(election.number_of_candidates == 2);
        CPPUNIT_ASSERT(election.number_of_ballots == 6);

        CPPUNIT_ASSERT(election.candidates[0].name == "Sudheesh Katkam");
        CPPUNIT_ASSERT(election.candidates[1].name == "Sheerhan Sheerhan");

        CPPUNIT_ASSERT(election.candidates[0].eliminated == false);
        CPPUNIT_ASSERT(election.candidates[1].eliminated == false);
    }

    /**********************************************************************************/
    // solve voting
    /**********************************************************************************/


    void solve_highest_vote_count_test_1() {
        /// Create Ballots
        Ballot ballotZero;
        ballotZero.assigned_vote = 1;

        Ballot ballotOne;
        ballotOne.assigned_vote = 0;

        Ballot ballotTwo;
        ballotTwo.assigned_vote = 1;

        Ballot ballotThree;
        ballotThree.assigned_vote = 0;

        Ballot ballotFour;
        ballotFour.assigned_vote = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.assigned_ballots.push_back(&ballotOne);
        candidateZero.assigned_ballots.push_back(&ballotThree);

        Candidate candidateOne;
        candidateOne.assigned_ballots.push_back(&ballotZero);
        candidateOne.assigned_ballots.push_back(&ballotTwo);
        candidateOne.assigned_ballots.push_back(&ballotFour);

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 5;
        election.ballots[0] = ballotZero;
        election.ballots[1] = ballotOne;
        election.ballots[2] = ballotTwo;
        election.ballots[3] = ballotThree;
        election.ballots[4] = ballotFour;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;

        int count = highest_vote_count(election.candidates, election.number_of_candidates);
        CPPUNIT_ASSERT(count == 3);
    }

    void solve_highest_vote_count_test_2() {
        /// Create Ballots
        Ballot ballotZero;
        ballotZero.assigned_vote = 1;

        Ballot ballotOne;
        ballotOne.assigned_vote = 0;

        Ballot ballotTwo;
        ballotTwo.assigned_vote = 1;

        Ballot ballotThree;
        ballotThree.assigned_vote = 0;

        Ballot ballotFour;
        ballotFour.assigned_vote = 1;

        Ballot ballotFive;
        ballotFour.assigned_vote = 2;

        Ballot ballotSix;
        ballotFour.assigned_vote = 2;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.assigned_ballots.push_back(&ballotOne);
        candidateZero.assigned_ballots.push_back(&ballotThree);

        Candidate candidateOne;
        candidateOne.assigned_ballots.push_back(&ballotZero);
        candidateOne.assigned_ballots.push_back(&ballotTwo);
        candidateOne.assigned_ballots.push_back(&ballotFour);

        Candidate candidateTwo;
        candidateTwo.assigned_ballots.push_back(&ballotFive);
        candidateTwo.assigned_ballots.push_back(&ballotSix);

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 7;
        election.ballots[0] = ballotZero;
        election.ballots[1] = ballotOne;
        election.ballots[2] = ballotTwo;
        election.ballots[3] = ballotThree;
        election.ballots[4] = ballotFour;
        election.ballots[5] = ballotFive;
        election.ballots[6] = ballotSix;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;
        election.candidates[2] = candidateTwo;

        int count = highest_vote_count(election.candidates, election.number_of_candidates);
        CPPUNIT_ASSERT(count == 3);
    }

    void solve_highest_vote_count_test_3() {
        /// Create Ballots
        Ballot ballotZero;
        ballotZero.assigned_vote = 1;

        Ballot ballotOne;
        ballotOne.assigned_vote = 0;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.assigned_ballots.push_back(&ballotOne);

        Candidate candidateOne;
        candidateOne.assigned_ballots.push_back(&ballotZero);

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 2;
        election.ballots[0] = ballotZero;
        election.ballots[1] = ballotOne;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;

        int count = highest_vote_count(election.candidates, election.number_of_candidates);
        CPPUNIT_ASSERT(count == 1);
    }

    void solve_lowest_vote_count_test_1() {
        /// Create Ballots
        Ballot ballotZero;
        ballotZero.assigned_vote = 1;

        Ballot ballotOne;
        ballotOne.assigned_vote = 0;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.assigned_ballots.push_back(&ballotOne);

        Candidate candidateOne;
        candidateOne.assigned_ballots.push_back(&ballotZero);

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 2;
        election.ballots[0] = ballotZero;
        election.ballots[1] = ballotOne;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;

        int count = lowest_vote_count(election.candidates, election.number_of_candidates);
        CPPUNIT_ASSERT(count == 1);
    }

    void solve_lowest_vote_count_test_2() {
        /// Create Ballots
        Ballot ballotZero;
        ballotZero.assigned_vote = 1;

        Ballot ballotOne;
        ballotOne.assigned_vote = 0;

        Ballot ballotTwo;
        ballotTwo.assigned_vote = 1;

        Ballot ballotThree;
        ballotThree.assigned_vote = 0;

        Ballot ballotFour;
        ballotFour.assigned_vote = 1;

        Ballot ballotFive;
        ballotFour.assigned_vote = 2;

        Ballot ballotSix;
        ballotFour.assigned_vote = 2;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.assigned_ballots.push_back(&ballotOne);
        candidateZero.assigned_ballots.push_back(&ballotThree);

        Candidate candidateOne;
        candidateOne.assigned_ballots.push_back(&ballotZero);
        candidateOne.assigned_ballots.push_back(&ballotTwo);
        candidateOne.assigned_ballots.push_back(&ballotFour);

        Candidate candidateTwo;
        candidateTwo.assigned_ballots.push_back(&ballotFive);
        candidateTwo.assigned_ballots.push_back(&ballotSix);

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 7;
        election.ballots[0] = ballotZero;
        election.ballots[1] = ballotOne;
        election.ballots[2] = ballotTwo;
        election.ballots[3] = ballotThree;
        election.ballots[4] = ballotFour;
        election.ballots[5] = ballotFive;
        election.ballots[6] = ballotSix;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;
        election.candidates[2] = candidateTwo;

        int count = lowest_vote_count(election.candidates, election.number_of_candidates);
        CPPUNIT_ASSERT(count == 2);
    }

    void solve_lowest_vote_count_test_3() {
        /// Create Ballots
        Ballot ballotZero;
        ballotZero.assigned_vote = 1;

        Ballot ballotOne;
        ballotOne.assigned_vote = 0;

        Ballot ballotTwo;
        ballotTwo.assigned_vote = 1;

        Ballot ballotThree;
        ballotThree.assigned_vote = 0;

        Ballot ballotFour;
        ballotFour.assigned_vote = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.assigned_ballots.push_back(&ballotOne);
        candidateZero.assigned_ballots.push_back(&ballotThree);

        Candidate candidateOne;
        candidateOne.assigned_ballots.push_back(&ballotZero);
        candidateOne.assigned_ballots.push_back(&ballotTwo);
        candidateOne.assigned_ballots.push_back(&ballotFour);

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 5;
        election.ballots[0] = ballotZero;
        election.ballots[1] = ballotOne;
        election.ballots[2] = ballotTwo;
        election.ballots[3] = ballotThree;
        election.ballots[4] = ballotFour;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;

        int count = lowest_vote_count(election.candidates, election.number_of_candidates);
        CPPUNIT_ASSERT(count == 2);
    }

    void solve_eliminate_losing_candidates_test_1() {
        /// Create Ballots
        Ballot ballotZero;
        ballotZero.assigned_vote = 1;

        Ballot ballotOne;
        ballotOne.assigned_vote = 0;

        Ballot ballotTwo;
        ballotOne.assigned_vote = 0;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.assigned_ballots.push_back(&ballotOne);
        candidateZero.assigned_ballots.push_back(&ballotTwo);

        Candidate candidateOne;
        candidateOne.assigned_ballots.push_back(&ballotZero);

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 3;
        election.ballots[0] = ballotZero;
        election.ballots[1] = ballotOne;
        election.ballots[2] = ballotTwo;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;
        bool return_val = eliminate_losing_candidates(election.candidates, election.number_of_candidates);
        CPPUNIT_ASSERT(return_val == true);
        CPPUNIT_ASSERT(election.candidates[1].eliminated == true);
    }

    void solve_eliminate_losing_candidates_test_2() {
        /// Create Ballots
        Ballot ballotZero;
        ballotZero.assigned_vote = 1;

        Ballot ballotOne;
        ballotOne.assigned_vote = 0;

        Ballot ballotTwo;
        ballotOne.assigned_vote = 0;

        Ballot ballotThree;
        ballotThree.assigned_vote = 2;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.assigned_ballots.push_back(&ballotOne);
        candidateZero.assigned_ballots.push_back(&ballotTwo);

        Candidate candidateOne;
        candidateOne.assigned_ballots.push_back(&ballotZero);

        Candidate candidateTwo;
        candidateTwo.assigned_ballots.push_back(&ballotThree);

        /// Create Election
        Election election;
        election.number_of_candidates = 3;
        election.number_of_ballots = 4;
        election.ballots[0] = ballotZero;
        election.ballots[1] = ballotOne;
        election.ballots[2] = ballotTwo;
        election.ballots[3] = ballotThree;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;
        election.candidates[2] = candidateTwo;
        bool return_val = eliminate_losing_candidates(election.candidates, election.number_of_candidates);
        CPPUNIT_ASSERT(return_val == true);
        CPPUNIT_ASSERT(election.candidates[1].eliminated == true);
        CPPUNIT_ASSERT(election.candidates[2].eliminated == true);
    }

    void solve_eliminate_losing_candidates_test_3() {
        /// Create Ballots
        Ballot ballotZero;
        ballotZero.assigned_vote = 1;

        Ballot ballotOne;
        ballotOne.assigned_vote = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = false;

        Candidate candidateOne;
        candidateOne.eliminated = false;
        candidateOne.assigned_ballots.push_back(&ballotZero);
        candidateOne.assigned_ballots.push_back(&ballotOne);

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 2;
        election.ballots[0] = ballotZero;
        election.ballots[1] = ballotOne;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;
        bool return_val = eliminate_losing_candidates(election.candidates, election.number_of_candidates);
        CPPUNIT_ASSERT(return_val == true);
        CPPUNIT_ASSERT(election.candidates[0].eliminated == true);
        CPPUNIT_ASSERT(election.candidates[1].eliminated == false);
    }

    void solve_assign_next_valid_vote_test_1() {
         /// Create Ballots
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 0;
        ballotZero.votes[0] = 0;
        ballotZero.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = true;

        Candidate candidateOne;
        candidateOne.eliminated = false;

        /// Create Election
        Election election;
        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;
        assign_next_valid_vote(&ballotZero, election.candidates);
        CPPUNIT_ASSERT(ballotZero.assigned_vote == 1);
    }

    void solve_assign_next_valid_vote_test_2() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 0;
        ballotZero.votes[0] = 0;
        ballotZero.votes[1] = 1;
        ballotZero.votes[2] = 2;
        ballotZero.votes[3] = 3;
        ballotZero.votes[4] = 4;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = true;

        Candidate candidateOne;
        candidateOne.eliminated = true;

        Candidate candidateTwo;
        candidateTwo.eliminated = true;

        Candidate candidateThree;
        candidateThree.eliminated = true;

        Candidate candidateFour;
        candidateFour.eliminated = false;

        /// Create Election
        Election election;
        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;
        election.candidates[2] = candidateTwo;
        election.candidates[3] = candidateThree;
        election.candidates[4] = candidateFour;
        assign_next_valid_vote(&ballotZero, election.candidates);
        CPPUNIT_ASSERT(ballotZero.assigned_vote == 4);
    }

    void solve_assign_next_valid_vote_test_3() {
         Ballot ballotZero;
        ballotZero.index = 1;
        ballotZero.assigned_vote = 1;
        ballotZero.votes[0] = 0;
        ballotZero.votes[1] = 1;
        ballotZero.votes[2] = 2;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = true;

        Candidate candidateOne;
        candidateOne.eliminated = true;

        Candidate candidateTwo;
        candidateTwo.eliminated = false;

        /// Create Election
        Election election;
        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;
        election.candidates[2] = candidateTwo;
        assign_next_valid_vote(&ballotZero, election.candidates);
        CPPUNIT_ASSERT(ballotZero.assigned_vote == 2);
    }

    void solve_unassign_losers_ballots_test_1() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 1;
        ballotZero.votes[0] = 1;
        ballotZero.votes[1] = 0;

        Ballot ballotOne;
        ballotOne.index = 0;
        ballotOne.assigned_vote = 1;
        ballotOne.votes[0] = 1;
        ballotOne.votes[1] = 0;

        Ballot ballotTwo;
        ballotTwo.index = 0;
        ballotTwo.assigned_vote = 0;
        ballotTwo.votes[0] = 0;
        ballotTwo.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = true;
        candidateZero.assigned_ballots.push_back(&ballotTwo);

        Candidate candidateOne;
        candidateOne.eliminated = false;
        candidateOne.assigned_ballots.push_back(&ballotZero);
        candidateOne.assigned_ballots.push_back(&ballotOne);

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;

        int invalidated_count = unassign_losers_ballots(election.candidates, election.number_of_candidates, election.unassigned_ballots);
        CPPUNIT_ASSERT(invalidated_count == 1);
        CPPUNIT_ASSERT(election.candidates[0].assigned_ballots.size() == 0);
        CPPUNIT_ASSERT(election.unassigned_ballots[0] == &ballotTwo);
    }

    void solve_unassign_losers_ballots_test_2() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 1;
        ballotZero.votes[0] = 1;
        ballotZero.votes[1] = 0;

        Ballot ballotOne;
        ballotOne.index = 0;
        ballotOne.assigned_vote = 1;
        ballotOne.votes[0] = 1;
        ballotOne.votes[1] = 0;

        Ballot ballotTwo;
        ballotTwo.index = 0;
        ballotTwo.assigned_vote = 0;
        ballotTwo.votes[0] = 0;
        ballotTwo.votes[1] = 1;

        Ballot ballotThree;
        ballotThree.index = 0;
        ballotThree.assigned_vote = 0;
        ballotThree.votes[0] = 0;
        ballotThree.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = true;
        candidateZero.assigned_ballots.push_back(&ballotTwo);
        candidateZero.assigned_ballots.push_back(&ballotThree);

        Candidate candidateOne;
        candidateOne.eliminated = false;
        candidateOne.assigned_ballots.push_back(&ballotZero);
        candidateOne.assigned_ballots.push_back(&ballotOne);

        /// Create Election
        Election election;
        election.number_of_candidates = 2;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;

        int invalidated_count = unassign_losers_ballots(election.candidates, election.number_of_candidates, election.unassigned_ballots);
        CPPUNIT_ASSERT(invalidated_count == 2);
        CPPUNIT_ASSERT(election.candidates[0].assigned_ballots.size() == 0);
        CPPUNIT_ASSERT(election.unassigned_ballots[0] == &ballotTwo);
        CPPUNIT_ASSERT(election.unassigned_ballots[1] == &ballotThree);
    }

    void solve_unassign_losers_ballots_test_3() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 1;
        ballotZero.votes[0] = 1;
        ballotZero.votes[1] = 0;

        Ballot ballotOne;
        ballotOne.index = 0;
        ballotOne.assigned_vote = 1;
        ballotOne.votes[0] = 1;
        ballotOne.votes[1] = 0;

        Ballot ballotTwo;
        ballotTwo.index = 0;
        ballotTwo.assigned_vote = 0;
        ballotTwo.votes[0] = 0;
        ballotTwo.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = false;
        candidateZero.assigned_ballots.push_back(&ballotTwo);

        Candidate candidateOne;
        candidateOne.eliminated = true;
        candidateOne.assigned_ballots.push_back(&ballotZero);
        candidateOne.assigned_ballots.push_back(&ballotOne);

        /// Create Election
        Election election;
        election.number_of_candidates = 2;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;

        int invalidated_count = unassign_losers_ballots(election.candidates, election.number_of_candidates, election.unassigned_ballots);
        CPPUNIT_ASSERT(invalidated_count == 2);
        CPPUNIT_ASSERT(election.candidates[1].assigned_ballots.size() == 0);
        CPPUNIT_ASSERT(election.unassigned_ballots[0] == &ballotZero);
        CPPUNIT_ASSERT(election.unassigned_ballots[1] == &ballotOne);
    }

    void solve_assign_ballots_test_1() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 1;
        ballotZero.votes[0] = 1;
        ballotZero.votes[1] = 0;

        Ballot ballotOne;
        ballotOne.index = 0;
        ballotOne.assigned_vote = 1;
        ballotOne.votes[0] = 1;
        ballotOne.votes[1] = 0;

        Ballot ballotTwo;
        ballotTwo.index = 0;
        ballotTwo.assigned_vote = 0;
        ballotTwo.votes[0] = 0;
        ballotTwo.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = false;
        Candidate candidateOne;
        candidateOne.eliminated = false;

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.unassigned_ballots.push_back(&ballotZero);
        election.unassigned_ballots.push_back(&ballotOne);
        election.unassigned_ballots.push_back(&ballotTwo);

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;

        int count = assign_ballots(election.unassigned_ballots, election.candidates);
        CPPUNIT_ASSERT(count == 3);
        CPPUNIT_ASSERT(election.candidates[0].assigned_ballots.size() == 1);
        CPPUNIT_ASSERT(election.candidates[1].assigned_ballots.size() == 2);
        CPPUNIT_ASSERT(election.unassigned_ballots.size() == 0);
    }

    void solve_assign_ballots_test_2() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 0;
        ballotZero.votes[0] = 0;
        ballotZero.votes[1] = 1;

        Ballot ballotOne;
        ballotOne.index = 0;
        ballotOne.assigned_vote = 0;
        ballotOne.votes[0] = 0;
        ballotOne.votes[1] = 1;

        Ballot ballotTwo;
        ballotTwo.index = 0;
        ballotTwo.assigned_vote = 0;
        ballotTwo.votes[0] = 0;
        ballotTwo.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = false;
        candidateZero.assigned_ballots.push_back(&ballotTwo);

        Candidate candidateOne;
        candidateOne.eliminated = false;

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.unassigned_ballots.push_back(&ballotZero);
        election.unassigned_ballots.push_back(&ballotOne);

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;

        int count = assign_ballots(election.unassigned_ballots, election.candidates);
        CPPUNIT_ASSERT(count == 2);
        CPPUNIT_ASSERT(election.candidates[0].assigned_ballots.size() == 3);
        CPPUNIT_ASSERT(election.candidates[1].assigned_ballots.size() == 0);
        CPPUNIT_ASSERT(election.unassigned_ballots.size() == 0);
    }

    void solve_assign_ballots_test_3() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 1;
        ballotZero.votes[0] = 1;
        ballotZero.votes[1] = 0;

        Ballot ballotOne;
        ballotOne.index = 0;
        ballotOne.assigned_vote = 0;
        ballotOne.votes[0] = 0;
        ballotOne.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = false;
        Candidate candidateOne;
        candidateOne.eliminated = false;

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.unassigned_ballots.push_back(&ballotZero);
        election.unassigned_ballots.push_back(&ballotOne);

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;

        int count = assign_ballots(election.unassigned_ballots, election.candidates);
        CPPUNIT_ASSERT(count == 2);
        CPPUNIT_ASSERT(election.candidates[0].assigned_ballots.size() == 1);
        CPPUNIT_ASSERT(election.candidates[1].assigned_ballots.size() == 1);
        CPPUNIT_ASSERT(election.unassigned_ballots.size() == 0);
    }

    void solve_check_for_single_winner_test_1() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 1;
        ballotZero.votes[0] = 1;
        ballotZero.votes[1] = 0;

        Ballot ballotOne;
        ballotOne.index = 0;
        ballotOne.assigned_vote = 0;
        ballotOne.votes[0] = 0;
        ballotOne.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = false;
        candidateZero.assigned_ballots.push_back(&ballotOne);
        Candidate candidateOne;
        candidateOne.eliminated = false;
        candidateOne.assigned_ballots.push_back(&ballotZero);

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 2;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;

        bool value = check_for_single_winner(election.candidates, election.number_of_candidates, election.winners, election.number_of_ballots);
        CPPUNIT_ASSERT(value == false);
        CPPUNIT_ASSERT(election.winners[0] == false);
        CPPUNIT_ASSERT(election.winners[1] == false);
    }

    void solve_check_for_single_winner_test_2() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 0;
        ballotZero.votes[0] = 0;
        ballotZero.votes[1] = 1;

        Ballot ballotOne;
        ballotOne.index = 1;
        ballotOne.assigned_vote = 0;
        ballotOne.votes[0] = 0;
        ballotOne.votes[1] = 1;

        Ballot ballotThree;
        ballotThree.index = 2;
        ballotThree.assigned_vote = 0;
        ballotThree.votes[0] = 0;
        ballotThree.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = false;
        candidateZero.assigned_ballots.push_back(&ballotZero);
        candidateZero.assigned_ballots.push_back(&ballotOne);
        candidateZero.assigned_ballots.push_back(&ballotThree);
        Candidate candidateOne;
        candidateOne.eliminated = false;

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 2;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;

        bool value = check_for_single_winner(election.candidates, election.number_of_candidates, election.winners, election.number_of_ballots);
        CPPUNIT_ASSERT(value == true);
        CPPUNIT_ASSERT(election.winners[0] == true);
        CPPUNIT_ASSERT(election.winners[1] == false);
    }

    void solve_check_for_single_winner_test_3() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 0;
        ballotZero.votes[0] = 0;
        ballotZero.votes[1] = 1;

        Ballot ballotOne;
        ballotOne.index = 0;
        ballotOne.assigned_vote = 0;
        ballotOne.votes[0] = 0;
        ballotOne.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = false;
        candidateZero.assigned_ballots.push_back(&ballotZero);
        candidateZero.assigned_ballots.push_back(&ballotOne);

        Candidate candidateOne;
        candidateOne.eliminated = false;
        
        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 2;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;

        bool value = check_for_single_winner(election.candidates, election.number_of_candidates, election.winners, election.number_of_ballots);
        CPPUNIT_ASSERT(value == true);
        CPPUNIT_ASSERT(election.winners[0] == true);
        CPPUNIT_ASSERT(election.winners[1] == false);
    }

    void solve_check_for_multiple_winner_test_1() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 1;
        ballotZero.votes[0] = 1;
        ballotZero.votes[1] = 0;

        Ballot ballotOne;
        ballotOne.index = 0;
        ballotOne.assigned_vote = 0;
        ballotOne.votes[0] = 0;
        ballotOne.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = false;
        candidateZero.assigned_ballots.push_back(&ballotOne);
        Candidate candidateOne;
        candidateOne.eliminated = false;
        candidateOne.assigned_ballots.push_back(&ballotZero);

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 2;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;
        election.winners[0] = false;
        election.winners[1] = false;

        bool value = check_for_multiple_winners(election.candidates, election.number_of_candidates, election.winners);
        CPPUNIT_ASSERT(value == true);
        CPPUNIT_ASSERT(election.winners[0] == true);
        CPPUNIT_ASSERT(election.winners[1] == true);
    }

    void solve_check_for_multiple_winner_test_2() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 0;
        ballotZero.votes[0] = 0;
        ballotZero.votes[1] = 1;

        Ballot ballotOne;
        ballotOne.index = 0;
        ballotOne.assigned_vote = 0;
        ballotOne.votes[0] = 0;
        ballotOne.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = false;
        candidateZero.assigned_ballots.push_back(&ballotZero);
        candidateZero.assigned_ballots.push_back(&ballotOne);
        Candidate candidateOne;
        candidateOne.eliminated = false;

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 2;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;
        election.winners[0] = false;
        election.winners[1] = false;

        bool value = check_for_multiple_winners(election.candidates, election.number_of_candidates, election.winners);
        CPPUNIT_ASSERT(value == false);
        CPPUNIT_ASSERT(election.winners[0] == false);
        CPPUNIT_ASSERT(election.winners[1] == false);
    }

    void solve_check_for_multiple_winner_test_3() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 0;
        ballotZero.votes[0] = 0;
        ballotZero.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = false;
        candidateZero.assigned_ballots.push_back(&ballotZero);

        Candidate candidateOne;
        candidateOne.eliminated = false;
        
        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 1;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;
        election.winners[0] = false;
        election.winners[1] = false;

        bool value = check_for_multiple_winners(election.candidates, election.number_of_candidates, election.winners);
        CPPUNIT_ASSERT(value == false);
        CPPUNIT_ASSERT(election.winners[0] == false);
        CPPUNIT_ASSERT(election.winners[1] == false);
    }

    void solve_check_for_winner_test_1() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 1;
        ballotZero.votes[0] = 1;
        ballotZero.votes[1] = 0;

        Ballot ballotOne;
        ballotOne.index = 0;
        ballotOne.assigned_vote = 0;
        ballotOne.votes[0] = 0;
        ballotOne.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = false;
        candidateZero.assigned_ballots.push_back(&ballotOne);
        Candidate candidateOne;
        candidateOne.eliminated = false;
        candidateOne.assigned_ballots.push_back(&ballotZero);

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 2;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;
        election.winners[0] = false;
        election.winners[1] = false;

        bool value = check_for_winners(election.candidates, election.number_of_candidates, election.winners, election.number_of_ballots);
        CPPUNIT_ASSERT(value == true);
        CPPUNIT_ASSERT(election.winners[0] == true);
        CPPUNIT_ASSERT(election.winners[1] == true);
    }

    void solve_check_for_winner_test_2() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 0;
        ballotZero.votes[0] = 0;
        ballotZero.votes[1] = 1;

        Ballot ballotOne;
        ballotOne.index = 0;
        ballotOne.assigned_vote = 0;
        ballotOne.votes[0] = 0;
        ballotOne.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = false;
        candidateZero.assigned_ballots.push_back(&ballotZero);
        candidateZero.assigned_ballots.push_back(&ballotOne);
        Candidate candidateOne;
        candidateOne.eliminated = false;

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 2;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;
        election.winners[0] = false;
        election.winners[1] = false;

        bool value = check_for_winners(election.candidates, election.number_of_candidates, election.winners, election.number_of_ballots);
        CPPUNIT_ASSERT(value == true);
        CPPUNIT_ASSERT(election.winners[0] == true);
        CPPUNIT_ASSERT(election.winners[1] == false);
    }

    void solve_check_for_winner_test_3() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 0;
        ballotZero.votes[0] = 0;
        ballotZero.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = false;
        candidateZero.assigned_ballots.push_back(&ballotZero);

        Candidate candidateOne;
        candidateOne.eliminated = false;
        
        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 1;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;
        election.winners[0] = false;
        election.winners[1] = false;

        bool value = check_for_winners(election.candidates, election.number_of_candidates, election.winners, election.number_of_ballots);
        CPPUNIT_ASSERT(value == true);
        CPPUNIT_ASSERT(election.winners[0] == true);
        CPPUNIT_ASSERT(election.winners[1] == false);
    }

    void solve_election_test_1() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 1;
        ballotZero.votes[0] = 1;
        ballotZero.votes[1] = 0;

        Ballot ballotOne;
        ballotOne.index = 0;
        ballotOne.assigned_vote = 0;
        ballotOne.votes[0] = 0;
        ballotOne.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = false;
        candidateZero.assigned_ballots.push_back(&ballotOne);
        Candidate candidateOne;
        candidateOne.eliminated = false;
        candidateOne.assigned_ballots.push_back(&ballotZero);

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 2;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;
        election.winners[0] = false;
        election.winners[1] = false;

        voting_solve_election(election);
        CPPUNIT_ASSERT(election.winners[0] == true);
        CPPUNIT_ASSERT(election.winners[1] == true);
    }

    void solve_election_test_2() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 0;
        ballotZero.votes[0] = 0;
        ballotZero.votes[1] = 1;

        Ballot ballotOne;
        ballotOne.index = 0;
        ballotOne.assigned_vote = 0;
        ballotOne.votes[0] = 0;
        ballotOne.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = false;
        candidateZero.assigned_ballots.push_back(&ballotZero);
        candidateZero.assigned_ballots.push_back(&ballotOne);
        Candidate candidateOne;
        candidateOne.eliminated = false;

        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 2;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;
        election.winners[0] = false;
        election.winners[1] = false;

        voting_solve_election(election);
        CPPUNIT_ASSERT(election.winners[0] == true);
        CPPUNIT_ASSERT(election.winners[1] == false);
    }

    void solve_election_test_3() {
        Ballot ballotZero;
        ballotZero.index = 0;
        ballotZero.assigned_vote = 0;
        ballotZero.votes[0] = 0;
        ballotZero.votes[1] = 1;

        /// Create Candididates
        Candidate candidateZero;
        candidateZero.eliminated = false;
        candidateZero.assigned_ballots.push_back(&ballotZero);

        Candidate candidateOne;
        candidateOne.eliminated = false;
        
        /// Create Election
        Election election;
        election.number_of_candidates = 2;
        election.number_of_ballots = 1;

        election.candidates[0] = candidateZero;
        election.candidates[1] = candidateOne;
        election.winners[0] = false;
        election.winners[1] = false;

        voting_solve_election(election);
        CPPUNIT_ASSERT(election.winners[0] == true);
        CPPUNIT_ASSERT(election.winners[1] == false);
    }
    /**********************************************************************************/
    // voting
    /**********************************************************************************/

    void voting_find_winners_test_1() {
        std::stringstream r;
        std::stringstream w;

        std::string s =     "2\n"
                            "\n"
                            "2\n"
                            "Sudheesh Katkam\n"
                            "Sheerhan Sheerhan\n"
                            "1 2\n"
                            "2 1\n"
                            "1 2\n"
                            "2 1\n"
                            "2 1\n"
                            "1 2\n"
                            "\n"
                            "4\n"
                            "Sudheesh Katkam\n"
                            "Sheerhan Sheerhan\n"
                            "Shamlam Shikash\n"
                            "Shruti Shakrum\n"
                            "1 2 3 4\n"
                            "2 3 1 4\n"
                            "3 2 1 4\n"
                            "3 1 2 4\n"
                            "2 1 3 4\n"
                            "1 3 2 4";
        r << s;
        voting_find_winners(r, w);
        getline(w, s);
        CPPUNIT_ASSERT(s == "Sudheesh Katkam");
        getline(w, s);
        CPPUNIT_ASSERT(s == "Sheerhan Sheerhan");
        getline(w, s);
        getline(w, s);
        CPPUNIT_ASSERT(s == "Sudheesh Katkam");
        getline(w, s);
        CPPUNIT_ASSERT(s == "Sheerhan Sheerhan");
        getline(w, s);
        CPPUNIT_ASSERT(s == "Shamlam Shikash");
    }

    void voting_find_winners_test_2() {
        std::stringstream r;
        std::stringstream w;

        std::string s =     "1\n"
                            "\n"
                            "1\n"
                            "Sheerhan Sheerhan\n"
                            "1\n"
                            "1\n"
                            "1\n"
                            "1\n"
                            "1\n"
                            "1";
        r << s;
        voting_find_winners(r, w);
        getline(w, s);
        CPPUNIT_ASSERT(s == "Sheerhan Sheerhan");
    }

    void voting_find_winners_test_3() {
        std::stringstream r;
        std::stringstream w;

        std::string s =     "3\n"
                            "\n"
                            "5\n"
                            "Sham Shukr\n"
                            "Laam Linguid\n"
                            "Stipler Stamfeddi\n"
                            "Jammilo Jangles\n"
                            "Zefferson Tang\n"
                            "1 3 2 4 5\n"
                            "5 1 3 2 4\n"
                            "3 2 1 5 3\n"
                            "5 2 3 1 4\n"
                            "5 4 3 2 1\n"
                            "\n"
                            "2\n"
                            "Sudheesh Katkam\n"
                            "Sheerhan Sheerhan\n"
                            "1 2\n"
                            "2 1\n"
                            "1 2\n"
                            "2 1\n"
                            "2 1\n"
                            "1 2\n"
                            "\n"
                            "4\n"
                            "Sudheesh Katkam\n"
                            "Sheerhan Sheerhan\n"
                            "Shamlam Shikash\n"
                            "Shruti Shakrum\n"
                            "1 2 3 4\n"
                            "2 3 1 4\n"
                            "3 2 1 4\n"
                            "3 1 2 4\n"
                            "2 1 3 4\n"
                            "1 3 2 4";
        r << s;
        voting_find_winners(r, w);
        getline(w, s);
        CPPUNIT_ASSERT(s == "Zefferson Tang");
        getline(w, s);
        getline(w, s);
        CPPUNIT_ASSERT(s == "Sudheesh Katkam");
        getline(w, s);
        CPPUNIT_ASSERT(s == "Sheerhan Sheerhan");
        getline(w, s);
        getline(w, s);
        CPPUNIT_ASSERT(s == "Sudheesh Katkam");
        getline(w, s);
        CPPUNIT_ASSERT(s == "Sheerhan Sheerhan");
        getline(w, s);
        CPPUNIT_ASSERT(s == "Shamlam Shikash");
    }



    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);

    /******* ReadVoting *******/
    // Read Ballot
    CPPUNIT_TEST(read_ballot_test_1);
    CPPUNIT_TEST(read_ballot_test_2);
    CPPUNIT_TEST(read_ballot_test_3);
    // Read Election
    CPPUNIT_TEST(read_election_test_1);
    CPPUNIT_TEST(read_election_test_2);
    CPPUNIT_TEST(read_election_test_3);


    /******* SolveVoting *******/
    // Highest vote count
    CPPUNIT_TEST(solve_highest_vote_count_test_1);
    CPPUNIT_TEST(solve_highest_vote_count_test_2);
    CPPUNIT_TEST(solve_highest_vote_count_test_3);
    // Lowest vote count
    CPPUNIT_TEST(solve_lowest_vote_count_test_1);
    CPPUNIT_TEST(solve_lowest_vote_count_test_2);
    CPPUNIT_TEST(solve_lowest_vote_count_test_3);
    // Elliminate losing candidates
    CPPUNIT_TEST(solve_eliminate_losing_candidates_test_1);
    CPPUNIT_TEST(solve_eliminate_losing_candidates_test_2);
    CPPUNIT_TEST(solve_eliminate_losing_candidates_test_3);
    // Assign next valid vote
    CPPUNIT_TEST(solve_assign_next_valid_vote_test_1);
    CPPUNIT_TEST(solve_assign_next_valid_vote_test_2);
    CPPUNIT_TEST(solve_assign_next_valid_vote_test_3);
    // Unassign losers ballots
    CPPUNIT_TEST(solve_unassign_losers_ballots_test_1);
    CPPUNIT_TEST(solve_unassign_losers_ballots_test_2);
    CPPUNIT_TEST(solve_unassign_losers_ballots_test_3);
    // Assign ballots
    CPPUNIT_TEST(solve_assign_ballots_test_1);
    CPPUNIT_TEST(solve_assign_ballots_test_2);
    CPPUNIT_TEST(solve_assign_ballots_test_3);
    // Check for single winner
    CPPUNIT_TEST(solve_check_for_single_winner_test_1);
    CPPUNIT_TEST(solve_check_for_single_winner_test_2);
    CPPUNIT_TEST(solve_check_for_single_winner_test_3);
    // Check for multiple winners
    CPPUNIT_TEST(solve_check_for_multiple_winner_test_1);
    CPPUNIT_TEST(solve_check_for_multiple_winner_test_2);
    CPPUNIT_TEST(solve_check_for_multiple_winner_test_3);
    // Check for winners
    CPPUNIT_TEST(solve_check_for_winner_test_1);
    CPPUNIT_TEST(solve_check_for_winner_test_2);
    CPPUNIT_TEST(solve_check_for_winner_test_3);
    // Solve election
    CPPUNIT_TEST(solve_election_test_1);
    CPPUNIT_TEST(solve_election_test_2);
    CPPUNIT_TEST(solve_election_test_3);

    /******* Voting *******/
    CPPUNIT_TEST(voting_find_winners_test_1);
    CPPUNIT_TEST(voting_find_winners_test_2);
    CPPUNIT_TEST(voting_find_winners_test_3);
    CPPUNIT_TEST_SUITE_END();};

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
