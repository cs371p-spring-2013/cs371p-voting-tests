// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector> //vector

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

// -----------
// TestCollatz
// -----------

struct TestCollatz : CppUnit::TestFixture {
    void test_read_1 (){
        istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        int numCases;
        vector <Candidate> canList;
        vector <Voter> voteList;
        
        get_num_cases(r, numCases);
        CPPUNIT_ASSERT(numCases   == 1);
        
        voting_read(r, canList, voteList); 
        CPPUNIT_ASSERT(canList[0].name == "John Doe");
        CPPUNIT_ASSERT(canList[1].name == "Jane Smith");
        CPPUNIT_ASSERT(canList[2].name == "Sirhan Sirhan");       
        CPPUNIT_ASSERT(canList[0].numVotes == 0);
        CPPUNIT_ASSERT(canList[1].numVotes == 0);
        CPPUNIT_ASSERT(canList[2].numVotes == 0);
       
        CPPUNIT_ASSERT(voteList[0].votes[0] == 1);
        CPPUNIT_ASSERT(voteList[0].votes[1] == 2);
        CPPUNIT_ASSERT(voteList[0].votes[2] == 3);
        CPPUNIT_ASSERT(voteList[0].index == 0);        
        CPPUNIT_ASSERT(voteList[4].votes[0] == 3);
        CPPUNIT_ASSERT(voteList[4].votes[1] == 1);
        CPPUNIT_ASSERT(voteList[4].votes[2] == 2);
        CPPUNIT_ASSERT(voteList[4].index == 0);
    }
    
    void test_read_2 (){
        istringstream r("2\n\n2\ngreen\norange\n1 2\n2 1\n2 1\n1 2\n\n3\nred\nblue\nblack\n1 2 3\n2 1 3");
        int numCases;
        vector <Candidate> canList;
        vector <Voter> voteList;
        
        get_num_cases(r, numCases);
        CPPUNIT_ASSERT(numCases   == 2);
        
        voting_read(r, canList, voteList);      
        CPPUNIT_ASSERT(canList[0].name == "green");
        CPPUNIT_ASSERT(canList[1].name == "orange");        
        CPPUNIT_ASSERT(voteList[0].votes[0] == 1);
        CPPUNIT_ASSERT(voteList[0].votes[1] == 2);        
        CPPUNIT_ASSERT(voteList[1].votes[0] == 2);
        CPPUNIT_ASSERT(voteList[1].votes[1] == 1);
        CPPUNIT_ASSERT(voteList[3].votes[0] == 1);
        CPPUNIT_ASSERT(voteList[3].votes[1] == 2);
        
        vector <Candidate> canList2;
        vector <Voter> voteList2;
        
        voting_read(r, canList2, voteList2);   
        CPPUNIT_ASSERT(canList2[0].name == "red");        
        CPPUNIT_ASSERT(canList2[1].name == "blue");
        CPPUNIT_ASSERT(canList2[2].name == "black");
        CPPUNIT_ASSERT(voteList2[0].votes[0] == 1);
        CPPUNIT_ASSERT(voteList2[0].votes[1] == 2);        
        CPPUNIT_ASSERT(voteList2[0].votes[2] == 3);
        CPPUNIT_ASSERT(voteList2[1].votes[0] == 2);
        CPPUNIT_ASSERT(voteList2[1].votes[1] == 1);        
        CPPUNIT_ASSERT(voteList2[1].votes[2] == 3);      
    }

