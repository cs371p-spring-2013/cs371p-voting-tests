/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -lcppunit -ldl -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz.c++.app
    % valgrind TestCollatz.c++.app >& TestCollatz.c++.out
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
  
  // void test_read () {
  // 	std::istringstream r("1 10\n");
  // 	int i;
  // 	int j;
  // 	const bool b = voting_read(r, i, j);
  // 	CPPUNIT_ASSERT(b == true);
  // 	CPPUNIT_ASSERT(i ==    1);
  // 	CPPUNIT_ASSERT(j ==   10);
  // }

  // ----
  // eval
  // ----
  
  // void test_eval_1 () {
  // 	int c[CACHESIZE];
  // 	const int v = voting_eval(1, 10,c);
  // 	CPPUNIT_ASSERT(v == 20);
  // }
  
  // -----
  // solve
  // -----
  
  void test_solve_1() {
	std::istringstream r("1\n\n1\nE\n1\n1\n1");
	std::ostringstream w;
	voting_solve(r, w);
	CPPUNIT_ASSERT(w.str() == "E\n");
  }

  void test_solve_2() {
	std::istringstream r("1\n\n2\nE\nA\n1 2\n1 2\n1 2\n2 1\n2 1\n2 1");
	std::ostringstream w;
	voting_solve(r, w);
	CPPUNIT_ASSERT(w.str() == "E\nA\n");
  }

  void test_solve_3() {
	std::istringstream r("1\n\n2\nE\nA\n1 2\n1 2\n1 2\n2 1\n2 1\n2 1\n2 1");
	std::ostringstream w;
	voting_solve(r, w);
	CPPUNIT_ASSERT(w.str() == "A\n");
  }
	
  void test_solve_case_1() {
	std::ostringstream w;
	vector<candidate> candidates;
	vector<ballet> ballets;
	candidate c1, c2;
	ballet b1, b2, b3, b4, b5, b6, b7, b8;

	c1.valid = 1;
	c1.votes = 0;
	c1.name = "Jack";
	candidates.push_back(c1);

	c2.valid = 1;
	c2.votes = 0;
	c2.name = "Jill";	
	candidates.push_back(c2);

	b1.add(1); b1.add(2);
	b2.add(1); b2.add(2);
	b3.add(1); b3.add(2);
	b4.add(1); b4.add(2);
	b5.add(2); b5.add(1);
	b6.add(1); b6.add(2);
	b7.add(2); b7.add(1);
	b8.add(1); b8.add(2);
	ballets.push_back(b1);
	ballets.push_back(b2);
	ballets.push_back(b3);
	ballets.push_back(b4);
	ballets.push_back(b5);
	ballets.push_back(b6);
	ballets.push_back(b7);
	ballets.push_back(b8);
	
	voting_solve_case(w, candidates, ballets);
	CPPUNIT_ASSERT(w.str() == "Jack\n");
  }

  void test_solve_case_2() {
	std::ostringstream w;
	vector<candidate> candidates;
	vector<ballet> ballets;
	candidate c1, c2, c3;
	ballet b1, b2, b3, b4, b5, b6, b7, b8, b9;

	c1.valid = 1;
	c1.votes = 0;
	c1.name = "Jack";
	candidates.push_back(c1);

	c2.valid = 1;
	c2.votes = 0;
	c2.name = "Jill";	
	candidates.push_back(c2);

	c3.valid = 1;
	c3.votes = 0;
	c3.name = "Hill";
	candidates.push_back(c3);
	
	b1.add(1); b1.add(2); b1.add(3);
	b2.add(3); b2.add(2); b2.add(1);
	b3.add(2); b3.add(1); b3.add(3);
	b4.add(2); b4.add(1); b4.add(3);
	b5.add(1); b5.add(2); b5.add(3);
	b6.add(3); b6.add(2); b6.add(1);
	b7.add(3); b7.add(1); b7.add(2);
	b8.add(1); b8.add(2); b8.add(3);
	b9.add(2); b9.add(3); b9.add(1);
	
	ballets.push_back(b1);
	ballets.push_back(b2);
	ballets.push_back(b3);
	ballets.push_back(b4);
	ballets.push_back(b5);
	ballets.push_back(b6);
	ballets.push_back(b7);
	ballets.push_back(b8);
	ballets.push_back(b9);
	
	voting_solve_case(w, candidates, ballets);
	CPPUNIT_ASSERT(w.str() == "Jack\nJill\nHill\n");
  }

  void test_solve_case_3() {
	std::ostringstream w;
	vector<candidate> candidates;
	vector<ballet> ballets;
	candidate c1, c2;
	ballet b1, b2, b3, b4, b5, b6, b7, b8;

	c1.valid = 1;
	c1.votes = 0;
	c1.name = "Jack";
	candidates.push_back(c1);

	c2.valid = 1;
	c2.votes = 0;
	c2.name = "Jill";	
	candidates.push_back(c2);

	b1.add(1); b1.add(2);
	b2.add(2); b2.add(1);
	b3.add(2); b3.add(1);
	b4.add(1); b4.add(2);
	b5.add(2); b5.add(1);
	b6.add(1); b6.add(2);
	b7.add(2); b7.add(1);
	b8.add(1); b8.add(2);
	ballets.push_back(b1);
	ballets.push_back(b2);
	ballets.push_back(b3);
	ballets.push_back(b4);
	ballets.push_back(b5);
	ballets.push_back(b6);
	ballets.push_back(b7);
	ballets.push_back(b8);
	
	voting_solve_case(w, candidates, ballets);
	CPPUNIT_ASSERT(w.str() == "Jack\nJill\n");
  }

  void test_read_case_1() {
	std::istringstream r("2\nE\nA\n1 2\n1 2\n1 2\n2 1\n2 1\n2 1\n2 1");
	vector<candidate> candidates;
	vector<ballet> ballets;
	
	CPPUNIT_ASSERT(voting_read_case(r, candidates, ballets) == 1);
	CPPUNIT_ASSERT(candidates.size() == 2);
	CPPUNIT_ASSERT(ballets.size() == 7);
	
  }
  void test_read_case_2() {
	std::istringstream r("3\nE\nA\nC\n1 2 3\n1 3 2\n1 3 2\n3 2 1");
	vector<candidate> candidates;
	vector<ballet> ballets;
	
	CPPUNIT_ASSERT(voting_read_case(r, candidates, ballets) == 1);
	CPPUNIT_ASSERT(candidates.size() == 3);
	CPPUNIT_ASSERT(ballets.size() == 4);
	
  }
  
  void test_read_case_3() {
	std::istringstream r("1\nE\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1");
	vector<candidate> candidates;
	vector<ballet> ballets;
	
	CPPUNIT_ASSERT(voting_read_case(r, candidates, ballets) == 1);
	CPPUNIT_ASSERT(candidates.size() == 1);
	CPPUNIT_ASSERT(ballets.size() == 11);
	
  }
  // -----
  // suite
  // -----
  
  CPPUNIT_TEST_SUITE(TestVoting);
  CPPUNIT_TEST(test_read_case_1);
  CPPUNIT_TEST(test_read_case_2);
  CPPUNIT_TEST(test_read_case_3);
  CPPUNIT_TEST(test_solve_1);
  CPPUNIT_TEST(test_solve_2);
  CPPUNIT_TEST(test_solve_3);
  CPPUNIT_TEST(test_solve_case_1);
  CPPUNIT_TEST(test_solve_case_2);
  CPPUNIT_TEST(test_solve_case_3);
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
