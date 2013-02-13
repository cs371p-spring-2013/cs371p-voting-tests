// --------
// includes
// --------

#include <iostream>
#include <sstream>
#include <string>

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"

#include "Voting.h"

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture
{
  // -------------------- //
  // Ballot class methods //
  // -------------------- //

  // -------------------
  // default constructor
  // -------------------

  void ballotDefault ()
  {
    Ballot thisBallot;
    int size = thisBallot.size ();
    CPPUNIT_ASSERT (size == 0);
  }

  // --------------------
  // explicit constructor
  // --------------------

  // ----
  // size
  // ----  

  void ballotExplicit1 ()
  {
    vector <int> someVotes {1};
    Ballot thisBallot (someVotes);
    int size = thisBallot.size ();
    CPPUNIT_ASSERT (size == 1);
  }

  void ballotExplicit2 ()
  {
    vector <int> someVotes {1, 2, 3};
    Ballot thisBallot (someVotes);
    int size = thisBallot.size ();
    CPPUNIT_ASSERT (size == 3);
  }

  void ballotExplicit3 ()
  {
    vector <int> someVotes {1, 2, 3, 4, 5};
    Ballot thisBallot (someVotes);
    int size = thisBallot.size ();
    CPPUNIT_ASSERT (size == 5);
  }

  // -------
  // getVote
  // -------

  void ballotGetVote1 ()
  {
    vector <int> someVotes {1};
    Ballot thisBallot (someVotes);
    int vote = thisBallot.getVote ();
    CPPUNIT_ASSERT (vote == 1);
  }

  void ballotGetVote2 ()
  {
    vector <int> someVotes {1, 2, 3};
    Ballot thisBallot (someVotes);
    int vote = thisBallot.getVote ();
    vote = thisBallot.getVote ();
    CPPUNIT_ASSERT (vote == 2);
  }

  void ballotGetVote3 ()
  {
    vector <int> someVotes {1, 2, 3, 4, 5};
    Ballot thisBallot (someVotes);
    int vote = thisBallot.getVote ();
    vote = thisBallot.getVote ();
    vote = thisBallot.getVote ();
    vote = thisBallot.getVote ();
    CPPUNIT_ASSERT (vote == 4);
  }

  // ---------------------- //
  // Candiate class methods //
  // ---------------------- //

  // -------------------
  // default constructor
  // -------------------

  void candidateDefault ()
  {
    Candidate thisCandidate;
    string name = thisCandidate.getName ();
    CPPUNIT_ASSERT (name == "");
  }

  // --------------------
  // explicit constructor
  // --------------------

  // -------
  // getName
  // -------

  // --------
  // getVotes
  // --------

  void candidateExplicit1 ()
  {
    Candidate thisCandidate ("John Doe");
    string name = thisCandidate.getName ();
    int votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (name == "John Doe");
    CPPUNIT_ASSERT (votes == 0);
  }

  void candidateExplicit2 ()
  {
    Candidate thisCandidate ("Jane Smith");
    string name = thisCandidate.getName ();
    int votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (name == "Jane Smith");
    CPPUNIT_ASSERT (votes == 0);
  }

  void candidateExplicit3 ()
  {
    Candidate thisCandidate ("Sirhan Sirhan");
    string name = thisCandidate.getName ();
    int votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (name == "Sirhan Sirhan");
    CPPUNIT_ASSERT (votes == 0);
  }

  // -------
  // addVote
  // -------

  // --------
  // getVotes
  // --------

  // ----------
  // getBallots
  // ----------

  void candidateAddVote1 ()
  {
    Candidate thisCandidate ("John Doe");
    int votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 0);
    vector <int> someVotes {1};
    Ballot thisBallot (someVotes);
    thisCandidate.addVote (thisBallot);
    votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 1);
    vector <Ballot> myBallots = thisCandidate.getBallots ();
    int size = myBallots.size ();
    CPPUNIT_ASSERT (size == 1);
  }

  void candidateAddVote2 ()
  {
    Candidate thisCandidate ("John Doe");
    int votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 0);
    vector <int> someVotes {1, 2, 3};
    Ballot thisBallot (someVotes);
    thisCandidate.addVote (thisBallot);
    votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 1);
    vector <int> moreVotes {2, 1, 3};
    Ballot anotherBallot (moreVotes);
    thisCandidate.addVote (anotherBallot);
    votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 2);
    vector <Ballot> myBallots = thisCandidate.getBallots ();
    int size = myBallots.size ();
    CPPUNIT_ASSERT (size == 2);
  }

  void candidateAddVote3 ()
  {
    Candidate thisCandidate ("John Doe");
    int votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 0);
    vector <int> someVotes {1, 2, 3};
    Ballot thisBallot (someVotes);
    thisCandidate.addVote (thisBallot);
    votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 1);
    vector <int> moreVotes {2, 1, 3};
    Ballot anotherBallot (moreVotes);
    thisCandidate.addVote (anotherBallot);
    votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 2);
    vector <int> lastVotes {3, 2, 1};
    Ballot lastBallot (lastVotes);
    thisCandidate.addVote (lastBallot);
    votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 3);
    vector <Ballot> myBallots = thisCandidate.getBallots ();
    int size = myBallots.size ();
    CPPUNIT_ASSERT (size == 3);
  }

  // ----------
  // removeVote
  // ----------

  // --------
  // getVotes
  // --------

  // ----------
  // getBallots
  // ----------

  void candidateRemoveVote1 ()
  {
    Candidate thisCandidate ("John Doe");
    int votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 0);
    vector <int> someVotes {1};
    Ballot thisBallot (someVotes);
    thisCandidate.addVote (thisBallot);
    votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 1);
    vector <Ballot> myBallots = thisCandidate.getBallots ();
    int size = myBallots.size ();
    CPPUNIT_ASSERT (size == 1);
    thisCandidate.removeVote ();
    votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 0);
    myBallots = thisCandidate.getBallots ();
    size = myBallots.size ();
    CPPUNIT_ASSERT (size == 0);
  }

  void candidateRemoveVote2 ()
  {
    Candidate thisCandidate ("John Doe");
    int votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 0);
    vector <int> someVotes {1, 2, 3};
    Ballot thisBallot (someVotes);
    thisCandidate.addVote (thisBallot);
    votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 1);
    vector <int> moreVotes {2, 1, 3};
    Ballot anotherBallot (moreVotes);
    thisCandidate.addVote (anotherBallot);
    votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 2);
    vector <Ballot> myBallots = thisCandidate.getBallots ();
    int size = myBallots.size ();
    CPPUNIT_ASSERT (size == 2);
    thisCandidate.removeVote ();
    votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 1);
    myBallots = thisCandidate.getBallots ();
    size = myBallots.size ();
    CPPUNIT_ASSERT (size == 1);
  }

  void candidateRemoveVote3 ()
  {
    Candidate thisCandidate ("John Doe");
    int votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 0);
    vector <int> someVotes {1, 2, 3};
    Ballot thisBallot (someVotes);
    thisCandidate.addVote (thisBallot);
    votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 1);
    vector <int> moreVotes {2, 1, 3};
    Ballot anotherBallot (moreVotes);
    thisCandidate.addVote (anotherBallot);
    votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 2);
    vector <int> lastVotes {3, 2, 1};
    Ballot lastBallot (lastVotes);
    thisCandidate.addVote (lastBallot);
    votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 3);
    vector <Ballot> myBallots = thisCandidate.getBallots ();
    int size = myBallots.size ();
    CPPUNIT_ASSERT (size == 3);
    thisCandidate.removeVote ();
    votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 2);
    myBallots = thisCandidate.getBallots ();
    size = myBallots.size ();
    CPPUNIT_ASSERT (size == 2);
    thisCandidate.removeVote ();
    votes = thisCandidate.getVotes ();
    CPPUNIT_ASSERT (votes == 1);
    myBallots = thisCandidate.getBallots ();
    size = myBallots.size ();
    CPPUNIT_ASSERT (size == 1);
  }

  // --------------------------------
  // outstream << operator overloader
  // --------------------------------

  void candidateToString1 ()
  {
    Candidate thisCandidate;
    ostringstream testStream;
    testStream << thisCandidate;
    CPPUNIT_ASSERT (testStream.str () == "\n");
  }

  void candidateToString2 ()
  {
    Candidate thisCandidate ("John Doe");
    ostringstream testStream;
    testStream << thisCandidate;
    CPPUNIT_ASSERT (testStream.str () == "John Doe\n");
  }

  void candidateToString3 ()
  {
    Candidate thisCandidate ("Sirhan Sirhan");
    ostringstream testStream;
    testStream << thisCandidate;
    CPPUNIT_ASSERT (testStream.str () == "Sirhan Sirhan\n");
  }

  // -------------
  // getCandidates
  // -------------

  void getCandidates1 ()
  {
    istringstream testStream ("1\nCandidate #1");
    vector <Candidate> candidates = getCandidates (testStream);
    CPPUNIT_ASSERT (candidates.size () == 1);
  }

  void getCandidates2 ()
  {
    istringstream testStream ("3\nCandidate #1\nCandidate #2\nCandidate #3");
    vector <Candidate> candidates = getCandidates (testStream);
    CPPUNIT_ASSERT (candidates.size () == 3);
  }

  void getCandidates3 ()
  {
    istringstream testStream ("4\nCandidate #1\nCandidate #2\nCandidate #3\nCandidate #4");
    vector <Candidate> candidates = getCandidates (testStream);
    CPPUNIT_ASSERT (candidates.size () == 4);
  }

  // ----------
  // getBallots
  // ----------

  void getBallots1 ()
  {
    istringstream testStream ("1 2 3 4");
    vector <Ballot> ballots = getBallots (testStream);
    CPPUNIT_ASSERT (ballots.size () == 1);
  }

  void getBallots2 ()
  {
    istringstream testStream ("1 2 3 4\n2 3 1 4");
    vector <Ballot> ballots = getBallots (testStream);
    CPPUNIT_ASSERT (ballots.size () == 2);
  }

  void getBallots3 ()
  {
    istringstream testStream ("1 2 3 4\n2 3 1 4\n1 2 3 4");
    vector <Ballot> ballots = getBallots (testStream);
    CPPUNIT_ASSERT (ballots.size () == 3);
  }

  // ---------
  // getBallot
  // ---------

  void getBallot1 ()
  {
    string votes = "1";
    Ballot aBallot = getBallot (votes);
    CPPUNIT_ASSERT (aBallot.size () == 1);
  }

  void getBallot2 ()
  {
    string votes = "1 2 3";
    Ballot aBallot = getBallot (votes);
    CPPUNIT_ASSERT (aBallot.size () == 3);
  }

  void getBallot3 ()
  {
    string votes = "1 2 3 4 5";
    Ballot aBallot = getBallot (votes);
    CPPUNIT_ASSERT (aBallot.size () == 5);
  }

  // -----
  // elect
  // -----

  void elect1 ()
  {
    istringstream candidateStream ("1\nCandidate #1");
    vector <Candidate> candidates = getCandidates (candidateStream);
    istringstream ballotStream ("1");
    vector <Ballot> ballots = getBallots (ballotStream);
    vector <Candidate> winners = elect (candidates, ballots);
    CPPUNIT_ASSERT (winners.size () == 1);
    ostringstream winnerStream;
    winnerStream << winners [0];
    CPPUNIT_ASSERT (winnerStream.str () == "Candidate #1\n");
  }

  void elect2 ()
  {
    istringstream candidateStream ("3\nCandidate #1\nCandidate #2\nCandidate #3");
    vector <Candidate> candidates = getCandidates (candidateStream);
    istringstream ballotStream ("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    vector <Ballot> ballots = getBallots (ballotStream);
    vector <Candidate> winners = elect (candidates, ballots);
    CPPUNIT_ASSERT (winners.size () == 1);
    ostringstream winnerStream;
    winnerStream << winners [0];
    CPPUNIT_ASSERT (winnerStream.str () == "Candidate #1\n");
  }

  void elect3 ()
  {
    istringstream candidateStream ("4\nCandidate #1\nCandidate #2\nCandidate #3\nCandidate #4");
    vector <Candidate> candidates = getCandidates (candidateStream);
    istringstream ballotStream ("1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
    vector <Ballot> ballots = getBallots (ballotStream);
    vector <Candidate> winners = elect (candidates, ballots);
    CPPUNIT_ASSERT (winners.size () == 2);
    ostringstream winnerStream;
    winnerStream << winners [0] << winners [1];
    CPPUNIT_ASSERT (winnerStream.str () == "Candidate #1\nCandidate #2\n");
  }

  // ------
  // report
  // ------

  void report1 ()
  {
    ostringstream testStream;
    istringstream candidateStream ("1\nCandidate #1");
    vector <Candidate> candidates = getCandidates (candidateStream);
    report (testStream, candidates);
    CPPUNIT_ASSERT (testStream.str () == "Candidate #1\n");
  }

  void report2 ()
  {
    ostringstream testStream;
    istringstream candidateStream ("3\nCandidate #1\nCandidate #2\nCandidate #3");
    vector <Candidate> candidates = getCandidates (candidateStream);
    report (testStream, candidates);
    CPPUNIT_ASSERT (testStream.str () == "Candidate #1\nCandidate #2\nCandidate #3\n");
  }

  void report3 ()
  {
    ostringstream testStream;
    istringstream candidateStream ("4\nCandidate #1\nCandidate #2\nCandidate #3\nCandidate #4");
    vector <Candidate> candidates = getCandidates (candidateStream);
    report (testStream, candidates);
    CPPUNIT_ASSERT (testStream.str () == "Candidate #1\nCandidate #2\nCandidate #3\nCandidate #4\n");
  }

  // -------------
  // runElections
  // -------------

  void runElections1 ()
  {
    istringstream inStream ("1\n\n1\nCandidate #1\n1\n");
    ostringstream outStream;
    runElections (inStream, outStream);
    CPPUNIT_ASSERT (outStream.str () == "Candidate #1\n");
  }

  void runElections2 ()
  {
    istringstream inStream ("1\n\n3\nCandidate #1\nCandidate #2\nCandidate #3\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    ostringstream outStream;
    runElections (inStream, outStream);
    CPPUNIT_ASSERT (outStream.str () == "Candidate #1\n");
  }

  void runElections3 ()
  {
    istringstream inStream ("2\n\n3\nCandidate #1\nCandidate #2\nCandidate #3\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n4\nCandidate #1\nCandidate #2\nCandidate #3\nCandidate #4\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
    ostringstream outStream;
    runElections (inStream, outStream);
    CPPUNIT_ASSERT (outStream.str () == "Candidate #1\n\nCandidate #1\nCandidate #2\n");
  }

  // -----
  // suite
  // -----

  CPPUNIT_TEST_SUITE (TestVoting);
  CPPUNIT_TEST (ballotDefault);
  CPPUNIT_TEST (ballotExplicit1);
  CPPUNIT_TEST (ballotExplicit2);
  CPPUNIT_TEST (ballotExplicit3);
  CPPUNIT_TEST (ballotGetVote1);
  CPPUNIT_TEST (ballotGetVote2);
  CPPUNIT_TEST (ballotGetVote3);
  CPPUNIT_TEST (candidateDefault);
  CPPUNIT_TEST (candidateExplicit1);
  CPPUNIT_TEST (candidateExplicit2);
  CPPUNIT_TEST (candidateExplicit3);
  CPPUNIT_TEST (candidateAddVote1);
  CPPUNIT_TEST (candidateAddVote2);
  CPPUNIT_TEST (candidateAddVote3);
  CPPUNIT_TEST (candidateRemoveVote1);
  CPPUNIT_TEST (candidateRemoveVote2);
  CPPUNIT_TEST (candidateRemoveVote3);
  CPPUNIT_TEST (candidateToString1);
  CPPUNIT_TEST (candidateToString2);
  CPPUNIT_TEST (candidateToString3);
  CPPUNIT_TEST (getCandidates1);
  CPPUNIT_TEST (getCandidates2);
  CPPUNIT_TEST (getCandidates3);
  CPPUNIT_TEST (getBallots1);
  CPPUNIT_TEST (getBallots2);
  CPPUNIT_TEST (getBallots3);
  CPPUNIT_TEST (getBallot1);
  CPPUNIT_TEST (getBallot2);
  CPPUNIT_TEST (getBallot3);
  CPPUNIT_TEST (elect1);
  CPPUNIT_TEST (elect2);
  CPPUNIT_TEST (elect3);
  CPPUNIT_TEST (report1);
  CPPUNIT_TEST (report2);
  CPPUNIT_TEST (report3);
  CPPUNIT_TEST (runElections1);
  CPPUNIT_TEST (runElections2);
  CPPUNIT_TEST (runElections3);
  CPPUNIT_TEST_SUITE_END ();
};

// ----
// main
// ----

int main ()
{
  using namespace std;
  ios_base::sync_with_stdio (false);
  cout << "TestVoting.c++" << endl;

  CppUnit::TextTestRunner testRunner;
  testRunner.addTest (TestVoting::suite ());
  testRunner.run ();

  cout << "Done." << endl;
  return 0;
}