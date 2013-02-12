#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

// -----------
// TestCollatz
// -----------

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_1 () {
        std::istringstream r("2\nBob\nJoe\n1 2\n2 1\n");
        Election e;
        voting_read(r, e);
        CPPUNIT_ASSERT(e.numCandidates == 2);
        CPPUNIT_ASSERT(e.totalBallots  == 2);
        CPPUNIT_ASSERT(e.candidates[0].name == "Bob");
        CPPUNIT_ASSERT(e.candidates[1].name == "Joe");
        CPPUNIT_ASSERT(e.allBallots[0].preference[0] == 1);
        CPPUNIT_ASSERT(e.allBallots[0].preference[1] == 2);
        CPPUNIT_ASSERT(e.allBallots[1].preference[0] == 2);
        CPPUNIT_ASSERT(e.allBallots[1].preference[1] == 1);
    }

    void test_read_2 () {
        std::istringstream r("3\nBob\nJoe\nFrank\n1 2 3\n2 1 3\n3 2 1\n3 1 2\n");
        Election e;
        voting_read(r, e);
        CPPUNIT_ASSERT(e.numCandidates == 3);
        CPPUNIT_ASSERT(e.totalBallots  == 4);
        CPPUNIT_ASSERT(e.candidates[0].name == "Bob");
        CPPUNIT_ASSERT(e.candidates[1].name == "Joe");
        CPPUNIT_ASSERT(e.candidates[2].name == "Frank");
        CPPUNIT_ASSERT(e.allBallots[0].preference[0] == 1);
        CPPUNIT_ASSERT(e.allBallots[0].preference[1] == 2);
        CPPUNIT_ASSERT(e.allBallots[0].preference[2] == 3);
        CPPUNIT_ASSERT(e.allBallots[1].preference[0] == 2);
        CPPUNIT_ASSERT(e.allBallots[1].preference[1] == 1);
        CPPUNIT_ASSERT(e.allBallots[1].preference[2] == 3);
        CPPUNIT_ASSERT(e.allBallots[2].preference[0] == 3);
        CPPUNIT_ASSERT(e.allBallots[2].preference[1] == 2);
        CPPUNIT_ASSERT(e.allBallots[2].preference[2] == 1);
        CPPUNIT_ASSERT(e.allBallots[3].preference[0] == 3);
        CPPUNIT_ASSERT(e.allBallots[3].preference[1] == 1);
        CPPUNIT_ASSERT(e.allBallots[3].preference[2] == 2);
    }

    void test_read_3 () {
        std::istringstream r("1\nBob\n1\n");
        Election e;
        voting_read(r, e);
        CPPUNIT_ASSERT(e.numCandidates == 1);
        CPPUNIT_ASSERT(e.totalBallots  == 1);
        CPPUNIT_ASSERT(e.candidates[0].name == "Bob");
        CPPUNIT_ASSERT(e.allBallots[0].preference[0] == 1);
    }

    void test_read_4 () {
        std::istringstream r("2\nBob\nJoe\n1 2\n2 1\n");
        Election e;
        voting_read(r, e);
        CPPUNIT_ASSERT(e.numCandidates == 2);
        CPPUNIT_ASSERT(e.totalBallots  == 2);
        CPPUNIT_ASSERT(e.candidates[0].name == "Bob");
        CPPUNIT_ASSERT(e.candidates[1].name == "Joe");
        CPPUNIT_ASSERT(e.allBallots[0].preference[0] == 1);
        CPPUNIT_ASSERT(e.allBallots[0].preference[1] == 2);
        CPPUNIT_ASSERT(e.allBallots[1].preference[0] == 2);
        CPPUNIT_ASSERT(e.allBallots[1].preference[1] == 1);
    }

    void test_read_5 () {
        std::istringstream r("3\nBob\nJoe\nFrank\n1 2 3\n2 1 3\n");
        Election e;
        voting_read(r, e);
        CPPUNIT_ASSERT(e.numCandidates == 3);
        CPPUNIT_ASSERT(e.totalBallots  == 2);
        CPPUNIT_ASSERT(e.candidates[0].name == "Bob");
        CPPUNIT_ASSERT(e.candidates[1].name == "Joe");
        CPPUNIT_ASSERT(e.candidates[2].name == "Frank");
        CPPUNIT_ASSERT(e.allBallots[0].preference[0] == 1);
        CPPUNIT_ASSERT(e.allBallots[0].preference[1] == 2);
        CPPUNIT_ASSERT(e.allBallots[0].preference[2] == 3);
        CPPUNIT_ASSERT(e.allBallots[1].preference[0] == 2);
        CPPUNIT_ASSERT(e.allBallots[1].preference[1] == 1);
        CPPUNIT_ASSERT(e.allBallots[1].preference[2] == 3);
    }

    void test_read_6 () {
        std::istringstream r("2\nBob\nJoe\n1 2\n2 1\n1 2\n");
        Election e;
        voting_read(r, e);
        CPPUNIT_ASSERT(e.numCandidates == 2);
        CPPUNIT_ASSERT(e.totalBallots  == 3);
        CPPUNIT_ASSERT(e.candidates[0].name == "Bob");
        CPPUNIT_ASSERT(e.candidates[1].name == "Joe");
        CPPUNIT_ASSERT(e.allBallots[0].preference[0] == 1);
        CPPUNIT_ASSERT(e.allBallots[0].preference[1] == 2);
        CPPUNIT_ASSERT(e.allBallots[1].preference[0] == 2);
        CPPUNIT_ASSERT(e.allBallots[1].preference[1] == 1);
        CPPUNIT_ASSERT(e.allBallots[2].preference[0] == 1);
        CPPUNIT_ASSERT(e.allBallots[2].preference[1] == 2);
    }

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::ostringstream w;
        Election e;
        //RIG ELECTION
        e.numCandidates = 1;
        e.totalBallots = 1;

        Candidate c;
        c.name = "Bob";
        c.voteCount = 0;
        c.loser = false;

        e.candidates.push_back(c);
        Ballot b;
        b.preference.push_back(1);
        e.allBallots.push_back(b);

        voting_solve(w, e);
        CPPUNIT_ASSERT(w.str() == "Bob\n");
    }


    void test_solve_2 () {
        std::ostringstream w;
        Election e;
        //RIG ELECTION
        e.numCandidates = 2;
        e.totalBallots = 2;

        Candidate c;
        c.name = "Bob";
        c.voteCount = 0;
        c.loser = false;

        e.candidates.push_back(c);
        Ballot b;
        b.preference.push_back(1);
        b.preference.push_back(2);
        e.allBallots.push_back(b);

        Candidate d;
        d.name = "Joe";
        d.voteCount = 0;
        d.loser = false;

        e.candidates.push_back(d);
        Ballot b2;
        b2.preference.push_back(2);
        b2.preference.push_back(1);
        e.allBallots.push_back(b2);

        voting_solve(w, e);
        CPPUNIT_ASSERT(w.str() == "Bob\nJoe\n");
    }


    void test_solve_3 () {
        std::ostringstream w;
        Election e;
        //RIG ELECTION
        e.numCandidates = 2;
        e.totalBallots = 2;

        Candidate c;
        c.name = "Bob";
        c.voteCount = 0;
        c.loser = false;

        e.candidates.push_back(c);
        Ballot b;
        b.preference.push_back(1);
        b.preference.push_back(2);
        e.allBallots.push_back(b);

        Candidate d;
        d.name = "Joe";
        d.voteCount = 0;
        d.loser = false;

        e.candidates.push_back(d);
        Ballot b2;
        b2.preference.push_back(1);
        b2.preference.push_back(2);
        e.allBallots.push_back(b2);

        voting_solve(w, e);
        CPPUNIT_ASSERT(w.str() == "Bob\n");
    }

    void test_solve_4 () {
        std::ostringstream w;
        Election e;
        //RIG ELECTION
        e.numCandidates = 3;
        e.totalBallots = 3;

        Candidate bob;
        bob.name = "Bob";
        bob.voteCount = 0;
        bob.loser = false;
        e.candidates.push_back(bob);

        Candidate joe;
        joe.name = "Joe";
        joe.voteCount = 0;
        joe.loser = false;
        e.candidates.push_back(joe);

        Candidate ron;
        ron.name = "Ron";
        ron.voteCount = 0;
        ron.loser = false;
        e.candidates.push_back(ron);

        Ballot b;
        b.preference.push_back(1);
        b.preference.push_back(2);
        b.preference.push_back(3);
        e.allBallots.push_back(b);

        Ballot b2;
        b2.preference.push_back(2);
        b2.preference.push_back(3);
        b2.preference.push_back(1);
        e.allBallots.push_back(b2);

        Ballot b3;
        b3.preference.push_back(2);
        b3.preference.push_back(1);
        b3.preference.push_back(3);
        e.allBallots.push_back(b3);


        voting_solve(w, e);
        CPPUNIT_ASSERT(w.str() == "Joe\n");
    }

    void test_solve_5 () {
        std::ostringstream w;
        Election e;
        //RIG ELECTION
        e.numCandidates = 3;
        e.totalBallots = 2;

        Candidate bob;
        bob.name = "Bob Dole";
        bob.voteCount = 0;
        bob.loser = false;
        e.candidates.push_back(bob);

        Candidate joe;
        joe.name = "Joe Biden";
        joe.voteCount = 0;
        joe.loser = false;
        e.candidates.push_back(joe);

        Candidate ron;
        ron.name = "Ron Paul";
        ron.voteCount = 0;
        ron.loser = false;
        e.candidates.push_back(ron);

        Ballot b;
        b.preference.push_back(1);
        b.preference.push_back(2);
        b.preference.push_back(3);
        e.allBallots.push_back(b);

        Ballot b2;
        b2.preference.push_back(2);
        b2.preference.push_back(3);
        b2.preference.push_back(1);
        e.allBallots.push_back(b2);

        voting_solve(w, e);
        CPPUNIT_ASSERT(w.str() == "Bob Dole\nJoe Biden\n");
    }

    void test_solve_6 () {
        std::ostringstream w;
        Election e;
        //RIG ELECTION
        e.numCandidates = 4;
        e.totalBallots = 1;

        Candidate obama;
        obama.name = "Barack Obama";
        obama.voteCount = 0;
        obama.loser = false;
        e.candidates.push_back(obama);

        Candidate romney;
        romney.name = "Mitt Romney";
        romney.voteCount = 0;
        romney.loser = false;
        e.candidates.push_back(romney);

        Candidate johnson;
        johnson.name = "Gary Johnson";
        johnson.voteCount = 0;
        johnson.loser = false;
        e.candidates.push_back(johnson);

        Candidate stein;
        stein.name = "Jill Stein";
        stein.voteCount = 0;
        stein.loser = false;
        e.candidates.push_back(stein);

        Ballot b;
        b.preference.push_back(1);
        b.preference.push_back(2);
        b.preference.push_back(3);
        b.preference.push_back(4);
        e.allBallots.push_back(b);

        voting_solve(w, e);
        CPPUNIT_ASSERT(w.str() == "Barack Obama\n");
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
    CPPUNIT_TEST(test_read_5);
    CPPUNIT_TEST(test_read_6);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);
    CPPUNIT_TEST(test_solve_5);
    CPPUNIT_TEST(test_solve_6);
    CPPUNIT_TEST_SUITE_END();};

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
    return 0;}
