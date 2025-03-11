#include "staticArray.h"
#include "point.h"
#include "fixedArray.h"
#include "dynamicArray.h"

int main()
{
    std::initializer_list<int> list = {1, 2, 3, 4, 5};
    StaticArray<int, 5> arr(list);
    std::cout << arr << std::endl;

    StaticArray<int, 5> arr2 = arr;
    std::cout << arr2 << std::endl;

    StaticArray<char, 5> arr3 = {'a', 'b', 'c', 'd', 'e'};
    std::cout << arr3 << std::endl;
    std::cout << arr3.getSize() << std::endl;

    StaticArray<Point, 5> arr4 = {Point(1, 2), Point(3, 4), Point(5, 6)};
    std::cout << arr4 << std::endl;

    FixedArray<int> arr5 = {1, 2, 3, 4, 5};
    std::cout << arr5 << std::endl;
    FixedArray<Point> arr6 = {Point(1, 2), Point(3, 4), Point(5, 6)};
    std::cout << arr6 << std::endl;

    std::cout << "DynamicArray" << std::endl;
    DynamicArray<int> arr7 = {1, 2, 3, 4, 5};
    std::cout << arr7 << std::endl;
    std::cout << "Add 6" << std::endl; // Add 6
    arr7.Add(6);
    std::cout << arr7 << std::endl;
    std::cout << "Remove third" << std::endl; // Remove 2
    arr7.Remove(2);
    std::cout << arr7 << std::endl;

    std::cout << "DynamicArray<Point>" << std::endl;
    DynamicArray<Point> arr8 = {Point(1, 2), Point(3, 4), Point(5, 6)};
    std::cout << arr8 << std::endl;
    std::cout << "Add (7, 8)" << std::endl; // Add (7, 8)
    arr8.Add(Point(7, 8));
    std::cout << arr8 << std::endl;
    std::cout << "Remove second" << std::endl; // Remove (3, 4)
    arr8.Remove(1);
    std::cout << arr8 << std::endl;

    return 0;
}