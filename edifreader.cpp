/**********************************************************************/
/* Author: Sumanish <sumanish.cse.jgec@gmail.com>                     */
/* Modified By: Sumanish <sumanish.cse.jgec@gmail.com>                */
/*                                                                    */  
/* This source code can be downloaded, use, modify, distribute        */
/* freely with this headed intact. Please don't delete this header.   */
/**********************************************************************/ 

#include "edifreader.hpp"
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "edif_parse_tree_builder.hpp"

using namespace boost::spirit;

bool 
EdifReader::Read(std::string& filename){

    typedef std::string::iterator base_iterator_type;
    typedef lex::lexertl::token< base_iterator_type, boost::mpl::vector<unsigned int, std::string> > token_type;
    typedef lex::lexertl::actor_lexer<token_type> lexer_type;
    typedef edif_tokens<lexer_type> edif_tokens;
    typedef edif_tokens::iterator_type iterator_type;
    typedef edif_grammar<iterator_type, edif_tokens::lexer_def> edif_grammar;

    EdifParseTreeBuilder* ptb = new EdifParseTreeBuilder();

    edif_tokens tokens;                                 // Our lexer
    edif_grammar grammar(tokens, ptb);                  // Our parser

    std::ifstream inFile;
    inFile.open(filename.c_str());
    if(inFile.fail()){
        std::cout << "Cannot open file to read...." << std::endl;
        return false;
    }

    std::stringstream strStream;
    strStream << inFile.rdbuf();
    std::string str(strStream.str());
    //str.pop_back();
    //std::cout << "File content:\n" << str << "!" << std::endl;
    inFile.close();

    std::string::iterator it = str.begin();
    iterator_type iter = tokens.begin(it, str.end());
    iterator_type end = tokens.end();

    //iterator_type itr = iter;
    //while (itr != end && token_is_valid(*itr))
    //{   
    //    std::cout << "Token: " << itr->id() << ": " /*<< tokens.nameof(itr)*/ << " ('" << itr->value() << "')\n";
    //    ++itr;
    //}   
    ////return 0;


    std::string ws("WS");
    bool r = qi::phrase_parse(iter, end, grammar, qi::in_state(ws)[tokens.self]);

    if (r && iter == end)
    {
        std::cout << "\n-------------------------\n";
        std::cout << "Parsing succeeded\n";
        std::cout << "-------------------------\n";
        return true;
    }
    else
    {
        std::cout << "\n-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "-------------------------\n";
        return false;
    }

    std::cout << "Bye... :-) \n\n";
    return true;
}
