//		CS371p: project 2: Voting
//		TestVoting.c++

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
#include "Voting.h"

typedef std::string string;
typedef std::vector<std::string>    vectorStrings;
typedef std::vector<std::vector<int> >  vectorvectorInts;
typedef std::vector<int>    vectorInts;
typedef unsigned short  uShort;
typedef std::vector<bool>   vectorBooleans;
typedef std::vector< std::vector<int>* > vecvecofints;

struct TestVoting : CppUnit::TestFixture {
	
	void test_read1() {
	std::istringstream r("3\n\nRed\nGreen\nBlue\n1 2 3\n2 1 3\n2 3 1\n");
	vectorStrings nameCand;
        int ballots[1000][20];
	int ballotsSize;
        std::ostringstream w;
        bool b = voting_read(r, w, nameCand, ballots, ballotsSize);
        CPPUNIT_ASSERT(b);
	CPPUNIT_ASSERT(ballotsSize == 3);
        CPPUNIT_ASSERT(nameCand[0] == "Red");
	CPPUNIT_ASSERT(nameCand[1] == "Green");
	CPPUNIT_ASSERT(nameCand[2] == "Blue");
	CPPUNIT_ASSERT(ballots[0][0] == 1);
	CPPUNIT_ASSERT(ballots[0][1] == 2);
	CPPUNIT_ASSERT(ballots[0][2] == 3);

	CPPUNIT_ASSERT(ballots[1][0] == 2);
	CPPUNIT_ASSERT(ballots[1][1] == 1);
	CPPUNIT_ASSERT(ballots[1][2] == 3);

	CPPUNIT_ASSERT(ballots[2][0] == 2);
	CPPUNIT_ASSERT(ballots[2][1] == 3);
	CPPUNIT_ASSERT(ballots[2][2] == 1);
        //CPPUNIT_ASSERT(ballots==   20);
	}

	void test_read2() {
	std::istringstream r("4\n\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n");
        int ballots[1000][20];
	int ballotsSize;
	vectorStrings nameCand;
        std::ostringstream w;
        bool b = voting_read(r, w, nameCand, ballots,ballotsSize);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(ballotsSize == 4);
        CPPUNIT_ASSERT(nameCand[0] == "Red");
	CPPUNIT_ASSERT(nameCand[1] == "Green");
	CPPUNIT_ASSERT(nameCand[2] == "Blue");
	CPPUNIT_ASSERT(nameCand[3] == "Orange");
	
	CPPUNIT_ASSERT(ballots[0][0] == 1);
	CPPUNIT_ASSERT(ballots[0][1] == 2);
	CPPUNIT_ASSERT(ballots[0][2] == 3);
	CPPUNIT_ASSERT(ballots[0][3] == 4);

	CPPUNIT_ASSERT(ballots[1][0] == 2);
	CPPUNIT_ASSERT(ballots[1][1] == 1);
	CPPUNIT_ASSERT(ballots[1][2]==3);
	CPPUNIT_ASSERT(ballots[1][3] == 4);
	
        
	}
	
	void test_read3() {
	std::istringstream r("3\n\nJane Smith\nMolly Sims\nJacqueline Smith\n1 2 3\n2 3 1\n");
        int ballots[1000][20];
	int ballotsSize;
	vectorStrings nameCand;
        std::ostringstream w;
        const bool b = voting_read(r, w, nameCand, ballots, ballotsSize);
        CPPUNIT_ASSERT(b == true);
	CPPUNIT_ASSERT(ballotsSize == 3);
        CPPUNIT_ASSERT(nameCand[0] == "Jane Smith");
	CPPUNIT_ASSERT(nameCand[1] == "Molly Sims");
	CPPUNIT_ASSERT(nameCand[2] == "Jacqueline Smith");
    
	CPPUNIT_ASSERT(ballots[0][0] == 1);
	CPPUNIT_ASSERT(ballots[0][1] == 2);
	CPPUNIT_ASSERT(ballots[0][2] == 3);
	CPPUNIT_ASSERT(ballots[1][0] == 2);
	CPPUNIT_ASSERT(ballots[1][1] == 3);
	CPPUNIT_ASSERT(ballots[1][2] == 1);
	}

