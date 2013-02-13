#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>
#include <map>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"


struct TestVoting : CppUnit::TestFixture {

    void test_Candidate_constructor_1 () {
      Candidate c("blah");
      CPPUNIT_ASSERT(c.getName() == "blah");
      CPPUNIT_ASSERT(c.isEliminated() == false);
      CPPUNIT_ASSERT(c.getVoteCount() == 0);
    }

    // ----
    // read
    // ----

    void test_read_1 () {
        std::istringstream r("4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1\n\n");
        vector<Candidate> candidates;
        map<string, int> allBallots;
        int totalBallotCount = 0;
        voting_read(r, candidates, allBallots, totalBallotCount);

        CPPUNIT_ASSERT(candidates.size() == 4);
        CPPUNIT_ASSERT(candidates[0].getName() == "Red");
        CPPUNIT_ASSERT(candidates[1].getName() == "Green");
        CPPUNIT_ASSERT(candidates[2].getName() == "Blue");
        CPPUNIT_ASSERT(candidates[3].getName() == "Orange");

        CPPUNIT_ASSERT(allBallots.size() == 5);
        CPPUNIT_ASSERT(allBallots["1 2 3 4"] == 2);
        CPPUNIT_ASSERT(allBallots["2 1 3 4"] == 1);
        CPPUNIT_ASSERT(allBallots["2 3 1 4"] == 1);
        CPPUNIT_ASSERT(allBallots["3 4 1 2"] == 1);
        CPPUNIT_ASSERT(allBallots["4 3 2 1"] == 1);
        CPPUNIT_ASSERT(totalBallotCount == 6);
    }

    void test_read_2 () {
        std::istringstream r("5\nR\nG\nB\nO\nY\n");
        vector<Candidate> candidates;
        map<string, int> allBallots;
        int totalBallotCount = 0;
        voting_read(r, candidates, allBallots, totalBallotCount);

        CPPUNIT_ASSERT(candidates.size() == 5);
        CPPUNIT_ASSERT(candidates[0].getName() == "R");
        CPPUNIT_ASSERT(candidates[1].getName() == "G");
        CPPUNIT_ASSERT(candidates[2].getName() == "B");
        CPPUNIT_ASSERT(candidates[3].getName() == "O");
        CPPUNIT_ASSERT(candidates[4].getName() == "Y");

        CPPUNIT_ASSERT(allBallots.size() == 0);
        CPPUNIT_ASSERT(totalBallotCount == 0);
    }

    void test_read_3 () {
        std::istringstream r("1\n;alskjf;lksj;af\n1\n1\n");
        vector<Candidate> candidates;
        map<string, int> allBallots;
        int totalBallotCount = 0;
        voting_read(r, candidates, allBallots, totalBallotCount);

        CPPUNIT_ASSERT(candidates.size() == 1);
        CPPUNIT_ASSERT(candidates[0].getName() == ";alskjf;lksj;af");

        CPPUNIT_ASSERT(allBallots.size() == 1);
        CPPUNIT_ASSERT(allBallots["1"] == 2);
        CPPUNIT_ASSERT(totalBallotCount == 2);
    }

    // ------------------
    // getElectionResults
    // ------------------

    void test_getElectionResults_1 () {
    	vector<Candidate> candidates;
    	Candidate a("R");
    	Candidate b("G");
		  Candidate c("B");
		  Candidate d("O");
		  Candidate e("Y");
    	candidates.push_back(a);
    	candidates.push_back(b);
    	candidates.push_back(c);
    	candidates.push_back(d);
    	candidates.push_back(e);

    	map<string, int> allBallots;
    	int totalBallotCount = 0;

      vector<string> winners = voting_getElectionResults(candidates, allBallots, totalBallotCount);

      CPPUNIT_ASSERT(winners.size() == 5);
      CPPUNIT_ASSERT(winners[0] == "R");
      CPPUNIT_ASSERT(winners[1] == "G");
      CPPUNIT_ASSERT(winners[2] == "B");
      CPPUNIT_ASSERT(winners[3] == "O");
      CPPUNIT_ASSERT(winners[4] == "Y");
    }

