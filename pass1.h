#ifndef PASS1_H
#define PASS1_H

#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <iostream>
#include <iomanip>
#include <cmath>

    int readFile(std::vector<std::vector<std::string>> &code){

        std::ifstream inFile("in.txt");
        std::string temp;
        std::string tempNoSpace="";
        int i=0;

        while (std::getline(inFile, temp)){

            for(int j=0;j<temp.size();j++){

                if(temp[j] != ' ' && temp[j] != '\t' && temp[j] != '\n' && temp[j] != '\0'){

                    tempNoSpace+=temp[j];

                }else{
                    code[i].push_back(tempNoSpace);
                    tempNoSpace.clear();
                }

            }

            code[i++].push_back(tempNoSpace);
            tempNoSpace.clear();
        }

        return i;
    }


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

    std::string intToHexString(int input){

        std::stringstream ss;
        ss<<std::hex<<input;
        return ss.str();
    }

    int getStartAddress(std::vector<std::vector<std::string>> code){

        return hexToDec(code[0][2]);
    }


void addressCounter(std::vector<std::vector<std::string>> code, std::vector<int> &location, int lines){

        location.push_back(getStartAddress(code));
        int address=getStartAddress(code);

        for(int i=1 ; i<lines ; i++){

            if(code[i].size()==1){
                if(code[i][0] == "LTORG"){
                    continue;
                }else if(code[i][0][0]== '+'){
                    address+=4;
                }else
                    address+=3;

                // HANDLE INSTRUCTIONS THAT HAVE ONLY ONE OPERAND

            }else if(code[i].size()==2){

                    if(code[i][0][0]=='+'){
                        address+=4;

                    }else if(code[i][0]=="FIX" || code[i][0]=="FLOAT" || code[i][0]=="HIO" || code[i][0]=="NORM" || code[i][0]=="SIO" || code[i][0]=="TIO" || code[i][0]=="FIX" ){
                        address+=1;

                    }else if(code[i][0]=="ADDR" || code[i][0]=="CLEAR" || code[i][0]=="COMPR" || code[i][0]=="DIVR" || code[i][0]=="MULR" || code[i][0]=="RMO" || code[i][0]=="SHIFTL" || code[i][0]=="SHIFTR" || code[i][0]=="SUBR" || code[i][0]=="SVC" || code[i][0]=="TIXR"){
                        address+=2;

                    }else if(code[i][0]=="BASE"){
                        continue;

                    }else{
                        address+=3;

                    }

            }else if (code[i].size()==3){

                    if(code[i][1] == "RESW"){
                        address+=stringToDec(code[i][2]) * 3;
                    }else if(code[i][1] == "RESB"){
                        address+=stringToDec(code[i][2]);
                    }else if(code[i][1] == "WORD"){
                        address+=3;
                    }else if(code[i][1] == "BYTE"){
                        if(code[i][2][0]=='X' || code[i][2][0]=='x'){

                            for(int j=0;j<(int)ceil( (double)(code[i][2].substr(2,code[i][2].size()-3).size() ) / 2.0 );j++){
                                address+=1;
                                location.push_back(address);
                            }

                            continue;   // WE CONTINUE BECAUSE WE ALREADY PUSHED TO THE VECTOR AND WE WANT TO EAVOID RUNNING THE VECTOR PUSH AT THE END OF THE BIG LOOP

                        }else if(code[i][2][0]=='C' || code[i][2][0]=='c'){

                            for(int j=0;j<code[i][2].substr(2,code[i][2].size()-3).size();j++){
                                address+=1;
                                location.push_back(address);
                            }

                            continue;
                        }

                    }else if(code[i][1][0]=='+'){
                        address+=4;

                    }else if(code[i][1]=="FIX" || code[i][1]=="FLOAT" || code[i][1]=="HIO" || code[i][1]=="NORM" || code[i][1]=="SIO" || code[i][1]=="TIO" || code[i][1]=="FIX"){
                        address+=1;

                    }else if(code[i][1]=="ADDR" || code[i][1]=="CLEAR" || code[i][1]=="COMPR" || code[i][1]=="DIVR" || code[i][1]=="MULR" || code[i][1]=="RMO" || code[i][1]=="SHIFTL" || code[i][1]=="SHIFTR" || code[i][1]=="SUBR" || code[i][1]=="SVC" || code[i][1]=="TIXR"){
                        address+=2;

                    }else if(code[i][1]=="EQU"){
                        continue;

                    }
                    else{
                        address+=3;

                    }

            }// END SIZE 3

            location.push_back(address);

        }// END LOOP

    return;
}
    void createSymbolTable(std::vector<std::vector<std::string>> code, std::vector<int> location, std::map<std::string,std::string> &symbolTable,int lines){

        int j=0,prevj=0;

        for(int i=1; i<lines ; i++){

            if(code[i].size() == 3 && code[i][1][(code[i][1].size()-1)] != ',' && code[i][2] != "X" && code[i][2] != "x"){

                if(code[i][1] == "EQU"){

                    if(code[i][2]=="*")
                        symbolTable.insert(std::pair<std::string,std::string>(code[i][0], intToHexString(location[prevj])));
                    else
                        symbolTable.insert(std::pair<std::string,std::string>(code[i][0], code[i][2]));
                }else{

                    symbolTable.insert(std::pair<std::string,std::string>(code[i][0],intToHexString(location[j])));
                }

                if(code[i][2][0]=='X' || code[i][2][0]=='x'){


                    j+=(int)ceil( (double)(code[i][2].substr(2,code[i][2].size()-3).size() ) / 2.0) -1;

                }else if(code[i][2][0]=='C' || code[i][2][0]=='c'){

                    j+=code[i][2].substr(2,code[i][2].size()-3).size() -1;
                }

                //symbolTable.insert(std::pair<std::string,int>(code[i][0], location[j]));
            }
            prevj=j;
            j++;
        }
    }

    void printSymbolTable(std::map<std::string,std::string> symbolTable){

        std::ofstream file;

        file.open("symboltable.txt");

        for( std::map<std::string,std::string>::const_iterator it = symbolTable.begin(); it != symbolTable.end(); ++it )
        {
          std::string key = it->first;
          //int value = it->second;
          std::string value = it->second;
          file<<key<<"\t"<<std::hex<< std::setfill('0') << std::setw(4) << value<<std::endl;

        }

        file.close();

        return;
    }

#endif
