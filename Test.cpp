#include <ctime>
#include <string>
#include <vector>

#include "doctest.h"
#include "sources/OrgChart.hpp"

using namespace ariel;
using std::string; using std::vector; using std::cout; using std::endl;

string getRandWorker();

// Check for iterators' operators: check their correctness for traversals
// and check to make sure iterators have all needed operators.
TEST_CASE("Iterators Operations"){
    OrgChart organization;
    CHECK_NOTHROW(organization.add_root("AAA")
    .add_sub("AAA", "BBB")
    .add_sub("AAA", "CCC")
    .add_sub("AAA", "DDD")
    .add_sub("DDD", "EEE")
    .add_sub("CCC", "FFF")
    .add_sub("FFF", "GGG"));
    /*
       AAA
       |--------|--------|
       BBB     CCC      DDD
                |        |
               FFF      EEE
                |
               GGG
     */
    // CHECK ITERATOR OPERATIONS FOR EACH ONE OF THEM
    // LEVEL ORDER //
    auto it = organization.begin_level_order();
    CHECK((*it) == "AAA");      /* '*' operator*/
    CHECK(*(++it) == "BBB");    /* prefix '++' operator*/
    CHECK(*(it++) == "BBB");    /* postfix '++' operator*/
    CHECK((*it) == "CCC");
    CHECK(it->size() == 3);
    CHECK(it == it);
    CHECK(it != organization.end_level_order());

    // REVERSE LEVEL ORDER //
    auto it2 = organization.begin_reverse_order();
    CHECK((*it2) == "GGG");      /* '*' operator*/
    CHECK(*(++it2) == "FFF");    /* prefix '++' operator*/
    CHECK(*(it2++) == "FFF");    /* postfix '++' operator*/
    CHECK((*it2) == "EEE");
    CHECK(it2->size() == 3);
    CHECK(it2 == it2);
    CHECK(it2 != organization.end_reverse_order());

    // LEVEL ORDER //
    auto it3 = organization.begin_preorder();
    CHECK((*it3) == "AAA");      /* '*' operator*/
    CHECK(*(++it3) == "BBB");    /* prefix '++' operator*/
    CHECK(*(it3++) == "BBB");    /* postfix '++' operator*/
    CHECK((*it3) == "CCC");
    CHECK(it3->size() == 3);
    CHECK(it3 == it3);
    CHECK(it3 != organization.end_preorder());

    // TEST TRAVERSALS
    vector<string> levelOrder = {"AAA", "BBB", "CCC", "DDD", "FFF", "EEE", "GGG"};
    vector<string> ReverseLevelOrder = {"GGG", "FFF", "EEE", "BBB", "CCC", "DDD", "AAA"};
    vector<string> Preorder = {"AAA", "BBB", "CCC", "FFF", "GGG", "DDD", "EEE"};

    // Should work as levelOrder
    size_t cnt = 0;
    for (const auto& levelElement: organization){
        CHECK(levelElement == levelOrder[cnt++]);
    }

    // Test again level order to see if it still works
    // with the original approach.
    cnt = 0; // reset counter
    for (auto iter = organization.begin_level_order(); iter != organization.end_level_order(); ++iter)
    {
        CHECK((*iter) == levelOrder[cnt++]);
    }

    cnt = 0; // reset counter
    for (auto iter = organization.begin_reverse_order(); iter != organization.end_reverse_order(); ++iter)
    {
        CHECK((*iter) == ReverseLevelOrder[cnt++]);
    }

    cnt = 0; // reset counter
    for (auto iter = organization.begin_preorder(); iter != organization.end_preorder(); ++iter)
    {
        CHECK((*iter) == Preorder[cnt++]);
    }
}

// Test cases in which an exception should be thrown.
TEST_CASE("Exceptional cases"){
    OrgChart organization;

    /*Add sub entity before adding a root entity*/
    CHECK_THROWS(organization.add_sub("A", "B"));

    /*Add blank root name*/
    CHECK_THROWS(organization.add_root(""));

    /*Add blank sub name*/
    CHECK_NOTHROW(organization.add_root("A"));
    CHECK_THROWS(organization.add_sub("A", ""));

    /*Add blank superior name*/
    CHECK_THROWS(organization.add_sub("", "D"));

    /*Superior element cannot be found*/
    CHECK_NOTHROW(organization.add_sub("A", "B"));
    CHECK_THROWS(organization.add_sub("C", "D"));

    /*Root already exist*/
    CHECK_THROWS(organization.add_root("A"));
    CHECK_THROWS(organization.add_root("F"));
}

// Make a big random organization to check performances,
// and no leaks or bad dealing with pointers among the program.
TEST_CASE("Random Organization"){
    OrgChart organization;
    CHECK_NOTHROW(organization.add_root("A"));
    srand(time(0)); /* Make a random generator*/
    vector<string> workers;
    int workersAmount = 3;

    // First workers creation
    for (unsigned long i = 0; i < workersAmount; ++i) {
        string randWorker = getRandWorker();
        CHECK_NOTHROW(organization.add_sub("A", randWorker));
        workers.push_back(randWorker);
    }
    // All other 100 workers in organization
    for (unsigned long j = 0; j < 100; ++j) {
        string randWorker = getRandWorker();
        unsigned long randPos = (unsigned long)(rand()) % workers.size();
        CHECK_NOTHROW(organization.add_sub(workers[randPos], randWorker));
        workers.push_back(randWorker);
    }
    cout << organization << endl;

    // Iterators check stability with big organization
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_NOTHROW(cout << (*it) << " ");
    }
    cout << endl;
    for (auto it = organization.begin_reverse_order(); it != organization.end_reverse_order(); ++it)
    {
        CHECK_NOTHROW(cout << (*it) << " ");
    }
    cout << endl;
    for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
        CHECK_NOTHROW(cout << (*it) << " ");
    }
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