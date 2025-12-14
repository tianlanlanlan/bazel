#include <iostream>
#include <vector>

void pop_sort(std::vector<int> *array, bool sort_to_descend = false) {
    if (array == nullptr || array->empty()) {
        return;
    }

    for (size_t i = 0; i < array->size() - 1; i++) {
        for (size_t j = 0; j < array->size() - 1; j++) {
            bool condition = true;
            if (sort_to_descend) {
                condition = (array->at(j) <= array->at(j + 1));
            } else {
                condition = (array->at(j) > array->at(j + 1));
            }
            if (condition) {
                int temp = array->at(j);
                array->at(j) = array->at(j + 1);
                array->at(j + 1) = temp;
            }
        }
    }
}

int main() {
    std::vector<int> array = {9, 1, 2, 6, 0, 4, 7, 3, 8, 5};
    pop_sort(&array, true);

    for (const int item : array) {
        std::cout << item << " ";
    }
    std::cout << '\n';
    return 0;
}