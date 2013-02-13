// Cppunit test program for unit testing

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"

#include "Voting.h"

//----------------------------------------------------------------------
// Test values that are going to be reused
int v1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
const std::vector<int> testValues(v1, v1 + sizeof(v1) / sizeof(v1[0]));

struct TestVoting: CppUnit::TestFixture {

    void testReadNumber_01() {
      std::istringstream r("1\n\n1\nJohn Doe\n11");
      int n;
      const bool b = voting::readNumber(r, n);
      CPPUNIT_ASSERT(b == true);
      CPPUNIT_ASSERT(n == 1);
    }

    void testReadNumber_02() {
      std::istringstream r("123456789");
      int n;
      const bool b = voting::readNumber(r, n);
      CPPUNIT_ASSERT(b == true);
      CPPUNIT_ASSERT(n == 123456789);
    }

    void testReadNumber_03() {
      std::istringstream r("123");
      int n;
      const bool b = voting::readNumber(r, n);
      CPPUNIT_ASSERT(b == true);
      CPPUNIT_ASSERT(n == 123);
    }

    void testReadCandidateName_01() {
      std::istringstream r("Teddy Roosevelt");
      std::string s;
      const bool b = voting::readCandidateName(r, s);
      CPPUNIT_ASSERT(b == true);
      CPPUNIT_ASSERT(s == "Teddy Roosevelt");
    }

    void testReadCandidateName_02() {
      std::istringstream r("Teddy Roosevelt\nBanana");
      std::string s;
      const bool b = voting::readCandidateName(r, s);
      CPPUNIT_ASSERT(b == true);
      CPPUNIT_ASSERT(s == "Teddy Roosevelt");
      CPPUNIT_ASSERT(s != "Banana");
    }

    void testReadCandidateName_03() {
      std::istringstream r("Teddy Roosevelt\nLeonard Church\nSterling Archer");
      std::string s1, s2, s3;
      const bool b1 = voting::readCandidateName(r, s1);
      const bool b2 = voting::readCandidateName(r, s2);
      const bool b3 = voting::readCandidateName(r, s3);
      CPPUNIT_ASSERT(b1 == true);
      CPPUNIT_ASSERT(b2 == true);
      CPPUNIT_ASSERT(b3 == true);
      CPPUNIT_ASSERT(s1 == "Teddy Roosevelt");
      CPPUNIT_ASSERT(s2 == "Leonard Church");
      CPPUNIT_ASSERT(s3 == "Sterling Archer");
    }

    //---------------------------------------------------------
    // ballot tests

    void testBallotConstructor_01() {
      ballot b(testValues, 1);

      int test = b.getCurrentVote();

      CPPUNIT_ASSERT(test == 1);
    }

    void testBallotConstructor_02() {
      ballot b(testValues, 10);

      int test[10];

      test[0] = b.getCurrentVote();
      for (int i = 1; i < 10; ++i)
        test[i] = b.getNextVote();

      CPPUNIT_ASSERT(test[0] == 1);
      CPPUNIT_ASSERT(test[1] == 2);
      CPPUNIT_ASSERT(test[2] == 3);
      CPPUNIT_ASSERT(test[3] == 4);
      CPPUNIT_ASSERT(test[4] == 5);
      CPPUNIT_ASSERT(test[5] == 6);
      CPPUNIT_ASSERT(test[6] == 7);
      CPPUNIT_ASSERT(test[7] == 8);
      CPPUNIT_ASSERT(test[8] == 9);
      CPPUNIT_ASSERT(test[9] == 10);
    }

    void testGetCurrentVote_01() {
      ballot testBallot(testValues, 10);

      int iTest = testBallot.getCurrentVote();
      CPPUNIT_ASSERT(iTest == 1);
    }

    void testGetCurrentVote_02() {
      ballot testBallot(testValues, 10);

      testBallot.getNextVote();
      int iTest = testBallot.getCurrentVote();
      CPPUNIT_ASSERT(iTest == 2);
    }

