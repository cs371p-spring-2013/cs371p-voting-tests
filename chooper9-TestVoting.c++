// ---
// includes
// ---

#include <iostream>
#include <sstream>
#include <vector>

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"

#include "Voting.h"

using namespace std;

// ---
// TestVoting
// ---

struct TestVoting : CppUnit::TestFixture {

  // ---
  // read_first
  // ---

  void test_read_first () {
    istringstream r("3\n");
    int l;
    const bool b = voting_read_first(r, l);
    CPPUNIT_ASSERT(b == true);
    CPPUNIT_ASSERT(l == 3);
  }

  void test_read_first_1 () {
    istringstream r("\n24\n");
    int l;
    const bool b = voting_read_first(r, l);
    CPPUNIT_ASSERT(b == true);
    CPPUNIT_ASSERT(l == 24);
  }

  void test_read_first_2 () {
    istringstream r("6\nRichard Marx\nMark Anthony\n");
    int l;
    const bool b = voting_read_first(r, l);
    CPPUNIT_ASSERT(b == true);
    CPPUNIT_ASSERT(l == 6);
  }

  void test_read_first_3 () {
    istringstream r("Dexter Morgan\n");
    int l;
    const bool b = voting_read_first(r, l);
    CPPUNIT_ASSERT(b == false);
  }

  // ---
  // read
  // ---

  void test_read () {
    istringstream r("2\nEdmond\nCarl Clover\n1 2\n2 1\n\n");
    int n;
    ostringstream w;
    ostringstream x;
    vector<string> candidates;
    vector<vector<string> > votes;
    const bool b = voting_read(r, n, candidates, votes);
    for(unsigned i = 0; i < candidates.size(); ++i) {
      w << candidates.at(i) << endl;
      for(unsigned j = 0; j < votes.at(i).size(); ++j)
        x << votes.at(i).at(j) << endl;
    }
    CPPUNIT_ASSERT(b == true);
    CPPUNIT_ASSERT(n == 2);
    CPPUNIT_ASSERT(w.str() == "Edmond\nCarl Clover\n");
    CPPUNIT_ASSERT(x.str() == "1 2\n2 1\n");
  }

  // test with extra blank line at front
  void test_read_1 () {
    istringstream r("\n2\nEdmond\nCarl Clover\n1 2\n2 1\n\n");
    int n;
    ostringstream w;
    ostringstream x;
    vector<string> candidates;
    vector<vector<string> > votes;
    const bool b = voting_read(r, n, candidates, votes);
    for(unsigned i = 0; i < candidates.size(); ++i) {
      w << candidates.at(i) << endl;
      for(unsigned j = 0; j < votes.at(i).size(); ++j)
        x << votes.at(i).at(j) << endl;
    }
    CPPUNIT_ASSERT(b == true);
    CPPUNIT_ASSERT(n == 2);
    CPPUNIT_ASSERT(w.str() == "Edmond\nCarl Clover\n");
    CPPUNIT_ASSERT(x.str() == "1 2\n2 1\n");
  }

  void test_read_2 () {
    istringstream r("1\nBill Murray\n1\n1\n1\n\n");
    int n;
    ostringstream w;
    ostringstream x;
    vector<string> candidates;
    vector<vector<string> > votes;
    const bool b = voting_read(r, n, candidates, votes);
    for(unsigned i = 0; i < candidates.size(); ++i) {
      w << candidates.at(i) << endl;
      for(unsigned j = 0; j < votes.at(i).size(); ++j)
        x << votes.at(i).at(j) << endl;
    }
    CPPUNIT_ASSERT(b == true);
    CPPUNIT_ASSERT(n == 1);
    CPPUNIT_ASSERT(w.str() == "Bill Murray\n");
    CPPUNIT_ASSERT(x.str() == "1\n1\n1\n");
  }

  void test_read_3 () {
    istringstream r("2\nChocobo\nMoogle\n2 1\n1 2\n2 1\n\n");
    int n;
    ostringstream w;
    ostringstream x;
    vector<string> candidates;
    vector<vector<string> > votes;
    const bool b = voting_read(r, n, candidates, votes);
    for(unsigned i = 0; i < candidates.size(); ++i) {
      w << candidates.at(i) << endl;
      for(unsigned j = 0; j < votes.at(i).size(); ++j)
        x << votes.at(i).at(j) << endl;
    }
    CPPUNIT_ASSERT(b == true);
    CPPUNIT_ASSERT(n == 2);
    CPPUNIT_ASSERT(w.str() == "Chocobo\nMoogle\n");
    CPPUNIT_ASSERT(x.str() == "1 2\n2 1\n2 1\n");
  }

