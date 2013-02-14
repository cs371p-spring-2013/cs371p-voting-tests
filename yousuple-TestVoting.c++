/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ Voting.c++ TestVoting.c++ -lcppunit -ldl -pedantic -std=c++0x -Wall -o TestVoting.c++.app
    % valgrind TestVoting.c++.app >& TestVoting.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>
#include <algorithm>
#include <queue>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

using namespace std;
vector<string> input;
vector<string> names;
vector<int> output;

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture{

	// Testing voting_read

	void test_read1 () {
    std::istringstream r("1\n""\n3\nJohn Doe\nJane Waterman\nJesus Lives\n1 2 3\n2 3 1\n3 1 2\n");
    voting_read(r, input);
    CPPUNIT_ASSERT(input.size() == 9);
	CPPUNIT_ASSERT(input.front() == "1");
	}

	void test_read2 () {
	input.erase(input.begin(), input.end());
    std::istringstream r("2\n""\n2\nJane Waterman\nJesus Lives\n1 2 \n1 2\n""\n2\nPeter Jeon\nBrandon Ho\n1 2\n2 1\n");
    voting_read(r, input);
    CPPUNIT_ASSERT(input.size() == 13);
	CPPUNIT_ASSERT(input.front() == "2");
	}

	void test_read3 () {
	input.erase(input.begin(), input.end());
    std::istringstream r("1\n""\n4\nJohn Doe\nJane Waterman\nJesus Lives\nPeter Jeon\n1 2 3 4\n4 2 3 1\n3 4 1 2\n");
    voting_read(r, input);
    CPPUNIT_ASSERT(input.size() == 10);
	CPPUNIT_ASSERT(input.front() == "1");
	}
	
	// Testing voting_eval
	void test_eval1 () {
	input.erase(input.begin(), input.end());
	output.erase(output.begin(), output.end());
	input = {"","3","John Doe","Jane Waterman","Jesus Lives","1 3 2","3 2 1","2 1 3"};
    voting_eval(input, names, output);
    CPPUNIT_ASSERT(output[2] == 3);
	}

	void test_eval2 () {
	input.erase(input.begin(), input.end());
	names.erase(names.begin(), names.end());
	output.erase(output.begin(), output.end());
	input = {"","3","John Doe","Jane Waterman","Jesus Lives","1 3 2","1 2 3","1 2 3"};
    voting_eval(input, names, output);
    CPPUNIT_ASSERT(output[0] == 1);
	}

	void test_eval3 () {
	input.erase(input.begin(), input.end());
	names.erase(names.begin(), names.end());
	output.erase(output.begin(), output.end());
	input = {"","4","John Doe","Jane Waterman","Jesus Lives","Peter Jeon","4 1 3 2","4 1 2 3","4 1 2 3","4 2 3 1"};
    voting_eval(input, names, output);
    CPPUNIT_ASSERT(output[0] == 4);
	}

	// testing voting_print
    void test_print1 () {
    std::ostringstream w;
	names.erase(names.begin(), names.end());
	names = {"John Doe", "Jane Waterman", "Jesus Lives"};
	output = {3};
    voting_print(w, output, names);
    CPPUNIT_ASSERT(w.str() == "Jesus Lives\n");}

    void test_print2 () {
    std::ostringstream w;
	names.erase(names.begin(), names.end());
	names = {"John Doe", "Jane Waterman", "Jesus Lives", "Peter Jeon"};
	output = {4};
    voting_print(w, output, names);
    CPPUNIT_ASSERT(w.str() == "Peter Jeon\n");}

    void test_print3 () {
    std::ostringstream w;
	names.erase(names.begin(), names.end());
	names = {"John Doe", "Jane Waterman", "Jesus Lives"};
	output = {1};
    voting_print(w, output, names);
    CPPUNIT_ASSERT(w.str() == "John Doe\n");}


	// Testing voting_solve
    void test_solve1 () {
    std::istringstream r("1\n""\n3\nJohn Doe\nJane Waterman\nJesus Lives\n1 3 2\n3 2 1\n2 1 3");
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Jane Waterman\nJohn Doe\nJesus Lives\n");}

    void test_solve2 () {
    std::istringstream r("1\n""\n3\nJohn Doe\nJane Waterman\nJesus Lives\n2 1 3\n2 3 1\n2 1 3");
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Jane Waterman\n");}
	

    void test_solve3 () {
    std::istringstream r("1\n""\n3\nJohn Doe\nJane Waterman\nJesus Lives\n3 1 2\n3 2 1\n2 1 3");
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Jesus Lives\n");}




	CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read1);
    CPPUNIT_TEST(test_read2);
    CPPUNIT_TEST(test_read3);
    CPPUNIT_TEST(test_eval1);
    CPPUNIT_TEST(test_eval2);
    CPPUNIT_TEST(test_eval3);
    CPPUNIT_TEST(test_print1);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);
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
