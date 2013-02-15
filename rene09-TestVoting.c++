// --------
// includes
// --------

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"

#include "Voting.h"

// ----------
// TestVoting
// ----------

struct TestVoting : CppUnit::TestFixture {
	// ------
	// nCases
	// ------

	void test_nCases_1() {
		std::istringstream r("1\n");
		int i;
		voting_nCases(r, i);
		CPPUNIT_ASSERT(i == 1);
	}

	void test_nCases_2() {
		std::istringstream r("2\n");
		int i;
		voting_nCases(r, i);
		CPPUNIT_ASSERT(i == 2);
	}

	void test_nCases_3() {
		std::istringstream r("3\n");
		int i;
		voting_nCases(r, i);
		CPPUNIT_ASSERT(i == 3);
	}

	// -----
	// nCand
	// -----

	void test_nCand_1() {
		std::istringstream r("1\n");
		int i;
		voting_nCand(r, i);
		CPPUNIT_ASSERT(i == 1);
	}

	void test_nCand_2() {
		std::istringstream r("2\n");
		int i;
		voting_nCand(r, i);
		CPPUNIT_ASSERT(i == 2);
	}

	void test_nCand_3() {
		std::istringstream r("3\n");
		int i;
		voting_nCand(r, i);
		CPPUNIT_ASSERT(i == 3);
	}
	
	// ----
	// Cand
	// ----
	
	void test_Cand_1() {
		std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\n");
		std::vector<std::string> c(3);
		int n = 3;
		voting_Cand(r, c, n);
		CPPUNIT_ASSERT(c.at(0) == "John Doe");
		CPPUNIT_ASSERT(c.at(1) == "Jane Smith");
		CPPUNIT_ASSERT(c.at(2) == "Sirhan Sirhan");
	}
	
	void test_Cand_2() {
		std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\nJane Doe\n");
		std::vector<std::string> c(4);
		int n = 4;
		voting_Cand(r, c, n);
		CPPUNIT_ASSERT(c.at(1) == "Jane Smith");
		CPPUNIT_ASSERT(c.at(2) == "Sirhan Sirhan");
		CPPUNIT_ASSERT(c.at(3) == "Jane Doe");
	}
	
	void test_Cand_3() {
		std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\nJane Doe\nMichael Fox\n");
		std::vector<std::string> c(5);
		int n = 5;
		voting_Cand(r, c, n);
		CPPUNIT_ASSERT(c.at(0) == "John Doe");
		CPPUNIT_ASSERT(c.at(2) == "Sirhan Sirhan");
		CPPUNIT_ASSERT(c.at(4) == "Michael Fox");
	}

	// -------
	// Ballots
	// -------

