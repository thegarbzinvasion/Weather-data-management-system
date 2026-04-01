#include <iostream>
#include "BST.h"

using namespace std;

// Simple print function for traversal testing
void printInt(int& value) {
    cout << value << " ";
}

int main() {
    cout << "=== BST Test Program ===\n\n";

    // Test 1: Default Constructor and IsEmpty
    cout << "Test 1: Default Constructor\n";
    Bst<int> tree;
    cout << "Tree empty? " << (tree.IsEmpty() ? "Yes" : "No") << " (should be Yes)\n\n";

    // Test 2: InsertTree
    cout << "Test 2: InsertTree\n";
    cout << "Inserting: 50, 30, 70, 20, 40, 60, 80\n";
    tree.InsertTree(50);
    tree.InsertTree(30);
    tree.InsertTree(70);
    tree.InsertTree(20);
    tree.InsertTree(40);
    tree.InsertTree(60);
    tree.InsertTree(80);
    cout << "Tree empty? " << (tree.IsEmpty() ? "Yes" : "No") << " (should be No)\n\n";

    // Test 3: SearchTree
    cout << "Test 3: SearchTree\n";
    cout << "Search 40: " << (tree.SearchTree(40) ? "Found" : "Not Found") << "\n";
    cout << "Search 100: " << (tree.SearchTree(100) ? "Found" : "Not Found") << "\n\n";

    // Test 4: InorderTraversal (should be sorted)
    cout << "Test 4: InorderTraversal (should be sorted)\n";
    cout << "Expected: 20 30 40 50 60 70 80\n";
    cout << "Actual:   ";
    tree.InorderTraversal(printInt);
    cout << "\n\n";

    // Test 5: PreorderTraversal
    cout << "Test 5: PreorderTraversal (root first)\n";
    cout << "Expected: 50 30 20 40 70 60 80\n";
    cout << "Actual:   ";
    tree.PreorderTraversal(printInt);
    cout << "\n\n";

    // Test 6: PostorderTraversal
    cout << "Test 6: PostorderTraversal (children first)\n";
    cout << "Expected: 20 40 30 60 80 70 50\n";
    cout << "Actual:   ";
    tree.PostorderTraversal(printInt);
    cout << "\n\n";

    // Test 7: CheckInvariant
    cout << "Test 7: CheckInvariant\n";
    cout << "BST invariant holds? " << (tree.CheckInvariant() ? "Yes" : "No") << "\n\n";

    // Test 8: Copy Constructor
    cout << "Test 8: Copy Constructor\n";
    Bst<int> tree2(tree);
    cout << "Original tree inorder: ";
    tree.InorderTraversal(printInt);
    cout << "\nCopied tree inorder:   ";
    tree2.InorderTraversal(printInt);
    cout << "\n\n";

    // Test 9: Assignment Operator
    cout << "Test 9: Assignment Operator\n";
    Bst<int> tree3;
    tree3 = tree;
    cout << "Assigned tree inorder: ";
    tree3.InorderTraversal(printInt);
    cout << "\n\n";

    // Test 10: Destructor (automatic when objects go out of scope)
    cout << "Test 10: Destructor (will be called automatically)\n";
    cout << "Creating a new tree inside a block...\n";
    {
        Bst<int> tempTree;
        tempTree.InsertTree(100);
        tempTree.InsertTree(50);
        tempTree.InsertTree(150);
        cout << "Temp tree inorder: ";
        tempTree.InorderTraversal(printInt);
        cout << "\n";
        cout << "Now temp tree goes out of scope - destructor called\n";
    }
    cout << "Destructor test complete\n\n";

    // Test 11: Insert Duplicate (should return false)
    cout << "Test 11: Insert Duplicate\n";
    bool inserted = tree.InsertTree(50);
    cout << "Inserting 50 again: " << (inserted ? "Inserted" : "Duplicate - not inserted") << "\n";
    cout << "Tree still has: ";
    tree.InorderTraversal(printInt);
    cout << "\n\n";

    // Test 12: Insert more values to test tree structure
    cout << "Test 12: Insert More Values\n";
    tree.InsertTree(10);
    tree.InsertTree(90);
    tree.InsertTree(35);
    tree.InsertTree(45);
    cout << "After inserting 10, 90, 35, 45:\n";
    cout << "Inorder: ";
    tree.InorderTraversal(printInt);
    cout << "\nCheckInvariant: " << (tree.CheckInvariant() ? "Valid" : "Invalid") << "\n\n";

    cout << "=== All Tests Complete ===\n";
    return 0;
}
