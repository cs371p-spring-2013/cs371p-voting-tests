// --------------------------------
// projects/voting/Testvoting.c++
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
    % g++ -pedantic -std=c++0x -Wall voting.c++ Testvoting.c++ -o Testvoting.c++.app -lcppunit -ldl
    % valgrind Testvoting.c++.app >& Testvoting.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>
#include <sstream>
#include <map>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

using namespace std;
// -----------
// Testvoting
// -----------

struct TestVoting : CppUnit::TestFixture {

    // ----
    // read_candidates
    // ----

    void test_read_candidates_1 () {
    	map<int,Candidate> candidates;
    	for(int j=1;j<=20;++j) {
    		Candidate temp = Candidate(j, "");
    		candidates.insert(make_pair(j,temp));
    	}
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n");
        int numCandidates = voting_read_candidates(r, candidates);
        CPPUNIT_ASSERT(numCandidates == 3);
        CPPUNIT_ASSERT(candidates[1].candidateName == "John Doe");
        CPPUNIT_ASSERT(candidates[2].candidateName == "Jane Smith");
        CPPUNIT_ASSERT(candidates[3].candidateName == "Sirhan Sirhan");
    }
    void test_read_candidates_2 () {
    	map<int,Candidate> candidates;
    	for(int j=1;j<=20;++j) {
    		Candidate temp = Candidate(j, "");
    		candidates.insert(make_pair(j,temp));
    	}
        std::istringstream r("4\nMature Downing\nProblematic Hawk\nVicious Oryx\nMature Pikachu\n");
        int numCandidates = voting_read_candidates(r, candidates);
        CPPUNIT_ASSERT(numCandidates == 4);
        CPPUNIT_ASSERT(candidates[1].candidateName == "Mature Downing");
        CPPUNIT_ASSERT(candidates[2].candidateName == "Problematic Hawk");
        CPPUNIT_ASSERT(candidates[3].candidateName == "Vicious Oryx");
        CPPUNIT_ASSERT(candidates[4].candidateName == "Mature Pikachu");
    }
    void test_read_candidates_3 () {
    	map<int,Candidate> candidates;
    	for(int j=1;j<=20;++j) {
    		Candidate temp = Candidate(j, "");
    		candidates.insert(make_pair(j,temp));
    	}
        std::istringstream r("4\nRed\nGreen\nBlue\nOrange\n");
        int numCandidates = voting_read_candidates(r, candidates);
        CPPUNIT_ASSERT(numCandidates == 4);
        CPPUNIT_ASSERT(candidates[1].candidateName == "Red");
        CPPUNIT_ASSERT(candidates[2].candidateName == "Green");
        CPPUNIT_ASSERT(candidates[3].candidateName == "Blue");
        CPPUNIT_ASSERT(candidates[4].candidateName == "Orange");
    }

    // ----
    // read_ballots
    // ----

    void test_read_ballots_1 () {
    	map<int,Candidate> candidates;
    	for(int j=1;j<=20;++j) {
    		Candidate temp = Candidate(j, "");
    		candidates.insert(make_pair(j,temp));
    	}
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        int numCandidates = voting_read_candidates(r, candidates);
    	int ballotBox[1000][20];
        int totalNumberOfBallots = voting_read_ballots(r, candidates, numCandidates, ballotBox);
        CPPUNIT_ASSERT(totalNumberOfBallots == 5);
        CPPUNIT_ASSERT(ballotBox[0][0] == 1);
        CPPUNIT_ASSERT(ballotBox[0][1] == 2);
        CPPUNIT_ASSERT(ballotBox[0][2] == 3);
    }
    void test_read_ballots_2 () {
    	map<int,Candidate> candidates;
    	for(int j=1;j<=20;++j) {
    		Candidate temp = Candidate(j, "");
    		candidates.insert(make_pair(j,temp));
    	}
        std::istringstream r("4\nMature Downing\nProblematic Hawk\nVicious Oryx\nMature Pikachu\n2 4 3 1 \n3 1 2 4 \n2 3 4 1 \n4 1 3 2 \n3 1 4 2 \n3 2 4 1 \n2 3 1 4 \n3 1 2 4 \n3 1 4 2 \n4 1 3 2");
        int numCandidates = voting_read_candidates(r, candidates);
    	int ballotBox[1000][20];
        int totalNumberOfBallots = voting_read_ballots(r, candidates, numCandidates, ballotBox);
        CPPUNIT_ASSERT(totalNumberOfBallots == 10);
        CPPUNIT_ASSERT(ballotBox[0][0] == 2);
        CPPUNIT_ASSERT(ballotBox[0][1] == 4);
        CPPUNIT_ASSERT(ballotBox[0][2] == 3);
        CPPUNIT_ASSERT(ballotBox[0][3] == 1);
    }
    void test_read_ballots_3 () {
    	map<int,Candidate> candidates;
    	for(int j=1;j<=20;++j) {
    		Candidate temp = Candidate(j, "");
    		candidates.insert(make_pair(j,temp));
    	}
        std::istringstream r("4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 4 1\n1 3 4 2\n3 4 2 1\n4 3 1 2");
        int numCandidates = voting_read_candidates(r, candidates);
    	int ballotBox[1000][20];
        int totalNumberOfBallots = voting_read_ballots(r, candidates, numCandidates, ballotBox);
        CPPUNIT_ASSERT(totalNumberOfBallots == 6);
        CPPUNIT_ASSERT(ballotBox[0][0] == 1);
        CPPUNIT_ASSERT(ballotBox[0][1] == 2);
        CPPUNIT_ASSERT(ballotBox[0][2] == 3);
        CPPUNIT_ASSERT(ballotBox[0][3] == 4);
    }

