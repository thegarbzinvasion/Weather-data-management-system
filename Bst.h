#ifndef BST_H
#define BST_H

//---------------------------------------------------------------------------------

#include <iostream>

//---------------------------------------------------------------------------------

/**
 * @class Bst
 * @brief A template BST Class for any data type.\n
 *
 * * @author Kyaw Okkar
 * @version 01
 * @date 13/03/2026 Kyaw Okkar
 * Defined Traversal algorithms, Preorder(), Postorder(), Inorder()
 *
 * * @author Kyaw Okkar
 * @version 01
 * @date 14/02/2026 Kyaw Okkar
 * Added Search(), Insert() and extra methods testing RI properties
 *
 * * @author Kyaw Okkar
 * @version 01
 * @date 18/02/2026 Kyaw Okkar
 * Added SearchTree(), InsertTree() as I had forgetten to convert them to recursive routines
 */


/** @brief Node of a BST represented in a struct
* as there is not business logic that needs to be involved
* or object composition */
template <class T>
struct Node
{
    T info; ///< The data to be contained inside Node
    Node<T> *left; ///< Pointer to left child node
    Node<T> *right; ///< Pointer to right child node
};

template <class T>
class Bst
{
public:
    /** @brief Default constructor. Sets m_root (Node) to nullptr */
    Bst();
    /** @brief Destructor. Due to pointer data member. Destroys instantiations of Bst<T> */
    ~Bst();
    /** @brief Copy Constructor. Due to pointer data member. Calls Copy() Method to deep copy */
    Bst(const Bst<T>& rhs);
    /** @brief Assignment Operator. Due to pointer data member. Prevents shallow copy*/
    const Bst<T>& operator=(const Bst<T>& rhs);

    /** @brief Checks whether BST is empty
    @return bool */
    bool IsEmpty() const;

    /** @brief Public interface method that calls the private helper Search()
    @param searchValue Value to search for in the BST
    @return bool */
    bool SearchTree(const T& searchValue) const;

    /** @brief Punlic interface method that calls the private helper Insert()
    @param insertValue Value to be inserted into the BST */
    bool InsertTree(const T& insertValue);

    /** @brief Public interface methods that calls the private traversal helper methods */
    void InorderTraversal(void (*visit)(T&)) const;
    void PreorderTraversal(void (*visit)(T&)) const;
    void PostorderTraversal(void (*visit)(T&)) const;

    /** @brief Checks whether the BST representation invariant holds
    @return true if BST ordering is valid, otherwise false */
    bool CheckInvariant() const;

private:
    Node<T> *m_root; ///< Encapsulated struct representing the starting point (root) of BST

    void DestroyTree(); ///< Interface method that calls the private helper Destroy()
    void Destroy(Node<T>* &p); ///< Private helper that deletes each Node and eventually deletes BST
    void Copy(Node<T>* &copiedRoot, Node<T>* otherRoot); ///< Private method that correctly copies contents of a BST
    ///< to another avoiding shallow copy of BST

    bool Search(Node<T> *p, const T& searchValue) const; ///< Searches for the value provided in the BST
    bool Insert(Node<T> *&p, const T& insertValue); ///< Inserts value provided as a new node at where it should be in the BST

