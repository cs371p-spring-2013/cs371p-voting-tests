// --------------------------------
// TestVoting.c++
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
#include <string>   // string, ==
#include <vector>   // vector

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

using namespace std;

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {

	// -----
	// voting_read_cases
	// -----

	void test_read_cases () {
		istringstream r ("1");
		int i;
		bool cases = voting_read_cases(r, i);
		CPPUNIT_ASSERT(i == 1);
		CPPUNIT_ASSERT(cases == true); }

	void test_read_cases_2 () {
		istringstream r ("1\n");
		int i;
		bool cases = voting_read_cases(r, i);
		CPPUNIT_ASSERT(i == 1);
		CPPUNIT_ASSERT(cases == true); }

	void test_read_cases_3 () {
		istringstream r ("\n1");
		int i;
		bool cases = voting_read_cases(r, i);
		CPPUNIT_ASSERT(i == 1);
		CPPUNIT_ASSERT(cases == true); }

	// -----
	// voting_read_candidates
	// -----

	void test_read_candidates () {
		istringstream r ("3\nDowning Downing\nEri Eli\nLuis Pugs\n");
		int i;
		vector< string > runners;
		bool candidates = voting_read_candidates(r, i, runners);
		vector< string > answer = {"Downing Downing", "Eri Eli", "Luis Pugs"};
		CPPUNIT_ASSERT(i == 3);
		CPPUNIT_ASSERT( (int)runners.size() == 3 );
		CPPUNIT_ASSERT ( runners == answer );
		CPPUNIT_ASSERT(candidates = true); }

	void test_read_candidates_2 () {
		istringstream r ("\n\n3\nFanciful Fancy\nMystical Mistic\nFailureful Fail\n");
		int i;
		vector< string > runners;
		bool candidates = voting_read_candidates(r, i, runners);
		vector< string > answer = {"Fanciful Fancy", "Mystical Mistic", "Failureful Fail"};
		CPPUNIT_ASSERT(i == 3);
		CPPUNIT_ASSERT( (int)runners.size() == 3 );
                CPPUNIT_ASSERT ( runners == answer );
		CPPUNIT_ASSERT(candidates == true); }

	void test_read_candidates_3 () {
		istringstream r ("\n3\nTesting Fun\nNofun Testing\nLetit Stop\n");
		vector< string > runners;
		int i;
		bool candidates = voting_read_candidates(r, i, runners );
		vector< string > answer = { "Testing Fun", "Nofun Testing", "Letit Stop"};
		CPPUNIT_ASSERT(i == 3);
		CPPUNIT_ASSERT( (int)runners.size() == 3 );
                CPPUNIT_ASSERT ( runners == answer );
		CPPUNIT_ASSERT(candidates == true); }

	// -----
	// voting_read_ballots
	// -----

	void test_read_ballots () {
		istringstream r ("1 3 2 4\n3 2 4 1\n1 4 2 3\n4 3 2 1\n\n");
		vector < vector < int > > b;
		vector < vector < int > > test = {{1,3,2,4},{3,2,4,1},{1,4,2,3},{4,3,2,1}};
		bool ballots = voting_read_ballots(r, b, 4);
		CPPUNIT_ASSERT(b == test); 
		CPPUNIT_ASSERT(ballots == true);}

	void test_read_ballots_2 () {
		istringstream r ("1 3 2 4 5\n3 5 2 4 1\n1 4 5 2 3\n4 5 3 2 1 \n\n");
		vector < vector < int > > b;
		vector < vector < int > > test = {{1,3,2,4,5},{3,5,2,4,1},{1,4,5,2,3},{4,5,3,2,1}};
		bool ballots = voting_read_ballots(r, b, 5);
		CPPUNIT_ASSERT(b == test);
		CPPUNIT_ASSERT(ballots == true); }
	
	void test_read_ballots_3 () {
		istringstream r ("1 3 2 4 5 6\n5 6 3 2 4 1\n5 1 4 2 3 6\n4 3 5 6 2 1\n5 6 3 2 4 1\n5 6 3 2 4 1\n");
		vector < vector < int > > b;
		vector < vector < int > > test = {{1,3,2,4,5,6},{5,6,3,2,4,1},{5,1,4,2,3,6},{4,3,5,6,2,1},{5,6,3,2,4,1},{5,6,3,2,4,1}};
		bool ballots = voting_read_ballots(r, b, 6);
		CPPUNIT_ASSERT(b == test);
		CPPUNIT_ASSERT(ballots == true); }

	// -----
	// voting_eval
	// -----

	void test_eval () {
		vector < vector < int > > ballots = {{1,3,2,4},{3,2,4,1},{1,4,2,3},{4,3,2,1}};
		vector < string > candidates = {"Luis Guevara","Eli Miller","Steve Seagulls","Glenn Downing"};
		vector < string > winners = voting_eval(candidates, candidates.size(), ballots, ballots.size());
		vector < string > test = {"Luis Guevara"};
		CPPUNIT_ASSERT(winners == test); }

	void test_eval_2 () {
		vector < vector < int > > ballots = {{1,3,2,4},{3,2,4,1},{1,4,2,3},{3,4,2,1}};
		vector < string > candidates = {"Luis Guevara","Eli Miller","Steve Seagulls","Glenn Downing"};
		vector < string > winners = voting_eval(candidates, candidates.size(), ballots, ballots.size());
		vector < string > test = {"Luis Guevara","Steve Seagulls"};
		CPPUNIT_ASSERT(winners == test); }
	
	void test_eval_3 () {
		vector < vector < int > > ballots = {{1,2,3,4},{1,3,2,4},{2,3,1,4},{2,3,1,4},{3,2,1,4},{4,1,3,2},{3,4,2,1}};
		vector < string > candidates = {"Luis Guevara","Eli Miller","Steve Seagulls","Glenn Downing"};
		vector < string > winners = voting_eval(candidates, candidates.size(), ballots, ballots.size());
		vector < string > test = {"Luis Guevara"};
		CPPUNIT_ASSERT(winners == test); }
	void test_eval_4 () {
		vector < vector < int > > ballots = {{1,2,3,4},{4,3,2,1},{3,3,1,2},{2,3,1,4}};
		vector < string > candidates = {"Luis Guevara","Eli Miller","Steve Seagulls","Glenn Downing"};
		vector < string > winners = voting_eval(candidates, candidates.size(), ballots, ballots.size());
		vector < string > test = {"Luis Guevara","Eli Miller","Steve Seagulls","Glenn Downing"};
		CPPUNIT_ASSERT(winners == test); }

	// -----
	// voting_print
	// -----

	void test_print () {
		ostringstream w;
		vector<string> tester = {"Soda Popinski","Albert Wesker","Knuckles Echinda"};
		voting_print (w, tester, tester.size());
		CPPUNIT_ASSERT(w.str() == "Soda Popinski\nAlbert Wesker\nKnuckles Echinda"); }
        void test_print_2 () {
                ostringstream w;
                vector<string> tester = {"Eri Mirrer","Luis Guevara"};
                voting_print (w, tester, tester.size());
                CPPUNIT_ASSERT(w.str() == "Eri Mirrer\nLuis Guevara"); }
        void test_print_3 () {
                ostringstream w;
                vector<string> tester = {"Soda Popinski","Albert Wesker","Knuckles Echinda", "Eri Mirrer","Luis Guevara"};
                voting_print (w, tester, tester.size());
                CPPUNIT_ASSERT(w.str() == "Soda Popinski\nAlbert Wesker\nKnuckles Echinda\nEri Mirrer\nLuis Guevara"); }

	// -----
	// voting_solve
	// -----
	
	void test_solve () {
		ostringstream n;
		istringstream y ("2\n\n3\nLuis Guevara\nEri Mirrer\nAli Homafar\n1 2 3\n 2 1 3\n3 1 2\n1 3 2\n2 3 1\n1 2 3\n1 3 2\n\n2\nLuis Guevara\nEri Mirrer\n2 1\n2 1\n2 1\n");
		voting_solve(y,n);
		CPPUNIT_ASSERT(n.str() == "Luis GuevaraEri Mirrer"); }
	// -----
	// suite
	// -----

	CPPUNIT_TEST_SUITE(TestVoting);
	CPPUNIT_TEST(test_read_cases);
	CPPUNIT_TEST(test_read_cases_2);
	CPPUNIT_TEST(test_read_cases_3);
	CPPUNIT_TEST(test_read_candidates);
	CPPUNIT_TEST(test_read_candidates_2);
	CPPUNIT_TEST(test_read_candidates_3);
	CPPUNIT_TEST(test_read_ballots);
	CPPUNIT_TEST(test_read_ballots_2);
	CPPUNIT_TEST(test_read_ballots_3);
	CPPUNIT_TEST(test_eval);
	CPPUNIT_TEST(test_eval_2);
	CPPUNIT_TEST(test_eval_3);
	CPPUNIT_TEST(test_eval_4);
	CPPUNIT_TEST(test_print);
	CPPUNIT_TEST(test_print_2);
	CPPUNIT_TEST(test_print_3);
	CPPUNIT_TEST(test_solve);
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
	return 0; }
