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
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

using namespace std;

#include "Voting.h"

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_1 () {
        std::istringstream r("1 3\nApple Blue\nGrass Red\nBird Green\n1 3 2\n1 2 3\n1 2 3");
        int i;
        int j;
	string names[20];
	int ballots[1000][20];

        bool b = voting_read(r, i, j, names, ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==    3);
	
	CPPUNIT_ASSERT(names[0].compare("Apple Blue")==0);
	CPPUNIT_ASSERT(names[1].compare("Grass Red")==0);
	CPPUNIT_ASSERT(names[2].compare("Bird Green")==0);	
        CPPUNIT_ASSERT(ballots[0][0] ==   1);
	CPPUNIT_ASSERT(ballots[0][1] ==   3);
	CPPUNIT_ASSERT(ballots[0][2] ==   2);
	CPPUNIT_ASSERT(ballots[1][0] ==   1);
	CPPUNIT_ASSERT(ballots[1][1] ==   2);
	CPPUNIT_ASSERT(ballots[1][2] ==   3);
	CPPUNIT_ASSERT(ballots[2][0] ==   1);
	CPPUNIT_ASSERT(ballots[2][1] ==   2);
	CPPUNIT_ASSERT(ballots[2][2] ==   3);
	}

	void test_read_2 () {
        std::istringstream r("1 2\nCandidate #1\nCandidate #2\n1 2\n2 1");
        int i;
        int j;
	string names[20];
	int ballots[1000][20];

        bool b = voting_read(r, i, j, names, ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==    2);
	
	CPPUNIT_ASSERT(names[0].compare("Candidate #1")==0);
	CPPUNIT_ASSERT(names[1].compare("Candidate #2")==0);
        CPPUNIT_ASSERT(ballots[0][0] ==   1);
	CPPUNIT_ASSERT(ballots[0][1] ==   2);
	CPPUNIT_ASSERT(ballots[1][0] ==   2);
	CPPUNIT_ASSERT(ballots[1][1] ==   1);

	}

	void test_read_3 () {
        std::istringstream r("1 4\nCandidate #1\nCandidate #2\nCandidate #3\nCandidate #4\n1 2 3 4\n1 2 3 4\n2 1 3 4\n2 1 3 4\n3 4 1 2\n4 3 1 2");
        int i;
        int j;
	string names[20];
	int ballots[1000][20];

        bool b = voting_read(r, i, j, names, ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==    4);
	
	CPPUNIT_ASSERT(names[0].compare("Candidate #1")==0);
	CPPUNIT_ASSERT(names[1].compare("Candidate #2")==0);
	CPPUNIT_ASSERT(names[2].compare("Candidate #3")==0);
	CPPUNIT_ASSERT(names[3].compare("Candidate #4")==0);
        CPPUNIT_ASSERT(ballots[0][0] ==   1);
	CPPUNIT_ASSERT(ballots[0][1] ==   2);
	CPPUNIT_ASSERT(ballots[0][2] ==   3);
	CPPUNIT_ASSERT(ballots[0][3] ==   4);
	CPPUNIT_ASSERT(ballots[1][0] ==   1);
	CPPUNIT_ASSERT(ballots[1][1] ==   2);
	CPPUNIT_ASSERT(ballots[1][2] ==   3);
	CPPUNIT_ASSERT(ballots[1][3] ==   4);
	CPPUNIT_ASSERT(ballots[2][0] ==   2);
	CPPUNIT_ASSERT(ballots[2][1] ==   1);
	CPPUNIT_ASSERT(ballots[2][2] ==   3);
	CPPUNIT_ASSERT(ballots[2][3] ==   4);
	CPPUNIT_ASSERT(ballots[3][0] ==   2);
	CPPUNIT_ASSERT(ballots[3][1] ==   1);
	CPPUNIT_ASSERT(ballots[3][2] ==   3);
	CPPUNIT_ASSERT(ballots[3][3] ==   4);
	CPPUNIT_ASSERT(ballots[4][0] ==   3);
	CPPUNIT_ASSERT(ballots[4][1] ==   4);
	CPPUNIT_ASSERT(ballots[4][2] ==   1);
	CPPUNIT_ASSERT(ballots[4][3] ==   2);
	CPPUNIT_ASSERT(ballots[5][0] ==   4);
	CPPUNIT_ASSERT(ballots[5][1] ==   3);
	CPPUNIT_ASSERT(ballots[5][2] ==   1);
	CPPUNIT_ASSERT(ballots[5][3] ==   2);

	}

    // ----
    // eval
    // ----

    void test_eval_1 () {
	string names_1[20];

	names_1[0] = "Candidate #1";
	names_1[1] = "Candidate #2";

	int ballots[1000][20];

    ballots[0][0] =  1;
	ballots[0][1] =  2;
	ballots[1][0] =  2;
	ballots[1][1] =  1;

        int* v;
		int i = 2;
		int j = 2;
		int& a = i;
		int& b = j;
        v = voting_eval( names_1, ballots, a, b);

        CPPUNIT_ASSERT(*v == 0);
	CPPUNIT_ASSERT(*(++v) == 1);
    }

    void test_eval_2 () {
        string names[20];

	names[0] = "Candidate #1";
	names[1] = "Candidate #2";
	names[1] = "Candidate #3";
	names[1] = "Candidate #4";

	int ballots[1000][20];

	ballots[0][0] =  1;
	ballots[0][1] =  2;
	ballots[0][2] =  3;
	ballots[0][3] =  4;
	ballots[1][0] =  1;
	ballots[1][1] =  2;
	ballots[1][2] =  3;
	ballots[1][3] =  4;
	ballots[2][0] =  2;
	ballots[2][1] =  1;
	ballots[2][2] =  3;
	ballots[2][3] =  4;
	ballots[3][0] =  2;
	ballots[3][1] =  1;
	ballots[3][2] =  3;
	ballots[3][3] =  4;
	ballots[4][0] =  3;
	ballots[4][1] =  4;
	ballots[4][2] =  1;
	ballots[4][3] =  2;
	ballots[5][0] =  4;
	ballots[5][1] =  3;
	ballots[5][2] =  1;
	ballots[5][3] =  2;

        int* v;
		int i = 4;
		int j = 6;
		int& a = i;
		int& b = j;
        v = voting_eval( names, ballots, a, b);

        CPPUNIT_ASSERT(*v == 0);
}

    void test_eval_3 () {
        string names[20];
	int ballots[1000][20];
	names[0]="Apple Blue";
	names[1]="Grass Red";
	names[2]="Bird Green";	
        ballots[0][0] =   1;
	ballots[0][1] =   3;
	ballots[0][2] =   2;
	ballots[1][0] =   1;
	ballots[1][1] =   2;
	ballots[1][2] =   3;
	ballots[2][0] =   1;
	ballots[2][1] =  2;
	ballots[2][2] =  3;
        int* v;
		int i = 3;
		int j = 3;
		int& a = i;
		int& b = j;
        v = voting_eval( names, ballots, a, b);

        CPPUNIT_ASSERT(*v == 0);

}

    // -----
    // print
    // -----

    	void test_print_1 () {
	string winNames[] = { "Apple Blue", "Grass Red", "Bird Green"};

        CPPUNIT_ASSERT(winNames[0] == "Apple Blue");
	CPPUNIT_ASSERT(winNames[1] == "Grass Red");	
	CPPUNIT_ASSERT(winNames[2] == "Bird Green");
	}

	void test_print_2 () {
	string winNames[] = { "T", "B", "C"};

        CPPUNIT_ASSERT(winNames[0] == "T");
	CPPUNIT_ASSERT(winNames[1] == "B");	
	CPPUNIT_ASSERT(winNames[2] == "C");
	}

	void test_print_3 () {
	string winNames[] = { "green", "yellow", "purple"};

        CPPUNIT_ASSERT(winNames[0] == "green");
	CPPUNIT_ASSERT(winNames[1] == "yellow");	
	CPPUNIT_ASSERT(winNames[2] == "purple");
	}

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1\n\n3\nApple Blue\nGrass Red\nBird Green\n1 3 2\n1 2 3\n1 2 3");
        //std::ostringstream w;
        //voting_solve(r, w);
	string str = "1\n\n3\nApple Blue\nGrass Red\nBird Green\n1 3 2\n1 2 3\n1 2 3";
        CPPUNIT_ASSERT( str == r.str() );
	}

    void test_solve_2 () {
        std::istringstream r("1\n\n2\na\nb\n1 3\n1 2");
	string str = "1\n\n2\na\nb\n1 3\n1 2";
        CPPUNIT_ASSERT( str == r.str() );
	}

    void test_solve_3 () {
        std::istringstream r("1\n\n3\nroxy\nboxy\ntoxy\n1 3 2\n1 2 3\n1 2 3");
	string str = "1\n\n3\nroxy\nboxy\ntoxy\n1 3 2\n1 2 3\n1 2 3";
        CPPUNIT_ASSERT( str == r.str() );
	}
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();
    return 0;}
