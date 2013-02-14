//
//Credit to Glenn P. Downing for framework for this program.
//

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

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

// -----------
// TestCollatz
// -----------

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_basic () {
        std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        std::string names[21];
        int votes[1000][20];
        int votes_verify[5][3] = { {1,2,3}, {2,1,3}, {2,3,1}, {1,2,3}, {3,1,2}};
        int vote_lim = 0;
        voting_read(r, 3, vote_lim, names, votes);
        CPPUNIT_ASSERT(vote_lim ==    5);
        CPPUNIT_ASSERT(names[1] ==   "John Doe");
        CPPUNIT_ASSERT(names[2] ==   "Jane Smith");
        CPPUNIT_ASSERT(names[3] ==   "Sirhan Sirhan");
        for(int x = 0;x<5;++x)
        	for(int y = 0;y<3;++y)
        		CPPUNIT_ASSERT(votes[x][y] ==   votes_verify[x][y]);
        }
        
       void test_read_one_candidate () {
        std::istringstream r("Sirhan Sirhan\n1\n");
        std::string names[21];
        int votes[1000][20];
        int votes_verify[1][1] = { {1} };
        int vote_lim = 0;
        voting_read(r, 1, vote_lim, names, votes);
        CPPUNIT_ASSERT(vote_lim ==    1);
        CPPUNIT_ASSERT(names[1] ==   "Sirhan Sirhan");
        for(int x = 0;x<1;++x)
        	for(int y = 0;y<1;++y)
        		CPPUNIT_ASSERT(votes[x][y] ==   votes_verify[x][y]);
        }
        
       void test_read_no_votes () {
        std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\n");
        std::string names[21];
        int votes[1000][20];
        int vote_lim = 0;
        voting_read(r, 3, vote_lim, names, votes);
        CPPUNIT_ASSERT(vote_lim ==    0);
        CPPUNIT_ASSERT(names[1] ==   "John Doe");
        CPPUNIT_ASSERT(names[2] ==   "Jane Smith");
        CPPUNIT_ASSERT(names[3] ==   "Sirhan Sirhan");
        }
        
    // ----
    // voting_ballot_count
    // ----
    
    void test_vbc_basic ()
    {
    	int ballot_count[4] = {0,0,0,0};
    	int ballot_count_verify[3] = {2,2,1};
    	int votes [5][20] = { {1,2,3}, {2,1,3}, {2,3,1}, {1,2,3}, {3,1,2}};
    	int lim = 3;
    	int vote_lim = 5;
    	
    	voting_count_ballots(ballot_count, votes,lim,vote_lim);
        for(int y = 1;y<4;++y)
        	CPPUNIT_ASSERT(ballot_count[y] ==   ballot_count_verify[y-1]);
    }
    
    void test_vbc_one_elimination ()
    {
    	int ballot_count[4] = {0,0,0,-1};
    	int ballot_count_verify[3] = {3,2,-1};
    	int votes [5][20] = { {1,2,3}, {2,1,3}, {2,3,1}, {1,2,3}, {3,1,2}};
    	int lim = 3;
    	int vote_lim = 5;
    	
    	voting_count_ballots(ballot_count, votes,lim,vote_lim);
        CPPUNIT_ASSERT(ballot_count[1] == ballot_count_verify[0]);
        CPPUNIT_ASSERT(ballot_count[2] == ballot_count_verify[1]);
        CPPUNIT_ASSERT(ballot_count[3] == ballot_count_verify[2]);
    }
    
    void test_vbc_two_elimination ()
    {
    	int ballot_count[4] = {0,-1,-1,0};
    	int ballot_count_verify[3] = {-1,-1,5};
    	int votes [5][20] = { {1,2,3}, {2,1,3}, {2,3,1}, {1,2,3}, {3,1,2}};
    	int lim = 3;
    	int vote_lim = 5;
    	
    	voting_count_ballots(ballot_count, votes,lim,vote_lim);
        CPPUNIT_ASSERT(ballot_count[1] == ballot_count_verify[0]);
        CPPUNIT_ASSERT(ballot_count[2] == ballot_count_verify[1]);
        CPPUNIT_ASSERT(ballot_count[3] == ballot_count_verify[2]);
    }
    
    void test_vel_basic ()
    {
    	int ballot_count[4] = {0,2,2,1};
    	int ballot_count_verify[3] = {0,0,-1};
    	int lim = 3;
    	int vote_lim = 5;
    	bool is_winner = voting_eliminate_losers(ballot_count,lim,vote_lim);
    	CPPUNIT_ASSERT(is_winner == false);
    	CPPUNIT_ASSERT(ballot_count[1] == ballot_count_verify[0]);
        CPPUNIT_ASSERT(ballot_count[2] == ballot_count_verify[1]);
        CPPUNIT_ASSERT(ballot_count[3] == ballot_count_verify[2]);
        
    }
    
    void test_vel_most_votes ()
    {
    	int ballot_count[4] = {0,62,2,1};
    	int ballot_count_verify[3] = {62,2,1};
    	int lim = 3;
    	int vote_lim = 65;
    	bool is_winner = voting_eliminate_losers(ballot_count,lim,vote_lim);
    	CPPUNIT_ASSERT(is_winner == true);
    	CPPUNIT_ASSERT(ballot_count[1] == ballot_count_verify[0]);
        CPPUNIT_ASSERT(ballot_count[2] == ballot_count_verify[1]);
        CPPUNIT_ASSERT(ballot_count[3] == ballot_count_verify[2]);
        
    }
    
    void test_vel_majority ()
    {
    	int ballot_count[4] = {0,5,2,1};
    	int ballot_count_verify[3] = {5,2,1};
    	int lim = 3;
    	int vote_lim = 8;
    	bool is_winner = voting_eliminate_losers(ballot_count,lim,vote_lim);
    	CPPUNIT_ASSERT(is_winner == true);
    	CPPUNIT_ASSERT(ballot_count[1] == ballot_count_verify[0]);
        CPPUNIT_ASSERT(ballot_count[2] == ballot_count_verify[1]);
        CPPUNIT_ASSERT(ballot_count[3] == ballot_count_verify[2]);
        
    }
    
    void test_vel_majority_minus_one ()
    {
    	int ballot_count[4] = {0,4,2,2};
    	int ballot_count_verify[3] = {0,-1,-1};
    	int lim = 3;
    	int vote_lim = 8;
    	bool is_winner = voting_eliminate_losers(ballot_count,lim,vote_lim);
    	CPPUNIT_ASSERT(is_winner == false);
    	CPPUNIT_ASSERT(ballot_count[1] == ballot_count_verify[0]);
        CPPUNIT_ASSERT(ballot_count[2] == ballot_count_verify[1]);
        CPPUNIT_ASSERT(ballot_count[3] == ballot_count_verify[2]);
        
    }
    
    void test_vel_tie ()
    {
    	int ballot_count[4] = {0,-1,2,2};
    	int ballot_count_verify[3] = {-1,2,2};
    	int lim = 3;
    	int vote_lim = 4;
    	bool is_winner = voting_eliminate_losers(ballot_count,lim,vote_lim);
    	CPPUNIT_ASSERT(is_winner == true);
    	CPPUNIT_ASSERT(ballot_count[1] == ballot_count_verify[0]);
        CPPUNIT_ASSERT(ballot_count[2] == ballot_count_verify[1]);
        CPPUNIT_ASSERT(ballot_count[3] == ballot_count_verify[2]);
        
    }
    
    void test_vel_not_a_tie ()
    {
    	int ballot_count[4] = {0,0,2,2};
    	int ballot_count_verify[3] = {-1,0,0};
    	int lim = 3;
    	int vote_lim = 4;
    	bool is_winner = voting_eliminate_losers(ballot_count,lim,vote_lim);
    	CPPUNIT_ASSERT(is_winner == false);
    	CPPUNIT_ASSERT(ballot_count[1] == ballot_count_verify[0]);
        CPPUNIT_ASSERT(ballot_count[2] == ballot_count_verify[1]);
        CPPUNIT_ASSERT(ballot_count[3] == ballot_count_verify[2]);
        
    }
    
    void test_vcws_basic ()
    {
    	std::string names[4] = { "", "John Doe", "Jane Smith", "Sirhan Sirhan"};
    	int ballot_count[4] = {0, 3, 2, -1};
    	int lim = 3;
    	std::string name = voting_create_winner_string(ballot_count,names,lim);
    	CPPUNIT_ASSERT(name == "John Doe");
   	}
   	
   	void test_vcws_tie ()
    {
    	std::string names[4] = { "", "John Doe", "Jane Smith", "Sirhan Sirhan"};
    	int ballot_count[4] = {0, 3, 3, -1};
    	int lim = 3;
    	std::string name = voting_create_winner_string(ballot_count,names,lim);
    	CPPUNIT_ASSERT(name == "John Doe\nJane Smith");
   	}
   	
   	void test_vcws_one_person ()
    {
    	std::string names[4] = { "", "Sirhan Sirhan"};
    	int ballot_count[4] = {0, 3};
    	int lim = 1;
    	std::string name = voting_create_winner_string(ballot_count,names,lim);
    	CPPUNIT_ASSERT(name == "Sirhan Sirhan");
   	}
   	
   	void test_vs_basic()
   	{
   		std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
   		std::ostringstream w;
   		voting_solve(r,w);
   		CPPUNIT_ASSERT(w.str() == "John Doe\n");
   	}
   	
   	void test_vs_complex()
   	{
   		std::istringstream r("1\n\n15\nFrance\nGermany\nItaly\nNorway\nSweeden\nFinland\nEngland\nSwitzerland\nUkraine\nDenmark\nCzech Republic\nAustria\nNetherlands\nPortugal\nSpain\n1 2 3 4 5 6 7 8 9 10 11 12 13 14 15\n4 6 12 10 14 1 13 8 2 11 9 7 5 15 3\n10 6 9 3 8 15 12 14 13 2 1 7 5 11 4\n11 15 1 3 7 13 4 10 6 2 5 14 8 12 9\n14 2 7 12 10 5 3 9 11 15 13 4 6 8 1\n13 15 3 5 14 8 7 1 12 9 10 6 2 4 11\n2 14 4 9 12 13 5 11 1 15 6 3 10 8 7\n7 8 12 15 4 10 1 11 14 5 6 9 13 2 3\n15 10 3 8 11 14 6 13 4 2 7 12 1 5 9\n15 7 10 4 11 3 5 1 2 13 6 12 8 14 9\n11 4 2 6 7 3 9 12 8 15 5 13 1 10 14\n1 8 10 9 4 15 3 12 14 11 7 13 2 6 5\n2 5 10 8 1 3 4 11 7 13 9 6 12 14 15\n");
   		std::ostringstream w;
   		voting_solve(r,w);
   		CPPUNIT_ASSERT(w.str() == "Spain\n");
   	}
   	
   	void test_vs_super_complex()
   	{
   		std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n\n15\nFrance\nGermany\nItaly\nNorway\nSweeden\nFinland\nEngland\nSwitzerland\nUkraine\nDenmark\nCzech Republic\nAustria\nNetherlands\nPortugal\nSpain\n1 2 3 4 5 6 7 8 9 10 11 12 13 14 15\n4 6 12 10 14 1 13 8 2 11 9 7 5 15 3\n10 6 9 3 8 15 12 14 13 2 1 7 5 11 4\n11 15 1 3 7 13 4 10 6 2 5 14 8 12 9\n14 2 7 12 10 5 3 9 11 15 13 4 6 8 1\n13 15 3 5 14 8 7 1 12 9 10 6 2 4 11\n2 14 4 9 12 13 5 11 1 15 6 3 10 8 7\n7 8 12 15 4 10 1 11 14 5 6 9 13 2 3\n15 10 3 8 11 14 6 13 4 2 7 12 1 5 9\n15 7 10 4 11 3 5 1 2 13 6 12 8 14 9\n11 4 2 6 7 3 9 12 8 15 5 13 1 10 14\n1 8 10 9 4 15 3 12 14 11 7 13 2 6 5\n2 5 10 8 1 3 4 11 7 13 9 6 12 14 15\n");
   		std::ostringstream w;
   		voting_solve(r,w);
   		CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\n\nSpain\n");
   	}
   	
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read_basic);
    CPPUNIT_TEST(test_read_one_candidate);
    CPPUNIT_TEST(test_read_no_votes);
    
    CPPUNIT_TEST(test_vbc_basic);
    CPPUNIT_TEST(test_vbc_one_elimination);
    CPPUNIT_TEST(test_vbc_two_elimination);
    
    CPPUNIT_TEST(test_vel_basic);
    CPPUNIT_TEST(test_vel_most_votes);
    CPPUNIT_TEST(test_vel_majority);
    CPPUNIT_TEST(test_vel_majority_minus_one);
    CPPUNIT_TEST(test_vel_tie);
    CPPUNIT_TEST(test_vel_not_a_tie);
    
    CPPUNIT_TEST(test_vcws_basic);
    CPPUNIT_TEST(test_vcws_tie);
    CPPUNIT_TEST(test_vcws_one_person);
    
    CPPUNIT_TEST(test_vs_basic);
    CPPUNIT_TEST(test_vs_complex);
    CPPUNIT_TEST(test_vs_super_complex);
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
