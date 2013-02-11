// --------------------------------
// projects/voting/TestVoting.c++
// Copyright (C) 2013
// cmbes
// --------------------------------

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
// TestCollatz
// -----------

struct TestVoting : CppUnit::TestFixture {

    // ----
    // eval
    // ----

		
		/**Baseline test**/
    void test_eval_1 () {
				Voting_Scenario vs;
				vs.add_candidate("John Doe");
				vs.add_candidate("Jane Smith");
				vs.add_candidate("Sirhan Sirhan");
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(2);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(1);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(3);
					b.add_vote(1);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(2);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(3);
					b.add_vote(1);
					b.add_vote(2);
					vs.add_ballot(b);
				}
        const string v = voting_eval(vs);
        CPPUNIT_ASSERT(v == "John Doe\n");
		}

		/**All votes for 1**/
    void test_eval_2 () {
        Voting_Scenario vs;
				vs.add_candidate("John Doe");
				vs.add_candidate("Jane Smith");
				vs.add_candidate("Sirhan Sirhan");
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(2);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(2);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(3);
					b.add_vote(2);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(2);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(3);
					b.add_vote(2);
					vs.add_ballot(b);
				}
        const string v = voting_eval(vs);
        CPPUNIT_ASSERT(v == "John Doe\n");
		}

		/**All votes for 2**/
    void test_eval_3 () {
				Voting_Scenario vs;
				vs.add_candidate("John Doe");
				vs.add_candidate("Jane Smith");
				vs.add_candidate("Sirhan Sirhan");
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(1);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(1);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(3);
					b.add_vote(1);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(1);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(3);
					b.add_vote(1);
					vs.add_ballot(b);
				}
        const string v = voting_eval(vs);
        CPPUNIT_ASSERT(v == "Jane Smith\n");
		}

		/**All votes for 3**/
    void test_eval_4 () {
        Voting_Scenario vs;
				vs.add_candidate("John Doe");
				vs.add_candidate("Jane Smith");
				vs.add_candidate("Sirhan Sirhan");
				{
					Ballot b;
					b.add_vote(3);
					b.add_vote(2);
					b.add_vote(1);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(3);
					b.add_vote(2);
					b.add_vote(1);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(3);
					b.add_vote(1);
					b.add_vote(2);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(3);
					b.add_vote(2);
					b.add_vote(1);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(3);
					b.add_vote(1);
					b.add_vote(2);
					vs.add_ballot(b);
				}
        const string v = voting_eval(vs);
        CPPUNIT_ASSERT(v == "Sirhan Sirhan\n");
		}
		
		/**3 Way Tie**/
    void test_eval_5 () {
        Voting_Scenario vs;
				vs.add_candidate("John Doe");
				vs.add_candidate("Jane Smith");
				vs.add_candidate("Sirhan Sirhan");
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(2);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(1);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(3);
					b.add_vote(1);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(2);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(3);
					b.add_vote(1);
					b.add_vote(2);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(3);
					b.add_vote(1);
					b.add_vote(2);
					vs.add_ballot(b);
				}
        const string v = voting_eval(vs);
        CPPUNIT_ASSERT(v == "John Doe\nJane Smith\nSirhan Sirhan\n");
		}
		
		
		/**Tie to be eliminated**/
    void test_eval_6 () {
        Voting_Scenario vs;
				stringstream ss(stringstream::in | stringstream::out);
				ss << "14\nA\nB\nC\nD\nE\nF\nG\nH\nI\nJ\nK\nL\nM\nN\n12 5 11 8 6 13 3 2 10 1 7 9 14 4\n8 14 1 13 11 12 5 4 3 10 2 6 7 9\n13 12 14 5 7 11 3 10 2 1 9 8 4 6\n12 3 7 11 2 10 13 5 9 1 6 14 8 4\n11 14 13 1 7 4 2 12 5 3 8 10 9 6\n4 3 12 8 5 1 2 7 13 11 10 14 6 9\n6 14 3 11 1 5 10 7 13 2 12 4 8 9\n";
				retrieve(ss, vs);
        //cout << vs;
				const string v = voting_eval(vs);
        CPPUNIT_ASSERT(v == "L\n");
		}
		
		/**Multiple elimination**/
    void test_eval_7 () {
        Voting_Scenario vs;
				stringstream ss(stringstream::in | stringstream::out);
				ss << "5\nA\nB\nC\nD\nE\n1 2 5 3 4\n2 1 3 5 4\n1 2 5 4 3\n2 1 3 4 5\n3 5 4 2 1\n";
				retrieve(ss, vs);
        //cout << vs;
				const string v = voting_eval(vs);
        CPPUNIT_ASSERT(v == "B\n");
		}
		
		
    void test_eval_8 () {
        Voting_Scenario vs;
				stringstream ss(stringstream::in | stringstream::out);
				ss << "6\nA\nB\nC\nD\nE\nF\n2 1 6 5 3 4\n6 3 2 5 4 1\n5 2 6 1 3 4\n3 6 1 5 2 4\n1 2 4 6 3 5\n3 2 5 6 1 4\n5 6 2 4 3 1\n5 3 1 4 2 6\n2 4 5 6 3 1\n2 5 3 4 6 1";
				retrieve(ss, vs);
        //cout << vs;
				const string v = voting_eval(vs);
        CPPUNIT_ASSERT(v == "B\n");
		}

		
		/** No ballots **/
		void test_eval_9 () {
        Voting_Scenario vs;
				stringstream ss(stringstream::in | stringstream::out);
				ss << "6\nA\nB\nC\nD\nE\nF\n";
				retrieve(ss, vs);
        //cout << vs;
				const string v = voting_eval(vs);
        CPPUNIT_ASSERT(v == "A\nB\nC\nD\nE\nF\n");
		}
		
    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        voting_print(w, "winner");
        CPPUNIT_ASSERT(w.str() == "winner");
		}
		
		void test_print_2 () {
        std::ostringstream w;
        voting_print(w, "");
        CPPUNIT_ASSERT(w.str() == "");
		}
		
		void test_print_3 () {
        std::ostringstream w;
        voting_print(w, "\n\n\n");
        CPPUNIT_ASSERT(w.str() == "\n\n\n");
		}
		
		void test_print_4 () {
        std::ostringstream w;
        voting_print(w, "aaaaaaaaaaaaaaaaa");
        CPPUNIT_ASSERT(w.str() == "aaaaaaaaaaaaaaaaa");
		}
		
		void test_print_5 () {
        std::ostringstream w;
        voting_print(w, "ee");
        CPPUNIT_ASSERT(w.str() == "ee");
		}
		void test_print_6 () {
        std::ostringstream w;
        voting_print(w, "lol these tests are useless");
        CPPUNIT_ASSERT(w.str() == "lol these tests are useless");
		}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1\n\n14\nA\nB\nC\nD\nE\nF\nG\nH\nI\nJ\nK\nL\nM\nN\n12 5 11 8 6 13 3 2 10 1 7 9 14 4\n8 14 1 13 11 12 5 4 3 10 2 6 7 9\n13 12 14 5 7 11 3 10 2 1 9 8 4 6\n12 3 7 11 2 10 13 5 9 1 6 14 8 4\n11 14 13 1 7 4 2 12 5 3 8 10 9 6\n4 3 12 8 5 1 2 7 13 11 10 14 6 9\n6 14 3 11 1 5 10 7 13 2 12 4 8 9\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "L\n");
		}
		
		void test_solve_2 () {
        std::istringstream r("1\n\n14\nA\nB\nC\nD\nE\nF\nG\nH\nI\nJ\nK\nL\nM\nN\n12 5 11 8 6 13 3 2 10 1 7 9 14 4\n8 14 1 13 11 12 5 4 3 10 2 6 7 9\n13 12 14 5 7 11 3 10 2 1 9 8 4 6\n12 3 7 11 2 10 13 5 9 1 6 14 8 4\n11 14 13 1 7 4 2 12 5 3 8 10 9 6\n4 3 12 8 5 1 2 7 13 11 10 14 6 9\n6 14 3 11 1 5 10 7 13 2 12 4 8 9\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "L\n");
		}
		
		void test_solve_3 () {
        std::istringstream r("1\n\n6\nA\nB\nC\nD\nE\nF\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "A\nB\nC\nD\nE\nF\n");
		}
		
		void test_solve_4 () {
        std::istringstream r("1\n\n5\nA\nB\nC\nD\nE\n1 2 5 3 4\n2 1 3 5 4\n1 2 5 4 3\n2 1 3 4 5\n3 5 4 2 1\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "B\n");
		}
		
		
		// --------
		// retrieve
		// --------
		
		void test_retrieve_1() {
				std::istringstream r("5\nA\nB\nC\nD\nE\n1 2 5 3 4\n2 1 3 5 4\n1 2 5 4 3\n2 1 3 4 5\n3 5 4 2 1\n");
        Voting_Scenario vs;
        retrieve(r, vs);
        CPPUNIT_ASSERT(vs.num_candidates() == 5);
		}
		
		void test_retrieve_2() {
				Voting_Scenario vs;
				std::istringstream r("6\nA\nB\nC\nD\nE\nF\n2 1 6 5 3 4\n6 3 2 5 4 1\n5 2 6 1 3 4\n3 6 1 5 2 4\n1 2 4 6 3 5\n3 2 5 6 1 4\n5 6 2 4 3 1\n5 3 1 4 2 6\n2 4 5 6 3 1\n2 5 3 4 6 1");
				retrieve(r, vs);
        CPPUNIT_ASSERT(vs.num_candidates() == 6);
		}
		
		void test_retrieve_3() {
				Voting_Scenario vs;
				std::istringstream r("6\nA\nB\nC\nD\nE\nF\n");
				retrieve(r, vs);
        CPPUNIT_ASSERT(vs.num_candidates() == 6);
		}
		
		void test_retrieve_4() {
				Voting_Scenario vs;
				std::istringstream r("14\nA\nB\nC\nD\nE\nF\nG\nH\nI\nJ\nK\nL\nM\nN\n12 5 11 8 6 13 3 2 10 1 7 9 14 4\n8 14 1 13 11 12 5 4 3 10 2 6 7 9\n13 12 14 5 7 11 3 10 2 1 9 8 4 6\n12 3 7 11 2 10 13 5 9 1 6 14 8 4\n11 14 13 1 7 4 2 12 5 3 8 10 9 6\n4 3 12 8 5 1 2 7 13 11 10 14 6 9\n6 14 3 11 1 5 10 7 13 2 12 4 8 9\n");
				retrieve(r, vs);
        CPPUNIT_ASSERT(vs.num_candidates() == 14);
		}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_eval_8);
    CPPUNIT_TEST(test_eval_9);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_print_4);
    CPPUNIT_TEST(test_print_5);
    CPPUNIT_TEST(test_print_6);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);
		CPPUNIT_TEST(test_retrieve_1);
		CPPUNIT_TEST(test_retrieve_2);
		CPPUNIT_TEST(test_retrieve_3);
		CPPUNIT_TEST(test_retrieve_4);
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