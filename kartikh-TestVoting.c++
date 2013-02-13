// --------------------------------
// cs371p-voting/Testvoting.c++
// Copyright (C) 2013
// Kartik S. Hattangadi
// Nicolas Schakel
// --------------------------------

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>
#include <deque>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"
#include "Candidate.h"

using namespace std;

// -----------
// Testvoting
// -----------

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_1 () {
        stringstream r;
        r << "\n3\nCool Apple\nSweet Orange\nSmooth Pear\n1 3 2\n3 1 2\n2 1 3\n";
        std::vector<Candidate> candidates;
        int total_votes = 0;
        const bool b = voting_read(r, candidates, total_votes);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(candidates.size() ==    3);
        CPPUNIT_ASSERT(candidates[0].name == "Cool Apple");
        CPPUNIT_ASSERT(candidates[1].name == "Sweet Orange");
        CPPUNIT_ASSERT(candidates[2].name == "Smooth Pear");
        CPPUNIT_ASSERT(candidates[0].ballots[0][0] == 0);
        CPPUNIT_ASSERT(candidates[0].ballots[0][2] == 1);
        CPPUNIT_ASSERT(candidates[1].ballots[0][0] == 1);
        CPPUNIT_ASSERT(candidates[1].ballots[0][1] == 0);
        CPPUNIT_ASSERT(candidates[1].ballots[0][2] == 2);
        CPPUNIT_ASSERT(candidates[2].ballots[0][0] == 2);
        CPPUNIT_ASSERT(candidates[2].ballots[0][1] == 0);
        CPPUNIT_ASSERT(candidates[2].ballots[0][2] == 1);
        CPPUNIT_ASSERT(total_votes ==   3);}

    void test_read_2() {
        std::istringstream r("\n1\nLonely Eggplant\n1\n");
        std::vector<Candidate> candidates;
        int total_votes = 0;
        const bool b = voting_read(r, candidates, total_votes);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(candidates.size() ==    1);
        CPPUNIT_ASSERT(candidates[0].name == "Lonely Eggplant");
        CPPUNIT_ASSERT(candidates[0].ballots[0][0] == 0);
        CPPUNIT_ASSERT(total_votes ==   1);}
    
    void test_read_3 () {
        std::istringstream r("\n2\nMushy Mushroom\nPrickly Broccoli\n1 2\n1 2\n");
        std::vector<Candidate> candidates;
        int total_votes = 0;
        const bool b = voting_read(r, candidates, total_votes);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(candidates[0].name == "Mushy Mushroom");
        CPPUNIT_ASSERT(candidates[1].name == "Prickly Broccoli");
        CPPUNIT_ASSERT(candidates[0].ballots[0][0] == 0);
        CPPUNIT_ASSERT(candidates[0].ballots[0][1] == 1);
        CPPUNIT_ASSERT(candidates[0].ballots[1][0] == 0);
        CPPUNIT_ASSERT(candidates[0].ballots[1][1] == 1);
        CPPUNIT_ASSERT(candidates[1].ballots.empty());
        CPPUNIT_ASSERT(total_votes == 2);}

    // ----
    // eval
    // ----

    void test_eval_1 () {
        std::vector<Candidate> candidates;
        Candidate c;
        c.name = "Cool Beans";
        c.votes = 1;
        c.running = true;
        std::deque<int> ballot;
        ballot.push_back(0);
        c.ballots.push_back(ballot);
        candidates.push_back(c);
        int total_votes = 1;
        const std::string v = voting_eval(candidates, total_votes);
        CPPUNIT_ASSERT(v == "Cool Beans\n");}

    void test_eval_2 () {
        std::vector<Candidate> candidates;
        Candidate c;
        c.name = "Big Apple";
        c.votes = 1;
        c.running = true;
        std::deque<int> ballot;
        ballot.push_back(0);
        ballot.push_back(1);
        c.ballots.push_back(ballot);
        Candidate c1;
        candidates.push_back(c);
        c1.name = "Red Orange";
        c1.running = true;
        c1.votes = 1;
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(0);
        c1.ballots.push_back(ballot);
        candidates.push_back(c1);
        int total_votes = 2;
        const std::string v = voting_eval(candidates, total_votes);
        CPPUNIT_ASSERT(v == "Big Apple\nRed Orange\n");}

    void test_eval_3 () {
        std::vector<Candidate> candidates;
        Candidate c;
        c.name = "Nice Peach";
        c.votes = 2;
        c.running = true;
        std::deque<int> ballot;
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        c.ballots.push_back(ballot);
        ballot.clear();
        ballot.push_back(0);
        ballot.push_back(2);
        ballot.push_back(1);
        c.ballots.push_back(ballot);
        candidates.push_back(c);
        Candidate c1;
        c1.name = "Funny Beet";
        c1.votes = 2;
        c1.running = true;
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(0);
        ballot.push_back(2);
        c1.ballots.push_back(ballot);
        ballot.clear();
        ballot.push_back(1);
        ballot.push_back(2);
        ballot.push_back(0);
        c1.ballots.push_back(ballot);
        candidates.push_back(c1);
        Candidate c2;
        c2.name = "Envious Onion";
        c2.votes = 1;
        c2.running = true;
        ballot.clear();
        ballot.push_back(2);
        ballot.push_back(0);
        ballot.push_back(1);
        c2.ballots.push_back(ballot);
        candidates.push_back(c2);
        int total_votes = 5;
        const std::string v = voting_eval(candidates, total_votes);
        CPPUNIT_ASSERT(v == "Nice Peach\n");}

    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        voting_print(w, "Tiny Grape\n");
        CPPUNIT_ASSERT(w.str() == "Tiny Grape\n\n");}
    
    void test_print_2 () {
        std::ostringstream w;
        voting_print(w, "Juicy Garlic\nMagnificent Celery\n");
        CPPUNIT_ASSERT(w.str() == "Juicy Garlic\nMagnificent Celery\n\n");}
    
    void test_print_3 () {
        std::ostringstream w;
        voting_print(w, "Smelly Ginger\nSmoky Cauliflower\nGross Brusselsprouts\n");
        CPPUNIT_ASSERT(w.str() == "Smelly Ginger\nSmoky Cauliflower\nGross Brusselsprouts\n\n");}

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}

    void test_solve_2 () {
        std::istringstream r("1\n\n1\nLonely Fruit\n1\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() =="Lonely Fruit\n");}

    void test_solve_3 () {
        std::istringstream r("2\n\n2\nAaron Austin\nBetty Boston\n2 1\n1 2\n\n1\nCool Cam\n1\n1\n1\n1\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Aaron Austin\nBetty Boston\n\nCool Cam\n");}


    // ---------
    // candidate
    // ---------

    void test_candidate_1 () {
      Candidate c;
      CPPUNIT_ASSERT(c.running == false);
      CPPUNIT_ASSERT(c.votes == 0);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_candidate_1);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestCollatz.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
