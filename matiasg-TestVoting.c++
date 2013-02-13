
// --------
// includes
// --------

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"

#include "Voting.h"

// ----------
// TestVoting
// ----------
struct TestVoting : CppUnit::TestFixture {

    // ---------
    // BallotBox
    // ---------
    void test_bb () {  // does this count as testing getTotalVotes as well?
        BallotBox bb;
        const int initialVotes = bb.getTotalVotes();
        CPPUNIT_ASSERT(initialVotes == 0);
    }
    void test_bb_2 () {
        BallotBox bb;
	int l [20];
        const int initialMin = bb.returnLosers(l);
        CPPUNIT_ASSERT(initialMin == 1001);
    }
    void test_bb_3 () {
        BallotBox bb;
	int w [20];
        const int initialMax = bb.returnWinners(w);
        CPPUNIT_ASSERT(initialMax == 0);
    }
    
    // -------------------
    // addVote/getNumVotes
    // -------------------
    
    void test_bb_av () {
        BallotBox bb;
	bb.addVote(1);
        const int v = bb.getNumVotes(1);
        CPPUNIT_ASSERT(v == 0);
    }
    void test_bb_av_2 () {
        BallotBox bb;
	bb.addVote(1);
        const int v = bb.getNumVotes(0);
        CPPUNIT_ASSERT(v == -1);
    }
    void test_bb_av_3 () {
        BallotBox bb;
	bb.addVote(20);
	bb.addVote(20);
	bb.addVote(20);
	bb.addVote(20);
	bb.addVote(20);
        const int v = bb.getNumVotes(20);
        CPPUNIT_ASSERT(v == 4);
    }
    // ---------------------------
    // setTotalVotes/getTotalVotes
    // ---------------------------
    void test_bb_stv () {
        BallotBox bb;
	bb.setTotalVotes(1);
        const int t = bb.getTotalVotes();
        CPPUNIT_ASSERT(t == 1);
    }
    void test_bb_stv_2 () {
        BallotBox bb;
	bb.setTotalVotes(1000);
        const int t = bb.getTotalVotes();
        CPPUNIT_ASSERT(t == 1000);
    }
    void test_bb_stv_3 () {
        BallotBox bb;
	bb.setTotalVotes(2147483647);
        const int t = bb.getTotalVotes();
        CPPUNIT_ASSERT(t == 2147483647);
    }
    // -----------
    // updateTally
    // -----------
    void test_bb_ut () {
        BallotBox bb;
	bb.updateTally(1,1);
        const int v = bb.getNumVotes(1);
        CPPUNIT_ASSERT(v == 1);  // note difference between updating candidate 1's tally to 1, and adding
    }				  // one vote to candidate one's iniital tally using addVote
    
    void test_bb_ut_2 () {
        BallotBox bb;
	bb.updateTally(20,1000);
        const int v = bb.getNumVotes(20);
        CPPUNIT_ASSERT(v == 1000);
    }
    
    void test_bb_ut_3 () {
        BallotBox bb;
	bb.updateTally(2,2147483647);
        const int v = bb.getNumVotes(2);
        CPPUNIT_ASSERT(v == 2147483647);
    }
    
    // ------------
    // returnLosers
    // ------------
    
    void test_bb_rl () {
        BallotBox bb;
	bb.addVote(1);
	bb.updateTally(2,1);
	int l [20];
        const int min = bb.returnLosers(l);
        CPPUNIT_ASSERT(min == 0);
	CPPUNIT_ASSERT(l[0] = 1);
    }
    
    void test_bb_rl_2 () {
        BallotBox bb;
	bb.updateTally(20,1);
	bb.updateTally(2,1);
	int l [20];
        const int min = bb.returnLosers(l);
        CPPUNIT_ASSERT(min == 1);
	CPPUNIT_ASSERT(l[0] = 2);
	CPPUNIT_ASSERT(l[1] = 20);
    }
    
    void test_bb_rl_3 () {
        BallotBox bb;
	bb.updateTally(20,1002);
	int l [20];
        const int min = bb.returnLosers(l);
        CPPUNIT_ASSERT(min == 1001);
    }
    
    // -------------
    // returnWinners
    // -------------
    
    void test_bb_rw () {
        BallotBox bb;
	bb.addVote(1);
	bb.updateTally(2,1);
	int w [20];
        const int max = bb.returnWinners(w);
        CPPUNIT_ASSERT(max == 1);
	CPPUNIT_ASSERT(w[0] = 2);
    }
    
    void test_bb_rw_2 () {
        BallotBox bb;
	bb.updateTally(1,1);
	bb.updateTally(2,1);
	int w [20];
        const int max = bb.returnWinners(w);
        CPPUNIT_ASSERT(max == 1);
	CPPUNIT_ASSERT(w[0] = 1);
	CPPUNIT_ASSERT(w[1] = 2);
    }
    
