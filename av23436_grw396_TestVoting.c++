/*
To test the program:
% ls /usr/include/cppunit/
...
TestFixture.h
...
% locate libcppunit.a
/usr/lib/libcppunit.a
% g++ -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting.c++.app -lcppunit -ldl
% valgrind TestVoting.c++.app >& TestVoting.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "Voting.h"

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {
 
    // -----
    // print
    // -----

    void test_print1 () {
        std::ostringstream w;
	std::vector<std::string> v = {"Akshay Vyas"};
        voting_write(w, v);
        CPPUNIT_ASSERT(w.str() == "Akshay Vyas\n");}


    void test_print2 () {
	std::ostringstream w;
	std::vector<std::string> v = {"Greg Wadley", "Akshay Vyas"};
        voting_write(w, v);
        CPPUNIT_ASSERT(w.str() == "Greg Wadley\nAkshay Vyas\n");}


    void test_print3 () {
        std::ostringstream w;
	std::vector<std::string> v = {"Glenn Downing", "Glenn Downing"};
        voting_write(w, v);
        CPPUNIT_ASSERT(w.str() == "Glenn Downing\nGlenn Downing\n");}
 void test_print4 () {
        std::ostringstream w;
	std::vector<std::string> v = {"Pikachu"};
        voting_write(w, v);
        CPPUNIT_ASSERT(w.str() == "Pikachu\n");}

 void test_print5 () {
        std::ostringstream w;
	std::vector<std::string> v = {"Cho-Gath"};
        voting_write(w, v);
        CPPUNIT_ASSERT(w.str() == "Cho-Gath\n");}

 void test_print6 () {
	std::ostringstream w;
	std::vector<std::string> v = {"Taric", "Lee Sin", "Riven"};
        voting_write(w, v);
        CPPUNIT_ASSERT(w.str() == "Taric\nLee Sin\nRiven\n");}
       

    // -----
    // solve
    // -----

  void test_solve_1 () {
        std::istringstream r("1\n\n3\nb\nG\nD\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "b\n");
	}
    
    void test_solve_2 () {
        std::istringstream r("1\n\n2\nJohnny\nTaylor nelson\n1 2\n2 1\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Johnny\nTaylor nelson\n");
    }
    
    void test_solve_3 () {
        std::istringstream r("1\n\n3\nAkshay\nGreg\nDowning\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Akshay\n");
    }
   void test_solve_4 () {
        std::istringstream r("1\n\n2\nJ\nT\n1 2\n2 1\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "J\nT\n");
 	}
  void test_solve_5 () {
        std::istringstream r("1\n\n2\np\nn\n1 2\n1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "p\n");
	}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_print1);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);
    CPPUNIT_TEST(test_print4);
    CPPUNIT_TEST(test_print5);
    CPPUNIT_TEST(test_print6);

    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);
    CPPUNIT_TEST(test_solve_5);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}

