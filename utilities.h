#ifndef UTILITIES_H
#define UTILITIES_H

#include "optable.h"

using namespace std;

int hexToDec(std::string str){

        int address;

        std::stringstream stream;
        stream << str;
        stream >> std::hex >> address;

        return address;
    }

int stringToDec(std::string str){

        int output;

        std::stringstream stream;
        stream << str;
        stream >> output;

        return output;
}

    int hexStringToDec(std::string str){
        int output;
        std::stringstream stream;
        stream <<std::hex<<str;
        stream >> output;

        return output;
    }

    std::string intToHexString(int input){

        std::stringstream ss;
        ss<<std::hex<<input;
        return ss.str();
    }

int handleFormat4(vector<string> line, string instruction ,map<string,string>opTable){

    string cleanedInstruction = instruction.substr(1,instruction.size()-1);

    int opcode = hexStringToDec(opTable.find(cleanedInstruction)->second);

        //to remove n,i
    opcode &= 252;


    if(line.size()==2){

        if(line[1][0]=='@'){

            //set n
            opcode |=2;

        }else if(line[1][0]=='#'){
            //set i
            opcode|=1;
            opcode = opcode<<4;
            return opcode;

        }else{
            //set n,i
            opcode|=3;
        }

    }else if(line.size()==3){

        if(line[2][0]=='@'){

            //set n
            opcode |=2;

        }else if(line[2][0]=='#'){

            //set i
            opcode|=1;
            opcode = opcode<<4;
            return opcode;

        }else{
            //set n,i
            opcode|=3;
        }

    }

    opcode = opcode << 4;

        if(line.size()==2){

        if(line[1][line[1].size()-1]=='x' || line[1][line[1].size()-1]=='X'){

            opcode|=9;  //set x,e

        }else{
            opcode|=1; //set e only
        }


    }else if(line.size()==3){

        if(line[2][line[2].size()-1]=='x' || line[2][line[2].size()-1]=='X'){

            opcode|=9;  //set x,e

        }else{
            opcode|=1; //set e only
        }
    }

    //to set n,i
    /*opcode |= 3;

    //make space for x,b,p,e
    opcode = opcode<<4;

    if(line.size()==2){

        if(line[1][line[1].size()-1]=='x' || line[1][line[1].size()-1]=='X'){

            opcode|=9;  //set x,e

        }else{
            opcode|=1; //set e only
        }


    }else if(line.size()==3){

        if(line[2][line[2].size()-1]=='x' || line[2][line[2].size()-1]=='X'){

            opcode|=9;  //set x,e

        }else{
            opcode|=1; //set e only
        }
    }
    */
    return opcode;
}


int handleFormat3(vector<string> line, string instruction ,map<string,string>opTable){

    int opcode = hexStringToDec(opTable.find(instruction)->second);

    //to remove n,i
    opcode &= 252;

    if(line.size()==1){

        opcode |= 3;
        opcode = opcode << 4;
        return opcode;
    }

    if(line.size()==2){

        if(line[1][0]=='@'){

            //set n
            opcode |=2;

        }else if(line[1][0]=='#'){
            //set i
            opcode|=1;
            opcode = opcode<<4;
            return opcode;

        }else{
            //set n,i
            opcode|=3;
        }

    }else if(line.size()==3){

        if(line[2][0]=='@'){

            //set n
            opcode |=2;

        }else if(line[2][0]=='#'){

            //set i
            opcode|=1;
            opcode = opcode<<4;
            return opcode;

        }else{
            //set n,i
            opcode|=3;
        }

    }

    //make space for x,b,p,e
    opcode = opcode<<4;

    if(line.size()==2){

        if(line[1][line[1].size()-1]=='x' || line[1][line[1].size()-1]=='X'){
            //set x,b,p,e to 1 0 1 0
            opcode|=10;

        }else{
            //set x,b,p,e to 0 0 1 0
            opcode|=2;
        }

    }else if(line.size()==3){

            if(line[2][line[2].size()-1]=='x' || line[2][line[2].size()-1]=='X'){
                //set x,b,p,e to 1 0 1 0
                opcode|=10;

            }else{
                //set x,b,p,e to 0 0 1 0
                opcode|=2;
            }
    }

    return opcode;
}

int handleFormat2(vector<string> line, string instruction ,map<string,string>opTable){
    /*a 0
     x 1
     l 2
     b 3
     s 4
     t 5
     f 6
     pc 8
     sw 9
    */
    string r1,r2;

    if(line.size()==2){

        int commaIndex=line[1].find(',');

        if(line[1].find(',') == std::string::npos){

            r1 = line[1].substr(0,commaIndex);
            r2 ="-1";

        }else{
            r1 = line[1].substr(0,commaIndex);
            r2 = line[1].substr(commaIndex+1,line[1].size()-r1.size()-1);
        }

    }else if(line.size()==3){

        int commaIndex=line[2].find(',');

        if(line[2].find(',') == std::string::npos){

            r1 = line[2].substr(0,commaIndex);
            r2 ="-1";

        }else{
            r1 = line[2].substr(0,commaIndex);
            r2 = line[2].substr(commaIndex+1,line[2].size()-r1.size()-1);
        }

    }

    int opcode = hexStringToDec(opTable.find(instruction)->second);

    //make space for r1
    opcode = opcode<<4;

    if(r1=="A"){
        opcode|=0;
    }else if(r1=="X"){
        opcode|=1;
    }else if(r1=="L"){
        opcode|=2;
    }else if(r1=="B"){
        opcode|=3;
    }else if(r1=="S"){
        opcode|=4;
    }else if(r1=="T"){
        opcode|=5;
    }else if(r1=="F"){
        opcode|=6;
    }else if(r1=="PC"){
        opcode|=8;
    }else if(r1=="SW"){
        opcode|=9;
    }

    //make space for r2
    opcode = opcode<<4;

    if(r2=="-1")
        return opcode;


    if(r2=="A"){
        opcode|=0;
    }else if(r2=="X"){
        opcode|=1;
    }else if(r2=="L"){
        opcode|=2;
    }else if(r2=="B"){
        opcode|=3;
    }else if(r2=="S"){
        opcode|=4;
    }else if(r2=="T"){
        opcode|=5;
    }else if(r2=="F"){
        opcode|=6;
    }else if(r2=="PC"){
        opcode|=8;
    }else if(r2=="SW"){
        opcode|=9;
    }

    return opcode;

}

int handleFormat1(vector<string> line, string instruction ,map<string,string>opTable){

    int opcode = hexStringToDec(opTable.find(instruction)->second);

    return opcode;

}

int findInLiteralTable(string literal,vector<vector<string>>literalTable){

        for(int i=0;i<literalTable.size();i++){
            if(literalTable[i][0] == literal){
                return hexStringToDec(literalTable[i][3]);
            }
        }
}

bool checkLiteralTable(string literal,vector<vector<string>>literalTable){
    bool flag = false;
    for(int i=0 ; i< literalTable.size();i++){
        if(literalTable[i][0] == literal){
            return true;
        }
    }
    return false;
    //return flag;
}

int getLiteralValue(string literal,vector<vector<string>>literalTable){

        for(int i=0;i<literalTable.size();i++){
            if(literalTable[i][0] == literal){
                return hexStringToDec(literalTable[i][1]);
            }
        }
}


#endif // UTILITIES_H
