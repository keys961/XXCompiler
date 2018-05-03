#ifndef COMPILER_SYMBOL_H
#define COMPILER_SYMBOL_H

#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <vector>
#include <iostream>

class Symbol;
class SymbolBucket;
class SymbolTable;

class Symbol
{
private:
    int lineNum;

    int location;

    int size;

    int immediateValue;

    std::string name;

    std::string typeName;
public:
    Symbol(int lineNum, std::string name, std::string typeName) :
            lineNum(lineNum), location(-1), immediateValue(0), name(name), typeName(typeName)
    { }

    Symbol(const Symbol& symbol)
    {
        this->typeName = symbol.typeName;
        this->name = symbol.name;
        this->typeName = symbol.typeName;
        this->immediateValue = symbol.immediateValue;
        this->size = symbol.size;
    }

    int getLineNum() const
    {
        return lineNum;
    }

    void setLineNum(int lineNum)
    {
        this->lineNum = lineNum;
    }

    int getLocation() const
    {
        return location;
    }

    void setLocation(int location)
    {
        this->location = location;
    }

    int getSize() const
    {
        return size;
    }

    void setSize(int size)
    {
        this->size = size;
    }

    int getImmediateValue() const
    {
        return immediateValue;
    }

    void setImmediateValue(int immediateValue)
    {
        this->immediateValue = immediateValue;
    }

    const std::string &getName() const
    {
        return name;
    }

    void setName(const std::string &name)
    {
        this->name = name;
    }

    const std::string &getTypeName() const
    {
        return typeName;
    }

    void setTypeName(const std::string &typeName)
    {
        this->typeName = typeName;
    }
};

class SymbolBucket
{
private:
    int id;

    Symbol symbol;

    // for complicated data structure.. normally it is just one node
    SymbolBucket* next;

    SymbolBucket* last;

    SymbolTable* currentTable;

    SymbolTable* nextTable;
public:
    SymbolBucket(int id, Symbol symbol, SymbolTable* currentTable, SymbolTable* nextTable = NULL) :
            id(id), next(NULL), last(NULL), symbol(symbol), currentTable(currentTable), nextTable(nextTable)
    { }

    SymbolBucket(const SymbolBucket& bucket) : symbol(bucket.symbol)
    {
        id = bucket.id;
        next = bucket.next;
        last = bucket.last;
        currentTable = bucket.currentTable;
        nextTable = bucket.nextTable;
    }

    int getId() const
    {
        return id;
    }

    void setId(int id) {
        this->id = id;
    }

    const Symbol &getSymbol() const
    {
        return symbol;
    }

    void setSymbol(const Symbol &symbol)
    {
        this->symbol = symbol;
    }

    SymbolBucket *getNextBucket() const
    {
        return next;
    }

    void setNextBucket(SymbolBucket *next)
    {
        this->next = next;
    }

    SymbolBucket *getLastBucket() const {
        return last;
    }

    void setLastBucket(SymbolBucket *last)
    {
        this->last = last;
    }

    SymbolTable *getCurrentTable() const
    {
        return currentTable;
    }

    void setCurrentTable(SymbolTable *currentTable)
    {
        this->currentTable = currentTable;
    }

    SymbolTable *getNextTable() const
    {
        return nextTable;
    }

    void setNextTable(SymbolTable *nextTable)
    {
        this->nextTable = nextTable;
    }

    void printBucket(std::ostream& out)
    {
        SymbolBucket* current = this;
        while(current != NULL)
        {
            out << current->getSymbol().getLineNum() << ":: type:"
                    << current->getSymbol().getTypeName() << " name:"
                    << current->getSymbol().getName() << " location:"
                    << current->getSymbol().getLocation() << "   ;";
            current = current->next;
        }

        out << std::endl;
    }

};

class SymbolTable
{
private:
    int level;

    std::string tableName;

    int count;

    // stack offset
    long location;

    std::map< std::string, std::list<SymbolBucket*>* > table;

    SymbolBucket* parentBucket;

public:
    SymbolTable(std::string name, int level = 0, SymbolBucket* parent = NULL) :
            level(level), tableName(name), parentBucket(parent), count(0)
    {

    }

    SymbolTable(const SymbolTable& symbolTable)
    {
        level = symbolTable.level;
        tableName = symbolTable.tableName;
        location = symbolTable.location;
        count = symbolTable.count;

        for(auto it = symbolTable.table.begin(); it != symbolTable.table.end(); it++)
        {
            table[it->first] = new std::list<SymbolBucket*>();
            std::list<SymbolBucket*>* newList = table[it->first];
            std::list<SymbolBucket*>* oldList = it->second;
            // copy the bucket pointers
            for(auto itList = oldList->begin(); itList != oldList->end(); itList++)
                newList->push_back(*itList);
        }
    }

    int getLevel() const
    {
        return level;
    }

    void setLevel(int level)
    {
        this->level = level;
    }

    int getCount() const
    {
        return count;
    }

    void setCount(int count)
    {
        this->count = count;
    }

    long getLocation() const
    {
        return location;
    }

    void setLocation(long location)
    {
        this->location = location;
    }

    SymbolBucket *getParentBucket() const
    {
        return parentBucket;
    }

    void setParentBucket(SymbolBucket *parentBucket)
    {
        this->parentBucket = parentBucket;
    }

    void insert(SymbolBucket* bucket);

    SymbolBucket* find(std::string name);

    void getSymbolBucketListByType(std::list<SymbolBucket*>& symbolBucketList, std::string typeName);

    void printTable(std::ostream& out)
    {
        out << "Print table " << tableName << std::endl;
        for(auto mapIter = table.begin(); mapIter != table.end(); mapIter++)
        {
            std::list<SymbolBucket*> bucketList = *(mapIter->second);
            for(auto listIter = bucketList.begin(); listIter != bucketList.end(); listIter++)
            {
                (*listIter)->printBucket(out);
                if((*listIter)->getNextTable() != NULL)
                {
                    out << "=== Print " << (*listIter)->getSymbol().getName() << "'s symbol table" << std::endl;
                    (*listIter)->getNextTable()->printTable(out);
                    out << "=== End print " << (*listIter)->getSymbol().getName() << "'s symbol table" << std::endl;
                }
            }
        }

        out << "End print table" << tableName << std::endl;
    }

    virtual ~SymbolTable()
    {
        for(auto it = table.begin(); it != table.end(); it++)
            delete it->second;
    }
};

#endif //COMPILER_SYMBOL_H
