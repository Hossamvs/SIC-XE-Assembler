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

    int getStartAddress(std::vector<std::vector<std::string>> code){

        return hexToDec(code[0][2]);
    }


void addressCounter(std::vector<std::vector<std::string>> code, std::vector<int> &location, std::vector<std::vector<std::string>>&literalTable ,int lines){

        location.push_back(getStartAddress(code));
        int address=getStartAddress(code);

        std::vector<std::string>literals;
        int literalTableIndex=0;

        for(int i=1 ; i<lines ; i++){

            if(code[i].size()==1){
                if(code[i][0]== "LTORG" && literals.size()>=1){
                    for(int j =0;j<literals.size();j++){    // EMPTYING LOOP

                         //PUSH IN LITERAL TABLE
                         literalTable[literalTableIndex].push_back(literals[j]); // LITERAL NAME

                         std::stringstream stream;


                         if(literals[j][1] == 'X' || literals[j][1] == 'x'){

                                 // CONTINUE PUSH IN LITERAL TABLE
                                 stream<<std::hex<<literals[j].substr(3,literals[j].size()-4);
                                 literalTable[literalTableIndex].push_back(stream.str()); // LITERAL VALUE
                                 stream.str(std::string());

                                 stream<<(int)ceil( (double)(literals[j].substr(3,literals[j].size()-4).size() ) / 2.0 );
                                 literalTable[literalTableIndex].push_back(stream.str()); // LITERAL SIZE
                                 stream.str(std::string());

                                 stream<<std::hex<<location[location.size()-1];
                                 literalTable[literalTableIndex].push_back(stream.str()); // LITERAL ADDRESS
                                 stream.str(std::string());

                                 literalTableIndex++;

                                 for(int k=0;k<(int)ceil( (double)(literals[j].substr(3,literals[j].size()-4).size() ) / 2.0 );k++){
                                    address+=1;
                                    location.push_back(address);
                                }

                         }else if(literals[j][1] == 'C' || literals[j][1] == 'c'){

                                // CONTINUE PUSH IN LITERAL TABLE
                                 std::string literalContent = literals[j].substr(3,literals[j].size()-4);

                                 for(int k=0;k<literalContent.size();k++)
                                    stream<<(int)literalContent[k];

                                 literalTable[literalTableIndex].push_back(stream.str()); // LITERAL VALUE
                                 stream.str(std::string());

                                 stream<<literals[j].substr(3,literals[j].size()-4).size();
                                 literalTable[literalTableIndex].push_back(stream.str()); // LITERAL SIZE
                                 stream.str(std::string());

                                 stream<<std::hex<<location[location.size()-1];
                                 literalTable[literalTableIndex].push_back(stream.str()); // LITERAL ADDRESS
                                 stream.str(std::string());

                                 literalTableIndex++;

                                for(int k=0;k<literals[j].substr(3,literals[j].size()-4).size();k++){
                                    address+=1;
                                    location.push_back(address);
                                }

                         }

                    } // END EMPTYING LOOP

                    literals.clear();

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


                    if(code[i][1][0] == '='){
                        literals.push_back(code[i][1]);

                    }

            }else if (code[i].size()==3){ // END SIZE 2 START SIZE 3

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

                    }else{
                        address+=3;

                    }

                if(code[i][2][0] == '='){
                    literals.push_back(code[i][2]);

                }

            }// END SIZE 3

            location.push_back(address);

        }// END LOOP


        if(literals.size()>=1){

            for(int j =0;j<literals.size();j++){    // EMPTYING LOOP

                         //PUSH IN LITERAL TABLE
                         literalTable[literalTableIndex].push_back(literals[j]); // LITERAL NAME

                         std::stringstream stream;


                         if(literals[j][1] == 'X' || literals[j][1] == 'x'){

                                 // CONTINUE PUSH IN LITERAL TABLE
                                 stream<<std::hex<<literals[j].substr(3,literals[j].size()-4);
                                 literalTable[literalTableIndex].push_back(stream.str()); // LITERAL VALUE
                                 stream.str(std::string());

                                 stream<<(int)ceil( (double)(literals[j].substr(3,literals[j].size()-4).size() ) / 2.0 );
                                 literalTable[literalTableIndex].push_back(stream.str()); // LITERAL SIZE
                                 stream.str(std::string());

                                 stream<<std::hex<<location[location.size()-1];
                                 literalTable[literalTableIndex].push_back(stream.str()); // LITERAL ADDRESS
                                 stream.str(std::string());

                                 literalTableIndex++;

                                 for(int k=0;k<(int)ceil( (double)(literals[j].substr(3,literals[j].size()-4).size() ) / 2.0 );k++){
                                    address+=1;
                                    location.push_back(address);
                                }

                         }else if(literals[j][1] == 'C' || literals[j][1] == 'c'){

                                // CONTINUE PUSH IN LITERAL TABLE
                                 std::string literalContent = literals[j].substr(3,literals[j].size()-4);

                                 for(int k=0;k<literalContent.size();k++)
                                    stream<<(int)literalContent[k];

                                 literalTable[literalTableIndex].push_back(stream.str()); // LITERAL VALUE
                                 stream.str(std::string());

                                 stream<<literals[j].substr(3,literals[j].size()-4).size();
                                 literalTable[literalTableIndex].push_back(stream.str()); // LITERAL SIZE
                                 stream.str(std::string());

                                 stream<<std::hex<<location[location.size()-1];
                                 literalTable[literalTableIndex].push_back(stream.str()); // LITERAL ADDRESS
                                 stream.str(std::string());

                                 literalTableIndex++;

                                for(int k=0;k<literals[j].substr(3,literals[j].size()-4).size();k++){
                                    address+=1;
                                    location.push_back(address);
                                }

                         }

                    } // END EMPTYING LOOP

                    literals.clear();

        }

    return;
}
    void createSymbolTable(std::vector<std::vector<std::string>> code, std::vector<int> location, std::map<std::string,std::string> &symbolTable,int lines){

        int j=0;

        for(int i=1; i<lines ; i++){

            if(code[i].size() == 3 && code[i][1][(code[i][1].size()-1)] != ',' && code[i][2] != "X" && code[i][2] != "x"){

                if(code[i][1] == "EQU"){

                    if(code[i][2]=="*")
                        symbolTable.insert(std::pair<std::string,std::string>(code[i][0], intToHexString(location[j--])));
                    else
                        symbolTable.insert(std::pair<std::string,std::string>(code[i][0], code[i][2]));
                }else{

                    symbolTable.insert(std::pair<std::string,std::string>(code[i][0],intToHexString(location[j+1])));
                }

                if(code[i][2][0]=='X' || code[i][2][0]=='x'){


                    j+=(int)ceil( (double)(code[i][2].substr(2,code[i][2].size()-3).size() ) / 2.0) -1;

                }else if(code[i][2][0]=='C' || code[i][2][0]=='c'){

                    j+=code[i][2].substr(2,code[i][2].size()-3).size() -1;
                }

                //symbolTable.insert(std::pair<std::string,int>(code[i][0], location[j]));
            }
            j++;
        }
        //for expressions
        for( std::map<std::string,std::string>::const_iterator it = symbolTable.begin(); it != symbolTable.end(); ++it ){
                std::string key = it->first;
                std::string temp = it->second;

                //handling subtraction
                std::size_t subFound = temp.find('-');
                subFound=temp.find('-');
                if(subFound!=std::string::npos){
                    std::size_t x = temp.find('-');
                    std::string firstOperand = temp.substr(0,subFound);
                    std::string secondOperand = temp.substr(subFound+1);
                    std::map<std::string,std::string>::const_iterator itr;

                    int firstOperandNumber = hexStringToDec(symbolTable.find(firstOperand)->second);
                    int secondOperandNumber = hexStringToDec(symbolTable.find(secondOperand)->second);

                    symbolTable.at(key)=intToHexString(firstOperandNumber - secondOperandNumber );

                    /* pour debugging */
                    //std::cout<<secondOperandNumber<<std::endl;
                    //std::cout<<firstOperandNumber<<std::endl;
                }

                //handling addition
                std::size_t addFound = temp.find('+');
                addFound=temp.find('+');
                if(addFound!=std::string::npos){
                    std::size_t x = temp.find('+');
                    std::string firstOperand = temp.substr(0,addFound);
                    std::string secondOperand = temp.substr(addFound+1);
                    std::map<std::string,std::string>::const_iterator itr;

                    int firstOperandNumber = hexStringToDec(symbolTable.find(firstOperand)->second);
                    int secondOperandNumber = hexStringToDec(symbolTable.find(secondOperand)->second);

                    symbolTable.at(key)=intToHexString(firstOperandNumber + secondOperandNumber );

                    /* pour debugging */
                    //std::cout<<secondOperandNumber<<std::endl;
                    //std::cout<<firstOperandNumber<<std::endl;
                }
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
