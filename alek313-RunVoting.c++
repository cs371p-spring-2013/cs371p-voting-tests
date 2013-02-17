/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall Voting.c++ RunVoting.c++ -o RunVoting
    % valgrind RunVoting < RunVoting.in > RunVoting.out

To configure Doxygen:
    % doxygen -g
That creates the file "Doxyfile".
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    % doxygen Doxyfile
*/

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

//--------------------
// includes
//---------------------
#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <map>

#include "Voting.h"
using namespace std;

//------------------
// main
//------------------
int main () {
    solve(cin, cout);
    return 0;}