	void test_Ballots_1() {
		std::istringstream r("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
		std::vector<std::vector<int> > b(3);
		int n = 3;
		voting_Ballots(r, b, n);
		CPPUNIT_ASSERT(b[0][0] == 0);
		CPPUNIT_ASSERT(b[1][1] == 0);
		CPPUNIT_ASSERT(b[2][2] == 0);
	}

	void test_Ballots_2() {
		std::istringstream r("1 2 3 4\n2 1 3 4\n3 2 1 4\n4 2 3 1\n");
		std::vector<std::vector<int> > b(3);
		int n = 4;;
		voting_Ballots(r, b, 4);
		CPPUNIT_ASSERT(b[0][1] == 1);
		CPPUNIT_ASSERT(b[1][2] == 1);
		CPPUNIT_ASSERT(b[2][3] == 2);
	}

	void test_Ballots_3() {
		std::istringstream r("5 4 3 2 1\n5 3 4 1 2\n5 2 4 3 1\n5 1 4 3 2\n");
		std::vector<std::vector<int> > b(3);
		int n = 5;
		voting_Ballots(r, b, 5);
		CPPUNIT_ASSERT(b[0][0] == 4);
		CPPUNIT_ASSERT(b[1][1] == 2);
		CPPUNIT_ASSERT(b[2][2] == 3);
	}
	
	// ---------
	// votesLeft
	// ---------
	
	void test_votesLeft_1() {
		std::vector<int> v;
		const bool b = voting_votesLeft(v);
		CPPUNIT_ASSERT(b == true);
	}
	
	void test_votesLeft_2() {
		std::vector<int> v(5, 1);
		const bool b = voting_votesLeft(v);
		CPPUNIT_ASSERT(b == true);
	}
	
	void test_votesLeft_3() {
		int i[] = {0, 1, 1, 0, 2};
		std::vector<int> v(i, i + sizeof(i)/sizeof(int));
		const bool b = voting_votesLeft(v);
		CPPUNIT_ASSERT(b == false);
	}

	// --------
	// tabulate
	// --------
	
	void test_tabulate_1() {
		int i[] = {0, 1, 1, 0, 2};
		std::vector<int> b(i, i + sizeof(i)/sizeof(int));
		std::vector<int> w;
		voting_tabulate(b, w, 3, false);
		CPPUNIT_ASSERT(w.size() == 2);
	}
	
	void test_tabulate_2() {
		int i[] = {1, 1, 1, 1, 1};
		std::vector<int> b(i, i + sizeof(i)/sizeof(int));
		std::vector<int> w;
		voting_tabulate(b, w, 3, false);
		CPPUNIT_ASSERT(w.size() == 1);
	}
	
	void test_tabulate_3() {
		int i[] = {0, 1, 2, 3};
		std::vector<int> b(i, i + sizeof(i)/sizeof(int));
		std::vector<int> w;
		voting_tabulate(b, w, 4, false);
		CPPUNIT_ASSERT(w.size() == 4);
	}
	
	// -------
	// compare
	// -------

	void test_compare_1() {
		std::pair<int, int> i(0, 1);
		std::pair<int, int> j(1, 2);
		const bool b = voting_compare(i, j);
		CPPUNIT_ASSERT(b == true);
	}
	
	void test_compare_2() {
		std::pair<int, int> i(0, 2);
		std::pair<int, int> j(1, 1);
		const bool b = voting_compare(i, j);
		CPPUNIT_ASSERT(b == false);
	}
	
	void test_compare_3() {
		std::pair<int, int> i(0, 0);
		std::pair<int, int> j(1, 3);
		const bool b = voting_compare(i, j);
		CPPUNIT_ASSERT(b == true);
	}
	
	// -------
	// discard
	// -------
	
	void test_discard_1() {
		int i1[] = {0, 1, 1, 0, 2};
		int i2[] = {1, 0, 2, 1, 0};
		int i3[] = {2, 2, 0, 2, 1};
		std::vector<int> b1(i1, i1 + sizeof(i1)/sizeof(int));
		std::vector<int> b2(i2, i2 + sizeof(i2)/sizeof(int));
		std::vector<int> b3(i3, i3 + sizeof(i3)/sizeof(int));
		std::vector<std::vector<int> > b;
		b.push_back(b1);
		b.push_back(b2);
		b.push_back(b3);
		voting_discard(b);
		CPPUNIT_ASSERT(b[0][4] == 0);
	}
	
	void test_discard_2() {
		int i1[] = {3, 3, 1, 0, 0};
		int i2[] = {1, 4, 0, 2, 2};
		int i3[] = {2, 1, 2, 3, 4};
		int i4[] = {0, 2, 4, 1, 1};
		int i5[] = {4, 0, 3, 4, 3};
		std::vector<int> b1(i1, i1 + sizeof(i1)/sizeof(int));
		std::vector<int> b2(i2, i2 + sizeof(i2)/sizeof(int));
		std::vector<int> b3(i3, i3 + sizeof(i3)/sizeof(int));
		std::vector<int> b4(i4, i4 + sizeof(i4)/sizeof(int));
		std::vector<int> b5(i5, i5 + sizeof(i5)/sizeof(int));
		std::vector<std::vector<int> > b;
		b.push_back(b1);
		b.push_back(b2);
		b.push_back(b3);
		b.push_back(b4);
		b.push_back(b5);
		voting_discard(b);
		CPPUNIT_ASSERT(b[0][2] == 0);
	}
	
	void test_discard_3() {
		int i1[] = {3, 2, 3, 0, 0};
		int i2[] = {1, 1, 0, 2, 2};
		int i3[] = {2, 0, 2, 3, 3};
		int i4[] = {0, 3, 1, 1, 1};
		std::vector<int> b1(i1, i1 + sizeof(i1)/sizeof(int));
		std::vector<int> b2(i2, i2 + sizeof(i2)/sizeof(int));
		std::vector<int> b3(i3, i3 + sizeof(i3)/sizeof(int));
		std::vector<int> b4(i4, i4 + sizeof(i4)/sizeof(int));
		std::vector<std::vector<int> > b;
		b.push_back(b1);
		b.push_back(b2);
		b.push_back(b3);
		b.push_back(b4);
		voting_discard(b);
		CPPUNIT_ASSERT(b[0][1] == 1);
	}
	
	// ----------
	// getWinners
	// ----------
	
	void test_getWinners_1() {
		int i1[] = {0, 1, 1, 0, 2};
		int i2[] = {1, 0, 2, 1, 0};
		int i3[] = {2, 2, 0, 2, 1};
		std::vector<int> b1(i1, i1 + sizeof(i1)/sizeof(int));
		std::vector<int> b2(i2, i2 + sizeof(i2)/sizeof(int));
		std::vector<int> b3(i3, i3 + sizeof(i3)/sizeof(int));
		std::vector<std::vector<int> > b;
		b.push_back(b1);
		b.push_back(b2);
		b.push_back(b3);
		std::vector<int> w;
		voting_getWinners(b, w, 2);
		CPPUNIT_ASSERT(w.size() == 1);
	}
	
	void test_getWinners_2() {
		int i1[] = {0, 1};
		int i2[] = {1, 0};
		std::vector<int> b1(i1, i1 + sizeof(i1)/sizeof(int));
		std::vector<int> b2(i2, i2 + sizeof(i2)/sizeof(int));
		std::vector<std::vector<int> > b;
		b.push_back(b1);
		b.push_back(b2);
		std::vector<int> w;
		voting_getWinners(b, w, 2);
		CPPUNIT_ASSERT(w.size() == 2);
	}
	
	void test_getWinners_3() {
		int i1[] = {3, 3, 3, 3, 3};
		int i2[] = {1, 4, 0, 2, 2};
		int i3[] = {2, 1, 2, 0, 4};
		int i4[] = {0, 2, 4, 1, 1};
		int i5[] = {4, 0, 1, 4, 0};
		std::vector<int> b1(i1, i1 + sizeof(i1)/sizeof(int));
		std::vector<int> b2(i2, i2 + sizeof(i2)/sizeof(int));
		std::vector<int> b3(i3, i3 + sizeof(i3)/sizeof(int));
		std::vector<int> b4(i4, i4 + sizeof(i4)/sizeof(int));
		std::vector<int> b5(i5, i5 + sizeof(i5)/sizeof(int));
		std::vector<std::vector<int> > b;
		b.push_back(b1);
		b.push_back(b2);
		b.push_back(b3);
		b.push_back(b4);
		b.push_back(b5);
		std::vector<int> w;
		voting_getWinners(b, w, 5);
		CPPUNIT_ASSERT(w.size() == 1);
	}
	
	// -----
	// print
	// -----
	
	void test_print_1() {
		std::ostringstream w;
		int i[] = {0, 1};
		std::string s[] = {"John Doe", "Jane Smith"};
		std::vector<int> g(i, i + sizeof(i)/sizeof(int));
		std::vector<std::string> c(s, s + sizeof(s)/sizeof(std::string));
		voting_print(w, g, c);
		CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\n\n");
	}
	
	void test_print_2() {
		std::ostringstream w;
		int i[] = {0, 2};
		std::string s[]= {"John Doe", "Jane Smith", "Michael Fox"};
		std::vector<int> g(i, i + sizeof(i)/sizeof(int));
		std::vector<std::string> c(s, s + sizeof(s)/sizeof(std::string));
		voting_print(w, g, c);
		CPPUNIT_ASSERT(w.str() == "John Doe\nMichael Fox\n\n");
	}
	
	void test_print_3() {
		std::ostringstream w;
		int i[] = {1, 2};
		std::string s[]= {"John Doe", "Jane Smith", "Michael Fox"};
		std::vector<int> g(i, i + sizeof(i)/sizeof(int));
		std::vector<std::string> c(s, s + sizeof(s)/sizeof(std::string));
		voting_print(w, g, c);
		CPPUNIT_ASSERT(w.str() == "Jane Smith\nMichael Fox\n\n");
	}
	
	// ------
	// result
	// ------
	
	void test_result_1() {
		std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\
				\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n");
		std::ostringstream w;
		voting_result(r, w);
		CPPUNIT_ASSERT(w.str() == "John Doe");
	}

	void test_result_2() {
		std::istringstream r("2\n\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\
				\nJane Doe\n1 2 3 4\n2 1 3 4\n3 2 1 4\n4 2 3 1\n\n2\n\
				John Doe\nJane Smith\n1 2\n2 1\n");
		std::ostringstream w;
		voting_result(r, w);
		CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\nJane Doe\n\nJohn Doe\nJane Smith");
	}

	void test_result_3() {
		std::istringstream r("3\n\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\
				\nJane Doe\n1 2 3 4\n1 2 3 4\n1 2 3 4\n1 2 4 3\n\n2\n\
				John Doe\nJane Smith\n2 1\n2 1\n2 1\n5\nJohn Doe\nJane Smith\
				\nSirhan Sirhan\nJane Doe\nMichael Fox\n5 4 3 2 1\n\
				5 3 4 1 2\n5 2 4 3 1\n5 1 4 3 2\n");
		std::ostringstream w;
		voting_result(r, w);
		CPPUNIT_ASSERT(w.str() == "John Doe\n\nJohn Doe\n\nMichael Fox");
	}

	CPPUNIT_TEST_SUITE(TestVoting);
	CPPUNIT_TEST(test_nCases_1);
	CPPUNIT_TEST(test_nCases_2);
	CPPUNIT_TEST(test_nCases_3);
	CPPUNIT_TEST(test_nCand_1);
	CPPUNIT_TEST(test_nCand_2);
	CPPUNIT_TEST(test_nCand_3);
	CPPUNIT_TEST(test_Cand_1);
	CPPUNIT_TEST(test_Cand_2);
	CPPUNIT_TEST(test_Cand_3);
	CPPUNIT_TEST(test_Ballots_1);
	CPPUNIT_TEST(test_Ballots_2);
	CPPUNIT_TEST(test_Ballots_3);
	CPPUNIT_TEST(test_votesLeft_1);
	CPPUNIT_TEST(test_votesLeft_2);
	CPPUNIT_TEST(test_votesLeft_3);
	CPPUNIT_TEST(test_tabulate_1);
	CPPUNIT_TEST(test_tabulate_2);
	CPPUNIT_TEST(test_tabulate_3);
	CPPUNIT_TEST(test_compare_1);
	CPPUNIT_TEST(test_compare_2);
	CPPUNIT_TEST(test_compare_3);
	CPPUNIT_TEST(test_discard_1);
	CPPUNIT_TEST(test_discard_2);
	CPPUNIT_TEST(test_discard_3);
	CPPUNIT_TEST(test_getWinners_1);
	CPPUNIT_TEST(test_getWinners_2);
	CPPUNIT_TEST(test_getWinners_3);
	CPPUNIT_TEST(test_print_1);
	CPPUNIT_TEST(test_print_2);
	CPPUNIT_TEST(test_print_3);
	CPPUNIT_TEST(test_result_1);
	CPPUNIT_TEST(test_result_2);
	//CPPUNIT_TEST(test_result_3);
	CPPUNIT_TEST_SUITE_END();
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
