#include "symbol.h"

using namespace std;

bool compare(SymbolBucket *a, SymbolBucket *b) {
    return (a)->getOrder() < (b)->getOrder();
}

void SymbolTable::insert(SymbolBucket *bucket) {
    bucket->setOrder(this->count++);//标记当前symbucket在符号表是第几个，同时更新符号表的count
    std::string name = bucket->getSymbol()->getName();
    //cout<<"before insert : "<<name<<endl;
    auto tableIter = (this->table).find(name);
    //未找到，就新建一个
    if (tableIter == (this->table).end())
        table[name] = new std::list<SymbolBucket *>();
    //找到的话就加到最后
    table[name]->push_back(bucket);
}

SymbolBucket *SymbolTable::find(std::string name) {
    auto it = table.find(name);
    if (it != table.end()) {
        std::list<SymbolBucket *> bucketList = *table[name];
        //todo 应该是从后往前找
        for (auto listIter = bucketList.begin(); listIter != bucketList.end(); listIter++) {
            if ((*listIter)->getSymbol()->getName() == name)
                return *listIter;
        }
    }

    //往上层的符号表继续找
    if (parentBucket != NULL)
        return parentBucket->getCurrentTable()->find(name);

    return NULL;
}

void SymbolTable::getSymbolBucketListByType(std::list<SymbolBucket *> &symbolBucketList, std::string typeName) {
    for (auto mapIter = table.begin(); mapIter != table.end(); mapIter++) {
        std::list<SymbolBucket *> bucketList = *(mapIter->second);
        for (auto listIter = bucketList.begin(); listIter != bucketList.end(); listIter++) {
            if ((*listIter)->getSymbol()->getTypeName() == typeName)
                symbolBucketList.push_back(*listIter);
        }
    }
    symbolBucketList.sort(compare);
}

void SymbolTable::printTable(std::ostream &out) {
    out << "Print table: " << tableName << std::endl;
    for (auto mapIter = table.begin(); mapIter != table.end(); mapIter++) {
        std::list<SymbolBucket *> bucketList = *(mapIter->second);
        out << mapIter->first + " :" << endl;
        for (auto listIter = bucketList.begin(); listIter != bucketList.end(); listIter++) {
            (*listIter)->printBucket(out);
            if ((*listIter)->getNextTable() != NULL) {
                out << std::endl << "-------Print " << (*listIter)->getSymbol()->getName() << "'s symbol table-----"
                    << std::endl;
                (*listIter)->getNextTable()->printTable(out);
                out << "---------End print " << (*listIter)->getSymbol()->getName() << "'s symbol table------"
                    << std::endl << std::endl;
            }
        }
    }

    out << "End print table: " << tableName << std::endl;
}
