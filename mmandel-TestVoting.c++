// --------------------------------
// TestVoting.c++
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

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {
	
	// --------------
    // read_num_cases
    // --------------
	
    void test_read_num_cases_1 () {
        std::istringstream r("1\n\n2\nMichelle Mandel\nAlice Biray\n1 2");
        int num_cases;
        const bool b = voting_read_num_cases(r, num_cases);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(num_cases ==    1);}

	void test_read_num_cases_2 () {
        std::istringstream r("2\n");
        int num_cases;
        const bool b = voting_read_num_cases(r, num_cases);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(num_cases ==    2);}

	void test_read_num_cases_3 () {
        std::istringstream r("10\n\n1\nM\n1\n\n1\nA\n1\n\n1\n\nM\n1\n\n1\nA\n1\n\n1\n\nM\n1\n\n1\nA\n1\n\n1\n\nM\n1\n\n1\nA\n1\n\n1\n\nM\n1\n\n1\nA\n1\n\n");
        int num_cases;
        const bool b = voting_read_num_cases(r, num_cases);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(num_cases ==    10);}
		
	void test_read_num_cases_4 () {
        std::istringstream r("");
        int num_cases;
        const bool b = voting_read_num_cases(r, num_cases);
        CPPUNIT_ASSERT(b == false);}
		
		
	// ------------------
    // read_num_cadidates
    // ------------------
	
    void test_read_num_candidates_1 () {
        std::istringstream r("2\nMichelle Mandel\nAlice Biray\n1 2");
        int num_cands;
        const bool b = voting_read_num_candidates(r, num_cands);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(num_cands ==    2);}

	void test_read_num_candidates_2 () {
        std::istringstream r("10\nMichelle Mandel\nAlice Biray\n1 2");
        int num_cands;
        const bool b = voting_read_num_candidates(r, num_cands);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(num_cands ==    10);}
		
	void test_read_num_candidates_3 () {
        std::istringstream r("200\nMichelle Mandel\nAlice Biray\n1 2");
        int num_cands;
        const bool b = voting_read_num_candidates(r, num_cands);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(num_cands ==    200);}
		
	void test_read_num_candidates_4 () {
        std::istringstream r("");
        int num_cands;
        const bool b = voting_read_num_candidates(r, num_cands);
        CPPUNIT_ASSERT(b == false);}
		
		
	// ---------------
    // read_cadidates
    // ---------------
	
    void test_read_candidates_1 () {
        std::istringstream r("2\nMichelle Mandel\nAlice Biray\n1 2");
        const bool b = voting_read_candidates(r, 2);
        CPPUNIT_ASSERT(b == true);}	
		
	void test_read_candidates_2 () {
        std::istringstream r("");
        const bool b = voting_read_candidates(r, 0);
        CPPUNIT_ASSERT(b == false);}		
		
	void test_read_candidates_3 () {
        std::istringstream r("1\nMichelle Mandel");
        const bool b = voting_read_candidates(r, 1);
        CPPUNIT_ASSERT(b == true);}	
		
		
	// -------------
    // read_ballots
    // -------------
	
    void test_read_ballots_1 () {
        std::istringstream r("2 1\n1 2");
        const bool b = voting_read_ballots(r, 2);
        CPPUNIT_ASSERT(b == true);}	
	
	void test_read_ballots_2 () {
        std::istringstream r("2 1\n1 2\n");
        const bool b = voting_read_ballots(r, 2);
        CPPUNIT_ASSERT(b == true);}	
		
	void test_read_ballots_3 () {
        std::istringstream r("2 1\n1 2\n\n");
        const bool b = voting_read_ballots(r, 2);
        CPPUNIT_ASSERT(b == true);}	
	
		
	// ------------
    // calc_winner	-- too many globals needed to test this function
    // ------------
	/*
    void test_calc_winner_1 () {
        std::istringstream r("1\n\n2\nMichelle\nAlice\n2 1\n1 2");
        const bool b = voting_calc_winner(2);
        CPPUNIT_ASSERT(b == true);}		
	*/	
		

/*
    // -----
    // print - need global to test
    // -----

    void test_print_1 () {
        std::ostringstream w;
        voting_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}
*/


    // -----
    // solve
    // -----
	void test_solve_1 () {
        std::istringstream r("1\n\n2\nMichelle Mandel\nAlice Biray\n1 2");
		std::ostringstream w;
        voting_solve(r, w);		
		CPPUNIT_ASSERT(w.str() == "Michelle Mandel\n");}
		
	void test_solve_2 () {
        std::istringstream r("1\n\n1\nMichelle\n1");
		std::ostringstream w;
        voting_solve(r, w);		
		CPPUNIT_ASSERT(w.str() == "Michelle\n");}
		
	void test_solve_3 () {
        std::istringstream r("1\n\n2\nMichelle Mandel\nAlice Biray\n1 2\n2 1\n2 1");
		std::ostringstream w;
        voting_solve(r, w);		
		CPPUNIT_ASSERT(w.str() == "Alice Biray\n");}
		
	void test_solve_4 () {
        std::istringstream r("1\n\n2\nMichelle\nAlice\n1 2\n2 1");
		std::ostringstream w;
        voting_solve(r, w);		
		CPPUNIT_ASSERT(w.str() == "Michelle\nAlice\n");}
		
	void test_solve_5 () {
        std::istringstream r("1\n\n3\nA\nB\nC\n1 2 3\n2 3 1\n3 2 1\n1 2 3\n2 3 1");
		std::ostringstream w;
        voting_solve(r, w);		
		CPPUNIT_ASSERT(w.str() == "B\n");}
		
	void test_solve_6 () {
        std::istringstream r("1\n\n3\nA\nB\nC\n1 2 3\n2 3 1\n3 2 1\n3 1 2\n1 2 3\n2 1 3\n1 3 2\n2 3 1");
		std::ostringstream w;
        voting_solve(r, w);		
		CPPUNIT_ASSERT(w.str() == "A\nB\n");}
	
	void test_solve_7 () {
        std::istringstream r("1\n\n3\nA \nB \nC \n1 2 3 \n2 3 1 \n3 2 1 \n3 1 2 \n1 2 3 \n2 1 3 \n1 3 2 \n2 3 1 ");
		std::ostringstream w;
        voting_solve(r, w);		
		CPPUNIT_ASSERT(w.str() == "A \nB \n");}

		
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
	CPPUNIT_TEST(test_read_num_cases_1);
	CPPUNIT_TEST(test_read_num_cases_2);
	CPPUNIT_TEST(test_read_num_cases_3);
	CPPUNIT_TEST(test_read_num_cases_4);
	CPPUNIT_TEST(test_read_num_candidates_1);
	CPPUNIT_TEST(test_read_num_candidates_2);
	CPPUNIT_TEST(test_read_num_candidates_3);
	CPPUNIT_TEST(test_read_num_candidates_4);
	CPPUNIT_TEST(test_read_candidates_1);
	CPPUNIT_TEST(test_read_candidates_2);
	CPPUNIT_TEST(test_read_candidates_3);
	CPPUNIT_TEST(test_read_ballots_1);
	CPPUNIT_TEST(test_read_ballots_2);
	CPPUNIT_TEST(test_read_ballots_3);
	//CPPUNIT_TEST(test_calc_winner_1);
	//CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);
    CPPUNIT_TEST(test_solve_5);
    CPPUNIT_TEST(test_solve_6);
    CPPUNIT_TEST(test_solve_7);
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
