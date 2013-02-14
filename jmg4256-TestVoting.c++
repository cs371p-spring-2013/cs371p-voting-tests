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

    void test_read () {
        std::istringstream r("John\nJane\nJames\n1 2 3\n2 1 3\n");
        string names [3];
        vector<vector<int>> votes;
	const bool b = voting_read(r, 3, names, votes);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(names[0] == "John");
        CPPUNIT_ASSERT(names[1] == "Jane");
        CPPUNIT_ASSERT(names[2] == "James");
        CPPUNIT_ASSERT(votes.size() == 2);
        
	CPPUNIT_ASSERT(votes[0][0] == 1);
	CPPUNIT_ASSERT(votes[0][1] == 2);
	CPPUNIT_ASSERT(votes[0][2] == 3);


        CPPUNIT_ASSERT(votes[1][0] == 2);
        CPPUNIT_ASSERT(votes[1][1] == 1);
        CPPUNIT_ASSERT(votes[1][2] == 3);
	
    }
    
    void test_read_2 (){
	
        std::istringstream r("John\nJane\n1 2\n2 1\n2 1\n2 1\n");
        string names [2];
        vector<vector<int> > votes;
	const bool b = voting_read(r, 2, names, votes);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(names[0] == "John");
        CPPUNIT_ASSERT(names[1] == "Jane");
        CPPUNIT_ASSERT(votes[0][0] == 1);
        CPPUNIT_ASSERT(votes[0][1] == 2);

        CPPUNIT_ASSERT(votes[1][0] == 2);
        CPPUNIT_ASSERT(votes[1][1] == 1);

        CPPUNIT_ASSERT(votes[2][0] == 2);
        CPPUNIT_ASSERT(votes[2][1] == 1);

        CPPUNIT_ASSERT(votes[3][0] == 2);
        CPPUNIT_ASSERT(votes[3][1] == 1);
    }

void test_read_3 (){ 
        std::istringstream r("John\nJane\nJames\nJaime\n4 1 2 3\n4 2 1 3\n4 2 1 3\n");
        string names [4];
        vector<vector<int> > votes;
	const bool b = voting_read(r, 4, names, votes);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(names[0] == "John");
        CPPUNIT_ASSERT(names[1] == "Jane");
        CPPUNIT_ASSERT(names[2] == "James");
        CPPUNIT_ASSERT(names[3] == "Jaime");
        
	CPPUNIT_ASSERT(votes[0][0] == 4);
        CPPUNIT_ASSERT(votes[0][1] == 1);
        CPPUNIT_ASSERT(votes[0][2] == 2);
        CPPUNIT_ASSERT(votes[0][3] == 3);


        CPPUNIT_ASSERT(votes[1][0] == 4);
        CPPUNIT_ASSERT(votes[1][1] == 2);
        CPPUNIT_ASSERT(votes[1][2] == 1);
        CPPUNIT_ASSERT(votes[1][3] == 3);

        CPPUNIT_ASSERT(votes[2][0] == 4);
        CPPUNIT_ASSERT(votes[2][1] == 2);
        CPPUNIT_ASSERT(votes[2][2] == 1);
        CPPUNIT_ASSERT(votes[2][3] == 3);
    }

    // eval
    // ----

    void test_eval_1 () {
	string names[] = {"John", "Elvis"};
	vector<vector<int>> votes;
	votes.resize(2);
	votes[0].push_back(1);
	votes[0].push_back(2);
	votes[1].push_back(1);
	votes[1].push_back(2);
        string result = voting_eval(2, names, votes);
	CPPUNIT_ASSERT(result == "John");
    }

    void test_eval_2 () {
	string names[] = {"John", "Elvis"};
	vector<vector<int> > votes;
	votes.resize(2);
	votes[0].push_back(1);
	votes[0].push_back(2);
	votes[1].push_back(2);
	votes[1].push_back(1);
        string result = voting_eval(2, names, votes);
	CPPUNIT_ASSERT(result == "John\nElvis");
    }

    void test_eval_3 () {
	string names[] = {"A", "B", "C", "D", "E"};
	vector<vector<int> > votes;
	votes.resize(6);
	votes[0].push_back(1);
	votes[0].push_back(2);
	votes[0].push_back(3);
	votes[0].push_back(4);
	votes[0].push_back(5);
	
	votes[1].push_back(1);
	votes[1].push_back(3);
	votes[1].push_back(4);
	votes[1].push_back(2);
	votes[1].push_back(5);

    
	votes[2].push_back(2);
	votes[2].push_back(1);
	votes[2].push_back(4);
	votes[2].push_back(3);
	votes[2].push_back(5);

	votes[3].push_back(2);
	votes[3].push_back(4);
	votes[3].push_back(3);
	votes[3].push_back(1);
	votes[3].push_back(5);

	votes[4].push_back(3);
	votes[4].push_back(4);
	votes[4].push_back(1);
	votes[4].push_back(2);
	votes[4].push_back(5);

	votes[5].push_back(4);
	votes[5].push_back(1);
	votes[5].push_back(3);
	votes[5].push_back(5);
	votes[5].push_back(2);

        string result = voting_eval(5, names, votes);
	CPPUNIT_ASSERT(result == "A");
    }
    
    void test_eval_4 () {
	string names[] = {"John", "Elvis", "Jane"};
	vector<vector<int>> votes;
	votes.resize(5);
	votes[0].push_back(2);
	votes[0].push_back(1);
	votes[0].push_back(3);
	votes[1].push_back(1);
	votes[1].push_back(2);
	votes[1].push_back(3);
	votes[2].push_back(3);
	votes[2].push_back(1);
	votes[2].push_back(2);
	votes[3].push_back(2);
	votes[3].push_back(1);
	votes[3].push_back(3);
	votes[4].push_back(1);
	votes[4].push_back(2);
	votes[4].push_back(3);
        string result = voting_eval(3, names, votes);
	CPPUNIT_ASSERT(result == "John");
    }

    void test_print () {
        std::ostringstream w;
	string winner = "John";
        voting_print(w, winner);
        CPPUNIT_ASSERT(w.str() == "John\n");
    }

    void test_print_2 () {
        std::ostringstream w;
	string winner = "John Miller";
        voting_print(w, winner);
        CPPUNIT_ASSERT(w.str() == "John Miller\n");
    }

    void test_print_3 () {
        std::ostringstream w;
	string winner = "John Miller Jones Jr.";
        voting_print(w, winner);
        CPPUNIT_ASSERT(w.str() == "John Miller Jones Jr.\n");
    }
    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1\n\n4\nJohn\nJane\nJames\nJaime\n4 1 2 3\n4 2 1 3\n4 2 1 3\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Jaime\n");
    }
    void test_solve_2 () {
        std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
    }
    
    void test_solve_3 () {
        std::istringstream r("2\n\n4\nJohn\nJane\nJames\nJaime\n4 1 2 3\n4 2 1 3\n4 2 1 3\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Jaime\nJohn Doe\n");
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
   /* CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    

    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
   

   */ CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
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
    return 0;
}
