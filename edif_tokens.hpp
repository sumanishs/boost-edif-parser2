/**********************************************************************/
/* Author: Sumanish <sumanish.cse.jgec@gmail.com>                     */
/* Modified By: Sumanish <sumanish.cse.jgec@gmail.com>                */
/*                                                                    */  
/* This source code can be downloaded, use, modify, distribute        */
/* freely with this headed intact. Please don't delete this header.   */
/**********************************************************************/ 
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
    ID_STRING_CONSTANT,    
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
    ID_CONTENTS,
    ID_INSTANCE,
    ID_VIEWREF,
    ID_CELLREF,
    ID_LIBRARYREF,
    ID_NET,
    ID_JOINED,
    ID_PORTREF,
    ID_INSTANCEREF, 
    ID_LIBRARY,
    ID_DESIGN,
    ID_OWNER,
    ID_RENAME,
    ID_SCALE,
    ID_UNIT,
    ID_COMMENT,
    ID_ARRAY,
    ID_BOOLEAN,
    ID_MEMBER,
    
    // Vivado type token ids
    ID_EDIF_VERSION_X,      
    ID_EDIF_LEVEL_X,        
    ID_KEYWORD_MAP_X,       
    ID_KEYWORD_LEVEL_X,     
    ID_TIME_STAMP_X,        
    ID_DATA_ORIGIN_X,       
    ID_NUMBER_DEFINITION_X, 
    ID_CELLTYPE_X,          
    ID_VIEWTYPE_X,          
    ID_VIEWREF_X,           
    ID_CELLREF_X,           
    ID_LIBRARYREF_X,        
    ID_PORTREF_X,           
    ID_INSTANCEREF_X,       
    ID_LIBRARY_X,

};

