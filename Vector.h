#ifndef VECTOR_H
#define VECTOR_H

//---------------------------------------------------------------------------------

#include <stdexcept>

//---------------------------------------------------------------------------------

/**
 * @class Vector
 * @brief A template vector Class for any data type.\n
 *
 * * @author Kyaw Okkar
 * @version 01
 * @date 10/02/2026 Kyaw Okkar
 * Defined private member variables, added default constructor, deconstructor, Append() and ResizeC() functions
 *
 * * @author Kyaw Okkar
 * @version 01
 * @date 14/02/2026 Kyaw Okkar
 * Added RemoveLast(), Size(), IsEmpty(), Clear(), copy constructor and assignment operator, and operator functions
 *
 */

template <typename T>
class Vector {
public:
    Vector();                                  // Default Constructor
    Vector(int n);                          // Initial Capacity Constructor
    Vector(const Vector<T>& initialiser);       // Copy Constructor
    ~Vector();                                 // Destructor

    Vector& operator=(const Vector & rhs);     // Assignment Operator

    void Append(const T& value);
    bool Insert(int index, const T & data);
    void RemoveLast();

    int Size() const;
    bool IsEmpty() const;

    T& operator[](int index);
    const T& operator[](int index) const;

    void Clear();

private:
    T* m_data;
    int m_size;
    int m_capacity;

    bool Copy(const Vector & rhs);
    void ResizeCapacity(int newCapacity);
};

// ---------------------------------------------------------
//                      IMPLEMENTATION
// ---------------------------------------------------------

/**
 * @brief Default constructor.
 * Initializes data pointer to nullptr and size/capacity to 0.
 */
template <typename T>
Vector<T>::Vector()
{
    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
}
/**
 * @brief Creates a vector with n default-initialised elements.
 * Sets size and capacity to n.
 */
template <typename T>
Vector<T>::Vector(int n)
{
    m_size = 0;
    m_capacity = n;
    m_data = new T[m_capacity];
}
/**
 * @brief Assignment operator.
 * Replaces current contents with a deep copy of rhs.
 */
template <typename T>
Vector<T>::Vector(const Vector<T> & initialiser)
{
    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
    Copy(initialiser);
}
/**
 * @brief Assignment operator.
 * Replaces current contents with a deep copy of rhs.
 */
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{
    if(this != &rhs)
    {
        Copy(rhs);
    }
    return *this;
}
/**
 * @brief Destructor = Deletes after clearing its contents
 */
template <typename T>
Vector<T>::~Vector()
{
    delete[] m_data;
}
/**
 * @brief Adds an element to the end of the vector.
 * Resizes capacity if needed.
 */
template <typename T>
void Vector<T>::Append(const T& value)
{
    if(m_size == m_capacity)
    {
        int newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        ResizeCapacity(newCapacity);
    }
    m_data[m_size] = value;
    m_size++;
}
/**
 * @brief Returns the number of elements stored.
 */
template <typename T>
int Vector<T>::Size() const
{
    return m_size;
}
/**
 * @brief Adds an element according to the given index.
 * Calls Append() if vector is full already.
 */
template <typename T>
bool Vector<T>::Insert(int index, const T& value)
{
    if(index < 0 || index > m_size)
    {
        return false;
    }
    if(m_size >= m_capacity)
    {
        int newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        ResizeCapacity(newCapacity);
    }

    for(int i = m_size; i > index; i--)
    {
        m_data[i] = m_data[i - 1];
    }

    m_data[index] = value;
    m_size++;

    return true;
}
/**
 * @brief Removes the last element if vector is not empty.
 */
template <typename T>
void Vector<T>::RemoveLast()
{
    if(m_size > 0)
    {
        m_size--;
    }
}
/**
 * @brief Clears the vector.
 * Frees memory and resets size and capacity to 0.
 */
template <typename T>
void Vector<T>::Clear()
{
    delete[] m_data;
    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
}
/**
 * @brief Returns true if the vector is empty.
 */
template <typename T>
bool Vector<T>::IsEmpty() const
{
    return m_size == 0;
}
/**
 * @brief Returns reference to element at index.
 * Throws std::out_of_range if index is invalid.
 */
template <typename T>
T& Vector<T>::operator[](int index)
{
    if(index >= m_size)
    {
        throw std::out_of_range("Index given is out of range");
    }
    return m_data[index];
}
/**
 * @brief Returns const reference to element at index.
 * Throws std::out_of_range if index is invalid.
 */
template <typename T>
const T& Vector<T>::operator[](int index) const
{
    if(index < 0 || index >= m_size)
    {
        throw std::out_of_range("Index given is out of range");
    }
    return m_data[index];
}
/**
 * @brief Performs a deep copy of another vector.
 * Allocates new memory and copies all elements.
 */
template <typename T>
bool Vector<T>::Copy(const Vector<T> & rhs)
{
    if(rhs.m_data == 0)
    {
        m_data = nullptr;
    }

    delete [] m_data;

    m_size = rhs.m_size;
    m_capacity = rhs.m_capacity;

    m_data = new T[m_capacity];

    for (int i = 0; i < m_size; i++)
    {
        m_data[i] = rhs.m_data[i];
    }

    return true;
}
/**
 * @brief Resizes vector by creating new vector with capacity passed.
 * Copies old data into the newly created vector.
 * Deletes old vector as well as replace its size and capacity with new.
 */
template <typename T>
void Vector<T>::ResizeCapacity(int newCapacity)
{
    T* newData = new T[newCapacity];

    for (int i = 0; i < m_size; i++)
    {
        newData[i] = m_data[i];
    }

    delete[] m_data;
    m_data = newData;
    m_capacity = newCapacity;
}

#endif // VECTOR_H
