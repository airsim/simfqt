#ifndef __SIMFQT_CMD_FAREPARSERHELPER_HPP
#define __SIMFQT_CMD_FAREPARSERHELPER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost
#include <boost/spirit/include/qi.hpp>
// StdAir
#include <stdair/command/CmdAbstract.hpp>
// Simfqt
#include <simfqt/SIMFQT_Types.hpp>
#include <simfqt/bom/FareRuleStruct.hpp>

// Forward declarations
namespace stdair {
  class BomRoot;
}

namespace SIMFQT {

  namespace FareParserHelper {
    
    // ///////////////////////////////////////////////////////////////////
    //  Semantic actions
    // ////////////////////////////////////////////////////
    ///////////////
    /** Generic Semantic Action (Actor / Functor) for the Fare Parser. */
    struct ParserSemanticAction {
      /** Actor Constructor. */
      ParserSemanticAction (FareRuleStruct&);
      /** Actor Context. */
      FareRuleStruct& _fareRule;
    };

    /** Store the parsed fare Id. */
    struct storeFareId : public ParserSemanticAction {
      /** Actor Constructor. */
      storeFareId (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (unsigned int,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the parsed origin. */
    struct storeOrigin : public ParserSemanticAction {
      /** Actor Constructor. */
      storeOrigin (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (std::vector<char>,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the parsed destination. */
    struct storeDestination : public ParserSemanticAction {
      /** Actor Constructor. */
      storeDestination (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (std::vector<char>,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };
    
    /** Store the parsed customer trip type. */
    struct storeTripType : public ParserSemanticAction {
      /** Actor Constructor. */
      storeTripType (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (std::vector<char>,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };


     /** Store the parsed start of the date range. */
    struct storeDateRangeStart : public ParserSemanticAction {
      /** Actor Constructor. */
      storeDateRangeStart (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the parsed end of the date range. */
    struct storeDateRangeEnd : public ParserSemanticAction {
      /** Actor Constructor. */
      storeDateRangeEnd (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the parsed start range time. */
    struct storeStartRangeTime : public ParserSemanticAction {
      /** Actor Constructor. */
      storeStartRangeTime (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the parsed end range time. */
    struct storeEndRangeTime : public ParserSemanticAction {
      /** Actor Constructor. */
      storeEndRangeTime (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the parsed customer point_of_sale. */
    struct storePOS : public ParserSemanticAction {
      /** Actor Constructor. */
      storePOS (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (std::vector<char>,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the cabin code. */
    struct storeCabinCode : public ParserSemanticAction {
      /** Actor Constructor. */
      storeCabinCode  (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (char,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the channel distribution. */
    struct storeChannel : public ParserSemanticAction {
      /** Actor Constructor. */
      storeChannel (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (std::vector<char>,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the parsed advance purchase days. */
    struct storeAdvancePurchase : public ParserSemanticAction {
      /** Actor Constructor. */
      storeAdvancePurchase (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (unsigned int,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the parsed saturday night. */
    struct storeSaturdayStay : public ParserSemanticAction {
      /** Actor Constructor. */
      storeSaturdayStay (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (char,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };
    
    /** Store the parsed change fees. */
    struct storeChangeFees : public ParserSemanticAction {
      /** Actor Constructor. */
      storeChangeFees (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (char,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the parsed refundable option */
    struct storeNonRefundable : public ParserSemanticAction {
      /** Actor Constructor. */
      storeNonRefundable (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (char,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };
    
    /** Store the parsed minimum stay. */
    struct storeMinimumStay : public ParserSemanticAction {
      /** Actor Constructor. */
      storeMinimumStay (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (unsigned int,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

     /** Store the parsed fare value. */
    struct storeFare : public ParserSemanticAction {
      /** Actor Constructor. */
      storeFare (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (double,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const; 
    };
    
    /** Store the parsed airline code. */
    struct storeAirlineCode : public ParserSemanticAction {
      /** Actor Constructor. */
      storeAirlineCode (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (std::vector<char>,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the parsed class code. */
    struct storeClass : public ParserSemanticAction {
      /** Actor Constructor. */
      storeClass (FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (std::vector<char>,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const; 
    };
    
    /** Mark the end of the fare-rule parsing. */
    struct doEndFare : public ParserSemanticAction {
      /** Actor Constructor. */
      doEndFare (stdair::BomRoot&, FareRuleStruct&);
      /** Actor Function (functor). */
      void operator() (boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
      /** Actor Specific Context. */
      stdair::BomRoot& _bomRoot;
    };
  
  }
  
  /////////////////////////////////////////////////////////////////////////
  //
  //  Entry class for the file parser
  //
  /////////////////////////////////////////////////////////////////////////
  /** Class wrapping the 
      initialisation and entry point of the parser.
      <br>The seemingly redundancy is used to force the instantiation of
      the actual parser, which is a templatised Boost Spirit grammar.
      Hence, the actual parser is instantiated within that class object
      code. */
  class FareRuleFileParser : public stdair::CmdAbstract {
  public:
    /** Constructor. */
    FareRuleFileParser (stdair::BomRoot& ioBomRoot,
                        const stdair::Filename_T& iFilename);

    /** Parse the input file and generate the fare rules. */
    void generateFareRules ();
      
  private:
    /** Initialise. */
    void init();
      
  private:
    // Attributes
    /** File-name of the CSV-formatted fare input file. */
    stdair::Filename_T _filename;

    /** stdair::BomRoot. */
    stdair::BomRoot& _bomRoot;

    /** Fare-Rule Structure. */
    FareRuleStruct _fareRule;
  };
    
}
#endif // __SIMFQT_CMD_FAREPARSERHELPER_HPP
