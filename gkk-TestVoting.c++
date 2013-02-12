#include <iostream>
#include <sstream>

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"

#include "Voting.h"

using namespace std;


struct TestVoting : CppUnit::TestFixture
{
    void test_get_winners_1()
    {
        Election election;
        char names[][16] = { "MEAO", "VINCENT" };
        Candidate c1(names[0]);
        Candidate c2(names[1]);
        Ballot b[2];
        b[0].add(1);
        b[0].add(0);
        b[1].add(1);
        b[1].add(0);
        election.add(c1);
        election.add(c2);
        election.add(b[0]);
        election.add(b[1]);

        vector< Candidate > winners = election.get_winners();
        CPPUNIT_ASSERT(winners.size() == 1);
        CPPUNIT_ASSERT(strcmp(winners[0].get_name(), "VINCENT") == 0);
    }

    void test_get_winners_2()
    {
        Election election;
        char names[][16] = { "MEAO", "VINCENT" };
        Candidate c1(names[0]);
        Candidate c2(names[1]);
        Ballot b[2];
        b[0].add(1);
        b[0].add(0);
        b[1].add(0);
        b[1].add(1);
        election.add(c1);
        election.add(c2);
        election.add(b[0]);
        election.add(b[1]);

        vector< Candidate > winners = election.get_winners();
        CPPUNIT_ASSERT(winners.size() == 2);
        CPPUNIT_ASSERT(strcmp(winners[0].get_name(), "MEAO") == 0);
        CPPUNIT_ASSERT(strcmp(winners[1].get_name(), "VINCENT") == 0);
    }

    void test_get_winners_3()
    {
        Election election;
        char names[][16] = { "MEAO", "VINCENT", "SHARON" };
        Candidate c1(names[0]);
        Candidate c2(names[1]);
        Candidate c3(names[2]);
        Ballot b[5];
        b[0].add(2);
        b[0].add(1);
        b[0].add(0);
        b[1].add(2);
        b[1].add(1);
        b[1].add(0);
        b[2].add(1);
        b[2].add(0);
        b[2].add(2);
        b[3].add(1);
        b[3].add(0);
        b[3].add(2);
        b[4].add(0);
        b[4].add(2);
        b[4].add(1);

        election.add(c1);
        election.add(c2);
        election.add(c3);
        election.add(b[0]);
        election.add(b[1]);
        election.add(b[2]);
        election.add(b[3]);
        election.add(b[4]);

        vector< Candidate > winners = election.get_winners();
        CPPUNIT_ASSERT(winners.size() == 1);
        CPPUNIT_ASSERT(strcmp(winners[0].get_name(), "SHARON") == 0);
    }

    void test_solve_1()
    {
        istringstream i("2\nMEAO\nVINCENT\n1 2\n2 1\n");
        ostringstream o;
        voting_solve(i, o);
        CPPUNIT_ASSERT(o.str() == "MEAO\nVINCENT\n");
    }

    void test_solve_2()
    {
        istringstream i("2\nMEAO\nVINCENT\n2 1\n2 1\n");
        ostringstream o;
        voting_solve(i, o);
        CPPUNIT_ASSERT(o.str() == "VINCENT\n");
    }

    void test_solve_3()
    {
        istringstream i("3\nMEAO\nVINCENT\nSHARON\n3 2 1\n3 2 1\n2 1 3\n2 1 3\n1 3 2\n");
        ostringstream o;
        voting_solve(i, o);
        CPPUNIT_ASSERT(o.str() == "SHARON\n");
    }

    void test_solve_all_1()
    {
        istringstream i("1\n\n2\nMEAO\nVINCENT\n2 1\n");
        ostringstream o;
        voting_solve_all(i, o);
        CPPUNIT_ASSERT(o.str() == "VINCENT\n");
    }

    void test_solve_all_2()
    {
        istringstream i("2\n\n2\nMEAO\nVINCENT\n2 1\n\n2\nSHARON\nCORK\n1 2\n");
        ostringstream o;
        voting_solve_all(i, o);
        CPPUNIT_ASSERT(o.str() == "VINCENT\n\nSHARON\n");
    }

    void test_solve_all_3()
    {
        istringstream i("2\n\n2\nMEAO\nVINCENT\n2 1\n\n2\nSHARON\nCORK\n1 2\n2 1\n");
        ostringstream o;
        voting_solve_all(i, o);
        CPPUNIT_ASSERT(o.str() == "VINCENT\n\nSHARON\nCORK\n");
    }

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_get_winners_1);
    CPPUNIT_TEST(test_get_winners_2);
    CPPUNIT_TEST(test_get_winners_3);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_all_1);
    CPPUNIT_TEST(test_solve_all_2);
    CPPUNIT_TEST(test_solve_all_3);
    CPPUNIT_TEST_SUITE_END();
};

int main()
{
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}