    void test_bb_rw_3 () {
        BallotBox bb;
	bb.updateTally(1,1);
	bb.updateTally(20,999);
	int w [20];
        const int max = bb.returnWinners(w);
        CPPUNIT_ASSERT(max == 999);
	CPPUNIT_ASSERT(w[0] = 20);
    }
    
    // -------------
    // Ballot Testing
    // -------------

    void test_ballot () {
        Ballot b(2);
	b.setNthPlace(12, 0);
	const int NthPlace = b.getNthPlace(0);
	CPPUNIT_ASSERT(NthPlace == 12);
    }
    
    void test_ballot_2() {
	Ballot b(19);
	b.setNthPlace(2, 19);
	const int NthPlace = b.getNthPlace(19);
	CPPUNIT_ASSERT(NthPlace == 2);
    }
    
    void test_ballot_3 () {
        Ballot b(1);
	b.setNthPlace(-1, 0);
	const int NthPlace = b.getNthPlace(0);
	CPPUNIT_ASSERT(NthPlace == -1);
    }
    
     // -------------
    // Candidate
    // -------------
    
    void test_can () {  
        Candidate c;	
        const int initialSize = c.getSize();
        CPPUNIT_ASSERT(initialSize == 0);
    }
    
    void test_can_2 () {  
	Candidate c;
	const bool initialHasLost = c.hasLost();
	CPPUNIT_ASSERT(initialHasLost == false);
    }
    
    void test_can_3 () { 
        Candidate c;	
        std::string name = c.getStrName(); 
	CPPUNIT_ASSERT(name == "");
    }
    
    // -------------
    // Candidate initCandidate
    // -------------
    void test_initCan () {  
        Candidate c;
	c.initCandidate(0, "Harvey Spector");
	std::string name = c.getStrName();
	CPPUNIT_ASSERT(name == "Harvey Spector");
    }
    void test_initCan_2 () {  
	Candidate c;
	c.initCandidate(19, "Michael Ross");
	std::string name = c.getStrName();
	CPPUNIT_ASSERT(name == "Michael Ross");
    }
    
    void test_initCan_3 () { 
        Candidate c;	
        c.initCandidate(1, "Donna Paulsen");
	std::string name = c.getStrName();
	CPPUNIT_ASSERT(name == "Donna Paulsen");
    }
    
    
    

    // -------------
    // Candidate addBallot
    // -------------
    
    void test_addB () {  
        Candidate c;
	Ballot b(0);
	b.setNthPlace(42,0);
	c.addBallot(b);
	const int vote = c.ballots[0].getNthPlace(0);
	const int size = c.getSize();
	CPPUNIT_ASSERT(vote == 42);
	CPPUNIT_ASSERT(size == 1);
    }   
    void test_addB_2 () {  
        Candidate c;
	Ballot b(0);
	Ballot d(0);
	b.setNthPlace(42,0);
	b.setNthPlace(4,1);
	d.setNthPlace(42,0);
	c.addBallot(b);
	c.addBallot(d);
	const int vote1 = c.ballots[0].getNthPlace(0);
	const int vote2 = c.ballots[1].getNthPlace(0);
	const int size = c.getSize();
	CPPUNIT_ASSERT(vote1 == 42);
	CPPUNIT_ASSERT(vote2 == 42);
	CPPUNIT_ASSERT(size == 2);
    }   
    void test_addB_3 () {  
        Candidate c;
	Ballot b(0);
	Ballot d(0);
	b.setNthPlace(42,0);
	b.setNthPlace(4,1);
	d.setNthPlace(42,0);
	c.addBallot(b);
	c.addBallot(d);
	const int vote1 = c.ballots[0].getNthPlace(1);
	const int vote2 = c.ballots[1].getNthPlace(0);
	const int size = c.getSize();
	CPPUNIT_ASSERT(vote1 == 4);
	CPPUNIT_ASSERT(vote2 == 42);
	CPPUNIT_ASSERT(size == 2);
    }   
    
    // -------------
    // Candidate getSize
    // -------------
 
    void test_getSize () {  
        Candidate c;
	const int size = c.getSize();
	CPPUNIT_ASSERT(size == 0);
    }
    
    void test_getSize_2 () {  
        Candidate c;
	Ballot b(0);
	b.setNthPlace(42,0);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	const int vote = c.ballots[0].getNthPlace(0);
	const int size = c.getSize();
	CPPUNIT_ASSERT(vote == 42);
	CPPUNIT_ASSERT(size == 4);
    }
    
    void test_getSize_3 () {  
        Candidate c;
	Ballot b(0);
	b.setNthPlace(42,0);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	c.addBallot(b);
	const int vote = c.ballots[0].getNthPlace(0);
	const int size = c.getSize();
	CPPUNIT_ASSERT(vote == 42);
	CPPUNIT_ASSERT(size == 24);
    }
    