    void test_getElectionResults_2 () {
       vector<Candidate> candidates;
       Candidate a("John Doe");
       Candidate b("Jane Smith");
       Candidate c("Sirhan Sirhan");
       Candidate d("Elizabeth Taylor");
       candidates.push_back(a); 
       candidates.push_back(b);
       candidates.push_back(c);
       candidates.push_back(d);

       map<string, int> allBallots;
       allBallots["1 2 3 4"] = 1;
       allBallots["2 3 4 1"] = 1;
       allBallots["3 4 1 2"] = 1;
       allBallots["4 3 2 1"] = 1;
       int totalBallotCount = 4;

  	   vector<string> winners = voting_getElectionResults(candidates, allBallots, totalBallotCount);
  	   CPPUNIT_ASSERT(winners.size() == 4);
  	   CPPUNIT_ASSERT(winners[0] == "John Doe");
  	   CPPUNIT_ASSERT(winners[1] == "Jane Smith");
  	   CPPUNIT_ASSERT(winners[2] == "Sirhan Sirhan");
  	   CPPUNIT_ASSERT(winners[3] == "Elizabeth Taylor");
    }

    void test_getElectionResults_3 () {
       vector<Candidate> candidates;
       Candidate a("\"\"");
       Candidate b("\'\'");
       Candidate c("[]");
       Candidate d("()");
       Candidate e("&&");
       candidates.push_back(a);
       candidates.push_back(b);
       candidates.push_back(c);
       candidates.push_back(d);
       candidates.push_back(e);

       map<string, int> allBallots;
       allBallots["5 4 3 2 1"] = 1;
       allBallots["1 3 2 4 5"] = 1;
       allBallots["1 2 3 4 5"] = 1;
       allBallots["4 5 2 3 1"] = 2;
       allBallots["2 4 5 1 3"] = 1;
       allBallots["1 5 2 3 4"] = 1;
       allBallots["3 5 4 2 1"] = 1;
       allBallots["3 1 2 4 5"] = 1;
       allBallots["5 1 4 2 3"] = 1;
       int totalBallotCount = 10;

       vector<string> winners = voting_getElectionResults(candidates, allBallots, totalBallotCount);
	     CPPUNIT_ASSERT(winners.size() == 2);
	     CPPUNIT_ASSERT(winners[0] == "\"\"");
	     CPPUNIT_ASSERT(winners[1] == "()");
   }

   void test_getElectionResults_4 () {
   	   vector<Candidate> candidates;
       Candidate a("John Doe");
       Candidate b("Jane Smith");
       Candidate c("Sirhan Sirhan");
       candidates.push_back(a);
       candidates.push_back(b);
       candidates.push_back(c);

       map<string, int> allBallots;
       allBallots["1 2 3"] = 2;
       allBallots["2 1 3"] = 1;
       allBallots["2 3 1"] = 1;
       allBallots["3 1 2"] = 1;
       int totalBallotCount = 5;

       vector<string> winners = voting_getElectionResults(candidates, allBallots, totalBallotCount);
	     CPPUNIT_ASSERT(winners.size() == 1);
	     CPPUNIT_ASSERT(winners[0] == "John Doe");
	}

  	// ---------------
      // votesSubmitted
      // ---------------

  	void test_noBallots_1 () {
  		vector<Candidate> candidates;
      Candidate a("R");
      Candidate b("G");
  	  Candidate c("B");
  		Candidate d("O");
  		Candidate e("Y");
      candidates.push_back(a);
      candidates.push_back(b);
      candidates.push_back(c);
      candidates.push_back(d);
      candidates.push_back(e);

      map<string, int> allBallots;

      vector<string> winners;

      const bool noballots = noBallots(allBallots, candidates, winners);

      CPPUNIT_ASSERT(winners.size() == 5);
      CPPUNIT_ASSERT(winners[0] == "R");
      CPPUNIT_ASSERT(winners[1] == "G");
      CPPUNIT_ASSERT(winners[2] == "B");
      CPPUNIT_ASSERT(winners[3] == "O");
      CPPUNIT_ASSERT(winners[4] == "Y");

      CPPUNIT_ASSERT(noballots == true);
    }

