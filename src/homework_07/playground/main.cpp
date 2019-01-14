#include <dataset.hpp>

#include <iostream>
#include <cstdint>

int main()
{
    Dataset< double, std::uint16_t > dataset{ 2, 3, "files/homework_07/dataset.txt" };
    std::cout << dataset.size() << '\n';
    return 0;
}
