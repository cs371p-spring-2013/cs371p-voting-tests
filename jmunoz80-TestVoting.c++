#include <iostream>
#include <sstream>
#include <string>

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"
#include <string.h>
#include "Voting.h"

struct TestVoting : CppUnit::TestFixture{

  void test_read(){
    std::istringstream r("\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n 2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n");
    std::string candidates[20];
    int players = 0;
    
    const bool b = voting_read_setup(r, candidates, players); 
    CPPUNIT_ASSERT(b == true);
    CPPUNIT_ASSERT(players == 3);
    CPPUNIT_ASSERT(candidates[0] == "John Doe");
    CPPUNIT_ASSERT(candidates[1] == "Jane Smith");
    CPPUNIT_ASSERT(candidates[2] == "Sirhan Sirhan");
  }

  void test_read2(){
    std::istringstream r("\n3\nWabbajack\nJane Goodall\nJosan Munoz\n1 2 3\n 2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n");
    std::string candidates[20];
    int players = 0;
    
    const bool b = voting_read_setup(r, candidates, players); 
    CPPUNIT_ASSERT(b == true);
    CPPUNIT_ASSERT(players == 3);
    CPPUNIT_ASSERT(candidates[0] == "Wabbajack");
    CPPUNIT_ASSERT(candidates[1] == "Jane Goodall");
    CPPUNIT_ASSERT(candidates[2] == "Josan Munoz");
  }

  void test_read3(){
    std::istringstream r("\n5\nA\nB\nC\nD\nE\n1 2 3\n 2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n");
    std::string candidates[20];
    int players = 0;
    
    const bool b = voting_read_setup(r, candidates, players); 
    CPPUNIT_ASSERT(b == true);
    CPPUNIT_ASSERT(players == 5);
    CPPUNIT_ASSERT(candidates[0] == "A");
    CPPUNIT_ASSERT(candidates[1] == "B");
    CPPUNIT_ASSERT(candidates[2] == "C");
    CPPUNIT_ASSERT(candidates[3] == "D");
    CPPUNIT_ASSERT(candidates[4] == "E");
  }


  //
  // TESTING READING VOTES
  // 
   
  void test_read_votes( ){
    std::istringstream r("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n");
    int box[1000][20];
    int count = 0;
    const bool v = voting_read_votes(r, box, 3, count);
    CPPUNIT_ASSERT(v == true);
    CPPUNIT_ASSERT(count == 5);
    CPPUNIT_ASSERT(box[0][0] == 1);
    CPPUNIT_ASSERT(box[0][1] == 2);
    CPPUNIT_ASSERT(box[0][2] == 3);
    CPPUNIT_ASSERT(box[2][0] == 2);
    CPPUNIT_ASSERT(box[2][1] == 3);
    CPPUNIT_ASSERT(box[2][2] == 1);
    CPPUNIT_ASSERT(box[4][0] == 3);
    CPPUNIT_ASSERT(box[4][1] == 1);
    CPPUNIT_ASSERT(box[4][2] == 2); 
  }
  void test_read_votes_max_cand( ){
    std::istringstream r("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20\n2 1 3 17 5 19 20 7 4 8 11 10 15 6 9 12 13 14 16 18\n20 13 11 4 2 5 17 10 1 7 9 3 14 12 6 8 15 16 18 19\n20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1\n\n");
    int box[1000][20];
    int count = 0;
    const bool v = voting_read_votes(r, box, 20, count);
    CPPUNIT_ASSERT(v == true);
    CPPUNIT_ASSERT(count == 4);
    CPPUNIT_ASSERT(box[0][0] == 1);
    CPPUNIT_ASSERT(box[0][10] == 11);
    CPPUNIT_ASSERT(box[0][19] == 20);
    CPPUNIT_ASSERT(box[2][0] == 20);
    CPPUNIT_ASSERT(box[2][10] == 9);
    CPPUNIT_ASSERT(box[2][19] == 19);
    CPPUNIT_ASSERT(box[3][0] == 20);
    CPPUNIT_ASSERT(box[3][1] == 19);
    CPPUNIT_ASSERT(box[3][2] == 18); 
  }

  void test_read_votes_min( ){
    std::istringstream r("1 2\n2 1\n2 1\n1 2\n2 1\n\n");
    int box[1000][20];
    int count = 0;
    const bool v = voting_read_votes(r, box, 2, count);
    CPPUNIT_ASSERT(v == true);
    CPPUNIT_ASSERT(count == 5);
    CPPUNIT_ASSERT(box[0][0] == 1);
    CPPUNIT_ASSERT(box[0][1] == 2);
    CPPUNIT_ASSERT(box[2][0] == 2);
    CPPUNIT_ASSERT(box[2][1] == 1);
    CPPUNIT_ASSERT(box[4][0] == 2);
    CPPUNIT_ASSERT(box[4][1] == 1);
  }
  //
  // TESTING EVAL
  //

