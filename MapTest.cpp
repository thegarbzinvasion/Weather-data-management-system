#include <iostream>
#include "Map.h"

#include <iostream>
#include <string>
#include "Map.h"

using namespace std;

int main() {
    cout << "=== Map Test ===\n\n";

    // Test 1: Create map and check size
    Map<string, int> scores;
    cout << "Test 1: Map created, size = " << scores.Size() << " (should be 0)\n";

    // Test 2: Insert values
    scores.InsertPair("Alice", 95);
    scores.InsertPair("Bob", 87);
    scores.InsertPair("Charlie", 92);
    cout << "Test 2: After 3 inserts, size = " << scores.Size() << " (should be 3)\n";

    // Test 3: Search for existing keys
    cout << "Test 3: Search for Alice: " << (scores.SearchPair("Alice") ? "Found" : "Not Found") << " (should be Found)\n";
    cout << "Test 4: Search for Bob: " << (scores.SearchPair("Bob") ? "Found" : "Not Found") << " (should be Found)\n";

    // Test 4: Search for non-existent key
    cout << "Test 5: Search for David: " << (scores.SearchPair("David") ? "Found" : "Not Found") << " (should be Not Found)\n";

    // Test 5: Insert duplicate
    scores.InsertPair("Alice", 100);
    cout << "Test 6: After duplicate insert, size = " << scores.Size() << " (should still be 3)\n";

    // Test 6: Different data types
    Map<int, string> numbers;
    numbers.InsertPair(1, "One");
    numbers.InsertPair(2, "Two");
    cout << "Test 7: Map with int key, find 1: " << (numbers.SearchPair(1) ? "Found" : "Not Found") << " (should be Found)\n";

    Map<string, double> prices;
    prices.InsertPair("Apple", 0.99);
    cout << "Test 8: Map with double value, find Apple: " << (prices.SearchPair("Apple") ? "Found" : "Not Found") << " (should be Found)\n";

    cout << "\n=== Test Complete ===\n";
    return 0;
}
