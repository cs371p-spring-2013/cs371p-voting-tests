#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "Voting.h"

struct TestVoting : CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(TestVoting);
    
    //test read
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    
    CPPUNIT_TEST(test_tied_1);
    CPPUNIT_TEST(test_tied_2);
    CPPUNIT_TEST(test_tied_3);
    
    CPPUNIT_TEST(test_reassign_1);
    CPPUNIT_TEST(test_reassign_2);
    CPPUNIT_TEST(test_reassign_3);
    
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    
    CPPUNIT_TEST_SUITE_END();
	
	//test base case with sample input
	void test_read_1(){
		std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        vector<Candidate> candidate_list;
        
    	int num_candidates, i;
		r >> num_candidates;
	
		//The zero index is a dummy candidate so candidate numbers will be assigned accordingly when read
		candidate_list.resize(num_candidates+1);
		// Read candidate names into Candidate objects
		string name;
		getline(r, name);
		for(i=1; i <=num_candidates; ++i){
			getline(r, name);
			candidate_list[i].name = name;
		}
		
		CPPUNIT_ASSERT(candidate_list[1].name == "John Doe");
        CPPUNIT_ASSERT(candidate_list[2].name == "Jane Smith");
        CPPUNIT_ASSERT(candidate_list[3].name == "Sirhan Sirhan");
        
        voting_read(r, candidate_list);
        
        CPPUNIT_ASSERT(candidate_list[1].ballots.size() == 2);
        CPPUNIT_ASSERT(candidate_list[2].ballots.size() == 2);
        CPPUNIT_ASSERT(candidate_list[3].ballots.size() == 1);
	}
	
	//test read of candidate value with more than one digit
	//and verify ranks are being read
	void test_read_2(){
		std::istringstream r("12\nOne\nTwo\nThree\nFour\nFive\nSix\nSeven\nEight\nNine\nTen\nEleven\nTwelve\n1 2 3 4 5 6 7 8 9 10 11 12\n");
        vector<Candidate> candidate_list;
        
    	int num_candidates, i;
		r >> num_candidates;
	
		//The zero index is a dummy candidate so candidate numbers will be assigned accordingly when read
		candidate_list.resize(num_candidates+1);
		// Read candidate names into Candidate objects
		string name;
		getline(r, name);
		for(i=1; i <=num_candidates; ++i){
			getline(r, name);
			candidate_list[i].name = name;
		}
      
        voting_read(r, candidate_list);
        
        CPPUNIT_ASSERT(candidate_list[1].ballots.size() == 1);
        CPPUNIT_ASSERT(candidate_list[2].ballots.size() == 0);
        CPPUNIT_ASSERT(candidate_list[3].ballots.size() == 0);
        CPPUNIT_ASSERT(candidate_list[4].ballots.size() == 0);
        CPPUNIT_ASSERT(candidate_list[5].ballots.size() == 0);
		CPPUNIT_ASSERT(candidate_list[6].ballots.size() == 0);
		CPPUNIT_ASSERT(candidate_list[7].ballots.size() == 0);
		CPPUNIT_ASSERT(candidate_list[8].ballots.size() == 0);
		CPPUNIT_ASSERT(candidate_list[9].ballots.size() == 0);
		CPPUNIT_ASSERT(candidate_list[10].ballots.size() == 0);
		CPPUNIT_ASSERT(candidate_list[11].ballots.size() == 0);
        CPPUNIT_ASSERT(candidate_list[12].ballots.size() == 0);
        CPPUNIT_ASSERT(candidate_list[1].ballots[0].ranks[0] == 1);
        CPPUNIT_ASSERT(candidate_list[1].ballots[0].ranks[1] == 2);
        CPPUNIT_ASSERT(candidate_list[1].ballots[0].ranks[2] == 3);
        CPPUNIT_ASSERT(candidate_list[1].ballots[0].ranks[3] == 4);
        CPPUNIT_ASSERT(candidate_list[1].ballots[0].ranks[4] == 5);
        CPPUNIT_ASSERT(candidate_list[1].ballots[0].ranks[5] == 6);
        CPPUNIT_ASSERT(candidate_list[1].ballots[0].ranks[6] == 7);
        CPPUNIT_ASSERT(candidate_list[1].ballots[0].ranks[7] == 8);
        CPPUNIT_ASSERT(candidate_list[1].ballots[0].ranks[8] == 9);
        CPPUNIT_ASSERT(candidate_list[1].ballots[0].ranks[9] == 10);
        CPPUNIT_ASSERT(candidate_list[1].ballots[0].ranks[10] == 11);
        CPPUNIT_ASSERT(candidate_list[1].ballots[0].ranks[11] == 12);
	}
	
	//test read for subsequent test cases
	void test_read_3(){
		std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        vector<Candidate> candidate_list;
        
    	int num_candidates, i;
		r >> num_candidates;
	
		//The zero index is a dummy candidate so candidate numbers will be assigned accordingly when read
		candidate_list.resize(num_candidates+1);
		// Read candidate names into Candidate objects
		string name;
		getline(r, name);
		for(i=1; i <=num_candidates; ++i){
			getline(r, name);
			candidate_list[i].name = name;
		}
		
		CPPUNIT_ASSERT(candidate_list[1].name == "John Doe");
        CPPUNIT_ASSERT(candidate_list[2].name == "Jane Smith");
        CPPUNIT_ASSERT(candidate_list[3].name == "Sirhan Sirhan");
        
        voting_read(r, candidate_list);
        
        CPPUNIT_ASSERT(candidate_list[1].ballots.size() == 2);
        CPPUNIT_ASSERT(candidate_list[2].ballots.size() == 2);
        CPPUNIT_ASSERT(candidate_list[3].ballots.size() == 1);
        
        //second test case
        vector<Candidate> candidate_list2;
        
		r >> num_candidates;
	
		//The zero index is a dummy candidate so candidate numbers will be assigned accordingly when read
		candidate_list2.resize(num_candidates+1);
		// Read candidate names into Candidate objects
		getline(r, name);
		for(i=1; i <=num_candidates; ++i){
			getline(r, name);
			candidate_list2[i].name = name;
		}
		
		CPPUNIT_ASSERT(candidate_list2[1].name == "John Doe");
        CPPUNIT_ASSERT(candidate_list2[2].name == "Jane Smith");
        CPPUNIT_ASSERT(candidate_list2[3].name == "Sirhan Sirhan");
        
        voting_read(r, candidate_list2);
        
        CPPUNIT_ASSERT(candidate_list2[1].ballots.size() == 2);
        CPPUNIT_ASSERT(candidate_list2[2].ballots.size() == 2);
        CPPUNIT_ASSERT(candidate_list2[3].ballots.size() == 1);
	}
	
	//test for the case of a tie for win
	void test_tied_1(){
		std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n3 1 2\n");
        vector<Candidate> candidate_list;
         
    	int num_candidates, i;
		r >> num_candidates;
	
		//The zero index is a dummy candidate so candidate numbers will be assigned accordingly when read
		candidate_list.resize(num_candidates+1);
		// Read candidate names into Candidate objects
		string name;
		getline(r, name);
		for(i=1; i <=num_candidates; ++i){
			getline(r, name);
			candidate_list[i].name = name;
		}
        
        voting_read(r, candidate_list);
       
        CPPUNIT_ASSERT(check_for_tied(candidate_list, 1));
	}
	
	//test that tied returns true when the winner is the only one left
	void test_tied_2(){
		std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n");
        vector<Candidate> candidate_list;
        
    	int num_candidates, i;
		r >> num_candidates;
	
		//The zero index is a dummy candidate so candidate numbers will be assigned accordingly when read
		candidate_list.resize(num_candidates+1);
		// Read candidate names into Candidate objects
		string name;
		getline(r, name);
		for(i=1; i <=num_candidates; ++i){
			getline(r, name);
			candidate_list[i].name = name;
		}
        
        voting_read(r, candidate_list);
        
        CPPUNIT_ASSERT(!check_for_tied(candidate_list, 1));
	}
	
	void test_tied_3(){
		std::istringstream r("4\nJohn Doe\nJane Smith\nSirhan Sirhan\nSpongebob Squarepants\n1 2 3 4\n4 2 3 1\n1 3 2 4\n4 1 3 2\n");
        vector<Candidate> candidate_list;
        
    	int num_candidates, i;
		r >> num_candidates;
	
		//The zero index is a dummy candidate so candidate numbers will be assigned accordingly when read
		candidate_list.resize(num_candidates+1);
		// Read candidate names into Candidate objects
		string name;
		getline(r, name);
		for(i=1; i <=num_candidates; ++i){
			getline(r, name);
			candidate_list[i].name = name;
		}
        
        voting_read(r, candidate_list);
        candidate_list[2].eliminated = true;
        candidate_list[3].eliminated = true;
        
        CPPUNIT_ASSERT(check_for_tied(candidate_list, 2));
	}
	
	//test reassign ballots of losers
	void test_reassign_1(){
		std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 3 1\n3 2 1\n1 3 2\n");
        vector<Candidate> candidate_list;
        
    	int num_candidates, i;
		r >> num_candidates;
	
		//The zero index is a dummy candidate so candidate numbers will be assigned accordingly when read
		candidate_list.resize(num_candidates+1);
		// Read candidate names into Candidate objects
		string name;
		getline(r, name);
		for(i=1; i <=num_candidates; ++i){
			getline(r, name);
			candidate_list[i].name = name;
		}
        
        voting_read(r, candidate_list);
        reassign_helper(candidate_list, 2);
        CPPUNIT_ASSERT(candidate_list[2].ballots.size() == 0);
        CPPUNIT_ASSERT(candidate_list[3].ballots.size() == 2);
        CPPUNIT_ASSERT(candidate_list[1].ballots.size() == 2);
        
	}
	
	//test that empty candidates are eliminated in reassign
	void test_reassign_2(){
		std::istringstream r("4\nJohn Doe\nJane Smith\nSirhan Sirhan\nSpongebob Squarepants\n1 2 3 4\n4 2 3 1\n1 3 2 4\n4 1 3 2\n");
        vector<Candidate> candidate_list;
        
    	int num_candidates, i;
		r >> num_candidates;
	
		//The zero index is a dummy candidate so candidate numbers will be assigned accordingly when read
		candidate_list.resize(num_candidates+1);
		// Read candidate names into Candidate objects
		string name;
		getline(r, name);
		for(i=1; i <=num_candidates; ++i){
			getline(r, name);
			candidate_list[i].name = name;
		}
        
        voting_read(r, candidate_list);
        
        reassign(candidate_list);
        
        CPPUNIT_ASSERT(check_for_tied(candidate_list, 2));
	}
	
	//test that multiple candidates with ballots to reassign get eliminated and ballots reassigned
	void test_reassign_3(){
		std::istringstream r("4\nJohn Doe\nJane Smith\nSirhan Sirhan\nSpongebob Squarepants\n1 4 2 3\n1 2 3 4\n4 1 3 2\n3 1 2 4\n2 1 3 4\n");
        vector<Candidate> candidate_list;
        
    	int num_candidates, i;
		r >> num_candidates;
	
		//The zero index is a dummy candidate so candidate numbers will be assigned accordingly when read
		candidate_list.resize(num_candidates+1);
		// Read candidate names into Candidate objects
		string name;
		getline(r, name);
		for(i=1; i <=num_candidates; ++i){
			getline(r, name);
			candidate_list[i].name = name;
		}
        
        voting_read(r, candidate_list);
        
        reassign(candidate_list);
        
        CPPUNIT_ASSERT(candidate_list[2].eliminated);
        CPPUNIT_ASSERT(candidate_list[3].eliminated);
        CPPUNIT_ASSERT(candidate_list[4].eliminated);
        CPPUNIT_ASSERT(candidate_list[1].ballots.size() == 5);
	}
	
	//test print after a reassign and some candidates eliminated
	void test_print_1(){
		std::istringstream r("4\nJohn Doe\nJane Smith\nSirhan Sirhan\nSpongebob Squarepants\n1 4 2 3\n1 2 3 4\n4 1 3 2\n3 1 2 4\n2 1 3 4\n");
        vector<Candidate> candidate_list;
        
    	int num_candidates, i;
		r >> num_candidates;
	
		//The zero index is a dummy candidate so candidate numbers will be assigned accordingly when read
		candidate_list.resize(num_candidates+1);
		// Read candidate names into Candidate objects
		string name;
		getline(r, name);
		for(i=1; i <=num_candidates; ++i){
			getline(r, name);
			candidate_list[i].name = name;
		}
        
        voting_read(r, candidate_list);
        reassign(candidate_list);
        std::ostringstream w;
        voting_print(candidate_list, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
	}
	
	//print only candidates not eliminated by hand
	void test_print_2(){
		std::istringstream r("4\nJohn Doe\nJane Smith\nSirhan Sirhan\nSpongebob Squarepants\n1 4 2 3\n1 2 3 4\n4 1 3 2\n3 1 2 4\n2 1 3 4\n");
        vector<Candidate> candidate_list;
        
    	int num_candidates, i;
		r >> num_candidates;
	
		//The zero index is a dummy candidate so candidate numbers will be assigned accordingly when read
		candidate_list.resize(num_candidates+1);
		// Read candidate names into Candidate objects
		string name;
		getline(r, name);
		for(i=1; i <=num_candidates; ++i){
			getline(r, name);
			candidate_list[i].name = name;
		}
        
        voting_read(r, candidate_list);
        
        candidate_list[1].eliminated = true;
        candidate_list[2].eliminated = true;
        candidate_list[3].eliminated = true;
        
        std::ostringstream w;
        voting_print(candidate_list, w);
        CPPUNIT_ASSERT(w.str() == "Spongebob Squarepants\n");
	}
	
	//print check that everyone is still in the running before elimination
	void test_print_3(){
		std::istringstream r("4\nJohn Doe\nJane Smith\nSirhan Sirhan\nSpongebob Squarepants\n1 4 2 3\n1 2 3 4\n4 1 3 2\n3 1 2 4\n2 1 3 4\n");
        vector<Candidate> candidate_list;
        
    	int num_candidates, i;
		r >> num_candidates;
	
		//The zero index is a dummy candidate so candidate numbers will be assigned accordingly when read
		candidate_list.resize(num_candidates+1);
		// Read candidate names into Candidate objects
		string name;
		getline(r, name);
		for(i=1; i <=num_candidates; ++i){
			getline(r, name);
			candidate_list[i].name = name;
		}
        
        voting_read(r, candidate_list);
        
        std::ostringstream w;
        voting_print(candidate_list, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\nSpongebob Squarepants\n");
	}
	
	//solve multiple reassigns
	void test_solve_1(){
		std::istringstream r("16\nNeedy Downton\nBold Nightengale\nColorful Mockingbird\nNonsensical Shrew\nQuick Cow\nEnvious Nightengale\nMassive Shrew\nProblematic Pikachu\nSizable Bear\nProblematic Chicken\nNeedy Nightengale\nCurvy Orangutan\nProblematic Bear\nLoyal Mite\nEvolved Birds\nSystematic Mite\n15 7 4 13 9 2 3 16 6 8 5 10 11 14 12 1\n10 14 11 6 3 7 5 16 13 8 1 12 15 9 2 4\n8 4 5 10 1 2 16 12 6 9 11 14 15 7 3 13\n13 1 8 4 11 15 6 7 2 12 3 10 9 14 16 5\n14 3 9 5 10 6 4 1 11 13 15 8 16 12 2 7\n13 5 12 11 10 6 2 9 15 8 4 14 16 3 1 7\n12 16 11 9 10 2 15 5 3 8 4 13 6 14 7 1\n14 1 13 4 3 6 7 12 9 16 10 5 2 11 15 8\n11 15 13 12 9 10 3 6 2 8 7 14 16 4 5 1\n16 10 14 3 2 8 11 7 6 1 5 12 15 13 4 9\n");
        
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Problematic Bear\nLoyal Mite\n");
	}
	
	//another test
	void test_solve_2(){
		std::istringstream r("5\nA\nB\nC\nD\nE\n1 2 3 4 5\n1 3 4 2 5\n2 1 4 3 5\n2 4 3 1 5\n3 4 1 2 5\n4 1 3 5 2\n");

        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "A\n");
	}
	
	void test_solve_3(){
	std::istringstream r("4\nDave\nDrake\nBake\nFake\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 4 2 3\n3 4 1 2\n");

        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Dave\n");
	}
	
};

int main(){

	using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;

	return 0;
}
