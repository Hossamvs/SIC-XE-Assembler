#ifndef HTE_H
#define HTE_H

#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include "utilities.h"

void createHead(std::vector<std::vector<std::string>> code, std::vector<int> location, std::vector<std::string> &hteRecord){

    std::stringstream stream;
    int progLength = location[location.size()-1] - location[0];

    std::string temp="H ";
    temp+=code[0][0]+" "; // program name
    stream<<std::setfill('0') << std::setw(6) << std::hex << code[0][2];
    temp+=stream.str()+" "; // starting address

    stream.str(std::string());

    stream<<std::setfill('0') << std::setw(6) << std::hex << progLength ;
    temp+= stream.str();

    hteRecord.push_back(temp);

}
void createText(std::vector<std::vector<std::string>> code, std::vector<int> location, std::vector<std::string> &hteRecord, std::vector<std::string>objectCode,int lines){

    int capacity=60;
    std::vector<std::vector<std::pair<std::string,int>>> textPool;
    std::vector<std::pair<std::string,int>> textField;

    for(int i=0;i<objectCode.size();i++){ //populates the textPool vector to construct the text records from it later

        if(objectCode[i]=="-")
            continue;

        if(objectCode[i]=="--"){

            if(textField.size()==0) //if the text record will start with a record breaker then we don't even have to start it
                continue;

            textField.push_back({"0",location[i]}); //appending the text record end address for easier calculations in the future
            textPool.push_back(textField);
            textField.clear();
            capacity=60;
            continue;
        }

        if(objectCode[i].size()<=capacity){

            capacity-=objectCode[i].size();
            textField.push_back({objectCode[i],location[i]});

        }else{

            textField.push_back({"0",location[i]});
            textPool.push_back(textField);
            textField.clear();
            capacity=60;
            i--; //stalling the next loop so we don't forget to push the current object code in the beginning of the next record
        }

    }

    if(textField.size()>0){ //dumping the last text record if it exists

        textField.push_back({"0",location[location.size()-1]});
        textPool.push_back(textField);
        textField.clear();
    }

    std::stringstream stream;

    for(int i=0;i<textPool.size();i++){ //creates text records

        std::string temp="T ";

        //construct the starting address
        stream<<std::setfill('0') << std::setw(6) << std::hex <<textPool[i][0].second;
        temp+=stream.str() + " ";
        stream.str(std::string());

        //constructing the text record length
        int length = (textPool[i][textPool[i].size()-1].second) - (textPool[i][0].second);
        stream<<std::setfill('0') << std::setw(2) << std::hex << length ;
        temp+=stream.str() + " ";
        stream.str(std::string());

        //adding the object codes for the current text record, size()-1 because the last element which is the end address shouldn't be considered an object code
        for(int j=0;j<textPool[i].size()-1;j++)
            temp+=textPool[i][j].first + " ";

        hteRecord.push_back(temp);
    }
}

void createEnd(std::vector<int> location, std::vector<std::string> &hteRecord){

    std::stringstream stream;
    std::string temp = "E ";
    stream<<std::setfill('0') << std::setw(6) << std::hex << location[0] ;
    temp+=stream.str();
    hteRecord.push_back(temp);
}

void createModification(std::vector<int> location,std::vector<std::string> &hteRecord, std::vector<std::vector<std::string>> code){
    std::string temp = "M ";
    std::stringstream stream;
    int address;

    for(int i = 0 ; i<code.size(); i++){
        if(code[i].size() == 2){//size 2 instructions
            if(code[i][0] == "+JSUB"){
                address = location[i-1]+1;
                //std::cout<<"address is "<<intToHexString(address)<<std::endl;

                stream<<std::setfill('0') << std::setw(6) << intToHexString(address);
                temp+=stream.str()+" ";

                stream.str(std::string());

                temp+= "05";

                hteRecord.push_back(temp);
                temp = "M ";
            }
        }

        if(code[i].size() == 3){//size 3 instructions
            if(code[i][1] == "+JSUB"){
                address = location[i-1]+1;
                //std::cout<<"address is "<<intToHexString(address)<<std::endl;
                stream<<std::setfill('0') << std::setw(6) << intToHexString(address);
                temp+=stream.str()+" ";
                stream.str(std::string());
                temp+= "05";
                hteRecord.push_back(temp);
                temp = "M ";
            }
        }

        stream.str(std::string());
    }
}

void generateHTEFile(std::vector<std::string> hteRecord){

        std::ofstream file;

        file.open("HTE.txt");

        for( int i = 0 ; i < hteRecord.size() ; i++)
          file<<hteRecord[i]<<std::endl;

        file.close();
}

#endif // HTE_H
