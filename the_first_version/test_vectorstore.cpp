#include <iostream>
#include <cassert>
#include <stdexcept>
#include <cmath>
#include "VectorStore.h"

using namespace std;

// Mock embedding function for testing
SinglyLinkedList<float>* mockEmbeddingFunction(const string& text) {
    SinglyLinkedList<float>* vector = new SinglyLinkedList<float>();
    
    // Simple mock: convert text length to a vector
    float baseValue = static_cast<float>(text.length());
    vector->add(baseValue);
    vector->add(baseValue * 0.5f);
    vector->add(baseValue * 0.25f);
    
    return vector;
}

class TestVectorStore {
public:
    static void runAllTests() {
        cout << "=== Testing VectorStore Class ===" << endl;
        
        testConstructor();
        testAddText();
        testGetVector();
        testGetRawText();
        testGetId();
        testRemoveAt();
        testUpdateText();
        testEmpty();
        testSize();
        testClear();
        testSetEmbeddingFunction();
        testCosineSimilarity();
        testL1Distance();
        testL2Distance();
        testFindNearest();
        testTopKNearest();
        
        cout << "VectorStore: All tests passed!" << endl << endl;
    }

private:
    static void testConstructor() {
        cout << "Testing VectorStore constructor..." << endl;
        VectorStore store(128);
        assert(store.empty());
        assert(store.size() == 0);
        cout << "✓ Constructor test passed" << endl;
    }

    static void testAddText() {
        cout << "Testing VectorStore addText..." << endl;
        VectorStore store(3, mockEmbeddingFunction);
        
        store.addText("hello");
        assert(store.size() == 1);
        assert(!store.empty());
        
        store.addText("world");
        assert(store.size() == 2);
        
        cout << "✓ AddText test passed" << endl;
    }

    static void testGetVector() {
        cout << "Testing VectorStore getVector..." << endl;
        VectorStore store(3, mockEmbeddingFunction);
        
        store.addText("test");
        SinglyLinkedList<float>& vector = store.getVector(0);
        
        // Mock function should create vector [4.0, 2.0, 1.0] for "test" (length=4)
        assert(vector.size() == 3);
        assert(abs(vector.get(0) - 4.0f) < 1e-6);
        assert(abs(vector.get(1) - 2.0f) < 1e-6);
        assert(abs(vector.get(2) - 1.0f) < 1e-6);
        
        cout << "✓ GetVector test passed" << endl;
    }

    static void testGetRawText() {
        cout << "Testing VectorStore getRawText..." << endl;
        VectorStore store(3, mockEmbeddingFunction);
        
        store.addText("hello world");
        assert(store.getRawText(0) == "hello world");
        
        store.addText("test text");
        assert(store.getRawText(1) == "test text");
        
        cout << "✓ GetRawText test passed" << endl;
    }

    static void testGetId() {
        cout << "Testing VectorStore getId..." << endl;
        VectorStore store(3, mockEmbeddingFunction);
        
        store.addText("first");
        store.addText("second");
        store.addText("third");
        
        // IDs should be assigned sequentially starting from 0
        assert(store.getId(0) == 0);
        assert(store.getId(1) == 1);
        assert(store.getId(2) == 2);
        
        cout << "✓ GetId test passed" << endl;
    }

    static void testRemoveAt() {
        cout << "Testing VectorStore removeAt..." << endl;
        VectorStore store(3, mockEmbeddingFunction);
        
        store.addText("first");
        store.addText("second");
        store.addText("third");
        
        assert(store.size() == 3);
        bool removed = store.removeAt(1);
        assert(removed);
        assert(store.size() == 2);
        
        // After removing index 1, the remaining texts should be "first" and "third"
        assert(store.getRawText(0) == "first");
        assert(store.getRawText(1) == "third");
        
        // Test invalid index
        bool invalidRemove = store.removeAt(10);
        assert(!invalidRemove);
        
        cout << "✓ RemoveAt test passed" << endl;
    }

    static void testUpdateText() {
        cout << "Testing VectorStore updateText..." << endl;
        VectorStore store(3, mockEmbeddingFunction);
        
        store.addText("original");
        assert(store.getRawText(0) == "original");
        
        bool updated = store.updateText(0, "updated");
        assert(updated);
        assert(store.getRawText(0) == "updated");
        
        // Vector should also be updated
        SinglyLinkedList<float>& vector = store.getVector(0);
        // "updated" has length 7, so mock should create [7.0, 3.5, 1.75]
        assert(abs(vector.get(0) - 7.0f) < 1e-6);
        assert(abs(vector.get(1) - 3.5f) < 1e-6);
        assert(abs(vector.get(2) - 1.75f) < 1e-6);
        
        // Test invalid index
        bool invalidUpdate = store.updateText(10, "invalid");
        assert(!invalidUpdate);
        
        cout << "✓ UpdateText test passed" << endl;
    }

