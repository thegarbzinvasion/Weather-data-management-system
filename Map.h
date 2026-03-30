#ifndef MAP_H
#define MAP_H

//---------------------------------------------------------------------------------

#include <map>

//---------------------------------------------------------------------------------

template <class Key, class Value>
class Map
{
public:
    Map(); // What do I put here???
    bool SearchPair(const Key& searchKeyValue) const;
    bool InsertPair(const Key& insertKeyValue, const Value& insertDefinitionValue);
    void DeletePair(const Key& deleteKeyValue);

private:
    std::map<Key, Value> m_data;

    bool Search(std::map<Key, Value> data, const Key& searchKeyValue) const;
    bool Insert(std::map<Key, Value> data, const Key& insertKeyValue, const Value& insertDefinitionValue);
};

// ---------------------------------------------------------
//                      IMPLEMENTATION
// ---------------------------------------------------------
template <class Key, class Value>
Map<Key, Value>::Map()
{
    default;
}


#endif // MAP_H
