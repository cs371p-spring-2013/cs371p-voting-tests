#include <iostream>
#include <sstream>
#include <string>

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"

#include "Voting.h"

struct TestVoting : CppUnit::TestFixture {

	void test_read_ballots_1 () {
	
		std::istringstream b("1 2 3\n3 2 1\n1 2 3\n");
		vector<Ballot> list;
		int i;

		for(i = 0; i < list.size(); ++i){
			const bool a = voting_read_ballots(b, list, i);
			CPPUNIT_ASSERT(a == true);
			CPPUNIT_ASSERT(list.size() > 0);
		}
	}
	
	void test_read_ballots_2 () {
	
		std::istringstream r("1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1\n");

		vector<Ballot> list;
		int i;

		for(i = 0; i < list.size(); ++i){
			const bool a = voting_read_ballots(r, list, i);
			CPPUNIT_ASSERT(a == true);
			CPPUNIT_ASSERT(list.size() > 0);
		}
	}
	
	void test_read_ballots_3 () {
	
		std::istringstream r("1\n1\n1\n1\n");
		vector<Ballot> list;
		int i;

		for(i = 0; i < list.size(); ++i){
			const bool a = voting_read_ballots(r, list, i);
			CPPUNIT_ASSERT(a == false);
			CPPUNIT_ASSERT(list.size() > 0);
		}
	}
	
	void test_read_cand_1 () {
	
		std::istringstream r("Darth Vader\nJar Jar\nLuke Skywalker\n");
		Candidate cand[3];
		int i;
		for(i = 0; i < 3; ++i){
			const bool a = voting_read_candidates(r, cand[i]);
			CPPUNIT_ASSERT(a == true);

		}
	}
	
	void test_read_cand_2 () {
	
		std::istringstream r("Red\nGreen\nBlue\nOrange\n");
		Candidate cand[4];
		int i;
		for(i = 0; i < 4; ++i){
			const bool a = voting_read_candidates(r, cand[i]);
			CPPUNIT_ASSERT(a == true);

		}
	}
	
	void test_read_cand_3 () {
	
		std::istringstream r("Johnny Bravo\n");
		Candidate cand[1];
		int i;
		for(i = 0; i < 1; ++i){
			const bool a = voting_read_candidates(r, cand[i]);
			CPPUNIT_ASSERT(a == true);

		}
	}
	
	void test_eval_1 () {
	
		std::istringstream r("Darth Vader\nJar Jar\nLuke Skywalker\n");
		Candidate cand[3];
		std::istringstream b("1 2 3\n3 2 1\n1 2 3\n");
		vector<Ballot> list;
		int i;
		
		for (i=0;i<3;i++) {
			voting_read_candidates(r, cand[i]);
		}
		
		for(i = 0; i < list.size(); ++i){
			const bool c = voting_read_ballots(b, list, i);
			CPPUNIT_ASSERT(c == true);
		}
		voting_eval(cand, 3, list);

		

	}
	
	
	void test_eval_2 () {
	
		std::istringstream r("Red\nGreen\nBlue\nOrange\n");
		Candidate cand[4];
		std::istringstream b("1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1\n");
		vector<Ballot> list;
		int i;
		
		for (i=0;i<4;i++) {
			voting_read_candidates(r, cand[i]);
		}
		
		for(i = 0; i < list.size(); ++i){
			const bool c = voting_read_ballots(b, list, i);
			CPPUNIT_ASSERT(c == true);
		}
		voting_eval(cand, 4, list);	

	}
	
	void test_eval_3 () {
	
		std::istringstream r("Johnny Bravo\n");
		Candidate cand[4];
		std::istringstream b("1\n1\n1\n1\n");
		vector<Ballot> list;
		int i;
		
		for (i=0;i<4;i++) {
			voting_read_candidates(r, cand[i]);
		}
		
		for(i = 0; i < list.size(); ++i){
			const bool c = voting_read_ballots(b, list, i);
			CPPUNIT_ASSERT(c == true);
		}
		voting_eval(cand, 4, list);

		

	}
	
	void test_solve_1 () {
	
		std::istringstream r("Darth Vader\nJar Jar\nLuke Skywalker\n");
		std::istringstream b("1 2 3\n3 2 1\n1 2 3\n");
		std::ostringstream w ("Darth Vader\n");
		Candidate cand[3];
		vector<Ballot> list;
		int i;
		
		for (i=0;i<3;i++) {
			voting_read_candidates(r, cand[i]);
		}
		
		for(i = 0; i < list.size(); ++i){
			const bool c = voting_read_ballots(b, list, i);
			CPPUNIT_ASSERT(c == true);
		}
		voting_eval(cand, 3, list);
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "Darth Vader\n");
	}
	
	void test_solve_2 () {
	
		std::istringstream r("Red\nGreen\nBlue\nOrange\n");
		std::istringstream b("1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1\n");
		std::ostringstream w ("Red\nGreen\n");
		Candidate cand[4];
		vector<Ballot> list;
		int i;
		
		for (i=0;i<4;i++) {
			voting_read_candidates(r, cand[i]);
		}
		
		for(i = 0; i < list.size(); ++i){
			const bool c = voting_read_ballots(b, list, i);
			CPPUNIT_ASSERT(c == true);
		}
		voting_eval(cand, 4, list);
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "Red\nGreen\n");
	}
	
	void test_solve_3 () {
	
		std::istringstream r("Red\nGreen\nBlue\nOrange\n");
		std::istringstream b("1\n1\n1\n1\n");
		std::ostringstream w ("Johnny Bravo\n");
		Candidate cand[3];
		vector<Ballot> list;
		int i;
		
		for (i=0;i<4;i++) {
			voting_read_candidates(r, cand[i]);
		}
		
		for(i = 0; i < list.size(); ++i){
			const bool c = voting_read_ballots(b, list, i);
			CPPUNIT_ASSERT(c == true);
		}
		voting_eval(cand, 4, list);
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "Johnny Bravo\n");
	}
	
	CPPUNIT_TEST_SUITE(TestVoting);
	CPPUNIT_TEST(test_read_ballots_1);
	CPPUNIT_TEST(test_read_ballots_2);
	CPPUNIT_TEST(test_read_ballots_3);
	CPPUNIT_TEST(test_read_cand_1);
	CPPUNIT_TEST(test_read_cand_2);
	CPPUNIT_TEST(test_read_cand_3);
	CPPUNIT_TEST(test_eval_1);
	CPPUNIT_TEST(test_eval_2);
	CPPUNIT_TEST(test_eval_3);
	CPPUNIT_TEST(test_solve_3);
	CPPUNIT_TEST(test_solve_3);
	CPPUNIT_TEST(test_solve_3);
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