  void test_read_4 () {
    istringstream r("SuperMagneticNeo\nPenPenTrilcelon\n2 1\n1 2\n2 1\n\n");
    int n;
    vector<string> candidates;
    vector<vector<string> > votes;
    const bool b = voting_read(r, n, candidates, votes);
    CPPUNIT_ASSERT(b == false);
  }

  // ---
  // score
  // ---

  void test_score () {
    vector<string> candidates;
    candidates.push_back("Keith Urban");
    candidates.push_back("Vanessa Carlton");
    candidates.push_back("DMX");
    vector<vector<string> > votes;
    vector<string> b;
    b.push_back("1 2 3");
    votes.push_back(b);
    b.clear();
    b.push_back("2 3 1");
    b.push_back("2 1 3");
    b.push_back("2 3 1");
    votes.push_back(b);
    b.clear();
    b.push_back("3 2 1");
    votes.push_back(b);
    const vector<string> winners = voting_score(candidates, votes);
    CPPUNIT_ASSERT(winners.size() == 1);
  }

  void test_score_1 () {
    vector<string> candidates;
    candidates.push_back("Keith Urban");
    candidates.push_back("Vanessa Carlton");
    candidates.push_back("DMX");
    vector<vector<string> > votes;
    vector<string> b;
    b.push_back("1 2 3");
    b.push_back("1 2 3");
    votes.push_back(b);
    b.clear();
    b.push_back("2 3 1");
    b.push_back("2 1 3");
    votes.push_back(b);
    b.clear();
    b.push_back("3 2 1");
    b.push_back("3 2 1");
    votes.push_back(b);
    const vector<string> winners = voting_score(candidates, votes);
    CPPUNIT_ASSERT(winners.size() == 3);
  }

  void test_score_2 () {
    vector<string> candidates;
    candidates.push_back("Keith Urban");
    candidates.push_back("Vanessa Carlton");
    candidates.push_back("DMX");
    vector<vector<string> > votes;
    vector<string> b;
    b.push_back("1 2 3");
    b.push_back("1 2 3");
    votes.push_back(b);
    b.clear();
    b.push_back("2 1 3");
    votes.push_back(b);
    b.clear();
    b.push_back("3 2 1");
    b.push_back("3 2 1");
    votes.push_back(b);
    const vector<string> winners = voting_score(candidates, votes);
    CPPUNIT_ASSERT(winners.size() == 1);
  }

  // ---
  // check
  // ---

  void test_check () {
    unsigned max = 0;
    unsigned min = 6;
    vector<unsigned> most;
    vector<unsigned> least;
    vector<string> candidates (1, "Laharl");
    vector<vector<string> > votes;
    vector<string> all_ones (6, "1");
    votes.push_back(all_ones);
    ostringstream w;
    ostringstream x;
    check(max, min, most, least, candidates, votes);
    w << most.at(0) << endl;
    x << least.at(0) << endl;
    CPPUNIT_ASSERT(max == 6);
    CPPUNIT_ASSERT(min == 6);
    CPPUNIT_ASSERT(most.size() == 1);
    CPPUNIT_ASSERT(least.size() == 1);
    CPPUNIT_ASSERT(w.str() == "0\n");
    CPPUNIT_ASSERT(x.str() == "0\n");
  }

  void test_check_1 () {
    unsigned max = 0;
    unsigned min = 4;
    vector<unsigned> most;
    vector<unsigned> least;
    vector<vector<string> > votes;
    vector<string> candidates;
    candidates.push_back("Yugi Moto");
    candidates.push_back("Neku Sakuraba");
    candidates.push_back("Pajama Sam");
    vector<string> vs;
    vs.push_back("1 2 3");
    vs.push_back("1 3 2");
    votes.push_back(vs);
    vs.clear();
    vs.push_back("2 1 3");
    vs.push_back("2 3 1");
    votes.push_back(vs);
    vs.clear();
    vs.push_back("3 1 2");
    votes.push_back(vs);
    check(max, min, most, least, candidates, votes);
    CPPUNIT_ASSERT(max == 2);
    CPPUNIT_ASSERT(min == 1);
  }

