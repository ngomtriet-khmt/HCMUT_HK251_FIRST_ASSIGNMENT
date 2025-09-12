#include <iostream>
#include <cassert>
#include <cmath>
#include <sstream>
#include "utils.h"

using namespace std;

class TestPoint {
public:
    static void runAllTests() {
        cout << "=== Testing Point Class ===" << endl;
        
        testDefaultConstructor();
        test2DConstructor();
        test3DConstructor();
        testCopyConstructor();
        testGetters();
        testSetters();
        testDistanceTo();
        testTranslate();
        testAdditionOperator();
        testSubtractionOperator();
        testMultiplicationOperator();
        testEqualityOperator();
        testInequalityOperator();
        testStreamOperator();
        
        cout << "Point: All tests passed!" << endl << endl;
    }

private:
    static void testDefaultConstructor() {
        cout << "Testing Point default constructor..." << endl;
        Point p;
        assert(abs(p.getX() - 0.0) < 1e-9);
        assert(abs(p.getY() - 0.0) < 1e-9);
        assert(abs(p.getZ() - 0.0) < 1e-9);
        cout << "✓ Default constructor test passed" << endl;
    }

    static void test2DConstructor() {
        cout << "Testing Point 2D constructor..." << endl;
        Point p(3.5, 4.2);
        assert(abs(p.getX() - 3.5) < 1e-9);
        assert(abs(p.getY() - 4.2) < 1e-9);
        assert(abs(p.getZ() - 0.0) < 1e-9);
        cout << "✓ 2D constructor test passed" << endl;
    }

    static void test3DConstructor() {
        cout << "Testing Point 3D constructor..." << endl;
        Point p(1.1, 2.2, 3.3);
        assert(abs(p.getX() - 1.1) < 1e-9);
        assert(abs(p.getY() - 2.2) < 1e-9);
        assert(abs(p.getZ() - 3.3) < 1e-9);
        cout << "✓ 3D constructor test passed" << endl;
    }

    static void testCopyConstructor() {
        cout << "Testing Point copy constructor..." << endl;
        Point original(5.5, 6.6, 7.7);
        Point copy(original);
        
        assert(abs(copy.getX() - 5.5) < 1e-9);
        assert(abs(copy.getY() - 6.6) < 1e-9);
        assert(abs(copy.getZ() - 7.7) < 1e-9);
        cout << "✓ Copy constructor test passed" << endl;
    }

    static void testGetters() {
        cout << "Testing Point getters..." << endl;
        Point p(10.1, 20.2, 30.3);
        
        assert(abs(p.getX() - 10.1) < 1e-9);
        assert(abs(p.getY() - 20.2) < 1e-9);
        assert(abs(p.getZ() - 30.3) < 1e-9);
        cout << "✓ Getters test passed" << endl;
    }

    static void testSetters() {
        cout << "Testing Point setters..." << endl;
        Point p;
        
        p.setX(100.5);
        p.setY(200.6);
        p.setZ(300.7);
        
        assert(abs(p.getX() - 100.5) < 1e-9);
        assert(abs(p.getY() - 200.6) < 1e-9);
        assert(abs(p.getZ() - 300.7) < 1e-9);
        cout << "✓ Setters test passed" << endl;
    }

    static void testDistanceTo() {
        cout << "Testing Point distanceTo..." << endl;
        
        // Test 2D distance
        Point p1(0, 0);
        Point p2(3, 4);
        double dist = p1.distanceTo(p2);
        assert(abs(dist - 5.0) < 1e-9);  // 3-4-5 triangle
        
        // Test 3D distance
        Point p3(0, 0, 0);
        Point p4(1, 1, 1);
        double dist3d = p3.distanceTo(p4);
        assert(abs(dist3d - sqrt(3.0)) < 1e-9);
        
        // Test distance to itself (should be 0)
        double distSelf = p1.distanceTo(p1);
        assert(abs(distSelf - 0.0) < 1e-9);
        
        cout << "✓ DistanceTo test passed" << endl;
    }

    static void testTranslate() {
        cout << "Testing Point translate..." << endl;
        Point p(1.0, 2.0, 3.0);
        
        p.translate(10.0, 20.0, 30.0);
        
        assert(abs(p.getX() - 11.0) < 1e-9);
        assert(abs(p.getY() - 22.0) < 1e-9);
        assert(abs(p.getZ() - 33.0) < 1e-9);
        
        // Test negative translation
        p.translate(-5.0, -10.0, -15.0);
        assert(abs(p.getX() - 6.0) < 1e-9);
        assert(abs(p.getY() - 12.0) < 1e-9);
        assert(abs(p.getZ() - 18.0) < 1e-9);
        
        cout << "✓ Translate test passed" << endl;
    }