  void test_eval(){
    int options[] = {0, 0, 5, 3, 0}; 
    int ballot_box[1000][20] = { {1, 2, 3}, {2, 1, 3}, {2, 3, 1}, {1, 2, 3}, {3, 1, 2} };
    int lost[20], rankings[20], winners[20];
    int i;
    for(i = 0; i < 20; i++){
      lost[i] = 0; 
      rankings[i] = 0;
    }
    while(options[1] <= 0){
      voting_eval(options, ballot_box, lost, rankings, winners);
      options[0]++;
    }
    CPPUNIT_ASSERT(options[1] = 1);
  }
  
  void test_basic_eval(){
    int options[] = {0, 0, 6, 4, 0, 0}; 
    int ballot_box[1000][20] = { {1, 2, 3, 4}, {2, 1, 3, 4}, {2, 3, 1, 4}, {1, 2, 3, 4}, {3, 4, 1, 2}, {4, 3, 2, 1} };
    int lost[20], rankings[20], winners[20];
    int i;
    for(i = 0; i < 20; i++){
      lost[i] = 0; 
      rankings[i] = 0;
    }
    while(options[1] <= 0){
      voting_eval(options, ballot_box, lost, rankings, winners);
      options[0]++;
    }
    CPPUNIT_ASSERT(options[1] = 2);
  }

  void test_eval_mult_win(){
    int options[] = {0, 0, 6, 4, 0, 0}; 
    int ballot_box[1000][20] = { {1, 2, 3, 4}, {2, 1, 3, 4}, {2, 3, 1, 4}, {1, 2, 3, 4}, {3, 4, 1, 2}, {4, 3, 2, 1} };
    int lost[20], rankings[20], winners[20];
    int i;
    for(i = 0; i < 20; i++){
      lost[i] = 0; 
      rankings[i] = 0;
    }
    while(options[1] <= 0){
      voting_eval(options, ballot_box, lost, rankings, winners);
      options[0]++;
    }
    CPPUNIT_ASSERT(options[1] = 2);
  }


  //
  // TESTING PRINTING
  //
  void test_print(){
    std::ostringstream w;
    std::string n1 = "John Doe", n2 = "Jane Smith", n3 = "Sirhan Sirhan";
    std::string names[20] = {n1, n2, n3};
    int winners[20] = {0};
    voting_print(w, names, 1, winners);
    std::string tmp = w.str();
    CPPUNIT_ASSERT(tmp.compare(n1) == 2); 
  }

  void test_print_multiple(){
    std::ostringstream w;
    std::string n1 = "Red", n2 = "Green", n3 = "Blue";
    std::string n4 = "Orange";
    std::string names[20] = {n1, n2, n3, n4};
    int winners[4] = {0, 1, -1, -1};
    voting_print(w, names, 1, winners);
    std::string tmp = w.str();
    CPPUNIT_ASSERT(tmp.compare(n1+"\n") == 1);
  }

  void test_print_full(){
    std::ostringstream w;
    std::string n1 = "John Doe", n2 = "Jane Smith", n3 = "Sirhan Sirhan";
    std::string names[20] = {n1, n2, n3};
    int winners[20] = {0, 1, 2};
    voting_print(w, names, 1, winners);
    std::string tmp = w.str();
    CPPUNIT_ASSERT(tmp.compare(n1+"\n") == 1);
  }


  //-----
  //Suite
  //-----

  CPPUNIT_TEST_SUITE(TestVoting);
  CPPUNIT_TEST(test_read);
  CPPUNIT_TEST(test_read2);
  CPPUNIT_TEST(test_read3);
  CPPUNIT_TEST(test_read_votes);
  CPPUNIT_TEST(test_read_votes_max_cand);
  CPPUNIT_TEST(test_read_votes_min);
  CPPUNIT_TEST(test_eval);
  CPPUNIT_TEST(test_basic_eval);
  CPPUNIT_TEST(test_eval_mult_win);
  CPPUNIT_TEST(test_print);
  CPPUNIT_TEST(test_print_multiple);
  CPPUNIT_TEST(test_print_full);
  CPPUNIT_TEST_SUITE_END();
};

int main() {
  using namespace std;
   ios_base::sync_with_stdio(false);
  cout << "TestVoting.c++" << endl;

  CppUnit::TextTestRunner tr;
  tr.addTest(TestVoting::suite());
  tr.run();
 
  cout<<"Done." << endl;
  return 0;
}
