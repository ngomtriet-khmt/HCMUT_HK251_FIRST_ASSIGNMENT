#include <iostream>
#include <cassert>
#include <stdexcept>
#include "VectorStore.h"

using namespace std;

class TestArrayList {
public:
    static void runAllTests() {
        cout << "=== Testing ArrayList Class ===" << endl;
        
        testConstructor();
        testCopyConstructor();
        testAssignmentOperator();
        testAdd();
        testAddAtIndex();
        testRemoveAt();
        testEmpty();
        testSize();
        testClear();
        testGet();
        testSet();
        testIndexOf();
        testContains();
        testIterator();
        
        cout << "ArrayList: All tests passed!" << endl << endl;
    }

private:
    static void testConstructor() {
        cout << "Testing ArrayList constructor..." << endl;
        ArrayList<int> list(5);
        assert(list.empty());
        assert(list.size() == 0);
        cout << "✓ Constructor test passed" << endl;
    }

    static void testCopyConstructor() {
        cout << "Testing ArrayList copy constructor..." << endl;
        ArrayList<int> original;
        original.add(1);
        original.add(2);
        original.add(3);
        
        ArrayList<int> copy(original);
        assert(copy.size() == 3);
        assert(copy.get(0) == 1);
        assert(copy.get(1) == 2);
        assert(copy.get(2) == 3);
        cout << "✓ Copy constructor test passed" << endl;
    }

    static void testAssignmentOperator() {
        cout << "Testing ArrayList assignment operator..." << endl;
        ArrayList<int> original;
        original.add(10);
        original.add(20);
        
        ArrayList<int> assigned;
        assigned = original;
        assert(assigned.size() == 2);
        assert(assigned.get(0) == 10);
        assert(assigned.get(1) == 20);
        cout << "✓ Assignment operator test passed" << endl;
    }

    static void testAdd() {
        cout << "Testing ArrayList add..." << endl;
        ArrayList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        
        assert(list.size() == 3);
        assert(list.get(0) == 1);
        assert(list.get(1) == 2);
        assert(list.get(2) == 3);
        cout << "✓ Add test passed" << endl;
    }

    static void testAddAtIndex() {
        cout << "Testing ArrayList add at index..." << endl;
        ArrayList<int> list;
        list.add(1);
        list.add(3);
        list.add(1, 2);  // Insert 2 at index 1
        
        assert(list.size() == 3);
        assert(list.get(0) == 1);
        assert(list.get(1) == 2);
        assert(list.get(2) == 3);

        // Test boundary conditions
        try {
            list.add(-1, 100);
            assert(false);  // Should not reach here
        } catch (const out_of_range& e) {
            cout << "✓ Invalid index exception caught correctly" << endl;
        }
        cout << "✓ Add at index test passed" << endl;
    }

    static void testRemoveAt() {
        cout << "Testing ArrayList removeAt..." << endl;
        ArrayList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        
        int removed = list.removeAt(1);
        assert(removed == 2);
        assert(list.size() == 2);
        assert(list.get(0) == 1);
        assert(list.get(1) == 3);

        // Test boundary conditions
        try {
            list.removeAt(10);
            assert(false);
        } catch (const out_of_range& e) {
            cout << "✓ Invalid removeAt index exception caught correctly" << endl;
        }
        cout << "✓ RemoveAt test passed" << endl;
    }

    static void testEmpty() {
        cout << "Testing ArrayList empty..." << endl;
        ArrayList<int> list;
        assert(list.empty());
        
        list.add(1);
        assert(!list.empty());
        
        list.removeAt(0);
        assert(list.empty());
        cout << "✓ Empty test passed" << endl;
    }

    static void testSize() {
        cout << "Testing ArrayList size..." << endl;
        ArrayList<int> list;
        assert(list.size() == 0);
        
        list.add(1);
        assert(list.size() == 1);
        
        list.add(2);
        assert(list.size() == 2);
        
        list.removeAt(0);
        assert(list.size() == 1);
        cout << "✓ Size test passed" << endl;
    }

    static void testClear() {
        cout << "Testing ArrayList clear..." << endl;
        ArrayList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        
        list.clear();
        assert(list.empty());
        assert(list.size() == 0);
        cout << "✓ Clear test passed" << endl;
    }

    static void testGet() {
        cout << "Testing ArrayList get..." << endl;
        ArrayList<int> list;
        list.add(10);
        list.add(20);
        list.add(30);
        
        assert(list.get(0) == 10);
        assert(list.get(1) == 20);
        assert(list.get(2) == 30);
        cout << "✓ Get test passed" << endl;
    }

    static void testSet() {
        cout << "Testing ArrayList set..." << endl;
        ArrayList<int> list;
        list.add(1);
        list.add(2);
        
        list.set(0, 100);
        list.set(1, 200);
        
        assert(list.get(0) == 100);
        assert(list.get(1) == 200);
        cout << "✓ Set test passed" << endl;
    }

    static void testIndexOf() {
        cout << "Testing ArrayList indexOf..." << endl;
        ArrayList<int> list;
        list.add(10);
        list.add(20);
        list.add(30);
        list.add(20);  // Duplicate
        
        assert(list.indexOf(10) == 0);
        assert(list.indexOf(20) == 1);  // Should return first occurrence
        assert(list.indexOf(30) == 2);
        assert(list.indexOf(999) == -1);  // Not found
        cout << "✓ IndexOf test passed" << endl;
    }

    static void testContains() {
        cout << "Testing ArrayList contains..." << endl;
        ArrayList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        
        assert(list.contains(1));
        assert(list.contains(2));
        assert(list.contains(3));
        assert(!list.contains(999));
        cout << "✓ Contains test passed" << endl;
    }

    static void testIterator() {
        cout << "Testing ArrayList iterator..." << endl;
        ArrayList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        
        // Test forward iteration
        int expected = 1;
        for (auto it = list.begin(); it != list.end(); ++it) {
            assert(*it == expected);
            expected++;
        }
        
        // Test range-based for loop
        expected = 1;
        for (int& value : list) {
            assert(value == expected);
            expected++;
        }
        
        cout << "✓ Iterator test passed" << endl;
    }
};