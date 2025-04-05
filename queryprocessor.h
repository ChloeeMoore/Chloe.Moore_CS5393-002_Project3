#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <math.h>
#include <sstream>
#include "indexhandler.h"
#include "porterstemmer2.h"

//Class definition
class QueryProcessor
{
private:
    //Private variables
    std::vector<std::string> storage;            
    std::map<std::string, int> relevantDocuments; 
    std::map<std::string, int> relDocs;           
    std::map<std::string, int> sendTo;           
    IndexHandler indexObject;                    
    std::vector<std::string> printVector;      

public:
    //Getter
    std::vector<std::string> getPrintVector() { return printVector; };

    //Getter
    int getPrintVectorSize() { return printVector.size(); };

    //Retrieves a specific item
    std::string getPrint(int num) { return printVector[num]; };

    //Clears
    void clearPrintVector() { printVector.clear(); };

    //Parses a query string and returns relevant documents
    std::map<std::string, int> parsingAnswer(std::string);

    //Dissects the answer
    std::map<std::string, int> disectAnswer();

    //Calculates the intersection of two maps
    std::map<std::string, int> intersection(std::map<std::string, int>, std::map<std::string, int>);

    //Calculates the complement of two maps
    std::map<std::string, int> complement(std::map<std::string, int>, std::map<std::string, int>);

    //Setter
    void setIndexHandler(IndexHandler i);

    //Determines the relevancy of documents
    std::vector<std::string> Relevancy(std::map<std::string, int>);

    //Implements quickSort algorithm for sorting
    void quickSort(std::map<std::string, int> &, int, int);

    //Helper function for quickSort
    int partition(std::map<std::string, int>, int, int);
};
#endif