    void testGetCurrentVote_03() {
      ballot testBallot(testValues, 10);

      for (int i = 0; i < 5; ++i)
        testBallot.getNextVote();
      int iTest = testBallot.getCurrentVote();
      CPPUNIT_ASSERT(iTest == 6);
    }

    void testGetCurrentVote_04() {
      ballot* testBallot = new ballot(testValues, 10);

      for (int i = 0; i < 5; ++i)
        testBallot->getNextVote();
      int iTest = testBallot->getCurrentVote();
      delete testBallot;
      CPPUNIT_ASSERT(iTest == 6);
    }

    void testGetNextVote_01() {
      ballot testBallot(testValues, 10);

      int n1 = testBallot.getNextVote();
      CPPUNIT_ASSERT(n1 == 2);
    }

    void testGetNextVote_02() {
      ballot testBallot(testValues, 10);

      int n[9];
      for (int i = 0; i < 9; ++i)
        n[i] = testBallot.getNextVote();
      CPPUNIT_ASSERT(n[0] == 2);
      CPPUNIT_ASSERT(n[1] == 3);
      CPPUNIT_ASSERT(n[2] == 4);
      CPPUNIT_ASSERT(n[3] == 5);
      CPPUNIT_ASSERT(n[4] == 6);
      CPPUNIT_ASSERT(n[5] == 7);
      CPPUNIT_ASSERT(n[6] == 8);
      CPPUNIT_ASSERT(n[7] == 9);
      CPPUNIT_ASSERT(n[8] == 10);
    }

    void testGetNextVote_03() {
      ballot* testBallot = new ballot(testValues, 10);

      int n[9];
      for (int i = 0; i < 9; ++i)
        n[i] = testBallot->getNextVote();
      delete testBallot;
      CPPUNIT_ASSERT(n[0] == 2);
      CPPUNIT_ASSERT(n[1] == 3);
      CPPUNIT_ASSERT(n[2] == 4);
      CPPUNIT_ASSERT(n[3] == 5);
      CPPUNIT_ASSERT(n[4] == 6);
      CPPUNIT_ASSERT(n[5] == 7);
      CPPUNIT_ASSERT(n[6] == 8);
      CPPUNIT_ASSERT(n[7] == 9);
      CPPUNIT_ASSERT(n[8] == 10);
    }

    //---------------------------------------------------------
    // candidate tests

    void testGetName_01() {
      candidate c("Bob Marley");
      std::string s = c.getName();

      CPPUNIT_ASSERT(s == "Bob Marley");
      CPPUNIT_ASSERT(s != "Jingle Bells");
    }

    void testGetName_02() {
      candidate c("Jingle Bells");
      std::string s = c.getName();

      CPPUNIT_ASSERT(s != "Bob Marley");
      CPPUNIT_ASSERT(s == "Jingle Bells");
    }

    void testGetName_03() {
      candidate* c = new candidate("Bob Marley");
      std::string s = c->getName();
      delete c;

      CPPUNIT_ASSERT(s == "Bob Marley");
      CPPUNIT_ASSERT(s != "Jingle Bells");
    }

    void testGetNumVotes_01() {
      candidate c("Dancing Pirate");

      int n = c.getNumVotes();

      CPPUNIT_ASSERT(n == 0);
    }

    void testGetNumVotes_02() {
      candidate c("Dancing Pirate");

      c.addVote(1);
      int n = c.getNumVotes();

      CPPUNIT_ASSERT(n == 1);
    }

    void testGetNumVotes_03() {
      candidate c("Dancing Pirate");

      for (int i = 0; i < 100; ++i)
        c.addVote(i);
      int n = c.getNumVotes();

      CPPUNIT_ASSERT(n == 100);
    }

    void testGetStillRunning_01() {
      candidate c("Emo Squid");

      bool b = c.getStillRunning();
      CPPUNIT_ASSERT(b == true);
    }

