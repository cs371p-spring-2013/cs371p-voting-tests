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
    // ----
    // read
    // ----

    void test_voting_read_1 () {
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
		int numBallots=0;
		int numCandidates;
        	struct Candidate candidates[20];
		int votes[1000][20];
        const bool b = voting_read(r, numCandidates, numBallots, candidates, votes);
	cout<< numBallots << endl;
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(numCandidates == 3);
        CPPUNIT_ASSERT(numBallots == 5);
		CPPUNIT_ASSERT(candidates[0].name.compare("John Doe") == 0); 
		CPPUNIT_ASSERT(candidates[1].name.compare("Jane Smith") == 0); 
		CPPUNIT_ASSERT(candidates[2].name.compare("Sirhan Sirhan") == 0); 
		CPPUNIT_ASSERT(votes[0][0] == 1); 
		CPPUNIT_ASSERT(votes[0][1] == 2); 
		CPPUNIT_ASSERT(votes[0][2] == 3); 
		CPPUNIT_ASSERT(votes[1][0] == 2); 
		CPPUNIT_ASSERT(votes[1][1] == 1); 
		CPPUNIT_ASSERT(votes[1][2] == 3);
		CPPUNIT_ASSERT(votes[2][0] == 2); 
		CPPUNIT_ASSERT(votes[2][1] == 3);
		CPPUNIT_ASSERT(votes[2][2] == 1);
		CPPUNIT_ASSERT(votes[3][0] == 1);
		CPPUNIT_ASSERT(votes[3][1] == 2);
		CPPUNIT_ASSERT(votes[3][2] == 3);
		CPPUNIT_ASSERT(votes[4][0] == 3);
		CPPUNIT_ASSERT(votes[4][1] == 1);
		CPPUNIT_ASSERT(votes[4][2] == 2);
		}

		void test_voting_read_2 () {
        std::istringstream r("5\nSirhan Sirhan\nJack Black\nBen Stiller\nJohn Doe\nJane Smith\n1 2 3 4 5\n5 2 1 3 4\n4 2 1 5 3\n1 2 3 4 5\n5 3 1 2 4");
		int numBallots=0;
		int numCandidates;
        	struct Candidate candidates[20];
		int votes[1000][20];
        const bool b = voting_read(r, numCandidates, numBallots, candidates, votes);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(numCandidates == 5);
        CPPUNIT_ASSERT(numBallots == 5);
		CPPUNIT_ASSERT(candidates[0].name.compare("Sirhan Sirhan") == 0); 
		CPPUNIT_ASSERT(candidates[1].name.compare("Jack Black") == 0); 
		CPPUNIT_ASSERT(candidates[2].name.compare("Ben Stiller") == 0);
		CPPUNIT_ASSERT(candidates[3].name.compare("John Doe") == 0);
		CPPUNIT_ASSERT(candidates[4].name.compare("Jane Smith") == 0); 
		CPPUNIT_ASSERT(votes[0][0] == 1); 
		CPPUNIT_ASSERT(votes[0][1] == 2); 
		CPPUNIT_ASSERT(votes[0][2] == 3);
		CPPUNIT_ASSERT(votes[0][3] == 4);
		CPPUNIT_ASSERT(votes[0][4] == 5);		   
		CPPUNIT_ASSERT(votes[1][0] == 5); 
		CPPUNIT_ASSERT(votes[1][1] == 2); 
		CPPUNIT_ASSERT(votes[1][2] == 1);
		CPPUNIT_ASSERT(votes[1][3] == 3);
		CPPUNIT_ASSERT(votes[1][4] == 4);
		CPPUNIT_ASSERT(votes[2][0] == 4); 
		CPPUNIT_ASSERT(votes[2][1] == 2);
		CPPUNIT_ASSERT(votes[2][2] == 1);
		CPPUNIT_ASSERT(votes[2][3] == 5); 
		CPPUNIT_ASSERT(votes[2][4] == 3);
		CPPUNIT_ASSERT(votes[3][0] == 1);
		CPPUNIT_ASSERT(votes[3][1] == 2);
		CPPUNIT_ASSERT(votes[3][2] == 3);
		CPPUNIT_ASSERT(votes[3][3] == 4);
		CPPUNIT_ASSERT(votes[3][4] == 5);		
		CPPUNIT_ASSERT(votes[4][0] == 5);
		CPPUNIT_ASSERT(votes[4][1] == 3);
		CPPUNIT_ASSERT(votes[4][2] == 1);
		CPPUNIT_ASSERT(votes[4][3] == 2); 
		CPPUNIT_ASSERT(votes[4][4] == 4); 
		}
		
		void test_voting_read_3 () {
        std::istringstream r("1\nSirhan Sirhan\n1\n1\n1\n1\n1\n1");
		int numBallots=0;
		int numCandidates;
        struct Candidate candidates[20];
		int votes[1000][20];
        const bool b = voting_read(r, numCandidates, numBallots, candidates, votes);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(numCandidates == 1);
        CPPUNIT_ASSERT(numBallots == 6);
		CPPUNIT_ASSERT(candidates[0].name.compare("Sirhan Sirhan") == 0); 
		CPPUNIT_ASSERT(votes[0][0] == 1); 
		CPPUNIT_ASSERT(votes[1][0] == 1);
		CPPUNIT_ASSERT(votes[2][0] == 1);
		CPPUNIT_ASSERT(votes[3][0] == 1);
		CPPUNIT_ASSERT(votes[4][0] == 1);
		CPPUNIT_ASSERT(votes[5][0] == 1);
		}
    // ----
    // eval
    // ----

    void test_voting_eval_1 () {
		struct Candidate candidates[20];
		candidates[0].name = "Jane Smith";
		candidates[1].name = "Joe Blow";
		candidates[2].name = "John Doe";
		string winner = "Jane Smith\nJoe Blow\n";
		int votes[1000][20] = {{2, 3, 1}, {1, 2, 3}, {3, 2, 1}, {2, 1, 3}, {1, 3, 2}, {3, 1, 2}, {2, 3, 1}, {1, 2, 3}};
	        string v = voting_eval(3, 8, candidates, votes);
		CPPUNIT_ASSERT(v.compare(winner) == 0);
		int totalVotes = candidates[0].votes.size() + candidates[1].votes.size() + candidates[2].votes.size(); 
		CPPUNIT_ASSERT(totalVotes == 8); 
		}

	void test_voting_eval_2 () {
		struct Candidate candidates[20];
		candidates[0].name = "Jane Smith";
		candidates[1].name = "Joe Blow";
		candidates[2].name = "John Doe";
		candidates[3].name = "John Smith";
		candidates[4].name =  "Sally Sue";
		string winner = "Sally Sue"; 
		int votes[1000][20] = {{5, 4, 3, 2, 1}, {5, 1, 2, 3, 4,}, {1, 2, 3, 4, 5}, {2, 3, 4, 5, 1}, {3, 2, 1, 4, 5}, {5, 3, 2, 1, 4}, {5, 1, 2, 3, 4}, {5, 2, 4, 1, 3}, {5, 3, 4, 1, 2}, {5, 1, 4, 2, 3}};
		string v = voting_eval(5, 10, candidates, votes);
		CPPUNIT_ASSERT(v.compare(winner+'\n') == 0);
		int totalVotes = candidates[0].votes.size()+ candidates[1].votes.size() + candidates[2].votes.size() + candidates[3].votes.size() + candidates[4].votes.size(); 
		CPPUNIT_ASSERT(totalVotes == 10);
		} 
	void test_voting_eval_3 () {
		struct Candidate candidates[20];
		candidates[0].name = "Red";
		candidates[1].name = "Green";
		candidates[2].name = "Blue";
		candidates[3].name = "Orange";
		string winner = "Red\nGreen\n"; 
		int votes[1000][20] = {{1, 2, 3, 4}, {2, 1, 3, 4}, {2, 3, 1, 4}, {1, 2, 3, 4}, {3, 4, 1, 2}, {4, 3, 2, 1}};
		string v = voting_eval(4, 6, candidates, votes); 
		CPPUNIT_ASSERT(v.compare(winner) == 0); 
		int totalVotes = candidates[0].votes.size() + candidates[1].votes.size() + candidates[2].votes.size(); 
		CPPUNIT_ASSERT(totalVotes == 6); }


    // -----
    // print
    // -----

    void test_voting_print_1 () {
        std::ostringstream w;
		string str = "This is a test of test of print";
        voting_print(w, str );
        CPPUNIT_ASSERT(w.str() == "This is a test of test of print");}

	void test_voting_print_2 () {
        std::ostringstream w;
		string str = "1\n\n2\nJohn Doe\nJane Smith\n1 2\n1 2\n2 1\n2 1\n1 2";
        voting_print(w, str );
        CPPUNIT_ASSERT(w.str() == "1\n\n2\nJohn Doe\nJane Smith\n1 2\n1 2\n2 1\n2 1\n1 2");}

	void test_voting_print_3 () {
        std::ostringstream w;
		string str = "";
        voting_print(w, str );
        CPPUNIT_ASSERT(w.str() == "");}

    // -----
    // solve
    // -----

    void test_voting_solve_1 () {
        std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n1 2 3\n\n5\nSirhan Sirhan\nJack Black\nBen Stiller\nJohn Doe\nJane Smith\n5 2 3 4 1\n5 2 1 3 4\n4 2 1 5 3\n1 2 3 4 5\n5 3 1 2 4");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n\nJane Smith\n");
		}
	void test_voting_solve_2 () {
        std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n1 2 3");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
		}
	void test_voting_solve_3 () {
        std::istringstream r("1\n\n1\nJohn Doe\n1\n1");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
		}
	


    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
	CPPUNIT_TEST(test_voting_read_1);
	CPPUNIT_TEST(test_voting_read_2);
	CPPUNIT_TEST(test_voting_read_3);
	CPPUNIT_TEST(test_voting_eval_1);
	CPPUNIT_TEST(test_voting_eval_2);
	CPPUNIT_TEST(test_voting_eval_3);
	CPPUNIT_TEST(test_voting_print_1);
	CPPUNIT_TEST(test_voting_print_2);
	CPPUNIT_TEST(test_voting_print_3);
	CPPUNIT_TEST(test_voting_solve_1);
	CPPUNIT_TEST(test_voting_solve_2);
	CPPUNIT_TEST(test_voting_solve_3);

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
