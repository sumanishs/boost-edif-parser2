#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/bind.hpp>
#include "edif_parse_tree_builder.hpp"

#include "edif_tokens.hpp"
#include "edif_functors.hpp"

using namespace boost::spirit;
using namespace boost::phoenix;

template <typename Iterator, typename Lexer>
struct edif_grammar 
  : qi::grammar<Iterator, qi::in_state_skipper<Lexer> >
{
    template <typename TokenDef>
    edif_grammar(TokenDef const& tok, EdifParseTreeBuilder* aPtb)
      : edif_grammar::base_type(start), ptb(aPtb)
    {
        using boost::spirit::_val;
		using boost::spirit::_1;
		using boost::spirit::_2;
		using boost::spirit::_3;
		using boost::spirit::_4;

        start       = +statements;  
        statements = '(' >> tok.edif_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] >> edif_version_ >> ')';
        edif_version_ = '(' >> tok.edif_version_ [PrintStr(*ptb)] >> +tok.int_constant [PrintInt(*ptb)] >> ')';
	
        str_identifier  = tok.identifier [_val = _1]
						| string_	[_val = _1]
						;

		string_         = '"' >> tok.identifier >> '"';

		qi::on_error<qi::fail>
		  (
		   edif_version_
		   , std::cout
		   << val("Error! Expecting ")
		   << _4                               // what failed?
		   << val(" here: \"")
		   << construct<std::string>(_3, _2)   // iterators to error-pos, end
		   << val("\"")
		   << std::endl
		  );
    }

    qi::rule<Iterator, qi::in_state_skipper<Lexer> > start, statements, edif_, edif_version_, number_list_;
    qi::rule<Iterator, std::string(), qi::in_state_skipper<Lexer> > string_;
	qi::rule<Iterator, std::string(), qi::in_state_skipper<Lexer> > str_identifier;

    EdifParseTreeBuilder*  ptb;
};