    static void testEmpty() {
        cout << "Testing VectorStore empty..." << endl;
        VectorStore store(3, mockEmbeddingFunction);
        
        assert(store.empty());
        
        store.addText("test");
        assert(!store.empty());
        
        store.clear();
        assert(store.empty());
        
        cout << "✓ Empty test passed" << endl;
    }

    static void testSize() {
        cout << "Testing VectorStore size..." << endl;
        VectorStore store(3, mockEmbeddingFunction);
        
        assert(store.size() == 0);
        
        store.addText("first");
        assert(store.size() == 1);
        
        store.addText("second");
        assert(store.size() == 2);
        
        store.removeAt(0);
        assert(store.size() == 1);
        
        cout << "✓ Size test passed" << endl;
    }

    static void testClear() {
        cout << "Testing VectorStore clear..." << endl;
        VectorStore store(3, mockEmbeddingFunction);
        
        store.addText("first");
        store.addText("second");
        store.addText("third");
        
        assert(store.size() == 3);
        store.clear();
        assert(store.size() == 0);
        assert(store.empty());
        
        cout << "✓ Clear test passed" << endl;
    }

    static void testSetEmbeddingFunction() {
        cout << "Testing VectorStore setEmbeddingFunction..." << endl;
        VectorStore store(3);
        
        store.setEmbeddingFunction(mockEmbeddingFunction);
        store.addText("test");
        
        // Should use the new embedding function
        SinglyLinkedList<float>& vector = store.getVector(0);
        assert(vector.size() == 3);
        assert(abs(vector.get(0) - 4.0f) < 1e-6);  // "test" length = 4
        
        cout << "✓ SetEmbeddingFunction test passed" << endl;
    }

    static void testCosineSimilarity() {
        cout << "Testing VectorStore cosineSimilarity..." << endl;
        VectorStore store(3, mockEmbeddingFunction);
        
        SinglyLinkedList<float> v1, v2;
        v1.add(1.0f); v1.add(0.0f); v1.add(0.0f);
        v2.add(0.0f); v2.add(1.0f); v2.add(0.0f);
        
        // Orthogonal vectors should have cosine similarity of 0
        double sim = store.cosineSimilarity(v1, v2);
        assert(abs(sim - 0.0) < 1e-6);
        
        // Identical vectors should have cosine similarity of 1
        double sim2 = store.cosineSimilarity(v1, v1);
        assert(abs(sim2 - 1.0) < 1e-6);
        
        cout << "✓ CosineSimilarity test passed" << endl;
    }

    static void testL1Distance() {
        cout << "Testing VectorStore l1Distance..." << endl;
        VectorStore store(3, mockEmbeddingFunction);
        
        SinglyLinkedList<float> v1, v2;
        v1.add(1.0f); v1.add(2.0f); v1.add(3.0f);
        v2.add(4.0f); v2.add(5.0f); v2.add(6.0f);
        
        // L1 distance should be |1-4| + |2-5| + |3-6| = 3 + 3 + 3 = 9
        double dist = store.l1Distance(v1, v2);
        assert(abs(dist - 9.0) < 1e-6);
        
        // Distance to itself should be 0
        double dist2 = store.l1Distance(v1, v1);
        assert(abs(dist2 - 0.0) < 1e-6);
        
        cout << "✓ L1Distance test passed" << endl;
    }

    static void testL2Distance() {
        cout << "Testing VectorStore l2Distance..." << endl;
        VectorStore store(3, mockEmbeddingFunction);
        
        SinglyLinkedList<float> v1, v2;
        v1.add(0.0f); v1.add(0.0f); v1.add(0.0f);
        v2.add(3.0f); v2.add(4.0f); v2.add(0.0f);
        
        // L2 distance should be sqrt(3^2 + 4^2 + 0^2) = sqrt(9 + 16) = 5
        double dist = store.l2Distance(v1, v2);
        assert(abs(dist - 5.0) < 1e-6);
        
        // Distance to itself should be 0
        double dist2 = store.l2Distance(v1, v1);
        assert(abs(dist2 - 0.0) < 1e-6);
        
        cout << "✓ L2Distance test passed" << endl;
    }

