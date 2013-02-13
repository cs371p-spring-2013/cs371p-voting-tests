
// --------------------------
// UVa Australian Voting Project
// File: TestVoting.c++
// Authors: Mitch Stephan and Boris Veltman
// UTEIDs: mjs4373 and bv3777 
// --------------------------


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

    // --------------------------
    // test voting_readNumCases
    // --------------------------

	
    void test_voting_readNumCases_1 () {
        std::istringstream r("1\n");
        voting_readNumCases(r);
		CPPUNIT_ASSERT(numCases == 1); }
		
	void test_voting_readNumCases_2 () {
        std::istringstream r("2\n");
        voting_readNumCases(r);
		CPPUNIT_ASSERT(numCases == 2); }
		
	void test_voting_readNumCases_3 () {
        std::istringstream r("3\n");
        voting_readNumCases(r);
		CPPUNIT_ASSERT(numCases == 3); }
        
        // --------------------------
    // test voting_clearBallots
    // --------------------------
	
	void test_voting_clearBallots_1(){
		ballots.at(1).push_back("1 2 3");
                CPPUNIT_ASSERT(ballots.at(1).size() == 1);
		voting_clearBallots();
		CPPUNIT_ASSERT(ballots.at(1).size() == 0);
		CPPUNIT_ASSERT(ballots.at(2).size() == 0);
	}
	
	void test_voting_clearBallots_2(){
		ballots.at(1).push_back("1 2 3");
                ballots.at(2).push_back("1 2 3");
                CPPUNIT_ASSERT(ballots.at(1).size() == 1);
                CPPUNIT_ASSERT(ballots.at(2).size() == 1);
		voting_clearBallots();
		CPPUNIT_ASSERT(ballots.at(1).size() == 0);
		CPPUNIT_ASSERT(ballots.at(2).size() == 0);
	}
	
	void test_voting_clearBallots_3(){
		ballots.at(2).push_back("1 2 3");
                ballots.at(2).push_back("1 2 3");
                CPPUNIT_ASSERT(ballots.at(1).size() == 0);
                CPPUNIT_ASSERT(ballots.at(2).size() == 2);
		voting_clearBallots();
		CPPUNIT_ASSERT(ballots.at(1).size() == 0);
		CPPUNIT_ASSERT(ballots.at(2).size() == 0);
	}

    // --------------------------
    // test voting_readCase
    // --------------------------

	void test_voting_readCase_1(){
		std::istringstream r("2\nMitch\nBoris\n1 2\n1 2\n");
		voting_readCase(r);
		CPPUNIT_ASSERT(numCands == 2);
		CPPUNIT_ASSERT(totalBallots == 2);
		CPPUNIT_ASSERT(winningThreshold = 1);
		CPPUNIT_ASSERT(candNames[1] == "Mitch");
		CPPUNIT_ASSERT(candNames[2] == "Boris");
		CPPUNIT_ASSERT(ballots.at(1).at(0) == "2");
		CPPUNIT_ASSERT(ballots.at(1).at(1) == "2");
		CPPUNIT_ASSERT(ballots.at(1).size() == 2);
		CPPUNIT_ASSERT(ballots.at(2).size() == 0);
	}
	
	void test_voting_readCase_2(){
                voting_clearBallots();
		std::istringstream r("2\nMitch\nBoris\n1 2\n2 1\n");
		voting_readCase(r);
		CPPUNIT_ASSERT(numCands == 2);
                CPPUNIT_ASSERT(totalBallots == 2);
		CPPUNIT_ASSERT(winningThreshold = 1);
		CPPUNIT_ASSERT(candNames[1] == "Mitch");
		CPPUNIT_ASSERT(candNames[2] == "Boris");
		CPPUNIT_ASSERT(ballots.at(1).at(0) == "2");
		CPPUNIT_ASSERT(ballots.at(2).at(0) == "1");
		CPPUNIT_ASSERT(ballots.at(1).size() == 1);
		CPPUNIT_ASSERT(ballots.at(2).size() == 1);
                voting_clearBallots();
	}
	
	void test_voting_readCase_3(){
                voting_clearBallots();
		std::istringstream r("3\nMitch\nBoris\nSally\n1 2 3\n2 1 3\n3 1 2\n1 2 3\n");
		voting_readCase(r);
		CPPUNIT_ASSERT(numCands == 3);
                CPPUNIT_ASSERT(totalBallots == 4);
		CPPUNIT_ASSERT(winningThreshold = 2);
		CPPUNIT_ASSERT(candNames[1] == "Mitch");
		CPPUNIT_ASSERT(candNames[2] == "Boris");
		CPPUNIT_ASSERT(candNames[3] == "Sally"); 
		CPPUNIT_ASSERT(ballots.at(1).at(0) == "2 3");
		CPPUNIT_ASSERT(ballots.at(1).at(1) == "2 3");
		CPPUNIT_ASSERT(ballots.at(2).at(0) == "1 3");
		CPPUNIT_ASSERT(ballots.at(3).at(0) == "1 2"); 
		CPPUNIT_ASSERT(ballots.at(1).size() == 2);
		CPPUNIT_ASSERT(ballots.at(2).size() == 1);
		CPPUNIT_ASSERT(ballots.at(3).size() == 1);
                voting_clearBallots();
	}

	
	// --------------------------
    // test voting_clearCandNames
    // --------------------------
	
	void test_voting_clearCandNames_1(){
		std::istringstream r("2\nMitch\nBoris\n1 2\n1 2\n");
		voting_readCase(r);
		voting_clearCandNames();
		CPPUNIT_ASSERT(candNames[1] == "");
		CPPUNIT_ASSERT(candNames[2] == "");
	}
	
	void test_voting_clearCandNames_2(){
		std::istringstream r("2\nMitch\nBoris\n1 2\n2 1\n");
		voting_readCase(r);
		voting_clearCandNames();
		CPPUNIT_ASSERT(candNames[1] == "");
		CPPUNIT_ASSERT(candNames[2] == "");
	}
	
	void test_voting_clearCandNames_3(){
		std::istringstream r("3\nMitch\nBoris\nSally\n1 2 3\n2 1 3\n3 1 2\n1 2 3\n");
		voting_readCase(r);
		voting_clearCandNames();
		CPPUNIT_ASSERT(candNames[1] == "");
		CPPUNIT_ASSERT(candNames[2] == "");
		CPPUNIT_ASSERT(candNames[3] == "");
	}
	
	// --------------------------
    // test voting_printWinner
    // --------------------------
	
	void test_voting_printWinner_1(){
		std::istringstream r("3\nMitch\nBoris\nSally1 2 3\n2 1 3\n3 1 2\n1 2 3\n");
		voting_readCase(r);
                std::ostringstream w;
                int index = 1;
                voting_printWinner(w, index);
                CPPUNIT_ASSERT(w.str() == "Mitch");
	}
	
	void test_voting_printWinner_2(){
		std::istringstream r("3\nMitch\nBoris\nSally\n1 2 3\n2 1 3\n3 1 2\n1 2 3\n");
		voting_readCase(r);
                std::ostringstream w;
                int index = 2;
                voting_printWinner(w, index);
                CPPUNIT_ASSERT(w.str() == "Boris");
	}
	
	void test_voting_printWinner_3(){
		std::istringstream r("3\nMitch\nBoris\nSally\n1 2 3\n2 1 3\n3 1 2\n1 2 3\n");
		voting_readCase(r);
                std::ostringstream w;
                int index = 3;
                voting_printWinner(w, index);
                CPPUNIT_ASSERT(w.str() == "Sally");
	}	
	
	// --------------------------
    // test voting_analyseBallots
    // --------------------------
	
	void test_voting_analyseBallots_1(){
                voting_clearBallots();
		std::istringstream r("2\nMitch\nBoris\n1 2\n1 2\n");
		voting_readCase(r);
                unsigned int a;
                unsigned int b;
		int c = voting_analyseBallots(a,b);
		CPPUNIT_ASSERT(c == 1);
	}
	
	void test_voting_analyseBallots_2(){
                voting_clearBallots();
		std::istringstream r("2\nMitch\nBoris\n1 2\n2 1\n");
		voting_readCase(r);
                unsigned int a;
                unsigned int b;
		int c = voting_analyseBallots(a,b);
		CPPUNIT_ASSERT(c == -1);
	}
	
	void test_voting_analyseBallots_3(){
                voting_clearBallots();
		std::istringstream r("3\nMitch\nBoris\nSally\n1 2 3\n2 1 3\n3 1 2\n1 2 3\n");
		voting_readCase(r);
                unsigned int a;
                unsigned int b;
		int c = voting_analyseBallots(a,b);
		CPPUNIT_ASSERT(c == 0);
	}
	
	// --------------------------
    // test voting_reassignLosers
    // --------------------------

	void test_voting_reassignLosers_1(){
                voting_clearBallots();
                totalBallots = 0;
		std::istringstream r("3\nMitch\nBoris\nSally\n1 2 3\n2 1 3\n3 1 2\n1 2 3\n");
		voting_readCase(r);
                unsigned int loser = 1;
		voting_reassignLosers(loser);
		CPPUNIT_ASSERT(ballots.at(1).size() == 4);
		CPPUNIT_ASSERT(ballots.at(2).size() == 0);
		CPPUNIT_ASSERT(ballots.at(3).size() == 0);
	}
	
	void test_voting_reassignLosers_2(){
                voting_clearBallots();
                totalBallots = 0;
		std::istringstream r("3\nMitch\nBoris\nSally\n1 2 3\n2 1 3\n1 2 3\n");
		voting_readCase(r);
                unsigned int loser = 1;
		voting_reassignLosers(loser);
		CPPUNIT_ASSERT(ballots.at(1).size() == 3);
		CPPUNIT_ASSERT(ballots.at(2).size() == 0);
		CPPUNIT_ASSERT(ballots.at(3).size() == 0);
	}
	
	void test_voting_reassignLosers_3(){
                voting_clearBallots();
		std::istringstream r("3\nMitch\nBoris\nSally\n1 2 3\n2 1 3\n3 1 2\n1 2 3\n1 2 3\n2 1 3\n");
		voting_readCase(r);
                unsigned int loser = 1;
		voting_reassignLosers(loser);
		CPPUNIT_ASSERT(ballots.at(1).size() == 4);
		CPPUNIT_ASSERT(ballots.at(2).size() == 2);
		CPPUNIT_ASSERT(ballots.at(3).size() == 0);
	}	
		
	// --------------------------
    // test voting_findWinners
    // --------------------------
	
	void test_voting_findWinners_1(){
                voting_clearBallots();
		std::istringstream r("2\nMitch\nBoris\n1 2\n1 2\n");
		voting_readCase(r);
		std::ostringstream w;
		voting_findWinners(w);
		CPPUNIT_ASSERT(w.str() == "Mitch");
	}
	
	void test_voting_findWinners_2(){
                voting_clearBallots();
		std::istringstream r("2\nMitch\nBoris\n1 2\n2 1\n");
		voting_readCase(r);
		std::ostringstream w;
		voting_findWinners(w);
		CPPUNIT_ASSERT(w.str() == "Mitch\nBoris");
	}
	
	void test_voting_findWinners_3(){
                voting_clearBallots();
		std::istringstream r("3\nMitch\nBoris\nSally\n1 2 3\n2 1 3\n3 1 2\n1 2 3\n");
		voting_readCase(r);
		std::ostringstream w;
		voting_findWinners(w);
		CPPUNIT_ASSERT(w.str() == "Mitch");
	}

	// --------------------------
    // test voting_solve
    // --------------------------

	void test_voting_solve_1(){
		std::istringstream r("1\n\n2\nMitch\nBoris\n1 2\n1 2\n");
		std::ostringstream w;
		voting_solve(r,w);
		CPPUNIT_ASSERT(w.str() == "Mitch");	
	}
	
	void test_voting_solve_2(){
		std::istringstream r("1\n\n2\nMitch\nBoris\n1 2\n2 1\n");
		std::ostringstream w;
		voting_solve(r,w);
		CPPUNIT_ASSERT(w.str() == "Mitch\nBoris");	
	}
	
	void test_voting_solve_3(){
		std::istringstream r("1\n\n3\nMitch\nBoris\nSally\n1 2 3\n2 1 3\n3 1 2\n1 2 3\n");
		std::ostringstream w;
		voting_solve(r,w);
		CPPUNIT_ASSERT(w.str() == "Mitch");	
	}

    // --------------------------
    // suite
    // ---------------------------

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_voting_readNumCases_1); 
	CPPUNIT_TEST(test_voting_readNumCases_2); 
	CPPUNIT_TEST(test_voting_readNumCases_3);
        CPPUNIT_TEST(test_voting_clearBallots_1);
	CPPUNIT_TEST(test_voting_clearBallots_2);
	CPPUNIT_TEST(test_voting_clearBallots_3);
	CPPUNIT_TEST(test_voting_readCase_1);
	CPPUNIT_TEST(test_voting_readCase_2);
	CPPUNIT_TEST(test_voting_readCase_3);
	CPPUNIT_TEST(test_voting_clearCandNames_1);
	CPPUNIT_TEST(test_voting_clearCandNames_2);
	CPPUNIT_TEST(test_voting_clearCandNames_3);
	CPPUNIT_TEST(test_voting_printWinner_1);
	CPPUNIT_TEST(test_voting_printWinner_2);
	CPPUNIT_TEST(test_voting_printWinner_3);
	CPPUNIT_TEST(test_voting_analyseBallots_1);
	CPPUNIT_TEST(test_voting_analyseBallots_2);
	CPPUNIT_TEST(test_voting_analyseBallots_3);
	CPPUNIT_TEST(test_voting_reassignLosers_1);
	CPPUNIT_TEST(test_voting_reassignLosers_2);
	CPPUNIT_TEST(test_voting_reassignLosers_3);
	CPPUNIT_TEST(test_voting_findWinners_1);
	CPPUNIT_TEST(test_voting_findWinners_2);
	CPPUNIT_TEST(test_voting_findWinners_3);
	CPPUNIT_TEST(test_voting_solve_1);
	CPPUNIT_TEST(test_voting_solve_2);
	CPPUNIT_TEST(test_voting_solve_3);
    CPPUNIT_TEST_SUITE_END();};

// ----------------
// main
// ----------------

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
 