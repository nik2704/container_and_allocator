#include <iostream>

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

template <typename Container>
void print_map(const Container& container) {
    for (const auto& [key, value] : container) {
        std::cout << key << " " << value << std::endl;
    }
}

