#ifndef DOCUMENT_PARSER_H
#define DOCUMENT_PARSER_H

// Including necessary header files
#include "indexhandler.h"             //IndexHandler header for indexing functionality
#include "rapidjson/istreamwrapper.h" //RapidJSON's istreamwrapper for handling JSON streams
#include "rapidjson/document.h"       //RapidJSON's document header for parsing JSON documents
#include "porterstemmer2.h"          //Porter Stemmer header for word stemming functionality
#include <string>                     //Library for string handling
#include <vector>                     //Library for vector data structure
#include <map>                        //Library for map data structure
#include <iostream>                   //Library for input/output streaming
#include <fstream>                    //Library for file streaming
#include <sstream>                    //Library for string streaming
#include <iomanip>                    //Library for input/output formatting
#include <filesystem>                 //Library for filesystem operations
#include <dirent.h>                   //Directory traversing
#include <algorithm>                  //Library for various algorithms
#include <set>                        //Library for set data structure

//Class definition
class DocumentParser
{
private:
    //Private variables
    IndexHandler ih;                
    std::vector<std::string> titles;

public:
    //Public functions

    //Parses a JSON document and indexes its content
    void parseDocument(const std::string &jsonContent);

    //Prints the content of a JSON document
    void printDocument(const std::string &jsonContent);

    //Sets the index handler for the parser
    void setIndex(IndexHandler ih);

    //Retrieves the index handler used by the parser
    IndexHandler getIndex();

    //Traverses a given directory and processes subdirectories
    void traverseSubdirectory(const std::string &directoryPath);

    //Prints information extracted from a JSON document
    void printInfo(const std::string &jsonContent);

    //Retrieves the title of a document given its index
    std::string getTitle(int num) { return titles[num]; };
};

#endif
