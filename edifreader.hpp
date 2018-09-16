/**********************************************************************/
/* Author: Sumanish <sumanish.cse.jgec@gmail.com>                     */
/* Modified By: Sumanish <sumanish.cse.jgec@gmail.com>                */
/*                                                                    */  
/* This source code can be downloaded, use, modify, distribute        */
/* freely with this headed intact. Please don't delete this header.   */
/**********************************************************************/ 

#include <iostream>
#include <string>

#include "edif_grammar.hpp"


class EdifReader {

    public:
        EdifReader() {}
        ~EdifReader() {}

        bool Read(std::string& filename);
};

