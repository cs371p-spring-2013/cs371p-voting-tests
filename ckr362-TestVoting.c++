/** 
 * TestVoting.c++
 * cs371p-voting
 * 
 * Charles Kasey Reed
 * ckr362
 */

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"  
#include "cppunit/TextTestRunner.h"

#include "Voting.h"
using namespace std;
struct TestVoting: CppUnit::TestFixture {

	Election e; // The election for all our tests.

	/**
	 * Function to clear sizes/nums in struct. 
	 * @param elec the election struct to clear.
	 */
	void clearElection(Election &elec) {
		elec.numberOfBallots = 0;
		elec.numberOfCandidates = 0;
		elec.numberOfEliminatedCandidates = 0;
		for(short i = 0; i < MAX_CANDIDATES; i++) 
			elec.ballot_buckets_size[i] = 0;
	}
	/**
	 * We define some of these for later use.
	 */ 
	
	

	void test_read() {
		// Simple Test Read
		istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n\
			1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
		
		clearElection(e);

 		bool result = voting_read(r, e);

 		short firstBallot[] = {1-1,2-1,3-1};
 		short *ballot = e.ballots[0];

 		string candidates[] = {"John Doe", "Jane Smith", "Sirhan Sirhan"};
 		CPPUNIT_ASSERT(equal(candidates, candidates+3, e.candidates));
 		//cout << ballot[0] << " " << ballot[1] << " " << ballot[2] << endl;
 		CPPUNIT_ASSERT(equal(ballot, ballot + 3, firstBallot));
		CPPUNIT_ASSERT(e.numberOfCandidates == 3);
		CPPUNIT_ASSERT(e.numberOfBallots == 5);

		CPPUNIT_ASSERT(result);
	}
	
	void test_read_1 () {		
		istringstream r("1\nThe Lone Candidate :(\n1");
		
		clearElection(e);

		bool result = voting_read(r, e);

		CPPUNIT_ASSERT(e.numberOfCandidates == 1);
		CPPUNIT_ASSERT(e.numberOfBallots == 1);
		CPPUNIT_ASSERT(e.candidates[0].compare("The Lone Candidate :(") == 0);
		CPPUNIT_ASSERT(e.ballot_buckets_size[0] == 1);
		
		CPPUNIT_ASSERT(result);	
	}

