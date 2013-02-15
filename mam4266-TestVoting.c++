#include <cassert>  // assert
#include <sstream>  // istringtstream, ostringstream
#include <string>
#include <vector>
#include <algorithm>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner


#include "Voting.h"


struct TestVoting : CppUnit::TestFixture {

// tests go here
void test_voting_solve_1(){
    istringstream r("1\n\n2\nJohn Doe\nJane Smith\n1 2\n2 1");
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\n");
}
void test_voting_solve_2(){
    istringstream r("1\n\n1\nJohn Doe\n1\n1\n1");
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "John Doe\n");
}
void test_voting_solve_3(){
    istringstream r("1\n\n3\nmariel\njessica\nbatman\n1 2 3\n1 2 3\n2 1 3\n1 2 3");
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "mariel\n");
}

void test_find_winner_1(){
    istringstream r("1\n\n2\nJohn Doe\nJane Smith\n1 2\n2 1");
    std::ostringstream w;
    voting_solve(r, w);
    vector<string> wins = get_winners();

    CPPUNIT_ASSERT(wins.size() > 0);
}
void test_find_winner_2(){
    istringstream r("1\n\n1\nJohn Doe\n1\n1\n1");
    std::ostringstream w;
    voting_solve(r, w);
    vector<string> wins = get_winners();

    CPPUNIT_ASSERT(wins.size() == 1);
}
void test_find_winner_3(){
    istringstream r("1\n\n3\nmariel\njessica\nbatman\n1 2 3\n1 2 3\n2 1 3\n1 2 3");
    std::ostringstream w;
    voting_solve(r, w);
    vector<string> wins = get_winners();

    CPPUNIT_ASSERT(wins.size() == 1);
}


// suite
	CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_voting_solve_1);
    CPPUNIT_TEST(test_voting_solve_2);
    CPPUNIT_TEST(test_voting_solve_3);
    CPPUNIT_TEST(test_find_winner_1);
    CPPUNIT_TEST(test_find_winner_2);
    CPPUNIT_TEST(test_find_winner_3);
	CPPUNIT_TEST_SUITE_END();};

//main
int main(){
  using namespace std;
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