    // -------------
    // Candidate SetLost/hasLost
    // -------------
    
     void test_Lost () {  
        Candidate c;
	bool b = c.hasLost();
	CPPUNIT_ASSERT(b == false);
    }
     void test_Lost_2 () {  
        Candidate c;
	c.initCandidate(0,"Yeah");
	bool b = c.hasLost();
	CPPUNIT_ASSERT(b == false);
    }
      void test_Lost_3 () {  
        Candidate c;
	c.setLost();
	bool b = c.hasLost();
	CPPUNIT_ASSERT(b == true);
    }
    
    
    // -------------
    // Candidate getStrName
    // -------------
    void test_getStr() {  
        Candidate c;
	c.initCandidate(0, " ");
	std::string name = c.getStrName();
	CPPUNIT_ASSERT(name == " ");
    }
    void test_getStr_2() {  
        Candidate c;
	c.initCandidate(0, "50");
	std::string name = c.getStrName();
	CPPUNIT_ASSERT(name == "50");
    }
    void test_getStr_3() {  
        Candidate c;
	c.initCandidate(0, "Jessica Pearson");
	std::string name = c.getStrName();
	CPPUNIT_ASSERT(name == "Jessica Pearson");
    }
    // ------------
    // voting_read
    // ------------
    void test_voting_read() {
      Candidate cs[20];
      std::istringstream r("4\nA\nB\nC\nD\n1 2 3 4\n1 2 3 4\n");
      voting_read_case(r, cs);
      CPPUNIT_ASSERT(cs[0].getSize() == 2);
      CPPUNIT_ASSERT(cs[1].getSize() == 0);
      CPPUNIT_ASSERT(cs[2].getSize() == 0);
      CPPUNIT_ASSERT(cs[3].getSize() == 0);
    }
    
