#include "ProjectMain.h"
#include "Parser.h"
#include "StringBuffer.h"
#include "Helper.h"
#include <vector>


int main(int argc, char* argv[])
{
    //Check if the number arguments are correct:
    if(argc != 3){//Remember the executable is one
        cerr << "Incorrect number of arguments\n";
        cerr << "g++ -std=c++11 *.cpp\n";
        cerr << "./a.out practice_case.txt prac_out.txt \n";
        return EXIT_FAILURE;
    }
    /*--------------------------------------------Initailze Object Variables:--------------------------------------------*/
    //Create and instance of Instruct Buffer to add the vector to it to hold the instruction Buffer:
    InstructBuf* ibuf = new InstructBuf(); //This is the Instruction Buffer
    StringBuf* sbuf = new StringBuf(); //This is the String Buffer
    //You will need to create the Symbol Table and the String Buffer instances here:
    //(As done Above for the instruction buffer):

    /*----------------------------------Input and output variables----------------------------------*/
    //Open an input file:
    fstream inputfile; //Input file
    string line; //Is the line in the file
    inputfile.open(argv[1]);
    //Open output file:
    //This is meant to create the output file in the correct order:
    ofstream outfile; string out_name  = argv[1]; out_name += ".pout";
    outfile.open(out_name);

    //IF the file is open:
    if(inputfile.is_open()){
        /*__________________________________________Checks Errors in file:__________________________________________*/
        int is_valid = NOERROR; //Set to assume No error in file(Refer to h file to see what NOERROR etc is)
        is_valid = ErrorChecking(argv[1]);
        if(is_valid == ERROR){cerr << "ERROR!!! INVALID INPUT!!!\n";outfile.open(argv[2]); outfile.close(); return EXIT_FAILURE;}
        
        /*______________________________________________Start Parsing______________________________________________*/
        //Reads the the line from the file:
        while(getline(inputfile,line)){
            //Read in the instructions HERE(PARSES the file & reads teh commands):
            ReadCommand(line, ibuf, sbuf);
        }
        /*---------------------------------------Write to the outputfile:---------------------------------------*/
            /*=========================Writing output of the String Buffer it has been built, and partially tested =========================*/
        //Open the output file:
        for(int i = 0; i < sbuf->str_buffer.size();i++){
            outfile << sbuf->str_buffer[i]; 
            outfile << "\n"; 
        }
            /*==============================Writing output of the Instruction Buffer it Works very WEll!!!==============================*/
        int i = 0;
        while(i < ibuf->inst_buffer.size()){
            outfile << ibuf->inst_buffer[i]->Printer(); 
            i++;
            //MAy need ths://if(i != ibuf->inst_buffer.size()){}
            outfile << "\n"; 
        }
        /*---------------------------------------------------FILE Writing Complete:---------------------------------------------------*/

        //Close the input and output files:
        inputfile.close(); 
        outfile.close();
    }
    else{ 
        cerr << "Error opening the inputfile!!!\n";
        return EXIT_FAILURE;
    }
    return  EXIT_SUCCESS;
}