#ifndef INDEX_HANDLER_H
#define INDEX_HANDLER_H

#include "hash.h"     
#include "dsavltree.h" 
#include <algorithm>   
#include <string>      
#include <map>         
#include <vector>      

//Class definition
class IndexHandler
{
private:
    //AVL Tree to store words
    DSAvlTree<std::string, std::string> words;

    //Hash tables for people and organizations
    Hash<std::string, std::string> people;
    Hash<std::string, std::string> orgs;

    //Vector to store document
    std::vector<std::string> docs;

    //Map to store word count
    std::map<std::string, int> wordCount;

public:
    //Public functions

    //Retrieves a map of words
    std::map<std::string, int> getWords(std::string);

    //Retrieves a map of people
    std::map<std::string, int> getPeople(std::string);

    //Retrieves a map of organizations
    std::map<std::string, int> getOrgs(std::string);

    //Returns the count of word
    int getWordCount(std::string);

    //Adds words to AVL tree
    void addWords(std::string, std::string);

    //Adds people to hash table
    void addPeople(std::string, std::string);

    //Adds organizations to hash table
    void addOrgs(std::string, std::string);

    //Adds a document to vector
    void addDocument(std::string);

    //Add word count to map
    void addWordCount(std::string, int);

    //Returns the size of vector
    int getDocSize();

    //Function to create persistence
    void createPersistence();

    //Function to read from persistence
    void readPersistence();

    //Returns the size of tree
    int returnSize();
};

#endif
