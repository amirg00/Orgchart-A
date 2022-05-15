#include <iostream>
#include <ctime>
#include <vector>
#include "sources/OrgChart.hpp"


using namespace ariel;
using std::cout; using std::endl; using std::string; using std::cin; using std::vector;

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

void RandOrganization(int amount){
    OrgChart organization;
    organization.add_root("A");
    srand(time(0)); /* Make a random generator*/
    vector<string> workers;
    int workersAmount = 3;

    // First workers creation
    for (unsigned long i = 0; i < workersAmount; ++i) {
        string randWorker = getRandWorker();
        organization.add_sub("A", randWorker);
        workers.push_back(randWorker);
    }
    // All other 100 workers in organization
    for (unsigned long j = 0; j < amount; ++j) {
        string randWorker = getRandWorker();
        unsigned long randPos = (unsigned long)(rand()) % workers.size();
        organization.add_sub(workers[randPos], randWorker);
        workers.push_back(randWorker);
    }
    cout << organization << endl;

    //==========================================/
    /************ Print Traversals *************/
    //==========================================/
    cout << "/************ ORGANIZATION TRAVERSALS *************/" << endl;
    cout << "====== LEVEL ORDER ======" << endl;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        cout << (*it) << " ";
    }
    cout << endl;
    cout << "====== REVERSE LEVEL ORDER ======" << endl;
    for (auto it = organization.begin_reverse_order(); it != organization.end_reverse_order(); ++it)
    {
        cout << (*it) << " ";
    }
    cout << endl;
    cout << "====== PREORDER ======" << endl;
    for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
        cout << (*it) << " ";
    }
    cout << endl;
}

int main() {
    cout << "/=============================================/\n"
            "/*********** GENERATE ORGANIZATION ***********/\n"
            "/=============================================/" << endl;
    cout << "Welcome!" << '\n';
    while(true){
        cout << "Choose preferred way to generate your organization: (manually/random)?" << endl;
        string answer;
        cin >> answer;
        if (answer == "manually"){
            OrgChart tmpOrganization;
            cout << "Enter root name: ";
            string rootName;
            cin >> rootName;
            tmpOrganization.add_root(rootName);

            while (true){
                cout << "Write 'exit exit' if you want to exit in any step." << endl;
                cout << "Enter touple (super, sub): ";
                string super, sub;
                cin >> super; cin >> sub;
                if (super == "exit"){
                    cout << "Here is your organization: \n" << tmpOrganization << endl;
                    //==========================================/
                    /************ Print Traversals *************/
                    //==========================================/
                    cout << "/************ ORGANIZATION TRAVERSALS *************/" << endl;
                    cout << "====== LEVEL ORDER ======" << endl;
                    for (auto it = tmpOrganization.begin_level_order(); it != tmpOrganization.end_level_order(); ++it)
                    {
                        cout << (*it) << " ";
                    }
                    cout << endl;
                    cout << "====== REVERSE LEVEL ORDER ======" << endl;
                    for (auto it = tmpOrganization.begin_reverse_order(); it != tmpOrganization.end_reverse_order(); ++it)
                    {
                        cout << (*it) << " ";
                    }
                    cout << endl;
                    cout << "====== PREORDER ======" << endl;
                    for (auto it=tmpOrganization.begin_preorder(); it!=tmpOrganization.end_preorder(); ++it) {
                        cout << (*it) << " ";
                    }
                    cout << endl;
                    break;
                }
                tmpOrganization.add_sub(super, sub);
            }

        }
        else if (answer == "random"){
            cout << "Enter amount of the organization's participants amount: ";
            int amount = 0;
            cin >> amount;
            if (amount < 0){ // Amount cannot be negative
                break;
            }
            RandOrganization(amount);
        }

        else if (answer == "exit"){
            break;
        }
        else{
            cout << "Bad input!" << endl;
            continue;
        }
    }
}


