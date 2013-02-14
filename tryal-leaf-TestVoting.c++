//
//  TestVoting.c++
//  voting
//
//  Created by Katie Park on 2/13/13.
//  Copyright (c) 2013 Katie Park. All rights reserved.
//

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


#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

struct TestVoting : CppUnit::TestFixture {

	//---------------
	// read_num_cases
	//---------------
	
	//	bool voting_read_num_cases (istream& input, int& n)
	void test_read_num_cases_1 () {
		std::istringstream input("1\n\n");
		int n;
		
		const bool b = voting_read_num_cases(r, n);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(n == 1);
	}
	
	void test_read_num_cases_2 () {
		std::istringstream input("20\n\n");
		int n;
		
		const bool b = voting_read_num_cases(r, n);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(n == 20);
	}
	
	void test_read_num_cases_3 () {
		std::istringstream input("9\n\n");
		int n;
		
		const bool b = voting_read_num_cases(r, n);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(n == 9);
	}
	
	
	//-----------
	// read_cands
	//-----------
	
	//	bool voting_read_cands (istream& input, int& c, string cands[])
	void test_read_cands_1 () {
		std::istringstream input("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n");
		int c;
		string cands[20];
		
		const bool b = voting_read_cands(r, c, cands);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(c == 3);
		CPPUNIT_ASSERT(c[0] == "John Doe");
		CPPUNIT_ASSERT(c[1] == "Jane Smith");
		CPPUNIT_ASSERT(c[2] == "Sirhan Sirhan");
	}
	
	void test_read_cands_2 () {
		std::istringstream input("2\nJohn Doe\nJane Smith\n");
		int c;
		string cands[20];
		
		const bool b = voting_read_cands(r, c, cands);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(c == 2);
		CPPUNIT_ASSERT(c[0] == "John Doe");
		CPPUNIT_ASSERT(c[1] == "Jane Smith");
	}
	
	void test_read_cands_3 () {
		std::istringstream input("1\nJohn Doe\n");
		int c;
		string cands[20];
		
		const bool b = voting_read_cands(r, c, cands);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(c == 1);
		CPPUNIT_ASSERT(c[0] == "John Doe");
	}
	
	
	//-------------
	// read_ballots
	//-------------
	
	//	bool voting_read_ballots (istream& input, int& b, int ballots[], int num_cands)
	void test_read_ballots_1 () {
		std::istringstream input("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
		int nb;
		int ballots[15];
		
		const bool b = voting_read_ballots(r, nb, ballots, 3);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(nb == 5);
		int soln[15] = {1, 2, 3, 2, 1, 3, 2, 3, 1, 1, 2, 3, 3, 1, 2};
		CPPUNIT_ASSERT(ballots == soln);
	}
	
	void test_read_ballots_2 () {
		std::istringstream input("1 2 3\n2 1 3\n");
		int nb;
		int ballots[6];
		
		const bool b = voting_read_ballots(r, nb, ballots, 3);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(nb == 2);
		int soln[6] = {1, 2, 3, 2, 1, 3};
		CPPUNIT_ASSERT(ballots == soln);
	}
	
	void test_read_ballots_3 () {
		std::istringstream input("1 2\n2 1\n");
		int nb;
		int ballots[4];
		
		const bool b = voting_read_ballots(r, nb, ballots, 3);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(nb == 2);
		int soln[4] = {1, 2, 2, 1};
		CPPUNIT_ASSERT(ballots == soln);
	}
	
	
	//----------
	// read_case
	//----------
	
	//	bool voting_read_case (istream& input, int& c, string cands[], int& b, int ballots[])
	void test_read_case_1 () {
		std::istringstream input("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
		int c;
		string cands[20];
		int nb;
		int ballots[15];
		
		const bool b = voting_read_case(input, c, cands, nb, ballots);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(c == 3);
		CPPUNIT_ASSERT(c[0] == "John Doe");
		CPPUNIT_ASSERT(c[1] == "Jane Smith");
		CPPUNIT_ASSERT(c[2] == "Sirhan Sirhan");
		CPPUNIT_ASSERT(nb == 5);
		int soln[15] = {1, 2, 3, 2, 1, 3, 2, 3, 1, 1, 2, 3, 3, 1, 2};
		CPPUNIT_ASSERT(ballots == soln);
	}
	
	void test_read_case_2 () {
		std::istringstream input("2\nJohn Doe\nJane Smith\n1 2\n2 1\n");
		int c;
		string cands[20];
		int nb;
		int ballots[4];
		
		const bool b = voting_read_case(input, c, cands, nb, ballots);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(c == 2);
		CPPUNIT_ASSERT(c[0] == "John Doe");
		CPPUNIT_ASSERT(c[1] == "Jane Smith");
		CPPUNIT_ASSERT(nb == 2);
		int soln[4] = {1, 2, 2, 1};
		CPPUNIT_ASSERT(ballots == soln);
	}
	
	void test_read_case_3 () {
		std::istringstream input("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n");
		int c;
		string cands[20];
		int nb;
		int ballots[6];
		
		const bool b = voting_read_case(input, c, cands, nb, ballots);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(c == 3);
		CPPUNIT_ASSERT(c[0] == "John Doe");
		CPPUNIT_ASSERT(c[1] == "Jane Smith");
		CPPUNIT_ASSERT(c[2] == "Sirhan Sirhan");
		CPPUNIT_ASSERT(nb == 2);
		int soln[6] = {1, 2, 3, 2, 1, 3};
		CPPUNIT_ASSERT(ballots == soln);
	}
	
	
	//------
	// solve
	//------
	
	//	void voting_solve (istream& input, ostream& output)
	void test_solve_1 () {
		std::istringstream input("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
		std::ostringstream output;
		
		voting_solve(input, output);
		CPPUNIT_ASSERT(output.str() == "John Doe\n");
	}
	
	void test_solve_2 () {
		std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan \
							 Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n 3 1 2\n\n4\nJohn \
							 Doe\nJane Smith\nSirhan Sirhan\nDark Horse\n1 2 3 4\n\
							 2 4 3 1\n3 2 4 1\n4 1 2 3\n1 2 3 4\n4 1 2 3\n");
		std::ostringstream output;
		
		voting_solve(input, output);
		CPPUNIT_ASSERT(output.str() == "John Doe\n\nDark Horse\n");
	}
	
	void test_solve_3 () {
		std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan \
							 Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n 3 1 2\n\n1\nJohn \
							 Unopposed\n1\n1\n1\n1\n1\n1\n");
		std::ostringstream output;
		
		voting_solve(input, output);
		CPPUNIT_ASSERT(output.str() == "John Doe\n\nJohn Unopposed\n");
	}
	
	
	//------
	// suite
	//------
	
	CPPUNIT_TEST_SUITE(TestVoting);
	
	CPPUNIT_TEST(test_read_num_cases_1);
	CPPUNIT_TEST(test_read_num_cases_2);
	CPPUNIT_TEST(test_read_num_cases_3);
	
	CPPUNIT_TEST(test_read_cands_1);
	CPPUNIT_TEST(test_read_cands_2);
	CPPUNIT_TEST(test_read_cands_3);
	
	CPPUNIT_TEST(test_read_ballots_1);
	CPPUNIT_TEST(test_read_ballots_2);
	CPPUNIT_TEST(test_read_ballots_3);
	
	CPPUNIT_TEST(test_read_case_1);
	CPPUNIT_TEST(test_read_case_2);
	CPPUNIT_TEST(test_read_case_3);
	
	CPPUNIT_TEST(test_solve_1);
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

