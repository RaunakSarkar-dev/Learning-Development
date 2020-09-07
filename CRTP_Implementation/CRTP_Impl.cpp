// CRTP_Implementation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CRTP_Implementation.hpp"
#include <vector>
#include <memory>
#include <algorithm>

int main()
{
    std::vector<std::shared_ptr<BaseShape>> shapeList;
    shapeList.emplace_back(new Circle(10.0));
    shapeList.emplace_back(new Rectangle(10.0, 20.0));
    shapeList.emplace_back(new Square(10.0));

    std::for_each(shapeList.begin(), shapeList.end(), [&](auto ptr) {
        ptr->computeArea();
        std::cout << "Area of " << ptr->getName() << " is: " << ptr->getArea() << std::endl;
    });


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
