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
	
	// -----------
    // voting_read
    // -----------
    
    void test_read_1 () {
		Case *test_case = new Case();
		vector<int> test_vector;
        std::istringstream r("\n\n1\nname");
        voting_read(r, test_case);
        CPPUNIT_ASSERT((*test_case).get_count() == 1);
        CPPUNIT_ASSERT((*test_case).get_candidate(0) == "name");
        test_vector.clear();
        delete test_case;
	}
    
    void test_read_2 () {
		Case *test_case = new Case();
		vector<int> test_vector;
        std::istringstream r("\n\n2\nname1\nname2\n1 2");
        test_vector.push_back(1);
        test_vector.push_back(2);
        voting_read(r, test_case);
        CPPUNIT_ASSERT((*test_case).get_count() == 2);
        CPPUNIT_ASSERT((*test_case).get_candidate(0) == "name1");
        CPPUNIT_ASSERT((*test_case).get_candidate(1) == "name2");
        CPPUNIT_ASSERT((*test_case).get_ballot_count() == 1);
        CPPUNIT_ASSERT((*test_case).get_ballot(0) == test_vector);
        test_vector.clear();
        delete test_case;
	}
	
	void test_read_3 () {
		Case *test_case = new Case();
		vector<int> test_vector;
        std::istringstream r("\n\n2\nname1\nname2\n1 2");
        test_vector.push_back(1);
        test_vector.push_back(2);
        voting_read(r, test_case);
        CPPUNIT_ASSERT((*test_case).get_count() == 2);
        CPPUNIT_ASSERT((*test_case).get_candidate(0) == "name1");
        CPPUNIT_ASSERT((*test_case).get_candidate(1) == "name2");
        CPPUNIT_ASSERT((*test_case).get_ballot_count() == 1);
        CPPUNIT_ASSERT((*test_case).get_ballot(0) == test_vector);
        test_vector.clear();
        delete test_case;
	}
	
	// ------------
    // voting_print
	// ------------
	
	void test_print_1 () {
		vector<std::string> test_vector;
        std::ostringstream w;
		voting_print(w, test_vector);
        CPPUNIT_ASSERT(w.str() == "");
        test_vector.clear();
	}
	
	void test_print_2 () {
		vector<std::string> test_vector;
		test_vector.push_back("");
		test_vector.push_back("");
        std::ostringstream w;
		voting_print(w, test_vector);
        CPPUNIT_ASSERT(w.str() == "\n\n");
        test_vector.clear();
	}
	
	void test_print_3 () {
		vector<std::string> test_vector;
		test_vector.push_back("test3");
		test_vector.push_back("");
        std::ostringstream w;
		voting_print(w, test_vector);
        CPPUNIT_ASSERT(w.str() == "test3\n\n");
        test_vector.clear();
	}
	
	// -----------
    // voting_eval
	// -----------
	
	void test_eval_1 () {
		Case *test_case = new Case();
		vector<std::string> test_vector, compare_vector;
        std::ostringstream w;
        std::istringstream r("\n\n2\nname1\nname2\n1 2");
        voting_read(r, test_case);        
		test_vector = voting_eval(w, test_case);
		compare_vector.push_back("name1");
        CPPUNIT_ASSERT(test_vector == compare_vector);
        test_vector.clear();
        compare_vector.clear();
        delete test_case;
	}
	
	void test_eval_2 () {
		Case *test_case = new Case();
		vector<std::string> test_vector, compare_vector;
        std::ostringstream w;
        std::istringstream r("\n\n0");
        voting_read(r, test_case);
        test_vector = voting_eval(w, test_case);
        CPPUNIT_ASSERT(test_vector.size() == 0);
        test_vector.clear();
        compare_vector.clear();
        delete test_case;
	}
	
	void test_eval_3 () {
		Case *test_case = new Case();
		vector<std::string> test_vector, compare_vector;
        std::ostringstream w;
        std::istringstream r("\n\n3\nname1\nname2\nname3\n1 2 3\n2 1 3\n3 1 2");
        voting_read(r, test_case);
		test_vector = voting_eval(w, test_case);
		compare_vector.push_back("name1");
		compare_vector.push_back("name2");
		compare_vector.push_back("name3");
        CPPUNIT_ASSERT(test_vector == compare_vector);
        test_vector.clear();
        compare_vector.clear();
        delete test_case;
	}
	
	
	// ------------
    // voting_solve
	// ------------
	
	void test_solve_1 () {
        std::ostringstream w;
        std::istringstream r("0");
        voting_solve(r,w);
        CPPUNIT_ASSERT(w.str() == "");
    }
    
    void test_solve_2 () {
        std::ostringstream w;
        std::istringstream r("1\n\n1\nname1");
        voting_solve(r,w);
        CPPUNIT_ASSERT(w.str() == "name1\n");
    }
    
    void test_solve_3 () {
        std::ostringstream w;
        std::istringstream r("2\n\n1\nname1\n\n2\nname1\nname2\n1 2\n2 1");
        voting_solve(r,w);
        CPPUNIT_ASSERT(w.str() == "name1\n\nname1\nname2\n");
    }
        
     
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
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
