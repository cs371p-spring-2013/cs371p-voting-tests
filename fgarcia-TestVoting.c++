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
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "Voting.h"

using namespace std;
// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {

    // ----
    // voting_read_numCases
    // ----
    void test_voting_read_numCases () {
        std::istringstream r("1\n\n");
        int numCases;
        const bool b = voting_read_numCases(r, numCases);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(numCases == 1);}
        
    void test_voting_read_numCases1 () {
        std::istringstream r("a\n\n");
        int numCases;
        const bool b = voting_read_numCases(r, numCases);
        CPPUNIT_ASSERT(b == false);
        CPPUNIT_ASSERT(numCases == 0);}
        
    void test_voting_read_numCases2 () {
        std::istringstream r("14\n\n");
        int numCases;
        const bool b = voting_read_numCases(r, numCases);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(numCases == 14);}
        
	// ----
    // voting_read_numCandidates
    // ----
    void test_voting_read_numCandidates () {
        std::istringstream r("1\n");
        int numCandidates;
        const bool b = voting_read_numCandidates(r, numCandidates);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(numCandidates == 1);}
        
    void test_voting_read_numCandidates1 () {
        std::istringstream r("CANDIDATES\n");
        int numCandidates;
        const bool b = voting_read_numCandidates(r, numCandidates);
        CPPUNIT_ASSERT(b == false);
        CPPUNIT_ASSERT(numCandidates == 0);}
        
    void test_voting_read_numCandidates2 () {
        std::istringstream r("19\n");
        int numCandidates;
        const bool b = voting_read_numCandidates(r, numCandidates);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(numCandidates == 19);}

	// ----
    // voting_read_candidates
    // ----
    void test_voting_read_candidates () {
        std::istringstream r("John Doe\n");
        std::vector<std::string> candidates;
        int numCandidates = 1;
        const bool b = voting_read_candidates(r, candidates, numCandidates);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(candidates[0] == "John Doe");}
        
    void test_voting_read_candidates1 () {
        std::istringstream r("John Doe\nJane Smith");
        std::vector<std::string> candidates;
        int numCandidates = 2;
        const bool b = voting_read_candidates(r, candidates, numCandidates);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(candidates[0] == "John Doe");
        CPPUNIT_ASSERT(candidates[1] == "Jane Smith");}
        
    void test_voting_read_candidates2 () {
        std::istringstream r("John Doe\n");
        std::vector<std::string> candidates;
        int numCandidates = 1;
        const bool b = voting_read_candidates(r, candidates, numCandidates);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(candidates[0] == "John Doe");}


    // ----
    // test_voting_read_ballots
    // ----
    void test_voting_read_ballots () {
        std::istringstream r("1 2 3\n");
        std::vector< std::queue<int> > ballots;
        const bool b = voting_read_ballots (r, ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(ballots.size() == 1);
        CPPUNIT_ASSERT(ballots[0].front() == 1);
        ballots[0].pop();
        CPPUNIT_ASSERT(ballots[0].front() == 2);
		ballots[0].pop();
        CPPUNIT_ASSERT(ballots[0].front() == 3);}
        
    void test_voting_read_ballots1 () {
        std::istringstream r("1 2 3\n4 5 6\n");
        std::vector< std::queue<int> > ballots;
        const bool b = voting_read_ballots (r, ballots);
        CPPUNIT_ASSERT(ballots.size() == 2);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(ballots[0].front() == 1);
        CPPUNIT_ASSERT(ballots[1].front() == 4);
        ballots[1].pop();
        CPPUNIT_ASSERT(ballots[1].front() == 5);}
        
	void test_voting_read_ballots2 () {
        std::istringstream r("1\n");
        std::vector< std::queue<int> > ballots;
        const bool b = voting_read_ballots (r, ballots);
        CPPUNIT_ASSERT(ballots.size() == 1);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(ballots[0].front() == 1);}
        
	// -----
    // test_voting_print_winner
    // -----
    void test_voting_print_winner () {
        std::ostringstream w;
        vector<int> countBallots;
        countBallots.push_back(1);
        countBallots.push_back(1);
        vector<string> candidates;
        candidates.push_back("John Doe");
        candidates.push_back("Sam Houston");
        int max = 1;
        int numCandidates = 2;
        voting_print_winner(w, max, numCandidates, countBallots, candidates);
        CPPUNIT_ASSERT(w.str() == "John Doe\nSam Houston\n");}

	void test_voting_print_winner1 () {
        std::ostringstream w;
        vector<int> countBallots;
        countBallots.push_back(2);
        countBallots.push_back(1);
        countBallots.push_back(0);
        vector<string> candidates;
        candidates.push_back("John Doe");
        candidates.push_back("Sam Houston");
        candidates.push_back("Big Loser");
        int max = 2;
        int numCandidates = 3;
        voting_print_winner(w, max, numCandidates, countBallots, candidates);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}

	void test_voting_print_winner2 () {
        std::ostringstream w;
        vector<int> countBallots;
        countBallots.push_back(2);
        countBallots.push_back(2);
        countBallots.push_back(0);
        vector<string> candidates;
        candidates.push_back("John Doe");
        candidates.push_back("Sam Houston");
        candidates.push_back("Big Loser");
        int max = 2;
        int numCandidates = 3;
        voting_print_winner(w, max, numCandidates, countBallots, candidates);
        CPPUNIT_ASSERT(w.str() == "John Doe\nSam Houston\n");}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1\n\n2\nJohn Doe\nSam Houston\n1 2\n2 1\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\nSam Houston\n");}
	
	void test_solve1 () {
        std::istringstream r("1\n\n2\nJohn Doe\nSam Houston\n1 2\n1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}
	
	void test_solve2 () {
        std::istringstream r("1\n\n3\nJohn Doe\nSam Houston\nBig Loser\n1 2 3\n2 1 3\n1 2 3\n2 3 1\n3 1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\nSam Houston\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_voting_read_numCases);
    CPPUNIT_TEST(test_voting_read_numCases1);
    CPPUNIT_TEST(test_voting_read_numCases2);
    CPPUNIT_TEST(test_voting_read_numCandidates);
    CPPUNIT_TEST(test_voting_read_numCandidates1);
    CPPUNIT_TEST(test_voting_read_numCandidates2);
    CPPUNIT_TEST(test_voting_read_ballots);
    CPPUNIT_TEST(test_voting_read_ballots1);
    CPPUNIT_TEST(test_voting_read_ballots2);
	CPPUNIT_TEST(test_voting_read_candidates);
	CPPUNIT_TEST(test_voting_read_candidates1);
	CPPUNIT_TEST(test_voting_read_candidates2);
	CPPUNIT_TEST(test_voting_print_winner);
	CPPUNIT_TEST(test_voting_print_winner1);
	CPPUNIT_TEST(test_voting_print_winner2);
	CPPUNIT_TEST(test_solve);
	CPPUNIT_TEST(test_solve1);
	//CPPUNIT_TEST(test_solve2);
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
