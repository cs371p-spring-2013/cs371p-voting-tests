
// --------
// includes
// --------

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"
#include <vector>
#include "Voting.h"



  using namespace std;


//Thank you to atc558 for our in/out file!

/*I got very stuck with a segfault, decided to turn in the working version 
instead of the better version that was more testable.  I included the better 
versions as Voting2.c++ and Voting2.h.  TestVoting.c++ was made for Voting2.c++ 
but I never quite got it to work.*/

struct TestVoting : CppUnit::TestFixture {

// struct candidates 	
// {
// 	string name;
// 	int votes;
// 	bool inRace;
// };

candidates cans[3];


	//--------------
	// mark_ winner
	//--------------

	void test_mark_winner_1() {



		cans[0].name = "Bob";
		cans[0].votes = 3;
		cans[0].inRace = true;
		cans[1].name = "Jim";
		cans[1].votes = 2;
		cans[1].inRace = true;
		cans[2].name = "Steve";
		cans[2].votes = 0;
		cans[2].inRace = false;
		mark_winner(0, 3, cans);
		CPPUNIT_ASSERT(cans[0].inRace == true);
		CPPUNIT_ASSERT(cans[1].inRace == false);
		CPPUNIT_ASSERT(cans[2].inRace == false);
	}



	void test_mark_winner_2() {
		cans[0].votes = 5;
		cans[0].inRace = true;
		cans[1].votes = 7;
		cans[1].inRace = true;
		cans[2].votes = 0;
		cans[2].inRace = false;
		mark_winner(1, 3, cans);
		CPPUNIT_ASSERT(cans[0].inRace == false);
		CPPUNIT_ASSERT(cans[1].inRace == true);
		CPPUNIT_ASSERT(cans[2].inRace == false);
	}


	

	void test_mark_winner_3() {
		cans[0].votes = 15;
		cans[0].inRace = true;
		cans[1].votes = 0;
		cans[1].inRace = false;
		cans[2].votes = 25;
		cans[2].inRace = true;
		mark_winner(2, 3, cans);
		CPPUNIT_ASSERT(cans[0].inRace == false);
		CPPUNIT_ASSERT(cans[1].inRace == false);
		CPPUNIT_ASSERT(cans[2].inRace == true);
	}

	//--------------
	// mark_ losers
	//--------------



	void test_mark_losers_1() {
		cans[0].votes = 5;
		cans[0].inRace = true;
		cans[1].votes = 7;
		cans[1].inRace = true;
		cans[2].votes = 3;
		cans[2].inRace = true;
		mark_losers(3, cans, 15);
		CPPUNIT_ASSERT(cans[0].inRace == true);
		CPPUNIT_ASSERT(cans[1].inRace == true);
		CPPUNIT_ASSERT(cans[2].inRace == false);
	}

	void test_mark_losers_2() {
		cans[0].votes = 20;
		cans[0].inRace = true;
		cans[1].votes = 7;
		cans[1].inRace = true;
		cans[2].votes = 13;
		cans[2].inRace = true;
		mark_losers(3, cans, 40);
		CPPUNIT_ASSERT(cans[0].inRace == true);
		CPPUNIT_ASSERT(cans[1].inRace == false);
		CPPUNIT_ASSERT(cans[2].inRace == true);
	}

	void test_mark_losers_3() {
		cans[0].votes = 4;
		cans[0].inRace = true;
		cans[1].votes = 4;
		cans[1].inRace = true;
		cans[2].votes = 3;
		cans[2].inRace = true;
		mark_losers(3, cans, 11);
		CPPUNIT_ASSERT(cans[0].inRace == true);
		CPPUNIT_ASSERT(cans[1].inRace == true);
		CPPUNIT_ASSERT(cans[2].inRace == false);
	}

	//--------------
	// give_ballots
	//--------------

	void test_give_ballots_1() {
		vector < vector < string >  > ballots (3);
		ballots.at(0).push_back("2 3");
		ballots.at(0).push_back("3 2");
		cans[0].inRace = true;
		cans[0].votes = 2;
		ballots.at(1).push_back("1 3");
		ballots.at(1).push_back("3 1");
		cans[1].inRace = true;
		cans[1].votes = 2;
		ballots.at(2).push_back("1 2");
		cans[2].inRace = false;
		cans[2].votes = 1;
		give_ballots(3, cans, ballots);
		CPPUNIT_ASSERT(cans[0].votes == 3);
		CPPUNIT_ASSERT(cans[1].votes == 2);
		CPPUNIT_ASSERT(cans[2].votes == 0);

	}

	void test_give_ballots_2() {
		vector < vector < string >  > ballots (3);
		ballots.at(0).push_back("2 3");
		ballots.at(0).push_back("3 2");
		cans[0].inRace = true;
		cans[0].votes = 2;
		ballots.at(1).push_back("1 3");
		ballots.at(1).push_back("3 1");
		cans[1].inRace = true;
		cans[1].votes = 2;
		ballots.at(2).push_back("1 2");
		ballots.at(2).push_back("2 1");
		cans[2].inRace = false;
		cans[2].votes = 2;
		give_ballots(3, cans, ballots);
		CPPUNIT_ASSERT(cans[0].votes == 3);
		CPPUNIT_ASSERT(cans[1].votes == 3);
		CPPUNIT_ASSERT(cans[2].votes == 0);
	}

