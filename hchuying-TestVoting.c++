
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
   

    // ----
    // prelim_read
    // ----

    void test_prelim_read_1 () {
        std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n");
        int i = 0;
        const bool b = preliminary_read(r,i);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i>0);}


    void test_prelim_read_2 () {
        std::istringstream r("");
        int i = 0;
        const bool b = preliminary_read(r,i);
        CPPUNIT_ASSERT(b == false);}

    void test_prelim_read_3 () {
        std::istringstream r("1\n\n1\nA\n1\n1\n");
        int i = 0;
        const bool b = preliminary_read(r,i);
        CPPUNIT_ASSERT(i>0);
        CPPUNIT_ASSERT(b == true);}


    // ----
    // mySplit2
    // ----


    void test_mySplit2_1 () {
        using namespace std;
        vector<string> candidates;
        candidates.push_back("John Doe");
        candidates.push_back("Jane Smith");
        candidates.push_back("Sirhan Sirhan");
        vector<vector<int> > ballots;
        int numcan =3;
        int numbal =0;

        mySplit2(ballots, "1 2 3", numcan, numbal);

        CPPUNIT_ASSERT(ballots.size() > 0);}

    void test_mySplit2_2 () {
        using namespace std;
        vector<string> candidates;
        candidates.push_back("John Doe");
        candidates.push_back("Jane Smith");
        candidates.push_back("Sirhan Sirhan");
        vector<vector<int> > ballots;
        int numcan =3;
        int numbal =0;

        mySplit2(ballots, "1 2 3", numcan, numbal);
        numbal++;
        mySplit2(ballots, "2 1 3", numcan, numbal);
        CPPUNIT_ASSERT(ballots.size()==2);}

    void test_mySplit2_3 () {
        using namespace std;
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n");
        vector<string> candidates;
        candidates.push_back("John Doe");
        candidates.push_back("Jane Smith");
        candidates.push_back("Sirhan Sirhan");
        vector<vector<int> > ballots;
        int numcan =3;
        int numbal =0;

        mySplit2(ballots, "1 2 3", numcan, numbal);
        numbal++;
        mySplit2(ballots, "2 1 3", numcan, numbal);
        numbal++;
        mySplit2(ballots, "3 1 2", numcan, numbal);
        CPPUNIT_ASSERT(ballots.size()==3);}


    // ----
    // read
    // ----


    void test_read_1 () {
        using namespace std;
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n");
        vector<string> candidates(20);
        vector<vector<int> > ballots;
        int numcan =0;
        int numbal =0;
        const bool b = voting_read(r,candidates,ballots, numcan, numbal);
        CPPUNIT_ASSERT(numcan > 0);
        CPPUNIT_ASSERT(numbal > 0);
        CPPUNIT_ASSERT(b == true);}

    void test_read_2 () {
        using namespace std;
        std::istringstream r("4\nA\nB\nC\nD\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n3 2 1\n");
        vector<string> candidates(20);
        vector<vector<int> > ballots;
        int numcan =0;
        int numbal =0;
        const bool b = voting_read(r,candidates,ballots, numcan, numbal);
        CPPUNIT_ASSERT(numcan > 0);
        CPPUNIT_ASSERT(numbal > 0);
        CPPUNIT_ASSERT(b == true);}

    void test_read_3 () {
        using namespace std;
        std::istringstream r("1\nA\n1\n1\n");
        vector<string> candidates(20);
        vector<vector<int> > ballots;
        int numcan =0;
        int numbal =0;
        const bool b = voting_read(r,candidates,ballots, numcan, numbal);
        CPPUNIT_ASSERT(numcan > 0);
        CPPUNIT_ASSERT(numbal > 0);
        CPPUNIT_ASSERT(b == true);}

    
    // ------------
    // fill_ballots
    // ------------

    void test_fill_ballots_1 () {
        using namespace std;
        vector<string> candidates(3);
        candidates[0] = "A";
        candidates[1] = "B";
        candidates[2] = "C";
        vector<vector<int> > ballots;
        vector<std::vector<int> > looserVoteContainer(1, vector<int>( 3));
        looserVoteContainer[0][0] =1;
        looserVoteContainer[0][1] =2;
        looserVoteContainer[0][2] =3;
        fill_ballots(ballots, looserVoteContainer);
        CPPUNIT_ASSERT(ballots[0][0] == 1&&ballots[0][1] ==2&&ballots[0][2]==3 );}

    void test_fill_ballots_2 () {
        using namespace std;
        vector<string> candidates(3);
        candidates[0] = "A";
        candidates[1] = "B";
        candidates[2] = "C";
        vector<vector<int> > ballots;
        vector<std::vector<int> > looserVoteContainer;
        fill_ballots(ballots, looserVoteContainer);
        CPPUNIT_ASSERT(ballots.size()==0 );}

    void test_fill_ballots_3 () {
        using namespace std;
        vector<string> candidates(3);
        candidates[0] = "A";
        candidates[1] = "B";
        candidates[2] = "C";
        vector<vector<int> > ballots;
        vector<std::vector<int> > looserVoteContainer(2, vector<int>( 3));
        looserVoteContainer[0][0] =1;
        looserVoteContainer[0][1] =2;
        looserVoteContainer[0][2] =3;
        looserVoteContainer[1][0] =2;
        looserVoteContainer[1][1] =3;
        looserVoteContainer[1][2] =1;
        fill_ballots(ballots, looserVoteContainer);
        CPPUNIT_ASSERT(ballots.size()==2 );}
    



    // ----
    // eval
    // ----

    void test_eval_1 () {
        using namespace std;
        vector<string> candidates(3);
        candidates[0] = "A";
        candidates[1] = "B";
        candidates[2] = "C";
        vector<vector<int> > ballots(5, vector<int>( 3));
        ballots[0][0]=1;
        ballots[0][1]=2;
        ballots[0][2]=3;
        ballots[1][0]=2;
        ballots[1][1]=1;
        ballots[1][2]=3;
        ballots[2][0]=2;
        ballots[2][1]=3;
        ballots[2][2]=1;
        ballots[3][0]=1;
        ballots[3][1]=2;
        ballots[3][2]=3;
        ballots[4][0]=3;
        ballots[4][1]=1;
        ballots[4][2]=2;

        vector<int>  winners(20);
        int numberOfCandidates = 3;
        int numberOfBallots = 5;
        int numberOfCandidatesEnrolled = numberOfCandidates;
        int allBallots = numberOfBallots;
        voting_eval (numberOfCandidates, ballots,numberOfBallots, winners, numberOfCandidatesEnrolled,allBallots);
        CPPUNIT_ASSERT(winners[0]==1);}

    void test_eval_2 () {
        using namespace std;
        vector<string> candidates(4);
        candidates[0] = "A";
        candidates[1] = "B";
        candidates[2] = "C";
        candidates[3] = "D";
        vector<vector<int> > ballots(6, vector<int>( 4));
        ballots[0][0]=1;
        ballots[0][1]=2;
        ballots[0][2]=3;
        ballots[0][3]=4;
        ballots[1][0]=2;
        ballots[1][1]=1;
        ballots[1][2]=3;
        ballots[1][3]=4;
        ballots[2][0]=1;
        ballots[2][1]=2;
        ballots[2][2]=3;
        ballots[2][3]=4;
        ballots[3][0]=3;
        ballots[3][1]=4;
        ballots[3][2]=1;
        ballots[3][3]=2;
        ballots[4][0]=4;
        ballots[4][1]=3;
        ballots[4][2]=2;
        ballots[4][3]=1;
        ballots[5][0]=2;
        ballots[5][1]=1;
        ballots[5][2]=3;
        ballots[5][3]=4;

        vector<int>  winners(20);
        int numberOfCandidates = 4;
        int numberOfBallots = 6;
        int numberOfCandidatesEnrolled = numberOfCandidates;
        int allBallots = numberOfBallots;
        voting_eval (numberOfCandidates, ballots,numberOfBallots, winners, numberOfCandidatesEnrolled,allBallots);
        CPPUNIT_ASSERT(winners[0]==1&&winners[1]==2);}


    void test_eval_3 () {
        using namespace std;
        vector<string> candidates(1);
        candidates[0] = "A";

        vector<vector<int> > ballots(1, vector<int>( 1));
        ballots[0][0]=1;


        vector<int>  winners(20);
        int numberOfCandidates = 1;
        int numberOfBallots = 1;
        int numberOfCandidatesEnrolled = numberOfCandidates;
        int allBallots = numberOfBallots;
        voting_eval (numberOfCandidates, ballots,numberOfBallots, winners, numberOfCandidatesEnrolled,allBallots);
        CPPUNIT_ASSERT(winners[0]==1);}

    // -----
    // print
    // -----

    void test_print_1 () {
        using namespace std;
        ostringstream w;
        vector<string> candidates;
        candidates.push_back("John Doe");
        candidates.push_back("Jane Smith");
        candidates.push_back("Sirhan Sirhan");
        vector<int> winners;
        winners.push_back(1);
        voting_print(w,winners,candidates);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}

    void test_print_2 () {
        using namespace std;
        ostringstream w;
        vector<string> candidates;
        candidates.push_back("John Doe");
        candidates.push_back("Jane Smith");
        candidates.push_back("Sirhan Sirhan");
        vector<int> winners;
        winners.push_back(1);
        winners.push_back(2);
        voting_print(w,winners,candidates);
        CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\n");}

    void test_print_3 () {
        using namespace std;
        ostringstream w;
        vector<string> candidates;
        candidates.push_back("John Doe");
        candidates.push_back("Jane Smith");
        candidates.push_back("Sirhan Sirhan");
        vector<int> winners;
        winners.push_back(1);
        winners.push_back(2);
        winners.push_back(3);
        voting_print(w,winners,candidates);
        CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");}


    // -----
    // solve
    // -----

    void test_solve_1() {
        using namespace std;
        istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n");
        ostringstream w;
        voting_solve ( r, w);
    }

	void test_solve_2 () {
        std::istringstream r("1\n\n5\nA\nB\nC\nD\nE\n1 2 5 3 4\n2 1 3 5 4\n1 2 5 4 3\n2 1 3 4 5\n3 5 4 2 1\n");
        std::ostringstream w;
        voting_solve(r, w);

        CPPUNIT_ASSERT(w.str() == "B\n");
    }
    void test_solve_3() {
        using namespace std;
        istringstream r("1\n\n4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1\n\n");
        ostringstream w;
        voting_solve ( r, w);
        CPPUNIT_ASSERT(w.str() == "Red\nGreen\n");
    }



    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_prelim_read_1);
    CPPUNIT_TEST(test_prelim_read_2);
    CPPUNIT_TEST(test_prelim_read_3);
    CPPUNIT_TEST(test_mySplit2_1);
    CPPUNIT_TEST(test_mySplit2_2);   
    CPPUNIT_TEST(test_mySplit2_3);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_fill_ballots_1);
    CPPUNIT_TEST(test_fill_ballots_2);
    CPPUNIT_TEST(test_fill_ballots_3);
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
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
