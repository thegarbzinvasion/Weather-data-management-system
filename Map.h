#ifndef MAP_H
#define MAP_H

//---------------------------------------------------------------------------------

#include <map>

//---------------------------------------------------------------------------------

template <class Key, class Value>
class Map
{
public:
    bool SearchPair(const Key& searchKeyValue) const;
    bool InsertPair(const Key& insertKeyValue, const Value& insertDefinitionValue);
    size_t Size() const { return m_data.size(); }

    using const_iterator = class std::map<Key, Value>::const_iterator;
    const_iterator begin() const { return m_data.begin(); }
    const_iterator end() const { return m_data.end(); }

    Value& operator[](const Key& key){
        return m_data[key];
    }

private:
    std::map<Key, Value> m_data;
};

// ---------------------------------------------------------
//                      IMPLEMENTATION
// ---------------------------------------------------------

template <class Key, class Value>
bool Map<Key, Value>::SearchPair(const Key& searchKeyValue) const
{
    return m_data.find(searchKeyValue) != m_data.end();
}

template <class Key, class Value>
bool Map<Key, Value>::InsertPair(const Key& insertKeyValue, const Value& insertDefinitionValue)
{
    return m_data.insert({insertKeyValue, insertDefinitionValue}).second;
}

#endif // MAP_H

