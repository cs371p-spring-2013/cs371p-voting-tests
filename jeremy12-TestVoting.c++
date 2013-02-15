#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"

#include "Voting.h"

struct TestVoting : CppUnit::TestFixture
{
	void test_read_1 ()
	{
		using namespace std;
		istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
		vector<string> names;
		vector<vector<int>> ballots;
		voting_read(r, names, ballots);
		string names_array[] = {"John Doe", "Jane Smith", "Sirhan Sirhan"};
		int ballots_matrix[5][3] = {{1, 2, 3}, {2, 1, 3}, {2, 3, 1}, {1,2,3}, {3, 1, 2}};
		for (int i = 0; i<3; ++i)
			CPPUNIT_ASSERT(names_array[i] == names[i]);

		for (int i = 0; i<5; ++i)
		{
			for (int j = 0; j<3; ++j)
			{
				CPPUNIT_ASSERT(ballots_matrix[i][j] == ballots[i][j]);
			}
		}
	}
	
	void test_read_2 ()
	{
		using namespace std;
		istringstream r("1\nJohn Doe\n1\n1\n1\n1\n1\n");
		vector<string> names;
		vector<vector<int>> ballots;
		voting_read(r, names, ballots);
		string names_array[] = {"John Doe"};
		int ballots_matrix[5][1] = {{1}, {1}, {1}, {1}, {1}};
		for (int i = 0; i<1; ++i)
			CPPUNIT_ASSERT(names_array[i] == names[i]);

		for (int i = 0; i<5; ++i)
		{
			for (int j = 0; j<1; ++j)
			{
				CPPUNIT_ASSERT(ballots_matrix[i][j] == ballots[i][j]);
			}
		}
	}
	
	void test_read_3 ()
	{
		using namespace std;
		istringstream r("2\nJohn Doe\nJane Smith\n1 2\n1 2\n1 2\n1 2\n1 2\n");
		vector<string> names;
		vector<vector<int>> ballots;
		voting_read(r, names, ballots);
		string names_array[] = {"John Doe", "Jane Smith"};
		int ballots_matrix[5][2] = {{1, 2}, {1, 2}, {1, 2}, {1, 2}, {1, 2}};
		for (int i = 0; i<2; ++i)
			CPPUNIT_ASSERT(names_array[i] == names[i]);
		for (int i = 0; i<5; ++i)
		{
			for (int j = 0; j<2; ++j)
			{
				CPPUNIT_ASSERT(ballots_matrix[i][j] == ballots[i][j]);
			}
		}
	}