    void testGetStillRunning_02() {
      candidate c("Emo Squid");

      c.dropOut();
      bool b = c.getStillRunning();
      CPPUNIT_ASSERT(b == false);
    }

    void testGetStillRunning_03() {
      candidate c("Emo Squid");

      c.dropOut();
      c.dropOut();
      bool b = c.getStillRunning();
      CPPUNIT_ASSERT(b == false);
    }

    void testAddVote_01() {
      candidate c("Fuzzy Wuzzy");

      c.addVote(1);
      int n = c.getNumVotes();
      CPPUNIT_ASSERT(n == 1);
    }

    void testAddVote_02() {
      candidate c("Fuzzy Wuzzy");

      c.addVote(1);
      c.addVote(2);
      int n = c.getNumVotes();
      CPPUNIT_ASSERT(n == 2);
    }

    void testAddVote_03() {
      candidate c("Fuzzy Wuzzy");

      for (int i = 0; i < 1000000; ++i)
        c.addVote(i);
      int n = c.getNumVotes();
      CPPUNIT_ASSERT(n == 1000000);
    }

    void testDropOut_01() {
      candidate c("Banana Republic");

      bool b = c.getStillRunning();
      c.dropOut();
      bool b2 = c.getStillRunning();

      CPPUNIT_ASSERT(b == true);
      CPPUNIT_ASSERT(b2 == false);
    }

    void testDropOut_02() {
      candidate c("Banana Republic");

      bool b = c.getStillRunning();
      c.dropOut();
      bool b2 = c.getStillRunning();
      c.dropOut();
      bool b3 = c.getStillRunning();

      CPPUNIT_ASSERT(b == true);
      CPPUNIT_ASSERT(b2 == false);
      CPPUNIT_ASSERT(b3 == false);
    }

    void testDropOut_03() {
      candidate c("Banana Republic");

      bool b = c.getStillRunning();
      for (int i = 0; i < 1000000; ++i)
        c.dropOut();
      bool b2 = c.getStillRunning();

      CPPUNIT_ASSERT(b == true);
      CPPUNIT_ASSERT(b2 == false);
    }

    //---------------------------------------------------------
    // Eval and solve

    void testEval_01() {
      candidate c("Teddy Roosevelt");
      ballot b(testValues, 1);

      candidate cvalues[] = {c};
      ballot bvalues[] = {b};

      std::vector<candidate> cv (cvalues, cvalues + sizeof(cvalues) / sizeof(cvalues[0]));
      std::vector<ballot> bv (bvalues, bvalues + sizeof(bvalues) / sizeof(bvalues[0]));

      std::string s = voting::eval(cv, bv);

      CPPUNIT_ASSERT(s == "Teddy Roosevelt");
    }

    void testEval_02() {
      candidate c1("General Disarray");
      candidate c2("Professor Chaos");
      ballot b(testValues, 2);

      candidate cvalues[] = {c1, c2};
      ballot bvalues[] = {b};

      std::vector<candidate> cv (cvalues, cvalues + sizeof(cvalues) / sizeof(cvalues[0]));
      std::vector<ballot> bv (bvalues, bvalues + sizeof(bvalues) / sizeof(bvalues[0]));

      std::string s = voting::eval(cv, bv);

      CPPUNIT_ASSERT(s == "General Disarray");
    }

    void testEval_03() {
      candidate c1("General Disarray");
      candidate c2("Professor Chaos");
      ballot b(testValues, 2);

      candidate cvalues[] = { c1, c2 };
      ballot bvalues[] = { b, b, b, b, b, b, b };

      std::vector<candidate> cv (cvalues, cvalues + sizeof(cvalues) / sizeof(cvalues[0]));
      std::vector<ballot> bv (bvalues, bvalues + sizeof(bvalues) / sizeof(bvalues[0]));

      std::string s = voting::eval(cv, bv);

      CPPUNIT_ASSERT(s == "General Disarray");
    }

