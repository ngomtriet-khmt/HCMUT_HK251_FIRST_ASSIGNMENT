#define TESTING
#include <iostream>
#include "test_vectorstore.cpp"

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "       VECTORSTORE TESTING ONLY        " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    try {
        TestVectorStore::runAllTests();
        std::cout << "========================================" << std::endl;
        std::cout << "      VECTORSTORE TESTS COMPLETED!     " << std::endl;
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