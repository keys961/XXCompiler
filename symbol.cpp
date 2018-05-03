#include "symbol.h"

bool compare(SymbolBucket* a, SymbolBucket* b)
{
    return (a)->getId() < (b)->getId();
}

void SymbolTable::insert(SymbolBucket *bucket)
{
    bucket->setId(this->count++);
    std::string name = bucket->getSymbol().getName();
    auto tableIter = (this->table).find(name);

    if(tableIter == (this->table).end())
        // not found, insert a new list
        table[name] = new std::list<SymbolBucket*>();
    table[name]->push_back(bucket);
}

SymbolBucket *SymbolTable::find(std::string name)
{
    auto it = table.find(name);
    if(it != table.end())
    {
        std::list<SymbolBucket*> bucketList = *table[name];
        for(auto listIter = bucketList.begin(); listIter != bucketList.end(); listIter++)
        {
            if((*listIter)->getSymbol().getName() == name)
                return *listIter;
        }
    }

    if(parentBucket != NULL)
        return parentBucket->getCurrentTable()->find(name);

    return NULL;
}

void SymbolTable::getSymbolBucketListByType(std::list<SymbolBucket *>& symbolBucketList, std::string typeName)
{
    for(auto mapIter = table.begin(); mapIter != table.end(); mapIter++)
    {
        std::list<SymbolBucket*> bucketList = *(mapIter->second);
        for(auto listIter = bucketList.begin(); listIter != bucketList.end(); listIter++)
        {
            if((*listIter)->getSymbol().getTypeName() == typeName)
                symbolBucketList.push_back(*listIter);
        }
    }

    symbolBucketList.sort(compare);
}

