/*
 * Doug Goldstein, UTEID: ddg625, CSID: ddg625
 * Cameron Bielstein, UTEID: ctb677, CSID: cameronb
 */

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
struct TestVoting : CppUnit::TestFixture
{
	// ----
	// read
	// ----
	void test_read_1 ()
	{
		std::istringstream r("test\n");
		string line;
		const bool b = voting_read(r, line);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(line == "test");
	}
	void test_read_2 ()
	{
		std::istringstream r("1 2 3 4 5\n");
		string line;
		const bool b = voting_read(r, line);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(line == "1 2 3 4 5");
	}
	void test_read_3 ()
	{
		std::istringstream r("\n");
		string line;
		const bool b = voting_read(r, line);
		CPPUNIT_ASSERT(b == false);
	}
	
	
	// -----------
	// parse_names
	// -----------
	void test_parse_names_1 ()
	{
		std::istringstream r("Cameron\nDoug\nHello\n");
		Candidate temp;
		vector<Candidate> candidates(3, temp);
		voting_parse_names(r, candidates);
		CPPUNIT_ASSERT(candidates[0].name == "Cameron");
		CPPUNIT_ASSERT(candidates[1].name == "Doug");
		CPPUNIT_ASSERT(candidates[2].name == "Hello");
	}
	void test_parse_names_2 ()
	{
		std::istringstream r("Hello World\n");
		Candidate temp;
		vector<Candidate> candidates(1, temp);
		voting_parse_names(r, candidates);
		CPPUNIT_ASSERT(candidates[0].name == "Hello World");
	}
	void test_parse_names_3 () {
		std::istringstream r("Cameron\nDoug\nHello World\nJack\nJill\nBen\nFlo\n");
		Candidate temp;
		vector<Candidate> candidates(7, temp);
		voting_parse_names(r, candidates);
		CPPUNIT_ASSERT(candidates[0].name == "Cameron");
		CPPUNIT_ASSERT(candidates[1].name == "Doug");
		CPPUNIT_ASSERT(candidates[2].name == "Hello World");
		CPPUNIT_ASSERT(candidates[3].name == "Jack");
		CPPUNIT_ASSERT(candidates[4].name == "Jill");
		CPPUNIT_ASSERT(candidates[5].name == "Ben");
		CPPUNIT_ASSERT(candidates[6].name == "Flo");
	}
	
	
	// -----------
	// parse_votes
	// -----------
	void test_parse_votes_1 ()
	{
		std::istringstream r("1 2 3\n");
		Candidate temp;
		vector<Candidate> candidates(3, temp);
		int i = voting_parse_votes(r, candidates);
		CPPUNIT_ASSERT(i == 1);
		CPPUNIT_ASSERT(candidates[0].votes.size() == 1u);
		CPPUNIT_ASSERT(candidates[1].votes.size() == 0u);
		CPPUNIT_ASSERT(candidates[2].votes.size() == 0u);                        
		CPPUNIT_ASSERT(candidates[0].votes[0][0] == 1);
		CPPUNIT_ASSERT(candidates[0].votes[0][1] == 2);
		CPPUNIT_ASSERT(candidates[0].votes[0][2] == 3);
	}
	void test_parse_votes_2 ()
	{
		std::istringstream r("1 2 3\n3 2 1\n2 3 1\n");
		Candidate temp;
		vector<Candidate> candidates(3, temp);
		int i = voting_parse_votes(r, candidates);
		CPPUNIT_ASSERT(i == 3);
		CPPUNIT_ASSERT(candidates[0].votes.size() == 1u);
		CPPUNIT_ASSERT(candidates[1].votes.size() == 1u);        
		CPPUNIT_ASSERT(candidates[2].votes.size() == 1u);
		CPPUNIT_ASSERT(candidates[0].votes[0][0] == 1);
		CPPUNIT_ASSERT(candidates[0].votes[0][1] == 2);
		CPPUNIT_ASSERT(candidates[0].votes[0][2] == 3);
		CPPUNIT_ASSERT(candidates[2].votes[0][0] == 3);
		CPPUNIT_ASSERT(candidates[2].votes[0][1] == 2);
		CPPUNIT_ASSERT(candidates[2].votes[0][2] == 1);
		CPPUNIT_ASSERT(candidates[1].votes[0][0] == 2);
		CPPUNIT_ASSERT(candidates[1].votes[0][1] == 3);
		CPPUNIT_ASSERT(candidates[1].votes[0][2] == 1);                               
	}
	void test_parse_votes_3 ()
	{
		std::istringstream r("1 2 3 4\n1 2 3 4\n2 1 3 4\n1 2 3 4\n");
		Candidate temp;
		vector<Candidate> candidates(4, temp);
		int i = voting_parse_votes(r, candidates);
		CPPUNIT_ASSERT(i == 4);
		CPPUNIT_ASSERT(candidates[0].votes.size() == 3u);
		CPPUNIT_ASSERT(candidates[1].votes.size() == 1u);
		CPPUNIT_ASSERT(candidates[2].votes.size() == 0u);        
		CPPUNIT_ASSERT(candidates[3].votes.size() == 0u);
		CPPUNIT_ASSERT(candidates[0].votes[0][0] == 1);
		CPPUNIT_ASSERT(candidates[0].votes[0][1] == 2);
		CPPUNIT_ASSERT(candidates[0].votes[0][2] == 3);
		CPPUNIT_ASSERT(candidates[0].votes[0][3] == 4);
		CPPUNIT_ASSERT(candidates[0].votes[1][0] == 1);
		CPPUNIT_ASSERT(candidates[0].votes[1][1] == 2);
		CPPUNIT_ASSERT(candidates[0].votes[1][2] == 3);
		CPPUNIT_ASSERT(candidates[0].votes[1][3] == 4);
		CPPUNIT_ASSERT(candidates[1].votes[0][0] == 2);
		CPPUNIT_ASSERT(candidates[1].votes[0][1] == 1);
		CPPUNIT_ASSERT(candidates[1].votes[0][2] == 3);
		CPPUNIT_ASSERT(candidates[1].votes[0][3] == 4);
		CPPUNIT_ASSERT(candidates[0].votes[2][0] == 1);
		CPPUNIT_ASSERT(candidates[0].votes[2][1] == 2);
		CPPUNIT_ASSERT(candidates[0].votes[2][2] == 3);
		CPPUNIT_ASSERT(candidates[0].votes[2][3] == 4);        
	}  
	
	
	// --------
	// isWinner
	// --------
	void test_isWinner_1 ()
	{
		Candidate temp;
		vector<Candidate> candidates(2, temp);
		vector<int> tempBallot(2, 0);
		tempBallot[0] = 1;
		tempBallot[1] = 2;
		candidates[0].votes.push_back(tempBallot);
		tempBallot[0] = 2;
		tempBallot[1] = 1;
		candidates[1].votes.push_back(tempBallot);
		tempBallot[0] = 1;
		tempBallot[1] = 2;
		candidates[0].votes.push_back(tempBallot);				
		bool b = voting_isWinner(candidates, 3);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(candidates[0].inRace == true);
		CPPUNIT_ASSERT(candidates[1].inRace == false);        
	}
	void test_isWinner_2 ()
	{
		Candidate temp;
		vector<Candidate> candidates(2, temp);
		vector<int> tempBallot(2, 0);
		tempBallot[0] = 1;
		tempBallot[1] = 2;
		candidates[0].votes.push_back(tempBallot);
		tempBallot[0] = 1;
		tempBallot[1] = 2;
		candidates[0].votes.push_back(tempBallot);
		tempBallot[0] = 2;
		tempBallot[1] = 1;
		candidates[1].votes.push_back(tempBallot);
		tempBallot[0] = 2;
		tempBallot[1] = 1;
		candidates[1].votes.push_back(tempBallot);				
		bool b = voting_isWinner(candidates, 4);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(candidates[0].inRace == true);
		CPPUNIT_ASSERT(candidates[1].inRace == true);        
	}
	void test_isWinner_3 ()
	{
		Candidate temp;
		vector<Candidate> candidates(4, temp);
		vector<int> tempBallot(4, 0);
		tempBallot[0] = 1;
		tempBallot[1] = 2;
		tempBallot[2] = 3;
		tempBallot[3] = 4;
		candidates[0].votes.push_back(tempBallot);
		tempBallot[0] = 1;
		tempBallot[1] = 2;
		tempBallot[2] = 3;
		tempBallot[3] = 4;
		candidates[0].votes.push_back(tempBallot);
		tempBallot[0] = 2;
		tempBallot[1] = 1;
		tempBallot[2] = 3;
		tempBallot[3] = 4;
		candidates[1].votes.push_back(tempBallot);
		tempBallot[0] = 3;
		tempBallot[1] = 1;
		tempBallot[2] = 2;
		tempBallot[3] = 4;
		candidates[2].votes.push_back(tempBallot);
		tempBallot[0] = 4;
		tempBallot[1] = 1;
		tempBallot[2] = 2;
		tempBallot[3] = 3;
		candidates[3].votes.push_back(tempBallot);
		tempBallot[0] = 4;
		tempBallot[1] = 1;
		tempBallot[2] = 2;
		tempBallot[3] = 3;
		candidates[3].votes.push_back(tempBallot);
		bool b = voting_isWinner(candidates, 6);
		CPPUNIT_ASSERT(b == false);
		CPPUNIT_ASSERT(candidates[0].inRace == true);
		CPPUNIT_ASSERT(candidates[1].inRace == true);
		CPPUNIT_ASSERT(candidates[2].inRace == true);
		CPPUNIT_ASSERT(candidates[3].inRace == true);        
	}
	
	
	// ---------
	// findLoser
	// ---------
	void test_findLoser_1 ()
	{
		Candidate temp;
		vector<Candidate> candidates(4, temp);
		vector<int> tempBallot(4, 0);
		tempBallot[0] = 1;
		tempBallot[1] = 2;
		tempBallot[2] = 3;
		tempBallot[3] = 4;
		candidates[0].votes.push_back(tempBallot);
		tempBallot[0] = 1;
		tempBallot[1] = 2;
		tempBallot[2] = 3;
		tempBallot[3] = 4;
		candidates[0].votes.push_back(tempBallot);
		tempBallot[0] = 2;
		tempBallot[1] = 1;
		tempBallot[2] = 3;
		tempBallot[3] = 4;
		candidates[1].votes.push_back(tempBallot);
		tempBallot[0] = 3;
		tempBallot[1] = 1;
		tempBallot[2] = 2;
		tempBallot[3] = 4;
		candidates[2].votes.push_back(tempBallot);
		tempBallot[0] = 4;
		tempBallot[1] = 1;
		tempBallot[2] = 2;
		tempBallot[3] = 3;
		candidates[3].votes.push_back(tempBallot);
		tempBallot[0] = 4;
		tempBallot[1] = 1;
		tempBallot[2] = 2;
		tempBallot[3] = 3;
		candidates[3].votes.push_back(tempBallot);
		voting_findLoser(candidates);
		CPPUNIT_ASSERT(candidates[0].inRace == true);
		CPPUNIT_ASSERT(candidates[1].inRace == false);
		CPPUNIT_ASSERT(candidates[2].inRace == false);
		CPPUNIT_ASSERT(candidates[3].inRace == true); 
	}
	void test_findLoser_2 ()
	{
		Candidate temp;
		vector<Candidate> candidates(5, temp);
		vector<int> tempBallot(5, 0);
		tempBallot[0] = 1;
		tempBallot[1] = 2;
		tempBallot[2] = 3;
		tempBallot[3] = 4;
		tempBallot[4] = 5;
		candidates[0].votes.push_back(tempBallot);
		tempBallot[0] = 2;
		tempBallot[1] = 1;
		tempBallot[2] = 3;
		tempBallot[3] = 4;
		tempBallot[4] = 5;
		candidates[1].votes.push_back(tempBallot);
		tempBallot[0] = 3;
		tempBallot[1] = 1;
		tempBallot[2] = 2;
		tempBallot[3] = 4;
		tempBallot[4] = 5;
		candidates[2].votes.push_back(tempBallot);
		tempBallot[0] = 4;
		tempBallot[1] = 1;
		tempBallot[2] = 2;
		tempBallot[3] = 3;
		tempBallot[4] = 5;
		candidates[3].votes.push_back(tempBallot);
		voting_findLoser(candidates);
		CPPUNIT_ASSERT(candidates[0].inRace == true);
		CPPUNIT_ASSERT(candidates[1].inRace == true);
		CPPUNIT_ASSERT(candidates[2].inRace == true);
		CPPUNIT_ASSERT(candidates[3].inRace == true);
		CPPUNIT_ASSERT(candidates[4].inRace == false);
	}
	void test_findLoser_3 ()
	{
		Candidate temp;
		vector<Candidate> candidates(3, temp);
		vector<int> tempBallot(3, 0);
		tempBallot[0] = 1;
		tempBallot[1] = 2;
		tempBallot[2] = 3;
		candidates[0].votes.push_back(tempBallot);
		tempBallot[0] = 1;
		tempBallot[1] = 2;
		tempBallot[2] = 3;
		candidates[0].votes.push_back(tempBallot);
		tempBallot[0] = 1;
		tempBallot[1] = 2;
		tempBallot[2] = 3;
		candidates[0].votes.push_back(tempBallot);
		tempBallot[0] = 2;
		tempBallot[1] = 1;
		tempBallot[2] = 3;
		candidates[1].votes.push_back(tempBallot);
		tempBallot[0] = 2;
		tempBallot[1] = 1;
		tempBallot[2] = 3;
		candidates[1].votes.push_back(tempBallot);
		tempBallot[0] = 2;
		tempBallot[1] = 1;
		tempBallot[2] = 3;
		candidates[1].votes.push_back(tempBallot);
		tempBallot[0] = 3;
		tempBallot[1] = 1;
		tempBallot[2] = 2;
		candidates[2].votes.push_back(tempBallot);
		tempBallot[0] = 3;
		tempBallot[1] = 2;
		tempBallot[2] = 1;
		candidates[2].votes.push_back(tempBallot);
		voting_findLoser(candidates);
		CPPUNIT_ASSERT(candidates[0].inRace == true);
		CPPUNIT_ASSERT(candidates[1].inRace == true);
		CPPUNIT_ASSERT(candidates[2].inRace == false);
	}
	
	
	// -----
	// print
	// -----
	void test_print_1 ()
	{
		std::ostringstream w;
		Candidate temp;
		vector<Candidate> candidates(1, temp);
		candidates[0].name = "Hello World";
		voting_print(w, candidates);
		CPPUNIT_ASSERT(w.str() == "Hello World\n");
	}
	void test_print_2 ()
	{
		std::ostringstream w;
		Candidate temp;
		vector<Candidate> candidates(2, temp);
		candidates[0].name = "Hello World";
		candidates[0].inRace = false;
		candidates[1].name = "Goodbye World";
		voting_print(w, candidates);
		CPPUNIT_ASSERT(w.str() == "Goodbye World\n");
	}
	void test_print_3 ()
	{
		std::ostringstream w;
		Candidate temp;
		vector<Candidate> candidates(4, temp);
		candidates[0].name = "Doug";
		candidates[1].name = "Cameron";
		candidates[1].inRace = false;
		candidates[2].name = "Turing";
		candidates[3].name = "Djikstra";
		candidates[3].inRace = false;
		voting_print(w, candidates);
		CPPUNIT_ASSERT(w.str() == "Doug\nTuring\n");
	}
	
	
	// ----
	// case
	// ----
	void test_case_1 ()
	{
		std::istringstream r("3\nCameron\nDoug\nHello\n1 2 3\n1 2 3\n3 2 1\n\n");
		std::ostringstream w;
		voting_case(r, w);
		CPPUNIT_ASSERT(w.str() == "Cameron\n");
	}
	void test_case_2 ()
	{
		std::istringstream r("4\nDoug\nCameron\nTuring\nDjikstra\n1 2 3 4\n2 1 3 4\n3 1 2 4\n3 4 2 1\n2 1 3 4\n");
		std::ostringstream w;
		voting_case(r, w);
		CPPUNIT_ASSERT(w.str() == "Cameron\n");
	}
	void test_case_3 ()
	{
		std::istringstream r("2\nCameron\nDoug\n1 2\n2 1\n\n");
		std::ostringstream w;
		voting_case(r, w);
		CPPUNIT_ASSERT(w.str() == "Cameron\nDoug\n");
	}  
	
	
	// -----
	// suite
	// -----
	CPPUNIT_TEST_SUITE(TestVoting);
	CPPUNIT_TEST(test_read_1);
	CPPUNIT_TEST(test_read_2);
	CPPUNIT_TEST(test_read_3);
	CPPUNIT_TEST(test_parse_names_1);
	CPPUNIT_TEST(test_parse_names_2);
	CPPUNIT_TEST(test_parse_names_3);
	CPPUNIT_TEST(test_parse_votes_1);
	CPPUNIT_TEST(test_parse_votes_2);
	CPPUNIT_TEST(test_parse_votes_3);
	CPPUNIT_TEST(test_isWinner_1); 
	CPPUNIT_TEST(test_isWinner_2); 
	CPPUNIT_TEST(test_isWinner_3);
	CPPUNIT_TEST(test_findLoser_1);
	CPPUNIT_TEST(test_findLoser_2);
	CPPUNIT_TEST(test_findLoser_3);
	CPPUNIT_TEST(test_print_1);
	CPPUNIT_TEST(test_print_2);
	CPPUNIT_TEST(test_print_3);
	CPPUNIT_TEST(test_case_1);
	CPPUNIT_TEST(test_case_2);
	CPPUNIT_TEST(test_case_3);
	CPPUNIT_TEST_SUITE_END();
};


// ----
// main
// ----
int main ()
{
	using namespace std;
	ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
	cout << "TestVoting.c++" << endl;
	
	CppUnit::TextTestRunner tr;
	tr.addTest(TestVoting::suite());
	tr.run();
	
	cout << "Done." << endl;
	return 0;
}
