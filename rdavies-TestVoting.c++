// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

/*
  To test the program:
  % ls /usr/include/cppunit/
  ...
  TestFixture.h
  ...
  % locate libcppunit.a
  /usr/lib/libcppunit.a
  % g++ -lcppunit -ldl -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting.c++.app
  % valgrind TestVoting.c++.app >& TestVoting.c++.out
*/

// ----------
// TestVoting
// ----------

struct TestVoting : CppUnit::TestFixture {
  // ----------
  // read_names
  // ----------

  void test_read_names_1() {
    std::istringstream r("3\nPerson A\nPerson B\nPerson C\n");
    voting_read_names(r);
    CPPUNIT_ASSERT(names.size() == 3);
    CPPUNIT_ASSERT(ballotStorage.size() == 3);
    CPPUNIT_ASSERT(names[0] == "Person A");
    CPPUNIT_ASSERT(names[1] == "Person B");
    CPPUNIT_ASSERT(names[2] == "Person C");
    ballotStorage.clear();
    names.clear();
  }

  void test_read_names_2() {

    std::istringstream r("5\nPerson 1\nPerson 2\nPerson 3\nPerson 4\nPerson 5\n");
    voting_read_names(r);
    CPPUNIT_ASSERT(names.size() == 5);
    CPPUNIT_ASSERT(ballotStorage.size() == 5);
    CPPUNIT_ASSERT(names[0] == "Person 1");
    CPPUNIT_ASSERT(names[1] == "Person 2");
    CPPUNIT_ASSERT(names[2] == "Person 3");
    CPPUNIT_ASSERT(names[3] == "Person 4");
    CPPUNIT_ASSERT(names[4] == "Person 5");
    ballotStorage.clear();
    names.clear();
  }

  void test_read_names_3() {
    std::istringstream r("2\nPerson 1 one\nPerson 2 two\n");
    voting_read_names(r);
    CPPUNIT_ASSERT(names.size() == 2);
    CPPUNIT_ASSERT(ballotStorage.size() == 2);
    CPPUNIT_ASSERT(names[0] == "Person 1 one");
    CPPUNIT_ASSERT(names[1] == "Person 2 two");
    ballotStorage.clear();
    names.clear();
  }


  // ------------
  // read_ballots
  // ------------

  /*** relies on read_names ***/
  void test_read_ballots_1() {
    std::istringstream r("4\nRed\nGreen\nBlue\nOrange\n");
    voting_read_names(r);
    r.str("1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1\n\n");
    voting_read_ballots(r);
    CPPUNIT_ASSERT(ballotStorage[0].size() == 2);
    CPPUNIT_ASSERT(ballotStorage[1].size() == 2);
    CPPUNIT_ASSERT(ballotStorage[2].size() == 1);
    CPPUNIT_ASSERT(ballotStorage[3].size() == 1);
    CPPUNIT_ASSERT(ballotStorage[0][0].front() == 1);
    CPPUNIT_ASSERT(ballotStorage[0][1].front() == 1);
    CPPUNIT_ASSERT(ballotStorage[1][0].front() == 2);
    CPPUNIT_ASSERT(ballotStorage[1][1].front() == 2);
    CPPUNIT_ASSERT(ballotStorage[2][0].front() == 3);
    CPPUNIT_ASSERT(ballotStorage[3][0].front() == 4);
    ballotStorage.clear();
    names.clear();
  }

  void test_read_ballots_2() {
    std::istringstream r("3\nA\nB\nC\n");
    voting_read_names(r);
    r.str("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n3 2 1\n2 1 3\n1 2 3\n2 3 1\n\n");
    voting_read_ballots(r);
    CPPUNIT_ASSERT(ballotStorage[0].size() == 3);
    CPPUNIT_ASSERT(ballotStorage[1].size() == 4);
    CPPUNIT_ASSERT(ballotStorage[2].size() == 2);
    CPPUNIT_ASSERT(ballotStorage[0][0].front() == 1);
    CPPUNIT_ASSERT(ballotStorage[0][1].front() == 1);
    CPPUNIT_ASSERT(ballotStorage[0][2].front() == 1);
    CPPUNIT_ASSERT(ballotStorage[1][0].front() == 2);
    CPPUNIT_ASSERT(ballotStorage[1][1].front() == 2);
    CPPUNIT_ASSERT(ballotStorage[1][2].front() == 2);
    CPPUNIT_ASSERT(ballotStorage[1][3].front() == 2);
    CPPUNIT_ASSERT(ballotStorage[2][0].front() == 3);
    CPPUNIT_ASSERT(ballotStorage[2][1].front() == 3);
    ballotStorage.clear();
    names.clear();
  }

