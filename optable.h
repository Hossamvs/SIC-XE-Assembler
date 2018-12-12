#ifndef OPTABLE_H
#define OPTABLE_H

void initOpTable(std::map<std::string,std::string>&opTable){

    opTable.insert(std::pair<std::string,std::string>("ADD","18"));
    opTable.insert(std::pair<std::string,std::string>("ADDF","58"));
    opTable.insert(std::pair<std::string,std::string>("ADDR","90"));
    opTable.insert(std::pair<std::string,std::string>("AND","40"));

    opTable.insert(std::pair<std::string,std::string>("CLEAR","B4"));
    opTable.insert(std::pair<std::string,std::string>("COMP","28"));

    opTable.insert(std::pair<std::string,std::string>("COMPF","88"));
    opTable.insert(std::pair<std::string,std::string>("COMPR","A0"));

    opTable.insert(std::pair<std::string,std::string>("DIV","24"));
    opTable.insert(std::pair<std::string,std::string>("DIVF","64"));
    opTable.insert(std::pair<std::string,std::string>("DIVR","9C"));

    opTable.insert(std::pair<std::string,std::string>("FIX","C4"));
    opTable.insert(std::pair<std::string,std::string>("FLOAT","C0"));
    opTable.insert(std::pair<std::string,std::string>("HIO","F4"));

    opTable.insert(std::pair<std::string,std::string>("J","3C"));
    opTable.insert(std::pair<std::string,std::string>("JEQ","30"));
    opTable.insert(std::pair<std::string,std::string>("JGT","34"));
    opTable.insert(std::pair<std::string,std::string>("JLT","38"));
    opTable.insert(std::pair<std::string,std::string>("JSUB","48"));

    opTable.insert(std::pair<std::string,std::string>("LDA","00"));
    opTable.insert(std::pair<std::string,std::string>("LDB","68"));
    opTable.insert(std::pair<std::string,std::string>("LDCH","50"));
    opTable.insert(std::pair<std::string,std::string>("LDF","70"));
    opTable.insert(std::pair<std::string,std::string>("LDL","08"));
    opTable.insert(std::pair<std::string,std::string>("LDS","6C"));
    opTable.insert(std::pair<std::string,std::string>("LDT","74"));
    opTable.insert(std::pair<std::string,std::string>("LDX","04"));
    opTable.insert(std::pair<std::string,std::string>("LPS","D0"));

    opTable.insert(std::pair<std::string,std::string>("MUL","20"));
    opTable.insert(std::pair<std::string,std::string>("MULF","60"));
    opTable.insert(std::pair<std::string,std::string>("MULR","98"));
    opTable.insert(std::pair<std::string,std::string>("NORM","C8"));
    opTable.insert(std::pair<std::string,std::string>("OR","44"));
    opTable.insert(std::pair<std::string,std::string>("RD","D8"));

    opTable.insert(std::pair<std::string,std::string>("RMO","AC"));
    opTable.insert(std::pair<std::string,std::string>("RSUB","4C"));
    opTable.insert(std::pair<std::string,std::string>("SHIFT","A4"));
    opTable.insert(std::pair<std::string,std::string>("SHIFTR","A8"));
    opTable.insert(std::pair<std::string,std::string>("SIO","F0"));
    opTable.insert(std::pair<std::string,std::string>("SSK","EC"));

    opTable.insert(std::pair<std::string,std::string>("STA","0C"));
    opTable.insert(std::pair<std::string,std::string>("STB","78"));
    opTable.insert(std::pair<std::string,std::string>("STCH","54"));
    opTable.insert(std::pair<std::string,std::string>("STF","80"));
    opTable.insert(std::pair<std::string,std::string>("STI","D4"));
    opTable.insert(std::pair<std::string,std::string>("STL","14"));
    opTable.insert(std::pair<std::string,std::string>("STS","7C"));
    opTable.insert(std::pair<std::string,std::string>("STSW","E8"));
    opTable.insert(std::pair<std::string,std::string>("STT","84"));
    opTable.insert(std::pair<std::string,std::string>("STX","10"));

    opTable.insert(std::pair<std::string,std::string>("SUB","1C"));
    opTable.insert(std::pair<std::string,std::string>("SUBF","5C"));
    opTable.insert(std::pair<std::string,std::string>("SUBR","94"));

    opTable.insert(std::pair<std::string,std::string>("SVC","B0"));

    opTable.insert(std::pair<std::string,std::string>("TD","E0"));
    opTable.insert(std::pair<std::string,std::string>("TIO","F8"));
    opTable.insert(std::pair<std::string,std::string>("TIX","2C"));
    opTable.insert(std::pair<std::string,std::string>("TIXR","B8"));
    opTable.insert(std::pair<std::string,std::string>("WD","DC"));
}

#endif
