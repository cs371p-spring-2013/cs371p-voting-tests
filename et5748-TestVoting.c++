#include <cassert>
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <list>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"


struct TestVoting : CppUnit::TestFixture{

  //----------------
  //store_candidates
  //---------------- 
  void test_store_candidates_1(){
   std::istringstream r("\nSimba\nMufasa\nScar\n");
   Candidate candidates[4];
   store_candidates(r,3,candidates);
   CPPUNIT_ASSERT(candidates[2].name=="Mufasa");
  }
  void test_store_candidates_2(){
   std::istringstream r("\nJurassic\nRobots\n");
   Candidate candidates[4];
   store_candidates(r,2,candidates);
   CPPUNIT_ASSERT(candidates[0].name=="");
  }
  void test_store_candidates_3(){
   std::istringstream r("\nPresident\n");
   Candidate candidates[2];
   store_candidates(r,1,candidates);
   CPPUNIT_ASSERT(candidates[1].name=="President");
  }

  //-------------
  //store_ballots
  //-------------
  void test_store_ballots_1(){
    std::istringstream r("1 2 3\n");
    int num=3;
    std::list<int> listArray[5];
    int ballots=store_ballots (r, num, listArray);
    CPPUNIT_ASSERT(ballots==1);}

  void test_store_ballots_2(){
    std::istringstream r("1 2 3\n3 2 1\n 2 1 3\n 3 1 2\n");
    int num=3;
    std::list<int> listArray[5];
    int ballots=store_ballots (r, num, listArray);
    CPPUNIT_ASSERT(ballots==4);}

  void test_store_ballots_3(){
    std::istringstream r("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20\n2 1 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20\n");
    int num=20;
    std::list<int> listArray[5];
    int ballots=store_ballots (r, num, listArray);
    CPPUNIT_ASSERT(ballots==2);}

  //-----------
  //count_votes
  //-----------
   void test_count_votes_1(){
     std::istringstream r("\nJoseph Stalin\nPresident Eisenhower\n2 1\n1 2\n");
     Candidate candidates[3];
     std::list<int> listArray[5];
     store_candidates(r, 2, candidates);
     int ballots= store_ballots(r,2,listArray);
     string s=count_votes(listArray, candidates, 2, ballots);
     CPPUNIT_ASSERT(s=="tie");
   }

   void test_count_votes_2(){
     std::istringstream r("\nJoseph Stalin\nPresident Eisenhower\n2 1\n");
     Candidate candidates[3];
     std::list<int> listArray[5];
     store_candidates(r, 2, candidates);
     int ballots=store_ballots(r,2,listArray);
     string s=count_votes(listArray, candidates, 2, ballots);
     CPPUNIT_ASSERT(s=="President Eisenhower");
   }

   void test_count_votes_3(){
     std::istringstream r("\nJoseph Stalin\nPresident Eisenhower\n2 1\n 1 2\n 1 2\n");
     Candidate candidates[3];
     std::list<int> listArray[5];
     store_candidates(r, 2, candidates);
     int ballots=store_ballots(r,2,listArray);
     string s=count_votes(listArray, candidates, 2, ballots);
     CPPUNIT_ASSERT(s=="Joseph Stalin");
   }
 

 
  //------------
  //voting_solve
  //------------
  void test_solve_1(){
    std::istringstream r("2\nJoseph Stalin\nPresident Eisenhower\n2 1\n2 1\n\n");
    std::ostringstream w;
    std::list<int> listArray[5];
    Candidate candidates[3];
    voting_solve(r, w, listArray, candidates);
    CPPUNIT_ASSERT(w.str()=="President Eisenhower");
  }
  void test_solve_2(){
    std::istringstream r("3\nLuke Skywalker\nJames T Kirk\nSimba\n3 2 1\n2 3 1\n 3 1 2\n3 1 2\n\n");
    std::ostringstream w;
    std::list<int> listArray[5];
    Candidate candidates[4];
    voting_solve(r, w, listArray, candidates);
    CPPUNIT_ASSERT(w.str()=="Simba");
  }
  void test_solve_3(){
    std::istringstream r("3\nGandalf\nMerlin\nSaruman\n2 1 3\n\n");
    std::ostringstream w;
    std::list<int> listArray[5];
    Candidate candidates[4];
    voting_solve(r, w, listArray, candidates);
    CPPUNIT_ASSERT(w.str()=="Merlin");
  }

  
  //suite
  //-----
  CPPUNIT_TEST_SUITE(TestVoting);

  CPPUNIT_TEST(test_store_candidates_1);
  CPPUNIT_TEST(test_store_candidates_2);
  CPPUNIT_TEST(test_store_candidates_3);

  CPPUNIT_TEST(test_store_ballots_1);
  CPPUNIT_TEST(test_store_ballots_2);
  CPPUNIT_TEST(test_store_ballots_3);


  CPPUNIT_TEST(test_count_votes_1);  //returns either "tie" or winner
  CPPUNIT_TEST(test_count_votes_2);
  CPPUNIT_TEST(test_count_votes_3);  


  CPPUNIT_TEST(test_solve_1);
  CPPUNIT_TEST(test_solve_2);
  CPPUNIT_TEST(test_solve_3);

  CPPUNIT_TEST_SUITE_END();
};

//----
//main
//----

int main ()
{
  using namespace std;
  ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
  cout << "TestVoting.c++" << endl;

  CppUnit::TextTestRunner tr;
  tr.addTest(TestVoting::suite());
  tr.run();

  cout << "Done." << endl;
  return 0;
}