  void test_read_ballots_3() {
    std::istringstream r("2\nPerson A\nPerson B\n\n");
    voting_read_names(r);
    r.str("1 2\n2 1\n\n");
    voting_read_ballots(r);
    CPPUNIT_ASSERT(ballotStorage[0].size() == 1);
    CPPUNIT_ASSERT(ballotStorage[1].size() == 1);
    CPPUNIT_ASSERT(ballotStorage[0][0].front() == 1);
    CPPUNIT_ASSERT(ballotStorage[1][0].front() == 2);
    ballotStorage.clear();
    names.clear();
  }


  // ------------
  // check_winner
  // ------------

  /*** relies on read_names and read_ballots ***/
  void test_check_winner_1() {
    std::istringstream r("5\nPerson A\nPerson B\nPerson C\nPerson D\nPerson E\n");
    voting_read_names(r);
    r.str("1 2 5 3 4\n2 5 1 3 4\n3 2 1 4 5\n5 1 2 3 4\n4 3 5 1 2\n\n");
    voting_read_ballots(r);
    int num = voting_check_winner(5);
    CPPUNIT_ASSERT(num == -1);

    ballotStorage.clear();
    names.clear();
  }

  void test_check_winner_2() {
    std::istringstream r("4\nPerson 1\nPerson 2\nPerson 3\nPerson 4\n");
    voting_read_names(r);
    r.str("1 2 3 4\n2 1 3 4\n1 2 3 4\n1 2 3 4\n4 3 1 2\n\n");
    voting_read_ballots(r);
    int num = voting_check_winner(5);
    CPPUNIT_ASSERT(num == 0);
    ballotStorage.clear();
    names.clear();
  }

  void test_check_winner_3() {
    std::istringstream r("5\nSir Foo 1\nSir Foo 2\nSir Foo 3\nSir Foo 4\nSir Foo 5\n");
    voting_read_names(r);
    r.str("1 2 5 3 4\n5 2 1 3 4\n5 2 1 4 3\n1 5 2 3 4\n5 3 4 1 2\n\n");
    voting_read_ballots(r);
    int num = voting_check_winner(5);
    CPPUNIT_ASSERT(num == 4);
    ballotStorage.clear();
    names.clear();
  }


  // -----------
  // count_votes
  // -----------

  /*** relies on check_winner, read_names and read_ballots ***/
  void test_count_votes_1() {
    std::istringstream r("4\nRed\nGreen\nBlue\nOrange\n");
    voting_read_names(r);
    r.str("1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1\n\n");
    voting_read_ballots(r);
    std::vector<std::string> winners = voting_count_votes(6);
    CPPUNIT_ASSERT(winners.size() == 2);
    CPPUNIT_ASSERT(winners[0] == "Red");
    CPPUNIT_ASSERT(winners[1] == "Green");
    ballotStorage.clear();
    names.clear();
  }

  void test_count_votes_2() {
    std::istringstream r("3\nA\nB\nC\n");
    voting_read_names(r);
    r.str("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 2 1\n3 1 2\n3 2 1\n\n");
    voting_read_ballots(r);
    std::vector<std::string> winners = voting_count_votes(6);
    CPPUNIT_ASSERT(winners.size() == 1);
    CPPUNIT_ASSERT(winners[0] == "C");
    ballotStorage.clear();
    names.clear();
  }

  void test_count_votes_3() {
    std::istringstream r("5\nPerson A\nPerson B\nPerson C\nPerson D\nPerson E\n");
    voting_read_names(r);
    r.str("1 2 5 3 4\n2 5 1 3 4\n3 2 1 4 5\n5 1 2 3 4\n4 3 5 1 2\n\n");
    voting_read_ballots(r);
    std::vector<std::string> winners = voting_count_votes(6);
    CPPUNIT_ASSERT(winners.size() == 5);
    CPPUNIT_ASSERT(winners[0] == "Person A");
    CPPUNIT_ASSERT(winners[1] == "Person B");
    CPPUNIT_ASSERT(winners[2] == "Person C");
    CPPUNIT_ASSERT(winners[3] == "Person D");
    CPPUNIT_ASSERT(winners[4] == "Person E");
    ballotStorage.clear();
    names.clear();
  }


