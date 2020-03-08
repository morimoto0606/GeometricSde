#include <iostream>
#include <cstddef>
#include <type_traits>

template <typename T>
concept bool Averageable() {
    return std::is_default_constructible<T>::value
    && requires(T a, T b) {
        {a += b}->T;
        {a / std::size_t{1}}->T;
    };
}

template <Averageable T>
T mean (const T* values, std::size_t length) {
    T result{};
    for (std::size_t i{}; i < length; ++i) {
        result += values[i];
    }
    return result / length;
}


int main() {
    const double nums_d[]{1.0f, 2.0f, 3.0f, 4.0f};
    const auto result = mean(nums_d, 4);
    std::cout << "nums = " << result << std::endl;
    std::cout << "hello world" << std::endl;

}