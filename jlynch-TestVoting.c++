/*
 * Test code for Voting project, TestCollatz.c++ used as a reference
 */
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

struct TestVoting : CppUnit::TestFixture{

  //Test reading
  void test_read_case_empty(){
    std::istringstream i("");
    std::vector<std::string> candidates;
    std::vector<std::queue<int>> ballots;
    CPPUNIT_ASSERT_EQUAL(false, voting_read_case(i, candidates, ballots));
  }

  void test_read_case_basic(){
    std::istringstream i("2\nDave\nBob\n1 2\n1 2");
    std::vector<std::string> candidates;
    std::vector<std::queue<int>> ballots;
    CPPUNIT_ASSERT_EQUAL(true, voting_read_case(i, candidates, ballots));
    CPPUNIT_ASSERT_EQUAL(2, (int)candidates.size());
    CPPUNIT_ASSERT(candidates[0] == "Dave");
    CPPUNIT_ASSERT(candidates[1] == "Bob");

    //Test ballots
    CPPUNIT_ASSERT_EQUAL(2, (int)ballots.size());
    CPPUNIT_ASSERT_EQUAL(2, (int) ballots[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int) ballots[1].size());
    CPPUNIT_ASSERT(ballots[0] == ballots[1]);

    CPPUNIT_ASSERT_EQUAL(1,ballots[0].front());
    ballots[0].pop();
    CPPUNIT_ASSERT_EQUAL(2,ballots[0].front());
    ballots[0].pop();
    CPPUNIT_ASSERT_EQUAL(1,ballots[1].front());
    ballots[1].pop();
    CPPUNIT_ASSERT_EQUAL(2,ballots[1].front());


  }


  void test_read_case_read(){
    std::istringstream i("3\nDave\nBob\nCriss\n1 2 3\n2 3 1\n3 2 1");
    std::vector<std::string> candidates;
    std::vector<std::queue<int>> ballots;
    CPPUNIT_ASSERT_EQUAL(true, voting_read_case(i, candidates, ballots));
    CPPUNIT_ASSERT_EQUAL(3, (int)candidates.size());
    CPPUNIT_ASSERT(candidates[0] == "Dave");
    CPPUNIT_ASSERT(candidates[1] == "Bob");
    CPPUNIT_ASSERT(candidates[2] == "Criss");
    CPPUNIT_ASSERT_EQUAL(3, (int)ballots.size());
    
    int expected[3][3] = {{1,2,3},{2,3,1},{3,2,1}};
    int queue_size;

    for(int b = 0; b<(int)ballots.size(); b++){
      queue_size = (int) ballots[b].size();
      for(int v =0; v<queue_size; v++){
        CPPUNIT_ASSERT_EQUAL(ballots[b].front(), expected[b][v]); //POP Y U NO RETURN DELETED VALUE
        ballots[b].pop(); 
      }
    }
  }
 
  //Test algo
  void test_tally_basic(){

    std::vector<std::queue<int> > ballots(3);
    ballots[0].push(1);
    ballots[1].push(1);
    ballots[2].push(1);

    ballots[0].push(2);
    ballots[1].push(2);
    ballots[2].push(2);

    ballots[0].push(3);
    ballots[1].push(3);
    ballots[2].push(3);

    std::vector<int> winners;

    voting_tally(ballots, winners);
    CPPUNIT_ASSERT_EQUAL(1, (int)winners.size());
    CPPUNIT_ASSERT(winners[0] == 1);
  }

  void test_tally_tie(){
  
    std::vector<std::queue<int>> ballots(4); 
    for(int i=0; i<4; i++){
      ballots[i].push((i < 2 ? 1 : 2)); 
      ballots[i].push((i < 2 ? 2 : 1)); 
      ballots[i].push(3); 
      ballots[i].push(4); 
    }

    std::vector<int> winners;

    voting_tally(ballots, winners);

    CPPUNIT_ASSERT_EQUAL(2, (int) winners.size());
    CPPUNIT_ASSERT_EQUAL(1, winners[0]);
    CPPUNIT_ASSERT_EQUAL(2, winners[1]);
  }

  void test_tally_tie_complex(){
  
    std::vector<std::queue<int>> ballots(6); 

    //Taken from quiz 8:

    //1 2 3 4
    //2 1 3 4
    //2 3 1 4
    //1 2 3 4
    //3 4 1 2
    //4 3 2 1

    //Winners should be 1,2
    int ballot_arr [6][4] = 
    {{1, 2, 3, 4},
    {2, 1, 3, 4},
    {2, 3, 1, 4},
    {1, 2, 3, 4},
    {3, 4, 1, 2},
    {4, 3, 2, 1}};

    for(int b=0; b<6; b++){
      for(int c=0; c<4; c++){
        ballots[b].push(ballot_arr[b][c]);
      }
    }

    std::vector<int> winners;
    voting_tally(ballots, winners);

    CPPUNIT_ASSERT_EQUAL(2, (int) winners.size());
    CPPUNIT_ASSERT_EQUAL(1, winners[0]);
    CPPUNIT_ASSERT_EQUAL(2, winners[1]);
  }

