#include <map>

#include "custom_allocator.h"
#include "custom_container.h"
#include "utils.h"


int main() {
    // Создание std::map с кастомным аллокатором, ограниченным 10 элементами
    std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int>, 10>> custom_map;

    // Заполнение карты факториалами чисел от 0 до 9
    for (int i = 0; i < 10; ++i) {
        custom_map[i] = factorial(i);
    }

    // вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
    print_map(custom_map);

    CustomContainer<int, CustomAllocator<int, 10>> container;

    //заполнение 10 элементами от 0 до 9
    for (int i = 0; i < 10; ++i) {
        container.add(i);
    }

    // вывод на экран всех значений, хранящихся в контейнере
    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
