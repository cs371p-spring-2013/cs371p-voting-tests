// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <cassert>

#include "Voting.h"

extern vector<string> candidate_names;
extern vector<vector<int> > ballots;
extern vector<vector<vector<int> > > candidate_ballots;
extern int tally[20];
extern int numBallots;

/*** Read Tests ***/
void test_voting_read_candidates_1() {
    std::istringstream r("charmander\n\n");
    voting_read_candidates(r);
    assert(candidate_names.at(0).compare("charmander\n"));
}

void test_voting_read_candidates_2() {
    std::istringstream r("charmander bulbasaur\n\n");
    voting_read_candidates(r);
    assert(candidate_names.at(0).compare("charmander bulbasaur\n"));
}

void test_voting_read_candidates_3() {
    std::istringstream r("Charmander T Bulbasaur\nBrandon Lee\nShan Gupta\n\n");
    voting_read_candidates(r);
    assert(candidate_names.at(0).compare("Charmander T Bulbasaur\n"));
    voting_read_candidates(r);
    assert(candidate_names.at(1).compare("Brandon Lee\n"));
}

void test_voting_read_ballots_1() {
    std::istringstream r("1 2 3 4 5\n2 1 3 4 5\n\n");
    voting_read_ballots(r, 5);
    assert(((candidate_ballots.at(0)).at(0)).at(0) == 2);
}

void test_voting_read_ballots_2() {
    std::istringstream r("1 2 3 4 5\n2 1 3 4 5\n\n");
    voting_read_ballots(r, 5);
    assert(((candidate_ballots.at(0)).at(0)).at(0) == 2);
    assert(((candidate_ballots.at(1)).at(0)).at(0) == 1);
}

void test_voting_read_ballots_3() {
    std::istringstream r("1 2 3 4 5\n2 1 3 4 5\n3 1 2 4 5\n\n");
    voting_read_ballots(r, 5);
    assert(((candidate_ballots.at(0)).at(0)).at(0) == 2);
    assert(((candidate_ballots.at(1)).at(0)).at(0) == 1);
    assert(((candidate_ballots.at(2)).at(0)).at(0) == 1);
}

void test_clearGlobal_1() {
    clearGlobal();
    assert(candidate_ballots.empty());
    assert(ballots.empty());
    assert(candidate_names.empty());
    assert(tally[3] == 0);
    assert(numBallots == 0);
}

void test_clearGlobal_2() {
    numBallots = 3;
    tally[3] = 3;
    clearGlobal();
    assert(candidate_ballots.empty());
    assert(ballots.empty());
    assert(candidate_names.empty());
    assert(tally[3] == 0);
    assert(numBallots == 0);
}

void test_clearGlobal_3() {
    string temp = "hello";
    candidate_names.push_back(temp);
    clearGlobal();
    assert(candidate_ballots.empty());
    assert(ballots.empty());
    assert(candidate_names.empty());
    assert(tally[3] == 0);
    assert(numBallots == 0);
}

void test_voting_solve_1() {
    std::istringstream r("3\nShan Gupta\nBrandon Lee\nGlenn Downing\n1 2 3\n2 1 3\n3 2 1\n\n");
    voting_solve(r);
}
void test_voting_solve_2() {
    std::istringstream r("3\nShan Gupta\nBrandon Lee\nGlenn Downing\n1 2 3\n1 2 3\n3 2 1\n\n");
    voting_solve(r);
}

void test_voting_solve_3() {
    std::istringstream r("3\nShan Gupta\nBrandon Lee\nGlenn Downing\n1 2 3\n2 1 3\n3 2 1\n3 2 1\n");
    voting_solve(r);
}

// ----
// main
// ----
int main () {
    using namespace std;
    cout << "TestVoting.c++" << endl;

    test_voting_read_candidates_1();
    test_voting_read_candidates_2();
    test_voting_read_candidates_3();
    cout << "voting_read_candidates checked" << endl;
    test_voting_read_ballots_1();
    test_voting_read_ballots_2();
    test_voting_read_ballots_3();
    cout << "voting_read_ballots checked" << endl;
    test_clearGlobal_1();
    test_clearGlobal_2();
    test_clearGlobal_3();
    cout << "clearGlobal checked" << endl;
    
    test_voting_solve_1();
    test_voting_solve_2();
    test_voting_solve_3();
    cout << "voting_solve checked" << endl;

    cout << "Done." << endl;
    return 0;
}