    void test_read_3 (){
        istringstream r("1\n\n3\nDowning\nIrving\nTroy\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        int numCases;
        vector <Candidate> canList;
        vector <Voter> voteList;
        
        get_num_cases(r, numCases);
        CPPUNIT_ASSERT(numCases   == 1);
        
        voting_read(r, canList, voteList); 
        CPPUNIT_ASSERT(canList[0].name == "Downing");
        CPPUNIT_ASSERT(canList[1].name == "Irving");
        CPPUNIT_ASSERT(canList[2].name == "Troy");       
        CPPUNIT_ASSERT(canList[0].numVotes == 0);
        CPPUNIT_ASSERT(canList[1].numVotes == 0);
        CPPUNIT_ASSERT(canList[2].numVotes == 0);
       
        CPPUNIT_ASSERT(voteList[0].votes[0] == 1);
        CPPUNIT_ASSERT(voteList[0].votes[1] == 2);
        CPPUNIT_ASSERT(voteList[0].votes[2] == 3);
        CPPUNIT_ASSERT(voteList[0].index == 0);        
        CPPUNIT_ASSERT(voteList[4].votes[0] == 3);
        CPPUNIT_ASSERT(voteList[4].votes[1] == 1);
        CPPUNIT_ASSERT(voteList[4].votes[2] == 2);
        CPPUNIT_ASSERT(voteList[4].index == 0);
    }
    
    void test_solver_1() {
        vector <Candidate> canList;
        canList.push_back(Candidate {"John Doe", 0, true});
        canList.push_back(Candidate {"Jane Smith", 0, true});
        canList.push_back(Candidate {"Sirhan Sirhan", 0, true});
        vector <Voter> voteList;
        voteList.push_back(Voter {vector<int>{1,2,3}, 0});
        voteList.push_back(Voter {vector<int>{2,1,3}, 0});
        voteList.push_back(Voter {vector<int>{2,3,1}, 0});
        voteList.push_back(Voter {vector<int>{1,2,3}, 0});
        voteList.push_back(Voter {vector<int>{3,1,2}, 0});
        string ret;
        ret = smart_solver(canList, voteList);
        CPPUNIT_ASSERT(ret == "John Doe\n");
    }

    void test_solver_2(){
        vector <Candidate> canList;
        canList.push_back(Candidate {"Red", 0, true});
        canList.push_back(Candidate {"Green", 0, true});
        canList.push_back(Candidate {"Orange", 0, true});
        canList.push_back(Candidate {"Purple", 0, true});

        vector<Voter> voteList;
        voteList.push_back(Voter {vector<int>{1, 2, 3, 4}, 0});
        voteList.push_back(Voter {vector<int>{1, 2, 3, 4}, 0});
        voteList.push_back(Voter {vector<int>{1, 2, 3, 4}, 0});

        string ret;
        ret = smart_solver(canList, voteList);
        CPPUNIT_ASSERT(ret == "Red\n");
    }

    void test_solver_3(){
        vector <Candidate> canList;
        canList.push_back(Candidate {"Red", 0, true});
        canList.push_back(Candidate {"Green", 0, true});
        canList.push_back(Candidate {"Orange", 0, true});
        canList.push_back(Candidate {"Purple", 0, true});

        vector<Voter> voteList;
        voteList.push_back(Voter {vector<int>{1, 2, 3, 4}, 0});
        voteList.push_back(Voter {vector<int>{1, 2, 3, 4}, 0});
        voteList.push_back(Voter {vector<int>{2, 1, 3, 4}, 0});
        voteList.push_back(Voter {vector<int>{2, 1, 3, 4}, 0});
        voteList.push_back(Voter {vector<int>{3, 4, 1, 2}, 0});

        string ret;
        ret = smart_solver(canList, voteList);
        CPPUNIT_ASSERT(ret == "Red\n");
    }

    void test_solver_4(){
        vector <Candidate> canList;
        canList.push_back(Candidate {"Red", 0, true});
        canList.push_back(Candidate {"Green", 0, true});
        canList.push_back(Candidate {"Blue", 0, true});
        canList.push_back(Candidate {"Orange", 0, true});

        vector<Voter> voteList;
        voteList.push_back(Voter {vector<int>{1, 2, 3, 4}, 0});
        voteList.push_back(Voter {vector<int>{2, 1, 3, 4}, 0});
        voteList.push_back(Voter {vector<int>{2, 3, 1, 4}, 0});
        voteList.push_back(Voter {vector<int>{1, 2, 3, 4}, 0});
        voteList.push_back(Voter {vector<int>{3, 4, 1, 2}, 0});
        voteList.push_back(Voter {vector<int>{4, 3, 2, 1}, 0});

        string ret;
        ret = smart_solver(canList, voteList);
        CPPUNIT_ASSERT(ret == "Red\nGreen\n");
    }

    void test_solver_5(){
        vector <Candidate> canList;
        canList.push_back(Candidate {"Red", 0, true});
        canList.push_back(Candidate {"Green", 0, true});
        canList.push_back(Candidate {"Blue", 0, true});

        vector<Voter> voteList;
        voteList.push_back(Voter {vector<int>{1, 2, 3}, 0});
        voteList.push_back(Voter {vector<int>{1, 2, 3}, 0});
        voteList.push_back(Voter {vector<int>{2, 3, 1}, 0});
        voteList.push_back(Voter {vector<int>{2, 1, 3}, 0});
        voteList.push_back(Voter {vector<int>{3, 2, 1}, 0});
        voteList.push_back(Voter {vector<int>{3, 1, 2}, 0});

        string ret;
        ret = smart_solver(canList, voteList);
        CPPUNIT_ASSERT(ret == "Red\nGreen\nBlue\n");
    }

    void test_solver_6(){
        vector <Candidate> canList;
        canList.push_back(Candidate {"Red", 0, true});
        canList.push_back(Candidate {"Blue", 0, true});
        canList.push_back(Candidate {"Green", 0, true});
        canList.push_back(Candidate {"Aqua", 0, true});
        canList.push_back(Candidate {"Pink", 0, true});
        canList.push_back(Candidate {"Orange", 0, true});

        vector<Voter> voteList;
        voteList.push_back(Voter {vector<int>{1, 2, 3, 4, 5, 6}, 0});
        voteList.push_back(Voter {vector<int>{1, 2, 3, 4, 5, 6}, 0});
        voteList.push_back(Voter {vector<int>{1, 2, 3, 4, 5, 6}, 0});
        voteList.push_back(Voter {vector<int>{1, 2, 3, 4, 5, 6}, 0});
        voteList.push_back(Voter {vector<int>{2, 1, 3, 4, 5, 6}, 0});
        voteList.push_back(Voter {vector<int>{2, 1, 3, 4, 5, 6}, 0});
        voteList.push_back(Voter {vector<int>{2, 1, 3, 4, 5, 6}, 0});
        voteList.push_back(Voter {vector<int>{2, 1, 3, 4, 5, 6}, 0});
        voteList.push_back(Voter {vector<int>{6, 5, 4, 3, 2, 1}, 0});
        voteList.push_back(Voter {vector<int>{6, 5, 4, 1, 2, 3}, 0});
        voteList.push_back(Voter {vector<int>{1, 2, 3, 4, 5, 6}, 0});
        voteList.push_back(Voter {vector<int>{2, 1, 3, 4, 5, 6}, 0});

        string ret;
        ret = smart_solver(canList, voteList);
        CPPUNIT_ASSERT(ret == "Red\nBlue\n");
    }

    void test_have_one_winner_1() {
        int winning_condition = 10;
        bool ret;

        vector<Candidate> canList;
        canList.push_back(Candidate {"Red", 10, true});

        ret = have_one_winner(canList, winning_condition);
        CPPUNIT_ASSERT(ret == true);
    }

    void test_have_one_winner_2() {
        int winning_condition = 10;
        bool ret;

        vector<Candidate> canList;
        canList.push_back(Candidate {"Red", 9, true});

        ret = have_one_winner(canList, winning_condition);
        CPPUNIT_ASSERT(ret == false);
    }

    void test_have_one_winner_3() {
        int winning_condition = 10;
        bool ret;

        vector<Candidate> canList;
        canList.push_back(Candidate {"Red", 9, true});
        canList.push_back(Candidate {"Blue", 10, true});

        ret = have_one_winner(canList, winning_condition);
        CPPUNIT_ASSERT(ret == true);
    }

    void test_have_one_winner_4() {
        int winning_condition = 10;
        bool ret;

        vector<Candidate> canList;
        canList.push_back(Candidate {"Red", 5, true});
        canList.push_back(Candidate {"Blue", 5, true});
        canList.push_back(Candidate {"Orange", 5, true});

        ret = have_one_winner(canList, winning_condition);
        CPPUNIT_ASSERT(ret == false);
    }

    void test_get_high_votes_1() {
        int ret;
        vector<Candidate> canList;
        canList.push_back(Candidate {"Red", 5, true});
        canList.push_back(Candidate {"Blue", 5, true});
        canList.push_back(Candidate {"Orange", 5, true});

        ret = get_high_votes(canList);
        CPPUNIT_ASSERT(ret == 5);
    }

    void test_get_high_votes_2() {
        int ret;
        vector<Candidate> canList;
        canList.push_back(Candidate {"Red", 5, true});
        canList.push_back(Candidate {"Blue", 5, true});
        canList.push_back(Candidate {"Orange", 6, true});

        ret = get_high_votes(canList);
        CPPUNIT_ASSERT(ret == 6);
    }

    void test_get_high_votes_3() {
        int ret;
        vector<Candidate> canList;
        canList.push_back(Candidate {"Red", 5, true});

        ret = get_high_votes(canList);
        CPPUNIT_ASSERT(ret == 5);
    }

    void test_get_low_votes_1() {
        int ret;
        vector<Candidate> canList;
        canList.push_back(Candidate {"Red", 5, true});
        canList.push_back(Candidate {"Blue", 5, true});
        canList.push_back(Candidate {"Orange", 5, true});

        ret = get_low_votes(canList, 6);
        CPPUNIT_ASSERT(ret == 5);
    }

    void test_get_low_votes_2() {
        int ret;
        vector<Candidate> canList;
        canList.push_back(Candidate {"Red", 5, true});
        canList.push_back(Candidate {"Blue", 5, true});
        canList.push_back(Candidate {"Orange", 4, true});

        ret = get_low_votes(canList, 6);
        CPPUNIT_ASSERT(ret == 4);
    }

    void test_get_low_votes_3() {
        int ret;
        vector<Candidate> canList;
        canList.push_back(Candidate {"Red", 5, true});

        ret = get_low_votes(canList, 6);
        CPPUNIT_ASSERT(ret == 5);
    }

    void test_get_num_cases_1() {
        int val;
        bool ret;
        istringstream r("2");
        ret = get_num_cases(r, val);
        CPPUNIT_ASSERT(ret == true);
        CPPUNIT_ASSERT(val == 2);
    }

    void test_get_num_cases_2() {
        int val;
        bool ret;
        istringstream r("");
        ret = get_num_cases(r, val);
        CPPUNIT_ASSERT(ret == false);
    }

    void test_get_num_cases_3() {
        int val;
        bool ret;
        istringstream r("7\n");
        ret = get_num_cases(r, val);
        CPPUNIT_ASSERT(ret == true);
        CPPUNIT_ASSERT(val == 7);
    }

    void test_voting_print_1() {
        ostringstream w;
        voting_print(w, "apples");
        CPPUNIT_ASSERT(w.str() == "apples");
    }

    void test_voting_print_2() {
        ostringstream w;
        voting_print(w, "apples\n");
        CPPUNIT_ASSERT(w.str() == "apples\n");
    }
    void test_voting_print_3() {
        ostringstream w;
        voting_print(w, "apples\norange");
        CPPUNIT_ASSERT(w.str() == "apples\norange");
    }


    void test_voting_run_1(){
        istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        ostringstream w;
        voting_run(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
    }
    void test_voting_run_2(){
        istringstream r("2\n\n2\ngreen\norange\n1 2\n2 1\n2 1\n1 2\n\n3\nred\nblue\nblack\n1 2 3\n2 1 3");
        ostringstream w;
        voting_run(r, w);
        CPPUNIT_ASSERT(w.str() == "green\norange\n\nred\nblue\n");
    }
    void test_voting_run_3(){
        istringstream r("1\n\n1\nbear\n1\n1");
        ostringstream w;
        voting_run(r, w);
        CPPUNIT_ASSERT(w.str() == "bear\n");
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    
    //test read
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);

    //test solver
    CPPUNIT_TEST(test_solver_1);
    CPPUNIT_TEST(test_solver_2);
    CPPUNIT_TEST(test_solver_3);
    CPPUNIT_TEST(test_solver_4);
    CPPUNIT_TEST(test_solver_5);
    CPPUNIT_TEST(test_solver_6);

        //test have_one_winner
    CPPUNIT_TEST(test_have_one_winner_1);
    CPPUNIT_TEST(test_have_one_winner_2);
    CPPUNIT_TEST(test_have_one_winner_3);
    CPPUNIT_TEST(test_have_one_winner_4);

    //test get_high_votes
    CPPUNIT_TEST(test_get_high_votes_1);
    CPPUNIT_TEST(test_get_high_votes_2);
    CPPUNIT_TEST(test_get_high_votes_3);

    //test get_low_votes
    CPPUNIT_TEST(test_get_low_votes_1);
    CPPUNIT_TEST(test_get_low_votes_2);
    CPPUNIT_TEST(test_get_low_votes_3);

    // test get_num_cases
    CPPUNIT_TEST(test_get_num_cases_1);
    CPPUNIT_TEST(test_get_num_cases_2);
    CPPUNIT_TEST(test_get_num_cases_3);

    // test voting print
    CPPUNIT_TEST(test_voting_print_1);
    CPPUNIT_TEST(test_voting_print_2);
    CPPUNIT_TEST(test_voting_print_3);

    // test voting run
    CPPUNIT_TEST(test_voting_run_1);
    CPPUNIT_TEST(test_voting_run_2);
    CPPUNIT_TEST(test_voting_run_3);

    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestCollatz.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestCollatz::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
