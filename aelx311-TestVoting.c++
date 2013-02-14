//--------------
//TestVoting.c++
//--------------

/*
To test the program:
    % g++ -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting -lcppunit -ldl
    % valgrind TestVoting >& TestVoting.c++.out
*/

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
    void test_voting_read_1() {
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n1 2 3\n3 1 2");
        AllCandidates test_candidate_1;
        int numberOfVoters = 0;
        bool b = voting_read(test_candidate_1, r, numberOfVoters);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(numberOfVoters == 4);
        CPPUNIT_ASSERT(test_candidate_1.allCandidates[0].name.compare("John Doe") == 0);
        CPPUNIT_ASSERT(test_candidate_1.allCandidates[1].name.compare("Jane Smith") == 0);
        CPPUNIT_ASSERT(test_candidate_1.allCandidates[2].name.compare("Sirhan Sirhan") == 0);
    }
    
    void test_voting_read_2() {
        std::istringstream r("4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
        AllCandidates test_candidate_1;
        int numberOfVoters = 0;
        bool b = voting_read(test_candidate_1, r, numberOfVoters);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(numberOfVoters == 6);
        CPPUNIT_ASSERT(test_candidate_1.allCandidates[0].name.compare("Red") == 0);
        CPPUNIT_ASSERT(test_candidate_1.allCandidates[1].name.compare("Green") == 0);
        CPPUNIT_ASSERT(test_candidate_1.allCandidates[2].name.compare("Blue") == 0);
        CPPUNIT_ASSERT(test_candidate_1.allCandidates[3].name.compare("Orange") == 0);
    }
    
    void test_voting_read_3() {
        std::istringstream r("2\nABC\nDEF\n1 2\n2 1\n1 2\n2 1");
        AllCandidates test_candidate_1;
        int numberOfVoters = 0;
        bool b = voting_read(test_candidate_1, r, numberOfVoters);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(numberOfVoters == 4);
        CPPUNIT_ASSERT(test_candidate_1.allCandidates[0].name.compare("ABC") == 0);
        CPPUNIT_ASSERT(test_candidate_1.allCandidates[1].name.compare("DEF") == 0);
    }
    
    // ----
    // eval
    // ----
    void test_voting_eval_1(){
        std::ostringstream w;
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n1 2 3\n3 1 2");
        int numberOfVoters = 0;
        AllCandidates test_candidate_1;
        voting_read(test_candidate_1, r, numberOfVoters);
        voting_eval(test_candidate_1, w, numberOfVoters);
        CPPUNIT_ASSERT(numberOfVoters == 4);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
    }
    
    void test_voting_eval_2(){
        std::ostringstream w;
        std::istringstream r("4\nRed\nGreen\nBlue\nOrange\n2 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
        int numberOfVoters = 0;
        AllCandidates test_candidate_1;
        voting_read(test_candidate_1, r, numberOfVoters);
        voting_eval(test_candidate_1, w, numberOfVoters);
        CPPUNIT_ASSERT(numberOfVoters == 6);
        CPPUNIT_ASSERT(w.str() == "Green\n");
    }
    
    void test_voting_eval_3(){
        std::ostringstream w;
        std::istringstream r("2\nABC\nDEF\n1 2\n2 1\n1 2\n1 2");
        int numberOfVoters = 0;
        AllCandidates test_candidate_1;
        voting_read(test_candidate_1, r, numberOfVoters);
        voting_eval(test_candidate_1, w, numberOfVoters);
        CPPUNIT_ASSERT(numberOfVoters == 4);
        CPPUNIT_ASSERT(w.str() == "ABC\n");
    }
    
    // -----
    // print
    // -----
    void test_voting_print_1(){
    	std::ostringstream w;
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n1 2 3\n3 1 2");
        int numberOfVoters = 0;
        AllCandidates test_candidate_1;
        voting_read(test_candidate_1, r, numberOfVoters);
        voting_eval(test_candidate_1, w, numberOfVoters);
        CPPUNIT_ASSERT(voting_print(w) == true);
    }
    
     void test_voting_print_2(){
    	std::ostringstream w;
        std::istringstream r("4\nRed\nGreen\nBlue\nOrange\n2 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
        int numberOfVoters = 0;
        AllCandidates test_candidate_1;
        voting_read(test_candidate_1, r, numberOfVoters);
        voting_eval(test_candidate_1, w, numberOfVoters);
        CPPUNIT_ASSERT(voting_print(w) == true);
    }
    
     void test_voting_print_3(){
    	std::ostringstream w;
        std::istringstream r("2\nABC\nDEF\n1 2\n2 1\n1 2\n1 2");
        int numberOfVoters = 0;
        AllCandidates test_candidate_1;
        voting_read(test_candidate_1, r, numberOfVoters);
        voting_eval(test_candidate_1, w, numberOfVoters);
        CPPUNIT_ASSERT(voting_print(w) == true);
    }

    
    // -----
    // solve
    // -----
    void test_voting_solve_1(){
    	std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n1 2 3\n3 1 2");
    	std::ostringstream w;
    	voting_solve(r,w);
    	CPPUNIT_ASSERT(w.str() == "John Doe\n");
    }
    
    void test_voting_solve_2(){
    	std::ostringstream w;
        std::istringstream r("1\n\n4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
        voting_solve(r,w);
        CPPUNIT_ASSERT(w.str() == "Red\nGreen\n");
    }
    
    void test_voting_solve_3(){
    	std::ostringstream w;
        std::istringstream r("2\n\n2\nABC\nDEF\n1 2\n2 1\n1 2\n1 2\n\n3\nTest1\nTest2\nTest3\n1 2 3\n2 1 3\n3 2 1\n2 1 3\n3 1 2\n1 2 3\n2 3 1");
        voting_solve(r,w);
        CPPUNIT_ASSERT(w.str() == "ABC\nTest2\n");
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