    void test_voting_read_2() {
      Candidate cs[20];
      std::istringstream r("4\nA\nB\nC\nD\n1 2 3 4\n1 2 3 4\n");
      voting_read_case(r, cs);
      CPPUNIT_ASSERT(cs[0].getStrName() == "A");
      CPPUNIT_ASSERT(cs[1].getStrName() == "B");
      CPPUNIT_ASSERT(cs[2].getStrName() == "C");
      CPPUNIT_ASSERT(cs[3].getStrName() == "D");
    }
    void test_voting_read_3() {
      Candidate cs[20];
      std::istringstream r("\n\n\n\n\n");
      voting_read_case(r, cs);
      CPPUNIT_ASSERT(cs[0].getStrName() == "");
      CPPUNIT_ASSERT(cs[1].getStrName() == "");
      CPPUNIT_ASSERT(cs[2].getStrName() == "");
      CPPUNIT_ASSERT(cs[3].getStrName() == "");
    }
    // ------------
    // voting_print
    // ------------
    void test_voting_print() {
      Candidate cs[20];
      std::ostringstream w;
      cs[19].initCandidate(20, "Henry Clay");
      int winners[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
      winners[0] = 20;
      voting_print(w, winners, cs);
      CPPUNIT_ASSERT(w.str() == "Henry Clay\n");
    }
    
    void test_voting_print_2() {
      Candidate cs[20];
      std::ostringstream w;
      cs[10].initCandidate(11, "Adlai Stevenson");
      cs[19].initCandidate(20, "Henry Clay");
      int winners[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
      winners[0] = 11;
      winners[1] = 20;
      voting_print(w, winners, cs);
      CPPUNIT_ASSERT(w.str() == "Adlai Stevenson\nHenry Clay\n");
    }
    void test_voting_print_3() {
      Candidate cs[20];
      std::ostringstream w;
      int winners[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
      for(int i = 0; i < 20; i++) {
	cs[i].initCandidate(i+1, "T");
	winners[i] = i+1;
      }
      voting_print(w, winners, cs);
      CPPUNIT_ASSERT(w.str() == "T\nT\nT\nT\nT\nT\nT\nT\nT\nT\nT\nT\nT\nT\nT\nT\nT\nT\nT\nT\n");
    }
    
    // ------------
    // voting_tally
    // ------------
    void test_voting_tally() {
      Candidate cs[20];
      cs[0].initCandidate(1, "Adlai Stevenson");
      BallotBox bb;
      int winners[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
      bb.updateTally(1,20);
      voting_tally(cs, bb, winners);
      CPPUNIT_ASSERT(winners[0] = 1);
    }
    void test_voting_tally_2() {
      Candidate cs[20];
      cs[0].initCandidate(1, "Adlai Stevenson");
      cs[1].initCandidate(2, "Al Gore");
      cs[2].initCandidate(3, "Henry Clay");
      BallotBox bb;
      int winners[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
      bb.updateTally(1,20);
      bb.updateTally(2,20);
      bb.updateTally(3,2);
      voting_tally(cs, bb, winners);
      CPPUNIT_ASSERT(winners[0] = 1);
      CPPUNIT_ASSERT(winners[1] = 2);
    }
    void test_voting_tally_3() {
      Candidate cs[20];
      cs[0].initCandidate(1, "Adlai Stevenson");
      cs[1].initCandidate(2, "Al Gore");
      cs[2].initCandidate(3, "Henry Clay");
      BallotBox bb;
      int winners[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
      bb.updateTally(1,0);
      bb.updateTally(2,0);
      bb.updateTally(3,0);
      voting_tally(cs, bb, winners);
      CPPUNIT_ASSERT(winners[0] = 1);
      CPPUNIT_ASSERT(winners[1] = 2);
      CPPUNIT_ASSERT(winners[2] = 3);
    }
    
    void test_voting_driver() {
      std::ostringstream w;
      std::istringstream r("1\n\n4\nA\nB\nC\nD\n1 2 3 4\n1 2 3 4\n");
      voting_driver(r,w);
      CPPUNIT_ASSERT(w.str() == "A\n");
    }
    void test_voting_driver_2() {
      std::ostringstream w;
      std::istringstream r("1\n\n4\nA\nB\nC\nD\n1 2 3 4\n2 1 3 4\n");
      voting_driver(r,w);
      CPPUNIT_ASSERT(w.str() == "A\nB\n");
    }
    void test_voting_driver_3() {
      std::ostringstream w;
      std::istringstream r("2\n\n4\n\n\n\n\n1 2 3 4\n2 1 3 4\n3 1 2 4\n4 2 1 3\n\n2\nA\nB\n1 2");
      voting_driver(r,w);
      CPPUNIT_ASSERT(w.str() == "\n\n\n\n\nA\n");
    }
    
    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_bb);
    CPPUNIT_TEST(test_bb_2);
    CPPUNIT_TEST(test_bb_3);
    CPPUNIT_TEST(test_bb_av);
    CPPUNIT_TEST(test_bb_av_2);
    CPPUNIT_TEST(test_bb_av_3);
    CPPUNIT_TEST(test_bb_stv);
    CPPUNIT_TEST(test_bb_stv_2);  
    CPPUNIT_TEST(test_bb_stv_3);
    CPPUNIT_TEST(test_bb_ut);
    CPPUNIT_TEST(test_bb_ut_2);
    CPPUNIT_TEST(test_bb_ut_3);
    CPPUNIT_TEST(test_bb_rl);
    CPPUNIT_TEST(test_bb_rl_2);
    CPPUNIT_TEST(test_bb_rl_3);
    CPPUNIT_TEST(test_bb_rw);
    CPPUNIT_TEST(test_bb_rw_2);
    CPPUNIT_TEST(test_bb_rw_3);
    CPPUNIT_TEST(test_ballot);
    CPPUNIT_TEST(test_ballot_2);
    CPPUNIT_TEST(test_ballot_3);
    CPPUNIT_TEST(test_can);
    CPPUNIT_TEST(test_can_2);
    CPPUNIT_TEST(test_can_3);
    CPPUNIT_TEST(test_initCan);
    CPPUNIT_TEST(test_initCan_2);
    CPPUNIT_TEST(test_initCan_3);
    CPPUNIT_TEST(test_addB);
    CPPUNIT_TEST(test_addB_2);
    CPPUNIT_TEST(test_addB_3);
    CPPUNIT_TEST(test_getSize);
    CPPUNIT_TEST(test_getSize_2);
    CPPUNIT_TEST(test_getSize_3);
    CPPUNIT_TEST(test_Lost);
    CPPUNIT_TEST(test_Lost_2);
    CPPUNIT_TEST(test_Lost_3);
    CPPUNIT_TEST(test_getStr);
    CPPUNIT_TEST(test_getStr_2);
    CPPUNIT_TEST(test_getStr_3);
    CPPUNIT_TEST(test_voting_read);
    CPPUNIT_TEST(test_voting_read_2);
    CPPUNIT_TEST(test_voting_read_3);
    CPPUNIT_TEST(test_voting_print);
    CPPUNIT_TEST(test_voting_print_2);
    CPPUNIT_TEST(test_voting_print_3);
    CPPUNIT_TEST(test_voting_tally);
    CPPUNIT_TEST(test_voting_tally_2);
    CPPUNIT_TEST(test_voting_tally_3);
    CPPUNIT_TEST(test_voting_driver);
    CPPUNIT_TEST(test_voting_driver_2);
    CPPUNIT_TEST(test_voting_driver_3);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

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