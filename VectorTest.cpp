#include <iostream>
#include "Vector.h"

using namespace std;

int main()
{
    cout << "=== Vector Test ===\n\n";

    Vector<int> v;

    // Test Append
    cout << "Test 1: Append\n";
    v.Append(10);
    v.Append(20);
    v.Append(30);
    v.Append(40);
    v.Append(50);
    cout << "After appends: ";
    for (int i = 0; i < v.Size(); i++) cout << v[i] << " ";
    cout << "\nSize: " << v.Size() << "\n\n";

    // Test Insert at beginning
    cout << "Test 2: Insert at beginning (index 0)\n";
    v.Insert(0, 5);
    cout << "Result: ";
    for (int i = 0; i < v.Size(); i++) cout << v[i] << " ";
    cout << "\nExpected: 5,10,20,30,40,50\n\n";

    // Test Insert in middle
    cout << "Test 3: Insert in middle (index 3)\n";
    v.Insert(3, 25);
    cout << "Result: ";
    for (int i = 0; i < v.Size(); i++) cout << v[i] << " ";
    cout << "\nExpected: 5,10,20,25,30,40,50\n\n";

    // Test Insert at end
    cout << "Test 4: Insert at end (index = size)\n";
    v.Insert(v.Size(), 55);
    cout << "Result: ";
    for (int i = 0; i < v.Size(); i++) cout << v[i] << " ";
    cout << "\nExpected: 5,10,20,25,30,40,50,55\n\n";

    // Test Insert invalid index
    cout << "Test 5: Insert invalid index\n";
    bool result = v.Insert(100, 99);
    cout << "Insert at index 100 returned: " << (result ? "true" : "false") << " (expected: false)\n\n";

    // Test RemoveAt
    cout << "Test 6: RemoveAt (index 2)\n";
    v.RemoveAt(2);
    cout << "Result: ";
    for (int i = 0; i < v.Size(); i++) cout << v[i] << " ";
    cout << "\nExpected: 5,10,25,30,40,50,55\n\n";

    // Test RemoveLast
    cout << "Test 7: RemoveLast\n";
    v.RemoveLast();
    cout << "Result: ";
    for (int i = 0; i < v.Size(); i++) cout << v[i] << " ";
    cout << "\nExpected: 5,10,25,30,40,50\n\n";

    // Test operator[] access
    cout << "Test 8: operator[] access\n";
    cout << "First element: " << v[0] << " (expected: 5)\n";
    cout << "Last element: " << v[v.Size()-1] << " (expected: 50)\n\n";

    // Test Clear
    cout << "Test 9: Clear\n";
    v.Clear();
    cout << "Size after clear: " << v.Size() << " (expected: 0)\n";
    cout << "Is empty: " << (v.IsEmpty() ? "Yes" : "No") << "\n\n";

    cout << "=== Test Complete ===\n";
    return 0;
}