	void test_eval1()
	 {
		int ballots[1000][20]={{1,2,3},{2,3,1}};
		int ballotsSize=2;
		vectorStrings nameCand={"Jane Smith", "Molly Sims", "Jacqueline Smith"};
		vectorStrings nameWinners={"Jane Smith", "Molly Sims"};
		std::ostringstream w;
		//nameWinners, nameCand, ballots, ballotsSize
		voting_eval(nameWinners, nameCand, ballots, ballotsSize);
		CPPUNIT_ASSERT(ballotsSize == 3);
		CPPUNIT_ASSERT(nameCand[0] == "Jane Smith");
		CPPUNIT_ASSERT(nameCand[1] == "Molly Sims");
		CPPUNIT_ASSERT(nameCand[2] == "Jacqueline Smith");
	    
		CPPUNIT_ASSERT(nameWinners[0]== "Jane Smith");
		CPPUNIT_ASSERT(nameWinners[1]== "Molly Sims");
	}

	void test_eval2() 
	{
		int ballots[1000][20]={{1, 2, 3, 4}, {2,1,3,4}};
		int ballotsSize=2;
		vectorStrings nameCand={"Red", "Green", "Blue", "Orange"};
		vectorStrings nameWinners;
		std::ostringstream w;
		//nameWinners, nameCand, ballots, ballotsSize
		voting_eval(nameWinners, nameCand, ballots, ballotsSize);
	
		CPPUNIT_ASSERT(ballotsSize == 3);
		CPPUNIT_ASSERT(nameCand[0] == "Red");
		CPPUNIT_ASSERT(nameCand[1] == "Green");
		CPPUNIT_ASSERT(nameCand[2] == "Blue");
	    	CPPUNIT_ASSERT(nameCand[3] == "Orange");
	    
		CPPUNIT_ASSERT(nameWinners[0]== "Red");
		CPPUNIT_ASSERT(nameWinners[1]== "Green");
	}

	void test_eval3() 
	{
		int ballots[1000][20]={{1, 2, 3}, {2, 1, 3}, {2, 3, 1}};
		int ballotsSize=3;
		vectorStrings nameCand={"Red", "Green", "Blue"};
		vectorStrings nameWinners;
		std::ostringstream w;
		//nameWinners, nameCand, ballots, ballotsSize
		voting_eval(nameWinners, nameCand, ballots, ballotsSize);
		CPPUNIT_ASSERT(ballotsSize == 3);
		CPPUNIT_ASSERT(nameCand[0] == "Jane Smith");
		CPPUNIT_ASSERT(nameCand[1] == "Molly Sims");
		CPPUNIT_ASSERT(nameCand[2] == "Jacqueline Smith");
	    
		CPPUNIT_ASSERT(nameWinners[0]== "Molly Sims");
	}

	void test_print1() 
	{
		std::ostringstream w;
		vectorStrings nameWinners={"Green"};
        	voting_print(w, nameWinners);
        	CPPUNIT_ASSERT(w.str() == "Green\n");
	}
	
	void test_print2() 
	{
		std::ostringstream w;
		vectorStrings nameWinners={"Red", "Green"};
        	voting_print(w, nameWinners);
        	CPPUNIT_ASSERT(w.str() == "Red\nGreen\n");
	}
	
	void test_print3() 
	{
		std::ostringstream w;
		vectorStrings nameWinners={"Jane Smith", "Molly Sims"};
        	voting_print(w, nameWinners);
        	CPPUNIT_ASSERT(w.str() == "Jane Smith\nMolly Sims\n");
	}

	void test_solve1() 
	{
		std::ostringstream w;
	std::istringstream r("3\n\nJane Smith\nMolly Sims\nJacqueline Smith\n1 2 3\n2 3 1\n");
		voting_solve(r, w);
        	CPPUNIT_ASSERT(w.str() == "Jane Smith\nMolly Sims\n");
	}
	
	void test_solve2() 
	{
		std::ostringstream w;
		std::istringstream r("4\n\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n");
        	voting_solve(r, w);
        	CPPUNIT_ASSERT(w.str() == "Red\nGreen\n");
	}

	void test_solve3() 
	{
		std::ostringstream w;
		std::istringstream r("3\n\nRed\nGreen\nBlue\n1 2 3\n2 1 3\n2 3 1\n");
        	voting_solve(r, w);
        	CPPUNIT_ASSERT(w.str() == "Green\n");
	}
	CPPUNIT_TEST_SUITE(TestVoting);
   //my test_read()'s
     CPPUNIT_TEST(test_read1);
     CPPUNIT_TEST(test_read2);
    CPPUNIT_TEST(test_read3);

    CPPUNIT_TEST(test_eval1);
    CPPUNIT_TEST(test_eval2);
    CPPUNIT_TEST(test_eval3);

   //  //my test_print()'s
     CPPUNIT_TEST(test_print1);
     CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);
   
   // //my test_solve()'s
     CPPUNIT_TEST(test_solve1);
    CPPUNIT_TEST(test_solve2);
    CPPUNIT_TEST(test_solve3);
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
