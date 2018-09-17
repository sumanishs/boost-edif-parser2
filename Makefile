########################################################################
## Author: Sumanish <sumanish.cse.jgec@gmail.com>                     ##
## Modified By: Sumanish <sumanish.cse.jgec@gmail.com>                ##
##                                                                    ##  
## This source code can be downloaded, use, modify, distribute        ##
## freely with this headed intact. Please don't delete this header.   ##
######################################################################## 

CC=g++
IPATHS=-I. -I../../Boost_1.68/boost_1_68_0
CFLAGS=-g -w
LPATHS=-L../../Boost_1.68/boost_1_68_0
LFLAGS=
DEPS=edif_tokens.hpp edif_grammar.hpp edifreader.hpp edif_functors.hpp edif_parse_tree_builder.hpp
OBJS=edifreader.o edif_parse_tree_builder.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(IPATHS) 

EdifParse: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LPATHS) $(LFLAGS)

clean:
	rm -f *.o *.log EdifParse 
