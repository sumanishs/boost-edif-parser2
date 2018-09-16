#define BOOST_VARIANT_USE_RELAXED_GET_BY_DEFAULT

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <iostream>
#include <fstream>
#include <string>

using namespace boost::spirit;
using boost::phoenix::val;

enum token_ids
{
    ID_INT_CONSTANT = 1000,
    ID_DOUBLE_CONSTANT,
    ID_DOUBLE_EXP_CONSTANT,
    ID_IDENTIFIER,
    ID_EDIF,
    ID_EDIF_VERSION,
};

template <typename Lexer>
struct edif_tokens : lex::lexer<Lexer>
{
    edif_tokens()
    {
        identifier      = "[a-zA-Z_][a-zA-Z_]*";
        int_constant    = "[0-9]";
        double_constant = "[0-9]+.[0-9]+";
        double_exp_constant = "[0-9]+e-[0-9]+";
        edif_           = "edif";
        edif_version_   = "edifVersion";

        this->self = lex::token_def<>('(') | ')' | '{' | '}' | '=' | ';' | ':' | '"' | '"';

        this->self.add
            (int_constant, ID_INT_CONSTANT)
            (double_constant, ID_DOUBLE_CONSTANT)
            (double_exp_constant, ID_DOUBLE_EXP_CONSTANT)
            (edif_, ID_EDIF)
            (edif_version_, ID_EDIF_VERSION)
            (identifier, ID_IDENTIFIER)
        ;

        this->self("WS") 
            =   lex::token_def<>("[ \\t\\n]+") 
            |   "\\/\\*[^*]*\\*+([^/*][^*]*\\*+)*\\/"
            |   "#[^\\n]*"
            ;
    }

    lex::token_def<std::string> identifier,  double_exp_constant ;
    lex::token_def<unsigned int> int_constant;
    lex::token_def<double> double_constant;
    
    lex::token_def<std::string> edif_, edif_version_
                                ;
};
