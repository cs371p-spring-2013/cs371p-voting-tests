// --------------------------------
// Paul Carroll
// pvc95
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
    % valgrind TestVoting.c++.app >& TestVoti.out
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

// ----------
// TestVoting
// ----------

struct TestVoting : CppUnit::TestFixture {


// ------------
// number_read
// ------------

void test_number_read_1(){
		std::istringstream r("41\n");
     	int i;
   		number_read(r, i);
        CPPUNIT_ASSERT(i == 41);
}

void test_number_read_2(){
		std::istringstream r("1\n");
     	int i;
   		number_read(r, i);
        CPPUNIT_ASSERT(i == 1);
}

void test_number_read_3(){
		std::istringstream r("414\n");
     	int i;
   		number_read(r, i);
        CPPUNIT_ASSERT(i == 414);
}

// ------------
// names_read
// ------------

void test_names_read_1(){
	std::istringstream r("Hello World\nJohn Argo\n");
   	 	std::vector<Candidate> candidates;
        int i = 2;
   		names_read(r, candidates, i);
        CPPUNIT_ASSERT(candidates.size() > 0);
}

void test_names_read_2(){
		std::istringstream r("Hello World\nJohn Argo\nAnother Name\n");
   	 	std::vector<Candidate> candidates;
        int i = 3;
   		names_read(r, candidates, i);
        CPPUNIT_ASSERT(candidates.size() > 0);
}

void test_names_read_3(){
	std::istringstream r("Just One\n");
   	 	std::vector<Candidate> candidates;
        int i = 1;
   		names_read(r, candidates, i);
        CPPUNIT_ASSERT(candidates.size() > 0);
}

//-------------------
// read_single_ballot
//-------------------

void test_read_single_ballot_1(){
	std::string pass("1 2 3\n");
 	std::vector<Ballots> ballot;
	read_single_ballot(pass, ballot, 3);
    CPPUNIT_ASSERT(!ballot.empty());
}

void test_read_single_ballot_2(){
	std::string pass("1 2 4 3\n");
 	std::vector<Ballots> ballot;
	read_single_ballot(pass, ballot, 4);
    CPPUNIT_ASSERT(!ballot.empty());
}

void test_read_single_ballot_3(){
	std::string pass("1 2 3 5 6 4\n");
 	std::vector<Ballots> ballot;
	read_single_ballot(pass, ballot, 6);
    CPPUNIT_ASSERT(!ballot.empty());
}

// ------------
// ballot_read
// ------------
 
void test_ballot_read_1(){
	std::istringstream r("1 2 3\n2 3 1\n3 1 2\n");
 	std::vector<Ballots> ballot;
	ballot_read(r, ballot, 3);
    CPPUNIT_ASSERT(!ballot.empty());
}

void test_ballot_read_2(){
 	std::istringstream r("1 2 3 4\n2 4 3 1\n3 1 4 2\n");
 	std::vector<Ballots> ballot;
	ballot_read(r, ballot, 4);
    CPPUNIT_ASSERT(!ballot.empty());
    
}

void test_ballot_read_3(){
 	std::istringstream r("1 2\n2 1\n");
 	std::vector<Ballots> ballot;
	ballot_read(r, ballot, 2);
    CPPUNIT_ASSERT(!ballot.empty());
    
}


//--------------
// ballot_assign
//--------------

void test_ballot_assign_1(){
	std::istringstream r("1 2 3\n2 3 1\n3 1 2\n");
 	std::vector<Ballots> ballot;
	int i = 3;
	ballot_read(r, ballot, i);
	std::istringstream x("Hello World\nJohn Argo\nAnother Name\n");
 	std::vector<Candidate> candidates;
	names_read(x, candidates, i);
	ballot_assign(ballot, candidates, i);
	int count = 0;
	for(int j = 0; j < (int)candidates.size(); j++){
		count += candidates.at(j).ballots_assigned.size();
	}
	CPPUNIT_ASSERT(ballot.size() == count);
	
}

void test_ballot_assign_2(){
	std::istringstream r("1 2\n2 1\n");
 	std::vector<Ballots> ballot;
	int i = 2;
	ballot_read(r, ballot, i);
	std::istringstream x("Hello World\nAnother Name\n");
 	std::vector<Candidate> candidates;
	names_read(x, candidates, i);
	ballot_assign(ballot, candidates, i);
	int count = 0;
	for(int j = 0; j < (int)candidates.size(); j++){
		count += candidates.at(j).ballots_assigned.size();
	}
	CPPUNIT_ASSERT(ballot.size() == count);
	
}

void test_ballot_assign_3(){
	std::istringstream r("1 2 3 4\n2 4 3 1\n4 3 1 2\n4 2 1 3\n");
 	std::vector<Ballots> ballot;
	int i = 4;
	ballot_read(r, ballot, i);
	std::istringstream x("Hello World\nJohn Argo\nAnother Name\nLast Naie\n");
 	std::vector<Candidate> candidates;
	names_read(x, candidates, i);
	ballot_assign(ballot, candidates, i);
	int count = 0;
	for(int j = 0; j < (int)candidates.size(); j++){
		count += candidates.at(j).ballots_assigned.size();
	}
	CPPUNIT_ASSERT(ballot.size() == count);
	
}

//-----------
// winner_single
//-----------

bool test_winner_single_1(){
	std::istringstream r("1 2 3 4\n4 2 3 1\n4 3 1 2\n4 2 1 3\n");
 	std::vector<Ballots> ballot;
	int i = 4;
	ballot_read(r, ballot, i);
	std::istringstream x("Hello World\nJohn Argo\nAnother Name\nLast Naie\n");
 	std::vector<Candidate> candidates;
	names_read(x, candidates, i);
	ballot_assign(ballot, candidates, i);
	std::vector<std::string> winners;
	winner_single(candidates, 4, winners);
	CPPUNIT_ASSERT(winners.size() == 1);
}

bool test_winner_single_2(){
	std::istringstream r("1 2 3\n2 3 1\n2 1 3\n");
 	std::vector<Ballots> ballot;
	int i = 3;
	ballot_read(r, ballot, i);
	std::istringstream x("Hello World\nJohn Argo\nAnother Name\nLast Naie\n");
 	std::vector<Candidate> candidates;
	names_read(x, candidates, i);
	ballot_assign(ballot, candidates, i);
	std::vector<std::string> winners;
	winner_single(candidates, 4, winners);
	CPPUNIT_ASSERT(winners.size() == 1);
}

bool test_winner_single_3(){
	std::istringstream r("1 2\n1 2\n");
 	std::vector<Ballots> ballot;
	int i = 2;
	ballot_read(r, ballot, i);
	std::istringstream x("Hello World\nJohn Argo");
 	std::vector<Candidate> candidates;
	names_read(x, candidates, i);
	ballot_assign(ballot, candidates, i);
	std::vector<std::string> winners;
	winner_single(candidates, 4, winners);
	CPPUNIT_ASSERT(winners.size() == 1);
}


//-----------
// winner_tie
//-----------

void test_winner_tie_1(){

	std::ostringstream w;
	std::vector<Candidate> candidates;
	std::vector<std::string> winners;
	int votes = 2;
	Ballots b1;
	b1.votes = {1, 2};
	Ballots b2;
	b2.votes = {2, 1};


	Candidate x;
	x.name = "x";
	x.alive = true;
	x.ballots_assigned.push_back(b1);

	Candidate y;
	y.name = "y";
	y.alive = true;
	y.ballots_assigned.push_back(b2);

	candidates.push_back(x);
	candidates.push_back(y);

	winner_tie(candidates, votes, winners);
	CPPUNIT_ASSERT(winners.at(0) == "x");
	CPPUNIT_ASSERT(winners.at(1) == "y");
	CPPUNIT_ASSERT(winners.size() == 2);
}

void test_winner_tie_2(){

	std::ostringstream w;
	std::vector<Candidate> candidates;
	std::vector<std::string> winners;
	int votes = 2;
	Ballots b1;
	b1.votes = {1, 2};
	Ballots b2;
	b2.votes = {1, 2};


	Candidate x;
	x.name = "x";
	x.alive = true;
	x.ballots_assigned.push_back(b1);

	Candidate y;
	y.name = "y";
	y.alive = true;
	y.ballots_assigned.push_back(b2);

	candidates.push_back(x);
	candidates.push_back(y);

	winner_tie(candidates, votes, winners);
	CPPUNIT_ASSERT(winners.at(0) == "x");

}

void test_winner_tie_3(){

	std::ostringstream w;
	std::vector<Candidate> candidates;
	std::vector<std::string> winners;
	int votes = 3;
	Ballots b1;
	b1.votes = {2, 1, 3};
	Ballots b2;
	b2.votes = {3, 2, 1};
	Ballots b3;
	b2.votes = {1, 2, 3};


	Candidate x;
	x.name = "x";
	x.alive = true;
	x.ballots_assigned.push_back(b3);

	Candidate y;
	y.name = "y";
	y.alive = true;
	y.ballots_assigned.push_back(b1);

	Candidate z;
	z.name = "z";
	z.alive = true;
	z.ballots_assigned.push_back(b2);

	candidates.push_back(x);
	candidates.push_back(y);
	candidates.push_back(z);

	winner_tie(candidates, votes, winners);
	CPPUNIT_ASSERT(winners.size() == 3);

}

//--------------
// print_winner
//--------------

void test_print_winner_1(){
	std::vector<std::string> winners = {"winner1", "winner2", "winner3"};
	std::ostringstream w;
	print_winner(w, winners);
	CPPUNIT_ASSERT(w.str() == "winner1\nwinner2\nwinner3\n");
}

void test_print_winner_2(){
	std::vector<std::string> winners = {"winner1"};
	std::ostringstream w;
	print_winner(w, winners);
	CPPUNIT_ASSERT(w.str() == "winner1\n");
}

void test_print_winner_3(){
	std::vector<std::string> winners = {"winner1", "winner2", "winner3", "winner4"};
	std::ostringstream w;
	print_winner(w, winners);
	CPPUNIT_ASSERT(w.str() == "winner1\nwinner2\nwinner3\nwinner4\n");
}

//----------------
// ballot_reassign
//----------------

void test_ballot_reassign_1(){
	std::ostringstream w;
	std::vector<Candidate> candidates;

	Ballots b1;
	b1.votes = {1, 2};


	Candidate x;
	x.name = "x";
	x.alive = true;
	x.ballots_assigned.push_back(b1);

	Candidate y;
	y.name = "y";
	y.alive = true;

	
	candidates.push_back(x);
	candidates.push_back(y);

	CPPUNIT_ASSERT(!candidates.empty());
	CPPUNIT_ASSERT(candidates.at(0).ballots_assigned.size() == 1);
	CPPUNIT_ASSERT(candidates.at(1).ballots_assigned.size() == 0);

	ballot_reassign(candidates);

	CPPUNIT_ASSERT(candidates.at(0).ballots_assigned.size() == 1);
	CPPUNIT_ASSERT(candidates.at(1).ballots_assigned.size() == 0);
}

void test_ballot_reassign_2(){
	std::ostringstream w;
	std::vector<Candidate> candidates;

	Ballots b1;
	b1.votes = {1, 2, 3};
	Ballots b2;
	b2.votes = {1, 2, 3};
	Ballots b3;
	b3.votes = {2, 1, 3};
	Ballots b4;
	b4.votes = {2, 1, 3};
	Ballots b5;
	b5.votes = {3, 1, 2};


	Candidate x;
	x.name = "x";
	x.alive = true;
	x.ballots_assigned.push_back(b1);
	x.ballots_assigned.push_back(b2);


	Candidate y;
	y.name = "y";
	y.alive = true;
	y.ballots_assigned.push_back(b3);
	y.ballots_assigned.push_back(b4);

	Candidate z;
	z.name = "z";
	z.alive = true;
	z.ballots_assigned.push_back(b5);

	
	candidates.push_back(x);
	candidates.push_back(y);
	candidates.push_back(z);

	CPPUNIT_ASSERT(candidates.size() == 3);
	CPPUNIT_ASSERT(candidates.at(0).ballots_assigned.size() == 2);
	CPPUNIT_ASSERT(candidates.at(1).ballots_assigned.size() == 2);
	CPPUNIT_ASSERT(candidates.at(2).ballots_assigned.size() == 1);

	ballot_reassign(candidates);

	CPPUNIT_ASSERT(candidates.at(0).ballots_assigned.size() == 3);
	CPPUNIT_ASSERT(candidates.at(1).ballots_assigned.size() == 2);
	CPPUNIT_ASSERT(candidates.at(2).ballots_assigned.size() == 0);
}

void test_ballot_reassign_3(){
	std::ostringstream w;
	std::vector<Candidate> candidates;

	Ballots b1;
	b1.votes = {1, 2, 3};
	Ballots b2;
	b2.votes = {1, 2, 3};
	Ballots b3;
	b3.votes = {2, 1, 3};

	Candidate x;
	x.name = "x";
	x.alive = true;
	x.ballots_assigned.push_back(b1);
	x.ballots_assigned.push_back(b2);


	Candidate y;
	y.name = "y";
	y.alive = true;
	y.ballots_assigned.push_back(b3);

	
	candidates.push_back(x);
	candidates.push_back(y);


	CPPUNIT_ASSERT(candidates.size() == 2);
	CPPUNIT_ASSERT(candidates.at(0).ballots_assigned.size() == 2);
	CPPUNIT_ASSERT(candidates.at(1).ballots_assigned.size() == 1);


	ballot_reassign(candidates);

	CPPUNIT_ASSERT(candidates.at(0).ballots_assigned.size() == 3);
	CPPUNIT_ASSERT(candidates.at(1).ballots_assigned.size() == 0);

}

// -------------
// voting_solve
// -------------

void test_voting_solve_1(){
	std::istringstream r("1\n\n2\na\nb\n1 2\n\n");
	std::ostringstream w;
	voting_solve(r, w);
	CPPUNIT_ASSERT(w.str() == "a\n");
}

void test_voting_solve_2(){
	std::istringstream r("1\n\n1\na\n1\n\n");
	std::ostringstream w;
	voting_solve(r, w);
	CPPUNIT_ASSERT(w.str() == "a\n");
}

void test_voting_solve_3(){
	std::istringstream r("1\n\n2\na\nb\n1 2\n2 1\n\n");
	std::ostringstream w;
	voting_solve(r, w);
	CPPUNIT_ASSERT(w.str() == "a\nb\n");
}



    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_number_read_1);
    CPPUNIT_TEST(test_number_read_2);
    CPPUNIT_TEST(test_number_read_3);
    CPPUNIT_TEST(test_names_read_1);
    CPPUNIT_TEST(test_names_read_2);
    CPPUNIT_TEST(test_names_read_3);
	CPPUNIT_TEST(test_ballot_read_1);
	CPPUNIT_TEST(test_ballot_read_2);
	CPPUNIT_TEST(test_ballot_read_3);
	CPPUNIT_TEST(test_read_single_ballot_1);
	CPPUNIT_TEST(test_read_single_ballot_2);
	CPPUNIT_TEST(test_read_single_ballot_3);
	CPPUNIT_TEST(test_ballot_assign_1);
	CPPUNIT_TEST(test_ballot_assign_2);
	CPPUNIT_TEST(test_ballot_assign_3);
    CPPUNIT_TEST(test_winner_tie_1);
    CPPUNIT_TEST(test_winner_tie_2);
    CPPUNIT_TEST(test_winner_tie_3);
    CPPUNIT_TEST(test_print_winner_1);
    CPPUNIT_TEST(test_print_winner_2);
    CPPUNIT_TEST(test_print_winner_3);
    CPPUNIT_TEST(test_ballot_reassign_1);
    CPPUNIT_TEST(test_ballot_reassign_2);
    CPPUNIT_TEST(test_ballot_reassign_3);
    CPPUNIT_TEST(test_voting_solve_1);
    CPPUNIT_TEST(test_voting_solve_2);
    CPPUNIT_TEST(test_voting_solve_3);
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
