/**********************************************************************/
/* Author: Sumanish <sumanish.cse.jgec@gmail.com>                     */
/* Modified By: Sumanish <sumanish.cse.jgec@gmail.com>                */
/*                                                                    */  
/* This source code can be downloaded, use, modify, distribute        */
/* freely with this headed intact. Please don't delete this header.   */
/**********************************************************************/ 
#ifndef __EDIF_PARSE_TREE_BUILDER_HPP__
#define __EDIF_PARSE_TREE_BUILDER_HPP__
#include <iostream>
#include <string>


class EdifParseTreeBuilder
{
    public:
        EdifParseTreeBuilder() {};
        ~EdifParseTreeBuilder() {};

    public:
        void PrintStr(const std::string& str);
        void PrintInt(const int& i);
        void PrintDouble(const double& d);

};

#endif
