#define TESTING
#include <iostream>
#include "test_arraylist.cpp"

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "         ARRAYLIST TESTING ONLY        " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    try {
        TestArrayList::runAllTests();
        std::cout << "========================================" << std::endl;
        std::cout << "         ARRAYLIST TESTS COMPLETED!    " << std::endl;
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