	void test_read_2() {
		istringstream r("3\nJohn Doe\nJane Smith\n\nSirhan Sirhan\n\
			1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
	
		clearElection(e);
		bool result = voting_read(r, e);
		CPPUNIT_ASSERT(!result);
	}

	void test_solve () {
		istringstream r("1\n\n1\nThe Lone Candidate :(\n1");
		ostringstream o;
		voting_solve(r, o);
		// cout << o.str() << endl;
		CPPUNIT_ASSERT(o.str().compare("The Lone Candidate :(\n") == 0);		
	}

	void test_solve_1 () {
		istringstream r("2\n\n1\nThe Lone Candidate :(\n1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n\
			1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
		ostringstream o;
		voting_solve(r, o);
		// cout << o.str() << endl;
		CPPUNIT_ASSERT(o.str().compare("The Lone Candidate :(\n\nJohn Doe\n") == 0);
		CPPUNIT_ASSERT(true);
	}

	void test_solve_2 () {
		istringstream r ("1\n\n4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n\
						2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
		ostringstream o;
		voting_solve(r,o);
		// cout << o.str() << endl;
		CPPUNIT_ASSERT(o.str().compare("Red\nGreen\n") == 0);
	}

	void test_print () {
		vector<string> winners;
		winners.push_back("Me");
		winners.push_back("You");

		ostringstream o;
		voting_print(o, winners);


		CPPUNIT_ASSERT(o.str().compare("Me\nYou"));
	}

	void test_print_1 () {
		vector<string> winners;
		winners.push_back("a");
		ostringstream o;
		voting_print(o, winners);
		CPPUNIT_ASSERT(o.str().compare("a"));
	}

	void test_print_2 () {
		vector<string> winners;
		winners.push_back("Mommy");
		winners.push_back("Daddy");
		winners.push_back("Granny");
		winners.push_back("Grampy");
		winners.push_back("La-a");
		ostringstream o;
		voting_print(o, winners);
		CPPUNIT_ASSERT(o.str().compare("Mommy\nDaddy\nGranny\nGrampy\nLa-a"));
	}

	void test_eval () {
		vector<string> winners;
		istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n\
			1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
		
		clearElection(e);
		bool result = voting_read(r, e);

		winners = voting_eval(e);
		CPPUNIT_ASSERT(winners.size() == 1);
		CPPUNIT_ASSERT(winners[0].compare("John Doe") == 0);
		CPPUNIT_ASSERT(result);
	}

	void test_eval_1 () {
		istringstream r("1\nThe Lone Candidate :(\n1");
		
		clearElection(e);
		bool result = voting_read(r, e);
		vector<string> winners = voting_eval(e);
		CPPUNIT_ASSERT(result);
		CPPUNIT_ASSERT(winners.size() == 1);
		CPPUNIT_ASSERT(winners[0].compare("The Lone Candidate :(") == 0);	}


	void test_eval_2 () {
		istringstream r ("4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n\
						2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
	
		clearElection(e);
		bool result = voting_read(r, e);

		vector<string> winners = voting_eval(e);
		CPPUNIT_ASSERT(result);
		CPPUNIT_ASSERT(winners.size() == 2);
		CPPUNIT_ASSERT(winners[0].compare("Red") == 0);
		CPPUNIT_ASSERT(winners[1].compare("Green") == 0);
	}
	
	void test_is_excluded () {
		// Number.
		istringstream r ("4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n\
						2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
		

		clearElection(e);
		bool result = voting_read(r, e);
		short t0, t1, t2, t3;
		t0 = 0; t1 = 1; t2 = 2; t3 = 3;

		bool test1 = !is_excluded(t0, e) && !is_excluded(t1, e) &&
			!is_excluded(t2, e) && !is_excluded(t3, e);

		voting_eval(e); 

		bool test2 = !is_excluded(t0, e) && !is_excluded(t1, e) &&
			is_excluded(t2, e) && is_excluded(t3, e); 

		CPPUNIT_ASSERT(test2);
		CPPUNIT_ASSERT(test1);
		CPPUNIT_ASSERT(e.numberOfEliminatedCandidates == 2);	
		CPPUNIT_ASSERT(result);
	}

	void test_is_excluded_1 () {
		istringstream r("1\nThe Lone Candidate :(\n1");
		clearElection(e);
		bool result = voting_read(r, e);
		short t0 = 0;

		bool test1 = !is_excluded(t0, e);
		voting_eval(e);
		bool test2 = !is_excluded(t0, e);
		CPPUNIT_ASSERT(test1 && test2);
		CPPUNIT_ASSERT(result);		
	}

	void test_is_excluded_2 () {
		istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n\
			1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
		clearElection(e);
		bool result = voting_read(r, e);
		short t0, t1, t2;
		t0 = 0; t1 = 1; t2 = 2;

		bool test1 = !is_excluded(t0, e) && !is_excluded(t1, e) &&
			!is_excluded(t2, e);

		voting_eval(e);
		// 									this guy has NOT been eliminated
		// 									he's just a loser HAHA
		bool test2 = !is_excluded(t0, e) && !is_excluded(t1, e) &&
			is_excluded(t2, e);
		CPPUNIT_ASSERT(test1 && test2 );
		CPPUNIT_ASSERT(result);
	}

	void test_eliminate_candidates () {
		// Number.
		istringstream r ("4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n\
						2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");

		clearElection(e);
		bool result = voting_read(r, e);

		voting_eval(e);

		// Blue and Orange should have been eliminated. 
		short numEliminated = e.numberOfEliminatedCandidates;

		CPPUNIT_ASSERT(numEliminated == 2);

		CPPUNIT_ASSERT(e.eliminated_candidates[0] == 2 && 
			e.eliminated_candidates[1] == 3);

		CPPUNIT_ASSERT(e.numberOfEliminatedCandidates == 2);	
		CPPUNIT_ASSERT(result);		
	}

	void test_eliminate_candidates_1 ()  {
		istringstream r("1\nThe Lone Candidate :(\n1");
		clearElection(e);
		bool result = voting_read(r, e);
		voting_eval(e);
		short numEliminated = e.numberOfEliminatedCandidates;
		CPPUNIT_ASSERT(numEliminated == 0);
		CPPUNIT_ASSERT(result);		
	}

	void test_eliminate_candidates_2 () {
		istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n\
			1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
		clearElection(e);
		bool result = voting_read(r, e);
		voting_eval(e);
		short numEliminated = e.numberOfEliminatedCandidates;
		CPPUNIT_ASSERT(numEliminated == 1);

		CPPUNIT_ASSERT(result);		
	}

	CPPUNIT_TEST_SUITE(TestVoting);
	CPPUNIT_TEST(test_read);
	CPPUNIT_TEST(test_read_1);
	CPPUNIT_TEST(test_read_2);
	CPPUNIT_TEST(test_solve);
	CPPUNIT_TEST(test_solve_1);
	CPPUNIT_TEST(test_solve_2);
	CPPUNIT_TEST(test_print);
	CPPUNIT_TEST(test_print_1);
	CPPUNIT_TEST(test_print_2);
	CPPUNIT_TEST(test_eval);
	CPPUNIT_TEST(test_eval_1);
	CPPUNIT_TEST(test_eval_2);
	CPPUNIT_TEST(test_is_excluded);
	CPPUNIT_TEST(test_is_excluded_1);
	CPPUNIT_TEST(test_is_excluded_2);
	CPPUNIT_TEST(test_eliminate_candidates);
	CPPUNIT_TEST(test_eliminate_candidates_1);
	CPPUNIT_TEST(test_eliminate_candidates_2);
	CPPUNIT_TEST_SUITE_END(); 

};

int main() {
 	
	ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
	cout << "TestVoting.c++" << endl;

	
	CppUnit::TextTestRunner tr; 
	tr.addTest(TestVoting::suite());
	tr.run(); 
	
	cout << "Done." << endl;
	return 0;
}
