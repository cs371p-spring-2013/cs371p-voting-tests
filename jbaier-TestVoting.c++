/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -lcppunit -ldl -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting.c++.app
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

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {
    
    // ----
    // read
    // ----

  void test_read_1 () {
    std::istringstream r("1\nPaul\n1");
    const bool v = voting_read(r);
  	CPPUNIT_ASSERT(v ==    true);
  	}
    
	void test_read_2 () {
  	std::istringstream r("2\nPaula\nAbdul\n1 2\n2 1");
    const bool v = voting_read(r);
  	CPPUNIT_ASSERT(v ==    true);
	}
    
  void test_read_3 () {
    std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3");
    const bool v = voting_read(r);
		CPPUNIT_ASSERT(v == true);
	}

    // ----
    // eval
    // ----

  void test_eval_1 () {
  	std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n1 2 3");
  	std::ostringstream w;
  	voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "John Doe\n");
  }

	void test_eval_2 () {
    std::istringstream r("1\n\n2\nPaula\nAbdul\n1 2\n2 1");
  	std::ostringstream w;
  	voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Paula\nAbdul\n");
  }

  void test_eval_3 () {
    std::istringstream r("1\n\n1\nJoerg\n1\n1");
  	std::ostringstream w;
  	voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Joerg\n");
  }
    
    
    // -----
    // print
    // -----
    
	void test_print_1 () {
  	std::istringstream r("1\n\n2\nPaula\nAbdul\n1 2\n2 1");
  	std::ostringstream w;
  	voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Paula\nAbdul\n");
  }
    
  void test_print_2 () {
    std::istringstream r("1\n\n1\nPaula\n1");
  	std::ostringstream w;
  	voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Paula\n");
  }
    
  void test_print_3 () {
    std::istringstream r("1\n\n3\nPaula\nRandy\nSimon\n1 2 3\n2 1 3");
  	std::ostringstream w;
  	voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Paula\nRandy\n");
  }
    

    // -----
    // solve
    // -----

  void test_solve_1 () {
  	std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n1 2 3");
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "John Doe\n");
  }

  void test_solve_2 () {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n3 2 1");
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "John Doe\nSirhan Sirhan\n");
  }

  void test_solve_3 () {
    std::istringstream r("1\n\n1\nZach Sais\n1\n1\n1\n1\n1");
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Zach Sais\n");
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
  //ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
  cout << "TestVoting.c++" << endl;

  CppUnit::TextTestRunner tr;
  tr.addTest(TestVoting::suite());
  tr.run();

  cout << "Done." << endl;
  return 0;}
