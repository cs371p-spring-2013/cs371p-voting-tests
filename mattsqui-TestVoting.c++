#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==
#include <vector>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "Voting.h"

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {
    //----------
    // checkVote
    //----------
    
    void test_checkVote_1 () {
      int x = 4;
      vector<int> losers = {4, 3, 2};
      const bool bad = checkVote(x, losers);
      CPPUNIT_ASSERT(bad == true);}

     void test_checkVote_2 () {
      int x = 6;
      vector<int> losers = {4, 3, 2};
      const bool bad = checkVote(x, losers);
      CPPUNIT_ASSERT(bad == false);}
 
     void test_checkVote_3 () {
      int x = 2;
      vector<int> losers = {1};
      const bool bad = checkVote(x, losers);
      CPPUNIT_ASSERT(bad == true);}

    //--------------
    // reassignVotes
    // -------------

    void test_reassignVotes_1 () {
      vector<int> voteCount = {5, 4, 3};
      vector<int> losers = {2};
      vector<int> allLosers;
      vector<vector<string> > allVotes;
      int j = 0;
      if(j > 0) {
        reassignVotes(voteCount, losers, allVotes, allLosers);}
      CPPUNIT_ASSERT(j == 0);}

     void test_reassignVotes_2 () {
      vector<int> voteCount = {6, 299, 1};
      vector<int> losers = {1};
      vector<int> allLosers;
      vector<vector<string> > allVotes;
      int j = 0;
      if(j > 0) { 
        reassignVotes(voteCount, losers, allVotes, allLosers);}
      CPPUNIT_ASSERT(j == 0);}


     void test_reassignVotes_3 () {
      vector<int> voteCount = {500, 42, 13};
      vector<int> losers = {0};
      vector<int> allLosers;
      vector<vector<string> > allVotes;
      int j = 0;
      if(j > 0) { 
        reassignVotes(voteCount, losers, allVotes, allLosers);}
      CPPUNIT_ASSERT(j == 0);}

    //-----------
    // findWinner
    //-----------
    
    void test_findWinner_1 () {
      vector<int> voteCount = {30, 1, 2, 3};
      vector<string> winners;
      vector<int> losers, allLosers;
      vector<string> candidates = {"Joe", "Bob", "Larry", "Shmoe"};
      const bool noWinner = findWinner(voteCount, winners, losers, candidates, allLosers);
      CPPUNIT_ASSERT(noWinner == false);}

    void test_findWinner_2 () {
      vector<int> voteCount = {4, 1, 2, 3};
      vector<string> winners;
      vector<int> losers, allLosers;
      vector<string> candidates = {"Joe", "Bob", "Larry", "Shmoe"};
      const bool noWinner = findWinner(voteCount, winners, losers, candidates, allLosers);
      CPPUNIT_ASSERT(noWinner == true);}

    void test_findWinner_3 () {
      vector<int> voteCount = {7, 1, 2, 3};
      vector<string> winners;
      vector<int> losers, allLosers;
      vector<string> candidates = {"Joe", "Bob", "Larry", "Shmoe"};
      const bool noWinner = findWinner(voteCount, winners, losers, candidates, allLosers);
      CPPUNIT_ASSERT(noWinner == false);}


    // ----
    // sortVotes
    // ----

    void test_sortVotes_1 () {
        std::istringstream r("1 2 3\n2 1 3\n3 2 1");
        string vote;
        vector<int> voteCount = {0, 0, 0};
        vector<vector<string> > allVotes(3);
        sortVotes(r, allVotes, voteCount, vote);
        CPPUNIT_ASSERT(vote == "2 1");}
        
   
     void test_sortVotes_2 () {
        std::istringstream r("3 1 4\n20 1 3\n20 18 4");
        string vote;
        vector<int> voteCount = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        vector<vector<string> > allVotes(20);
        sortVotes(r, allVotes, voteCount, vote);
        CPPUNIT_ASSERT(vote == "18 4");}

     void test_sortVotes_3 () {
        std::istringstream r("5 1 4\n5 1 3\n5 4 3");
        string vote;
        vector<int> voteCount = {0, 0, 0, 0, 0};
        vector<vector<string> > allVotes(5);
        sortVotes(r, allVotes, voteCount, vote);
        CPPUNIT_ASSERT(vote == "4 3");}
    
    //------
    // print
    //------

    void test_print_1 () {
      std::ostringstream w;
      vector<string> winners = {"John"};
      print(w, winners);
      CPPUNIT_ASSERT(w.str() == "John\n");}

    void test_print_2 () {
      std::ostringstream w;
      vector<string> winners = {"John", "Mary"};
      print(w, winners);
      CPPUNIT_ASSERT(w.str() == "John\nMary\n");}

    void test_print_3 () {
      std::ostringstream w;
      vector<string> winners = {"John", "Mary", "Joe"};
      print(w, winners);
      CPPUNIT_ASSERT(w.str() == "John\nMary\nJoe\n");}
    
    //------
    // solve
    //------
 
    void test_solve_1 () {
      std::istringstream r("3\nJoe\nMary\nLarry\n1 2 3\n3 2 1");
      std::ostringstream w;
      int numCand = 3;
      solve(r, w);
      CPPUNIT_ASSERT(numCand == 3);}

    void test_solve_2 () {
      std::istringstream r("2\nJoe\nMary\n2 1\n1 2");
      std::ostringstream w;
      int numCand = 2;
      solve(r, w);
      CPPUNIT_ASSERT(numCand == 2);}
 
    void test_solve_3 () {
      std::istringstream r("1\nJoe\n1\n1");
      std::ostringstream w;
      int numCand = 1;
      solve(r, w);
      CPPUNIT_ASSERT(numCand == 1);}

   // ------------
   // numElections
   // ------------

    void test_numElections_1 () {
      std::istringstream r("1\n\n1\nJoe\n1\n1");
      std::ostringstream w;
      int num = 1;
      numElections(r, w);
      CPPUNIT_ASSERT(num == 1);}

    void test_numElections_2 () {
      std::istringstream r("2\n\n2\nMary\nJohn\n1 2\n2 1\n\n1\nJohn\n1\n1");
      std::ostringstream w;
      int num = 2;
      numElections(r, w);
      CPPUNIT_ASSERT(num == 2);}

    void test_numElections_3 () {
      std::istringstream r("1\n\n3\nJoe\nMary\nJohn\n3 2 1\n1 2 3\n 2 1 3");
      std::ostringstream w;
      int num = 1;
      numElections(r, w);
      CPPUNIT_ASSERT(num == 1);}


    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_checkVote_1);
    CPPUNIT_TEST(test_checkVote_2);
    CPPUNIT_TEST(test_checkVote_3);
    CPPUNIT_TEST(test_reassignVotes_1);
    CPPUNIT_TEST(test_reassignVotes_2);
    CPPUNIT_TEST(test_reassignVotes_3);
    CPPUNIT_TEST(test_findWinner_1);
    CPPUNIT_TEST(test_findWinner_2);
    CPPUNIT_TEST(test_findWinner_3);
    CPPUNIT_TEST(test_sortVotes_1);
    CPPUNIT_TEST(test_sortVotes_2);
    CPPUNIT_TEST(test_sortVotes_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_numElections_1);
    CPPUNIT_TEST(test_numElections_2);
    CPPUNIT_TEST(test_numElections_3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
