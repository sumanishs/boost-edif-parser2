########################################################################
## Author: Sumanish <sumanish.cse.jgec@gmail.com>                     ##
## Modified By: Sumanish <sumanish.cse.jgec@gmail.com>                ##
##                                                                    ##  
## This source code can be downloaded, use, modify, distribute        ##
## freely with this headed intact. Please don't delete this header.   ##
######################################################################## 

A C++ parser to parse EDIF (Electronic Design Interchange Format) format files. 
Developed using Boost::Spirit.
Code comes with absolutely no warranty.

It's under development and not guaranteed to parse all files.

THIS Parser only parses and prints the token and values in std::out.
Parse tree is not developed. Sample functors are added. It's user's 
resposibility to design their own parse tree and parse tree population
functors in the edif_functors.hpp. A dummy parse tree builder provided
to follow the same coding pattern to design parse tree builder.

Developement environment:
Fedora 28,
Boost 1.68.0
GCC version 8.2.0 (GCC)
