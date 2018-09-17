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
    ID_WHITE_SPACE,
    ID_EDIF,
    ID_EDIF_VERSION,
    ID_EDIF_LEVEL,
    ID_KEYWORD_MAP,
    ID_STATUS,
    ID_WRITTEN,
    ID_TIME_STAMP,
    ID_PROGRAM,
    ID_PROG_VERSION,   
    ID_DATA_ORIGIN,
    ID_AUTHOR, 
    ID_EXTERNAL,
    ID_TECHNOLOGY,
    ID_NUMBER_DEFINITION,
    ID_KEYWORD_LEVEL,   
    ID_CELL,
    ID_CELLTYPE,
    ID_VIEW,
    ID_VIEWTYPE,
    ID_INTERFACE,
    ID_PORT,
    ID_STRING,
    ID_INTEGER,
    ID_PROPERTY,
    ID_DIRECTION,
    ID_CONTENTSTAG,
    ID_INSTANCE,
    ID_VIEWREF,
    ID_CELLREF,
    ID_LIBRARYREF,
    ID_NET,
    ID_JOINED,
    ID_PORTREF,
    ID_INSTANCEREF, 
};

template <typename Lexer>
struct edif_tokens : lex::lexer<Lexer>
{
    edif_tokens()
    {
        identifier      = "[a-zA-Z_][a-zA-Z_0-9\\\.]*";
        int_constant    = "[0-9][0-9]*";
        double_constant = "[0-9]+\\\.[0-9]+";
        double_exp_constant = "[0-9]+e-[0-9]+";
        edif_           = "edif";
        edif_version_   = "edifVersion";
        edif_level_     = "edifLevel";
        keyword_map_    = "keywordMap";
        keyword_level_  = "keywordLevel";
        status_         = "status";
        written_        = "written";
        time_stamp_     = "timeStamp";
        program_        = "program";
        prog_version_   = "version";
        data_origin_    = "dataOrigin";
        author_         = "author";
        external_       = "external";
        technology_     = "technology";
        numberDefinition_   = "numberDefinition";
        cell_           = "cell";
        cellType_       = "cellType";
        view_           = "view";
        viewType_       = "viewType";
        interface_      = "interface";
        port_           = "port";
        direction_      = "direction";
        integer_        = "integer";
        string_         = "string";
        property_       = "property";
        contentstag_    = "contents";
        instance_       = "instance";
        viewRef_        = "viewRef";
        cellRef_        = "cellRef";
        libraryRef_     = "libraryRef";
        net_            = "net";
        joined_         = "joined";
        portRef_        = "portRef";
        instanceRef_    = "instanceRef";

        white_space     = "[ \\t]+";

        this->self = lex::token_def<>('(') | ')' | '{' | '}' | '=' | ';' | ':' | '"' | '"';

        this->self.add
            (int_constant, ID_INT_CONSTANT)
            (double_constant, ID_DOUBLE_CONSTANT)
            (double_exp_constant, ID_DOUBLE_EXP_CONSTANT)
            (edif_, ID_EDIF)
            (edif_version_, ID_EDIF_VERSION)
            (edif_level_, ID_EDIF_LEVEL)
            (keyword_map_, ID_KEYWORD_MAP)
            (keyword_level_, ID_KEYWORD_LEVEL)
            (status_, ID_STATUS)
            (written_, ID_WRITTEN)
            (time_stamp_, ID_TIME_STAMP)
            (program_, ID_PROGRAM)
            (prog_version_, ID_PROG_VERSION)    
            (data_origin_,  ID_DATA_ORIGIN)
            (author_, ID_AUTHOR)
            (external_, ID_EXTERNAL)
            (technology_, ID_TECHNOLOGY)
            (numberDefinition_, ID_NUMBER_DEFINITION)
            (cell_, ID_CELL)
            (cellType_, ID_CELLTYPE)
            (view_, ID_VIEW)
            (viewType_, ID_VIEWTYPE)
            (interface_, ID_INTERFACE)
            (port_, ID_PORT)
            (direction_, ID_DIRECTION)
            (integer_, ID_INTEGER)
            (string_, ID_STRING)
            (property_, ID_PROPERTY)
            (identifier, ID_IDENTIFIER)
            (contentstag_, ID_CONTENTSTAG)
            (instance_, ID_INSTANCE)
            (viewRef_, ID_VIEWREF)
            (cellRef_, ID_CELLREF)
            (libraryRef_, ID_LIBRARYREF)
            (net_, ID_NET)
            (joined_, ID_JOINED)
            (portRef_, ID_PORTREF)
            (instanceRef_, ID_INSTANCEREF)
        ;

        this-> self += white_space [lex::_pass = lex::pass_flags::pass_ignore]; // Need to tokenize but space not
        white_space.id(ID_WHITE_SPACE);                                         // required in as token in parser
                                                                                // grammar                                                                            
        //this->self("WS")   
        //    =   lex::token_def<>("[\\n]+") 
        //    |   "\\/\\*[^*]*\\*+([^/*][^*]*\\*+)*\\/"
        //    |   "#[^\\n]*"
        //    ;
        this->self("WS") 
            =   lex::token_def<>("[\\n]+") 
            |   "\\/\\*[^*]*\\*+([^/*][^*]*\\*+)*\\/"
            |   "#[^\\n]*"
            ;
    }

    lex::token_def<std::string> identifier,  double_exp_constant ;
    lex::token_def<unsigned int> int_constant;
    lex::token_def<double> double_constant;
    
    lex::token_def<std::string> edif_, edif_version_, edif_level_, keyword_map_, keyword_level_, status_, written_,
                                time_stamp_, program_, prog_version_, data_origin_, author_, external_, technology_,
                                numberDefinition_, cell_, cellType_, view_, viewType_, interface_, port_, direction_,
                                integer_, string_, property_, contentstag_, instance_, viewRef_, cellRef_, libraryRef_,
                                net_, joined_, portRef_, instanceRef_
                                ;

    lex::token_def<lex::omit> white_space;
};
