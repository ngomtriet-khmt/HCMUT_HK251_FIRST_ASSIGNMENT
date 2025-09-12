#include <iostream>
#include <cassert>
#include <stdexcept>
#include "VectorStore.h"

using namespace std;

class TestSinglyLinkedList {
public:
    static void runAllTests() {
        cout << "=== Testing SinglyLinkedList Class ===" << endl;
        
        testConstructor();
        testAdd();
        testAddAtIndex();
        testRemoveAt();
        testRemoveItem();
        testEmpty();
        testSize();
        testClear();
        testGet();
        testIndexOf();
        testContains();
        testIterator();
        
        cout << "SinglyLinkedList: All tests passed!" << endl << endl;
    }

private:
    static void testConstructor() {
        cout << "Testing SinglyLinkedList constructor..." << endl;
        SinglyLinkedList<int> list;
        assert(list.empty());
        assert(list.size() == 0);
        cout << "✓ Constructor test passed" << endl;
    }

    static void testAdd() {
        cout << "Testing SinglyLinkedList add..." << endl;
        SinglyLinkedList<int> list;
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
        cout << "Testing SinglyLinkedList add at index..." << endl;
        SinglyLinkedList<int> list;
        list.add(1);
        list.add(3);
        list.add(1, 2);  // Insert 2 at index 1
        
        assert(list.size() == 3);
        assert(list.get(0) == 1);
        assert(list.get(1) == 2);
        assert(list.get(2) == 3);

        // Test adding at beginning
        list.add(0, 0);
        assert(list.get(0) == 0);
        assert(list.size() == 4);

        // Test adding at end
        list.add(list.size(), 4);
        assert(list.get(list.size() - 1) == 4);
        assert(list.size() == 5);

        // Test invalid index
        try {
            list.add(-1, 100);
            assert(false);
        } catch (const out_of_range& e) {
            cout << "✓ Invalid index exception caught correctly" << endl;
        }
        cout << "✓ Add at index test passed" << endl;
    }

    static void testRemoveAt() {
        cout << "Testing SinglyLinkedList removeAt..." << endl;
        SinglyLinkedList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        list.add(4);
        
        // Remove from middle
        int removed = list.removeAt(1);
        assert(removed == 2);
        assert(list.size() == 3);
        assert(list.get(0) == 1);
        assert(list.get(1) == 3);
        assert(list.get(2) == 4);

        // Remove from beginning
        removed = list.removeAt(0);
        assert(removed == 1);
        assert(list.size() == 2);
        assert(list.get(0) == 3);

        // Remove from end
        removed = list.removeAt(list.size() - 1);
        assert(removed == 4);
        assert(list.size() == 1);
        assert(list.get(0) == 3);

        // Test invalid index
        try {
            list.removeAt(10);
            assert(false);
        } catch (const out_of_range& e) {
            cout << "✓ Invalid removeAt index exception caught correctly" << endl;
        }
        cout << "✓ RemoveAt test passed" << endl;
    }

    static void testRemoveItem() {
        cout << "Testing SinglyLinkedList removeItem..." << endl;
        SinglyLinkedList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        list.add(2);  // Duplicate
        
        // Remove existing item (should remove first occurrence)
        bool removed = list.removeItem(2);
        assert(removed);
        assert(list.size() == 3);
        assert(list.get(0) == 1);
        assert(list.get(1) == 3);
        assert(list.get(2) == 2);  // Second occurrence should remain

        // Remove non-existing item
        removed = list.removeItem(999);
        assert(!removed);
        assert(list.size() == 3);
        
        cout << "✓ RemoveItem test passed" << endl;
    }

    static void testEmpty() {
        cout << "Testing SinglyLinkedList empty..." << endl;
        SinglyLinkedList<int> list;
        assert(list.empty());
        
        list.add(1);
        assert(!list.empty());
        
        list.removeAt(0);
        assert(list.empty());
        cout << "✓ Empty test passed" << endl;
    }

    static void testSize() {
        cout << "Testing SinglyLinkedList size..." << endl;
        SinglyLinkedList<int> list;
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
        cout << "Testing SinglyLinkedList clear..." << endl;
        SinglyLinkedList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        
        list.clear();
        assert(list.empty());
        assert(list.size() == 0);
        cout << "✓ Clear test passed" << endl;
    }

    static void testGet() {
        cout << "Testing SinglyLinkedList get..." << endl;
        SinglyLinkedList<int> list;
        list.add(10);
        list.add(20);
        list.add(30);
        
        assert(list.get(0) == 10);
        assert(list.get(1) == 20);
        assert(list.get(2) == 30);

        // Test invalid index
        try {
            list.get(10);
            assert(false);
        } catch (const out_of_range& e) {
            cout << "✓ Invalid get index exception caught correctly" << endl;
        }
        cout << "✓ Get test passed" << endl;
    }

    static void testIndexOf() {
        cout << "Testing SinglyLinkedList indexOf..." << endl;
        SinglyLinkedList<int> list;
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
        cout << "Testing SinglyLinkedList contains..." << endl;
        SinglyLinkedList<int> list;
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
        cout << "Testing SinglyLinkedList iterator..." << endl;
        SinglyLinkedList<int> list;
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

    static void testFloatList() {
        cout << "Testing SinglyLinkedList with float..." << endl;
        SinglyLinkedList<float> list;
        list.add(1.5f);
        list.add(2.7f);
        list.add(3.14f);
        
        assert(list.size() == 3);
        assert(abs(list.get(0) - 1.5f) < 1e-6);
        assert(abs(list.get(1) - 2.7f) < 1e-6);
        assert(abs(list.get(2) - 3.14f) < 1e-6);
        cout << "✓ Float list test passed" << endl;
    }
};