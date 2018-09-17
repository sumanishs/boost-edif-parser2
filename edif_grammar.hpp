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

        str_identifier  = tok.identifier [_val = _1] | string_	[_val = _1] ;
		string_         = '"' >> tok.identifier >> '"';
        
        start       = +statements;  
        statements =    '(' 
                        >> tok.edif_ [PrintStr(*ptb)] 
                        >> str_identifier [PrintStr(*ptb)] 
                        >> +edif_statements_
                        >> ')';
        edif_statements_ = edif_version_
                          | edif_level_
                          | keyword_map_
                          | status_statement_ 
                          | external_section_ 
                          | library_section_
                          | design_section_
                          ;        
        
        edif_version_   = '(' >> tok.edif_version_ [PrintStr(*ptb)] >> +tok.int_constant [PrintInt(*ptb)] >> ')';
	    edif_level_     = '(' >> tok.edif_level_ [PrintStr(*ptb)] >> +tok.int_constant [PrintInt(*ptb)] >> ')'; 
        keyword_map_    = '(' >> tok.keyword_map_ [PrintStr(*ptb)] >> '(' >> tok.keyword_level_ [PrintStr(*ptb)] >> +tok.int_constant [PrintInt(*ptb)] >> ')' >> ')';
        status_statement_   = '(' >> tok.status_ [PrintStr(*ptb)] >> written_statement_ >> ')';
        written_statement_  = '(' >> tok.written_ [PrintStr(*ptb)] >> +written_sections_ >> ')';
        written_sections_   = time_stamp_
                             | program_statement_
                             | data_origin_
                             | author_
                             ;
        time_stamp_         = '(' >> tok.time_stamp_ [PrintStr(*ptb)] >> +tok.int_constant [PrintInt(*ptb)] >> ')';
        program_statement_  = '(' >> tok.program_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] >> prog_version_ >> ')';
        prog_version_       = '(' >> tok.prog_version_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] >> ')';
        data_origin_        = '(' >> tok.data_origin_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] >> ')';
        author_             = '(' >> tok.author_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] >> ')'; 

        external_section_   = '(' 
                               >> tok.external_ [PrintStr(*ptb)] 
                               >> str_identifier [PrintStr(*ptb)] 
                               >> +external_section_statements_
                               >> ')'
                               ;
        external_section_statements_ = edif_level_
                                      | technology_section_
                                      | cell_definition_section_  
                                      ;

        technology_section_ = '(' >> tok.technology_ [PrintStr(*ptb)] >> numberDefinition_section_ >> ')';
        numberDefinition_section_   = '(' >> tok.numberDefinition_ [PrintStr(*ptb)] >> ')';     
 
        cell_definition_section_ = '(' >> tok.cell_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] 
                                       >> + cell_def_statements_
                                       >> ')';
        cell_def_statements_    = cell_type_section_
                                 | view_section_
                                 ;    
        cell_type_section_  = '(' >> tok.cellType_ [PrintStr(*ptb)]>> str_identifier [PrintStr(*ptb)] >> ')';
        view_section_   = '(' >> tok.view_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)]
                              >> +view_section_statements_
                              >> ')'
                                ;
        view_section_statements_    = view_type_section_
                                     | interface_section_
                                     | contents_section_
                                     ;
        view_type_section_              = '(' >> tok.viewType_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] >> ')';
        interface_section_              = '(' >> tok.interface_ [PrintStr(*ptb)] >> +interface_section_statements_ >> ')';
        interface_section_statements_   = port_declarations_
                                        | property_declaration_
                                        ;          
        port_declarations_              = '(' >> tok.port_ [PrintStr(*ptb)] >> id_or_rename_ >> direction_section_ >> ')';
        direction_section_              = '(' >> tok.direction_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] >> ')';
        property_declaration_           = '(' >> tok.property_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] >> +property_val_section_ >> ')';
        property_val_section_           = prop_int_val_
                                        | prop_str_val_
                                        | prop_owner_val_
                                        ;                                    
        prop_int_val_   = '(' >> tok.integer_ [PrintStr(*ptb)] >> tok.int_constant [PrintInt(*ptb)] >> ')';
        prop_str_val_   = '(' >> tok.string_  [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] >> ')';  
        prop_owner_val_ = '(' >> tok.owner_   [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] >> ')';

        contents_section_ = '(' >> tok.contents_ [PrintStr(*ptb)] 
                                >> +contents_section_statements_ 
                                >> ')';
        contents_section_statements_ = instance_section_
                                      | net_section_
                                      ;
        instance_section_   = '(' >> tok.instance_ [PrintStr(*ptb)] >> id_or_rename_ >> viewref_section_ >> ')';
        viewref_section_    = '(' >> tok.viewRef_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] >> cellref_section_ >> ')';
        cellref_section_    = '(' >> tok.cellRef_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] >> libraryref_section_ >> ')';
        libraryref_section_ = '(' >> tok.libraryRef_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] >> ')';

        net_section_        = '(' >> tok.net_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] >> connection_section_ >> ')';
        connection_section_ = '(' >> tok.joined_ [PrintStr(*ptb)] >> +port_connections_ >> ')';
        port_connections_   = '(' >> tok.portRef_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] 
                                >> -instanceref_section_
                                >> ')';
        instanceref_section_ = '(' >> tok.instanceRef_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] >> ')';    
                   
        library_section_    = '(' >> tok.library_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)]
                                  >> +library_section_statements_
                                  >> ')'
                                  ;

        library_section_statements_ = edif_level_
                                     | technology_section_
                                     | cell_definition_section_
                                     ;

        design_section_ = '(' >> tok.design_ [PrintStr(*ptb)] >> id_or_rename_
                              >> +design_section_statements_
                              >> ')'
                              ;

        design_section_statements_ = cellref_section_
                                    | property_declaration_
                                    ; 

        rename_section_ = '(' >> tok.rename_ [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] >> str_identifier [PrintStr(*ptb)] >> ')';

        id_or_rename_ = str_identifier [PrintStr(*ptb)]
                       | rename_section_
                       ;

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

    qi::rule<Iterator, qi::in_state_skipper<Lexer> > start, statements, edif_, edif_statements_, edif_version_, edif_level_,
                                                     keyword_map_, status_statement_, written_statement_, written_sections_, time_stamp_, 
                                                     program_statement_, prog_version_, data_origin_, author_, external_section_,
                                                     technology_section_, numberDefinition_section_, external_section_statements_;

    qi::rule<Iterator, qi::in_state_skipper<Lexer> > cell_definition_section_, cell_def_statements_, cell_type_section_,
                                                     view_section_, view_section_statements_, view_type_section_, interface_section_,
                                                     interface_section_statements_, port_declarations_, direction_section_,
                                                     property_declaration_, property_val_section_, prop_int_val_, prop_str_val_, prop_owner_val_,
                                                     contents_section_, contents_section_statements_, instance_section_, net_section_,
                                                     viewref_section_, cellref_section_, libraryref_section_, connection_section_,
                                                     port_connections_, instanceref_section_, library_section_, library_section_statements_,
                                                     design_section_, design_section_statements_, rename_section_, id_or_rename_
                                                     ; 


    qi::rule<Iterator, std::string(), qi::in_state_skipper<Lexer> > string_;
	qi::rule<Iterator, std::string(), qi::in_state_skipper<Lexer> > str_identifier;

    EdifParseTreeBuilder*  ptb;
};
