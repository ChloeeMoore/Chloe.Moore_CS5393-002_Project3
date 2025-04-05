#include "indexhandler.h"

//Returns a map of words that match the input word
std::map<std::string, int> IndexHandler::getWords(std::string word)
{
    return words.contains(word);
}

//Returns the count of occurrences of a specific word
int IndexHandler::getWordCount(std::string title)
{
    return wordCount[title]; 
}

//Returns a map of people that match the input person
std::map<std::string, int> IndexHandler::getPeople(std::string person)
{
    return people.find(person);
}

//Returns a map of organizations that match the input organization
std::map<std::string, int> IndexHandler::getOrgs(std::string org)
{
    return orgs.find(org); 
}

//Updates the word count in the index
void IndexHandler::addWordCount(std::string title, int count)
{
    wordCount[title] = count;
}

//Adds a word and filepath to the words AVL tree
void IndexHandler::addWords(std::string word, std::string filepath)
{
    words.insert(word, filepath);
}

//Adds a person and filepath to the people hash table
void IndexHandler::addPeople(std::string person, std::string filepath)
{
    people.insert(person, filepath); 
}

//Adds an organization and filepath to the orgs hash table
void IndexHandler::addOrgs(std::string org, std::string filepath)
{
    orgs.insert(org, filepath); 
}

//Adds a document's filepath to the document list
void IndexHandler::addDocument(std::string filepath)
{
    docs.push_back(filepath); 
}

//Returns the number of documents in the index
int IndexHandler::getDocSize()
{
    return docs.size(); 
}

//Creates a persistent storage of the index data
void IndexHandler::createPersistence()
{
    std::ofstream output("persistence.txt");
    if (!output.is_open())
    {
        std::cerr << "Error! File could not be opened!" << std::endl;
        exit(-1); 
    }
    output << "//words" << std::endl;
    words.printTree(output); 
    output << "//people" << std::endl;
    people.printHash(output); 
    output << "//orgs" << std::endl;
    orgs.printHash(output); 
    output << "//docs" << std::endl;
    for (const auto &itr : docs)
    {
        output << itr << "$" << std::endl; 
    }
    output << "//wordCount" << std::endl;
    for (const auto &itr : wordCount)
    {
        output << itr.first << "^" << itr.second << "#" << std::endl; 
    }
}

//Reads and populates the index data from persistent storage
void IndexHandler::readPersistence()
{
    std::ifstream input("persistence.txt");
    std::string buffer, answer, node, id, freq, title, count, path;
    if (!input.is_open())
    {
        std::cerr << "Error! File could not be opened!" << std::endl;
        exit(-1); 
    }
    while (getline(input, buffer))
    {
        int index = 0; 
        for (size_t i = 0; i < buffer.length(); i++)
        {
            if (buffer[i] == '/' && buffer[i + 1] == '/')
            {
                answer = buffer.substr(2, buffer.length()); 
                break;
            }
            else if (buffer[i] == ':')
            {
                node = buffer.substr(index, i - index); 
                index = i + 1;
            }
            else if (buffer[i] == ',')
            {
                id = buffer.substr(index, i - index); 
                index = i + 1;
            }
            else if (buffer[i] == ';')
            {
                freq = buffer.substr(index, i - index); 
                index = i + 1;
                int num = stoi(freq); 
                if (answer == "words")
                    words.insert(node, id, num);
                else if (answer == "people")
                    people.insert(node, id, num);
                else if (answer == "orgs")
                    orgs.insert(node, id, num);
            }
            else if (buffer[i] == '^')
            {
                title = buffer.substr(index, i - index); 
                index = i + 1;
            }
            else if (buffer[i] == '$')
            {
                path = buffer.substr(index, i - index); 
                docs.push_back(path);                 
            }
            else if (buffer[i] == '#')
            {
                count = buffer.substr(index, i - index);
                index = i + 1;
                int num2 = stoi(count); 
                wordCount[title] = num2; 
            }
        }
    }
    input.close(); 
}

//Returns the size of the words AVL tree
int IndexHandler::returnSize()
{
    return words.getSize(); 
}
