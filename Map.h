#ifndef MAP_H
#define MAP_H

//---------------------------------------------------------------------------------

#include <map>

//---------------------------------------------------------------------------------

template <class Key, class Value>
class Map
{
public:
    Map() = default;
    bool SearchPair(const Key& searchKeyValue) const;
    bool InsertPair(const Key& insertKeyValue, const Value& insertDefinitionValue);
    size_t Size() const {return m_data.size();}

    //using const_iterator = typename std::map<Key, Value>::const_iterator;
    //const_iterator begin() const {return m_data.begin();}
    //const_iterator end() const {return m_data.end();};

private:
    std::map<Key, Value> m_data;
};

// ---------------------------------------------------------
//                      IMPLEMENTATION
// ---------------------------------------------------------
template <class Key, class Value>
bool Map::SearchPair(const Key& searchKeyValue) const
{
    return m_data.find(searchKeyValue) != m_data.end();
}

template <class Key, class Value>
bool Map::InsertPair(const Key& insertKeyValue, const Value& insertDefinitionValue) const
{
    return m_data.insert({insertKeyValue, insertDefinitionValue}).second;
}

template <class Key, class Value>
size_t Map::Size() const
{
    return m_data.size();
}

#endif // MAP_H

