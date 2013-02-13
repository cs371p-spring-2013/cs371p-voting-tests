
/*
To test the program:
% ls /usr/include/cppunit/
...
TestFixture.h
...
% locate libcppunit.a
/usr/lib/libcppunit.a
% g++ -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz.c++.app -lcppunit -ldl
% valgrind TestCollatz.c++.app >& TestCollatz.c++.out
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

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {
    // ----
    // readNumElections
    // ----
    
    void test_readNumElections_1()
    {
    	std::istringstream r("1\n");
	int i;
	const bool b = readNumElections(r, i);
	CPPUNIT_ASSERT(b == true);
	CPPUNIT_ASSERT(i == 1);
    }

    void test_readNumElections_2()
    {
    	std::istringstream r("2\n");
	int i;
	const bool b = readNumElections(r, i);
	CPPUNIT_ASSERT(b == true);
	CPPUNIT_ASSERT(i == 2);
    }

    void test_readNumElections_3()
    {
    	std::istringstream r("20\n");
	int i;
	const bool b = readNumElections(r, i);
	CPPUNIT_ASSERT(b == true);
	CPPUNIT_ASSERT(i == 20);
    }

    // ----
    // readNumCandidates
    // ----
    void test_readNumCandidates_1()
    {
    	std::istringstream r("1\n");
	int i;
	const bool b = readNumCandidates(r, i);
	CPPUNIT_ASSERT(b == true);
	CPPUNIT_ASSERT(i == 1);
    }

    void test_readNumCandidates_2()
    {
    	std::istringstream r("5\n");
	int i;
	const bool b = readNumCandidates(r, i);
	CPPUNIT_ASSERT(b == true);
	CPPUNIT_ASSERT(i == 5);
    }

    void test_readNumCandidates_3()
    {
    	std::istringstream r("20\n");
	int i;
	const bool b = readNumCandidates(r, i);
	CPPUNIT_ASSERT(b == true);
	CPPUNIT_ASSERT(i == 20);
    }


    // ----
    // readCandidates
    // ----


    void test_readCandidates_1()
    {
    	vector<Candidate> candidates;
	std::istringstream r("A\nB\n");
	int numCandidates = 2;
	const bool b = readCandidates(candidates, r, numCandidates);
	CPPUNIT_ASSERT(b == true);
    	int size = candidates.size();
	CPPUNIT_ASSERT(size == 2);
	CPPUNIT_ASSERT(candidates[0].getName() == "A");
	CPPUNIT_ASSERT(candidates[1].getName() == "B");
    }
    void test_readCandidates_2()
    {
    	vector<Candidate> candidates;
	std::istringstream r("A\nB\nC\n");
	int numCandidates = 3;
	const bool b = readCandidates(candidates, r, numCandidates);
	CPPUNIT_ASSERT(b == true);
    	int size = candidates.size();
	CPPUNIT_ASSERT(size == 3);
	CPPUNIT_ASSERT(candidates[0].getName() == "A");
	CPPUNIT_ASSERT(candidates[1].getName() == "B");
	CPPUNIT_ASSERT(candidates[2].getName() == "C");
    }
    void test_readCandidates_3()
    {
    	vector<Candidate> candidates;
	std::istringstream r("A\nB\nC\nD\n");
	int numCandidates = 4;
	const bool b = readCandidates(candidates, r, numCandidates);
	CPPUNIT_ASSERT(b == true);
    	int size = candidates.size();
	CPPUNIT_ASSERT(size == 4);
	CPPUNIT_ASSERT(candidates[0].getName() == "A");
	CPPUNIT_ASSERT(candidates[1].getName() == "B");
	CPPUNIT_ASSERT(candidates[2].getName() == "C");
	CPPUNIT_ASSERT(candidates[3].getName() == "D");
    }
    
    // -----
    // solve
    // -----

    void test_solve_1 () {
    	vector<Candidate> candidates;
        std::istringstream r("3\nA\nB\nC\n1 2 3\n1 2 3\n1 2 3\n");
        std::ostringstream w;
        const bool b = solve(candidates, r, w);
	CPPUNIT_ASSERT(w.str() == "A\n");
	CPPUNIT_ASSERT(b == true);}
    
    void test_solve_2 () {
        vector<Candidate> candidates;
	std::istringstream r("1\nA\n1\n");
        std::ostringstream w;
	const bool b = solve(candidates, r, w);
	CPPUNIT_ASSERT(w.str() == "A\n");
	CPPUNIT_ASSERT(b == true);}
    
    
    void test_solve_3 () {
        vector<Candidate> candidates;
	std::istringstream r("2\nA\nB\n1 2\n2 1\n");
        std::ostringstream w;
	const bool b = solve(candidates, r, w);
	CPPUNIT_ASSERT(w.str() == "A\nB\n");
   	CPPUNIT_ASSERT(b == true);} 
    
    void test_solveAll_1 () {
        vector<Candidate> candidates;
	std::istringstream r("1\n\n3\nA\nB\nC\n1 2 3\n1 2 3\n1 2 3\n");
        std::ostringstream w;
	const bool b = solveAll(r, w);
	CPPUNIT_ASSERT(w.str() == "A\n");
	CPPUNIT_ASSERT(b == true);}
    
    
    void test_solveAll_2 () {
	std::istringstream r("2\n\n3\nA\nB\nC\n1 2 3\n1 2 3\n1 2 3\n\n2\nA\nB\n1 2\n1 2\n");
        std::ostringstream w;
	const bool b = solveAll(r, w);
	CPPUNIT_ASSERT(w.str() == "A\n\nA\n");
	CPPUNIT_ASSERT(b == true);}
    
    
    void test_solveAll_3 () {
	std::istringstream r("2\n\n3\nA\nB\nC\n1 2 3\n1 2 3\n1 2 3\n\n1\nA\n1");
        std::ostringstream w;
	const bool b = solveAll(r, w);
	CPPUNIT_ASSERT(w.str() == "A\nA\n");
	CPPUNIT_ASSERT(b == true);}
    
    
    void test_checkWinner_1 () {
        vector<Candidate> candidates;
	
	Candidate one = Candidate("A", 1);
	Ballot A = Ballot();
	A.addVote(1);
	one.addBallot(A);

	candidates.push_back(one);

	std::ostringstream w;
	const bool b = checkWinner(candidates, w);
	CPPUNIT_ASSERT(b == true);}


    void test_checkWinner_2 () {
        vector<Candidate> candidates;
	

	Candidate one = Candidate("A", 1);
	Ballot A = Ballot();
	A.addVote(1);
	one.addBallot(A);
	
	candidates.push_back(one);
	
	std::ostringstream w;
	const bool b = checkWinner(candidates, w);
	CPPUNIT_ASSERT(w.str() == "A\n");
	CPPUNIT_ASSERT(b == true);}


    void test_checkWinner_3 () {
        vector<Candidate> candidates;
	
	Candidate one = Candidate("A", 1);
	Ballot A = Ballot();
	A.addVote(1);
	one.addBallot(A);

	Candidate two = Candidate("B", 2);

	candidates.push_back(one);
	candidates.push_back(two);

	std::ostringstream w;
	const bool b = checkWinner(candidates, w);
	CPPUNIT_ASSERT(b == true);}


    void test_readBallots_1()
    {
	vector<Candidate> candidates;
	Candidate one = Candidate("A", 1);
	Candidate two = Candidate("B", 2);
	candidates.push_back(one);
	candidates.push_back(two);
	std::istringstream r("1 2\n2 1\n");
	const bool b = readBallots(candidates, r);
	CPPUNIT_ASSERT(b == true);
	CPPUNIT_ASSERT(candidates[0].getNumBallots() == 1);
	CPPUNIT_ASSERT(candidates[1].getNumBallots() == 1);
    }

    void test_readBallots_2()
    {
    	vector<Candidate> candidates;
	Candidate one = Candidate("A", 1);
	Candidate two = Candidate("B", 2);
	candidates.push_back(one);
	candidates.push_back(two);
    	std::istringstream r("1 2\n1 2\n");
	const bool b = readBallots(candidates, r);
	CPPUNIT_ASSERT(b == true);
	CPPUNIT_ASSERT(candidates[1].getNumBallots() == 0);
    }

    void test_readBallots_3()
    {
    	vector<Candidate> candidates;
	Candidate one = Candidate("A", 1);
	Candidate two = Candidate("B", 2);
	Candidate three = Candidate("C", 3);
	candidates.push_back(one);
	candidates.push_back(two);
	candidates.push_back(three);
    	std::istringstream r("1 2 3\n1 2 3\n");
	const bool b = readBallots(candidates, r);
	CPPUNIT_ASSERT(b == true);
	CPPUNIT_ASSERT(candidates[0].getNumBallots() == 2);
	CPPUNIT_ASSERT(candidates[1].getNumBallots() == 0);
	CPPUNIT_ASSERT(candidates[2].getNumBallots() == 0);
    }

    void test_readInput_1()
    {
    	vector<Candidate> candidates;
    	std::istringstream r("2\nA\nB\n1 2\n2 1\n");
	const bool b = readInput(candidates, r);
	CPPUNIT_ASSERT(b == true);
    }

    void test_readInput_2()
    {
    	vector<Candidate> candidates;
    	std::istringstream r("2\nA\nB\n1 2\n2 1\n");
	const bool b = readInput(candidates, r);
	CPPUNIT_ASSERT(b == true);
    }


    void test_readInput_3()
    {
    	vector<Candidate> candidates;
    	std::istringstream r("2\nA\nB\n1 2\n2 1\n");
	const bool b = readInput(candidates, r);
	CPPUNIT_ASSERT(b == true);
    }

    void test_Ballot_1()
    {
	    Ballot b = Ballot();
	    b.addVote(1);
	    CPPUNIT_ASSERT(b.getVote() == 1);
    }

    void test_Ballot_2()
    {
	Ballot b = Ballot();
	b.addVote(1);
	b.addVote(2);
	b.advanceVote();
	CPPUNIT_ASSERT(b.getVote() == 2);
    }

    void test_Ballot_3()
    {
	    Ballot b = Ballot();
	    b.addVote(1);
	    b.addVote(2);
	    b.addVote(3);

	    b.advanceVote();
	    b.advanceVote();

	    CPPUNIT_ASSERT(b.getVote() == 3);
    }

    void test_Candidate_1()
    {
	    Candidate candidate = Candidate("Name", 1);
	    CPPUNIT_ASSERT(candidate.getName() == "Name");
    }

    void test_Candidate_2()
    {
	    Candidate candidate = Candidate("Name", 1);
	    Ballot b = Ballot();
	    b.addVote(1);
	    
	    candidate.addBallot(b);
	    CPPUNIT_ASSERT(candidate.getNumBallots() == 1);
    }

    void test_Candidate_3()
    {
	    Candidate candidate = Candidate("Name", 1);
	    
	    CPPUNIT_ASSERT(candidate.isRunning() == true);
	    candidate.dropout();
	    CPPUNIT_ASSERT(candidate.isRunning() == false);
    }
    
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_readNumElections_1);
    CPPUNIT_TEST(test_readNumElections_2);
    CPPUNIT_TEST(test_readNumElections_3);
    CPPUNIT_TEST(test_readNumCandidates_1);
    CPPUNIT_TEST(test_readNumCandidates_2);
    CPPUNIT_TEST(test_readNumCandidates_3);
    CPPUNIT_TEST(test_readCandidates_1);
    CPPUNIT_TEST(test_readCandidates_2);
    CPPUNIT_TEST(test_readCandidates_3);
    CPPUNIT_TEST(test_readBallots_1);
    CPPUNIT_TEST(test_readBallots_2);
    CPPUNIT_TEST(test_readBallots_3);
    CPPUNIT_TEST(test_readInput_1);
    CPPUNIT_TEST(test_readInput_2);
    CPPUNIT_TEST(test_readInput_3);
    CPPUNIT_TEST(test_solveAll_1);
    CPPUNIT_TEST(test_solveAll_2);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_checkWinner_1);
    CPPUNIT_TEST(test_checkWinner_2);
    CPPUNIT_TEST(test_checkWinner_3);
    CPPUNIT_TEST(test_Ballot_1);
    CPPUNIT_TEST(test_Ballot_2);
    CPPUNIT_TEST(test_Ballot_3);
    CPPUNIT_TEST(test_Candidate_1);
    CPPUNIT_TEST(test_Candidate_2);
    CPPUNIT_TEST(test_Candidate_3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestCollatz.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