    static void testAdditionOperator() {
        cout << "Testing Point addition operator..." << endl;
        Point p1(1.0, 2.0, 3.0);
        Point p2(4.0, 5.0, 6.0);
        
        Point result = p1 + p2;
        
        assert(abs(result.getX() - 5.0) < 1e-9);
        assert(abs(result.getY() - 7.0) < 1e-9);
        assert(abs(result.getZ() - 9.0) < 1e-9);
        
        // Original points should remain unchanged
        assert(abs(p1.getX() - 1.0) < 1e-9);
        assert(abs(p2.getX() - 4.0) < 1e-9);
        
        cout << "✓ Addition operator test passed" << endl;
    }

    static void testSubtractionOperator() {
        cout << "Testing Point subtraction operator..." << endl;
        Point p1(10.0, 8.0, 6.0);
        Point p2(4.0, 3.0, 2.0);
        
        Point result = p1 - p2;
        
        assert(abs(result.getX() - 6.0) < 1e-9);
        assert(abs(result.getY() - 5.0) < 1e-9);
        assert(abs(result.getZ() - 4.0) < 1e-9);
        
        cout << "✓ Subtraction operator test passed" << endl;
    }

    static void testMultiplicationOperator() {
        cout << "Testing Point multiplication operator..." << endl;
        Point p(2.0, 3.0, 4.0);
        
        Point result = p * 2.5;
        
        assert(abs(result.getX() - 5.0) < 1e-9);
        assert(abs(result.getY() - 7.5) < 1e-9);
        assert(abs(result.getZ() - 10.0) < 1e-9);
        
        // Test multiplication by zero
        Point zeroResult = p * 0.0;
        assert(abs(zeroResult.getX() - 0.0) < 1e-9);
        assert(abs(zeroResult.getY() - 0.0) < 1e-9);
        assert(abs(zeroResult.getZ() - 0.0) < 1e-9);
        
        // Test multiplication by negative number
        Point negResult = p * -1.0;
        assert(abs(negResult.getX() - (-2.0)) < 1e-9);
        assert(abs(negResult.getY() - (-3.0)) < 1e-9);
        assert(abs(negResult.getZ() - (-4.0)) < 1e-9);
        
        cout << "✓ Multiplication operator test passed" << endl;
    }

    static void testEqualityOperator() {
        cout << "Testing Point equality operator..." << endl;
        Point p1(1.0, 2.0, 3.0);
        Point p2(1.0, 2.0, 3.0);
        Point p3(1.0, 2.0, 3.1);
        
        assert(p1 == p2);
        assert(!(p1 == p3));
        
        // Test with small differences (within epsilon)
        Point p4(1.0000000001, 2.0, 3.0);  // Very small difference
        assert(p1 == p4);  // Should be equal due to epsilon tolerance
        
        cout << "✓ Equality operator test passed" << endl;
    }

    static void testInequalityOperator() {
        cout << "Testing Point inequality operator..." << endl;
        Point p1(1.0, 2.0, 3.0);
        Point p2(1.0, 2.0, 3.0);
        Point p3(1.1, 2.0, 3.0);
        
        assert(!(p1 != p2));
        assert(p1 != p3);
        
        cout << "✓ Inequality operator test passed" << endl;
    }

    static void testStreamOperator() {
        cout << "Testing Point stream operator..." << endl;
        Point p(1.5, 2.7, 3.9);
        
        stringstream ss;
        ss << p;
        string result = ss.str();
        
        // Should output in format "(x,y,z)"
        assert(result == "(1.5,2.7,3.9)");
        
        cout << "✓ Stream operator test passed" << endl;
    }

    static void testEdgeCases() {
        cout << "Testing Point edge cases..." << endl;
        
        // Test with very large numbers
        Point large(1e10, 2e10, 3e10);
        assert(abs(large.getX() - 1e10) < 1e-6);
        
        // Test with very small numbers
        Point small(1e-10, 2e-10, 3e-10);
        assert(abs(small.getX() - 1e-10) < 1e-15);
        
        // Test with negative numbers
        Point negative(-1.5, -2.5, -3.5);
        assert(abs(negative.getX() - (-1.5)) < 1e-9);
        assert(abs(negative.getY() - (-2.5)) < 1e-9);
        assert(abs(negative.getZ() - (-3.5)) < 1e-9);
        
        cout << "✓ Edge cases test passed" << endl;
    }
};