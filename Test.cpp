#include <ctime>
#include <string>
#include <vector>

#include "doctest.h"
#include "sources/OrgChart.hpp"

using namespace ariel;
using std::string; using std::vector; using std::cout; using std::endl;

string getRandWorker();


// Cases in which an exception should be thrown.
TEST_CASE("Exceptional cases"){

}

// Make a big random organization to check performances,
// and no leaks or bad dealing with pointers among the program.
TEST_CASE("Random Organization"){
    OrgChart organization;
    CHECK_NOTHROW(organization.add_root("A"));
    srand(time(0)); /* Make a random generator*/
    vector<string> workers;
    int workersAmount = 3;
    for (unsigned long i = 0; i < workersAmount; ++i) {
        string randWorker = getRandWorker();
        CHECK_NOTHROW(organization.add_sub("A", randWorker));
        workers.push_back(randWorker);
    }

    for (unsigned long j = 0; j < 100; ++j) {
        string randWorker = getRandWorker();
        unsigned long randPos = (unsigned long)(rand()) % workers.size();
        CHECK_NOTHROW(organization.add_sub(workers[randPos], randWorker));
        workers.push_back(randWorker);
    }

    cout << organization << endl;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_NOTHROW(cout << (*it) << " ");
    } // prints: CEO CTO CFO COO VP_SW VP_BI
    cout << endl;
    for (auto it = organization.begin_reverse_order(); it != organization.end_reverse_order(); ++it)
    {
        CHECK_NOTHROW(cout << (*it) << " ");
    } // prints: VP_SW VP_BI CTO CFO COO CEO
    cout << endl;
    for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
        CHECK_NOTHROW(cout << (*it) << " ");
    }  // prints: CEO CTO VP_SW CFO COO VP_BI
    cout << endl;
}

// Return a random worker in the organization which
// a random name contains only big chars.
string getRandWorker(){
    string charsSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string randWorker;
    int randLen = 1 + (rand() % 5);
    for (unsigned long j = 0; j < randLen; ++j) {
        unsigned long randPos = (unsigned long)(rand()) % charsSet.length();
        randWorker += charsSet[(unsigned long)randPos];
    }
    return randWorker;
}

