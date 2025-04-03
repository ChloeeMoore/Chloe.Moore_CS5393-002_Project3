#ifndef DSAVL_TREE_H
#define DSAVL_TREE_H
#define DEBUG
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>

//Template class for a node in an AVL tree
template <typename Comparable, typename Value>
class DSAvlTree
{
private:
    //Nested struct representing a node in the AVL tree
    struct DSAvlNode
    {
        Comparable key;        
        DSAvlNode *left;             
        DSAvlNode *right;             
        int height;                
        std::map<Value, int> mapVals; 

        //Constructor
        DSAvlNode(const Comparable &theKey, DSAvlNode *lt, DSAvlNode *rt, int h)
            : key{theKey}, left{lt}, right{rt}, height{h} {}

        //Constructor
        DSAvlNode(const Comparable &theKey, Value v, DSAvlNode *lt, DSAvlNode *rt, int h)
            : key{theKey}, left{lt}, right{rt}, height{h}
        {
            mapVals.emplace(v, 1);
        }
    };

    DSAvlNode *root; 
    int size;   

public:
    //Default constructor
    DSAvlTree() : root{nullptr}, size{0} {}

    //Copy constructor
    DSAvlTree(const DSAvlTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }

    //Destructor
    ~DSAvlTree()
    {
        makeEmpty();
    }

    //Assignment operator
    DSAvlTree &operator=(const DSAvlTree &rhs)
    {
        makeEmpty();
        root = clone(rhs.root);
        return *this;
    }

    //Check if a key is in tree
    std::map<Value, int> contains(const Comparable &x) const
    {
        return contains(x, root);
    }

    //Check if tree is empty
    bool isEmpty() const
    {
        return root == nullptr;
    }

    //Make the tree empty
    void makeEmpty()
    {
        makeEmpty(root);
        root = nullptr;
        size = 0;
    }

    //Insert a key-value pair
    void insert(const Comparable &x, const Value &v)
    {
        insert(x, v, root);
    }

    //Insert a key-value pair with a specific count
    void insert(const Comparable &x, const Value &v, const int &a)
    {
        insert(x, v, a, root);
    }

    //Remove a key
    void remove(const Comparable &x)
    {
        remove(x, root);
    }

    //Get the size of the tree
    int getSize()
    {
        return size;
    }

    //Print the tree structure
    void printTree(std::ostream &out)
    {
        printTree(out, root);
    }

private:
    //Private methods

    //Insert a key-value pair
    void insert(const Comparable &x, const Value &v, DSAvlNode *&t)
    {
        if (t == nullptr)
        {
            t = new DSAvlNode{x, v, nullptr, nullptr, 0}; 
            size++;
        }
        else if (x < t->key)
        {
            insert(x, v, t->left);
        }
        else if (t->key < x)
        {
            insert(x, v, t->right);
        }
        else
        {
            if (t->mapVals.find(v) == t->mapVals.end()) 
            {
                t->mapVals[v] = 1;
            }
            else
            {
                t->mapVals[v] += 1; 
            }
            return;
        }
        balance(t);
    }

    //Insert a key-value pair with count
    void insert(const Comparable &x, const Value &v, const int &a, DSAvlNode *&t)
    {
        if (t == nullptr)
        {
            t = new DSAvlNode{x, v, nullptr, nullptr, 0};
            t->mapVals[v] = a;
            size++;
        }
        else if (x < t->key)
        {
            insert(x, v, a, t->left); 
        }
        else if (t->key < x)
        {
            insert(x, v, a, t->right); 
        }
        else
        {
            if (t->mapVals.find(v) == t->mapVals.end()) 
            {
                t->mapVals[v] = a;
            }
            else
            {
                t->mapVals[v] += a; 
            }
            return;
        }
        balance(t); 
    }

    //Remove a key
    void remove(const Comparable &x, DSAvlNode *&t) 
    {
        if (t == nullptr)
        {
            throw std::runtime_error("Error, could not find 'x' in private remove function"); 
        }
        if (x < t->key)
        {
            remove(x, t->left); 
        }
        else if (t->key < x)
        {
            remove(x, t->right);
        }
        else
        {
            if (t->right != nullptr) 
            {
                DSAvlNode *tCopy = t;
                t->key = deleteLeftMostIn(tCopy->right);
            }
            else if (t->left != nullptr) 
            {
                DSAvlNode *tCopy = t;
                t = t->left;
                delete tCopy;
            }
            else 
            {
                delete t;
                t = nullptr;
                size--;
                return;
            }
        }
        balance(t);
        t->height = std::max(height(t->left), height(t->right)) + 1;
    }

    //Delete the leftmost node and return key
    Comparable deleteLeftMostIn(DSAvlNode *&t) 
    {
        if (t == nullptr)
        {
            throw std::runtime_error("Error in Comparable deleteLeftMostIn(DSAvlNode *t)");
        }
        if (t->left == nullptr)
        {
            Comparable valueToReturn = t->key;
            delete t;
            t = nullptr;

            return valueToReturn;
        }
        else
        {
            Comparable valueToReturn = deleteLeftMostIn(t->left);
            t->height = std::max(height(t->left), height(t->right)) + 1;
            balance(t);
            return valueToReturn;
        }
    }

    //Check if a key is in subtree
    std::map<Value, int> contains(const Comparable &x, DSAvlNode *t) const
    {
        if (t == nullptr)
        {
            return std::map<Value, int>(); 
        }
        else if (x < t->key)
        {
            return contains(x, t->left); 
        }
        else if (t->key < x)
        {
            return contains(x, t->right);
        }
        else
        {
            return t->mapVals;
        }
    }

    //Make subtree empty
    void makeEmpty(DSAvlNode *&t) 
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }
    }

    //Clones subtree
    DSAvlNode *clone(DSAvlNode *t) const
    {
        if (t == nullptr)
        {
            return nullptr;
        }
        DSAvlNode *newNode = new DSAvlNode(*t);
        newNode->left = clone(t->left);
        newNode->right = clone(t->right);
        newNode->height = t->height;
        return newNode;
    }

    //Height of node
    int height(DSAvlNode *t) const
    {
        return t == nullptr ? -1 : t->height;
    }

    static const int ALLOWED_IMBALANCE = 1; //1 is the default

    //Balances tree
    void balance(DSAvlNode *&t)
    {
        if (t == nullptr)
        {
            return;
        }
        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
        {
            if (height(t->left->left) >= height(t->left->right))
            {
                rotateWithLeftChild(t);
            }
            else
            {
                doubleWithLeftChild(t);
            }
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
        {
            if (height(t->right->right) >= height(t->right->left))
            {
                rotateWithRightChild(t);
            }
            else
            {
                doubleWithRightChild(t); 
            }
        }
        t->height = max(height(t->left), height(t->right)) + 1;
    }
    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Edited from: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
     */

    void printTree(std::ostream &out, DSAvlNode *&t)
    {
        if (t != nullptr)
        {
            out << t->key << ":";
            for (const auto &itr : t->mapVals)
            {
                out << itr.first << "," << itr.second << ";";
            }
            out << std::endl;
            printTree(out, t->left);
            printTree(out, t->right);
        }
    }

    //Rotate with left child
    void rotateWithLeftChild(DSAvlNode *&k2)
    {
        DSAvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    //Rotate with right child
    void rotateWithRightChild(DSAvlNode *&k1)
    {
        DSAvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    //Double rotate with left child
    void doubleWithLeftChild(DSAvlNode *&k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    //Double rotate with right child
    void doubleWithRightChild(DSAvlNode *&k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
};
#endif
