// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner
//#include <cassert>  // assert
#include <vector> // vector stuff

#include "Voting.h"


struct TestVoting : CppUnit::TestFixture {

  void test_voting_1() {
    std::ostringstream w;
    vector<string> names;
    names.push_back("aaaa");
    names.push_back("b");
    names.push_back("c");
    vector<vector<int> > ballots;
    vector<int> ballot;
    ballot.push_back(1);
    ballot.push_back(2);
    ballot.push_back(3);
    ballots.push_back(ballot);
    solve_voting(w,names,ballots);
    CPPUNIT_ASSERT(w.str() == "aaaa");
  }
  
    void test_voting_2() {
    std::ostringstream w;
    vector<string> names;
    names.push_back("a");
    names.push_back("b");
    names.push_back("c");
    vector<vector<int> > ballots;
    solve_voting(w,names,ballots);
    CPPUNIT_ASSERT(w.str() == "a\nb\nc");
  }
  
    void test_voting_3() {
    std::ostringstream w;
    vector<string> names;
    names.push_back("bob");
    names.push_back("dan");
    names.push_back("sue");
    names.push_back("geff");
    vector<vector<int> > ballots;
    vector<int> ballot;
    ballot.push_back(1);
    ballot.push_back(2);
    ballot.push_back(3);
    ballot.push_back(4);
    
    vector<int> ballot2;
    ballot2.push_back(2);
    ballot2.push_back(3);
    ballot2.push_back(4);
    ballot2.push_back(1);
    ballots.push_back(ballot);
    ballots.push_back(ballot2);
    solve_voting(w,names,ballots);
    CPPUNIT_ASSERT(w.str() == "bob\ndan");
  }
  
  void read_test_1(){
     std::ostringstream w;
     std::istringstream r("4\nbob\ndan\nsue\ngeff\n1 2 3 4\n2 3 1 4\n4 1 2 3\n\n");
     read_voting(r,w);
     CPPUNIT_ASSERT(w.str() == "bob\ndan\ngeff");
     
  }
  
    void read_test_2(){
     std::ostringstream w;
     std::istringstream r("3\nbob\ndan\naaa\n1 2 3 \n2 3 1\n1 2 3\n 2 3 1\n3 2 1\n");
     read_voting(r,w);
     CPPUNIT_ASSERT(w.str() == "dan");
     
  }
  
    void read_test_3(){
     std::ostringstream w;
     std::istringstream r("1\nJeff\n1\n2 3 1 4\n4 1 2 3\n\n");
     read_voting(r,w);
     CPPUNIT_ASSERT(w.str() == "Jeff");
     
  }
  
  void voting_test_1(){
    std::ostringstream w;
    std::istringstream r("1\n\n1\nJeff\n1\n2 3 1 4\n4 1 2 3\n\n");
    voting_solve(r,w);
    CPPUNIT_ASSERT(w.str() == "Jeff\n");
  }
  
  void voting_test_2(){
    std::ostringstream w;
    std::istringstream r("2\n\n2\nJeff\nTim\n1 2\n1 2\n2 1\n\n3\nTom\nAAA\nBBB\n1 2 3\n2 3 1\n1 2 3\n2 3 1\n3 2 1\n\n");
    voting_solve(r,w);
    CPPUNIT_ASSERT(w.str() == "Jeff\n\nAAA\n");
  }
  
  void voting_test_3(){
    std::ostringstream w;
    std::istringstream r("1\n\n3\nJeff\nMark\nKyle\n1 2 3\n2 3 1\n\n");
    voting_solve(r,w);
    CPPUNIT_ASSERT(w.str() == "Jeff\nMark\n");
  }





  CPPUNIT_TEST_SUITE(TestVoting);
  CPPUNIT_TEST(test_voting_1);
  CPPUNIT_TEST(test_voting_2);
  CPPUNIT_TEST(test_voting_3);
  CPPUNIT_TEST(read_test_1);
  CPPUNIT_TEST(read_test_2);
  CPPUNIT_TEST(read_test_3);
  CPPUNIT_TEST(voting_test_1);
  CPPUNIT_TEST(voting_test_2);
  CPPUNIT_TEST(voting_test_3);
  CPPUNIT_TEST_SUITE_END();
  };



int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}