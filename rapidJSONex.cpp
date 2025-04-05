#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <iomanip>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
using namespace rapidjson;
using namespace std;

//Function Prototypes
void testReadJsonFile(const string &fileName);
void testFileSystem(const string &path);

int main()
{

    cout << "-------------------------------------------" << endl;
    cout << "------ RapidJSON Doc Parsing Example ------" << endl;
    cout << "-------------------------------------------" << endl;
    testReadJsonFile("sample_data/coll_1/news_0064567.json");

    cout << "\n";
    cout << "-------------------------------------------" << endl;
    cout << "------     File System Example       ------" << endl;
    cout << "-------------------------------------------" << endl;
    testFileSystem("sample_data");

    return 0;
}

//Reads and parses a json file
void testReadJsonFile(const string &fileName)
{
    ifstream input(fileName);
    if (!input.is_open())
    {
        cerr << "cannot open file: " << fileName << endl;
        return;
    }
    IStreamWrapper isw(input);
    Document d;
    d.ParseStream(isw);
    auto val = d["title"].GetString();
    cout << "Title: " << val << "\n";
    auto persons = d["entities"]["persons"].GetArray();
    cout << "  Person Entities + sentiment:"
         << "\n";
    for (auto &p : persons)
    {
        cout << "    > " << setw(30) << left << p["name"].GetString()
             << setw(10) << left << p["sentiment"].GetString() << "\n";
    }

    cout << endl;
    input.close();
}

//Traverse the filesystem using std::filesystem
void testFileSystem(const string &path)
{
    // https://en.cppreference.com/w/cpp/filesystem/recursive_directory_iterator
    auto it = filesystem::recursive_directory_iterator(path);
    for (const auto &entry : it)
    {
        cout << "--- " << setw(60) << left << entry.path().c_str() << " ---" << endl;
        if (entry.is_regular_file() && entry.path().extension().string() == ".json")
        {
            testReadJsonFile(entry.path().string());
        }
    }
}