  	void test_noBallots_2 () {
  	   vector<Candidate> candidates;
       Candidate a("\"\"");
       Candidate b("\'\'");
       Candidate c("[]");
       Candidate d("()");
       Candidate e("&&");
       candidates.push_back(a);
       candidates.push_back(b);
       candidates.push_back(c);
       candidates.push_back(d);
       candidates.push_back(e);

       map<string, int> allBallots;
       allBallots["5 4 3 2 1"] = 1;
       allBallots["1 3 2 4 5"] = 1;
       allBallots["1 2 3 4 5"] = 1;
       allBallots["4 5 2 3 1"] = 2;
       allBallots["2 4 5 1 3"] = 1;
       allBallots["1 5 2 3 4"] = 1;
       allBallots["3 5 4 2 1"] = 1;
       allBallots["3 1 2 4 5"] = 1;
       allBallots["5 1 4 2 3"] = 1;

       vector<string> winners;

       const bool noballots = noBallots(allBallots, candidates, winners);

  	   CPPUNIT_ASSERT(winners.size() == 0);
  	   CPPUNIT_ASSERT(noballots == false);
  	}

  	void test_noBallots_3 () {
  	   vector<Candidate> candidates;
       Candidate a("John Doe");
       Candidate b("Jane Smith");
       Candidate c("Sirhan Sirhan");
       candidates.push_back(a);
       candidates.push_back(b);
       candidates.push_back(c);

       map<string, int> allBallots;
       allBallots["1 2 3"] = 2;
       allBallots["2 1 3"] = 1;
       allBallots["2 3 1"] = 1;
       allBallots["3 1 2"] = 1;

       vector<string> winners;

       const bool noballots = noBallots(allBallots, candidates, winners);

  	   CPPUNIT_ASSERT(winners.size() == 0);
  	   CPPUNIT_ASSERT(noballots == false);
  	}

      // --------------
      // assign_ballots
      // --------------

    void test_assign_ballots_1() {
        vector<Candidate> candidates;
        Candidate a("\"\"");
        Candidate b("\'\'");
        Candidate c("[]");
        Candidate d("()");
        Candidate e("&&");
        candidates.push_back(a);
        candidates.push_back(b);
        candidates.push_back(c);
        candidates.push_back(d);
        candidates.push_back(e);

        map<string, int> allBallots;
        allBallots["5 4 3 2 1"] = 1;
        allBallots["1 3 2 4 5"] = 1;
        allBallots["1 2 3 4 5"] = 1;
        allBallots["4 5 2 3 1"] = 2;
        allBallots["2 4 5 1 3"] = 1;
        allBallots["1 5 2 3 4"] = 1;
        allBallots["3 5 4 2 1"] = 1;
        allBallots["3 1 2 4 5"] = 1;
        allBallots["5 1 4 2 3"] = 1;

        assign_ballots(candidates, allBallots);

        CPPUNIT_ASSERT(candidates[0].getVoteCount() == 3);
        CPPUNIT_ASSERT(candidates[1].getVoteCount() == 1);
        CPPUNIT_ASSERT(candidates[2].getVoteCount() == 2);
        CPPUNIT_ASSERT(candidates[3].getVoteCount() == 2);
        CPPUNIT_ASSERT(candidates[4].getVoteCount() == 2);

        CPPUNIT_ASSERT(candidates[0].getBallots()["1 3 2 4 5"] == 1);
        CPPUNIT_ASSERT(candidates[0].getBallots()["1 3 2 4 5"] == 1);
        CPPUNIT_ASSERT(candidates[0].getBallots()["1 5 2 3 4"] == 1);

        CPPUNIT_ASSERT(candidates[1].getBallots()["2 4 5 1 3"] == 1);

        CPPUNIT_ASSERT(candidates[2].getBallots()["3 5 4 2 1"] == 1);
        CPPUNIT_ASSERT(candidates[2].getBallots()["3 1 2 4 5"] == 1);

        CPPUNIT_ASSERT(candidates[3].getBallots()["4 5 2 3 1"] == 2);

        CPPUNIT_ASSERT(candidates[4].getBallots()["5 4 3 2 1"] == 1);
        CPPUNIT_ASSERT(candidates[4].getBallots()["5 1 4 2 3"] == 1);
    }

