// --------------------------------
// TestVoting.c++
// Ruoxing
// Lynette Perkins
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -lcppunit -ldl -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz.c++.app
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
    // vote_all_tied
    // ----

	void test_vote_all_tied_1(){
		vector<int> v;
		v.push_back(0);
		v.push_back(2);
		v.push_back(0);
		v.push_back(2);
		v.push_back(0);
		bool result = vote_all_tied(v);
		CPPUNIT_ASSERT(result == true);
	}

	void test_vote_all_tied_2(){
		vector<int> v;
		v.push_back(0);
		v.push_back(123);
		v.push_back(1);
		v.push_back(444);
		v.push_back(0);
		bool result = vote_all_tied(v);
		CPPUNIT_ASSERT(result == false);
	}

	void test_vote_all_tied_3(){
		vector<int> v;
		v.push_back(0);
		v.push_back(2);
		v.push_back(11);
		v.push_back(2);
		v.push_back(3);
		bool result = vote_all_tied(v);
		CPPUNIT_ASSERT(result == false);
	}

    // -----
    // completed
    // -----
	
	void test_completed_1(){
		vector<string> peopleList;
		int numVotes = 100;
		vector<int> count;
		peopleList.push_back("xxxxxxx");
		peopleList.push_back("Bush");
		peopleList.push_back("Clinton");
		peopleList.push_back("Obama");
		count.push_back(0);
		count.push_back(50);
		count.push_back(50);
		count.push_back(0);
		bool result = completed(numVotes, count, peopleList);
		CPPUNIT_ASSERT(result == true);
	}

	void test_completed_2(){
		vector<string> peopleList;
		int numVotes = 100;
		vector<int> count;
		peopleList.push_back("xxxxxxx");
		peopleList.push_back("Bush");
		peopleList.push_back("Clinton");
		peopleList.push_back("Obama");
		count.push_back(0);
		count.push_back(33);
		count.push_back(33);
		count.push_back(34);
		bool result = completed(numVotes, count, peopleList);
		CPPUNIT_ASSERT(result == false);
	}

	void test_completed_3(){
		vector<string> peopleList;
		int numVotes = 100;
		vector<int> count;
		peopleList.push_back("xxxxxxx");
		peopleList.push_back("Bush");
		peopleList.push_back("Clinton");
		peopleList.push_back("Obama");
		count.push_back(0);
		count.push_back(70);
		count.push_back(30);
		count.push_back(0);
		bool result = completed(numVotes, count, peopleList);
		CPPUNIT_ASSERT(result == true);
	}

    // -----
    // makeBallots
    // -----


	void test_makeBallots_1(){
		string s = "1 2 3 4 5";
		vector<int> v = makeBallots(s);
		vector<int> result;
		result.push_back(1);
		result.push_back(2);
		result.push_back(3);
		result.push_back(4);
		result.push_back(5);
		CPPUNIT_ASSERT(equal(v.data(), v.data()+5, result.data()));
	}

	void test_makeBallots_2(){
		string s = "654654 7987897";
		vector<int> v = makeBallots(s);
		vector<int> result;
		result.push_back(654654);
		result.push_back(7987897);
		CPPUNIT_ASSERT(equal(v.data(), v.data()+2, result.data()));
	}

	void test_makeBallots_3(){
		string s = "12 20 89";
		vector<int> v = makeBallots(s);
		vector<int> result;
		result.push_back(12);
		result.push_back(20);
		result.push_back(89);
		CPPUNIT_ASSERT(equal(v.data(), v.data()+2, result.data()));
	}

    // -----
    // contains
    // -----

   void test_contains_1(){
		vector<int> result;
		result.push_back(1);
		result.push_back(2);
		result.push_back(3);
		bool test = contains(result, 2);
		CPPUNIT_ASSERT(test == true);
   }

   void test_contains_2(){
		vector<int> result;
		result.push_back(1);
		result.push_back(22);
		result.push_back(656);
		bool test = contains(result, 2);
		CPPUNIT_ASSERT(test == false);
   }

   void test_contains_3(){
		vector<int> result;
		result.push_back(1111);
		result.push_back(2662);
		result.push_back(3165);
		bool test = contains(result, 3165);
		CPPUNIT_ASSERT(test == true);
   }


    // -----
    // voting_reset
    // -----


	void test_voting_reset_1(){
		vector<string> result1;
		result1.push_back("hi");
		vector< vector<int> > result2;

        vector<int> i;
		i.push_back(1111);

		result2.push_back(i);
		vector< vector<int> > result3;
		result3.push_back(i);
		voting_reset(result1, result2, result3);

		CPPUNIT_ASSERT( result1.empty() );
		CPPUNIT_ASSERT( result2.empty() );
		CPPUNIT_ASSERT( result3.empty() );
   }
   

	void test_voting_reset_2(){
		vector<string> result1;
		result1.push_back("hi");
		result1.push_back("goodbye");
		vector< vector<int> > result2;

        vector<int> i;
		i.push_back(1);
		i.push_back(2);

		result2.push_back(i);
		vector< vector<int> > result3;
		result3.push_back(i);
		voting_reset(result1, result2, result3);

		CPPUNIT_ASSERT( result1.empty() );
		CPPUNIT_ASSERT( result2.empty() );
		CPPUNIT_ASSERT( result3.empty() );
   }

	void test_voting_reset_3(){
		vector<string> result1;
		result1.push_back("hi");
		vector< vector<int> > result2;

      vector<int> i;

		result2.push_back(i);
		vector< vector<int> > result3;
		result3.push_back(i);
		voting_reset(result1, result2, result3);

		CPPUNIT_ASSERT( result1.empty() );
		CPPUNIT_ASSERT( result2.empty() );
		CPPUNIT_ASSERT( result3.empty() );
   }

    // -----
    // make_count
    // -----

 	void test_make_count_1(){
		vector< vector<int> > v;
	    vector<int> vote_list;
		v.push_back(vote_list);

		vote_list.push_back(1);
		vote_list.push_back(2);
		v.push_back(vote_list);
		vector<int> result = make_count(v);
		vector<int> expected;
		expected.push_back(0);		
		expected.push_back(2);
		CPPUNIT_ASSERT(equal(result.data(), result.data()+1, expected.data()));
	}
	
 	void test_make_count_2(){
		vector< vector<int> > v;
	    vector<int> vote_list;
		v.push_back(vote_list);

		vote_list.push_back(1);
		vote_list.push_back(2);
		vote_list.push_back(3);
		vote_list.push_back(4);
		v.push_back(vote_list);
		vector<int> result = make_count(v);
		vector<int> expected;
		expected.push_back(0);		
		expected.push_back(4);
		CPPUNIT_ASSERT(equal(result.data(), result.data()+1, expected.data()));
	}

 	void test_make_count_3(){
		vector< vector<int> > v;
	    vector<int> vote_list;
		v.push_back(vote_list);

		vote_list.push_back(1);
		vote_list.push_back(2);
		v.push_back(vote_list);

	   vector<int> vote_list2;
		vote_list2.push_back(1);
		vote_list2.push_back(2);
		v.push_back(vote_list2);


		vector<int> result = make_count(v);
		vector<int> expected;
		expected.push_back(0);		
		expected.push_back(2);
		expected.push_back(2);
		CPPUNIT_ASSERT(equal(result.data(), result.data()+1, expected.data()));
	}

	// -----
    // update_lost_list
    // -----
	void test_update_lost_list_1(){
	    vector<int> lost_list;

		lost_list.push_back(0);
		lost_list.push_back(1);
		lost_list.push_back(2);
		lost_list.push_back(1);
		lost_list.push_back(1);

		vector<int> result = update_lost_list(lost_list);
		vector<int> expected;
		expected.push_back(1);		
		expected.push_back(3);
		expected.push_back(4);
		CPPUNIT_ASSERT(equal(result.data(), result.data()+3, expected.data()));
	}

	void test_update_lost_list_2(){
	    vector<int> lost_list;

		lost_list.push_back(0);
		lost_list.push_back(1);
		lost_list.push_back(2);
		lost_list.push_back(1);
		lost_list.push_back(5);

		vector<int> result = update_lost_list(lost_list);
		vector<int> expected;
		expected.push_back(1);		
		expected.push_back(3);
		CPPUNIT_ASSERT(equal(result.data(), result.data()+2, expected.data()));
	}

	void test_update_lost_list_3(){
	    vector<int> lost_list;
		lost_list.push_back(0);
		lost_list.push_back(0);
		lost_list.push_back(2);
		lost_list.push_back(2);
		lost_list.push_back(1);

		vector<int> result = update_lost_list(lost_list);
		vector<int> expected;
		expected.push_back(1);		
		expected.push_back(4);
		CPPUNIT_ASSERT(equal(result.data(), result.data()+2, expected.data()));
	}

	// -----
    // voting_tally
    // -----
	void test_voting_tally_1(){
		vector<string> result1;
		result1.push_back("xx");
		result1.push_back("hi1");
		result1.push_back("hi2");
		
		vector< vector<int> > result2;
        vector<int> i;
		i.push_back(1);
		result2.push_back(i);
        result2.push_back(i);

		vector< vector<int> > result3;
		result3.push_back(i);
		result3.push_back(i);

		vector< vector<int> > expected;
		expected.push_back(i);
		expected.push_back(i);

		voting_tally(result1, result2, result3); //tie
		CPPUNIT_ASSERT(equal(result3.data(), result3.data()+2, expected.data()));

	}

	void test_voting_tally_2(){
		vector<string> result1;
		result1.push_back("xx");
		result1.push_back("hi1");
		result1.push_back("hi2");
		
		vector< vector<int> > result2;
        vector<int> i;
		i.push_back(3);
		result2.push_back(i);
        result2.push_back(i);

		vector< vector<int> > result3;
		result3.push_back(i);
		result3.push_back(i);

		vector< vector<int> > expected;
		expected.push_back(i);
		expected.push_back(i);

		voting_tally(result1, result2, result3); //win
		CPPUNIT_ASSERT(equal(result3.data(), result3.data()+2, expected.data()));
	}

	void test_voting_tally_3(){
		vector<string> result1;
		result1.push_back("xx");
		result1.push_back("hi1");
		result1.push_back("hi2");
		
		vector< vector<int> > result2;
        vector<int> i;
		i.push_back(2);
		result2.push_back(i);
        result2.push_back(i);

		vector< vector<int> > result3;
		result3.push_back(i);
		result3.push_back(i);

		vector< vector<int> > expected;
		expected.push_back(i);
		expected.push_back(i);

		voting_tally(result1, result2, result3); //tie
		CPPUNIT_ASSERT(equal(result3.data(), result3.data()+2, expected.data()));
	}

	// -----
    // reassign_vote
    // -----
	void test_reassign_vote_1(){
		vector<int> loser_list;
		vector< vector<int> > ballots;
		vector< vector<int> > ballots_distribution;

		loser_list.push_back(2);
		
		vector<int> vote0;
		vote0.push_back(1);
		vote0.push_back(2);
		vector<int> vote1;
		vote1.push_back(1);
		vote1.push_back(2);
		vector<int> vote2;
		vote2.push_back(2);
		vote2.push_back(1);

		ballots.push_back(vote0);
		ballots.push_back(vote1);
		ballots.push_back(vote2);

		vector<int> emptyVec;
		vector<int> d1;
		d1.push_back(0);
		d1.push_back(1);

		vector<int> d2;
		d2.push_back(2);

		ballots_distribution.push_back(emptyVec);
		ballots_distribution.push_back(d1);
		ballots_distribution.push_back(d2);

		reassign_vote(loser_list, ballots, ballots_distribution);
		CPPUNIT_ASSERT((int)ballots_distribution.at(1).size()==3);
		CPPUNIT_ASSERT((int)ballots_distribution.at(2).size()==0);			

	}

	void test_reassign_vote_2(){
		vector<int> loser_list;
		vector< vector<int> > ballots;
		vector< vector<int> > ballots_distribution;

		loser_list.push_back(1);
		
		vector<int> vote0;
		vote0.push_back(2);
		vote0.push_back(1);
		vector<int> vote1;
		vote1.push_back(1);
		vote1.push_back(2);
		vector<int> vote2;
		vote2.push_back(2);
		vote2.push_back(1);

		ballots.push_back(vote0);
		ballots.push_back(vote1);
		ballots.push_back(vote2);

		vector<int> emptyVec;
		vector<int> d1;
		d1.push_back(1);

		vector<int> d2;
		d2.push_back(0);
		d2.push_back(2);

		ballots_distribution.push_back(emptyVec);
		ballots_distribution.push_back(d1);
		ballots_distribution.push_back(d2);

		reassign_vote(loser_list, ballots, ballots_distribution);
		CPPUNIT_ASSERT((int)ballots_distribution.at(1).size()==0);
		CPPUNIT_ASSERT((int)ballots_distribution.at(2).size()==3);
	}

	void test_reassign_vote_3(){
		vector<int> loser_list;
		vector< vector<int> > ballots;
		vector< vector<int> > ballots_distribution;

		loser_list.push_back(3);
		loser_list.push_back(4);
		
		vector<int> vote0;
		vote0.push_back(1);
		vote0.push_back(2);
		vote0.push_back(3);
		vote0.push_back(4);
		vector<int> vote1;
		vote1.push_back(2);
		vote1.push_back(1);
		vote1.push_back(3);
		vote1.push_back(4);
		vector<int> vote2;
		vote2.push_back(2);
		vote2.push_back(3);
		vote2.push_back(1);
		vote2.push_back(4);
		vector<int> vote3;
		vote3.push_back(1);
		vote3.push_back(2);
		vote3.push_back(3);
		vote3.push_back(4);
		vector<int> vote4;
		vote4.push_back(3);
		vote4.push_back(4);
		vote4.push_back(1);
		vote4.push_back(2);
		vector<int> vote5;
		vote5.push_back(4);
		vote5.push_back(3);
		vote5.push_back(2);
		vote5.push_back(1);

		ballots.push_back(vote0);
		ballots.push_back(vote1);
		ballots.push_back(vote2);
		ballots.push_back(vote3);
		ballots.push_back(vote4);
		ballots.push_back(vote5);

		vector<int> emptyVec;
		vector<int> d1;
		d1.push_back(0);
		d1.push_back(3);

		vector<int> d2;
		d2.push_back(1);
		d2.push_back(2);

		vector<int> d3;
		d3.push_back(4);

		vector<int> d4;
		d4.push_back(5);

		ballots_distribution.push_back(emptyVec);
		ballots_distribution.push_back(d1);
		ballots_distribution.push_back(d2);
		ballots_distribution.push_back(d3);
		ballots_distribution.push_back(d4);

		reassign_vote(loser_list, ballots, ballots_distribution);
		CPPUNIT_ASSERT((int)ballots_distribution.at(1).size()==3);
		CPPUNIT_ASSERT((int)ballots_distribution.at(2).size()==3);
		CPPUNIT_ASSERT((int)ballots_distribution.at(3).size()==0);
		CPPUNIT_ASSERT((int)ballots_distribution.at(4).size()==0);
	}

    // -----
    // solve
    // -----

	void test_voting_solve_1(){
		std::istringstream r("1\n\n3\nGeorge Bush\nAl Gore\nJohn McCain\n1 2 3\n3 2 1\n1 3 2\n2 1 3\n3 1 2\n");
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str().compare("")==0);
	}

	void test_voting_solve_2(){
		std::istringstream r("1\n\n2\nGeorge Bush\nAl Gore\n1 2\n");
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str().compare("")==0);
	}

	void test_voting_solve_3(){
		std::istringstream r("1\n\n2\nGeorge Bush\nAl Gore\n1 2\n");
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str().compare("")==0);
	}

    // ----
    // voting_read
    // ----
	void test_voting_read_1(){
		std::istringstream r("1\nGeorge Bush\n1\n1\n");
		vector<string> peopleList;
		vector< vector<int> > ballots;
		vector< vector<int> > ballots_distribution;
		voting_read(r, peopleList, ballots, ballots_distribution);

		CPPUNIT_ASSERT(peopleList.at(1).compare("George Bush")==0);
		CPPUNIT_ASSERT(ballots.size() == 2);
		CPPUNIT_ASSERT((int)ballots_distribution.at(1).size() == 2);
	}

	void test_voting_read_2(){
		std::istringstream r("2\nGeorge Bush\nAl Gore\n1 2\n2 1\n1 2\n");
		vector<string> peopleList;
		vector< vector<int> > ballots;
		vector< vector<int> > ballots_distribution;
		voting_read(r, peopleList, ballots, ballots_distribution);


		CPPUNIT_ASSERT(peopleList.at(1).compare("George Bush")==0);
		CPPUNIT_ASSERT(peopleList.at(2).compare("Al Gore")==0);
		CPPUNIT_ASSERT(ballots.size() == 3);
		CPPUNIT_ASSERT((int)ballots_distribution.at(1).size() == 2);
		CPPUNIT_ASSERT((int)ballots_distribution.at(2).size() == 1);
	}

	void test_voting_read_3(){
		std::istringstream r("4\nA\nB\nC\nD\n1 2 3 4\n2 1 3 4\n1 2 4 3\n");
		vector<string> peopleList;
		vector< vector<int> > ballots;
		vector< vector<int> > ballots_distribution;
		voting_read(r, peopleList, ballots, ballots_distribution);


		CPPUNIT_ASSERT(peopleList.at(1).compare("A")==0);
		CPPUNIT_ASSERT(peopleList.at(2).compare("B")==0);
		CPPUNIT_ASSERT(peopleList.at(3).compare("C")==0);
		CPPUNIT_ASSERT(peopleList.at(4).compare("D")==0);
		CPPUNIT_ASSERT(ballots.size() == 3);
		CPPUNIT_ASSERT((int)ballots_distribution.at(1).size() == 2);
		CPPUNIT_ASSERT((int)ballots_distribution.at(2).size() == 1);
		CPPUNIT_ASSERT((int)ballots_distribution.at(3).size() == 0);
		CPPUNIT_ASSERT((int)ballots_distribution.at(4).size() == 0);
	}


    // -----
    // suite
    // -----
	CPPUNIT_TEST_SUITE(TestVoting);
	   	CPPUNIT_TEST(test_vote_all_tied_1);
   		CPPUNIT_TEST(test_vote_all_tied_2);
  	 	CPPUNIT_TEST(test_vote_all_tied_3);

		CPPUNIT_TEST(test_completed_1);
		CPPUNIT_TEST(test_completed_2);
		CPPUNIT_TEST(test_completed_3);

		CPPUNIT_TEST(test_makeBallots_1);
		CPPUNIT_TEST(test_makeBallots_2);
		CPPUNIT_TEST(test_makeBallots_3);

		CPPUNIT_TEST(test_contains_1);
		CPPUNIT_TEST(test_contains_2);
		CPPUNIT_TEST(test_contains_3);

		CPPUNIT_TEST(test_voting_reset_1);
		CPPUNIT_TEST(test_voting_reset_2);
		CPPUNIT_TEST(test_voting_reset_3);

		CPPUNIT_TEST(test_make_count_1);
		CPPUNIT_TEST(test_make_count_2);
		CPPUNIT_TEST(test_make_count_3);

		CPPUNIT_TEST(test_update_lost_list_1);
		CPPUNIT_TEST(test_update_lost_list_2);
		CPPUNIT_TEST(test_update_lost_list_3);

		CPPUNIT_TEST(test_voting_tally_1);
		CPPUNIT_TEST(test_voting_tally_2);
		CPPUNIT_TEST(test_voting_tally_3);

		CPPUNIT_TEST(test_voting_read_1);
		CPPUNIT_TEST(test_voting_read_2);
		CPPUNIT_TEST(test_voting_read_3);

		CPPUNIT_TEST(test_reassign_vote_1);
		CPPUNIT_TEST(test_reassign_vote_2);
		CPPUNIT_TEST(test_reassign_vote_3);

		CPPUNIT_TEST(test_voting_solve_1);
		CPPUNIT_TEST(test_voting_solve_2);
		CPPUNIT_TEST(test_voting_solve_3);

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
