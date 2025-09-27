#define TESTING
#include <iostream>
#include "test_point.cpp"

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "         POINT TESTING ONLY             " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    try {
        TestPoint::runAllTests();
        std::cout << "========================================" << std::endl;
        std::cout << "         POINT TESTS COMPLETED!        " << std::endl;
        std::cout << "========================================" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cout << "❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "❌ Test failed with unknown exception!" << std::endl;
        return 1;
    }
}