    void test_assign_ballots_2() {
      vector<Candidate> candidates;
      Candidate a("John Doe");
      Candidate b("Jane Smith");
      Candidate c("Sirhan Sirhan");
      candidates.push_back(a);
      candidates.push_back(b);
      candidates.push_back(c);

      map<string, int> allBallots;
      allBallots["1 2 3"] = 2;
      allBallots["2 1 3"] = 1;
      allBallots["2 3 1"] = 1;
      allBallots["3 1 2"] = 1;

      assign_ballots(candidates, allBallots);

      CPPUNIT_ASSERT(candidates[0].getVoteCount() == 2);
      CPPUNIT_ASSERT(candidates[1].getVoteCount() == 2);
      CPPUNIT_ASSERT(candidates[2].getVoteCount() == 1);

      CPPUNIT_ASSERT(candidates[0].getBallots()["1 2 3"] == 2);
      CPPUNIT_ASSERT(candidates[1].getBallots()["2 1 3"] == 1);
      CPPUNIT_ASSERT(candidates[1].getBallots()["2 3 1"] == 1);
      CPPUNIT_ASSERT(candidates[2].getBallots()["3 1 2"] == 1);
    }

      // ------------------------
      // init_remainingCandidates
      //-------------------------   

    void test_init_remainingCandidates_1() {
        vector<Candidate> candidates;
        Candidate a("\"\"");
        Candidate b("[]");
        b.setEliminated(true);
        Candidate c("()");
        Candidate d("&&");
        d.setEliminated(true);
        candidates.push_back(a);
        candidates.push_back(b);
        candidates.push_back(c);
        candidates.push_back(d);

        vector<Candidate> remainingCandidates = init_remainingCandidates(candidates);

        CPPUNIT_ASSERT(remainingCandidates.size() == 2);
        CPPUNIT_ASSERT(remainingCandidates[0].getName() == "\"\"");
        CPPUNIT_ASSERT(remainingCandidates[1].getName() == "()");
    }

    void test_init_remainingCandidates_2 () {
      vector<Candidate> candidates;
      Candidate a("John Doe");
      Candidate b("Jane Smith");
      Candidate c("Sirhan Sirhan");  
      candidates.push_back(a);
      candidates.push_back(b);
      candidates.push_back(c);


      vector<Candidate> remainingCandidates = init_remainingCandidates(candidates);

      CPPUNIT_ASSERT(remainingCandidates.size() == 3);
      CPPUNIT_ASSERT(remainingCandidates[0].getName() == "John Doe");
      CPPUNIT_ASSERT(remainingCandidates[1].getName() == "Jane Smith");
      CPPUNIT_ASSERT(remainingCandidates[2].getName() == "Sirhan Sirhan");
    }


      // ----------
      // check_tie
      // ----------

    void test_check_tie_1 () {
       vector<Candidate> candidates;
       Candidate a("\"\"");
       Candidate b("()");
       a.addVotes(5);
       b.addVotes(5);
       candidates.push_back(a);
       candidates.push_back(b);

       vector<string> winners;
       const bool tieFound = check_tie(candidates, winners);

       CPPUNIT_ASSERT(tieFound == true);
       CPPUNIT_ASSERT(winners.size() == 2);
       CPPUNIT_ASSERT(winners[0] == "\"\"");
       CPPUNIT_ASSERT(winners[1] == "()");
    }

