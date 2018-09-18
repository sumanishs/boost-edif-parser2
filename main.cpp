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
    clock_t start, end;
    
    start = clock();
    if(reader.Read(file)){
        std::cout << "Done...." << std::endl;
        end = clock();
        double time_taken = ((double)(end - start))/CLOCKS_PER_SEC;
        std::cout << "Time taken to parse the design: " << time_taken << "seconds" << std::endl;
        return 0;
    }   
    else {
        std::cout << "Failed...." << std::endl;
        end = clock();
        double time_taken = ((double)(end - start))/CLOCKS_PER_SEC;
        std::cout << "Execution time: " << time_taken << "seconds" << std::endl;
        return 1;
    }  
}

