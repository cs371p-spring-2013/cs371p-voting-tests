/*
	RunVoting.c++
	CS371P - Project2 Voting
	2013.02.04
	Hyunchel Kim
*/


/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -lcppunit -ldl -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz.c++.app
    % valgrind TestCollatz.c++.app >& TestCollatz.c++.out
*/


 //	includes

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <stdexcept> // domain_error
#include <vector>
#include <algorithm>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"


/*
//  TestVoting
*/

struct TestVoting : CppUnit::TestFixture {

    /*
    //  prints (has many forms...polymorphism?)
    */
    void test_print_int_1 ()
    {
        std::ostringstream w;
        voting_print(w, 20);
        CPPUNIT_ASSERT(w.str() == "20\n");    
    }

    void test_print_int_2 ()
    {
        std::ostringstream w;
        try
        {
            // throwing negatvie value
            voting_print(w, -1);
            CPPUNIT_ASSERT(false);
        }
        catch(std::domain_error& e)
        {
            // there should be an excpetion
            CPPUNIT_ASSERT(true);
        }   
    }

    void test_print_int_3 ()
    {
        std::ostringstream w;
        voting_print(w, 0);
        CPPUNIT_ASSERT(w.str() == "0\n");   
    }

    void test_print_array_1 ()
    {
        std::ostringstream w;
        int candidates = 10;
        int array[candidates];


        // just plugging in number into array to make it a valid array
        for (int i=0; i<10; i++)
        {
            array[i] = i+10;
        }

        try
        {
            voting_print(w, array, candidates);
            CPPUNIT_ASSERT(w.str() == "10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n");
 
        }
        catch(std::domain_error& e)
        {
            // no exception should be thrown
            CPPUNIT_ASSERT(false);
        }
    }

    void test_print_array_2 ()
    {
        std::ostringstream w;
        int candidates = 1;
        int array[candidates];


        // just plugging in number into array to make it a valid array
        for (int i=0; i<1; i++)
        {
            array[i] = i+10;
        }

        try
        {
            voting_print(w, array, candidates);
            CPPUNIT_ASSERT(w.str() == "10\n");
 
        }
        catch(std::domain_error& e)
        {
            // no exception should be thrown
            CPPUNIT_ASSERT(false);
        }
    }
 
    void test_print_array_3 ()
    {
        std::ostringstream w;
        int candidates = 10;
        int array[candidates];


        // insert a non-positive integer in the array
        array[2] = -1;

        try
        {
            voting_print(w, array, candidates);
            CPPUNIT_ASSERT(false);
 
        }
        catch(std::domain_error& e)
        {
            // should throw an exception 
            CPPUNIT_ASSERT(true);
        }
    }

    void test_print_string_1 ()
    {
        std::ostringstream w;
        int candidates = 10;
        string string_array[candidates];

        // new string..must have empty

        try
        {
            voting_print(w, string_array, candidates);
            CPPUNIT_ASSERT(false);
 
        }
        catch(std::domain_error& e)
        {
            // an exception SHOULD be thrown
            CPPUNIT_ASSERT(true);
        }
    }

    void test_print_string_2 ()
    {
        std::ostringstream w;
        int candidates = 10;
        string string_array[candidates];

        for (int i=0; i<10; i++)
        {
            string_array[i] = "HI";
        }

        try
        {
            voting_print(w, string_array, candidates);
            CPPUNIT_ASSERT(w.str() == "HI\nHI\nHI\nHI\nHI\nHI\nHI\nHI\nHI\nHI\n");
 
        }
        catch(std::domain_error& e)
        {
            // NO exception should be thrown
            CPPUNIT_ASSERT(false);
        }
    }

    void test_print_string_3 ()
    {
        std::ostringstream w;
        int candidates = 10;
        string string_array[candidates];


        for (int i=0; i<10; i++)
        {
            string_array[i] = "HI";
            
            // empty lines... should throw an exception
            if (i == 5 || i ==9)
            {
                string_array[i] = "";
            }
        }

        try
        {
            voting_print(w, string_array, candidates);
            CPPUNIT_ASSERT(false);
        }
        catch(std::domain_error& e)
        {
            // there should be an exception
            CPPUNIT_ASSERT(true);
        }
    }

    void test_print_ballots_1 ()
    {
        std::ostringstream w;
        int candidates = 10;
        string string_array[candidates];


        for (int i=0; i<10; i++)
        {
            string_array[i] = "1 2 3";
            
            // empty lines... should throw an exception
            if (i == 5 || i ==9)
            {
                string_array[i] = "";
            }
        }

        try
        {
            voting_print(w, string_array, candidates);
            CPPUNIT_ASSERT(false);
        }
        catch(std::domain_error& e)
        {
            // there should be an exception
            CPPUNIT_ASSERT(true);
        }
    }