    void test_check_tie_2 () {
       vector<Candidate> candidates;
       Candidate a("John Doe");
       Candidate b("Jane Smith");
       Candidate c("Sirhan Sirhan");
       a.addVotes(2);
       b.addVotes(2);
       c.addVotes(1);  
       candidates.push_back(a);
       candidates.push_back(b);
       candidates.push_back(c);

       vector<string> winners;
       const bool tieFound = check_tie(candidates, winners);

       CPPUNIT_ASSERT(tieFound == false);
       CPPUNIT_ASSERT(winners.size() == 0);
    } 

    void test_check_winner_1 () {
       vector<Candidate> candidates;
       Candidate a("John Doe");
       Candidate b("Jane Smith");
       Candidate c("Sirhan Sirhan");
       a.addVotes(2);
       b.addVotes(2);
       c.addVotes(1);  
       candidates.push_back(a);
       candidates.push_back(b);
       candidates.push_back(c);

       int totalBallotCount = 5;
       vector<string> winners;
       bool winnerFound = check_winner(candidates, winners, totalBallotCount);

       CPPUNIT_ASSERT(winnerFound == false);
       CPPUNIT_ASSERT(winners.size() == 0);
    }

    void test_check_winner_2 () {
       vector<Candidate> candidates;
       Candidate a("John Doe");
       Candidate b("Jane Smith");
       a.addVotes(3);
       b.addVotes(2);  
       candidates.push_back(a);
       candidates.push_back(b);

       int totalBallotCount = 5;
       vector<string> winners;
       bool winnerFound = check_winner(candidates, winners, totalBallotCount);

       CPPUNIT_ASSERT(winnerFound == true);
       CPPUNIT_ASSERT(winners.size() == 1);
       CPPUNIT_ASSERT(winners[0] == "John Doe");
    }

    void test_eliminate_candidates_1 () {
        vector<Candidate> candidates;
        Candidate a("\"\"");
        Candidate b("[]");
        Candidate c("()");
        Candidate d("&&");
        a.addVotes(3);
        b.addVotes(2);
        c.addVotes(3);
        d.addVotes(2);
        candidates.push_back(a);
        candidates.push_back(b);
        candidates.push_back(c);
        candidates.push_back(d);

        vector<Candidate> remainingCandidates = candidates;

        eliminate_candidates(candidates, remainingCandidates);

        CPPUNIT_ASSERT(candidates[0].isEliminated() == false);
        CPPUNIT_ASSERT(candidates[1].isEliminated() == true);
        CPPUNIT_ASSERT(candidates[2].isEliminated() == false);
        CPPUNIT_ASSERT(candidates[3].isEliminated() == true);
    }

    void test_eliminate_candidates_2 () {
       vector<Candidate> candidates;
       Candidate a("John Doe");
       Candidate b("Jane Smith");
       Candidate c("Sirhan Sirhan");
       a.addVotes(2);
       b.addVotes(2);
       c.addVotes(1);  
       candidates.push_back(a);
       candidates.push_back(b);
       candidates.push_back(c);

       vector<Candidate> remainingCandidates = candidates;

       eliminate_candidates(candidates, remainingCandidates);

       CPPUNIT_ASSERT(candidates[0].isEliminated() == false);
       CPPUNIT_ASSERT(candidates[1].isEliminated() == false);
       CPPUNIT_ASSERT(candidates[2].isEliminated() == true);
    }

