#ifndef COMPILER_SYMBOL_H
#define COMPILER_SYMBOL_H

#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <utility>
#include <utility>
#include <vector>
#include <iostream>

class Symbol;

class SymbolBucket;

class SymbolTable;

bool compare(SymbolBucket *a, SymbolBucket *b);

class Symbol {
private:
    int lineNum{};

    int location{};

    int size{};//这个symbol的字节数

    std::string name;//变量名

    std::string typeName;//类型名

    bool isConst{};

    int immediateValue;
public:

    Symbol(int lineNum, std::string name, std::string typeName)
            : lineNum(lineNum), location(-1), name(std::move(std::move(name))), typeName(std::move(std::move(typeName))), isConst(false), immediateValue(0) {
    }

    Symbol(const Symbol &symbol) {
        this->typeName = symbol.typeName;
        this->name = symbol.name;
        this->typeName = symbol.typeName;
        this->immediateValue = symbol.immediateValue;
        this->size = symbol.size;
    }


    int getLineNum() const {
        return lineNum;
    }

    void setLineNum(int lineNum) {
        this->lineNum = lineNum;
    }

    int getLocation() const {
        return location;
    }

    void setLocation(int location) {
        this->location = location;
    }

    int getSize() const {
        return size;
    }

    void setSize(int size) {
        this->size = size;
    }

    int getImmediateValue() const {
        return immediateValue;
    }

    void setImmediateValue(int immediateValue) {
        this->immediateValue = immediateValue;
    }

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        this->name = name;
    }

    const std::string &getTypeName() const {
        return typeName;
    }

    void setTypeName(const std::string &typeName) {
        this->typeName = typeName;
    }
};

class SymbolBucket {
private:
    int order;

    Symbol *symbol;

    // for complicated data structure.. normally it is just one node
    SymbolBucket *next;//当前数据结构下一个symbol，默认是this

    SymbolBucket *last;//当前数据结构最后一个symbol

    SymbolTable *currentTable;

    SymbolTable *nextTable;
public:
    SymbolBucket(Symbol *symbol, SymbolTable *currentTable, SymbolTable *nextTable = nullptr) :
            order(0), next(nullptr), last(nullptr), symbol(symbol), currentTable(currentTable), nextTable(nextTable) {}

    explicit SymbolBucket(const SymbolBucket *bucket) {
        this->symbol = new Symbol(*bucket->symbol);
        order = bucket->order;
        next = this;
        last = this;
        currentTable = bucket->currentTable;//todo
        nextTable = nullptr;
    }

    SymbolBucket(std::string name, int lineNum, std::string typeName, SymbolTable *currentTable)
            : order(0), next(this), last(this), currentTable(currentTable), nextTable(nullptr) {
        this->symbol = new Symbol(lineNum, std::move(name), std::move(typeName));
    }

    int getOrder() const {
        return order;
    }

    void setOrder(int order) {
        this->order = order;
    }

    Symbol *getSymbol() const {
        return symbol;
    }

    void setSymbol(Symbol *&symbol) {
        this->symbol = symbol;
    }

    SymbolBucket *getNextBucket() const {
        return next;
    }

    void setNextBucket(SymbolBucket *next) {
        this->next = next;
    }

    SymbolBucket *getLastBucket() const {
        return last;
    }

    void setLastBucket(SymbolBucket *last) {
        this->last = last;
    }

    SymbolTable *getCurrentTable() const {
        return currentTable;
    }

    void setCurrentTable(SymbolTable *currentTable) {
        this->currentTable = currentTable;
    }

    SymbolTable *getNextTable() const {
        return nextTable;
    }

    void setNextTable(SymbolTable *nextTable) {
        this->nextTable = nextTable;
    }

    //todo cout都改成out
    void printBucket(std::ostream &out) {
        SymbolBucket *current = this;
        do {
            out << current->getSymbol()->getLineNum() << ":: type:"
                << current->getSymbol()->getTypeName() << " name:"
                << current->getSymbol()->getName() << " location:"
                << current->getSymbol()->getLocation() << " size:"
                << current->getSymbol()->getSize() << std::endl;
            current = current->next;
        } while (current != this);
    }

