#ifndef HASH_H
#define HASH_H
#include <map>
#include <functional>
#include <ostream>

//Template class for hash table
template <typename Comparable, typename Value>
class Hash
{
private:
    // Nested struct representing a node
    struct HashNode
    {
        Comparable comp;           
        std::map<Value, int> maps; 
        HashNode *next;            

        //Constructor
        HashNode(Comparable c, Value v)
        {
            comp = c;
            maps[v] = 1;
            next = nullptr;
        }

        //Constructor 
        HashNode(Comparable c, std::map<Value, int> v)
        {
            comp = c;
            maps = v;
            next = nullptr;
        }

        //Copy constructor
        HashNode(const HashNode &n) : comp(n.comp), maps(n.maps), next(nullptr) {}
    };

    int capacity;    
    int size;        
    HashNode **table;

    //Resize and rehash
    void rehash()
    {
        int storeCapacity = capacity;
        capacity = capacity * 2;
        HashNode **storeTable = table;
        createHash(capacity);
        for (int i = 0; i < storeCapacity; i++)
        {
            HashNode *itr = storeTable[i];
            while (itr != nullptr)
            {
                secondInsert(itr->comp, itr->maps);
                HashNode *temp = itr;
                itr = itr->next;
                delete temp;
            }
            storeTable[i] = nullptr;
        }
        delete[] storeTable;
    }

    //Compute the bucket index
    int hash(Comparable comp)
    {
        int index = std::hash<Comparable>{}(comp);
        return abs(index % capacity);
    }

public:
    //Default constructor
    Hash() : table{nullptr}
    {
        createHash();
    }

    //Destructor
    ~Hash()
    {
        clear();
        delete[] table;
    }

    //Copy constructor
    Hash(const Hash &rhs) : table{nullptr}
    {
        clone(rhs);
    }

    //Assignment operator
    Hash &operator=(const Hash &rhs)
    {
        if (this != &rhs)
        {
            clear();
            clone(rhs);
        }
        return *this;
    }

    //Get current size
    int getSize()
    {
        return size;
    }

    //Clear hash table
    void clear() 
    {
        for (int i = 0; i < capacity; i++)
        {
            HashNode *itr = table[i];
            while (itr != nullptr)
            {
                HashNode *prev = itr;
                itr = itr->next;
                delete prev;
            }
            table[i] = nullptr;
        }
        delete[] table;
        createHash(capacity);
        size = 0;
    }

    //Create new hash table with capacity (default 100)
    void createHash(int x = 100) 
    {
        capacity = x;
        size = 0;
        table = new HashNode *[capacity];
        for (int i = 0; i < capacity; i++)
        {
            table[i] = nullptr;
        }
    }

    //Clones hash table
    void clone(const Hash &copy) 
    {
        createHash(copy.capacity);
        size = copy.size;
        for (int i = 0; i < capacity; i++)
        {
            HashNode *itr1 = copy.table[i];
            HashNode *prev = nullptr;
            while (itr1 != nullptr)
            {
                HashNode *newNode = new HashNode(*itr1);
                if (prev == nullptr)
                {
                    table[i] = newNode;
                }
                else
                {
                    prev->next = newNode;
                }
                prev = newNode;
                itr1 = itr1->next;
            }
        }
    }

    //Inserts comp into hash at val
    void insert(Comparable comp, Value val)
    {
        int index = hash(comp);
        if (table[index] == nullptr)
        {
            table[index] = new HashNode(comp, val);
            size++;
        }
        else
        {
            HashNode *itr = table[index];
            HashNode *prev = nullptr;
            while (itr != nullptr)
            {
                if (itr->comp == comp)
                {
                    if (itr->maps.find(val) == itr->maps.end())
                    {
                        itr->maps[val] = 1;
                    }
                    else
                    {
                        itr->maps[val] += 1;
                    }
                    break;
                }
                prev = itr;
                itr = itr->next;
            }
            if (itr == nullptr)
            {
                if (prev != nullptr)
                {
                    prev->next = new HashNode(comp, val);
                    size++;
                }
            }
        }
        if (size == capacity)
        {
            rehash();
        }
    }

    //Insert a key-value pair with a frequency
    void insert(Comparable comp, Value val, int freq) 
    {
        int index = hash(comp);
        if (table[index] == nullptr)
        {
            table[index] = new HashNode(comp, val);
            table[index]->maps[val] = freq;
            size++;
        }
        else
        {
            HashNode *itr = table[index];
            HashNode *prev = nullptr;
            while (itr != nullptr)
            {
                if (itr->comp == comp)
                {
                    if (itr->maps.find(val) == itr->maps.end())
                    {
                        itr->maps[val] = freq;
                    }
                    else
                    {
                        itr->maps[val] += freq;
                    }
                    break;
                }
                prev = itr;
                itr = itr->next;
            }
            if (itr == nullptr)
            {
                if (prev != nullptr)
                {
                    prev->next = new HashNode(comp, val);
                    size++;
                }
            }
        }
        if (size == capacity)
        {
            rehash();
        }
    }

    //Print hash table 
    void printHash(std::ostream &out)
    {
        for (int i = 0; i < capacity; i++)
        {
            HashNode *itr = table[i];
            while (itr != nullptr)
            {
                out << itr->comp << ":";
                for (const auto &itr : itr->maps)
                {
                    out << itr.first << "," << itr.second << ";";
                }
                out << std::endl;
                itr = itr->next;
            }
        }
    }

    //Insert a key with a map of values 
    void secondInsert(Comparable comp, std::map<Value, int> val)
    {
        int index = hash(comp);
        if (table[index] == nullptr)
        {
            table[index] = new HashNode(comp, val);
            size++;
        }
        else
        {
            HashNode *itr = table[index];
            HashNode *prev = nullptr;
            while (itr != nullptr)
            {
                if (itr->comp == comp)
                {
                    for (const auto &entry : val)
                    {
                        itr->maps[entry.first] = entry.second;
                    }
                    break;
                }
                prev = itr;
                itr = itr->next;
            }
            if (itr == nullptr)
            {
                prev->next = new HashNode(comp, val);
                size++;
            }
        }
        if (size == capacity)
        {
            rehash();
        }
    }
    
    //Find and return the map of values for key
    std::map<Value, int> find(const Comparable comp)
    {
        int index = hash(comp);
        HashNode *itr = table[index];
        while (itr != nullptr)
        {
            if (itr->comp == comp)
            {
                return itr->maps;
            }
            itr = itr->next;
        }
        return std::map<Value, int>();
    }
};
#endif