  // -----
  // solve
  // -----

  void test_print_winners_1() {
    std::ostringstream w;
    std::vector<std::string> winners;
    winners.push_back("Person A");
    voting_print_winners(w, winners, false);
    CPPUNIT_ASSERT(w.str() == "Person A\n\n");
  }

  void test_print_winners_2() {
    std::ostringstream w;
    std::vector<std::string> winners;
    winners.push_back("A");
    winners.push_back("B");
    winners.push_back("C");
    voting_print_winners(w, winners, false);
    CPPUNIT_ASSERT(w.str() == "A\nB\nC\n\n");
  }

  void test_print_winners_3() {
    std::ostringstream w;
    std::vector<std::string> winners;
    winners.push_back("foo");
    winners.push_back("bar");
    voting_print_winners(w, winners, true);
    CPPUNIT_ASSERT(w.str() == "foo\nbar\n");
  }


  // -----
  // solve
  // -----

  /*** relies on all previous tests ***/
  void test_solve_1() {
    std::istringstream r("1\n\n3\nPerson A\nPerson B\nPerson C\n1 2 3\n2 3 1\n3 2 1\n\n");
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Person A\nPerson B\nPerson C\n");
    ballotStorage.clear();
    names.clear();
  }

  void test_solve_2() {
    std::string test1names = "3\n\n4\nRed\nGreen\nBlue\nOrange\n";
    std::string test1votes = "1 2 3 4\n2 3 1 4\n3 4 1 2\n4 3 2 1\n\n";
    std::string test2names = "3\nA\nB\nC\n";
    std::string test2votes = "1 2 3\n1 2 3\n1 2 3\n 2 3 1\n 3 2 1\n\n";
    std::string test3names = "2\nReece\nBrien\n";
    std::string test3votes = "1 2\n2 1\n 2 1\n 1 2\n\n";
    std::istringstream r(test1names + test1votes + test2names + test2votes + test3names + test3votes);
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Red\nGreen\nBlue\nOrange\n\nA\n\nReece\nBrien\n");
    ballotStorage.clear();
    names.clear();
  }

  void test_solve_3() {
    std::string test1names = "2\n\n3\nPerson A\nPerson B\nPerson C\n";
    std::string test1votes = "1 2 3\n3 2 1\n3 1 2\n3 2 1\n\n";
    std::string test2names = "3\nfoo\nbar\nbaz\n";
    std::string test2votes = "1 2 3\n1 2 3\n1 2 3\n 2 3 1\n 3 2 1\n\n";
    std::istringstream r(test1names + test1votes + test2names + test2votes);
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Person C\n\nfoo\n");
    ballotStorage.clear();
    names.clear();
  }


  // -----
  // suite
  // -----

  CPPUNIT_TEST_SUITE(TestVoting);
  CPPUNIT_TEST(test_read_names_1);
  CPPUNIT_TEST(test_read_names_2);
  CPPUNIT_TEST(test_read_names_3);
  CPPUNIT_TEST(test_read_ballots_1);
  CPPUNIT_TEST(test_read_ballots_2);
  CPPUNIT_TEST(test_read_ballots_3);
  CPPUNIT_TEST(test_check_winner_1);
  CPPUNIT_TEST(test_check_winner_2);
  CPPUNIT_TEST(test_check_winner_3);
  CPPUNIT_TEST(test_count_votes_1);
  CPPUNIT_TEST(test_count_votes_2);
  CPPUNIT_TEST(test_count_votes_3);
  CPPUNIT_TEST(test_print_winners_1);
  CPPUNIT_TEST(test_print_winners_2);
  CPPUNIT_TEST(test_print_winners_3);
  CPPUNIT_TEST(test_solve_1);
  CPPUNIT_TEST(test_solve_2);
  CPPUNIT_TEST(test_solve_3);
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
  return 0;
}
