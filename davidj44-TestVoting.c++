#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==
#include <vector>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "Voting.h"

using namespace std;

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_can_1 () {
        std::istringstream r("\nDavid Joseph\nJeff Li");
        int candidates = 2;
        vector<string> namesList(candidates);
        namesList = readNames(r, candidates);
        CPPUNIT_ASSERT(namesList.at(0).compare("David Joseph") == 0);
        CPPUNIT_ASSERT(namesList.at(1).compare("Jeff Li") == 0);}
    
    void test_read_can_2 () {
        std::istringstream r("\nJohn Doe\nJane Smith\nSirhan Sirhan");
        int candidates = 3;
        vector<string> namesList(candidates);
        namesList = readNames(r, candidates);
        CPPUNIT_ASSERT(namesList.at(0).compare("John Doe") == 0);
        CPPUNIT_ASSERT(namesList.at(1).compare("Jane Smith") == 0);
        CPPUNIT_ASSERT(namesList.at(2).compare("Sirhan Sirhan") == 0);}    
        
    void test_read_can_3 () {
        std::istringstream r("\nJohn Doe");
        int candidates = 1;
        vector<string> namesList(candidates);
        namesList = readNames(r, candidates);
        CPPUNIT_ASSERT(namesList.at(0).compare("John Doe") == 0);}
        
    void test_read_bal_1 () {
        std::istringstream r("1 2 3 4");
        int candidates = 4;
        vector<vector<int> > ballotList;
        ballotList = readBallots(r, candidates);
        CPPUNIT_ASSERT(ballotList.at(0).at(0) == 1);
        CPPUNIT_ASSERT(ballotList.at(0).at(1) == 2);
        CPPUNIT_ASSERT(ballotList.at(0).at(2) == 3);
        CPPUNIT_ASSERT(ballotList.at(0).at(3) == 4);}          

    void test_read_bal_2 () {
        std::istringstream r("1 2 3 4\n4 2 3 1");
        int candidates = 4;
        vector<vector<int> > ballotList;
        ballotList = readBallots(r, candidates);
        CPPUNIT_ASSERT(ballotList.at(0).at(0) == 1);
        CPPUNIT_ASSERT(ballotList.at(0).at(1) == 2);
        CPPUNIT_ASSERT(ballotList.at(0).at(2) == 3);
        CPPUNIT_ASSERT(ballotList.at(0).at(3) == 4);
        CPPUNIT_ASSERT(ballotList.at(1).at(0) == 4);
        CPPUNIT_ASSERT(ballotList.at(1).at(1) == 2);
        CPPUNIT_ASSERT(ballotList.at(1).at(2) == 3);
        CPPUNIT_ASSERT(ballotList.at(1).at(3) == 1);}
        
    void test_read_bal_3 () {
        std::istringstream r("1 2 3 4\n1 2 3 4\n2 1 3 4\n2 1 3 4\n3 4 1 2");
        int candidates = 4;
        vector<vector<int> > ballotList;
        ballotList = readBallots(r, candidates);
        CPPUNIT_ASSERT(ballotList.at(0).at(0) == 1);
        CPPUNIT_ASSERT(ballotList.at(1).at(1) == 2);
        CPPUNIT_ASSERT(ballotList.at(2).at(2) == 3);
        CPPUNIT_ASSERT(ballotList.at(3).at(3) == 4);
        CPPUNIT_ASSERT(ballotList.at(4).at(1) == 4);}    
        
    void test_countVotes_1 () {
        vector<vector<int> > votes = {{1, 2, 3, 4}, {2, 1, 3, 4}};
        int candidates = 4;
        vector<vector<int> > result;
        result = countVotes(votes, candidates);
        CPPUNIT_ASSERT(result.at(0).at(0) == 0);
        CPPUNIT_ASSERT(result.at(1).at(0) == 1);
        CPPUNIT_ASSERT(result.at(2).size() == 0);
        CPPUNIT_ASSERT(result.at(3).size() == 0);} 
        
    void test_countVotes_2 () {
        vector<vector<int> > votes = {{1, 2, 3, 4}, {2, 1, 3, 4}, {2, 3, 1, 4}, {1, 2, 3, 4}, {3, 1, 2, 4}};
        int candidates = 4;
        vector<vector<int> > result;
        result = countVotes(votes, candidates);
        CPPUNIT_ASSERT(result.at(0).at(0) == 0);
        CPPUNIT_ASSERT(result.at(1).at(0) == 1);
        CPPUNIT_ASSERT(result.at(1).at(1) == 2);
        CPPUNIT_ASSERT(result.at(0).at(1) == 3);
        CPPUNIT_ASSERT(result.at(2).at(0) == 4);}
        
    void test_countVotes_3 () {
        vector<vector<int> > votes = {{4, 2, 3, 1}};
        int candidates = 4;
        vector<vector<int> > result;
        result = countVotes(votes, candidates);
        CPPUNIT_ASSERT(result.at(3).at(0) == 0);}                            
      
    void test_checkWin_1 () {
        vector<vector<int> > votes = {{0, 1, 3}, {2, 4, 5}, {6, 7}, {}};
        vector<int> losers = {0, 0, 0, 0};
        bool result;
        int total = 8;
        result = checkWin(votes, losers, total);
        CPPUNIT_ASSERT(result == false);
        CPPUNIT_ASSERT(losers.at(0) == 0); 
        CPPUNIT_ASSERT(losers.at(1) == 0);
        CPPUNIT_ASSERT(losers.at(2) == 0);
        CPPUNIT_ASSERT(losers.at(3) == 1);}
        
    void test_checkWin_2 () {
        vector<vector<int> > votes = {{0, 1, 3}, {2, 4, 5}, {6, 7}, {}};
        vector<int> losers = {0, 0, 0, 1};
        bool result;
        int total = 8;
        result = checkWin(votes, losers, total);
        CPPUNIT_ASSERT(result == false);
        CPPUNIT_ASSERT(losers.at(0) == 0); 
        CPPUNIT_ASSERT(losers.at(1) == 0);
        CPPUNIT_ASSERT(losers.at(2) == 1);
        CPPUNIT_ASSERT(losers.at(3) == 2);}

    void test_checkWin_3 () {
        vector<vector<int> > votes = {{0, 1, 3}, {2, 4, 5}, {6, 7}, {}};
        vector<int> losers = {0, 0, 1, 2};
        bool result;
        int total = 8;
        result = checkWin(votes, losers, total);
        CPPUNIT_ASSERT(result == false);
        CPPUNIT_ASSERT(losers.at(0) == 1); 
        CPPUNIT_ASSERT(losers.at(1) == 1);
        CPPUNIT_ASSERT(losers.at(2) == 2);
        CPPUNIT_ASSERT(losers.at(3) == 3);}
	
    void test_checkTie_1 () {
        vector<int> losers = {0, 0, 0, 1};
        bool result;
        result = checkTie(losers);
        CPPUNIT_ASSERT(result == false);}
        
    void test_checkTie_2 () {
        vector<int> losers = {0, 0, 1, 2};
        bool result;
        result = checkTie(losers);
        CPPUNIT_ASSERT(result == false);}
        
    void test_checkTie_3 () {
        vector<int> losers = {1, 1, 2, 3};
        bool result;
        result = checkTie(losers);
        CPPUNIT_ASSERT(result == true);}
    
        
    void test_processVotes_1 () {
        vector<vector<int> > ballotList = {{1, 2, 3, 4}, {2, 1, 3, 4}, {3, 4, 1, 2}, {1, 3, 2, 4}};
        vector<int> losers = {0, 0, 0, 1};
        vector<vector<int> > votes = {{0,3},{1},{2},{}};
        vector<vector<int> > result;
        result = processVotes(ballotList, votes, losers);
        CPPUNIT_ASSERT(result.at(0).at(0) == 1);
        CPPUNIT_ASSERT(result.at(1).at(0) == 2);
        CPPUNIT_ASSERT(result.at(2).at(0) == 3);
        CPPUNIT_ASSERT(result.at(3).at(0) == 1);}
           
    void test_processVotes_2 () {
        vector<vector<int> > ballotList = {{1, 2, 3, 4}, {2, 1, 3, 4}, {3, 4, 1, 2}, {1, 3, 2, 4}};
        vector<int> losers = {0, 0, 1, 2};
        vector<vector<int> > result;
        vector<vector<int> > votes = {{0,3},{1},{2},{}};
        result = processVotes(ballotList, votes, losers);
        CPPUNIT_ASSERT(result.at(0).at(0) == 1);
        CPPUNIT_ASSERT(result.at(1).at(0) == 2);
        CPPUNIT_ASSERT(result.at(2).at(0) == 1);
        CPPUNIT_ASSERT(result.at(3).at(0) == 1);
        CPPUNIT_ASSERT(votes.at(0).at(2) == 2);}
   
    void test_processVotes_3 () {
        vector<vector<int> > ballotList = {{3, 4, 1, 2}, {3, 4, 2, 1}, {4, 3, 1, 2}, {1, 4, 3, 2}};
        vector<int> losers = {0, 0, 1, 1};
        vector<vector<int> > result;
        vector<vector<int> > votes = {{3},{},{0,1},{2}};
        result = processVotes(ballotList, votes, losers);
        CPPUNIT_ASSERT(result.at(0).at(0) == 1);
        CPPUNIT_ASSERT(result.at(1).at(0) == 2);
        CPPUNIT_ASSERT(result.at(2).at(0) == 1);
        CPPUNIT_ASSERT(result.at(3).at(0) == 1);
        CPPUNIT_ASSERT(votes.at(0).at(2) == 2);}  
      
    void test_solve_1 () {
    	std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3");
    	std::ostringstream w;
    	votingSolve(r, w);
    	CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\n");}
    	
  	void test_solve_2 () {
    	std::istringstream r("4\nDoodoo Jones\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 1 2 4");
    	std::ostringstream w;
    	votingSolve(r, w);
    	CPPUNIT_ASSERT(w.str() == "Doodoo Jones\n");}
    	
    void test_solve_3 () {
    	std::istringstream r("7\nDoodoo Jones\nJohn Doe\nJane Smith\nSirhan Sirhan\nAbe Lincoln\nDarth Vader\nOzarka\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7\n1 2 3 4 5 6 7");
    	std::ostringstream w;
    	votingSolve(r, w);
    	CPPUNIT_ASSERT(w.str() == "Doodoo Jones\n");} 
    	
    void test_print_1 () {
    	vector<int> losers = {0, 1, 1, 1};
    	vector<string> names = {"Dirk Nowitzski", "Ray Allen", "LeBron James", "Steve Nash"};
    	std::ostringstream w;
    	printWinner(losers, names, w, false);
    	CPPUNIT_ASSERT(w.str() == "Dirk Nowitzski\n");}
    	
    void test_print_2 () {
    	vector<int> losers = {1, 1, 1, 0};
    	vector<string> names = {"Dirk Nowitzski", "Ray Allen", "LeBron James", "Steve Nash"};
    	std::ostringstream w;
    	printWinner(losers, names, w, false);
    	CPPUNIT_ASSERT(w.str() == "Steve Nash\n");}
    	
    void test_print_3 () {
    	vector<int> losers = {0, 1, 1, 1};
    	vector<string> names = {"Dirk Nowitzski", "Ray Allen", "LeBron James", "Steve Nash"};
    	std::ostringstream w;
    	printWinner(losers, names, w, true);
    	CPPUNIT_ASSERT(w.str() == "Ray Allen\nLeBron James\nSteve Nash\n");}
    	    	
    CPPUNIT_TEST_SUITE(TestVoting);
    
    CPPUNIT_TEST(test_read_can_1);
    CPPUNIT_TEST(test_read_can_2);
    CPPUNIT_TEST(test_read_can_3);
    CPPUNIT_TEST(test_read_bal_1);
    CPPUNIT_TEST(test_read_bal_2);
    CPPUNIT_TEST(test_read_bal_3);
   
    CPPUNIT_TEST(test_countVotes_1);
    CPPUNIT_TEST(test_countVotes_2);
    CPPUNIT_TEST(test_countVotes_3);
    
    CPPUNIT_TEST(test_checkWin_1);
    CPPUNIT_TEST(test_checkWin_2);
    CPPUNIT_TEST(test_checkWin_3);
    CPPUNIT_TEST(test_checkTie_1);
    CPPUNIT_TEST(test_checkTie_2);
    CPPUNIT_TEST(test_checkTie_3);
    CPPUNIT_TEST(test_processVotes_1);
    CPPUNIT_TEST(test_processVotes_2);
    CPPUNIT_TEST(test_processVotes_3);
	CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);  
    CPPUNIT_TEST(test_solve_3);  
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST_SUITE_END();};

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