    void Inorder(Node<T> *p, void (*visit) (T&)) const; ///< Processes left children, parent, than right children
    void Preorder(Node<T> *p, void (*visit) (T&) const; ///< Processes parent, left children, than right children
    void Postorder(Node<T> *p, void (*visit) (T&) const; ///< Processes left children, right children, than the parent
    bool CheckBST(Node<T>* p, const T* min, const T* max) const; ///< Checks BST ordering invariant
};

// ---------------------------------------------------------
//                      IMPLEMENTATION
// ---------------------------------------------------------

template <class T>
Bst<T>::Bst()
{
    /** @brief Initializes an empty BST by setting the root pointer to nullptr */
    m_root = nullptr;
}

template <class T>
Bst<T>::~Bst()
{
    /** @brief Frees all dynamically allocated nodes in the BST */
    Destroy(m_root);
}

template <class T>
Bst<T>::Bst(const Bst<T>& rhs)
{
    /** @brief Creates a deep copy of another BST */
    if(rhs.m_root == nullptr)
    {
        m_root = nullptr;
    }
    else
    {
        Copy(m_root, rhs.m_root);
    }
}

template <class T>
const Bst<T>& Bst<T>::operator=(const Bst<T>& rhs)
{
    /** @brief Assigns one BST to another using deep copy
    @param rhs Right-hand side BST to copy from
    @return Reference to the current BST object */
    if(this != &rhs)
    {
        Destroy(m_root);

        if(rhs.m_root == nullptr)
        {
            m_root = nullptr;
        }
        else
        {
            Copy(m_root, rhs.m_root);
        }
    }
    return *this;
}

template <class T>
bool Bst<T>::IsEmpty() const
{
    /** @brief Checks whether the BST contains any nodes
    @return true if root is nullptr, otherwise false */
    return (m_root == nullptr);
}

template <class T>
bool Bst<T>::SearchTree(const T& searchValue) const
{
    /** @brief Recursively checks each node for the searchValue
    @return true if searchValue is found, otherwise false */
    return Search(m_root, searchValue);
}

template <class T>
bool Bst<T>::InsertTree(const T& insertValue)
{
    /** @brief Recursively inserts value by comparing it to nodes
    @return true if insert is successful otherwise false */
    Insert(m_root, insertValue);
}

template <class T>
void Bst<T>::InorderTraversal(void (*visit)(T&)) const
{
    /** @brief Starts inorder traversal from the root node */
    Inorder(m_root, *visit);
}

template <class T>
void Bst<T>::PreorderTraversal(void (*visit)(T&)) const
{
    /** @brief Starts preorder traversal from the root node */
    Preorder(m_root, *visit);
}

template <class T>
void Bst<T>::PostorderTraversal(void (*visit)(T&)) const
{
    /** @brief Starts postorder traversal from the root node */
    Postorder(m_root, *visit);
}

template <class T>
bool Bst<T>::CheckInvariant() const
{
    /** @brief Checks whether the entire BST satisfies strict BST ordering rules
    @return true if the BST invariant holds, otherwise false */
    return CheckBST(m_root, nullptr, nullptr);
}

template <class T>
void Bst<T>::Inorder(Node<T> *p, void (*visit) (T&)) const
{
    /** @brief Recursively performs inorder traversal
    @param p Pointer to current node being processed */
    if(p != nullptr)
    {
        Inorder(p->left, *visit);
        /** This calls the function that traverses and prints whatever is inside BST **/
        (*visit)(p->info);
        Inorder(p->right, *visit);
    }
}

template <class T>
void Bst<T>::Preorder(Node<T> *p, void (*visit) (T&)) const
{
    /** @brief Recursively performs preorder traversal
    @param p Pointer to current node being processed */
    if(p != nullptr)
    {
        /** This calls the function that traverses and prints whatever is inside BST **/
        (*visit)(p->info);
        Preorder(p->left);
        Preorder(p->right);
    }
}

template <class T>
void Bst<T>::Postorder(Node<T> *p, void (*visit) (T&)) const
{
    /** @brief Recursively performs postorder traversal
    @param p Pointer to current node being processed */
    if(p != nullptr)
    {
        Postorder(p->left);
        Postorder(p->right);
        /** This calls the function that traverses and prints whatever is inside BST **/
        (*visit)(p->info);
    }
}

template <class T>
bool Bst<T>::Search(Node<T> *p, const T& searchValue) const
{
    /** @brief Searches the BST for a target value
    @param searchValue Value to search for
    @return true if value is found, otherwise false */

    if(p == nullptr)
    {
        return false;
    }
    else if(p->info == searchValue)
    {
        return true;
    }
    else if(p->info > searchValue)
    {
        return Search(p->left, searchValue);
    }
    else if(p->info < searchValue)
    {
        return Search(p->right, searchValue);
    }
}

template <class T>
bool Bst<T>::Insert(Node<T> *&p, const T& insertValue)
{
    /** @brief Inserts a new value into the BST while preserving BST ordering
    @param insertValue Value to insert into the BST */

    if(p == nullptr)
    {
        p = new Node<T>;
        p->info = insertValue;
        p->left = nullptr;
        p->right = nullptr;

        return true;
    }
    else if(insertValue < p->info)
    {
        return Insert(p->left, insertValue);
    }
    else if(insertValue > p->info)
    {
        return Insert(p->right, insertValue);
    }
    else
    {
        return false;
    }
}

template <class T>
void Bst<T>::DestroyTree()
{
    /** @brief Destroys the entire BST by calling the recursive destroy helper */
    Destroy(m_root);
}

template <class T>
void Bst<T>::Destroy(Node<T>* &p)
{
    /** @brief Recursively deletes all nodes in a subtree
    @param p Reference to pointer of subtree root */
    if(p != nullptr)
    {
        Destroy(p->left);
        Destroy(p->right);
        delete p;
        p = nullptr;
    }
}

template <class T>
void Bst<T>::Copy(Node<T>* &copiedRoot, Node<T>* otherRoot)
{
    /** @brief Recursively deep copies a subtree
    @param copiedRoot Reference to destination subtree root
    @param otherRoot Pointer to source subtree root */
    if(otherRoot == nullptr)
    {
        copiedRoot = nullptr;
    }
    else
    {
        copiedRoot = new Node<T>;
        copiedRoot->info = otherRoot->info;
        copiedRoot->left = nullptr;
        copiedRoot->right = nullptr;

        Copy(copiedRoot->left, otherRoot->left);
        Copy(copiedRoot->right, otherRoot->right);
    }
}

template <class T>
bool Bst<T>::CheckBST(Node<T>* p, const T* min, const T* max) const
{
    /** @brief Recursively verifies strict BST ordering within a subtree
    @param p Pointer to current node
    @param min Lower bound that current node must be greater than
    @param max Upper bound that current node must be less than
    @return true if subtree satisfies BST ordering, otherwise false */
    if(p == nullptr)
    {
        return true;
    }

    if(min != nullptr && !(*min < p->info))
    {
        return false;
    }

    if(max != nullptr && !(p->info < *max))
    {
        return false;
    }

    return CheckBST(p->left, min, &(p->info)) &&
           CheckBST(p->right, &(p->info), max);
}

#endif

