#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "indexhandler.h"
#include "documentparser.h"
using namespace std;

//Test for IndexHandler
TEST_CASE("IndexHandler Test", "[IndexHandler]")
{
    DocumentParser dp;
    dp.parseDocument("../sample_data/sampledata1.txt");
    IndexHandler ih = dp.getIndex(); 

    //Test getWords functionality
    SECTION("getWords Test")
    {
        map<string, int> result = ih.getWords("plan");
        REQUIRE(result.size() == 1);
        REQUIRE(result["../sample_data/sampledata1.txt"] == 2);
        map<string, int> result1 = ih.getWords("german");
        REQUIRE(result1.size() == 1);
        REQUIRE(result1["../sample_data/sampledata1.txt"] == 4);
        map<string, int> result2 = ih.getWords("interest");
        REQUIRE(result2.size() == 1);
        REQUIRE(result2["../sample_data/sampledata1.txt"] == 1);
        map<string, int> result3 = ih.getWords("prospect");
        REQUIRE(result3.size() == 1);
        REQUIRE(result3["../sample_data/sampledata1.txt"] == 3);
        map<string, int> result5 = ih.getWords("potato");
        REQUIRE(result5.size() == 0);
        map<string, int> result6 = ih.getWords("orange");
        REQUIRE(result6.size() == 0);
    }

    //Test getPeople functionality
    SECTION("getPeople Test")
    {
        map<string, int> result4 = ih.getPeople("schweitzer");
        REQUIRE(result4.size() == 1);
        map<string, int> result5 = ih.getPeople("adam");
        REQUIRE(result5.size() == 0);
        map<string, int> result6 = ih.getPeople("george");
        REQUIRE(result6.size() == 0);
        map<string, int> result7 = ih.getPeople("sarah");
        REQUIRE(result7.size() == 0);
    }
    //Test getWordCount functionality
    SECTION("getWordCount Test")
    {
        REQUIRE(ih.getWordCount("../sample_data/sampledata1.txt") == 251);
    }

    //Test getOrgs functionality
    SECTION("getOrgs Test")
    {
        map<string, int> result = ih.getOrgs("cnn");
        REQUIRE(result.size() == 0);
        map<string, int> result1 = ih.getOrgs("nbc");
        REQUIRE(result1.size() == 0);
        map<string, int> result2 = ih.getOrgs("abc");
        REQUIRE(result2.size() == 0);
        map<string, int> result3 = ih.getOrgs("reuters");
        REQUIRE(result3.size() == 1);
        REQUIRE(result3["../sample_data/sampledata1.txt"] == 1);
    }

    //Test persistence functionality
    SECTION("Persistance tests")
    {
        ih.createPersistence(); 
        IndexHandler index;
        index.readPersistence();
        map<string, int> result = index.getWords("plan");
        REQUIRE(result.size() == 1);
        REQUIRE(result["../sample_data/sampledata1.txt"] == 2); 
        REQUIRE(result["../sample_data/sampledata1.txt"] == 2);
        map<string, int> result1 = index.getWords("german");
        REQUIRE(result1.size() == 1);
        REQUIRE(result1["../sample_data/sampledata1.txt"] == 4);
        map<string, int> result2 = index.getWords("interest");
        REQUIRE(result2.size() == 1);
        REQUIRE(result2["../sample_data/sampledata1.txt"] == 1);
        map<string, int> result3 = index.getWords("prospect");
        REQUIRE(result3.size() == 1);
        REQUIRE(result3["../sample_data/sampledata1.txt"] == 3);
        map<string, int> result5 = index.getWords("potato");
        REQUIRE(result5.size() == 0);
        map<string, int> result6 = index.getWords("orange");
        REQUIRE(result6.size() == 0);
        map<string, int> result10 = index.getPeople("schweitzer");
        REQUIRE(result10.size() == 1);
        map<string, int> result11 = index.getPeople("adam");
        REQUIRE(result11.size() == 0);
        map<string, int> result12 = index.getPeople("george");
        REQUIRE(result12.size() == 0);
        map<string, int> result13 = index.getPeople("sarah");
        REQUIRE(result13.size() == 0);
        REQUIRE(index.getWordCount("../sample_data/sampledata1.txt") == 251);
        map<string, int> result14 = index.getOrgs("cnn");
        REQUIRE(result14.size() == 0);
        map<string, int> result15 = index.getOrgs("nbc");
        REQUIRE(result15.size() == 0);
        map<string, int> result16 = index.getOrgs("abc");
        REQUIRE(result16.size() == 0);
        map<string, int> result17 = index.getOrgs("Reuters");
        REQUIRE(result17.size() == 0);
        REQUIRE(index.getDocSize() == 1);
    }

    //Test with multiple documents
    SECTION("Multiple Doc Testing")
    {
        dp.parseDocument("../sample_data/sampledata2.txt");
        IndexHandler ih = dp.getIndex(); 
        map<string, int> result1 = ih.getWords("german");
        REQUIRE(result1.size() == 1);
        REQUIRE(result1["../sample_data/sampledata1.txt"] == 4);
        map<string, int> result2 = ih.getWords("group");
        REQUIRE(result2.size() == 2);
        REQUIRE(result2["../sample_data/sampledata1.txt"] == 1);
        REQUIRE(result2["../sample_data/sampledata2.txt"] == 2);
        ih.createPersistence();
        IndexHandler index2;
        index2.readPersistence();
        map<string, int> result = ih.getWords("german");
        REQUIRE(result.size() == 1);
        REQUIRE(result["../sample_data/sampledata1.txt"] == 4);
        map<string, int> result3 = ih.getWords("group");
        REQUIRE(result3.size() == 2);
        REQUIRE(result3["../sample_data/sampledata1.txt"] == 1);
        REQUIRE(result3["../sample_data/sampledata2.txt"] == 2);
    }
}