	void test_give_ballots_3() {
		vector < vector < string >  > ballots (3);
		ballots.at(0).push_back("2 3");
		ballots.at(0).push_back("3 2");
		cans[0].inRace = false;
		cans[0].votes = 2;
		ballots.at(1).push_back("1 3");
		ballots.at(1).push_back("3 1");
		ballots.at(1).push_back("3 1");
		cans[1].inRace = true;
		cans[1].votes = 3;
		ballots.at(2).push_back("1 2");
		ballots.at(2).push_back("2 1");
		ballots.at(2).push_back("2 1");
		cans[2].inRace = true;
		cans[2].votes = 3;
		give_ballots(3, cans, ballots);
		CPPUNIT_ASSERT(cans[0].votes == 0);
		CPPUNIT_ASSERT(cans[1].votes == 4);
		CPPUNIT_ASSERT(cans[2].votes == 4);
	}

	//--------------
	// voting_read
	//--------------

	void test_voting_read_1() {

	}

	void test_voting_read_2() {

	}

	void test_voting_read_3() {

	}

	//--------------
	// voting_print
	//--------------

	void test_voting_print_1() {
		std::ostringstream w;
		cans[0].name = "Bob";
		cans[0].inRace = true;
		cans[1].name = "Steve";
		cans[1].inRace = false;
		voting_print(w, 2, cans);
		CPPUNIT_ASSERT(w.str() == "Bob\n");

	}

	void test_voting_print_2() {
		std::ostringstream w;
		cans[0].name = "Bob";
		cans[0].inRace = true;
		cans[1].name = "Steve";
		cans[1].inRace = true;
		voting_print(w, 2, cans);
		CPPUNIT_ASSERT(w.str() == "Bob\nSteve\n");
	}

	void test_voting_print_3() {
		std::ostringstream w;
		cans[0].name = "Bob";
		cans[0].inRace = false;
		cans[1].name = "Steve";
		cans[1].inRace = true;
		cans[2].name = "Fred";
		cans[2].inRace = true;
		voting_print(w, 3, cans);
		CPPUNIT_ASSERT(w.str() == "Steve\nFred\n");
	}

	//--------------
	// voting_solve
	//--------------

	void test_voting_solve_1() {
        std::istringstream r("3\nBob\nSteve\nDirk\n1 2 3\n1 2 3\n1 2 3\n");
        std::ostringstream w;
        bool done = voting_solve(r, w);
        CPPUNIT_ASSERT (done);
        CPPUNIT_ASSERT (w.str() == "Bob\n");
	}

	void test_voting_solve_2() {
		std::istringstream r("6\nBob\nSteve\nDirk\nEvan\nFrank\nJoel\n3 2 1 4 5 6\n");
        std::ostringstream w;
        bool done = voting_solve(r, w);
        CPPUNIT_ASSERT (done);
        CPPUNIT_ASSERT (w.str() == "Dirk\n");
	}

	void test_voting_solve_3() {
		 std::istringstream r("3\nSteve\nBob\nEvan\n1 2 3\n3 2 1\n2 1 3\n1 2 3\n2 1 3\n");
        std::ostringstream w;
        bool done = voting_solve(r, w);
        CPPUNIT_ASSERT (done);
        CPPUNIT_ASSERT (w.str() == "Bob\n");
	}

	//---------------
	// tests
	//---------------

    CPPUNIT_TEST_SUITE(TestVoting);

    CPPUNIT_TEST(test_mark_winner_1);
    CPPUNIT_TEST(test_mark_winner_2);
    CPPUNIT_TEST(test_mark_winner_3);

    CPPUNIT_TEST(test_mark_losers_1);
    CPPUNIT_TEST(test_mark_losers_2);
    CPPUNIT_TEST(test_mark_losers_3);

    CPPUNIT_TEST(test_give_ballots_1);
    CPPUNIT_TEST(test_give_ballots_2);
    CPPUNIT_TEST(test_give_ballots_3);

    // CPPUNIT_TEST(test_voting_read_1);
    // CPPUNIT_TEST(test_voting_read_2);
    // CPPUNIT_TEST(test_voting_read_3);

    CPPUNIT_TEST(test_voting_print_1);
    CPPUNIT_TEST(test_voting_print_2);
    CPPUNIT_TEST(test_voting_print_3);

   // CPPUNIT_TEST(test_voting_solve_1);
    //CPPUNIT_TEST(test_voting_solve_2);
    //CPPUNIT_TEST(test_voting_solve_3);


    CPPUNIT_TEST_SUITE_END();

};

// ----
// main
// ----

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false);
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
