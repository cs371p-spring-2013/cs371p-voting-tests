// ----------------------------
// TestVoting.c++
// Marcella Nguyen
// ----------------------------

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

// -----------
// TestVoting
// -----------

using namespace std;

struct TestVoting : CppUnit::TestFixture {

    // ----
    // read
    // ----
    void test_read_1 () {
        istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n\
                        1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        int j;
        string c[MAXCANDIDATES];
        vector<Ballots> v;

        string candidates[MAXCANDIDATES];
        candidates[1] = "John Doe";
        candidates[2] = "Jane Smith";
        candidates[3] = "Sirhan Sirhan";

        vector<Ballots> voters;
        Ballots q;
        q.push_back(1);
        q.push_back(2);
        q.push_back(3);
        voters.push_back(q);
        q.clear();
        q.push_back(2);
        q.push_back(1);
        q.push_back(3);
        voters.push_back(q);
        q.clear();
        q.push_back(2);
        q.push_back(3);
        q.push_back(1);
        voters.push_back(q);
        q.clear();
        q.push_back(1);
        q.push_back(2);
        q.push_back(3);
        voters.push_back(q);
        q.clear();
        q.push_back(3);
        q.push_back(1);
        q.push_back(2);
        voters.push_back(q);

        const bool b = voting_read(r, j, c, v);

        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(j == 3);
        for (int x = 1; x <= j; ++x) {
            CPPUNIT_ASSERT(c[x] == candidates[x]);
        }
        CPPUNIT_ASSERT(equal(v.begin(), v.end(), voters.begin()));}

    void test_read_2 () {
        istringstream r("4\nred\ngreen\norange\npurple\n1 2 3 4\n1 2 3 4\n2 1 3 4\n2 1 3 4\n3 4 1 2");
        int j;
        string c[MAXCANDIDATES];
        vector<Ballots> v;

        string candidates[MAXCANDIDATES];
        candidates[1] = "red";
        candidates[2] = "green";
        candidates[3] = "orange";
        candidates[4] = "purple";

        vector<Ballots> voters;
        Ballots q;
        q.push_back(1);
        q.push_back(2);
        q.push_back(3);
        q.push_back(4);
        voters.push_back(q);
        q.clear();
        q.push_back(1);
        q.push_back(2);
        q.push_back(3);
        q.push_back(4);
        voters.push_back(q);
        q.clear();
        q.push_back(2);
        q.push_back(1);
        q.push_back(3);
        q.push_back(4);
        voters.push_back(q);
        q.clear();
        q.push_back(2);
        q.push_back(1);
        q.push_back(3);
        q.push_back(4);
        voters.push_back(q);
        q.clear();
        q.push_back(3);
        q.push_back(4);
        q.push_back(1);
        q.push_back(2);
        voters.push_back(q);

        const bool b = voting_read(r, j, c, v);

        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(j == 4);
        for (int x = 1; x <= j; ++x) {
            CPPUNIT_ASSERT(c[x] == candidates[x]);
        }
        CPPUNIT_ASSERT(equal(v.begin(), v.end(), voters.begin()));}

    void test_read_3 () {
        istringstream r("2\nPrivate Pigeon\nHelpful Frog\n1 2 \n2 1 \n1 2 \n2 1 \n1 2 \n1 2 \n1 2 \n1 2 \n2 1 \n2 1");
        int j;
        string c[MAXCANDIDATES];
        vector<Ballots> v;

        string candidates[MAXCANDIDATES];
        candidates[1] = "Private Pigeon";
        candidates[2] = "Helpful Frog";

        vector<Ballots> voters;
        Ballots q;
        q.push_back(1);
        q.push_back(2);
        voters.push_back(q);
        q.clear();
        q.push_back(2);
        q.push_back(1);
        voters.push_back(q);
        q.clear();
        q.push_back(1);
        q.push_back(2);
        voters.push_back(q);
        q.clear();
        q.push_back(2);
        q.push_back(1);
        voters.push_back(q);
        q.clear();
        q.push_back(1);
        q.push_back(2);
        voters.push_back(q);
        q.clear();
        q.push_back(1);
        q.push_back(2);
        voters.push_back(q);
        q.clear();
        q.push_back(1);
        q.push_back(2);
        voters.push_back(q);
        q.clear();
        q.push_back(1);
        q.push_back(2);
        voters.push_back(q);
        q.clear();
        q.push_back(2);
        q.push_back(1);
        voters.push_back(q);
        q.clear();
        q.push_back(2);
        q.push_back(1);
        voters.push_back(q);

        const bool b = voting_read(r, j, c, v);

        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(j == 2);
        for (int x = 1; x <= j; ++x) {
            CPPUNIT_ASSERT(c[x] == candidates[x]);
        }
        CPPUNIT_ASSERT(equal(v.begin(), v.end(), voters.begin()));}