    //根据当前的SymBucket重新构造一个Symbucket(深拷贝)
    //todo 可能有问题
    SymbolBucket *deepCopyBucket() {
        auto *head = new SymbolBucket(this);
        SymbolBucket *tmpBucket = head;
        SymbolBucket *member = next;

        if (member == this) {
            head->next = head;
            head->last = head;
            return head;
        }

        do {
            auto *newBucket = new SymbolBucket(member);
            SymbolBucket *subTmpBucket = newBucket;
            if (member->last != member) {
                SymbolBucket *subMem = member->next;
                do {
                    auto *subNewBucket = new SymbolBucket(subMem);
                    subTmpBucket->next = subNewBucket;
                    subTmpBucket = subNewBucket;
                    subMem = subMem->next;
                } while (subMem != member->last->next);
                newBucket->last = subTmpBucket;
                tmpBucket->next = newBucket;
                tmpBucket = newBucket->last;
                member = member->last->next;
            } else {
                newBucket->last = newBucket;
                tmpBucket->next = newBucket;
                tmpBucket = newBucket;
                member = member->next;
            }
        } while (member != this);
        head->last = tmpBucket;
        head->last->next = head;
        return head;
    }

};

class SymbolTable {
private:
    int level;//当前符号表所在层级

    std::string tableName;//符号表表名

    int count;//当前符号表一共有多少个symbucket(每插入一个就加一)

    // stack offset
    long location;//当前符号表的栈深度(每个symbucket的size的累加)

    std::map<std::string, std::list<SymbolBucket *> *> table;

    SymbolBucket *parentBucket{};

public:
    explicit SymbolTable(std::string name, SymbolBucket *parent = nullptr) :
            level(0), tableName(std::move(std::move(name))), parentBucket(parent), count(0), location(0) {}

    //深拷贝
    SymbolTable(const SymbolTable &symbolTable) {
        level = symbolTable.level;
        tableName = symbolTable.tableName;
        location = symbolTable.location;
        count = symbolTable.count;

        for (const auto &it : symbolTable.table) {
            table[it.first] = new std::list<SymbolBucket *>();
            std::list<SymbolBucket *> *newList = table[it.first];
            std::list<SymbolBucket *> *oldList = it.second;
            // copy the bucket pointers
            for (auto &itList : *oldList)
                newList->push_back(itList);
        }
    }

    void getSymBucketList(std::vector<SymbolBucket *> &v) {
        for (auto &iter : table) {
            std::list<SymbolBucket *> *q = iter.second;
            for (auto &it : *q) {
                //if (!(*q)[i]->getIsType())
                v.push_back(it);
            }
        }
        sort(v.begin(), v.end(), compare);
    }

    int getLevel() const {
        return level;
    }

    void setLevel(int level) {
        this->level = level;
    }

    int getCount() const {
        return count;
    }

    void setCount(int count) {
        this->count = count;
    }

    //先获取当前的location，再更新location(栈深度)
    //参数为0的话就不会更新，只是获取当前栈深度
    int getAndUpdateLocation(int size) {
        location += size;
        return location - size;
    }

    void setLocation(long location) {
        this->location = location;
    }

    int getLocation() {
        return this->location;
    }

    SymbolBucket *getParentBucket() const {
        return parentBucket;
    }

    void setParentBucket(SymbolBucket *parentBucket) {
        this->parentBucket = parentBucket;
    }

    std::string getTableName() const  {
        return tableName;
    }

    void insert(SymbolBucket *bucket);

    SymbolBucket *find(std::string name);

    void getSymbolBucketListByType(std::list<SymbolBucket *> &symbolBucketList, std::string typeName);

    void printTable(std::ostream &out);

    virtual ~SymbolTable() {
        for (auto &it : table)
            delete it.second;
    }
};

#endif //COMPILER_SYMBOL_H
