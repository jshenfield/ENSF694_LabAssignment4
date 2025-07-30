#include <assert.h>
#include <iostream>
#include "lookupTable.h"
#include <cstring>
using namespace std;

LookupTable* run_test();
void print(LookupTable& lt);
void try_to_find(LookupTable& lt, int key);
void more_tests(LookupTable& lt);

int main()
{
    if(freopen("./data-part1.txt", "r", stdin) == NULL){
        std::cerr << "Sorry cannot open the input file..." << endl;
        exit(1);
    }
    cout << "Starting Test Run. Using input file." <<  endl;
    LookupTable* myList = run_test();
    cout << "\nMORE TESTS....." << endl;
    more_tests(*myList);
    cout<<"\n\nProgram terminated successfully.\n\n";
    return 0;
}

LookupTable* run_test() {
    const static  string prompt = " >> ";
    string command;
    string comment;
    int cnt = 0;
    LookupTable* myList = nullptr;
    getline(cin, comment);
    cout << "Line " << ++ cnt << prompt << "is comment" << endl;
    cin >> command;
    
    if (  cin.eof() ) {
        cout << "Exiting..." <<  endl;
        return myList;
    }
    
    cout << "Line " << ++cnt << prompt;
    
    if ( command == "new" ) {
        myList = new LookupTable();
        cout << " Passed" <<  endl;
    }
    else {
        cout << "\nNo object was created... ";
        exit(1);
    }
    
    while ( true ) {
        cin >> command;
        
        if (  cin.eof() ) {
            cout << "Reached End of Input File" <<  endl;
            return myList;
        }
        
        cout << "Line "<< ++cnt << prompt;
        
        if ( command == "size" ) {
            int expected_size;
            cin >> expected_size;
            int actual_size = myList->size();
            if ( actual_size == expected_size ) {
                cout << " Passed" <<  endl;
            } else {
                cout << " Failed in size(): expected value is " << expected_size << "not " << actual_size <<  endl;
            }
        } else if ( command == "isEmpty" ) {
            bool expected_empty;
            cin >> expected_empty;
            bool actual_empty;
            actual_empty= myList->isEmpty();
            if ( actual_empty == expected_empty ) {
                cout << " Passed" <<  endl;
            } else {
                cout << " Failed in is_empty(): expected value is " << expected_empty << ", not " << actual_empty <<  endl;
            }
        }
        else if ( command == "retrieve_at" ) {
            int expected_key;
            int index;
            cin >> index >> expected_key;
            
            int* actual_key = myList->retrieve_at(index);
            
            if ( *actual_key == expected_key ) {
                cout << " Passed" <<  endl;
            } else {
                cout << " Failed in rettrieve_at: expected key is " << expected_key << ", not " << actual_key <<  endl;
            }
        }
        else if ( command == "find" ) {
            string expected_datum;
            int key;
            cin >> key;
            getline(cin,expected_datum);
            
            myList->find(key);
            if ( myList->cursor_datum() == expected_datum){
                cout << " Passed" <<  endl;
            } else {
                cout << " Failed in find: expected data is " << expected_datum << ", not " << myList->cursor_datum() <<  endl;
            }
        }
        else if ( command == "insert" ) {
            int index;
            int key;
            string name;
            
            cin >> index >>  key;
            getline(cin, name);
            Pair pair(key, name);
            myList->insert(pair);
            if (*myList->retrieve_at(index) == key){
                cout << " Passed" << endl;
            }
            else {
                cout << "Failed in insert. " << endl;
            }
            
        }
        
        else if ( command == "remove" ) {
            int expected_removed_key;
            
            cin  >> expected_removed_key;
            
            int actual_removed_key = myList->remove(expected_removed_key);
            
            if ( actual_removed_key == expected_removed_key ) {
                cout << " Passed" <<  endl;
            } else {
                cout << " Failed in remove(): expecte key is " << expected_removed_key << ", not " << actual_removed_key <<  endl;
            }
        }
    }
    return myList;
}

void print(LookupTable& lt)
{
    if (lt.size() == 0)
        cout << "  Table is EMPTY.\n";
    for (lt.go_to_first(); lt.cursor_ok(); lt.step_fwd()) {
        lt.display();
    }
}

void try_to_find(LookupTable& lt, int key)
{
    lt.find(key);
    if (lt.cursor_ok()) {
        cout << "\nFound key:";
        lt.display();
    }
    else
        cout << "\nSorry, I couldn't find key: " << key << " in the table.\n";
}

void more_tests(LookupTable& lt) {
    // Insert using new keys.
    cout << "Inserting 3 pairs: " << endl;
    lt.insert(Pair (8002, "Joe Morrison"));
    lt.insert(Pair (8004, "Jack Lewis"));
    lt.insert(Pair (8001, "Tim Hardy"));
    cout << "Assert: three data must be in the list: " << endl;
    assert(lt.size() == 3);
    cout << "Okay. Passed. " << endl;
    cout << "Removing one pair with the key 8004: " << endl;
    lt.remove(8004);
    cout << "Assert: one pair is removed. " << endl;
    assert(lt.size() == 2);
    cout << "Okay. Passed. " << endl;
    cout << "\nPrinting table after inserting 3 and removing 1...\n";
    cout << "\nExpected to dispaly 8001 Tim Hardy and 8002 Joe Morrison: " << endl;
    print(lt);
    
    // Pretend that a user is trying to look up customers info.
    cout << "\nLet's look up some keys 8001 and 8000...\n";
    cout << "Expected to find 8001 and NOT to find 8000...\n";
    try_to_find(lt, 8001);
    try_to_find(lt, 8000);
    
    //test copying
    lt.go_to_first();
    lt.step_fwd();
    LookupTable clt(lt);
    assert(clt.cursor_datum() == "Joe Morrison");
    
    cout << "\nTest copying: keys should be 8001, and 8002\n";
    print(clt);
    lt.remove(8002);
    
    //Assignment operator check.
    clt= lt;
    cout << "\nTest assignment operator (key expected be 8001):\n";
    print(clt);
    
    //Wipe out the entries in the table.
    lt.make_empty();
    cout << "\nPrinting table for the last time: Table should be empty...\n";
    print(lt);
    
    cout << "***----Finished tests on Customers Lookup Table <not template>-----***\n";
    cout << "PRESS RETURN TO CONTINUE.";
    cin.get();
}

