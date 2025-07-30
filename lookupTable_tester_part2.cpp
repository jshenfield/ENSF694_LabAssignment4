#include <assert.h>
#include <iostream>
#include "lookupTable.h"
#include <cstring>
using namespace std;

void run_test();
//void print(LookupTable& lt);
//void try_to_find(LookupTable& lt, int key);

int main()
{
    if(!freopen("/Users/mahmoodmoussavi/Dropbox/ENSF 694 Labs/Lab3/Lookup Table Part II/Lookup Table/Lookup Table/data-part2.txt", "r", stdin)){
        std::cerr << "Failed to use the input file";
        exit(1);
    }
    
    cout << "Starting Test Run. Using input file." <<  endl;
    run_test();
    cout << "Finishing Test Run" <<  endl;
    cout << "Showing Data in the List:" << endl;
    cout<<"\n\nProgram terminated successfully.\n\n";
    return 0;
}

void run_test() {
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
        return;
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
            cout << "Exiting..." <<  endl;
            return;
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
            string expected_label;
            int key;
            cin >> key;
            getline(cin,expected_label);
            
            myList->find(key);
            string s = myList->cursor_datum().get_label();
            
            if ( s == expected_label){
                cout << " Passed" <<  endl;
            } else {
                cout << " Failed in find: expected data is " << expected_label << ", not " << myList->cursor_datum().get_label() <<  endl;
            }
        }
        else if ( command == "insert" ) {
            int index;
            int key;
            int x, y;
            string label;
            
            cin >> index >> key >> x >> y;
            getline(cin, label);
            Point p(x, y, label.c_str());
            Pair pair(key, p);
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
}
/*
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

*/
