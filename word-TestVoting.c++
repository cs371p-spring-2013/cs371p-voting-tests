// --------------------------------
// projects/Voting/TestVoting.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -lcppunit -ldl -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting.c++.app
    % valgrind TestVoting.c++.app >& TestVoting.c++.out
*/
/**
  Christopher Word   word@cs.utexas.edu
  eid: cword
  csid: word

  Austrailian Voting Problem 
  Assignment 2 OOP - Spring 13

**/


// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <queue>
#include <vector>
#include <list>
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {

// int voting_read(istream& in , vector<queue<int> >& collection , vector<string>& id );

  void test_read1 () {
    std::istringstream r("1\nJohn Doe\n1\n");
    queue<int> singleVote;
    singleVote.push(0);
    vector<queue<int> > votes;
    votes.push_back(singleVote);
    vector<vector<queue<int> > > bucket;
    bucket.push_back(votes);

    vector<string> names;
    names.push_back("John Doe");
    vector<vector<queue<int> > >v;
    vector<string> n;
    int i = voting_read(r, v, n);


    CPPUNIT_ASSERT(i == 1);
    CPPUNIT_ASSERT(n == names);
    CPPUNIT_ASSERT(v.size()==bucket.size());
    for(uint i = 0; i < v.size(); i++){
      CPPUNIT_ASSERT(v[i].size()==bucket[i].size());
      CPPUNIT_ASSERT(v[i]==bucket[i]);
    }


  }

  void test_read2 () {
    std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    vector<queue<int> > votesFor1;
    int vote1[] = {1,2,3};
    int vote4[] = {1,2,3};

    vector<queue<int> > votesFor2;
    int vote2[] = {2,1,3};
    int vote3[] = {2,3,1};

    vector<queue<int> > votesFor3;
    int vote5[] = {3,1,2};

    queue<int> voter1;
    queue<int> voter2;
    queue<int> voter3;
    queue<int> voter4;
    queue<int> voter5;
    for(int i = 0; i < 3 ; i++ ){
      voter1.push(vote1[i]-1);
      voter2.push(vote2[i]-1);
      voter3.push(vote3[i]-1);
      voter4.push(vote4[i]-1);
      voter5.push(vote5[i]-1);
    }
    votesFor1.push_back(voter1);
    votesFor2.push_back(voter2);
    votesFor2.push_back(voter3);
    votesFor1.push_back(voter4);
    votesFor3.push_back(voter5);
    vector<vector<queue<int> > > bucket;
    bucket.push_back(votesFor1);
    bucket.push_back(votesFor2);
    bucket.push_back(votesFor3);

    vector<string> names;
    names.push_back("John Doe");
    names.push_back("Jane Smith");
    names.push_back("Sirhan Sirhan");
    vector<vector<queue<int> > > v;
    vector<string> n;
    int i = voting_read(r, v, n);

    CPPUNIT_ASSERT(i == 3);
    CPPUNIT_ASSERT(n == names);
//    CPPUNIT_ASSERT(v == votes);
    for(uint i = 0; i < v.size(); i++){
      CPPUNIT_ASSERT(v[i].size()==bucket[i].size());
      CPPUNIT_ASSERT(v[i]==bucket[i]);
    }

  }

  void test_read3 () {
    std::istringstream r("3\nJohn Dodo\nJayne Smooth\nSir Han\n3 2 1\n1 3 2\n2 3 1\n1 2 3\n2 3 1\n");
    vector<queue<int> > votesFor1;
    vector<queue<int> > votesFor2;
    vector<queue<int> > votesFor3;


    int vote1[] = {3,2,1};
    int vote2[] = {1,3,2};
    int vote3[] = {2,3,1};
    int vote4[] = {1,2,3};
    int vote5[] = {2,3,1};
    queue<int> voter1;
    queue<int> voter2;
    queue<int> voter3;
    queue<int> voter4;
    queue<int> voter5;
    for(int i = 0; i < 3 ; i++ ){
      voter1.push(vote1[i]-1);
      voter2.push(vote2[i]-1);
      voter3.push(vote3[i]-1);
      voter4.push(vote4[i]-1);
      voter5.push(vote5[i]-1);
    }
    votesFor3.push_back(voter1);
    votesFor1.push_back(voter2);
    votesFor2.push_back(voter3);
    votesFor1.push_back(voter4);
    votesFor2.push_back(voter5);

    vector<vector<queue<int> > > bucket;
    bucket.push_back(votesFor1);
    bucket.push_back(votesFor2);
    bucket.push_back(votesFor3);

    vector<string> names;
    names.push_back("John Dodo");
    names.push_back("Jayne Smooth");
    names.push_back("Sir Han");
    vector<vector<queue<int> > >v;
    vector<string> n;
    int i = voting_read(r, v, n);

    CPPUNIT_ASSERT(i == 3);
    CPPUNIT_ASSERT(n == names);
    for(uint i = 0; i < v.size(); i++){
      CPPUNIT_ASSERT(v[i].size()==bucket[i].size());
      CPPUNIT_ASSERT(v[i]==bucket[i]);
    }
  }

  // -----
  // print
  // -----
// void voting_print(ostream& out , vector<string> viniVidiVici);

  void test_print1 () {
    vector<string> names;
    names.push_back("John Doe");
    names.push_back("Jane Smith");
    names.push_back("Sirhan Sirhan");
    std::ostringstream w;
    voting_print(w, names);
    CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");
  }

  void test_print2 () {
    vector<string> names;
    names.push_back("Sirhan Sirhan");
    std::ostringstream w;
    voting_print(w, names);
    CPPUNIT_ASSERT(w.str() == "Sirhan Sirhan\n");
  }

  void test_print3 () {
    vector<string> names;
    names.push_back("Jane Smith");
    names.push_back("Sirhan Sirhan");
    std::ostringstream w;
    voting_print(w, names);
    CPPUNIT_ASSERT(w.str() == "Jane Smith\nSirhan Sirhan\n");
  }

  // ----
  // eval
  // ----
// vector<string> voting_eval(int count , vector<queue<int> >& collection , vector<string>& id );

  void test_eval1 () {
    vector<string> s;
    vector<queue<int> > votes;
    vector<vector<queue<int> > > buckets;

    vector<string> names;
    vector<string> output;

    queue<int> singleVote;
    singleVote.push(0);

    votes.push_back(singleVote);
    buckets.push_back(votes);
    names.push_back("John Doe");
    output.push_back("John Doe");


    s = voting_eval(1, buckets, names);
    CPPUNIT_ASSERT(s == output);
  }

  void test_eval2 () {
    vector<string> s;
    vector<queue<int> > votesFor1;
    vector<queue<int> > votesFor2;
    vector<queue<int> > votesFor3;


    vector<vector<queue<int> > > buckets;

    vector<string> names;
    vector<string> output;

    output.push_back("John Doe");

    int vote1[] = {1,2,3};
    int vote2[] = {2,1,3};
    int vote3[] = {2,3,1};
    int vote4[] = {1,2,3};
    int vote5[] = {3,1,2};
    queue<int> voter1;
    queue<int> voter2;
    queue<int> voter3;
    queue<int> voter4;
    queue<int> voter5;
    for(int i = 0; i < 3 ; i++ ){
      voter1.push(vote1[i]-1);
      voter2.push(vote2[i]-1);
      voter3.push(vote3[i]-1);
      voter4.push(vote4[i]-1);
      voter5.push(vote5[i]-1);
    }
    votesFor1.push_back(voter1);
    votesFor2.push_back(voter2);
    votesFor2.push_back(voter3);
    votesFor1.push_back(voter4);
    votesFor3.push_back(voter5);

    buckets.push_back(votesFor1);
    buckets.push_back(votesFor2);
    buckets.push_back(votesFor3);



    names.push_back("John Doe");
    names.push_back("Jane Smith");
    names.push_back("Sirhan Sirhan");

    s = voting_eval(3, buckets, names);
    CPPUNIT_ASSERT(s == output);
  }

  void test_eval3 () {
    vector<string> s;
    vector<queue<int> > votesFor1;
    vector<queue<int> > votesFor2;
    vector<queue<int> > votesFor3;


    vector<vector<queue<int> > > buckets;
    vector<string> names;
    vector<string> output;

    int vote1[] = {3,2,1};
    int vote2[] = {1,3,2};
    int vote3[] = {2,3,1};
    int vote4[] = {1,2,3};
    int vote5[] = {2,3,1};

    queue<int> voter1;
    queue<int> voter2;
    queue<int> voter3;
    queue<int> voter4;
    queue<int> voter5;

    for(int i = 0; i < 3 ; i++ ){
      voter1.push(vote1[i]-1);
      voter2.push(vote2[i]-1);
      voter3.push(vote3[i]-1);
      voter4.push(vote4[i]-1);
      voter5.push(vote5[i]-1);
    }
    votesFor3.push_back(voter1);
    votesFor1.push_back(voter2);
    votesFor2.push_back(voter3);
    votesFor1.push_back(voter4);
    votesFor2.push_back(voter5);

    buckets.push_back(votesFor1);
    buckets.push_back(votesFor2);
    buckets.push_back(votesFor3);

    names.push_back("John Dodo");
    names.push_back("Jayne Smooth");
    names.push_back("Sir Han");

    output.push_back("Jayne Smooth");

    s = voting_eval(3, buckets, names);

//    cout << s[0];

    CPPUNIT_ASSERT(s == output);
  }

  void test_eval4 () {
    vector<string> s;
    vector<queue<int> > votesFor1;
    vector<queue<int> > votesFor2;
    vector<queue<int> > votesFor3;


    vector<vector<queue<int> > > buckets;
    vector<string> names;
    vector<string> output;

    int vote1[] = {3,2,1};
    int vote2[] = {1,3,2};
    int vote3[] = {2,3,1};
    int vote4[] = {1,2,3};
    int vote5[] = {2,3,1};
    int vote6[] = {3,2,1};

    queue<int> voter1;
    queue<int> voter2;
    queue<int> voter3;
    queue<int> voter4;
    queue<int> voter5;
    queue<int> voter6;

    for(int i = 0; i < 3 ; i++ ){
      voter1.push(vote1[i]-1);
      voter2.push(vote2[i]-1);
      voter3.push(vote3[i]-1);
      voter4.push(vote4[i]-1);
      voter5.push(vote5[i]-1);
      voter6.push(vote6[i]-1);
    }
    votesFor3.push_back(voter1);
    votesFor1.push_back(voter2);
    votesFor2.push_back(voter3);
    votesFor1.push_back(voter4);
    votesFor2.push_back(voter5);
    votesFor3.push_back(voter6);

    buckets.push_back(votesFor1);
    buckets.push_back(votesFor2);
    buckets.push_back(votesFor3);

    names.push_back("John Dodo");
    names.push_back("Jayne Smooth");
    names.push_back("Sir Han");

    s = voting_eval(3, buckets, names);
    CPPUNIT_ASSERT(s == names);
  }


  // -----
  // solve
  // -----
// void voting_solve (istream& in, ostream& out);



  void test_solve1 () {
    std::istringstream r("1\n\n1\nJohn Doe\n1\n");
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "John Doe\n");
  }

  void test_solve2 () {
    std::istringstream r("1\n\n3\nJohn Dodo\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "John Dodo\n");
  }

  void test_solve3 () {
    std::istringstream r("2\n\n1\nJohn Doe\n1\n\n3\nJohn Dodo\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "John Doe\n\nJohn Dodo\n");
  }

//void getAloser(vector<int> oneElection, vector<int>& eliminated){
  void test_loser1(){
    vector<int> l;
    vector<int> losers;
    vector<int> results;

    l.push_back(2);

    losers.push_back(2);
    losers.push_back(1);

    results.push_back(12);
    results.push_back(4);
    results.push_back(0);

    getAloser(results, l);

    CPPUNIT_ASSERT(l == losers);

  }

  void test_loser2(){
    vector<int> l;
    vector<int> losers;
    vector<int> results;


    losers.push_back(2);

    results.push_back(12);
    results.push_back(4);
    results.push_back(0);

    getAloser(results, l);

    CPPUNIT_ASSERT(l == losers);

  }

  void test_loser3(){
    vector<int> l;
    vector<int> losers;
    vector<int> results;

    l.push_back(2);


    losers.push_back(2);
    losers.push_back(3);


    results.push_back(12);
    results.push_back(4);
    results.push_back(0);
    results.push_back(0);

    getAloser(results, l);

    CPPUNIT_ASSERT(l == losers);

  }


  // ----
  // calc
  // ----
// vector<int> gotAwinner(vector<int> oneElection);
  void test_winner1(){
    vector<int> winners;
    vector<int> w;
    vector<int> results;

    winners.push_back(0);

    results.push_back(12);
    results.push_back(4);
    results.push_back(0);

    w = gotAwinner(results);
    CPPUNIT_ASSERT(w == winners);
  }

  void test_winner2(){
    vector<int> winners;
    vector<int> w;
    vector<int> results;

    winners.push_back(0);
    winners.push_back(1);
    winners.push_back(2);

    results.push_back(12);
    results.push_back(12);
    results.push_back(12);
    results.push_back(0);
    results.push_back(0);
    results.push_back(0);

    w = gotAwinner(results);
    CPPUNIT_ASSERT(w == winners);
  }

  void test_winner3(){
    vector<int> winners;
    vector<int> w;
    vector<int> results;

    winners.push_back(2);

    results.push_back(3);
    results.push_back(1);
    results.push_back(300);
    results.push_back(7);
    results.push_back(8);
    results.push_back(0);

    w = gotAwinner(results);
    CPPUNIT_ASSERT(w == winners);
  }

  void test_winner4(){
    vector<int> winners;
    vector<int> w;
    vector<int> results;
    winners.push_back(2);
    winners.push_back(3);

    results.push_back(0);
    results.push_back(0);
    results.push_back(300);
    results.push_back(300);
    results.push_back(0);
    results.push_back(0);

    w = gotAwinner(results);
    CPPUNIT_ASSERT(w == winners);
  }

  // -----
  // suite
  // -----

  CPPUNIT_TEST_SUITE(TestVoting);

  CPPUNIT_TEST(test_read1);
  CPPUNIT_TEST(test_read2);
  CPPUNIT_TEST(test_read3);

  CPPUNIT_TEST(test_print1);
  CPPUNIT_TEST(test_print2);
  CPPUNIT_TEST(test_print3);

  CPPUNIT_TEST(test_winner1);
  CPPUNIT_TEST(test_winner2);
  CPPUNIT_TEST(test_winner3);
  CPPUNIT_TEST(test_winner4);

  CPPUNIT_TEST(test_loser1);
  CPPUNIT_TEST(test_loser2);
  CPPUNIT_TEST(test_loser3);

  CPPUNIT_TEST(test_solve1);
  CPPUNIT_TEST(test_solve2);
  CPPUNIT_TEST(test_solve3);


  CPPUNIT_TEST(test_eval1);
  CPPUNIT_TEST(test_eval2);
  CPPUNIT_TEST(test_eval3);
  CPPUNIT_TEST(test_eval4);

  CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

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









