// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

//Adapted by Matt Johnson for use in projects/voting

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
#include <sstream> // istringtstream, ostringstream
#include <string> // ==
#include <cstring>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "Voting.h"

using namespace std;
// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {
    
    // ----
    // read
    // ----
  
    void test_read_1 () {
        std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        int cases = 0;
        int numCandidates = 0;
        int votes[1001][21];
        int numVotes;
        char candidates[21][81];
        
        const bool b = voting_read(r, cases, numCandidates, votes, numVotes, candidates);
            
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(cases == 1);
        CPPUNIT_ASSERT(numCandidates == 3);
        CPPUNIT_ASSERT(numVotes == 5);
        
        CPPUNIT_ASSERT(votes[0][0] == 0);
        CPPUNIT_ASSERT(votes[0][1] == 1);
        CPPUNIT_ASSERT(votes[0][2] == 2);
        CPPUNIT_ASSERT(votes[1][0] == 1);
        CPPUNIT_ASSERT(votes[1][1] == 0);
        CPPUNIT_ASSERT(votes[1][2] == 2);
        CPPUNIT_ASSERT(votes[2][0] == 1);
        CPPUNIT_ASSERT(votes[2][1] == 2);
        CPPUNIT_ASSERT(votes[2][2] == 0);
        CPPUNIT_ASSERT(votes[3][0] == 0);
        CPPUNIT_ASSERT(votes[3][1] == 1);
        CPPUNIT_ASSERT(votes[3][2] == 2);
        CPPUNIT_ASSERT(votes[4][0] == 2);
        CPPUNIT_ASSERT(votes[4][1] == 0);
        CPPUNIT_ASSERT(votes[4][2] == 1);
        
        std::string str1 ("John Doe");
        std::string str2 ("Jane Smith");
        std::string str3 ("Sirhan Sirhan");
        CPPUNIT_ASSERT(str1.compare(candidates[0]) == 0);
        CPPUNIT_ASSERT(str2.compare(candidates[1]) == 0);
        CPPUNIT_ASSERT(str3.compare(candidates[2]) == 0);
    }
    
   	void test_read_2 () {
        std::istringstream r("");
        int cases = 0;
        int numCandidates = 0;
        int votes[1001][21];
        int numVotes;
        char candidates[21][81];
        
        const bool b = voting_read(r, cases, numCandidates, votes, numVotes, candidates);
        
        CPPUNIT_ASSERT(b == false);
    }
    
    void test_read_3 () {
        std::istringstream r("1\n\n4\nDave\nDrake\nBake\nFake\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 4 2 3\n3 4 1 2\n");
        int cases = 0;
        int numCandidates = 0;
        int votes[1001][21];
        int numVotes;
        char candidates[21][81];
        
        const bool b = voting_read(r, cases, numCandidates, votes, numVotes, candidates);
        
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(cases == 1);
        CPPUNIT_ASSERT(numCandidates == 4);
        CPPUNIT_ASSERT(numVotes == 5);
        
        CPPUNIT_ASSERT(votes[0][0] == 0);
        CPPUNIT_ASSERT(votes[0][1] == 1);
        CPPUNIT_ASSERT(votes[0][2] == 2);
        CPPUNIT_ASSERT(votes[0][3] == 3);
        CPPUNIT_ASSERT(votes[1][0] == 1);
        CPPUNIT_ASSERT(votes[1][1] == 0);
        CPPUNIT_ASSERT(votes[1][2] == 2);
        CPPUNIT_ASSERT(votes[1][3] == 3);
        CPPUNIT_ASSERT(votes[2][0] == 1);
        CPPUNIT_ASSERT(votes[2][1] == 2);
        CPPUNIT_ASSERT(votes[2][2] == 0);
        CPPUNIT_ASSERT(votes[2][3] == 3);
        CPPUNIT_ASSERT(votes[3][0] == 0);
        CPPUNIT_ASSERT(votes[3][1] == 3);
        CPPUNIT_ASSERT(votes[3][2] == 1);
        CPPUNIT_ASSERT(votes[3][3] == 2);
        CPPUNIT_ASSERT(votes[4][0] == 2);
        CPPUNIT_ASSERT(votes[4][1] == 3);
        CPPUNIT_ASSERT(votes[4][2] == 0);
        CPPUNIT_ASSERT(votes[4][3] == 1);
        
        std::string str1 ("Dave");
        std::string str2 ("Drake");
        std::string str3 ("Bake");
        std::string str4 ("Fake");
        CPPUNIT_ASSERT(str1.compare(candidates[0]) == 0);
        CPPUNIT_ASSERT(str2.compare(candidates[1]) == 0);
        CPPUNIT_ASSERT(str3.compare(candidates[2]) == 0);
        CPPUNIT_ASSERT(str4.compare(candidates[3]) == 0);

    }
    
	// -------
    // compare
    // -------
    
    void test_compare_1 () {
    	int a[3] = {1, 2, 3};
    	int b[3] = {3, 2, 1};
    	
    	int c = voting_compare(a, b);
    	
    	CPPUNIT_ASSERT(c < 0);
    }
    
    void test_compare_2 () {
    	int a[3] = {3, 2, 3};
    	int b[3] = {1, 2, 1};
    	
    	int c = voting_compare(a, b);
    	
    	CPPUNIT_ASSERT(c > 0);
    }
    
    void test_compare_3 () {
    	int a[3] = {3, 2, 3};
    	int b[3] = {3, 2, 1};
    	
    	int c = voting_compare(a, b);
    	
    	CPPUNIT_ASSERT(c == 0);
    }

	
	// ---------
    // get_tally
    // ---------
    
    void test_get_tally_1 () {
		int numLosers = 0;
		int numVotes = 3;
		int votes[1001][21];
		
		votes[0][0] = 0;
		votes[0][1] = 1;
		votes[1][0] = 1;
		votes[1][1] = 0;
		votes[2][0] = 1;
		votes[2][1] = 0;
		
		int numCandidates = 2;
		int losers[21] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int tally[21] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		
		voting_get_tally(numLosers, numVotes, votes, numCandidates, losers, tally);
		
		CPPUNIT_ASSERT(tally[0] == 1);
		CPPUNIT_ASSERT(tally[1] == 2);
		for(int i = 2; i < 21; i++)
			CPPUNIT_ASSERT(tally[i] == 0);
		
    }
    
    void test_get_tally_2 () {
    	int numLosers = 1;
		int numVotes = 3;
		int votes[1001][21];
		
		votes[0][0] = 1;
		votes[0][1] = 0;
		votes[1][0] = 1;
		votes[1][1] = 0;
		votes[2][0] = 20;
		votes[2][1] = 1;
		
		int numCandidates = 2;
		int losers[21] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
		int tally[21] = {0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		
		voting_get_tally(numLosers, numVotes, votes, numCandidates, losers, tally);
		
		CPPUNIT_ASSERT(votes[2][0] == 1);
		CPPUNIT_ASSERT(tally[0] == 0);
		CPPUNIT_ASSERT(tally[1] == 3);
		for(int i = 2; i < 21; i++)
			CPPUNIT_ASSERT(tally[i] == 0);
    
    }
    
    void test_get_tally_3 () {
    	int numLosers = 0;
		int numVotes = 10;
		int votes[1001][21];
		
		votes[0][0] = 0;
		votes[0][1] = 1;
		votes[0][2] = 2;
		votes[1][0] = 1;
		votes[1][1] = 0;
		votes[1][2] = 2;
		votes[2][0] = 2;
		votes[2][1] = 1;
		votes[2][2] = 0;
		votes[3][0] = 0;
		votes[3][1] = 1;
		votes[3][2] = 2;
		votes[4][0] = 0;
		votes[4][1] = 1;
		votes[4][2] = 2;
		votes[5][0] = 0;
		votes[5][1] = 1;
		votes[5][2] = 2;
		votes[6][0] = 2;
		votes[6][1] = 1;
		votes[6][2] = 0;
		votes[7][0] = 1;
		votes[7][1] = 0;
		votes[7][2] = 2;
		votes[8][0] = 1;
		votes[8][1] = 0;
		votes[8][2] = 2;
		votes[9][0] = 1;
		votes[9][1] = 0;
		votes[9][2] = 2;

		int numCandidates = 3;
		int losers[21] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int tally[21] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		
		voting_get_tally(numLosers, numVotes, votes, numCandidates, losers, tally);
		
		CPPUNIT_ASSERT(tally[0] == 4);
		CPPUNIT_ASSERT(tally[1] == 4);
		CPPUNIT_ASSERT(tally[2] == 2);
		for(int i = 3; i < 21; i++)
			CPPUNIT_ASSERT(tally[i] == 0);
    }
	
	// ------------
    // check_winner
    // ------------
	
	void test_check_winner_1 () {		
		int numCandidates = 5;
		int tally[21] = {5, 10, 15, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int numVotes = 50;
		int winner[21] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
		
		bool b = voting_check_winner(numCandidates, tally, numVotes, winner);
		
		CPPUNIT_ASSERT(!b);
		for(int i = 0; i < 21; i++){
			CPPUNIT_ASSERT(winner[i] == -1);
		}
	}
	
	void test_check_winner_2 () {		
		int numCandidates = 20;
		int tally[21] = {1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int numVotes = 10;
		int winner[21] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
		
		bool b = voting_check_winner(numCandidates, tally, numVotes, winner);
		
		CPPUNIT_ASSERT(b);
		CPPUNIT_ASSERT(winner[0] == -1);
		CPPUNIT_ASSERT(winner[1] != -1);
		for(int i = 2; i < 21; i++){
			CPPUNIT_ASSERT(winner[i] == -1);
		}
	}
	
	void test_check_winner_3 () {		
		int numCandidates = 2;
		int tally[21] = {25, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int numVotes = 50;
		int winner[21] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
		
		bool b = voting_check_winner(numCandidates, tally, numVotes, winner);
		
		CPPUNIT_ASSERT(!b);
		for(int i = 0; i < 21; i++){
			CPPUNIT_ASSERT(winner[i] == -1);
		}
	}
	
	// ---------
    // check_tie
    // ---------
	
	void test_check_tie_1 () {
		int numCandidates = 3;
		int tally[21] = {5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int losers[21] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int winner[21] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
		
		bool b = voting_check_tie(numCandidates, tally, losers, winner);
		
		CPPUNIT_ASSERT(b);
		CPPUNIT_ASSERT(winner[0] != -1);
		CPPUNIT_ASSERT(winner[1] != -1);
		CPPUNIT_ASSERT(winner[2] != -1);
		for(int i = 3; i < 21; i++){
			CPPUNIT_ASSERT(winner[i] == -1);
		}	
	}
	
	void test_check_tie_2 () {
		int numCandidates = 20;
		int tally[21] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};
		int losers[21] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int winner[21] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
		
		bool b = voting_check_tie(numCandidates, tally, losers, winner);
		
		CPPUNIT_ASSERT(b);
		CPPUNIT_ASSERT(winner[20] == -1);
		for(int i = 0; i < 20; i++){
			CPPUNIT_ASSERT(winner[i] != -1);
		}	
	}
	
	void test_check_tie_3 () {
		int numCandidates = 3;
		int tally[21] = {5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int losers[21] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int winner[21] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
		
		bool b = voting_check_tie(numCandidates, tally, losers, winner);
		
		CPPUNIT_ASSERT(!b);
		for(int i = 0; i < 21; i++){
			CPPUNIT_ASSERT(winner[i] == -1);
		}	
	}
	
	// ----------
    // get_losers
    // ----------
    
    void test_get_losers_1 () {
		int numLosers = 0;
		int numCandidates = 5;
		int numVotes = 2;
		int losers[21] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int tally[21] = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int votes[1001][21];
		votes[0][0] = 1;
		votes[0][1] = 0;
		votes[0][2] = 2;
		votes[0][3] = 3;
		votes[0][4] = 4;
		votes[1][0] = 0;
		votes[1][1] = 1;
		votes[1][2] = 2;
		votes[1][3] = 3;
		votes[1][4] = 4;
		
		voting_get_losers(numLosers, numCandidates, numVotes, losers, tally, votes);
		
		
		CPPUNIT_ASSERT(!losers[0]);
		CPPUNIT_ASSERT(!losers[1]);
		CPPUNIT_ASSERT(losers[20]);
		CPPUNIT_ASSERT(numLosers == 0);
		for(int i = 2; i < numCandidates; i++){
			CPPUNIT_ASSERT(losers[i]);
		}
    }
    
    void test_get_losers_2 () {
		int numLosers = 0;
		int numCandidates = 2;
		int numVotes = 4;
		int losers[21] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int tally[21] = {1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int votes[1001][21];
		votes[0][0] = 0;
		votes[0][1] = 1;
		votes[1][0] = 1;
		votes[1][1] = 0;
		votes[2][0] = 1;
		votes[2][1] = 0;
		votes[3][0] = 1;
		votes[3][1] = 0;
		
		voting_get_losers(numLosers, numCandidates, numVotes, losers, tally, votes);
		
		
		CPPUNIT_ASSERT(losers[0]);
		CPPUNIT_ASSERT(!losers[1]);
		CPPUNIT_ASSERT(losers[20]);
		CPPUNIT_ASSERT(numLosers == 1);
		CPPUNIT_ASSERT(votes[0][0] == 20);
    }
    
    void test_get_losers_3 () {
		int numLosers = 0;
		int numCandidates = 1;
		int numVotes = 1;
		int losers[21] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int tally[21] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int votes[1001][21];
		votes[0][0] = 0;
		
		voting_get_losers(numLosers, numCandidates, numVotes, losers, tally, votes);
		
		
		CPPUNIT_ASSERT(losers[0]);
		CPPUNIT_ASSERT(losers[20]);
		CPPUNIT_ASSERT(numLosers == 1);
		CPPUNIT_ASSERT(votes[0][0] == 20);
    }
    
    
    // ----
    // eval
    // ----
    
    void test_eval_1 () {   	
    	int numCandidates = 4;
    	int numVotes = 4;
    	int winner[21];
    	int votes[1001][21];
    	votes[0][0] = 1;
    	votes[0][1] = 0;
    	votes[0][2] = 2;
    	votes[0][3] = 3;
    	votes[1][0] = 0;
    	votes[1][1] = 1;
    	votes[1][2] = 2;
    	votes[1][3] = 3;
    	votes[2][0] = 3;
    	votes[2][1] = 2;
    	votes[2][2] = 1;
    	votes[2][3] = 0;
    	votes[3][0] = 3;
    	votes[3][1] = 1;
    	votes[3][2] = 0;
    	votes[3][3] = 2;
    	
    	voting_eval(numCandidates, votes, numVotes, winner);
    	
    	CPPUNIT_ASSERT(winner[0] == -1);
    	CPPUNIT_ASSERT(winner[1] == -1);
    	CPPUNIT_ASSERT(winner[2] == -1);
    	CPPUNIT_ASSERT(winner[3] == 3);
    }
    
    void test_eval_2 () {   	
    	int numCandidates = 1;
    	int numVotes = 1;
    	int winner[21];
    	int votes[1001][21];
    	votes[0][0] = 0;
 	
    	voting_eval(numCandidates, votes, numVotes, winner);
    	
    	CPPUNIT_ASSERT(winner[0] == 0);
    }
    
    void test_eval_3 () {   	
    	int numCandidates = 2;
    	int numVotes = 2;
    	int winner[21];
    	int votes[1001][21];
    	votes[0][0] = 1;
    	votes[0][1] = 0;
    	votes[1][0] = 0;
    	votes[1][1] = 1;
    	
    	voting_eval(numCandidates, votes, numVotes, winner);
    	
    	CPPUNIT_ASSERT(winner[0] == 0);
    	CPPUNIT_ASSERT(winner[1] == 1);
    }
	
    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        int winner[21] = {0, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
        char candidates[21][81] = {{"hello"}, {"bye"}, {"no"}, {"yes"}, {"kyle"}, {"bake"}, {"dude"},
        							{"mine"}, {"never"}, {"this"}, {"dude"}, {"Jo"}, {"forne"}, {"hope"},
        							{"great"}, {"man"}, {"modern"}, {"six"}, {"last"}, {"first"}, {"please"}};
        int cases = 1;
        voting_print(w, winner, candidates, cases);
        
        

        CPPUNIT_ASSERT(w.str() == "hello\nbye\n");
    }
    
    void test_print_2 () {
        std::ostringstream w;
        int winner[21] = {-1, -1, -1, 3, -1, -1, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
        char candidates[21][81] = {{"hello"}, {"bye"}, {"no"}, {"yes"}, {"kyle"}, {"bake"}, {"dude"},
        							{"mine"}, {"never"}, {"this"}, {"dude"}, {"Jo"}, {"forne"}, {"hope"},
        							{"great"}, {"man"}, {"modern"}, {"six"}, {"last"}, {"first"}, {"please"}};
        int cases = 1;
        voting_print(w, winner, candidates, cases);
      	
        CPPUNIT_ASSERT(w.str() == "yes\ndude\nmine\n");
    }
    
    void test_print_3 () {
        std::ostringstream w;
        int winner[21] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
        char candidates[21][81] = {{"hello"}, {"bye"}, {"no"}, {"yes"}, {"kyle"}, {"bake"}, {"dude"},
        							{"mine"}, {"never"}, {"this"}, {"dude"}, {"Jo"}, {"forne"}, {"hope"},
        							{"great"}, {"man"}, {"modern"}, {"six"}, {"last"}, {"first"}, {"please"}};
        int cases = 1;
        voting_print(w, winner, candidates, cases);

        CPPUNIT_ASSERT(w.str() == "this\n");
    }
    
    // -----
    // solve
    // -----
	
    void test_solve_1 () {
        std::istringstream r("1\n\n3\nDoug\nBarry\nDirk\n1 2 3\n3 2 1\n2 1 3\n1 2 3\n 1 3 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Doug\n");
     }
     
     void test_solve_2 () {
        std::istringstream r("1\n\n1\nDavid\n1\n1\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "David\n");
     }
     
     void test_solve_3 () {
        std::istringstream r("2\n\n3\nDoug\nBarry\nDirk\n1 2 3\n3 2 1\n2 1 3\n1 2 3\n 1 3 2\n\n1\nDavid\n1\n1\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Doug\n\nDavid\n");
     }
	
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_compare_1);
    CPPUNIT_TEST(test_compare_2);
    CPPUNIT_TEST(test_compare_3);
    CPPUNIT_TEST(test_get_tally_1);
    CPPUNIT_TEST(test_get_tally_2);
    CPPUNIT_TEST(test_get_tally_3);
    CPPUNIT_TEST(test_check_winner_1);
    CPPUNIT_TEST(test_check_winner_2);
    CPPUNIT_TEST(test_check_winner_3);
    CPPUNIT_TEST(test_check_tie_1);
    CPPUNIT_TEST(test_check_tie_2);
    CPPUNIT_TEST(test_check_tie_3);
    CPPUNIT_TEST(test_get_losers_1);
    CPPUNIT_TEST(test_get_losers_2);
    CPPUNIT_TEST(test_get_losers_3);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    //ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
