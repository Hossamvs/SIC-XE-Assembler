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
    int progLength = location[location.size()-1] - location[0] + 1;

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

    std::stringstream stream;
    std::string temp = "T ";

    int startLocation = location[0];
    int capacity=60;
    int length=0;
    int i=0;
    for(i=0;i<objectCode.size();i++){

        if(objectCode[i]=="-"){
            continue;
        }

        if(objectCode[i]=="--"){

            if(temp.size()<3){
                continue;
            }

            length = location[i] - startLocation;

            startLocation = location[i+3];
            //cout<<"Location is" <<intToHexString(location[i])<<endl; //pour debugging
            stream<<std::setfill('0') << std::setw(2) << std::hex << length ;
            temp.insert(9,stream.str()+" ");

            stream.str(std::string());

            hteRecord.push_back(temp);

            temp="T ";
            capacity=60;
            continue;
        }

        if(temp == "T "){
            stream<<std::setfill('0') << std::setw(6) << std::hex << startLocation ;
            temp+=stream.str() + " ";

            stream.str(std::string());
        }


        if(objectCode[i].size() <= capacity){
            temp+=objectCode[i] + " ";
            capacity-=objectCode[i].size();
        }
        else{
            length = location[i] - startLocation;

            startLocation = location[i];
            //cout<<"Location is" <<intToHexString(location[i])<<endl; //pour debugging
            stream<<std::setfill('0') << std::setw(2) << std::hex << length ;
            temp.insert(9,stream.str()+" ");

            stream.str(std::string());

            hteRecord.push_back(temp);

            temp="T ";
            capacity=60;
            i--;
        }
    }
            i--;
            length = location[i] - startLocation +1 ;

            startLocation = location[i];

            stream<<std::setfill('0') << std::setw(2) << std::hex << length ;
            temp.insert(9,stream.str()+" ");

            stream.str(std::string());

            hteRecord.push_back(temp);


}
/*void createText(std::vector<std::vector<std::string>> code, std::vector<int> location, std::vector<std::string> &hteRecord, std::vector<std::string>objectCode,int lines){

    std::stringstream stream;
    std::string temp = "T ";
    int startAddress=location[0];
    int endAddress=location[1];
    int capacity = 60;
    int length=0;

    for(int i=0 ; i<objectCode.size() ; i++){
        if(objectCode[i] == "--" || objectCode[i].size() > capacity){
            if(temp.size()<3){
                continue;
            }
            length = endAddress - startAddress;

            startAddress = endAddress;
            //endAddress = lo TODO

            stream<<std::setfill('0') << std::setw(2) << std::hex << length ;
            temp.insert(9,stream.str()+" ");

            stream.str(std::string());

            hteRecord.push_back(temp);

            temp="T ";
            capacity=60;
        }
        else if(objectCode[i] == "-"){
            continue;
        }else if(temp == "T "){
            stream<<std::setfill('0') << std::setw(6) << std::hex << startAddress ;
            temp+=stream.str() + " ";
            stream.str(std::string());
        }else {
            temp+=objectCode[i] + " ";
            capacity-=objectCode[i].size();
            endAddress=location[i+1];
        }
    }
}*/

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