  void test_check_2 () {
    unsigned max = 0;
    unsigned min = 4;
    vector<unsigned> most;
    vector<unsigned> least;
    vector<vector<string> > votes;
    vector<string> candidates;
    candidates.push_back("Batman");
    candidates.push_back("Spiderman");
    vector<string> vs;
    vs.push_back("1 2");
    vs.push_back("1 2");
    votes.push_back(vs);
    vs.clear();
    vs.push_back("2 1");
    vs.push_back("2 1");
    votes.push_back(vs);
    check(max, min, most, least, candidates, votes);
    CPPUNIT_ASSERT(max == 2);
    CPPUNIT_ASSERT(min == 2);
  }

  // ---
  // rmLosers
  // ---

  void test_rmLosers () {
    vector<unsigned> losers (1, 2);
    vector<vector<string> > votes;
    vector<string> candidates;
    candidates.push_back("Yugi Moto");
    candidates.push_back("Neku Sakuraba");
    candidates.push_back("Pajama Sam");
    vector<string> vs;
    vs.push_back("1 2 3");
    vs.push_back("1 3 2");
    votes.push_back(vs);
    vs.clear();
    vs.push_back("2 1 3");
    vs.push_back("2 3 1");
    votes.push_back(vs);
    vs.clear();
    vs.push_back("3 1 2");
    votes.push_back(vs);
    ostringstream w;
    ostringstream x;
    for(unsigned i = 0; i < votes.size(); ++i) {
      for(unsigned j = 0; j < votes.at(i).size(); ++j) {
        x << votes[i][j] << endl;
      }
    }
    w << candidates[0] << " " << candidates[1] << " " << candidates[2] << endl;
    rmLosers(losers, votes);
    ostringstream y;
    for(unsigned i = 0; i < votes.size(); ++i) {
      for(unsigned j = 0; j < votes.at(i).size(); ++j) {
        y << votes[i][j] << endl;
      }
    }
    CPPUNIT_ASSERT(w.str() == "Yugi Moto Neku Sakuraba Pajama Sam\n");
    CPPUNIT_ASSERT(x.str() == "1 2 3\n1 3 2\n2 1 3\n2 3 1\n3 1 2\n");
    CPPUNIT_ASSERT(y.str() == "1 2 3\n1 3 2\n3 1 2\n2 1 3\n2 3 1\n");
    CPPUNIT_ASSERT(votes.at(2).empty());
  }

  void test_rmLosers_1 () {
    vector<unsigned> losers;
    losers.push_back(1);
    losers.push_back(2);
    vector<vector<string> > votes;
    vector<string> candidates;
    candidates.push_back("Mammon");
    candidates.push_back("Baal");
    candidates.push_back("Asmodeus");
    vector<string> vs;
    vs.push_back("1 2 3");
    vs.push_back("1 3 2");
    votes.push_back(vs);
    vs.clear();
    vs.push_back("2 1 3");
    votes.push_back(vs);
    vs.clear();
    vs.push_back("3 2 1");
    votes.push_back(vs);
    ostringstream w;
    ostringstream x;
    for(unsigned i = 0; i < votes.size(); ++i) {
      for(unsigned j = 0; j < votes.at(i).size(); ++j) {
        x << votes[i][j] << endl;
      }
    }
    w << candidates[0] << " " << candidates[1] << " " << candidates[2] << endl;
    rmLosers(losers, votes);
    ostringstream y;
    for(unsigned i = 0; i < votes.size(); ++i) {
      for(unsigned j = 0; j < votes.at(i).size(); ++j) {
        y << votes[i][j] << endl;
      }
    }
    CPPUNIT_ASSERT(w.str() == "Mammon Baal Asmodeus\n");
    CPPUNIT_ASSERT(x.str() == y.str());
    CPPUNIT_ASSERT(votes.at(1).empty());
    CPPUNIT_ASSERT(votes.at(2).empty());
  }

