#include "Helper.h"

//Don't Change this function its only for error checking it its throwing you errors then comment it out:
int ErrorChecking(char* arg)
{   
    fstream inputfile;
    string line;
    string lower;
    string sec_line;
    inputfile.open(arg);
    vector<string> vec;
    if(inputfile.is_open()){
        //Converts into lower case and adds to a vector:
        int i = 0;
        while (getline(inputfile,line)){
            lower = line; string::iterator character = lower.begin();
            while(character != lower.end()){
                *character = tolower(*character);
                character++;
            }
            vec.push_back(lower);
            //cerr << vec[i] <<"\n";
            i++;
        }
        if(vec[vec.size()-1] != "end"){cerr << "Program did not end in END!!!\n";return ERROR; }        
        for(i = 0; i < vec.size();i++){
            line = vec[i];
            //line = lower;
            //Read in the instructions HERE:
            if(i == 0 && line != "start"){cerr<<"Start does not begin the program!!!\n";return ERROR;}
            if(i == 0 && line == "end"){cerr<<"The program start with end!!!\n";return ERROR;}
            if(line == "start"){
                for(int j = 1; j<vec.size()-1;j++){
                    sec_line = vec[j];
                    if(sec_line == "start"){cerr << "BOTH are start!!!\n"; return ERROR;}
                }       
            }
            //if(i != 0 && line == "end"){return ERROR;}
            //cerr << line << "\n"; //TEST STATEMENT
        }
        //Close the input file:
        inputfile.close();
    }
    return NOERROR;
}

/* ReadCommand notes to keep in mind:
  This runs the Parser, if anything needs to be runner, for the parser,
  then it should be run here(this is unlikely but mentioned just in case):
*/
void ReadCommand(string line, InstructBuf* ibuf, StringBuf* sbuf)
{
    Parser obj; //Parser object to call the function 
    //Convert instructions to lowercase(For consistentcy and to ALWAYS ensure correct inputs in program):
    string lower = line;
    string::iterator character = lower.begin();
    while(character != lower.end()){
        *character = tolower(*character);
        character++;
    }
    /*----------------------------------------------------------Get the Flag:----------------------------------------------------------*/
    //Stores the parsed command to which gets executed in BuildStmt
    string parsed_command;
    int flag = obj.GetFlag(lower, &parsed_command);
    obj.BuildStmt(flag, lower, parsed_command, ibuf, sbuf);
}