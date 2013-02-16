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
#include "Voting.h"
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner


// -----------
// TestCollatz
// -----------

struct TestVoting: CppUnit::TestFixture {
	// ----
	//voting_ read
	// ----

	void test_voting_read_one() {
		std::istringstream r("1\n");
		std::string s;
		const bool b = voting_read(r, s);
		CPPUNIT_ASSERT(b == true);
	}
	void test_voting_read_two() {
		std::istringstream r("\n");
		std::string s;
		const bool b = voting_read(r, s);
		CPPUNIT_ASSERT(b == true);
	}
	void test_voting_read_three() {
		std::istringstream r("bobby\n");
		std::string s;
		const bool b = voting_read(r, s);
		CPPUNIT_ASSERT(b == true);
	}

	
	
	//-----
	//
	// -----
        // suite
        // -----

   	 CPPUNIT_TEST_SUITE(TestVoting);
   	 CPPUNIT_TEST(test_voting_read_one);
   	 CPPUNIT_TEST(test_voting_read_two);
   	 CPPUNIT_TEST(test_voting_read_three);
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


