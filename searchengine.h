#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "indexhandler.h"   
#include "documentparser.h" 
#include "userinterface.h"  
#include "queryprocessor.h"

//Class definition
class SearchEngine
{
private:
    //Private variables
    IndexHandler ih;   
    DocumentParser dp; 
    UserInterface ui;  
    QueryProcessor qp;

public:
    //Public function

    //Function to handle input arguments and initialize
    void input(int, char **); //Needs command line arguments
};
#endif