    // ----
    // eval
    // ----

    void test_eval_1 () {
    	map<int,Candidate> candidates;
    	for(int j=1;j<=20;++j) {
    		Candidate temp = Candidate(j, "");
    		candidates.insert(make_pair(j,temp));
    	}
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        int numCandidates = voting_read_candidates(r, candidates);
    	int ballotBox[1000][20];
        int totalNumberOfBallots = voting_read_ballots(r, candidates, numCandidates, ballotBox);
        string result = voting_eval(candidates, ballotBox, totalNumberOfBallots);
        CPPUNIT_ASSERT(result == "John Doe");
	}

    void test_eval_2 () {
    	map<int,Candidate> candidates;
    	for(int j=1;j<=20;++j) {
    		Candidate temp = Candidate(j, "");
    		candidates.insert(make_pair(j,temp));
    	}
        std::istringstream r("4\nMature Downing\nProblematic Hawk\nVicious Oryx\nMature Pikachu\n2 4 3 1 \n3 1 2 4 \n2 3 4 1 \n4 1 3 2 \n3 1 4 2 \n3 2 4 1 \n2 3 1 4 \n3 1 2 4 \n3 1 4 2 \n4 1 3 2");
        int numCandidates = voting_read_candidates(r, candidates);
    	int ballotBox[1000][20];
        int totalNumberOfBallots = voting_read_ballots(r, candidates, numCandidates, ballotBox);
        string result = voting_eval(candidates, ballotBox, totalNumberOfBallots);
        CPPUNIT_ASSERT(result == "Vicious Oryx");
	}

    void test_eval_3 () {
    	map<int,Candidate> candidates;
    	for(int j=1;j<=20;++j) {
    		Candidate temp = Candidate(j, "");
    		candidates.insert(make_pair(j,temp));
    	}
        std::istringstream r("4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 4 1\n1 3 4 2\n3 4 2 1\n4 3 1 2");
        int numCandidates = voting_read_candidates(r, candidates);
    	int ballotBox[1000][20];
        int totalNumberOfBallots = voting_read_ballots(r, candidates, numCandidates, ballotBox);
        string result = voting_eval(candidates, ballotBox, totalNumberOfBallots);
        CPPUNIT_ASSERT(result == "Red\nGreen");
	}

    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        voting_print(w, "John Doe");
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}
    void test_print_2 () {
        std::ostringstream w;
        voting_print(w, "Vicious Oryx");
        CPPUNIT_ASSERT(w.str() == "Vicious Oryx\n");}
    void test_print_3 () {
        std::ostringstream w;
        voting_print(w, "Red\nGreen");
        CPPUNIT_ASSERT(w.str() == "Red\nGreen\n");}

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}
    void test_solve_2 () {
        std::istringstream r("1\n\n4\nMature Downing\nProblematic Hawk\nVicious Oryx\nMature Pikachu\n2 4 3 1 \n3 1 2 4 \n2 3 4 1 \n4 1 3 2 \n3 1 4 2 \n3 2 4 1 \n2 3 1 4 \n3 1 2 4 \n3 1 4 2 \n4 1 3 2");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Vicious Oryx\n");}
    void test_solve_3 () {
        std::istringstream r("1\n\n4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 4 1\n1 3 4 2\n3 4 2 1\n4 3 1 2");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Red\nGreen\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read_candidates_1);
    CPPUNIT_TEST(test_read_candidates_2);
    CPPUNIT_TEST(test_read_candidates_3);
    CPPUNIT_TEST(test_read_ballots_1);
    CPPUNIT_TEST(test_read_ballots_2);
    CPPUNIT_TEST(test_read_ballots_3);
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
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}

