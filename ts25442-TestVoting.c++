// ----------------------------
// CS371p Project 2 - Voting
// Tim Simmons - ts25442
// ----------------------------

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
    // read
    // ----

    void test_read_1 () {
        std::istringstream r("3\nWalter White\nJesse Pinkman\nSkyler White\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        int candidates = 0;
        int ballots = 0;
        // cout << "pre read ";
        // cout << flush; 
        voting_read(r, candidates, ballots);
       // print_all(candidates);
        CPPUNIT_ASSERT(candidates ==    3);
        CPPUNIT_ASSERT(ballots ==    5);
    }

    void test_read_2 () {
        std::istringstream r("4\nShawn Spencer\nBurton Guster\nCarlton Lassiter\nJuliet O'Hara\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 1 2 4\n");
        int candidates = 0;
        int ballots = 0;
        voting_read(r, candidates, ballots);
        // print_all(candidates);
        CPPUNIT_ASSERT(candidates ==    4);
        CPPUNIT_ASSERT(ballots ==    5);
    }

    void test_read_3 () {
        std::istringstream r("0\n");
        int candidates = 0;
        int ballots = 0;
        voting_read(r, candidates, ballots);
        // print_all(candidates);
        CPPUNIT_ASSERT(candidates ==    0);
        CPPUNIT_ASSERT(ballots ==    0);
    }
    
    void test_loser_1 () {
     std::vector<candidate> election;
     std::vector<int> losers;
     std::vector<int> new_losers;
     int loser_placer = 0;
     struct candidate c;
     c.ballots.clear();
     election.clear();
     vector<int> b; 
     c.name = "Bob";
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     c.ballots.clear();
     c.name = "Joe";
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     c.ballots.clear();
     c.name = "Jerk";
     c.ballots.push_back(b);
     election.push_back(c);
     int test = check_losers(losers, new_losers, loser_placer, election);
     CPPUNIT_ASSERT(test == 1);
     CPPUNIT_ASSERT(losers[0] == 2);
 }

 void test_loser_2 (){
     std::vector<candidate> election;
     std::vector<int> losers;
     std::vector<int> new_losers;
     int loser_placer = 0;
     struct candidate c;
     c.ballots.clear();
     election.clear();
     vector<int> b; 
     c.name = "Bob";
     c.ballots.push_back(b);
     election.push_back(c);
     c.ballots.clear();
     c.name = "Joe";
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     c.ballots.clear();
     c.name = "Jerk";
     c.ballots.push_back(b);
     c.ballots.push_back(b); // 1 2 2 1
     election.push_back(c);
     c.ballots.clear();
     c.name = "Smit";
     c.ballots.push_back(b);
     election.push_back(c);
     int test = check_losers(losers, new_losers, loser_placer, election);
     CPPUNIT_ASSERT(test = 2);
     CPPUNIT_ASSERT(losers[0] == 0);
     CPPUNIT_ASSERT(losers[1] == 3);  
 }

 void test_loser_3 (){
     std::vector<candidate> election;
     std::vector<int> losers;
     std::vector<int> new_losers;
     int loser_placer = 0;
     struct candidate c;
     vector<int> b;
     c.ballots.clear();
     election.clear();
     c.name = "Bob";
     c.ballots.push_back(b);
     election.push_back(c);
     c.ballots.clear();
     c.name = "Joe";
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     c.ballots.clear();
     c.name = "Jerk";
     c.ballots.push_back(b);
     election.push_back(c);
     c.ballots.clear();
     c.name = "Smit";
     c.ballots.push_back(b);
     election.push_back(c);
     int test = check_losers(losers, new_losers, loser_placer, election);
     CPPUNIT_ASSERT(test = 3);
     CPPUNIT_ASSERT(losers[0] == 0);
     CPPUNIT_ASSERT(losers[1] == 2);
     CPPUNIT_ASSERT(losers[2] == 3);   
 }

 void test_loser_4 () {
     std::vector<candidate> election;
     std::vector<int> losers;
     std::vector<int> new_losers;
     int loser_placer = 0;
     struct candidate c;
     vector<int> b;
     election.clear();
     c.ballots.clear();
     c.name = "Bob";
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     c.ballots.clear();
     c.name = "Joe";
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     c.ballots.clear();
     c.name = "Jerk";
     c.ballots.push_back(b);
     election.push_back(c);
     c.ballots.clear();
     c.name = "Smit";
     c.ballots.push_back(b);
     election.push_back(c);
     int test = check_losers(losers, new_losers, loser_placer, election);
     CPPUNIT_ASSERT(test == 2);
     CPPUNIT_ASSERT(losers[0] == 2);
     CPPUNIT_ASSERT(losers[0] == 3);
 }

    //check tie
 void test_tie_1 () {
     std::vector<int> losers;
     std::vector<int> new_losers;
     struct candidate c;
     vector<int> b;
     std::vector<candidate> election;
     c.ballots.clear();
     election.clear();
     c.name = "Bob";
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     c.ballots.clear();
     c.name = "Joe";
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     int test = check_tie(election);
     CPPUNIT_ASSERT(test == true);
 }

 void test_tie_2 () {
     std::vector<int> losers;
     std::vector<int> new_losers;
     struct candidate c;
     vector<int> b;
     std::vector<candidate> election;
     election.clear();
     c.ballots.clear();
     c.name = "Bob";
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     c.ballots.clear();
     c.name = "Joe";
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     c.ballots.clear();
     c.name = "Jerk";
     c.ballots.push_back(b);
     election.push_back(c);
     bool test = check_tie(election);
     CPPUNIT_ASSERT(test == false);
 }

 void test_tie_3 () {
     std::vector<int> losers;
     std::vector<int> new_losers;
     struct candidate c;
     vector<int> b;
     std::vector<candidate> election;
     election.clear();
     c.ballots.clear();
     c.name = "Bob";
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     c.ballots.clear();
     c.name = "Joe";
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     c.ballots.clear();
     c.name = "Jerk";
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     bool test = check_tie(election);
     CPPUNIT_ASSERT(test == true);
 }

    //check tie
 void test_eval_1 () {
     std::vector<int> losers;
     std::vector<int> new_losers;
     struct candidate c;
     vector<int> b;

     std::vector<candidate> election;
     c.ballots.clear();
     election.clear();


     c.name = "Bob";
     b.push_back(1);
     b.push_back(2);
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     b.clear();
     c.ballots.clear();
     c.name = "Joe";
     b.push_back(2);
     b.push_back(1);
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     int arr[20];
     int test = voting_eval(2, 4, arr);
     CPPUNIT_ASSERT(test == 1);
 }

 void test_eval_2 () {
    std::vector<int> losers;
     std::vector<int> new_losers;
     struct candidate c;
     vector<int> b;

     std::vector<candidate> election;
     c.ballots.clear();
     election.clear();


     c.name = "Bob";
     b.push_back(1);
     b.push_back(2);
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     b.clear();
     c.ballots.clear();
     c.name = "Joe";
     b.push_back(2);
     b.push_back(1);
     c.ballots.push_back(b);
     election.push_back(c);
     int arr[20];
     int test = voting_eval(2, 3, arr);
     CPPUNIT_ASSERT(test == 1);
 }

 void test_eval_3 () {
     std::vector<int> losers;
     std::vector<int> new_losers;
     struct candidate c;
     vector<int> b;

     std::vector<candidate> election;
     c.ballots.clear();
     election.clear();


     c.name = "Bob";
     b.push_back(1);
     b.push_back(2);
     c.ballots.push_back(b);
     election.push_back(c);
     b.clear();
     c.ballots.clear();
     c.name = "Joe";
     b.push_back(2);
     b.push_back(1);
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     int arr[20];
     int test = voting_eval(2, 3, arr);
     CPPUNIT_ASSERT(test == 1);
     CPPUNIT_ASSERT(arr[0] = 1);
 }

 void test_reassign_1(){
     std::vector<int> losers;
     std::vector<int> new_losers;
     struct candidate c;
     vector<int> b;

     std::vector<candidate> election;
     c.ballots.clear();
     election.clear();


     c.name = "Bob";
     b.push_back(1);
     b.push_back(2);
     c.ballots.push_back(b);
     election.push_back(c);
     b.clear();
     c.ballots.clear();
     c.name = "Joe";
     b.push_back(2);
     b.push_back(1);
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     int arr[20];
     reassign_votes(losers, 0);

     CPPUNIT_ASSERT(election[0].ballots.size() == 1);
 }

  void test_reassign_2(){
     std::vector<int> losers;
     std::vector<int> new_losers;
     struct candidate c;
     vector<int> b;

     std::vector<candidate> election;
     c.ballots.clear();
     election.clear();


     c.name = "Bob";
     b.push_back(1);
     b.push_back(2);
     c.ballots.push_back(b);
     election.push_back(c);
     b.clear();
     c.ballots.clear();
     c.name = "Joe";
     b.push_back(2);
     b.push_back(1);
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     int arr[20];
     reassign_votes(losers, 1);
     CPPUNIT_ASSERT(election[1].ballots.size() == 2);
 }

   void test_reassign_3(){
     std::vector<int> losers;
     std::vector<int> new_losers;
     struct candidate c;
     vector<int> b;

     std::vector<candidate> election;
     c.ballots.clear();
     election.clear();


     c.name = "Bob";
     b.push_back(1);
     b.push_back(2);
     c.ballots.push_back(b);
     election.push_back(c);
     b.clear();
     c.ballots.clear();
     c.name = "Joe";
     b.push_back(2);
     b.push_back(1);
     c.ballots.push_back(b);
     c.ballots.push_back(b);
     election.push_back(c);
     int arr[20];
     reassign_votes(losers, 1);
     CPPUNIT_ASSERT(election[1].ballots.size() == 2);
     CPPUNIT_ASSERT(election[0].ballots.size() == 1);
 }



    // ----
    // eval
    // ----


    // void test_eval_1 () {
    //     const int v = voting_eval(1, 10);
    //     CPPUNIT_ASSERT(v == 20);
    // }

    // -----
    // print
    // -----

    // void test_print () {
    //     std::ostringstream w;
    //     voting_print(w, 1, 2, 3);
    //     CPPUNIT_ASSERT(w.str() == "1 2 3\n");}


    // -----
    // solve
    // -----

    // void test_solve () {
    //     std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    //     std::ostringstream w;
    //     voting_solve(r, w);
    //     CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    // -----
    // suite
    // -----

 CPPUNIT_TEST_SUITE(TestVoting);
 CPPUNIT_TEST(test_read_1);
CPPUNIT_TEST(test_read_2);
CPPUNIT_TEST(test_read_3);
CPPUNIT_TEST(test_loser_1);
CPPUNIT_TEST(test_loser_2);
CPPUNIT_TEST(test_loser_3);
CPPUNIT_TEST(test_tie_1);
CPPUNIT_TEST(test_tie_2);
 CPPUNIT_TEST(test_tie_3);
 CPPUNIT_TEST(test_eval_1);
CPPUNIT_TEST(test_eval_2);
 CPPUNIT_TEST(test_eval_3);
CPPUNIT_TEST(test_reassign_1);
CPPUNIT_TEST(test_reassign_2);
 CPPUNIT_TEST(test_reassign_3);


    // CPPUNIT_TEST(test_eval);
    // CPPUNIT_TEST(test_print);
    // CPPUNIT_TEST(test_solve);
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
