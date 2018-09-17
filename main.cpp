/**********************************************************************/
/* Author: Sumanish <sumanish.cse.jgec@gmail.com>                     */
/* Modified By: Sumanish <sumanish.cse.jgec@gmail.com>                */
/*                                                                    */  
/* This source code can be downloaded, use, modify, distribute        */
/* freely with this headed intact. Please don't delete this header.   */
/**********************************************************************/ 

#include <iostream>
#include <string>

#include "edifreader.hpp"

int main(int argc, char* argv[])
{
    if(argc < 2){ 
        std::cout << "Usage:" << argv[0] << " <file name>" << std::endl;
        return 1;
    }   

    std::string file (argv[1]);
    EdifReader reader;
    if(reader.Read(file)){
        std::cout << "Done...." << std::endl;
        return 0;
    }   
    else {
        std::cout << "Failed...." << std::endl;
        return 1;
    }  
    std::cout << ".......BYE...... :-)" << std::endl; 
}

