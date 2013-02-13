#include <iostream>
#include <sstream>
#include <string>

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"

#include "Voting.h"


struct TestVoting : CppUnit::TestFixture {
    // voting_tests

    void test_voting_tests_1 ()
    {
        std::istringstream r("1\n");
        unsigned int n;
        n = voting_tests(r);
        CPPUNIT_ASSERT(n == 1);
    }

    void test_voting_tests_2 ()
    {
        std::istringstream r("10\n");
        unsigned int n;
        n = voting_tests(r);
        CPPUNIT_ASSERT(n == 10);
    }

    void test_voting_tests_3 ()
    {
        std::istringstream r("321\n");
        unsigned int n;
        n = voting_tests(r);
        CPPUNIT_ASSERT(n == 321);
    }

    // voting_candidates

    void test_voting_candidates_1 ()
    {
        std::istringstream r("3\n");
        unsigned int n;
        n = voting_candidates(r);
        CPPUNIT_ASSERT(n == 3);
    }

    void test_voting_candidates_2 ()
    {
        std::istringstream r("10\n");
        unsigned int n;
        n = voting_candidates(r);
        CPPUNIT_ASSERT(n == 10);
    }

    void test_voting_candidates_3 ()
    {
        std::istringstream r("20\n");
        unsigned int n;
        n = voting_candidates(r);
        CPPUNIT_ASSERT(n == 20);
    }

    // voting_candidates_names

    void test_voting_candidates_names ()
    {
        std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\n");
        std::vector<Candidate> names;
        voting_candidates_names(r, 3, names);
        CPPUNIT_ASSERT(names.at(0) == "John Doe");
        CPPUNIT_ASSERT(names.at(1) == "Jane Smith");
        CPPUNIT_ASSERT(names.at(2) == "Sirhan Sirhan");
    }

    void test_voting_candidates_names_2 ()
    {
        std::istringstream r("Bob Dole\nGeorge Washington\nAL GORE\nyo mama\n");
        std::vector<Candidate> names;
        voting_candidates_names(r, 4, names);
        CPPUNIT_ASSERT(names.at(0) == "Bob Dole");
        CPPUNIT_ASSERT(names.at(1) == "George Washington");
        CPPUNIT_ASSERT(names.at(2) == "AL GORE");
        CPPUNIT_ASSERT(names.at(3) == "yo mama");
    }

    void test_voting_candidates_names_3 ()
    {
        std::istringstream r("Very long name in which probably isn't really a name\n");
        std::vector<Candidate> names;
        voting_candidates_names(r, 1, names);
        CPPUNIT_ASSERT(names.at(0) == "Very long name in which probably isn't really a name");
    }

    // voting_ballots

    void test_voting_ballots ()
    {
        std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        std::vector<Ballot> ballots;
        std::vector<Candidate> names;
        voting_candidates_names(r, 3, names);
        voting_ballots(r, ballots, names);
        CPPUNIT_ASSERT(ballots.size() == 5);
        CPPUNIT_ASSERT(ballots.at(0).vote() == 1);
        CPPUNIT_ASSERT(ballots.at(1).vote() == 2);
        CPPUNIT_ASSERT(ballots.at(2).vote() == 2);
        CPPUNIT_ASSERT(ballots.at(3).vote() == 1);
        CPPUNIT_ASSERT(ballots.at(4).vote() == 3);
    }

    void test_voting_ballots_2 ()
    {
        std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\nBob Dole\nJohnny Flame\n1 2 3 4 5\n2 1 3 5 4\n4 5 2 3 1\n1 4 2 5 3\n4 3 1 2 5\n");
        std::vector<Ballot> ballots;
        std::vector<Candidate> names;
        voting_candidates_names(r, 5, names);
        voting_ballots(r, ballots, names);
        CPPUNIT_ASSERT(ballots.size() == 5);
        CPPUNIT_ASSERT(ballots.at(0).vote() == 1);
        CPPUNIT_ASSERT(ballots.at(1).vote() == 2);
        CPPUNIT_ASSERT(ballots.at(2).vote() == 4);
        CPPUNIT_ASSERT(ballots.at(3).vote() == 1);
        CPPUNIT_ASSERT(ballots.at(4).vote() == 4);
    }

