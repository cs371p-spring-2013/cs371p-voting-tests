// --------------------------------
// projects/collatz/TestVoting.c++
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
#include <string>   // ==
#include <vector>
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"
#include <stdio.h>

using namespace std;
// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read () {
        istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n1 2 3\n3 1 2");
        vector<election> elections;
	int numElections;
        const bool b = voting_read(r, elections,numElections);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(numElections == 1);
        CPPUNIT_ASSERT(elections[0].numCandidates == 3);
        CPPUNIT_ASSERT(elections[0].candidates[0] == "John Doe");
	CPPUNIT_ASSERT(elections[0].candidates[1] == "Jane Smith");
	CPPUNIT_ASSERT(elections[0].candidates[2] == "Sirhan Sirhan");
	CPPUNIT_ASSERT(elections[0].ballots[0][0] == 1);
	CPPUNIT_ASSERT(elections[0].ballots[0][1] == 2);
	CPPUNIT_ASSERT(elections[0].ballots[0][2] == 3);
	CPPUNIT_ASSERT(elections[0].ballots[1][0] == 2);
	CPPUNIT_ASSERT(elections[0].ballots[1][1] == 1);
	CPPUNIT_ASSERT(elections[0].ballots[1][2] == 3);
	CPPUNIT_ASSERT(elections[0].ballots[2][0] == 1);
	CPPUNIT_ASSERT(elections[0].ballots[2][1] == 2);
	CPPUNIT_ASSERT(elections[0].ballots[2][2] == 3);
	CPPUNIT_ASSERT(elections[0].ballots[3][0] == 3);
	CPPUNIT_ASSERT(elections[0].ballots[3][1] == 1);
	CPPUNIT_ASSERT(elections[0].ballots[3][2] == 2);
	}

    void test_read1 () {
	istringstream r("2\n\n2\nGlenn Downing\nJane Smith\n2 1\n1 2\n1 2\n\n3\nGlenn Downing\nJane Doe\nJohn Smith\n1 2 3\n3 1 2\n1 3 2");
	vector<election> elections;
	int numElections;
	const bool b = voting_read(r, elections, numElections);
        CPPUNIT_ASSERT(b == true);
	CPPUNIT_ASSERT(numElections == 2);
	CPPUNIT_ASSERT(elections[0].numCandidates == 2);
	CPPUNIT_ASSERT(elections[0].candidates[0] == "Glenn Downing");
	CPPUNIT_ASSERT(elections[0].candidates[1] == "Jane Smith");
	CPPUNIT_ASSERT(elections[0].ballots[0][0] == 2);
	CPPUNIT_ASSERT(elections[0].ballots[0][1] == 1);
	CPPUNIT_ASSERT(elections[0].ballots[1][0] == 1);
	CPPUNIT_ASSERT(elections[0].ballots[1][1] == 2);
	CPPUNIT_ASSERT(elections[0].ballots[2][0] == 1);
	CPPUNIT_ASSERT(elections[0].ballots[2][1] == 2);
	CPPUNIT_ASSERT(elections[1].numCandidates == 3);
	CPPUNIT_ASSERT(elections[1].candidates[0] == "Glenn Downing");
	CPPUNIT_ASSERT(elections[1].candidates[1] == "Jane Doe");
	CPPUNIT_ASSERT(elections[1].candidates[2] == "John Smith");
	CPPUNIT_ASSERT(elections[1].ballots[0][0] == 1);

	CPPUNIT_ASSERT(elections[1].ballots[0][1] == 2);
	CPPUNIT_ASSERT(elections[1].ballots[0][2] == 3);
	CPPUNIT_ASSERT(elections[1].ballots[1][0] == 3);
	CPPUNIT_ASSERT(elections[1].ballots[1][1] == 1);
	CPPUNIT_ASSERT(elections[1].ballots[1][2] == 2);
	CPPUNIT_ASSERT(elections[1].ballots[2][0] == 1);
	CPPUNIT_ASSERT(elections[1].ballots[2][1] == 3);
	CPPUNIT_ASSERT(elections[1].ballots[2][2] == 2);
}

    void test_read2(){
	std::istringstream r("1\n\n1\nGlenn Downing\n1");
	int numElections;
	vector<election> elections;
	const bool b = voting_read(r, elections, numElections);
	CPPUNIT_ASSERT(numElections == 1);
	CPPUNIT_ASSERT(elections[0].numCandidates == 1);
	CPPUNIT_ASSERT(elections[0].candidates[0] == "Glenn Downing");
	CPPUNIT_ASSERT(elections[0].ballots[0][0] == 1);
	CPPUNIT_ASSERT(b == true);
}


    // ----
    // eval
    // ----

    void test_eval_1 () {
	election elec;
	elec.numCandidates = 3;
	vector<string> candidates = {"John Doe", "Jane Smith", "Sirhan Sirhan"};
	elec.candidates = candidates;
	vector<int> ballot1 = {1,2,3};
	vector<int> ballot2 = {2,1,3};
	vector<int> ballot3 = {2,3,1};
	vector<int> ballot4 = {1,2,3};
	vector<int> ballot5 = {3,1,2};
	vector<vector<int>> ballots = {ballot1, ballot2, ballot3, ballot4, ballot5};
	elec.ballots = ballots;
        const vector<string> v = voting_eval(elec);
        CPPUNIT_ASSERT(v[0] == "John Doe");}

    void test_eval_2 () {
	election elec;
	elec.numCandidates = 1;
	vector<string> candidates = {"John Doe"};
	elec.candidates = candidates;
	vector<int> ballot1 = {1};
	vector<vector<int>> ballots = {ballot1};
	elec.ballots = ballots;
        const vector<string> v = voting_eval(elec);
        CPPUNIT_ASSERT(v[0] == "John Doe");}

    void test_eval_3 () {
	election elec;
	elec.numCandidates = 4;
	vector<string> candidates = {"Red", "Green", "Blue", "Orange"};
	elec.candidates = candidates;
	vector<int> ballot1 = {1,2,3,4};
	vector<int> ballot2 = {2,1,3,4};
	vector<int> ballot3 = {2,3,1,4};
	vector<int> ballot4 = {1,2,3,4};
	vector<int> ballot5 = {3,4,1,2};
	vector<int> ballot6 = {4,3,2,1};
	vector<vector<int>> ballots = {ballot1, ballot2, ballot3, ballot4, ballot5, ballot6};
	elec.ballots = ballots;
        const vector<string> v = voting_eval(elec);
        CPPUNIT_ASSERT(v[0] == "Red");
	CPPUNIT_ASSERT(v[1] == "Green");
	}


    void test_eval_4 () {
	election elec;
	elec.numCandidates = 4;
	vector<string> candidates = {"Red", "Green", "Blue", "Orange"};
	elec.candidates = candidates;
	vector<int> ballot1 = {1,2,3,4};
	vector<int> ballot2 = {2,1,3,4};
	vector<int> ballot3 = {2,3,1,4};
	vector<int> ballot4 = {1,2,3,4};
	vector<int> ballot5 = {3,4,1,2};
	vector<int> ballot6 = {4,3,2,1};
	vector<vector<int>> ballots = {ballot5, ballot6, ballot3, ballot4, ballot1, ballot2};
	elec.ballots = ballots;
        const vector<string> v = voting_eval(elec);
        CPPUNIT_ASSERT(v[0] == "Red");
	CPPUNIT_ASSERT(v[1] == "Green");
	}

    void test_eval_5 () {
	election elec;
	elec.numCandidates = 5;
	vector<string> candidates = {"Evolved Dove", "Mature Terrier", "Quick Dove", "Sinful Downing", "Needy Oryx"};
	elec.candidates = candidates;
	vector<int> ballot1 = {5,2,4,3,1};
	vector<int> ballot2 = {1,4,3,2,5};
	vector<int> ballot3 = {2,5,3,1,4};
	vector<int> ballot4 = {5,3,4,2,1};
	vector<int> ballot5 = {2,5,4,1,3};
	vector<int> ballot6 = {4,5,2,1,3};
	vector<int> ballot7 = {4,3,2,5,1};
	vector<int> ballot8 = {4,5,3,2,1};
	vector<int> ballot9 = {4,3,5,2,1};
	vector<int> ballot10 = {1,2,3,5,4};
	vector<vector<int>> ballots = {ballot1, ballot2, ballot3, ballot4, ballot5, ballot6, ballot7, ballot8, ballot9, ballot10};
	elec.ballots = ballots;
        const vector<string> v = voting_eval(elec);
        CPPUNIT_ASSERT(v[0] == "Sinful Downing");
	}
    // -----
    // print
    // -----

    void test_print1 () {
        std::ostringstream w;
	vector<string> v = {"John Doe"};
        voting_print(w, v);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}

	
    void test_print2 () {
        std::ostringstream w;
	vector<string> v = {"John Doe", "Bruno Mars"};
        voting_print(w, v);
        CPPUNIT_ASSERT(w.str() == "John Doe\nBruno Mars\n");}

	
    void test_print3 () {
        std::ostringstream w;
	vector<string> v = {"Glenn Downing", "Glenn Downing"};
        voting_print(w, v);
        CPPUNIT_ASSERT(w.str() == "Glenn Downing\nGlenn Downing\n");}

    // --------
    // inLosers
    // --------

    void test_inLosers1(){
	int k = 3;
	vector<int> losers = {1, 2, 3};
	vector<int> remaining = {3, 4};
	bool b = inLosers(k, losers, remaining);
	CPPUNIT_ASSERT(b == true);
    }


    void test_inLosers2(){
	int k = 3;
	vector<int> losers = {1, 2, 4};
	vector<int> remaining = {3, 5};
	bool b = inLosers(k, losers, remaining);
	CPPUNIT_ASSERT(b == false);
    }


    void test_inLosers3(){
	int k = 0;
	vector<int> losers;
	vector<int> remaining;
	bool b = inLosers(k, losers, remaining);
	CPPUNIT_ASSERT(b == true);
    }
	

    // -----
    // solve
    // -----

    void test_solve1 () {
        istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n1 2 3\n3 1 2");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}

    void test_solve2 () {
	istringstream r("2\n\n2\nGlenn Downing\nJane Smith\n2 1\n1 2\n1 2\n\n3\nGlenn Downing\nJane Doe\nJohn Smith\n1 2 3\n3 1 2\n1 3 2");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Glenn Downing\n\nGlenn Downing\n");}
    
    void test_solve3 () {	
	std::istringstream r("1\n\n1\nGlenn Downing\n1");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Glenn Downing\n");}

    void test_solve4() {
	std::istringstream r("2\n\n3\nJohn Doe\nSirhan Sirhan\nJane Smith\n1 2 3\n3 1 2\n2 3 1\n1 2 3\n3 1 2\n2 1 3\n\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\nReza Sheerhan\n1 2 3 4\n2 3 4 1\n3 4 1 2\n4 3 2 1");
	std::ostringstream w;
	voting_solve(r, w);
	CPPUNIT_ASSERT(w.str() == "John Doe\nSirhan Sirhan\nJane Smith\n\nJohn Doe\nJane Smith\nSirhan Sirhan\nReza Sheerhan\n");
	}


     void test_solve5(){
	std::istringstream r("1\n\n4\nFriendly Boobs\nHelpful Hyena\nNeedy Sardine\nQuizzical Hawk\n2 1 3 4\n1 3 2 4\n3 2 1 4\n4 3 2 1\n2 1 3 4\n4 2 3 1\n1 3 4 2\n2 3 1 4\n4 1 2 3\n3 4 1 2\n1 4 2 3\n4 1 2 3\n1 2 3 4\n4 3 2 1\n4 2 3 1\n2 3 1 4\n2 3 1 4\n2 4 1 3\n3 4 2 1\n2 3 1 4");
	std::ostringstream w;
	voting_solve(r, w);
	CPPUNIT_ASSERT(w.str() == "Helpful Hyena\nQuizzical Hawk\n");
	}
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read1);
    CPPUNIT_TEST(test_read2);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4); 
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_inLosers1);
    CPPUNIT_TEST(test_inLosers2);
    CPPUNIT_TEST(test_inLosers3);
    CPPUNIT_TEST(test_solve1);
    CPPUNIT_TEST(test_solve2);
    CPPUNIT_TEST(test_solve3); 
    CPPUNIT_TEST(test_solve4);
    CPPUNIT_TEST(test_solve5);
    CPPUNIT_TEST(test_print1);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3); 
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
