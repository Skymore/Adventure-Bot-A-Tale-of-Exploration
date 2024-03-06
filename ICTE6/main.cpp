#include <iostream>
#include <vector>
#include <map>
#include <string>

// Function for a vector of strings or an array of ints
template <typename T>
void print_elements(const T& container) {
    for (const auto& elem : container) {
        std::cout << elem;
        if constexpr (std::is_same_v<T, std::vector<std::string>>) {
            std::cout << "!";
        }
        std::cout << ", ";
    }
    std::cout << std::endl;
}

// Overload function specifically for a map
void print_elements(const std::map<std::string, int>& container) {
    for (const auto& [key, value] : container) {
        std::cout << key << ": " << value << ", ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<std::string> vec = {"i", "am", "on", "a", "very", "bumpy", "flight"};
    int arr[] = {1, 4, 9, 16};
    std::map<std::string, int> mp = {{"John", 30}, {"Jane", 25}, {"Jim", 35}};

    print_elements(vec);
    print_elements(arr); // This directly uses the template function for arrays.
    print_elements(mp);

    return 0;
}