    // ----
    // eval
    // ----
    void test_eval_1 () {
        int j = 3;
        string c[MAXCANDIDATES];
        vector<Ballots> v;
        vector<string> winners;

        c[1] = "John Doe";
        c[2] = "Jane Smith";
        c[3] = "Sirhan Sirhan";

        Ballots q;
        q.push_back(1);
        q.push_back(2);
        q.push_back(3);
        v.push_back(q);
        q.clear();
        q.push_back(2);
        q.push_back(1);
        q.push_back(3);
        v.push_back(q);
        q.clear();
        q.push_back(2);
        q.push_back(3);
        q.push_back(1);
        v.push_back(q);
        q.clear();
        q.push_back(1);
        q.push_back(2);
        q.push_back(3);
        v.push_back(q);
        q.clear();
        q.push_back(3);
        q.push_back(1);
        q.push_back(2);
        v.push_back(q);
      
        voting_eval(j, c, v, winners);

        vector<string> win;
        win.push_back("John Doe");

        CPPUNIT_ASSERT(equal(winners.begin(), winners.end(), win.begin()));}

    void test_eval_2 () {
        int j = 2;
        string c[MAXCANDIDATES];
        vector<Ballots> v;
        vector<string> winners;

        c[1] = "Private Pigeon";
        c[2] = "Helpful Frog";

        Ballots q;
        q.push_back(1);
        q.push_back(2);
        v.push_back(q);
        q.clear();
        q.push_back(2);
        q.push_back(1);
        v.push_back(q);
        q.clear();
        q.push_back(1);
        q.push_back(2);
        v.push_back(q);
        q.clear();
        q.push_back(2);
        q.push_back(1);
        v.push_back(q);
        q.clear();
        q.push_back(1);
        q.push_back(2);
        v.push_back(q);
        q.clear();
        q.push_back(1);
        q.push_back(2);
        v.push_back(q);
        q.clear();
        q.push_back(1);
        q.push_back(2);
        v.push_back(q);
        q.clear();
        q.push_back(1);
        q.push_back(2);
        v.push_back(q);
        q.clear();
        q.push_back(2);
        q.push_back(1);
        v.push_back(q);
        q.clear();
        q.push_back(2);
        q.push_back(1);
        v.push_back(q);
      
        voting_eval(j, c, v, winners);

        vector<string> win;
        win.push_back("Private Pigeon");

        CPPUNIT_ASSERT(equal(winners.begin(), winners.end(), win.begin()));}

    void test_eval_3 () {
        int j = 3;
        string c[MAXCANDIDATES];
        vector<Ballots> v;
        vector<string> winners;

        c[1] = "John Doe";
        c[2] = "Jane Smith";
        c[3] = "Sirhan Sirhan";

        Ballots q;
        q.push_back(1);
        q.push_back(2);
        q.push_back(3);
        v.push_back(q);
        q.clear();
        q.push_back(2);
        q.push_back(1);
        q.push_back(3);
        v.push_back(q);
        q.clear();
        q.push_back(2);
        q.push_back(3);
        q.push_back(1);
        v.push_back(q);
        q.clear();
        q.push_back(1);
        q.push_back(2);
        q.push_back(3);
        v.push_back(q);
        q.clear();
        q.push_back(3);
        q.push_back(1);
        q.push_back(2);
        v.push_back(q);
        q.clear();
        q.push_back(3);
        q.push_back(2);
        q.push_back(1);
        v.push_back(q);

        voting_eval(j, c, v, winners);

        vector<string> win;
        win.push_back("John Doe");
        win.push_back("Jane Smith");
        win.push_back("Sirhan Sirhan");

        CPPUNIT_ASSERT(equal(winners.begin(), winners.end(), win.begin()));}

    // -----
    // print
    // -----
    void test_print_1 () {
        ostringstream w;
        int i = 0;
        vector<string> winners;
        winners.push_back("John Doe");

        voting_print(w, i, winners);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}

    void test_print_2 () {
        ostringstream w;
        int i = 0;
        vector<string> winners;
        winners.push_back("John Doe");
        winners.push_back("Jane Smith");
        winners.push_back("Sirhan Sirhan");

        voting_print(w, i, winners);
        CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");}

    void test_print_3 () {
        ostringstream w;
        int i = 1;
        vector<string> winners;
        winners.push_back("John Doe");

        voting_print(w, i, winners);

        --i;
        winners.clear();
        winners.push_back("John Doe");
        winners.push_back("Jane Smith");
        winners.push_back("Sirhan Sirhan"); 

        voting_print(w, i, winners);
        CPPUNIT_ASSERT(w.str() == "John Doe\n\nJohn Doe\nJane Smith\nSirhan Sirhan\n");}

    // -----
    // solve
    // -----
    void test_solve_1 () {
        istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}

    void test_solve_2 () {
        istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n1 2 3\n1 3 2");
        ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}

    void test_solve_3 () {
        istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n3 2 1");
        ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");}

    void test_solve_4 () {
        istringstream r("4\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n1 2 3\n1 3 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n3 2 1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n4\nred\ngreen\norange\npurple\n1 2 3 4\n1 2 3 4\n2 1 3 4\n2 1 3 4\n3 4 1 2\n");
        ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n\nJohn Doe\nJane Smith\nSirhan Sirhan\n\nJohn Doe\n\nred\n");}

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
    CPPUNIT_TEST(test_solve_4);

    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
//    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}