    void test_print_ballots_2 ()
    {
        std::ostringstream w;
        int candidates = 10;
        string string_array[candidates];


        for (int i=0; i<10; i++)
        {
            string_array[i] = "3 2 1";
        }

        try
        {
            voting_print(w, string_array, candidates, 10);
            CPPUNIT_ASSERT(w.str() == "3 2 1\n3 2 1\n3 2 1\n3 2 1\n3 2 1\n3 2 1\n3 2 1\n3 2 1\n3 2 1\n3 2 1\n");
        }
        catch(std::domain_error& e)
        {
            // NO exception should be thrown
            CPPUNIT_ASSERT(false);
        }
    }

    void test_print_ballots_3 ()
    {
        std::ostringstream w;
        int candidates = 10;
        string string_array[candidates];


        try
        {
            voting_print(w, string_array, candidates);
            CPPUNIT_ASSERT(false);
 
        }
        catch(std::domain_error& e)
        {
            // an exception SHOULD be thrown
            CPPUNIT_ASSERT(true);
        }
    }

    

    /*
    //  cnum (candidate number)
    */
    void test_cnum_1 ()
    {   
        // pass an int 5, must return an int 5
        int k =5;
        std::istringstream r("5\n");
        int number = voting_cnum(r, &k);
        CPPUNIT_ASSERT(number == 5);
        
    }

    void test_cnum_2 ()
    {   
        // pass an int 20, must return an int 20
        int k = 20;
        std::istringstream r("20\n");
        int number = voting_cnum(r, &k);
        CPPUNIT_ASSERT(number == 20);
        
    }
    
    void test_cnum_3 ()
    {   
        int k = 100;
        std::istringstream r("100\n");

        // must throw an exception b/c the number of candidate is more than 20
        try
        {
            voting_cnum(r, &k);
            CPPUNIT_ASSERT(false);
        }
        catch(std::domain_error& e)
        {
            CPPUNIT_ASSERT(true);
        }
    }

    void test_cnum_4 ()
    {   
        int k = 0;
        std::istringstream r("0\n");

        // must throw an exception b/c the number of candidate is 0
        try
        {
            voting_cnum(r, &k);
            CPPUNIT_ASSERT(false);
        }
        catch(std::domain_error& e)
        {
            CPPUNIT_ASSERT(true);
        }
    }
    
    void test_cnum_5 ()
    {   
        int k = -1;
        std::istringstream r("-1\n");

        // must throw an exception b/c the number of candidate is a negative number
        try
        {
            voting_cnum(r, &k);
            CPPUNIT_ASSERT(false);
        }
        catch(std::domain_error& e)
        {
            CPPUNIT_ASSERT(true);
        }
    }