    void testEval_04() {
      candidate c1("General Disarray");
      candidate c2("Professor Chaos");
      ballot b1(testValues, 2);

      int vvalues[] = { 2, 1 };

      const std::vector<int> values2 (vvalues, vvalues + sizeof(vvalues) / sizeof(vvalues[0]));
      ballot b2(values2, 2);

      candidate cvalues[] = { c1, c2 };
      ballot bvalues[] = { b1, b2, b2 };

      std::vector<candidate> cv (cvalues, cvalues + sizeof(cvalues) / sizeof(cvalues[0]));
      std::vector<ballot> bv (bvalues, bvalues + sizeof(bvalues) / sizeof(bvalues[0]));


      std::string s = voting::eval(cv, bv);

      CPPUNIT_ASSERT(s == "Professor Chaos");
    }

    // Tests a tie
    void testEval_05() {
      candidate c1("General Disarray");
      candidate c2("Professor Chaos");
      ballot b1(testValues, 2);

      int vvalues[] = { 2, 1 };

      const std::vector<int> values2 (vvalues, vvalues + sizeof(vvalues) / sizeof(vvalues[0]));
      ballot b2(values2, 2);

      candidate cvalues[] = { c1, c2 };
      ballot bvalues[] = { b1, b2 };

      std::vector<candidate> cv (cvalues, cvalues + sizeof(cvalues) / sizeof(cvalues[0]));
      std::vector<ballot> bv (bvalues, bvalues + sizeof(bvalues) / sizeof(bvalues[0]));

      std::string s = voting::eval(cv, bv);

      CPPUNIT_ASSERT(s == "General Disarray\nProfessor Chaos");
    }

    // Tests dropping losers
    void testEval_06() {
      candidate c1("General Disarray");
      candidate c2("Professor Chaos");
      candidate c3("Ninja Star");
      ballot b1(testValues, 3);

      int vvalues2[] = { 2, 3, 1 };
      int vvalues3[] = { 3, 2, 1 };

      const std::vector<int> values2 (vvalues2, vvalues2 + sizeof(vvalues2) / sizeof(vvalues2[0]));
      ballot b2(values2, 3);

      const std::vector<int> values3 (vvalues3, vvalues3 + sizeof(vvalues3) / sizeof(vvalues3[0]));
      ballot b3(values3, 3);

      candidate cvalues[] = { c1, c2, c3 };
      ballot bvalues[] = { b1, b2, b2, b3, b3 };

      std::vector<candidate> cv (cvalues, cvalues + sizeof(cvalues) / sizeof(cvalues[0]));
      std::vector<ballot> bv (bvalues, bvalues + sizeof(bvalues) / sizeof(bvalues[0]));

      std::string s = voting::eval(cv, bv);

      CPPUNIT_ASSERT(s == "Professor Chaos");
    }

    // Tests dropping losers
    void testEval_07() {
      candidate c1("General Disarray");
      candidate c2("Professor Chaos");
      candidate c3("Ninja Star");
      ballot b1(testValues, 3);

      int vvalues2[] = { 2, 3, 1 };
      int vvalues3[] = { 3, 2, 1 };

      const std::vector<int> values2 (vvalues2, vvalues2+ sizeof(vvalues2) / sizeof(vvalues2[0]));
      ballot b2(values2, 3);

      const std::vector<int> values3 (vvalues3, vvalues3 + sizeof(vvalues3) / sizeof(vvalues3[0]));
      ballot b3(values3, 3);

      candidate cvalues[] = { c1, c2, c3 };
      ballot bvalues[] = { b1, b1, b2, b3, b3 };

      std::vector<candidate> cv (cvalues, cvalues + sizeof(cvalues) / sizeof(cvalues[0]));
      std::vector<ballot> bv (bvalues, bvalues + sizeof(bvalues) / sizeof(bvalues[0]));

      std::string s = voting::eval(cv, bv);

      CPPUNIT_ASSERT(s == "Ninja Star");
    }

