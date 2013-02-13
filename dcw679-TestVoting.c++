// ----------------------
// CS371P Assignment 2
// Australian Voting Problem
// ----------------------

// --------
// includes
// --------

#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

using namespace std;


struct TestVoting : CppUnit::TestFixture{ //Voting {

    // -----
    // solve
    // -----

    void test_solve_1 () {
        istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
	ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
    }

    void test_solve_tie () {
	istringstream r("1\n\n2\nJohn Doe\nJane Smith\n1 2\n2 1\n1 2\n2 1\n");
	ostringstream w;
	voting_solve(r, w);
	CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\n");
    }

	void test_solve_majority () {
	istringstream r("1\n\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\nBarack Obama\n1 2 3 4\n2 1 3 4\n3 1 3 4\n4 1 3 2\n1 3 2 4\n1 4 2 3\n");
	ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
	}

	void test_solve_multiple_cases(){
	istringstream r("2\n\n2\nJohn Doe\nJane Smith\n1 2\n2 1\n1 2\n2 1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
	ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\n\nJohn Doe\n");
	}

    // -----
    // split
    // -----

    void test_split_1() {
        queue<int> ballot = vote_split("1 2 3");
        CPPUNIT_ASSERT(ballot.size() == 3);

    }

    void test_split_2() {
        queue<int> ballot = vote_split("1 2 3 4 5 6 7 8 9 10 11");
        CPPUNIT_ASSERT(ballot.front() == 1);
        CPPUNIT_ASSERT(ballot.back()  == 11);
         
    }

    void test_split_3() {
        queue<int> ballot = vote_split("6 5 4 3 2 1");
        CPPUNIT_ASSERT(ballot.size()  == 6);
        CPPUNIT_ASSERT(ballot.front() == 6);
        ballot.pop();
        CPPUNIT_ASSERT(ballot.front() == 5);
        ballot.pop();
        CPPUNIT_ASSERT(ballot.front() == 4);
        CPPUNIT_ASSERT(ballot.size()  == 4);
    }

	void test_voting_case_1(){
		vector< queue<int> > ballots;
		queue<int> ballot1 = vote_split("1 2 3");
		queue<int> ballot2 = vote_split("1 2 3");
		ballots.push_back(ballot1);
		ballots.push_back(ballot2);

		map<int, string> candidates;
		candidates[1] = "John Doe";
		candidates[2] = "Jane Doe";
		candidates[3] = "Sirhan Sirhan";
		
		CPPUNIT_ASSERT(voting_case(ballots, candidates) == "John Doe");
	}

	void test_voting_case_2(){
		vector< queue<int> > ballots;
		ballots.push_back(vote_split("3 2 1 4"));
		ballots.push_back(vote_split("3 4 1 2"));
		ballots.push_back(vote_split("4 3 1 2"));
		ballots.push_back(vote_split("1 3 2 4"));
		ballots.push_back(vote_split("1 4 3 2"));
		ballots.push_back(vote_split("2 3 1 4"));
		ballots.push_back(vote_split("1 2 3 4"));
		ballots.push_back(vote_split("3 2 4 1"));
		ballots.push_back(vote_split("3 2 4 1"));
		ballots.push_back(vote_split("4 3 2 1"));
		ballots.push_back(vote_split("1 4 3 2"));

		map<int, string> candidates;
		candidates[1] = "Iron Man";
		candidates[2] = "Hulk";
		candidates[3] = "Thor";
		candidates[4] = "Loki";
		
		CPPUNIT_ASSERT(voting_case(ballots, candidates) == "Thor");
	}

        void test_voting_case_3() {
            vector< queue<int> > ballots;
            ballots.push_back(vote_split("1 2"));
            ballots.push_back(vote_split("2 1"));
            ballots.push_back(vote_split("2 1"));
            ballots.push_back(vote_split("1 2"));
            map <int, string> candidates;
            candidates[1] = "Richard Nixon";
            candidates[2] = "John F Kennedy";
 
            CPPUNIT_ASSERT(voting_case(ballots, candidates) == "Richard Nixon\nJohn F Kennedy");
        }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    
    CPPUNIT_TEST(test_split_1);
    CPPUNIT_TEST(test_split_2);
    CPPUNIT_TEST(test_split_3);

    CPPUNIT_TEST(test_solve_1);
	CPPUNIT_TEST(test_solve_tie);
	CPPUNIT_TEST(test_solve_majority);
	CPPUNIT_TEST(test_solve_multiple_cases);
	CPPUNIT_TEST(test_voting_case_1);
	CPPUNIT_TEST(test_voting_case_2);
        CPPUNIT_TEST(test_voting_case_3);
    CPPUNIT_TEST_SUITE_END();
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