template <typename Lexer>
struct edif_tokens : lex::lexer<Lexer>
{
    edif_tokens()
    {
        identifier      = "[a-zA-Z_&][a-zA-Z_0-9\\\.\\\-\\\[\\\]$]*";
        string_constant = "[\\\"][a-zA-Z0-9_\\\.\\\-\\\[\\\]$ :'\\\<\\\>\\\{\\\}\\\*=\\\/\\\\,()]*[\\\"]";        
        int_constant    = "[0-9\\\-][0-9]*";
        double_constant = "[0-9]+\\\.[0-9]+";
        double_exp_constant = "[0-9]+e-[0-9]+";
        edif_           = "edif";
        edif_version_   = "edifVersion";
        edif_level_     = "edifLevel";
        keyword_map_    = "keywordMap";
        keyword_level_  = "keywordLevel";
        time_stamp_     = "timeStamp";
        data_origin_    = "dataOrigin";
        numberDefinition_   = "numberDefinition";
        cellType_       = "cellType";
        viewType_       = "viewType";
        viewRef_        = "viewRef";
        cellRef_        = "cellRef";
        libraryRef_     = "libraryRef";
        portRef_        = "portRef";
        instanceRef_    = "instanceRef";
        status_         = "status";
        written_        = "written";
        program_        = "program";
        prog_version_   = "version";
        author_         = "author";
        external_       = "external";
        technology_     = "technology";
        cell_           = "cell";
        view_           = "view";
        interface_      = "interface";
        port_           = "port";
        direction_      = "direction";
        integer_        = "integer";
        string_         = "string";
        property_       = "property";
        contents_       = "contents";
        instance_       = "instance";
        net_            = "net";
        joined_         = "joined";
        library_        = "library";
        design_         = "design";
        owner_          = "owner";
        rename_         = "rename";
        scale_          = "scale";
        unit_           = "unit";
        comment_        = "comment";
        array_          = "array";
        boolean_        = "boolean";
        member_         = "member";
        // Vivado tokens are little different. This is not good.
        edif_version_x_ = "edifversion";
        edif_level_x_   = "ediflevel";
        keyword_map_x_  = "keywordmap";
        keyword_level_x_= "keywordlevel";
        time_stamp_x_   = "timestamp"; 
        data_origin_x_  = "dataorigin";
        numberDefinition_x_ = "numberdefinition";
        cellType_x_     = "celltype";
        viewType_x_     = "viewtype";
        viewRef_x_      = "viewref";
        cellRef_x_      = "cellref";
        libraryRef_x_   = "libraryref";
        portRef_x_      = "portref";
        instanceRef_x_  = "instanceref";
        library_x_      = "Library";
        

        white_space     = "[ \\t]+";

        this->self = lex::token_def<>('(') | ')' | '{' | '}' | '=' | ';' | ':' | '"' | '"' | ',';

        this->self.add
            (int_constant, ID_INT_CONSTANT)
            (double_constant, ID_DOUBLE_CONSTANT)
            (double_exp_constant, ID_DOUBLE_EXP_CONSTANT)
            (string_constant, ID_STRING_CONSTANT)
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
            (contents_, ID_CONTENTS)
            (instance_, ID_INSTANCE)
            (viewRef_, ID_VIEWREF)
            (cellRef_, ID_CELLREF)
            (libraryRef_, ID_LIBRARYREF)
            (net_, ID_NET)
            (joined_, ID_JOINED)
            (portRef_, ID_PORTREF)
            (instanceRef_, ID_INSTANCEREF)
            (library_, ID_LIBRARY)
            (design_, ID_DESIGN)
            (owner_, ID_OWNER)
            (rename_, ID_RENAME)
            (scale_, ID_SCALE)
            (unit_, ID_UNIT)
            (comment_, ID_COMMENT)
            (array_, ID_ARRAY)
            (boolean_, ID_BOOLEAN)
            (member_, ID_MEMBER)
            /****Vivado type edif tokens****/
            (edif_version_x_,       ID_EDIF_VERSION_X       ) 
            (edif_level_x_,         ID_EDIF_LEVEL_X         )   
            (keyword_map_x_,        ID_KEYWORD_MAP_X        )  
            (keyword_level_x_,      ID_KEYWORD_LEVEL_X      )
            (time_stamp_x_,         ID_TIME_STAMP_X         )   
            (data_origin_x_,        ID_DATA_ORIGIN_X        )  
            (numberDefinition_x_,   ID_NUMBER_DEFINITION_X  )
            (cellType_x_,           ID_CELLTYPE_X           )     
            (viewType_x_,           ID_VIEWTYPE_X           )     
            (viewRef_x_,            ID_VIEWREF_X            )      
            (cellRef_x_,            ID_CELLREF_X            )      
            (libraryRef_x_,         ID_LIBRARYREF_X         )   
            (portRef_x_,            ID_PORTREF_X            )      
            (instanceRef_x_,        ID_INSTANCEREF_X        )  
            (library_x_,            ID_LIBRARY_X            )
            /*******************************/

            (identifier, ID_IDENTIFIER)
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

    lex::token_def<std::string> identifier,  double_exp_constant , string_constant;
    lex::token_def<int> int_constant;
    lex::token_def<double> double_constant;
    
    lex::token_def<std::string> edif_, edif_version_, edif_level_, keyword_map_, keyword_level_, status_, written_,
                                time_stamp_, program_, prog_version_, data_origin_, author_, external_, technology_,
                                numberDefinition_, cell_, cellType_, view_, viewType_, interface_, port_, direction_,
                                integer_, string_, property_, contents_, instance_, viewRef_, cellRef_, libraryRef_,
                                net_, joined_, portRef_, instanceRef_, library_, library_x_, design_, owner_, rename_, scale_,
                                unit_, comment_, array_, boolean_, member_;

    lex::token_def<std::string> edif_version_x_, edif_level_x_, keyword_map_x_, keyword_level_x_, time_stamp_x_, 
                                data_origin_x_, numberDefinition_x_, cellType_x_, viewType_x_, viewRef_x_,        
                                cellRef_x_, libraryRef_x_, portRef_x_, instanceRef_x_ ;

    lex::token_def<lex::omit> white_space;
};