    void testSolve_01() {
      std::istringstream in("1\n1\nMajor Payne\n1");
      std::ostringstream out;

      voting::solve(in, out);
      CPPUNIT_ASSERT(out.str() == "Major Payne\n");
    }

    void testSolve_02() {
      std::istringstream in("1\n2\nWinner\nLoser\n1 2");
      std::ostringstream out;

      voting::solve(in, out);
      CPPUNIT_ASSERT(out.str() == "Winner\n");

    }

    void testSolve_03() {
      std::istringstream in("1\n2\nWinner\nLoser\n1 2\n1 2\n2 1");
      std::ostringstream out;

      voting::solve(in, out);
      CPPUNIT_ASSERT(out.str() == "Winner\n");
    }

    void testSolve_04() {
      std::istringstream in(
          "2\n2\nWinner\nLoser\n1 2\n1 2\n2 1\n\n2\nWinner\nLoser\n1 2");
      std::ostringstream out;

      voting::solve(in, out);
      CPPUNIT_ASSERT(out.str() == "Winner\n\nWinner\n");
    }

    //---------------------------------------------------------
    // testing suite
  CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(testReadNumber_01);
    CPPUNIT_TEST(testReadNumber_02);
    CPPUNIT_TEST(testReadNumber_03);

    CPPUNIT_TEST(testReadCandidateName_01);
    CPPUNIT_TEST(testReadCandidateName_02);
    CPPUNIT_TEST(testReadCandidateName_03);

    CPPUNIT_TEST(testBallotConstructor_01);
    CPPUNIT_TEST(testBallotConstructor_02);

    CPPUNIT_TEST(testGetCurrentVote_01);
    CPPUNIT_TEST(testGetCurrentVote_02);
    CPPUNIT_TEST(testGetCurrentVote_03);
    CPPUNIT_TEST(testGetCurrentVote_04);

    CPPUNIT_TEST(testGetNextVote_01);
    CPPUNIT_TEST(testGetNextVote_02);
    CPPUNIT_TEST(testGetNextVote_03);

    CPPUNIT_TEST(testGetName_01);
    CPPUNIT_TEST(testGetName_02);
    CPPUNIT_TEST(testGetName_03);

    CPPUNIT_TEST(testGetNumVotes_01);
    CPPUNIT_TEST(testGetNumVotes_02);
    CPPUNIT_TEST(testGetNumVotes_03);

    CPPUNIT_TEST(testGetStillRunning_01);
    CPPUNIT_TEST(testGetStillRunning_02);
    CPPUNIT_TEST(testGetStillRunning_03);

    CPPUNIT_TEST(testAddVote_01);
    CPPUNIT_TEST(testAddVote_02);
    CPPUNIT_TEST(testAddVote_03);

    CPPUNIT_TEST(testDropOut_01);
    CPPUNIT_TEST(testDropOut_02);
    CPPUNIT_TEST(testDropOut_03);

    CPPUNIT_TEST(testEval_01);
    CPPUNIT_TEST(testEval_02);
    CPPUNIT_TEST(testEval_03);
    CPPUNIT_TEST(testEval_04);
    CPPUNIT_TEST(testEval_05);
    CPPUNIT_TEST(testEval_06);
    CPPUNIT_TEST(testEval_07);

    CPPUNIT_TEST(testSolve_01);
    CPPUNIT_TEST(testSolve_02);
    CPPUNIT_TEST(testSolve_03);
    CPPUNIT_TEST(testSolve_04);

    CPPUNIT_TEST_SUITE_END()
    ;
};

int main() {
  using namespace std;
  ios_base::sync_with_stdio(false);
  cout << "TestVoting.c++" << endl;

  CppUnit::TextTestRunner tr;
  tr.addTest(TestVoting::suite());
  tr.run();

  cout << "Done." << endl;
  return 0;

}
