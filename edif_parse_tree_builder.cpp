/**********************************************************************/
/* Author: Sumanish <sumanish.cse.jgec@gmail.com>                     */
/* Modified By: Sumanish <sumanish.cse.jgec@gmail.com>                */
/*                                                                    */  
/* This source code can be downloaded, use, modify, distribute        */
/* freely with this headed intact. Please don't delete this header.   */
/**********************************************************************/ 
#include "edif_parse_tree_builder.hpp"

void
EdifParseTreeBuilder::PrintStr(const std::string& str)
{
    std::cout << str << " ";
}

void
EdifParseTreeBuilder::PrintInt(const int& i)
{
    std::cout << i << " ";
}

void
EdifParseTreeBuilder::PrintDouble(const double& d)
{
    std::cout << d << " ";
}
