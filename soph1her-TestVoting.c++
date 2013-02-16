//---------------
// TestVoting.c++
//
// Sophia Hernandez
// Daniel Gresham
//
//---------------

    #include "cppunit/extensions/HelperMacros.h"
    #include "cppunit/TestFixture.h"
    #include "cppunit/TextTestRunner.h"
    
    #include "Voting.h"

struct TestVoting : CppUnit:: TestFixture{

    //testing V_eval does not return anything
    
    // Voting_read
    void test_read_1(){
        std::istringstream r("1\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1");
        int num_elec;
        int num_cand;
        const bool valid = Voting_read(r, num_elec, num_cand);
        CPPUNIT_ASSERT(valid == true);
        CPPUNIT_ASSERT(num_elec == 1);
        CPPUNIT_ASSERT(num_cand == 3);
    }
    void test_read_2(){
        std::istringstream r("2\n2\nJohn Doe\nJane Smith\n1 2 \n2 1\n2 1\n\n3\nJohn Does\nJanie Smith\nJoe No\n2 3 1 \n3 2 1\n2 1 3");
        int num_elec;
        int num_cand;
        const bool valid = Voting_read(r, num_elec, num_cand);
        CPPUNIT_ASSERT(valid == true);
        CPPUNIT_ASSERT(num_elec == 2);
        CPPUNIT_ASSERT(num_cand == 3);  // last election's number of candidates
    }
    void test_read_3(){
        std::istringstream r("3\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n\n3\nJohn Does\nJanie Smith\nJoe No\n2 3 1 \n3 2 1\n2 1 3\n\n5\nCand #1\nCand #2\nCand #3\nCand #4\nCand #5\n4 5 3 2 1\n5 1 2 3 4\n2 5 4 1 3\n4 5 3 1 2\n3 1 4 5 2");
       r.clear();
       int num_elec;
        int num_cand;
        const bool valid = Voting_read(r, num_elec, num_cand);
        CPPUNIT_ASSERT(valid == true);
        CPPUNIT_ASSERT(num_elec == 3);
        CPPUNIT_ASSERT(num_cand == 5);
    }
    
    // Voting_write also returns void, hence no unit test here, but buffer full in solve
    // so writes from above read tests are included in the below test_solve_1 case
    
    // V_solve
    void test_solve_1(){
    	istringstream r("1\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1");
        ostringstream w;
        V_solve(r, w);
    	CPPUNIT_ASSERT(w.str() == "Jane Smith\nJane Smith\n\nJanie Smith\nJane Smith\n\nJanie Smith\n\nCand #4\nJane Smith\n");
    }
    void test_solve_2(){
    istringstream r("1\n2\nM1\nM2\n1 2\n1 2\n2 1\n2 1\n");
        ostringstream w;
        V_solve(r, w);
    	CPPUNIT_ASSERT(w.str() == "M1\nM2\n");
    }
    void test_solve_3(){
    	ifstream r ("./RunVoting.in");
    	ostringstream w;
    	V_solve(r, w);
    	CPPUNIT_ASSERT(w.str() == "Cand #1\n\nCand #1\n\Cand #2\nCand #3\nCand #4\n\nCand #4\n\nCand #4\n\nCand #2\n\nCand #1\n\nCand #5\n\nCand #3\n\nCand #2\n\nCand #10\n");
    }
    
    
    CPPUNIT_TEST_SUITE(TestVoting);

    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);     
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
   	CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST_SUITE_END();};
    
    //main
    
int main(){
    using namespace std;
    ios_base::sync_with_stdio(false);
    cout << "TestVoting.c++" << endl;
    
    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();
    
    cout << "Done." << endl;
    return 0;
}