  void test_rmLosers_2 () {
    vector<unsigned> losers (1, 0);
    vector<vector<string> > votes;
    vector<string> candidates;
    candidates.push_back("Ratatosk");
    candidates.push_back("Gilgamesh");
    candidates.push_back("Nebilim");
    vector<string> vs;
    vs.push_back("1 2 3");
    votes.push_back(vs);
    vs.clear();
    vs.push_back("2 1 3");
    vs.push_back("2 3 1");
    votes.push_back(vs);
    vs.clear();
    vs.push_back("3 1 2");
    vs.push_back("3 2 1");
    votes.push_back(vs);
    ostringstream w;
    ostringstream x;
    for(unsigned i = 0; i < votes.size(); ++i) {
      for(unsigned j = 0; j < votes.at(i).size(); ++j) {
        x << votes[i][j] << endl;
      }
    }
    w << candidates[0] << " " << candidates[1] << " " << candidates[2] << endl;
    rmLosers(losers, votes);
    ostringstream y;
    for(unsigned i = 0; i < votes.size(); ++i) {
      for(unsigned j = 0; j < votes.at(i).size(); ++j) {
        y << votes[i][j] << endl;
      }
    }
    CPPUNIT_ASSERT(w.str() == "Ratatosk Gilgamesh Nebilim\n");
    CPPUNIT_ASSERT(x.str() == "1 2 3\n2 1 3\n2 3 1\n3 1 2\n3 2 1\n");
    CPPUNIT_ASSERT(y.str() == "2 1 3\n2 3 1\n1 2 3\n3 1 2\n3 2 1\n");
    CPPUNIT_ASSERT(votes.at(0).empty());
  }


  // ---
  // print
  // ---

  void test_print () {
    ostringstream w;
    vector<string> winners;
    winners.push_back("Sera Farron");
    voting_print(w, winners);
    CPPUNIT_ASSERT(w.str() == "Sera Farron\n");
  }

  void test_print_1 () {
    ostringstream w;
    vector<string> winners;
    winners.push_back("Miles Tails Prower");
    winners.push_back("Renamon");
    voting_print(w, winners);
    CPPUNIT_ASSERT(w.str() == "Miles Tails Prower\nRenamon\n");
  }

  void test_print_2 () {
    ostringstream w;
    vector<string> winners;
    winners.push_back("The Beatles");
    winners.push_back("Geto Boys");
    winners.push_back("The Crickets");
    voting_print(w, winners);
    CPPUNIT_ASSERT(w.str() == "The Beatles\nGeto Boys\nThe Crickets\n");
  }

  // ---
  // solve
  // ---

  void test_solve () {
    istringstream r("1\n\n1\nLloyd Irving\n1\n1\n1\n");
    ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Lloyd Irving\n");
  }

  void test_solve_1 () {
    istringstream r("2\n\n2\nYoko Ono\nYoko Okino\n2 1\n2 1\n2 1\n2 1\n\n2\nBanjo\nKazooie\n1 2\n2 1\n1 2\n2 1\n");
    ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Yoko Okino\n\nBanjo\nKazooie\n");
  }

  void test_solve_2 () {
    istringstream r("1\n\n8\nRoxanne\nBrawly\nWattson\nFlannery\nNorman\nWinona\nTate & Liza\nWallace\n8 7 6 5 4 3 2 1\n");
    ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Wallace\n");
  }


  // ---
  // suite
  // ---

  CPPUNIT_TEST_SUITE(TestVoting);
  CPPUNIT_TEST(test_read_first);
  CPPUNIT_TEST(test_read_first_1);
  CPPUNIT_TEST(test_read_first_2);
  CPPUNIT_TEST(test_read_first_3);
  CPPUNIT_TEST(test_read);
  CPPUNIT_TEST(test_read_1);
  CPPUNIT_TEST(test_read_2);
  CPPUNIT_TEST(test_read_3);
  CPPUNIT_TEST(test_read_4);
  CPPUNIT_TEST(test_score);
  CPPUNIT_TEST(test_score_1);
  CPPUNIT_TEST(test_score_2);
  CPPUNIT_TEST(test_check);
  CPPUNIT_TEST(test_check_1);
  CPPUNIT_TEST(test_check_2);
  CPPUNIT_TEST(test_rmLosers);
  CPPUNIT_TEST(test_rmLosers_1);
  CPPUNIT_TEST(test_rmLosers_2);
  CPPUNIT_TEST(test_print);
  CPPUNIT_TEST(test_print_1);
  CPPUNIT_TEST(test_print_2);
  CPPUNIT_TEST(test_solve);
  CPPUNIT_TEST(test_solve_1);
  CPPUNIT_TEST(test_solve_2);
  CPPUNIT_TEST_SUITE_END();
};


// ---
// main
// ---

int main () {
  ios_base::sync_with_stdio(false);
  cout << "TestCollatz.c++" << endl;

  CppUnit::TextTestRunner tr;
  tr.addTest(TestVoting::suite());
  tr.run();

  cout << "Done." << endl;
  return 0;
}
