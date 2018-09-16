#include <boost/spirit/include/qi.hpp>
#include "edif_parse_tree_builder.hpp"

#include <iostream>

namespace qi = boost::spirit::qi;

struct PrintStr {
    void operator()(const std::string& str, qi::unused_type, qi::unused_type ) const{
        //std::cout << str;
        ptb.PrintStr(str);
    }
    PrintStr(EdifParseTreeBuilder& aPtb):ptb(aPtb){ }
    EdifParseTreeBuilder& ptb;
};

struct PrintInt {
    void operator()(const int& i, qi::unused_type, qi::unused_type ) const{
        //std::cout << i;
        ptb.PrintInt(i);
    }
    PrintInt(EdifParseTreeBuilder& aPtb):ptb(aPtb){ }
    EdifParseTreeBuilder& ptb;
};

struct PrintDouble {
    void operator()(const double& d, qi::unused_type, qi::unused_type ) const{
        //std::cout << d;
        ptb.PrintDouble(d);
    }
    PrintDouble(EdifParseTreeBuilder& aPtb):ptb(aPtb){ }
    EdifParseTreeBuilder& ptb;
};
