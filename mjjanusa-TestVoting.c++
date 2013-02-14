// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

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
#include <vector>
#include <string> //string
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

// -----------
// Test
// -----------

struct TestVoting: CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read1 () {
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        int numCandidates;
		std::string* s; 
		std::vector<std::vector<int> > v; 
		const bool read = voting_read(r, v, &s, numCandidates);		
        CPPUNIT_ASSERT(read == true);
        CPPUNIT_ASSERT(numCandidates == 3);
        CPPUNIT_ASSERT(s[2] ==  "Sirhan Sirhan");
		CPPUNIT_ASSERT(v[1][0] ==  2);
		}

    void test_read2 () {
        std::istringstream r("2\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3");
        int numCandidates;
		std::string* s; 
		std::vector<std::vector<int> > v; 
		const bool read = voting_read(r, v, &s, numCandidates);		
        CPPUNIT_ASSERT(read == true);
        CPPUNIT_ASSERT(numCandidates == 2);
        CPPUNIT_ASSERT(s[0] ==  "Jane Smith");
		CPPUNIT_ASSERT(v[0][0] ==  1);
		}

    void test_read3 () {
        std::istringstream r("3\nJohn Doe\nJane Smith");
        int numCandidates;
		std::string* s; 
		std::vector<std::vector<int> > v; 
		const bool read = voting_read(r, v, &s, numCandidates);		
        CPPUNIT_ASSERT(read == false);
		}

    // ----
    // eval
    // ----

    void test_eval_1 () {
		int numCandidates = 2;
		std::string* s = new std::string[2];
		s[0] = "John"; 
		s[1] = "Bob"; 
		std::vector<std::vector<int> > v; 
		std::vector<int> inner; 
		inner.push_back(1);
		inner.push_back(2);
		v.push_back(inner);
		v.push_back(inner);
		std::string result = voting_eval(v, s, numCandidates);
        CPPUNIT_ASSERT(result == "John");
		delete[] s; 
		}

    void test_eval_2 () {
		int numCandidates = 2;
		std::string* s = new std::string[2];
		s[0] = "John"; 
		s[1] = "Bob"; 
		std::vector<std::vector<int> > v; 
		std::vector<int> inner; 
		inner.push_back(2);
		inner.push_back(1);
		v.push_back(inner);
		v.push_back(inner);
		std::string result = voting_eval(v, s, numCandidates);
        CPPUNIT_ASSERT(result == "Bob");
		delete[] s; 
		}
		
    void test_eval_3 () {
		int numCandidates = 3;
		std::string* s = new std::string[3];
		s[0] = "John"; 
		s[1] = "Bob"; 
		s[2] = "Nancy";
 		std::vector<std::vector<int> > v; 
		std::vector<int> inner; 
		std::vector<int> inner2; 
		std::vector<int> inner3; 
		inner.push_back(1);
		inner.push_back(2);
		inner.push_back(3);
		inner2.push_back(2);
		inner2.push_back(1);
		inner2.push_back(3);
		inner3.push_back(3);
		inner3.push_back(1);
		inner3.push_back(2);
		v.push_back(inner);
		v.push_back(inner2);
		v.push_back(inner3);
		std::string result = voting_eval(v, s, numCandidates);
        CPPUNIT_ASSERT(result == "John\nBob\nNancy");
		delete[] s; 
		}
 
    // -----
    // countVotes
    // -----

   void test_countVotes1 () {
	int* ballotCounts = new int[4];
	ballotCounts[0] = 0; 
	ballotCounts[1] = 3; 
	ballotCounts[2] = 3; 
	ballotCounts[3] = 3;
	int maxVotes; 
	int leastVotes; 
	std::vector<int> remainingCandidates;
	//load remainingCandidates Vector
	for(int i = 1; i <= 3; i++)
		remainingCandidates.push_back(i);
	bool tieFound = voting_countVotes(ballotCounts, remainingCandidates, maxVotes, leastVotes); 
    CPPUNIT_ASSERT(tieFound == true);
	CPPUNIT_ASSERT(maxVotes == 3);
	CPPUNIT_ASSERT(leastVotes == 3);
	delete[] ballotCounts; 
	}

   void test_countVotes2 () {
	int* ballotCounts = new int[4];
	ballotCounts[0] = 0; 
	ballotCounts[1] = 3; 
	ballotCounts[2] = 1; 
	ballotCounts[3] = 2;
	int maxVotes; 
	int leastVotes; 
	std::vector<int> remainingCandidates;
	//load remainingCandidates Vector
	for(int i = 1; i <= 3; i++)
		remainingCandidates.push_back(i);
	bool tieFound = voting_countVotes(ballotCounts, remainingCandidates, maxVotes, leastVotes); 
    CPPUNIT_ASSERT(tieFound == false);
	CPPUNIT_ASSERT(maxVotes == 3);
	CPPUNIT_ASSERT(leastVotes == 1);
	delete[] ballotCounts; 
	}

   void test_countVotes3 () {
	int* ballotCounts = new int[4];
	ballotCounts[0] = 0; 
	ballotCounts[1] = 3; 
	ballotCounts[2] = 1; 
	ballotCounts[3] = 3;
	int maxVotes; 
	int leastVotes; 
	std::vector<int> remainingCandidates;
	//load remainingCandidates Vector
	for(int i = 1; i <= 3; i++)
		remainingCandidates.push_back(i);
	bool tieFound = voting_countVotes(ballotCounts, remainingCandidates, maxVotes, leastVotes); 
    CPPUNIT_ASSERT(tieFound == false);
	CPPUNIT_ASSERT(maxVotes == 3);
	CPPUNIT_ASSERT(leastVotes == 1);
	delete[] ballotCounts; 
	}


    // -----
    // print
    // -----

    void test_print1 () {
        std::ostringstream w;
		std::string s = "HelloWorld\nHelloWorld2"; 
        voting_print(w, s, 1);
        CPPUNIT_ASSERT(w.str() == "\nHelloWorld\nHelloWorld2\n");}

    void test_print2 () {
        std::ostringstream w;
		std::string s = "HelloWorld"; 
        voting_print(w, s, 0);
        CPPUNIT_ASSERT(w.str() == "HelloWorld\n");}

    void test_print3 () {
        std::ostringstream w;
		std::string s = "HelloWorld"; 
        voting_print(w, s, 1);
        CPPUNIT_ASSERT(w.str() == "\nHelloWorld\n");}

    // -----
    // solve
    // -----

   void test_solve1 () {
        std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}

    void test_solve2 () {
        std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n\nJohn Doe\n");}

   void test_solve3 () {
        std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n2 1 3");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n\nJane Smith\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read1);
    CPPUNIT_TEST(test_read2);
    CPPUNIT_TEST(test_read3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_print1);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);
    CPPUNIT_TEST(test_solve1);
    CPPUNIT_TEST(test_solve2);
    CPPUNIT_TEST(test_solve3);
    CPPUNIT_TEST(test_countVotes1);
    CPPUNIT_TEST(test_countVotes2);
    CPPUNIT_TEST(test_countVotes3);
	
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