	void test_setBallotSpot_1()
	{
		using namespace std;
		vector<bool> losers(4, false);
		losers[0] = true;
		int ballot_array[] = {1, 2, 3, 4};
		vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array) / sizeof(int));
		Ballot b;
		b.ballot = ballot;
		b.ballotSpot = 0;
		b.setBallotSpot(losers);

		CPPUNIT_ASSERT(b.ballotSpot == 1);
	}

	void test_setBallotSpot_2()
	{
		using namespace std;
		vector<bool> losers(4, false);
		losers[0] = true;
		losers[1] = true;
		int ballot_array[] = {1, 2, 3, 4};
		vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array) / sizeof(int));
		Ballot b;
		b.ballot = ballot;
		b.ballotSpot = 0;
		b.setBallotSpot(losers);

		CPPUNIT_ASSERT(b.ballotSpot == 2);
	}

	void test_setBallotSpot_3()
	{
		using namespace std;
		vector<bool> losers(4, false);
		losers[2] = true;
		int ballot_array[] = {3, 2, 1, 4};
		vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array) / sizeof(int));
		Ballot b;
		b.ballot = ballot;
		b.ballotSpot = 0;
		b.setBallotSpot(losers);

		CPPUNIT_ASSERT(b.ballotSpot == 1);
	}

	void test_currentVote_1()
	{
		using namespace std;
		int ballot_array[] = {3, 2, 1, 4};
		vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array) / sizeof(int));
		Ballot b;
		b.ballot = ballot;
		b.ballotSpot = 1;

		CPPUNIT_ASSERT(b.currentVote() == 2);
	}
	void test_currentVote_2()
	{
		using namespace std;
		int ballot_array[] = {1};
		vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array) / sizeof(int));
		Ballot b;
		b.ballot = ballot;
		b.ballotSpot = 0;

		CPPUNIT_ASSERT(b.currentVote() == 1);
	}
	void test_currentVote_3()
	{
		using namespace std;
		int ballot_array[] = {5, 2, 4, 3, 1};
		vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array) / sizeof(int));
		Ballot b;
		b.ballot = ballot;
		b.ballotSpot = 4;

		CPPUNIT_ASSERT(b.currentVote() == 1);
	}

	void test_numVoters_1()
	{
		Candidate c;
		Ballot voters_array[5];
		vector<Ballot> voters (voters_array, voters_array + sizeof(voters_array)/sizeof(Ballot));
		
		c.voters = voters;

		CPPUNIT_ASSERT(c.numVoters() == 5);
	}

	void test_numVoters_2()
	{
		Candidate c;
		Ballot voters_array[1];
		vector<Ballot> voters (voters_array, voters_array + sizeof(voters_array)/sizeof(Ballot));
		
		c.voters = voters;

		CPPUNIT_ASSERT(c.numVoters() == 1);
	}
	void test_numVoters_3()
	{
		Candidate c;
		Ballot voters_array[1000];
		vector<Ballot> voters (voters_array, voters_array + sizeof(voters_array)/sizeof(Ballot));
		
		c.voters = voters;

		CPPUNIT_ASSERT(c.numVoters() == 1000);
	}

	void test_lose_1()
	{
		Candidate c;
		vector<Ballot> voters;

		for(int i =0; i<1000; ++i)
		{
			Ballot b;
			int ballot_array[] = {1, 2, 3, 4};
			vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array)/sizeof(int));
			b.ballot = ballot;
			b.ballotSpot = 0;
			voters.push_back(b);
		}
		vector<bool> losers(4, false);
		losers[0] = true;
		losers[1] = true;
		c.voters = voters;
		c.number = 1;

		c.lose(losers);
		for(int i = 0; i<1000; ++i)
		{
			CPPUNIT_ASSERT(c.voters[i].ballotSpot > 0);
		}
	}
	void test_lose_2()
	{
		Candidate c;
		vector<Ballot> voters;

		for(int i =0; i<1; ++i)
		{
			Ballot b;
			int ballot_array[] = {1, 2, 3, 4};
			vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array)/sizeof(int));
			b.ballot = ballot;
			b.ballotSpot = 0;
			voters.push_back(b);
		}
		vector<bool> losers(4, false);
		losers[0] = true;
		losers[1] = true;
		c.voters = voters;
		c.number = 1;

		c.lose(losers);
		for(int i = 0; i<1; ++i)
		{
			CPPUNIT_ASSERT(c.voters[i].ballotSpot > 0);
		}
	}
	void test_lose_3()
	{
		Candidate c;
		vector<Ballot> voters;

		for(int i =0; i<10; ++i)
		{
			Ballot b;
			int ballot_array[] = {1, 2, 3, 4};
			vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array)/sizeof(int));
			b.ballot = ballot;
			b.ballotSpot = 0;
			voters.push_back(b);
		}
		for(int i =0; i<10; ++i)
		{
			Ballot b;
			int ballot_array[] = {1, 4, 3, 2};
			vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array)/sizeof(int));
			b.ballot = ballot;
			b.ballotSpot = 0;
			voters.push_back(b);
		}
		vector<bool> losers(4, false);
		losers[0] = true;
		losers[3] = true;
		c.voters = voters;
		c.number = 1;

		c.lose(losers);
		for(int i = 0; i<10; ++i)
		{
			CPPUNIT_ASSERT(c.voters[i].ballotSpot == 1);
		}
		for(int i = 10; i<20; ++i)
		{
			CPPUNIT_ASSERT(c.voters[i].ballotSpot == 2);
		}
	}

	void test_addLoser_1()
	{
		Election e;
		vector<Candidate> candidates;
		vector<bool>losers (4, false);
		e.num_ballots = 80;
		e.losers = losers;
		for(int i =0; i<4; ++i)
		{
			Candidate c;
			vector<Ballot> voters;
			for(int j =0; j<20; ++j)
			{
				Ballot b;
				int ballot_array[] = {(i+1), ((i+1) % 4)+1, ((i+2) % 4)+1, ((i+3) % 4)+1};
				vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array)/sizeof(int));
				b.ballot = ballot;
				b.ballotSpot = 0;
				voters.push_back(b);
			}
			c.number = i+1;
			c.voters = voters;
			candidates.push_back(c);


		}
		e.candidates = candidates;
		e.addLoser(1);

		CPPUNIT_ASSERT(e.candidates[1].numVoters() == 40);
	}

	void test_addLoser_2()
	{
		Election e;
		vector<Candidate> candidates;
		vector<bool>losers (20, false);
		e.num_ballots = 400;
		e.losers = losers;
		for(int i =0; i<20; ++i)
		{
			Candidate c;
			vector<Ballot> voters;
			for(int j =0; j<20; ++j)
			{
				Ballot b;
				int ballot_array[20];
				for (int k = 0; k<20; ++k)
				{
					ballot_array[k] = ((i+k) % 20) + 1;
				}
				vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array)/sizeof(int));
				b.ballot = ballot;
				b.ballotSpot = 0;
				voters.push_back(b);
			}
			c.number = i+1;
			c.voters = voters;
			candidates.push_back(c);
		}
		e.candidates = candidates;
		e.addLoser(1);

		CPPUNIT_ASSERT(e.candidates[1].numVoters() == 40);
	}
	void test_addLoser_3()
	{
		Election e;
		vector<Candidate> candidates;
		vector<bool>losers (4, false);
		e.num_ballots = 80;
		e.losers = losers;
		for(int i =0; i<4; ++i)
		{
			Candidate c;
			vector<Ballot> voters;
			for(int j =0; j<20; ++j)
			{
				Ballot b;
				int ballot_array[] = {(i+1), ((i+1) % 4)+1, ((i+2) % 4)+1, ((i+3) % 4)+1};
				vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array)/sizeof(int));
				b.ballot = ballot;
				b.ballotSpot = 0;
				voters.push_back(b);
			}
			c.number = i+1;
			c.voters = voters;
			candidates.push_back(c);
		}
		e.candidates = candidates;
		e.addLoser(1);
		e.addLoser(2);

		CPPUNIT_ASSERT(e.candidates[2].numVoters() == 60);
	}
	
	void test_winner_1()
	{
		using namespace std;
		Election e;
		vector<Candidate> candidates;
		vector<bool>losers (4, false);
		e.num_ballots = 80;
		e.num_candidates = 4;
		e.losers = losers;
		for(int i =0; i<4; ++i)
		{
			cout.flush();
			Candidate c;
			vector<Ballot> voters;
			for(int j =0; j<20; ++j)
			{
				Ballot b;
				int ballot_array[] = {(i+1), ((i+1) % 4)+1, ((i+2) % 4)+1, ((i+3) % 4)+1};
				vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array)/sizeof(int));
				b.ballot = ballot;
				b.ballotSpot = 0;
				voters.push_back(b);
			}
			c.number = i+1;
			c.voters = voters;
			c.name = "Candidate";
			candidates.push_back(c);
		}
		e.candidates = candidates;
		vector<int> result = voting_winner(e, 80);

		for (int i = 0; i<4; ++i)
			CPPUNIT_ASSERT(result[i] == i+1);
	}

	void test_winner_2()
	{
		using namespace std;
		Election e;
		vector<Candidate> candidates;
		vector<bool>losers (5, false);
		e.num_ballots = 80;
		e.num_candidates = 5;
		e.losers = losers;
		for(int i =0; i<4; ++i)
		{
			Candidate c;
			vector<Ballot> voters;
			for(int j =0; j<20; ++j)
			{
				Ballot b;
				int ballot_array[] = {(i+1), ((i+1) % 5)+1, ((i+2) % 5)+1,
										((i+3) % 5)+1, ((i+4) % 5)+1};
				vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array)/sizeof(int));
				b.ballot = ballot;
				b.ballotSpot = 0;
				voters.push_back(b);
			}
			c.number = i+1;
			c.voters = voters;
			c.name = "Candidate";
			candidates.push_back(c);
		}
		{
			int i = 4;
			Candidate c;
			vector<Ballot> voters;
			for(int j =0; j<100; ++j)
			{
				Ballot b;
				int ballot_array[] = {(i+1), ((i+1) % 5)+1, ((i+2) % 5)+1,
								((i+3) % 5)+1, ((i+4) % 5)+1};
				vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array)/sizeof(int));
				b.ballot = ballot;
				b.ballotSpot = 0;
				voters.push_back(b);
			}
			c.number = i+1;
			c.voters = voters;
			c.name = "Candidate";
			candidates.push_back(c);
		}
		e.candidates = candidates;
		vector<int> result = voting_winner(e, 180);
		cout.flush();


		CPPUNIT_ASSERT(result[0] == 5);
		CPPUNIT_ASSERT(result.size() == 1);
	}
	void test_winner_3()
	{
		using namespace std;
		Election e;
		vector<Candidate> candidates;
		vector<bool>losers (6, false);
		e.num_ballots = 280;
		e.num_candidates = 6;
		e.losers = losers;
		for(int i =0; i<4; ++i)
		{
			Candidate c;
			vector<Ballot> voters;
			for(int j =0; j<20; ++j)
			{
				Ballot b;
				int ballot_array[] = {(i+1), ((i+1) % 6)+1, ((i+2) % 6)+1,
										((i+3) % 6)+1, ((i+4) % 6)+1, ((i+5)%6)+1};
				vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array)/sizeof(int));
				b.ballot = ballot;
				b.ballotSpot = 0;
				voters.push_back(b);
			}
			c.number = i+1;
			c.voters = voters;
			c.name = "Candidate";
			candidates.push_back(c);
		}
		for (int i = 4; i<6; ++i)
		{
			Candidate c;
			vector<Ballot> voters;
			for(int j =0; j<100; ++j)
			{
				Ballot b;
				int ballot_array[] = {(i+1), ((i+1) % 6)+1, ((i+2) % 6)+1,
								((i+3) % 6)+1, ((i+4) % 6)+1, ((i+5) % 6)+1};
				vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array)/sizeof(int));
				b.ballot = ballot;
				b.ballotSpot = 0;
				voters.push_back(b);
			}
			c.number = i+1;
			c.voters = voters;
			c.name = "Candidate";
			candidates.push_back(c);
		}
		e.candidates = candidates;
		vector<int> result = voting_winner(e, 280);
		


		CPPUNIT_ASSERT(result[0] == 5);
	}
	void test_eval_1()
	{
		using namespace std;
		vector<string> candidate_names = {"Jim", "EK", "Jeremy"};
		vector<vector<int> > ballots = {{1,2,3}, {2, 1, 3}, {2, 3, 2}};
		string ans = voting_eval(candidate_names, ballots);
		CPPUNIT_ASSERT(ans.compare(candidate_names[1] + "\n") == 0);
	}
	void test_eval_2()
	{
		using namespace std;
		vector<string> candidate_names = {"Jeremy"};
		vector<vector<int> > ballots = {{1}, {1}, {1}, {1}, {1}, {1}, {1}};
		string ans = voting_eval(candidate_names, ballots);
		CPPUNIT_ASSERT(ans.compare(candidate_names[0] + "\n") == 0);
	}
	void test_eval_3()
	{
		using namespace std;
		vector<string> candidate_names;
		string a = "a";
		for(int i = 0; i < 20; ++i){
			candidate_names.push_back(a);
			a += "a";
		}
		vector<vector<int> > ballots = {{14, 2, 3, 1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 16, 17, 18, 19, 20}};
		string ans = voting_eval(candidate_names, ballots);
		CPPUNIT_ASSERT(ans.compare(candidate_names[13] + "\n") == 0);
	}
	void test_solve_1()
	{
		using namespace std;
		istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
		ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "John Doe\n");
	}
	void test_solve_2()
	{	
		using namespace std;
		istringstream r("1\n\n1\nJohn Doe\n1\n1\n1\n1\n1\n");
		ostringstream w;
		voting_solve(r,w);
		CPPUNIT_ASSERT(w.str() == "John Doe\n");
	}
	void test_solve_3()
	{
		using namespace std;
		istringstream r("2\n\n1\nJeremy S\n1\n1\n1\n1\n\n2\nEk Y\nJude K\n2 1\n1 2\n");
		ostringstream w;
		voting_solve(r,w);
		CPPUNIT_ASSERT(w.str() == "Jeremy S\n\nEk Y\nJude K\n");
	}
	void test_sort_1()
	{
		using namespace std;
		
		Election e;
		vector<Candidate> candidates;
		vector<bool>losers (5, false);
		e.num_ballots = 80;
		e.num_candidates = 5;
		e.losers = losers;
		for(int i =0; i<5; ++i)
		{
			Candidate c;
			vector<Ballot> voters;
			for(int j =0; j<20; ++j)
			{
				Ballot b;
				int ballot_array[] = {(i+1), ((i+1) % 5)+1, ((i+2) % 5)+1,
										((i+3) % 5)+1, ((i+4) % 5)+1};
				vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array)/sizeof(int));
				b.ballot = ballot;
				b.ballotSpot = 0;
				voters.push_back(b);
			}
			c.number = i+1;
			c.voters = voters;
			c.name = "Candidate";
			candidates.push_back(c);
		}
		e.candidates = candidates;
		vector<int> cands;
		cands.push_back(1);
		cands.push_back(2);
		voting_sort(cands, e);

		CPPUNIT_ASSERT(cands[0] == 1);
		CPPUNIT_ASSERT(cands[1] == 2);
	}
	void test_sort_2()
	{
		using namespace std;
		
		Election e;
		vector<Candidate> candidates;
		vector<bool>losers (20, false);
		e.num_ballots = 80;
		e.num_candidates = 20;
		e.losers = losers;
		for(int i =0; i<20; ++i)
		{
			Candidate c;
			vector<Ballot> voters;
			for(int j =0; j<20; ++j)
			{
				Ballot b;
				int ballot_array[] = {(i+1), ((i+1) % 5)+1, ((i+2) % 5)+1,
										((i+3) % 5)+1, ((i+4) % 5)+1};
				vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array)/sizeof(int));
				b.ballot = ballot;
				b.ballotSpot = 0;
				voters.push_back(b);
			}
			c.number = i+1;
			c.voters = voters;
			c.name = "Candidate";
			candidates.push_back(c);
		}
		e.candidates = candidates;
		vector<int> cands;
		cands.push_back(1);
		cands.push_back(2);
		voting_sort(cands, e);

		CPPUNIT_ASSERT(cands[0] == 1);
		CPPUNIT_ASSERT(cands[1] == 2);
	}
	void test_sort_3()
	{
		using namespace std;
		Election e;
		vector<Candidate> candidates;
		vector<bool>losers (6, false);
		e.num_ballots = 280;
		e.num_candidates = 6;
		e.losers = losers;
		for(int i =0; i<4; ++i)
		{
			Candidate c;
			vector<Ballot> voters;
			for(int j =0; j<20; ++j)
			{
				Ballot b;
				int ballot_array[] = {(i+1), ((i+1) % 6)+1, ((i+2) % 6)+1,
										((i+3) % 6)+1, ((i+4) % 6)+1, ((i+5)%6)+1};
				vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array)/sizeof(int));
				b.ballot = ballot;
				b.ballotSpot = 0;
				voters.push_back(b);
			}
			c.number = i+1;
			c.voters = voters;
			c.name = "Candidate";
			candidates.push_back(c);
		}
		for (int i = 4; i<6; ++i)
		{
			Candidate c;
			vector<Ballot> voters;
			for(int j =0; j<100; ++j)
			{
				Ballot b;
				int ballot_array[] = {(i+1), ((i+1) % 6)+1, ((i+2) % 6)+1,
								((i+3) % 6)+1, ((i+4) % 6)+1, ((i+5) % 6)+1};
				vector<int> ballot (ballot_array, ballot_array + sizeof(ballot_array)/sizeof(int));
				b.ballot = ballot;
				b.ballotSpot = 0;
				voters.push_back(b);
			}
			c.number = i+1;
			c.voters = voters;
			c.name = "Candidate";
			candidates.push_back(c);
		}
		e.candidates = candidates;
		vector<int> cands;
		cands.push_back(1);
		cands.push_back(2);
		cands.push_back(3);	
		cands.push_back(4);
		cands.push_back(5);
		cands.push_back(6);
		voting_sort(cands, e);

		CPPUNIT_ASSERT(cands[0] == 5);
		CPPUNIT_ASSERT(cands[1] == 6);
	}
	void test_winner_or_loser_1()
	{
		Election e;
		Candidate c;
		vector<Ballot> voters;
		for(int j =0; j<20; ++j)
		{
			Ballot b;
			voters.push_back(b);
		}
		c.voters = voters;
		vector<int> losers;
		int max = 15;
		int min = 10;
		voting_winner_or_loser(e, c, min, max, losers);
		CPPUNIT_ASSERT(max == 20);
		CPPUNIT_ASSERT(losers.size() == 0);
	}
	void test_winner_or_loser_2()
	{
		Election e;
		Candidate c;
		vector<Ballot> voters;
		for(int j =0; j<20; ++j)
		{
			Ballot b;
			voters.push_back(b);
		}
		c.voters = voters;
		vector<int> losers;
		int max = 40;
		int min = 25;
		voting_winner_or_loser(e, c, min, max, losers);
		CPPUNIT_ASSERT(max == 40);
		CPPUNIT_ASSERT(min == 20);
		CPPUNIT_ASSERT(losers.size() == 1);
	}
	void test_winner_or_loser_3()
	{
		Election e;
		Candidate c;
		vector<Ballot> voters;
		for(int j =0; j<20; ++j)
		{
			Ballot b;
			voters.push_back(b);
		}
		c.voters = voters;
		vector<int> losers (1, 1);
		int max = 25;
		int min = 20;
		voting_winner_or_loser(e, c, min, max, losers);
		CPPUNIT_ASSERT(max == 25);
		CPPUNIT_ASSERT(min == 20);
		CPPUNIT_ASSERT(losers.size() == 2);
	}
	CPPUNIT_TEST_SUITE(TestVoting);
	CPPUNIT_TEST(test_read_1);
	CPPUNIT_TEST(test_read_2);
	CPPUNIT_TEST(test_read_3);
	CPPUNIT_TEST(test_setBallotSpot_1);
	CPPUNIT_TEST(test_setBallotSpot_2);
	CPPUNIT_TEST(test_setBallotSpot_3);
	CPPUNIT_TEST(test_currentVote_1);
	CPPUNIT_TEST(test_currentVote_2);
	CPPUNIT_TEST(test_currentVote_3);
	CPPUNIT_TEST(test_numVoters_1);
	CPPUNIT_TEST(test_numVoters_2);
	CPPUNIT_TEST(test_numVoters_3);
	CPPUNIT_TEST(test_lose_1);
	CPPUNIT_TEST(test_lose_2);
	CPPUNIT_TEST(test_lose_3);
	CPPUNIT_TEST(test_addLoser_1);
	CPPUNIT_TEST(test_addLoser_2);
	CPPUNIT_TEST(test_addLoser_3);
	CPPUNIT_TEST(test_winner_1);
	CPPUNIT_TEST(test_winner_2);
	CPPUNIT_TEST(test_winner_3);
	CPPUNIT_TEST(test_eval_1);
	CPPUNIT_TEST(test_eval_2);
	CPPUNIT_TEST(test_eval_3);
	CPPUNIT_TEST(test_solve_1);
	CPPUNIT_TEST(test_solve_2);
	CPPUNIT_TEST(test_solve_3);
	CPPUNIT_TEST(test_sort_1);
	CPPUNIT_TEST(test_sort_2);
	CPPUNIT_TEST(test_sort_3);
	CPPUNIT_TEST(test_winner_or_loser_1);
	CPPUNIT_TEST(test_winner_or_loser_2);
	CPPUNIT_TEST(test_winner_or_loser_3);
	CPPUNIT_TEST_SUITE_END();
};

int main()
{
	using namespace std;
	//ios_base::sync_with_stdio(false);
	cout << "TestVoting.c++" << endl;
	
	CppUnit::TextTestRunner tr;
	tr.addTest(TestVoting::suite());
	tr.run();

	cout<< "Done." << endl;
	return 0;
}