    static void testFindNearest() {
        cout << "Testing VectorStore findNearest..." << endl;
        VectorStore store(3, mockEmbeddingFunction);
        
        store.addText("a");      // length 1 -> [1.0, 0.5, 0.25]
        store.addText("bb");     // length 2 -> [2.0, 1.0, 0.5]
        store.addText("ccc");    // length 3 -> [3.0, 1.5, 0.75]
        
        SinglyLinkedList<float> query;
        query.add(2.1f); query.add(1.1f); query.add(0.6f);  // Close to "bb"
        
        int nearest = store.findNearest(query, "cosine");
        assert(nearest == 1);  // Should find "bb" at index 1
        
        // Test with L1 metric
        int nearestL1 = store.findNearest(query, "l1");
        assert(nearestL1 == 1);  // Should still find "bb"
        
        // Test with L2 metric
        int nearestL2 = store.findNearest(query, "l2");
        assert(nearestL2 == 1);  // Should still find "bb"
        
        cout << "✓ FindNearest test passed" << endl;
    }

    static void testTopKNearest() {
        cout << "Testing VectorStore topKNearest..." << endl;
        VectorStore store(3, mockEmbeddingFunction);
        
        store.addText("a");      // [1.0, 0.5, 0.25]
        store.addText("bb");     // [2.0, 1.0, 0.5]
        store.addText("ccc");    // [3.0, 1.5, 0.75]
        store.addText("dddd");   // [4.0, 2.0, 1.0]
        
        SinglyLinkedList<float> query;
        query.add(2.5f); query.add(1.25f); query.add(0.625f);  // Between "bb" and "ccc"
        
        int* topK = store.topKNearest(query, 2, "cosine");
        
        // Should return the 2 nearest vectors
        // The exact order depends on the similarity calculation
        assert(topK != nullptr);
        assert(topK[0] >= 0 && topK[0] < 4);  // Valid index
        assert(topK[1] >= 0 && topK[1] < 4);  // Valid index
        assert(topK[0] != topK[1]);           // Different indices
        
        delete[] topK;
        
        // Test with k larger than available vectors
        int* topKLarge = store.topKNearest(query, 10, "cosine");
        assert(topKLarge != nullptr);
        
        // Verify all indices are valid and unique
        for (int i = 0; i < 4; i++) {  // Should return all 4 vectors
            assert(topKLarge[i] >= 0 && topKLarge[i] < 4);
            for (int j = i + 1; j < 4; j++) {
                assert(topKLarge[i] != topKLarge[j]);  // No duplicates
            }
        }
        
        delete[] topKLarge;
        
        cout << "✓ TopKNearest test passed" << endl;
    }

    static void testInvalidMetric() {
        cout << "Testing VectorStore invalid metric handling..." << endl;
        VectorStore store(3, mockEmbeddingFunction);
        
        store.addText("test");
        SinglyLinkedList<float> query;
        query.add(1.0f); query.add(1.0f); query.add(1.0f);
        
        try {
            store.findNearest(query, "invalid_metric");
            assert(false);  // Should throw exception
        } catch (const invalid_metric& e) {
            cout << "✓ Invalid metric exception caught correctly" << endl;
        }
        
        try {
            store.topKNearest(query, 1, "invalid_metric");
            assert(false);  // Should throw exception
        } catch (const invalid_metric& e) {
            cout << "✓ Invalid metric exception in topKNearest caught correctly" << endl;
        }
        
        cout << "✓ Invalid metric test passed" << endl;
    }

    static void testInvalidKValue() {
        cout << "Testing VectorStore invalid k value handling..." << endl;
        VectorStore store(3, mockEmbeddingFunction);
        
        store.addText("test");
        SinglyLinkedList<float> query;
        query.add(1.0f); query.add(1.0f); query.add(1.0f);
        
        try {
            store.topKNearest(query, 0, "cosine");
            assert(false);  // Should throw exception
        } catch (const invalid_k_value& e) {
            cout << "✓ Invalid k value exception caught correctly" << endl;
        }
        
        try {
            store.topKNearest(query, -1, "cosine");
            assert(false);  // Should throw exception
        } catch (const invalid_k_value& e) {
            cout << "✓ Negative k value exception caught correctly" << endl;
        }
        
        cout << "✓ Invalid k value test passed" << endl;
    }
};