    void test_voting_ballots_3 ()
    {
        std::istringstream r("Red\nGreen\n1 2\n2 1\n2 1\n1 2\n1 2");
        std::vector<Ballot> ballots;
        std::vector<Candidate> names;
        voting_candidates_names(r, 2, names);
        voting_ballots(r, ballots, names);
        CPPUNIT_ASSERT(ballots.size() == 5);
        CPPUNIT_ASSERT(ballots.at(0).vote() == 1);
        CPPUNIT_ASSERT(ballots.at(1).vote() == 2);
        CPPUNIT_ASSERT(ballots.at(2).vote() == 2);
        CPPUNIT_ASSERT(ballots.at(3).vote() == 1);
        CPPUNIT_ASSERT(ballots.at(4).vote() == 1);
    }

    // voting_eval

    void test_voting_eval ()
    {
        std::istringstream r("Red\nGreen\nBlue\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        std::vector<Candidate> candidates;
        std::vector<Ballot> ballots;
        voting_candidates_names(r, 3, candidates);
        voting_ballots(r, ballots, candidates);
        voting_eval(candidates, ballots.size());
        CPPUNIT_ASSERT(candidates.at(0).valid() == true);
        CPPUNIT_ASSERT(candidates.at(1).valid() == false);
        CPPUNIT_ASSERT(candidates.at(2).valid() == false);
    }

    void test_voting_eval_tie ()
    {
        std::istringstream r("Red\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
        std::vector<Candidate> candidates;
        std::vector<Ballot>    ballots;
        voting_candidates_names(r, 4, candidates);
        voting_ballots(r, ballots, candidates);
        voting_eval(candidates, ballots.size());
        CPPUNIT_ASSERT(candidates.at(0).valid() == true);
        CPPUNIT_ASSERT(candidates.at(1).valid() == true);
        CPPUNIT_ASSERT(candidates.at(2).valid() == false);
        CPPUNIT_ASSERT(candidates.at(3).valid() == false);
    }

    void test_voting_eval_tie_2 ()
    {
        std::istringstream r("Blue\nOrange\n1 2\n2 1");
        std::vector<Candidate> candidates;
        std::vector<Ballot>    ballots;
        voting_candidates_names(r, 2, candidates);
        voting_ballots(r, ballots, candidates);
        voting_eval(candidates, ballots.size());
        CPPUNIT_ASSERT(candidates.at(0).valid() == true);
        CPPUNIT_ASSERT(candidates.at(1).valid() == true);
    }

    // Ballot class

    void test_ballot_constructor ()
    {
        Ballot b;
        CPPUNIT_ASSERT(b.vote() == 0);
        CPPUNIT_ASSERT(b.len() == 0);
        CPPUNIT_ASSERT(b.next() == false);
    }

    void test_ballot_constructor_vector ()
    {
        std::vector<unsigned int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        Ballot b(v);
        CPPUNIT_ASSERT(b.len() == 3);
        CPPUNIT_ASSERT(b.vote() == 1);
        CPPUNIT_ASSERT(b.next() == true);
        CPPUNIT_ASSERT(b.vote() == 2);
    }

    void test_ballot_constructor_copy ()
    {
        std::vector<unsigned int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        Ballot b(v);
        Ballot c(b);
        CPPUNIT_ASSERT(c.len() == 3);
        CPPUNIT_ASSERT(c.vote() == 1);
        CPPUNIT_ASSERT(c.next() == true);
        CPPUNIT_ASSERT(c.vote() == 2);
    }

    void test_ballot_vote ()
    {
        std::vector<unsigned int> v;
        v.push_back(1);
        v.push_back(2);
        Ballot b(v);
        CPPUNIT_ASSERT(b.vote() == 1);
    }

    void test_ballot_next ()
    {
        std::vector<unsigned int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        Ballot b(v);
        CPPUNIT_ASSERT(b.next() == true);
        CPPUNIT_ASSERT(b.next() == true);
        CPPUNIT_ASSERT(b.next() == false);
        CPPUNIT_ASSERT(b.next() == false);
    }

    void test_ballot_len ()
    {
        std::vector<unsigned int> v;
        v.push_back(1);
        v.push_back(2);
        Ballot b(v);
        CPPUNIT_ASSERT(b.len() == 2);
        v.push_back(3);
        Ballot c(v);
        CPPUNIT_ASSERT(c.len() == 3);
    }

    // Candidate

    void test_candidate_constructor ()
    {
        std::string n("Bob Dole");
        Candidate c(n);
        CPPUNIT_ASSERT(c.name() == "Bob Dole");
    }

    void test_candidate_valid ()
    {
        std::string n("Bob Dole");
        Candidate c(n);
        CPPUNIT_ASSERT(c.valid());
        c.setLoser();
        CPPUNIT_ASSERT(c.valid() == false);
    }

    void test_candidate_addBallot ()
    {
        std::string n("Bob Dole");
        Candidate c(n);
        std::vector<unsigned int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        Ballot b(v);
        c.addBallot(b);
        CPPUNIT_ASSERT(c.votes() == 1);
        c.addBallot(b);
        CPPUNIT_ASSERT(c.votes() == 2);
    }

    void test_candidate_reassignVotes ()
    {
        std::vector<Candidate> cands;
        std::string n("Bob Dole");
        Candidate c1(n);
        n = "Al Gore";
        Candidate c2(n);
        cands.push_back(c1);
        cands.push_back(c2);

        std::vector<unsigned int> v;
        v.push_back(1);
        v.push_back(2);
        Ballot b1(v);
        v.clear();
        v.push_back(2);
        v.push_back(1);
        Ballot b2(v);

        cands[0].addBallot(b1);
        cands[1].addBallot(b2);

        cands[1].setLoser();

        cands[1].reassignVotes(cands);

        CPPUNIT_ASSERT(cands[0].votes() == 2);
    }

    // SUITE

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_voting_tests_1);
    CPPUNIT_TEST(test_voting_tests_2);
    CPPUNIT_TEST(test_voting_tests_3);
    CPPUNIT_TEST(test_voting_candidates_1);
    CPPUNIT_TEST(test_voting_candidates_2);
    CPPUNIT_TEST(test_voting_candidates_3);
    CPPUNIT_TEST(test_voting_candidates_names);
    CPPUNIT_TEST(test_voting_candidates_names_2);
    CPPUNIT_TEST(test_voting_candidates_names_3);
    CPPUNIT_TEST(test_voting_ballots);
    CPPUNIT_TEST(test_voting_ballots_2);
    CPPUNIT_TEST(test_voting_ballots_3);
    CPPUNIT_TEST(test_voting_eval);
    CPPUNIT_TEST(test_voting_eval_tie);
    CPPUNIT_TEST(test_voting_eval_tie_2);
    CPPUNIT_TEST(test_ballot_constructor);
    CPPUNIT_TEST(test_ballot_constructor_vector);
    CPPUNIT_TEST(test_ballot_constructor_copy);
    CPPUNIT_TEST(test_ballot_vote);
    CPPUNIT_TEST(test_ballot_next);
    CPPUNIT_TEST(test_ballot_len);
    CPPUNIT_TEST(test_candidate_constructor);
    CPPUNIT_TEST(test_candidate_valid);
    CPPUNIT_TEST(test_candidate_addBallot);
    CPPUNIT_TEST(test_candidate_reassignVotes);
    CPPUNIT_TEST_SUITE_END();
};

int main()
{
    using namespace std;
    ios_base::sync_with_stdio(false);
    cout << "TestVoting.c++\n";

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done.\n";
    return 0;
}