    /*
    //  cnames (candidate names)
    */
    void test_cnames_1 ()
    {
        int candidate_number = 3;
        // creating input for cnames_1
        std::istringstream r("Thomas Aldo\nCollin Hazelnut\nYeun Kim\n");
        string names[1000];


        // must return three candidate names with NO exception being thrown
        try
        {
            voting_cnames(r, names, candidate_number);
            CPPUNIT_ASSERT(names[0] == "Thomas Aldo");
            CPPUNIT_ASSERT(names[1] == "Collin Hazelnut");
            CPPUNIT_ASSERT(names[2] == "Yeun Kim");
        }
        catch(std::domain_error& e)
        {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_cnames_2 ()
    {
        int candidate_number = 4;
        // creating input for cnames_1
        // a space added as fourth element
        std::istringstream r("Thomas Aldo\nCollin Hazelnut\nYeun Kim\n \n");
        string names[1000];

        // must return four candidate names with NO exception being thrown
        try
        {
            voting_cnames(r, names, candidate_number);
            CPPUNIT_ASSERT(names[0] == "Thomas Aldo");
            CPPUNIT_ASSERT(names[1] == "Collin Hazelnut");
            CPPUNIT_ASSERT(names[2] == "Yeun Kim");
            CPPUNIT_ASSERT(names[3] == " ");
        }
        catch(std::domain_error& e)
        {
            CPPUNIT_ASSERT(false);
        }
    }    

    void test_cnames_3 ()
    {
        int candidate_number = 5;
        // creating input for cnames_1
        // NOTHING added as fith element
        std::istringstream r("Thomas Aldo\nCollin Hazelnut\nYeun Kim\n \n\n");
        string names[1000];

        // must return five candidate names with NO exception being thrown
        try
        {
            voting_cnames(r, names, candidate_number);
            CPPUNIT_ASSERT(names[0] == "Thomas Aldo");
            CPPUNIT_ASSERT(names[1] == "Collin Hazelnut");
            CPPUNIT_ASSERT(names[2] == "Yeun Kim");
            CPPUNIT_ASSERT(names[3] == " ");
            CPPUNIT_ASSERT(names[4] == "");
        }
        catch(std::domain_error& e)
        {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_cnames_4 ()
    {
        int candidate_number = 6;
        // creating input for cnames_1
        // four sets of alphabets are added as sixth element (26 * 4 = 104 > 80)
        std::istringstream r("Thomas Aldo\nCollin Hazelnut\nYeun Kim\n \n\nabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz\n");
        string names[candidate_number];

        // must throw an exception since teh name is > 80 characters
        try
        {
            voting_cnames(r, names, candidate_number);
            CPPUNIT_ASSERT(false);
        }
        catch(std::domain_error& e)
        {
            CPPUNIT_ASSERT(true);
        }
    }


    /*
    //  ballots
    */

    void test_ballots_1 ()
    {
        std::istringstream r("1 2 3\n3 2 1\n\n");
        string ballots[1000];
        voting_ballots(r, ballots);
        CPPUNIT_ASSERT(ballots[0] == "1 2 3");
        CPPUNIT_ASSERT(ballots[1] == "3 2 1");
    }
    
    void test_ballots_2 ()
    {
        std::istringstream r("\n");
        string ballots[1000];
        voting_ballots(r, ballots);
        CPPUNIT_ASSERT(ballots[0].empty());
    }

    void test_ballots_3 ()
    {
        // 1000 Heys.. utilizing teh array in full size!
        // The first two heys are named "1stHey" and "2ndHey", and the last two heys are named "999thHey" and "1000thHey". 
        std::istringstream r("1stHey\n2ndHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\n999thHey\n1000thHey\n\n");
        string ballots[1000];
        
        try
        {       
            voting_ballots(r, ballots);
            CPPUNIT_ASSERT(ballots[0] == "1stHey");
            CPPUNIT_ASSERT(ballots[999] == "1000thHey");
        }
        catch(...)
        {
            // should NOT throw any exception
            CPPUNIT_ASSERT(false);
            
        }
    }


    void test_ballots_4 ()
    {

        // 1001 HEYs (over 1000 ballots). 
        // The first two heys are named "1stHey" and "2ndHey", and the last two heys are named "1000thHey" and "1001thHey". 
        std::istringstream r("1stHey\n2ndHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\nHey\n999thHey\n1000thHey\n1001thHey\n\n");
        string ballots[1000];

        // size of array increase to 1001
        // b/c if set to size 1000 and throw 1001 elements in it will result a segmentation fault
        // no way to catch segmentation fault.
        // voting_ballots function will only take first 1000 ranks as its ballot.

        try
        {       
            voting_ballots(r, ballots);
            CPPUNIT_ASSERT(ballots[0] == "1stHey");
            CPPUNIT_ASSERT(ballots[999] == "1000thHey");

            // though array has 1001th index exist, 
            // voting_ballots function does not put 1001thHey in it.
            CPPUNIT_ASSERT(ballots[1000] != "1001thHey");
        }
        catch(...)
        {
            // should NOT throw any exception
            CPPUNIT_ASSERT(false);
            
        }
    }

    void test_set_first_rank_1 ()
    {

        int candidates = 10;
        int ballots_num = 15;
        int first_ranks[ballots_num];
        int int_ballots[ballots_num][20];
        int index[ballots_num];
        

        // set ballots
        for (int i=0; i<ballots_num; i++)
        {
            // cleans ups..set slots with '0'
            first_ranks[i] = 0;
            index[i] = 0;

            for (int j=0; j<candidates; j++)
            {   
                // inser "1 2 3 4 5 6 7 8 9 10" into each row
                int_ballots[i][j] = j+1;
            }
        }
        voting_set_first_rank(candidates, ballots_num, first_ranks, int_ballots, index);
        
        // first ballots of first_rank should be '1'
        for (int i=0; i<ballots_num; i++)
        {
            CPPUNIT_ASSERT(first_ranks[i] == 1);
        }
    }
    
    void test_set_first_rank_2 ()
    {
        // test with simple numbrs
        int candidates = 2;
        int ballots_num = 5;
        int first_ranks[ballots_num];
        int int_ballots[ballots_num][20];
        int index[ballots_num];
        

        // set ballots
        for (int i=0; i<ballots_num; i++)
        {
            // cleans ups..set slots with '0'
            first_ranks[i] = 0;
            index[i] = 0;

            for (int j=0; j<candidates; j++)
            {   
                // inser "1 2 3 4 5 6 7 8 9 10" into each row
                int_ballots[i][j] = j+1;
            }
        }
        voting_set_first_rank(candidates, ballots_num, first_ranks, int_ballots, index);
        
        // first ballots of first_rank should be '1'
        for (int i=0; i<ballots_num; i++)
        {
            CPPUNIT_ASSERT(first_ranks[i] == 1);
        }
    }

    void test_set_first_rank_3 ()
    {
        // testout to the max
        int candidates = 20;
        int ballots_num = 1000;
        int first_ranks[ballots_num];
        int int_ballots[ballots_num][20];
        int index[ballots_num];
        

        // set ballots
        for (int i=0; i<ballots_num; i++)
        {
            // cleans ups..set slots with '0'
            first_ranks[i] = 0;
            index[i] = 0;

            for (int j=0; j<candidates; j++)
            {   
                // inser "1 2 3 4 5 6 7 8 9 10" into each row
                int_ballots[i][j] = j+1;
            }
        }
        voting_set_first_rank(candidates, ballots_num, first_ranks, int_ballots, index);
        
        // first ballots of first_rank should be '1'
        for (int i=0; i<ballots_num; i++)
        {
            CPPUNIT_ASSERT(first_ranks[i] == 1);
        }
    }

    void test_mark_1 ()
    {
        int candidates = 20;
        int ballots_num = 1000;
        int first_ranks[ballots_num];
        int int_ballots[ballots_num][20];
        int index[ballots_num];
        int loser_index[20];
        int winner_index[20];
        int vote_counts[20];
        bool winner = false;

        double majority = (double)ballots_num;
        majority = majority / 2;

        int flag = 0;
        int current = 0;
        int min = 2;
        int max = 5;

        for (int i=0; i<ballots_num; i++)
        {
            // cleans ups..set slots with '0'
            first_ranks[i] = 0;
            index[i] = 0;


            for (int j=0; j<candidates; j++)
            {   
                // inser "1 2 3 4 5 6 7 8 9 10" into each row
                int_ballots[i][j] = j+1;
                
                // clean ups...set slots with '0'
                loser_index[j] = 0;
                winner_index[j] = 0;
                vote_counts[j] = 0;

            }
        }

        voting_mark(flag, current, candidates, index, loser_index, min, max, winner_index, vote_counts, first_ranks, ballots_num,  majority, winner);

        // first ballots of first_rank should be '1'
        // for (int i=0; i<ballots_num; i++)
        // {
            CPPUNIT_ASSERT(vote_counts[first_ranks[0]-1] == 1);
        // }
    }


    /*
    //  suite
    */

    CPPUNIT_TEST_SUITE(TestVoting);


// cnum
    CPPUNIT_TEST(test_cnum_1);
    CPPUNIT_TEST(test_cnum_2);
    CPPUNIT_TEST(test_cnum_3);
    CPPUNIT_TEST(test_cnum_4);
    CPPUNIT_TEST(test_cnum_5);



//  print - no need anymore
    // CPPUNIT_TEST(test_print_int_1);
    // CPPUNIT_TEST(test_print_int_2);
    // CPPUNIT_TEST(test_print_int_3);

    // CPPUNIT_TEST(test_print_array_1);
    // CPPUNIT_TEST(test_print_array_2);
    // CPPUNIT_TEST(test_print_array_3);

    // CPPUNIT_TEST(test_print_string_1);
    // CPPUNIT_TEST(test_print_string_2);
    // CPPUNIT_TEST(test_print_string_3);

    // CPPUNIT_TEST(test_print_ballots_1);
    // CPPUNIT_TEST(test_print_ballots_2);
    // CPPUNIT_TEST(test_print_ballots_3);


// cnames
    CPPUNIT_TEST(test_cnames_1);
    CPPUNIT_TEST(test_cnames_2);
    CPPUNIT_TEST(test_cnames_3);
    CPPUNIT_TEST(test_cnames_4);


// ballots
    CPPUNIT_TEST(test_ballots_1);
    CPPUNIT_TEST(test_ballots_2);
    CPPUNIT_TEST(test_ballots_3);
    CPPUNIT_TEST(test_ballots_4);


// set_first_rank
    CPPUNIT_TEST(test_set_first_rank_1);
    CPPUNIT_TEST(test_set_first_rank_2);
    CPPUNIT_TEST(test_set_first_rank_3);


// mark
    CPPUNIT_TEST(test_mark_1);

    CPPUNIT_TEST_SUITE_END();
};

int main()
{
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}