    void test_reassign_ballots_1() {
       vector<Candidate> candidates;
       Candidate a("\"\"");
       Candidate b("\'\'");
       Candidate c("[]");
       Candidate d("()");
       Candidate e("&&");
       a.addVotes(3);
       c.addVotes(2);
       d.addVotes(3);
       e.addVotes(2);
       b.setEliminated(true);
       c.setEliminated(true);
       e.setEliminated(true);
       a.addBallotBucket("1 3 2 4 5", 1);
       a.addBallotBucket("1 2 3 4 5", 1);
       a.addBallotBucket("1 5 2 3 4", 1);
       c.addBallotBucket("3 5 4 2 1", 1);
       c.addBallotBucket("3 1 2 4 5", 1);
       d.addBallotBucket("4 5 2 3 1", 2);
       d.addBallotBucket("2 4 5 1 3", 1);
       e.addBallotBucket("5 4 3 2 1", 1);
       e.addBallotBucket("5 1 4 2 3", 1);
       candidates.push_back(a);
       candidates.push_back(b);
       candidates.push_back(c);
       candidates.push_back(d);
       candidates.push_back(e);     

       reassign_ballots(candidates);

       CPPUNIT_ASSERT(candidates[0].getVoteCount() == 5);
       CPPUNIT_ASSERT(candidates[3].getVoteCount() == 5);
       CPPUNIT_ASSERT(candidates[2].getVoteCount() == 0);
       CPPUNIT_ASSERT(candidates[4].getVoteCount() == 0);

       CPPUNIT_ASSERT(candidates[0].getBallots()["3 1 2 4 5"] == 1);
       CPPUNIT_ASSERT(candidates[0].getBallots()["5 1 4 2 3"] == 1);
       CPPUNIT_ASSERT(candidates[3].getBallots()["3 5 4 2 1"] == 1);
       CPPUNIT_ASSERT(candidates[3].getBallots()["5 4 3 2 1"] == 1);

       CPPUNIT_ASSERT(candidates[2].getBallots().size() == 0);
       CPPUNIT_ASSERT(candidates[4].getBallots().size() == 0);
    }

    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        vector<string> winners;
        winners.push_back("alskjf;lksj;af");
        voting_print(w, winners);
        CPPUNIT_ASSERT(w.str() == "alskjf;lksj;af\n");
    }

    void test_print_2 () {
        std::ostringstream w;
        vector<string> winners;
        winners.push_back("\"\"");
        winners.push_back("()");
        voting_print(w, winners);
        CPPUNIT_ASSERT(w.str() == "\"\"\n()\n");
    }

     void test_print_3 () {
        std::ostringstream w;
        vector<string> winners;
        winners.push_back("John Doe");
        winners.push_back("Sirhan Sirhan");
		winners.push_back("Jane Smith");
        voting_print(w, winners);
        CPPUNIT_ASSERT(w.str() == "John Doe\nSirhan Sirhan\nJane Smith\n");
    }

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1\n\n4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Red\nGreen\n");
    }    

    void test_solve_2 () {
        std::istringstream r("2\n\n5\nR\nG\nB\nO\nY\n\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\nElizabeth Taylor\n4 3 2 1\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "R\nG\nB\nO\nY\n\nElizabeth Taylor\n");
    }

    void test_solve_3 () {
        std::istringstream r("2\n\n1\nhello\n1\n1\n1\n\n5\nR\nG\nB\nO\nY\n1 2 3 4 5\n1 2 3 4 5\n1 2 3 4 5\n1 2 3 4 5\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "hello\n\nR\n");
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_Candidate_constructor_1);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_getElectionResults_1);
    CPPUNIT_TEST(test_getElectionResults_2);
    CPPUNIT_TEST(test_getElectionResults_3);
    CPPUNIT_TEST(test_getElectionResults_4);
    CPPUNIT_TEST(test_noBallots_1);
    CPPUNIT_TEST(test_noBallots_2);
    CPPUNIT_TEST(test_noBallots_3);
    CPPUNIT_TEST(test_assign_ballots_1);
    CPPUNIT_TEST(test_assign_ballots_2);
    CPPUNIT_TEST(test_init_remainingCandidates_1);
    CPPUNIT_TEST(test_init_remainingCandidates_2);
    CPPUNIT_TEST(test_check_tie_1);
    CPPUNIT_TEST(test_check_tie_2);
    CPPUNIT_TEST(test_check_winner_1);
    CPPUNIT_TEST(test_check_winner_2);
    CPPUNIT_TEST(test_eliminate_candidates_1);
    CPPUNIT_TEST(test_eliminate_candidates_2);
    CPPUNIT_TEST(test_reassign_ballots_1);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST_SUITE_END();};

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}