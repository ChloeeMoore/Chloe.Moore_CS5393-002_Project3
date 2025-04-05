#define CATCH_CONFIG_MAIN    
#include "catch.hpp"         
#include <iostream>         
#include <cassert>           
#include <iomanip>           
#include "queryprocessor.h"  
#include "indexhandler.h"    
#include "documentparser.h"  
#include "porterstemmer2.h" 

//Test query processor functionality
TEST_CASE("query processor", "[QueryProcessor.h]")
{
    DocumentParser dp;
    IndexHandler ih;
    QueryProcessor qp;
    dp.parseDocument("../sample_data/sampledata1.txt");
    dp.parseDocument("../sample_data/sampledata2.txt");
    dp.parseDocument("../sample_data/sampledata3.txt");
    ih = dp.getIndex();     
    ih.createPersistence(); 
    ih.readPersistence();   
    ih = dp.getIndex();     
    qp.setIndexHandler(ih);

    //Test 1
    std::map<std::string, int> relevantDocs = qp.parsingAnswer("common PERSON:schweitzer");
    REQUIRE(relevantDocs.size() == 1);
    relevantDocs.clear();

    //Test 2
    relevantDocs = qp.parsingAnswer("PERIOD PERSON:strax PERSON:ab");
    REQUIRE(relevantDocs.size() == 1);
    relevantDocs.clear();

    //Test 3
    relevantDocs = qp.parsingAnswer("stocks ORGS:carrefour PERSON:jerome powell");
    REQUIRE(relevantDocs.size() == 1);
    relevantDocs.clear();
}