  //Test output
  void test_print_basic(){
    std::ostringstream w;
    std::vector<std::string> names;
    names.push_back("Dave");
    names.push_back("Jim");
    names.push_back("Bob");

    std::vector<int> winners;
    winners.push_back(1);

    voting_print(w, winners, names);
    CPPUNIT_ASSERT(w.str() == "Dave\n");
  }

  void test_print_adjacent(){
    std::ostringstream w;
    std::vector<std::string> names;
    names.push_back("Dave");
    names.push_back("Jim");
    names.push_back("Bob");

    std::vector<int> winners;
    winners.push_back(1);
    winners.push_back(2);

    voting_print(w, winners, names);
    CPPUNIT_ASSERT(w.str() == "Dave\nJim\n");
  }

  void test_print_spaced(){
    std::ostringstream w;
    std::vector<std::string> names;

    names.push_back("Dave");
    names.push_back("Jim");
    names.push_back("Bob");

    std::vector<int> winners;
    winners.push_back(1);
    winners.push_back(3);

    voting_print(w, winners, names);
    CPPUNIT_ASSERT(w.str() == "Dave\nBob\n");
  }
 
  //Test whole thing 

  void test_voting_elect_basic(){
    //TODO delete unnecessary couts
    //std::cout << "Doing basic elect test" << std::endl;

    std::string input = std::string("1\n")+
    "\n"+
    "3\n"+
    "Bob Boblaw\n"+
    "Michael Bluth\n"+
    "George Michael\n"+
    "1 2 3\n"+
    "1 2 3\n"+
    "1 3 2";
    std::string out = "Bob Boblaw\n";

    
    std::istringstream r(input);
    std::ostringstream w;
    voting_elect(r, w);
    CPPUNIT_ASSERT(w.str() == out);
  }

  void test_voting_elect_complex(){
    //std::cout << "Doing complex elect test" << std::endl;
    //Taken from quiz 8 again
    std::string input = std::string("1\n")+
    "\n"+
    "4\n"+
    "Red\n"+
    "Green\n"+
    "Blue\n"+
    "Orange\n"+
    "1 2 3 4\n"+
    "2 1 3 4\n"+
    "2 3 1 4\n"+
    "1 2 3 4\n"+
    "3 4 1 2\n"+
    "4 3 2 1";
    std::string out = "Red\nGreen\n";

    
    std::istringstream r(input);
    std::ostringstream w;
    voting_elect(r, w);
    CPPUNIT_ASSERT_EQUAL(out, w.str());
  }

  void test_voting_elect_cases(){
    //std::cout << "Doing multiple case elect test" << std::endl;
    //Mix of other two test cases
    std::string input = std::string("2\n")+
    "\n"+
    "4\n"+
    "Red\n"+
    "Green\n"+
    "Blue\n"+
    "Orange\n"+
    "1 2 3 4\n"+
    "2 1 3 4\n"+
    "2 3 1 4\n"+
    "1 2 3 4\n"+
    "3 4 1 2\n"+
    "4 3 2 1\n"+
    "\n"+
    "3\n"+
    "Bob Boblaw\n"+
    "Michael Bluth\n"+
    "George Michael\n"+
    "1 2 3\n"+
    "1 2 3\n"+
    "1 3 2";
    std::string out = "Red\nGreen\n\nBob Boblaw\n";
    
    std::istringstream r(input);
    std::ostringstream w;
    voting_elect(r, w);
    CPPUNIT_ASSERT_EQUAL(out, w.str());
  }

  //Test Suite
  CPPUNIT_TEST_SUITE(TestVoting);

  CPPUNIT_TEST(test_tally_basic);
  CPPUNIT_TEST(test_tally_tie);
  CPPUNIT_TEST(test_tally_tie_complex);

  CPPUNIT_TEST(test_print_basic);
  CPPUNIT_TEST(test_print_spaced);
  CPPUNIT_TEST(test_print_adjacent);

  CPPUNIT_TEST(test_read_case_basic);
  CPPUNIT_TEST(test_read_case_empty);
  CPPUNIT_TEST(test_read_case_read);

  CPPUNIT_TEST(test_voting_elect_basic);
  CPPUNIT_TEST(test_voting_elect_complex);
  CPPUNIT_TEST(test_voting_elect_cases);

  CPPUNIT_TEST_SUITE_END();
};

//The code below is almost completely copied from the collatz project
int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
