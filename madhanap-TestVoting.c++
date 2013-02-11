// --------------------------------
// projects/voting/TestVoting.c++
// Copyright (C) 2013
// Philip Jacobs
// Manoj Dhanapal
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting.c++.app -lcppunit -ldl
    % valgrind TestVoting.c++.app >& TestVoting.c++.out
*/

// --------
// includes
// --------

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read () {
        vector<string> cand;
        vector<vector<int> > votes;
        std::istringstream r("3\nIntel\nAMD\nTexas Instruments\n1 2 3\n2 3 1\n3 1 2\n");
        const bool retval = voting_read(r, cand, votes);
        CPPUNIT_ASSERT(retval);
        CPPUNIT_ASSERT(cand.size()     == 3);
        CPPUNIT_ASSERT(cand[0]         == "Intel");
        CPPUNIT_ASSERT(cand[1]         == "AMD");
        CPPUNIT_ASSERT(cand[2]         == "Texas Instruments");
        CPPUNIT_ASSERT(votes.size()    == 3);
        CPPUNIT_ASSERT(votes[0].size() == 3);
        CPPUNIT_ASSERT(votes[1].size() == 3);
        CPPUNIT_ASSERT(votes[2].size() == 3);}

    void test_read_2 () {
        vector<string> cand;
        vector<vector<int> > votes;
        std::istringstream r("1\nname\n1\n1\n1\n1\n1\n1\n1\n1\n");
        const bool retval = voting_read(r, cand, votes);
        CPPUNIT_ASSERT(retval);
        CPPUNIT_ASSERT(cand.size()     == 1);
        CPPUNIT_ASSERT(cand[0]         == "name");
        CPPUNIT_ASSERT(votes.size()    == 8);
        CPPUNIT_ASSERT(votes[0].size() == 1);}

    void test_read_3 () {
        vector<string> cand;
        vector<vector<int> > votes;
        std::istringstream r("2\nHarlem\nShake\n1 2\n2 1\n");
        const bool retval = voting_read(r, cand, votes);
        CPPUNIT_ASSERT(retval);
        CPPUNIT_ASSERT(cand.size()     == 2);
        CPPUNIT_ASSERT(cand[0]         == "Harlem");
        CPPUNIT_ASSERT(cand[1]         == "Shake");
        CPPUNIT_ASSERT(votes.size()    == 2);
        CPPUNIT_ASSERT(votes[0].size() == 2);
        CPPUNIT_ASSERT(votes[1].size() == 2);}


    // ----
    // read_initial
    // ----

    void test_read_initial() {
        int i;
        std::istringstream r("2\n");
        const bool retval = voting_read_initial(r, i);
        CPPUNIT_ASSERT(retval);
        CPPUNIT_ASSERT(i == 2);}

    void test_read_initial_2() {
        int i;
        std::istringstream r("3\n");
        const bool retval = voting_read_initial(r, i);
        CPPUNIT_ASSERT(retval);
        CPPUNIT_ASSERT(i == 3);}

    void test_read_initial_3() {
        int i;
        std::istringstream r("7\n");
        const bool retval = voting_read_initial(r, i);
        CPPUNIT_ASSERT(retval);
        CPPUNIT_ASSERT(i == 7);}

    // ----
    // read_cand
    // ----
    void test_read_cand() {
        vector<string> cand;
        std::istringstream r("2\nimdb\nRotten Tomatoes\n");
        const bool retval = voting_read_cand(r, cand);
        CPPUNIT_ASSERT(retval);
        CPPUNIT_ASSERT(cand[0] == "imdb");
        CPPUNIT_ASSERT(cand[1] == "Rotten Tomatoes");
        CPPUNIT_ASSERT(cand.size() == 2);}

    void test_read_cand_2() {
        vector<string> cand;
        std::istringstream r("3\na\nb\nc\n");
        const bool retval = voting_read_cand(r, cand);
        CPPUNIT_ASSERT(retval);
        CPPUNIT_ASSERT(cand[0] == "a");
        CPPUNIT_ASSERT(cand[1] == "b");
        CPPUNIT_ASSERT(cand[2] == "c");
        CPPUNIT_ASSERT(cand.size() == 3);}

    void test_read_cand_3() {
        vector<string> cand;
        std::istringstream r("3\na\naaa\naaaaa\n");
        const bool retval = voting_read_cand(r, cand);
        CPPUNIT_ASSERT(retval);
        CPPUNIT_ASSERT(cand[0] == "a");
        CPPUNIT_ASSERT(cand[1] == "aaa");
        CPPUNIT_ASSERT(cand[2] == "aaaaa");
        CPPUNIT_ASSERT(cand.size() == 3);}

    // ----
    // read_votes
    // ----
    void test_read_votes () {
        vector<vector<int> > votes;
        std::istringstream r("1 2 3\n2 3 1\n3 1 2\n");
        const bool retval = voting_read_votes(r, 3, votes);
        CPPUNIT_ASSERT(retval);
        CPPUNIT_ASSERT(votes.size()    == 3);
        CPPUNIT_ASSERT(votes[0].size() == 3);
        CPPUNIT_ASSERT(votes[1].size() == 3);
        CPPUNIT_ASSERT(votes[2].size() == 3);}

    void test_read_votes_2 () {
        vector<vector<int> > votes;
        std::istringstream r("1\n1\n1\n1\n1\n1\n1\n");
        const bool retval = voting_read_votes(r, 1, votes);
        CPPUNIT_ASSERT(retval);
        CPPUNIT_ASSERT(votes.size()    == 7);
        CPPUNIT_ASSERT(votes[0].size() == 1);
        CPPUNIT_ASSERT(votes[1].size() == 1);
        CPPUNIT_ASSERT(votes[6].size() == 1);}

    void test_read_votes_3 () {
        vector<vector<int> > votes;
        std::istringstream r("1 2\n2 1\n");
        const bool retval = voting_read_votes(r, 2, votes);
        CPPUNIT_ASSERT(retval);
        CPPUNIT_ASSERT(votes.size()    == 2);
        CPPUNIT_ASSERT(votes[0].size() == 2);
        CPPUNIT_ASSERT(votes[1].size() == 2);}


    // ----
    // eval
    // ----

    void test_eval_1 () {
        vector<string> cands;
        vector<vector<int> > votes;
        cands.push_back("Intel");
        cands.push_back("AMD");
        votes.resize(2);
        votes[0].push_back(1), votes[0].push_back(2);
        votes[1].push_back(1), votes[1].push_back(2);
        vector<string> out;
        voting_eval(cands, votes, out);
        CPPUNIT_ASSERT(out.size() == 1);
        CPPUNIT_ASSERT(out[0] == "Intel");}

    void test_eval_2 () {
        vector<string> cands;
        vector<vector<int> > votes;
        cands.push_back("BLEH");
        votes.resize(7);
        for(int i = 0; i<7; i++)
		votes[i].push_back(1); 
        vector<string> out;
        voting_eval(cands, votes, out);
        CPPUNIT_ASSERT(out.size() == 1);
        CPPUNIT_ASSERT(out[0] == "BLEH");}

    void test_eval_3 () {
        vector<string> cands;
        vector<vector<int> > votes;
        cands.push_back("Bored");
        cands.push_back("Right");
        cands.push_back("Now");
        cands.push_back("Like");
        cands.push_back("Srsly");
        votes.resize(5);
        votes[0].push_back(1), votes[0].push_back(2),votes[0].push_back(3),votes[0].push_back(4),votes[0].push_back(5);
        votes[1].push_back(2), votes[1].push_back(1),votes[1].push_back(3),votes[1].push_back(4),votes[1].push_back(5);
        votes[2].push_back(3), votes[2].push_back(2),votes[2].push_back(1),votes[2].push_back(4),votes[2].push_back(5);
        votes[3].push_back(4), votes[3].push_back(2),votes[3].push_back(3),votes[3].push_back(1),votes[3].push_back(5);
        votes[4].push_back(5), votes[4].push_back(2),votes[4].push_back(3),votes[4].push_back(4),votes[4].push_back(1);
        vector<string> out;
        voting_eval(cands, votes, out);
        CPPUNIT_ASSERT(out.size() == 5);
        CPPUNIT_ASSERT(out[0] == "Bored");
        CPPUNIT_ASSERT(out[1] == "Right");
        CPPUNIT_ASSERT(out[2] == "Now");
        CPPUNIT_ASSERT(out[3] == "Like");
        CPPUNIT_ASSERT(out[4] == "Srsly");}
    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        vector<string> cands;
        cands.push_back("Hello");
        cands.push_back("World");
        voting_print(w, cands);
        CPPUNIT_ASSERT(w.str() == "Hello\nWorld\n");}

    void test_print_2 () {
        std::ostringstream w;
        vector<string> cands;
        cands.push_back("This Is A Test");
        voting_print(w, cands);
        CPPUNIT_ASSERT(w.str() == "This Is A Test\n");}

    void test_print_3 () {
        std::ostringstream w;
        vector<string> cands;
        cands.push_back("Hello");
        cands.push_back("World");
        voting_print(w, cands);
        CPPUNIT_ASSERT(w.str() == "Hello\nWorld\n");}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1\n\n3\nIntel\nAMD\nTexas Instruments\n1 2 3\n2 3 1\n3 1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Intel\nAMD\nTexas Instruments\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_initial);
    CPPUNIT_TEST(test_read_initial_2);
    CPPUNIT_TEST(test_read_initial_3);
    CPPUNIT_TEST(test_read_cand);
    CPPUNIT_TEST(test_read_cand_2);
    CPPUNIT_TEST(test_read_cand_3);
    CPPUNIT_TEST(test_read_votes);
    CPPUNIT_TEST(test_read_votes_2);
    CPPUNIT_TEST(test_read_votes_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    //ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}

