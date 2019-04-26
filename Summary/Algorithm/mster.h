#include <iostream>
#include <list>
#include <string>
#include <iterator>
#include <vector>
#include <memory>
#include <map>
using std::cout;
using std::endl;
using std::iterator;
using std::list;
using std::map;
using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::vector;
using std::weak_ptr;

static inline void checkParam(int arr[], int size)
{
    if (arr == nullptr || size == 0)
        return;
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "第" << i << "个: " << arr[i] << endl;
    }
    return;
}
void swapElement(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}