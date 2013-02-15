

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
    // -------------
	// voting_solve
	// -------------

    void test_solve1 () {
		std::istringstream r("1\n\n2\ne1\ne2\n1 2\n1 2\n");
        std::ostringstream w;
        bool res = voting_solve(r, w);		
        CPPUNIT_ASSERT(res);}
		
	void test_solve2 () {
        std::istringstream r("1\n\n2\ne1\ne2\n1 2\n2 1\n");
        std::ostringstream w;
        bool res = voting_solve(r, w);
        CPPUNIT_ASSERT(res);}

		
	void test_solve3 () {
        std::istringstream r("1\n\n3\ne1\ne2\ne3\n2 1 3\n3 2 1\n1 3 2\n3 1 2\n2 3 1\n");
        std::ostringstream w;
        bool res = voting_solve(r, w);
        CPPUNIT_ASSERT(res);}


	// ------------
	// voting_read
	// ------------
		
	void test_read1 () {
		std::istringstream r("1\n\n2\ne1\ne2\n1 2\n");        
		int numCand;
		int voters;
		vector<string> cands(20);
		vector<list<int> > ballots(1000);
        const bool b = voting_read(r,numCand,voters,cands,ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(numCand ==    1);}

	void test_read2 () {
        std::istringstream r("1\n\n2\ne1\ne2\n1 2\n2 1\n1 2\n");        
		int numCand;
		int voters;
		vector<string> cands(20);
		vector<list<int> > ballots(1000);
        const bool b = voting_read(r,numCand,voters,cands,ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(numCand ==    1);}
		
	void test_read3 () {
        std::istringstream r("1\n\n2\ne1\ne2\n1 2\n2 1\n");        
		int numCand;
		int voters;
		vector<string> cands(20);
		vector<list<int> > ballots(1000);
        const bool b = voting_read(r,numCand,voters,cands,ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(numCand ==    1);}
		
	// ------------
	// voting_eval
	// ------------
	
	void test_eval1 () {
		int numCand = 1;
		vector<string> candidates(1);
		candidates[0] = ("e1");
		
		vector<list<int> > votes(1);
		votes[0].push_back(1);
		const bool b = voting_eval(numCand,candidates,votes);
		CPPUNIT_ASSERT(b == true);}
		
	void test_eval2 () {
        int numCand = 2;
		vector<string> candidates(2);
		candidates[0] = ("e1");
		candidates[1] = ("e2");
		
		vector<list<int> > votes(3);
		votes[0].push_back(1);
		votes[0].push_back(2);
	
		votes[1].push_back(2);
		votes[1].push_back(1);
		
		votes[2].push_back(2);
		votes[2].push_back(1);
		const bool b = voting_eval(numCand,candidates,votes);
		CPPUNIT_ASSERT(b == true);}
		
	void test_eval3 () {
        int numCand = 1;
		vector<string> candidates(3);
		candidates[0] = ("e1");
		candidates[1] = ("e2");
		candidates[2] = ("e3");
		
		vector<list<int> > votes(2);
		votes[0].push_back(1);
		votes[0].push_back(2);
		votes[0].push_back(3);
	
		votes[1].push_back(3);
		votes[1].push_back(2);
		votes[1].push_back(1);
		
		const bool b = voting_eval(numCand,candidates,votes);
		CPPUNIT_ASSERT(b == true);}
		
	// ------------
	// findWinner
	// ------------
	
	void test_findWinner1 () {
		int numCand = 1;
		int c = 3;
		vector<Candidate> cands(1);
		
		cands[0].setName("e1");
		cands[0].assignBallot();
		cands[0].assignBallot();
		
		const bool b = findWinner(numCand, c, cands);
		CPPUNIT_ASSERT(b == true);
        }
		
	void test_findWinner2 () {
        int numCand = 1;
		int c = 3;
		vector<Candidate> cands(1);
		
		cands[0].setName("e1");
		cands[0].assignBallot();
		
		
		const bool b = findWinner(numCand, c, cands);
		CPPUNIT_ASSERT(b == false);
        }
		
	void test_findWinner3 () {
        int numCand = 1;
		int c = 11;
		vector<Candidate> cands(1);
		
		cands[0].setName("e1");
		cands[0].assignBallot();
		cands[0].assignBallot();
		cands[0].assignBallot();
		cands[0].assignBallot();
		cands[0].assignBallot();
		
		
		const bool b = findWinner(numCand, c, cands);
		CPPUNIT_ASSERT(b == false);
        }
		
	
		
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_solve1);
	CPPUNIT_TEST(test_solve2);
	CPPUNIT_TEST(test_solve3);
	
	CPPUNIT_TEST(test_read1);
	CPPUNIT_TEST(test_read2);
	CPPUNIT_TEST(test_read3);
	
	CPPUNIT_TEST(test_eval1);
	CPPUNIT_TEST(test_eval2);
	CPPUNIT_TEST(test_eval3);
	
	CPPUNIT_TEST(test_findWinner1);
	CPPUNIT_TEST(test_findWinner2);
	CPPUNIT_TEST(test_findWinner3);
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