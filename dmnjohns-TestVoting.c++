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

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

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

    void test_read_1 () {
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n"
                             "1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        std::vector<Candidate> c;
        const bool b = voting_read(r, c);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(c.size() == 3);
        CPPUNIT_ASSERT(c[0].name == "John Doe");
        CPPUNIT_ASSERT(c[0].voteCount == 2);
        CPPUNIT_ASSERT(c[0].valid == true);}
        
    void test_read_2 () {
        std::istringstream r("1\nJack Smith\n1");
        std::vector<Candidate> c;
        const bool b = voting_read(r, c);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(c.size() == 1);
        CPPUNIT_ASSERT(c[0].name == "Jack Smith");
        CPPUNIT_ASSERT(c[0].voteCount == 1);
        CPPUNIT_ASSERT(c[0].valid == true);}
        
    void test_read_3 () {
        std::istringstream r("3\nAdam Bob\nCarol Dog\nElaine Fast\n"
                             "1 2 3\n2 1 3\n3 2 1");
        std::vector<Candidate> c;
        const bool b = voting_read(r, c);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(c.size() == 3);
        CPPUNIT_ASSERT(c[0].name == "Adam Bob");
        CPPUNIT_ASSERT(c[0].voteCount == 1);
        CPPUNIT_ASSERT(c[0].valid == true);
        CPPUNIT_ASSERT(c[1].name == "Carol Dog");
        CPPUNIT_ASSERT(c[1].voteCount == 1);
        CPPUNIT_ASSERT(c[1].valid == true);
        CPPUNIT_ASSERT(c[2].name == "Elaine Fast");
        CPPUNIT_ASSERT(c[2].voteCount == 1);
        CPPUNIT_ASSERT(c[2].valid == true);}
        
    /* TODO: incomplete, sorry, not enough time before I had to go back to class
    // case of letters in ballots
    void test_read_2 () {
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n"
                             "a b c\nd e f\nh i j\nl m n\no p q");
        std::vector<Candidate> c;
        const bool b = voting_read(r, c);
        CPPUNIT_ASSERT(b == false);}
    
    // TODO: incomplete
    // case of multiple of same number in ballots
    void test_read_3 () {
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n"
                             "1 1 1\n");
        std::vector<Candidate> c;
        const bool b = voting_read(r, c);
        CPPUNIT_ASSERT(b == false);}
        
    // TODO: incomplete
    // case of invalid vote in ballot
    void test_read_4 () {
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n"
                             "4 1 1\n");
        std::vector<Candidate> c;
        const bool b = voting_read(r, c);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(c.size() == 3);
        CPPUNIT_ASSERT(c[0].name == "John Doe");
        CPPUNIT_ASSERT(c[0].voteCount == 2);
        CPPUNIT_ASSERT(c[0].valid == true);}*/

    // ----
    // eval
    // ----

    void test_eval_1 () {
        std::vector<Candidate> c;
        std::vector<std::string> b, r;
        b.push_back("1 2 3");
        b.push_back("1 2 3");
        Candidate d = {b, "John Doe", 2, true};
        c.push_back(d);
        b.clear();
        b.push_back("2 1 3");
        b.push_back("2 3 1");
        d = {b, "Jane Smith", 2, true};
        c.push_back(d);
        b.clear();
        b.push_back("3 1 2");
        d = {b, "Sirhan Sirhan", 1, true};
        c.push_back(d);
        r = voting_eval(c);
        CPPUNIT_ASSERT(r.size() == 1);
        CPPUNIT_ASSERT(r[0] == "John Doe");}
        
    void test_eval_2 () {
        std::vector<Candidate> c;
        std::vector<std::string> b, r;
        b.push_back("1");
        Candidate d = {b, "Jack Smith", 1, true};
        c.push_back(d);
        b.clear();
        r = voting_eval(c);
        CPPUNIT_ASSERT(r.size() == 1);
        CPPUNIT_ASSERT(r[0] == "Jack Smith");}
        
    void test_eval_3 () {
        std::vector<Candidate> c;
        std::vector<std::string> b, r;
        b.push_back("1 2 3");
        Candidate d = {b, "Adam Bob", 1, true};
        c.push_back(d);
        b.clear();
        b.push_back("2 1 3");
        d = {b, "Carol Dog", 1, true};
        c.push_back(d);
        b.clear();
        b.push_back("3 2 1");
        d = {b, "Elaine Fast", 1, true};
        c.push_back(d);
        r = voting_eval(c);
        CPPUNIT_ASSERT(r.size() == 3);
        CPPUNIT_ASSERT(r[0] == "Adam Bob");
        CPPUNIT_ASSERT(r[1] == "Carol Dog");
        CPPUNIT_ASSERT(r[2] == "Elaine Fast");}

    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        std::vector<std::string> n;
        n.push_back("John Doe");
        voting_print(w, n);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}
        
    void test_print_2 () {
        std::ostringstream w;
        std::vector<std::string> n;
        n.push_back("123456789");
        voting_print(w, n);
        CPPUNIT_ASSERT(w.str() == "123456789\n");}
        
    void test_print_3 () {
        std::ostringstream w;
        std::vector<std::string> n;
        n.push_back("");
        voting_print(w, n);
        CPPUNIT_ASSERT(w.str() == "\n");}

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n"
                             "1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}
        
    void test_solve_2 () {
        std::istringstream r("1\n\n1\nJack Smith\n"
                             "1");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Jack Smith\n");}
        
    void test_solve_3 () {
        std::istringstream r("2\n\n1\nJack Smith\n"
                             "1\n\n"
                             "3\nAdam Bob\nCarol Dog\nElaine Fast\n"
                             "1 2 3\n2 1 3\n3 2 1");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Jack Smith\n\n"
                                  "Adam Bob\nCarol Dog\nElaine Fast\n");}
    
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    //CPPUNIT_TEST(test_read_4);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    // ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
