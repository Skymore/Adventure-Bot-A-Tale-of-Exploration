// Memory Management: Write a C++ program that demonstrates the use of dynamically
// allocating and deallocating memory using new and delete operators. The program should
// create an array of integers with a size specified by the user, fill the array with numbers, and
// then deallocate the memory

#include <iostream>
using namespace std;

int main()
{
    int sz;
    cout << "Enter the size of the array: ";
    cin >> sz;

    int *arr = new int[sz];

    cout << "Enter the elements of the array: ";
    for (int i = 0; i < sz; i++)
    {
        cin >> arr[i];
    }

    cout << "The elements of the array are: ";
    for (int i = 0; i < sz; i++)
    {
        cout << arr[i] << " ";
    }

    delete[] arr;
    return 0;
}