#ifndef MAP_H
#define MAP_H

//---------------------------------------------------------------------------------

#include <map>

//---------------------------------------------------------------------------------

template <class Key, class Value>
class Map
{
public:
    Value& operator[](const Key& key){ return m_data[key]; }
    using iterator = class std::map<Key, Value>::iterator;
    iterator begin() const { return m_data.begin(); }
    iterator end() const { return m_data.end(); }
    size_t Size() const { return m_data.size(); }

private:
    std::map<Key, Value> m_data;
};

// ---------------------------------------------------------
//                      IMPLEMENTATION
// ---------------------------------------------------------

#endif // MAP_H

