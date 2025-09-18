// Compile command: g++ -std=c++17 -Wall -Wextra -O2 test_main.cpp -o test_main && ./test_main

#define TESTING  // Enable testing mode for friend class access

#include <iostream>
#include <chrono>
#include "test_arraylist.cpp"
#include "test_singlylinkedlist.cpp"
#include "test_vectorstore.cpp"
#include "test_point.cpp"

using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "         DATA STRUCTURES TESTING        " << endl;
    cout << "========================================" << endl;
    cout << endl;

    auto start = chrono::high_resolution_clock::now();

    try {
        // Run all test suites
        TestPoint::runAllTests();
        TestArrayList::runAllTests();
        TestSinglyLinkedList::runAllTests();
        TestVectorStore::runAllTests();
        
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        
        cout << "========================================" << endl;
        cout << "         ALL TESTS COMPLETED!           " << endl;
        cout << "         Total time: " << duration.count() << " ms" << endl;
        cout << "========================================" << endl;
        
        return 0;
        
    } catch (const exception& e) {
        cout << "❌ Test failed with exception: " << e.what() << endl;
        return 1;
    } catch (...) {
        cout << "❌ Test failed with unknown exception!" << endl;
        return 1;
    }
}