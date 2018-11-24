#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "pass1.h"
#include "optable.h"

using namespace std;


int main(){

    bool battleRoyale = false;

    vector<vector<string>> code(1000);
    vector<int> location;
    map<string,string> symbolTable;
    map<string,string>opTable;
    vector<string>objectCode;
    vector<string>hteRecord;
    vector<vector<string>>literalTable(500);

    int lines = readFile(code);

    addressCounter(code,location,literalTable,lines-1);

    createSymbolTable(code,location,symbolTable,lines-1);
    printSymbolTable(symbolTable);
    printLiteralTable(literalTable);

    //initOpTable(opTable);

    /*generateOpcode(code,objectCode,opTable,lines-1);
    generateAddresses(code,objectCode,symbolTable,lines-1);

    createHead(code,location,hteRecord);
    createText(code,location,hteRecord,objectCode,lines-1);
    createEnd(location,hteRecord);
    generateHTEFile(hteRecord);
*/
    //FOR DEBUGGING

//      for(int i=0;i<literalTable.size();i++){
//        for(int j=0;j<literalTable[i].size();j++)
//            cout<<literalTable[i][j]<<' ';
//
//        cout<<endl;
//      }

//    for(int i=0 ; i<hteRecord.size(); i++)
//        cout<<hteRecord[i]<<endl;

    for(int i=0 ; i<location.size(); i++)
        cout<<hex<<location[i]<<endl;



//    for( std::map<string,string>::const_iterator it = opTable.begin(); it != opTable.end(); ++it )
//    {
//      string value = it->first;
//      string key = it->second;
//      cout<<value<<"\t"<<key<<endl;
//
//    }

//    for(int i=0;i<objectCode.size();i++)
//        cout<<objectCode[i]<<endl;

//        for(int c=0;c<code.size();c++)
//            for(int j=0;j<code[c].size();j++)
//                cout<<code[c][j]<<endl;



        return 0;
}

