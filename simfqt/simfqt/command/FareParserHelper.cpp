 // //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <vector>
#include <fstream>
// StdAir
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/service/Logger.hpp>
// SIMFQT
#include <simfqt/command/FareParserHelper.hpp>
#include <simfqt/command/FareRuleGenerator.hpp>

namespace SIMFQT {

  namespace FareParserHelper {
      
    // //////////////////////////////////////////////////////////////////
    //  Semantic actions
    // //////////////////////////////////////////////////////////////////

    ParserSemanticAction::
    ParserSemanticAction (FareRuleStruct& ioFareRule)
      : _fareRule (ioFareRule) {
    }      
   
    // //////////////////////////////////////////////////////////////////
    storeFareId::
    storeFareId (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeFareId::operator() (unsigned int iFareId,
                                  boost::spirit::qi::unused_type,
                                  boost::spirit::qi::unused_type) const {
      _fareRule._fareId = iFareId;

       STDAIR_LOG_DEBUG ( "Fare Id: " << _fareRule._fareId);

       _fareRule._nbOfAirlines = 0;
       _fareRule._airlineCode = "";
       _fareRule._classCode = "";
       _fareRule._airlineCodeList.clear();
       _fareRule._classCodeList.clear(); 
    }
    
    // //////////////////////////////////////////////////////////////////
    storeOrigin ::
    storeOrigin (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeOrigin::operator() (std::vector<char> iChar,
                                  boost::spirit::qi::unused_type,
                                  boost::spirit::qi::unused_type) const {
       stdair::AirportCode_T lOrigin (iChar.begin(), iChar.end());
       STDAIR_LOG_DEBUG ( "Origin: " << lOrigin);
       _fareRule._origin = lOrigin;
    }

    // //////////////////////////////////////////////////////////////////
    storeDestination ::
    storeDestination (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeDestination::operator() (std::vector<char> iChar,
                                       boost::spirit::qi::unused_type,
                                       boost::spirit::qi::unused_type) const {
       stdair::AirportCode_T lDestination (iChar.begin(), iChar.end());
       STDAIR_LOG_DEBUG ( "Destination: " << lDestination);
       _fareRule._destination = lDestination;
    }
    
    // //////////////////////////////////////////////////////////////////
    storeDateRangeStart::
    storeDateRangeStart (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeDateRangeStart::operator() (boost::spirit::qi::unused_type,
                                          boost::spirit::qi::unused_type,
                                          boost::spirit::qi::unused_type) const {
      _fareRule._dateRangeStart = _fareRule.getDate();
      STDAIR_LOG_DEBUG ("Date Range Start: "<< _fareRule._dateRangeStart);
    }

    // //////////////////////////////////////////////////////////////////
    storeDateRangeEnd::
    storeDateRangeEnd(FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeDateRangeEnd::operator() (boost::spirit::qi::unused_type,
                                        boost::spirit::qi::unused_type,
                                        boost::spirit::qi::unused_type) const {
       _fareRule._dateRangeEnd = _fareRule.getDate();
       STDAIR_LOG_DEBUG ("Date Range End: " << _fareRule._dateRangeEnd);
    }

    // //////////////////////////////////////////////////////////////////
    storeStartRangeTime::
    storeStartRangeTime (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeStartRangeTime::operator() (boost::spirit::qi::unused_type,
                                          boost::spirit::qi::unused_type,
                                          boost::spirit::qi::unused_type) const {
      _fareRule._timeRangeStart = _fareRule.getTime();
      STDAIR_LOG_DEBUG ("Time Range Start: " << _fareRule._timeRangeStart);
      // Reset the number of seconds
      _fareRule._itSeconds = 0;
    }

    // //////////////////////////////////////////////////////////////////
    storeEndRangeTime::
    storeEndRangeTime (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeEndRangeTime::operator() (boost::spirit::qi::unused_type,
                                        boost::spirit::qi::unused_type,
                                        boost::spirit::qi::unused_type) const {
      _fareRule._timeRangeEnd = _fareRule.getTime();
      STDAIR_LOG_DEBUG ("Time Range End: " << _fareRule._timeRangeEnd);
      // Reset the number of seconds
      _fareRule._itSeconds = 0;
    }
   
    // //////////////////////////////////////////////////////////////////
    storePOS ::
    storePOS (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storePOS::operator() (std::vector<char> iChar,
                               boost::spirit::qi::unused_type,
                               boost::spirit::qi::unused_type) const {
      stdair::AirlineCode_T lPOS (iChar.begin(), iChar.end());
      _fareRule._pos = lPOS;
     STDAIR_LOG_DEBUG ("POS: " << _fareRule._pos);
    }

    // //////////////////////////////////////////////////////////////////
    storeChannel ::
    storeChannel (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeChannel::operator() (std::vector<char> iChar,
                                   boost::spirit::qi::unused_type,
                                   boost::spirit::qi::unused_type) const {
      stdair::ChannelLabel_T lChannel (iChar.begin(), iChar.end());
      if (lChannel != "IN" && lChannel != "IF"
          && lChannel != "DN" && lChannel != "DF") {
        STDAIR_LOG_DEBUG ("Invalid channel " << lChannel);
      }
      _fareRule._channel = lChannel;
      STDAIR_LOG_DEBUG ("Channel: " << _fareRule._channel);
    }
    
    // //////////////////////////////////////////////////////////////////
    storeAdvancePurchase ::
    storeAdvancePurchase (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeAdvancePurchase::operator() (unsigned int iAdancePurchase,
                                           boost::spirit::qi::unused_type,
                                           boost::spirit::qi::unused_type) const {
      _fareRule._advancePurchase = iAdancePurchase;
      STDAIR_LOG_DEBUG ( "Advance Purchase: " << _fareRule._advancePurchase);
    }
    
    // //////////////////////////////////////////////////////////////////
    storeSaturdayStay ::
    storeSaturdayStay (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeSaturdayStay::operator() (char iSaturdayStay,
                                        boost::spirit::qi::unused_type,
                                        boost::spirit::qi::unused_type) const {
      bool lBool = false;
      if (iSaturdayStay == 'T') {
        lBool = true;
      } else {
        if (iSaturdayStay != 'F') {
          STDAIR_LOG_DEBUG ("Invalid saturdayStay char " << iSaturdayStay);
        }
      }
      stdair::SaturdayStay_T lSaturdayStay (lBool);
      _fareRule._saturdayStay = lSaturdayStay;
      STDAIR_LOG_DEBUG ("Saturday Stay: " << _fareRule._saturdayStay);
    }

    // //////////////////////////////////////////////////////////////////
    storeChangeFees ::
    storeChangeFees (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeChangeFees::operator() (char iChangefees,
                                      boost::spirit::qi::unused_type,
                                      boost::spirit::qi::unused_type) const {
      
      bool lBool = false;
      if (iChangefees == 'T') {
        lBool = true;
      } else {
        if (iChangefees != 'F') {
          STDAIR_LOG_DEBUG ("Invalid change fees char " << iChangefees);
        }
      }
      stdair::ChangeFees_T lChangefees (lBool);
      _fareRule._changeFees = lChangefees;
      STDAIR_LOG_DEBUG ("Change fees: " << _fareRule._changeFees);
    }
    
    // //////////////////////////////////////////////////////////////////
    storeNonRefundable ::
    storeNonRefundable (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeNonRefundable::operator() (char iNonRefundable,
                                         boost::spirit::qi::unused_type,
                                         boost::spirit::qi::unused_type) const {
       bool lBool = false;
       if (iNonRefundable == 'T') {
         lBool = true;
       } else {
         if (iNonRefundable != 'F') {
           STDAIR_LOG_DEBUG ("Invalid non refundable char " << iNonRefundable);
         }
       }
       stdair::NonRefundable_T lNonRefundable (lBool);
       _fareRule._nonRefundable = lNonRefundable;
       STDAIR_LOG_DEBUG ("Non refundable: " << _fareRule._nonRefundable);
    }
    
    // //////////////////////////////////////////////////////////////////
    storeMinimumStay ::
    storeMinimumStay (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeMinimumStay::operator() (unsigned int iMinStay,
                                       boost::spirit::qi::unused_type,
                                       boost::spirit::qi::unused_type) const {
      _fareRule._minimumStay = iMinStay;
      STDAIR_LOG_DEBUG ("Minimum Stay: " << _fareRule._minimumStay );
    }

    // //////////////////////////////////////////////////////////////////
    storeFare ::
    storeFare (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeFare::operator() (double iFare,
                                boost::spirit::qi::unused_type,
                                boost::spirit::qi::unused_type) const {
      _fareRule._fare = iFare;
      STDAIR_LOG_DEBUG ("Fare: " << _fareRule._fare);
    }

    // //////////////////////////////////////////////////////////////////
    storeAirlineCode ::
    storeAirlineCode (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeAirlineCode::operator() (std::vector<char> iChar,
                                       boost::spirit::qi::unused_type,
                                       boost::spirit::qi::unused_type) const {

      bool lAlreadyInTheList = false;
      stdair::AirlineCode_T lAirlineCode (iChar.begin(), iChar.end());
      // Update the airline code
      _fareRule._airlineCode = lAirlineCode;
      // Test if the FareRule Struct stands for interline products
      if (_fareRule._airlineCodeList.size() > 0) {
        // Update the number of airlines if necessary
        std::vector<stdair::AirlineCode_T>::iterator Airline_iterator;
        for (Airline_iterator = _fareRule._airlineCodeList.begin();
             Airline_iterator != _fareRule._airlineCodeList.end();
             ++Airline_iterator) {
          stdair::AirlineCode_T lPreviousAirlineCode =
            *Airline_iterator;
          if (lPreviousAirlineCode == lAirlineCode) {
            lAlreadyInTheList = true;
            /*STDAIR_LOG_DEBUG ("Airline Code Already Existing: "
              << lAirlineCode);*/
          }
        }
        if (lAlreadyInTheList == false) {
          /*STDAIR_LOG_DEBUG ("New Airline Code: "
          << lAirlineCode);*/
          _fareRule._airlineCodeList.push_back(lAirlineCode);
        }
      } else {
        /*STDAIR_LOG_DEBUG ("First Airline Code: "
          << lAirlineCode);*/
        _fareRule._airlineCodeList.push_back (lAirlineCode);
      }
      STDAIR_LOG_DEBUG ( "Airline code: " << lAirlineCode);
    }

    // //////////////////////////////////////////////////////////////////
    storeClass ::
    storeClass (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeClass::operator() (char iChar,
                                 boost::spirit::qi::unused_type,
                                 boost::spirit::qi::unused_type) const {
      std::ostringstream ostr;
      ostr << iChar;
      std::string classCodeStr = ostr.str();
      const stdair::ClassCode_T lClassCode (classCodeStr);
      _fareRule._classCodeList.push_back(lClassCode);
      // Insertion of this class Code in the whole classCode name
      std::ostringstream ostrr;
      ostrr << _fareRule._classCode << classCodeStr;
      _fareRule._classCode = ostrr.str();
      STDAIR_LOG_DEBUG ("Class Code: " << lClassCode);
        
    }
    
    // //////////////////////////////////////////////////////////////////
    doEndFare::
    doEndFare (stdair::BomRoot& ioBomRoot,
               FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule),
        _bomRoot (ioBomRoot) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void doEndFare::operator() (boost::spirit::qi::unused_type,
                                boost::spirit::qi::unused_type,
                                boost::spirit::qi::unused_type) const {

      // Generation of the fare rule object.
      STDAIR_LOG_DEBUG ("Do End");
      FareRuleGenerator::createFareRule (_bomRoot, _fareRule);
    }  

    // ///////////////////////////////////////////////////////////////////
    //
    //  Utility Parsers
    //
    // ///////////////////////////////////////////////////////////////////
    /** 1-digit-integer parser */
    int1_p_t int1_p;
    
    /** 2-digit-integer parser */
    uint2_p_t uint2_p;

    /** 4-digit-integer parser */
    uint4_p_t uint4_p;
    
    /** Up-to-4-digit-integer parser */
    uint1_4_p_t uint1_4_p;

    // //////////////////////////////////////////////////////////////////
    //  (Boost Spirit) Grammar Definition
    // //////////////////////////////////////////////////////////////////

    // //////////////////////////////////////////////////////////////////
    FareRuleParser::FareRuleParser (stdair::BomRoot& ioBomRoot,
                                    FareRuleStruct& iofareRule) :
      FareRuleParser::base_type(start),
      _bomRoot(ioBomRoot),
      _fareRule(iofareRule) {

      start = *(comments | fare_rule)
        ;

      comments = (boost::spirit::qi::lexeme[
                                            boost::spirit::qi::repeat(2)[boost::spirit::ascii::char_('/')]
                                            >> +(boost::spirit::ascii::char_ - boost::spirit::qi::eol)
                                            >> boost::spirit::qi::eol
                                            ]
                  | boost::spirit::qi::lexeme[
                                              boost::spirit::ascii::char_('/') >>
                                              boost::spirit::ascii::char_('*') >>
                                              +(boost::spirit::ascii::char_ - boost::spirit::ascii::char_('*')) >>
                                              boost::spirit::ascii::char_('*') >> boost::spirit::ascii::char_('/')
                                              ])
        ;

      fare_rule = fare_key
        >> +( ';' >> segment )
        >> fare_rule_end[doEndFare(_bomRoot, _fareRule)]
        ;

      fare_rule_end = boost::spirit::ascii::char_(';')
        ;

      fare_key = fare_id
        >> ';' >>  origin >> ';' >> destination
        >> ';' >> dateRangeStart >> ';' >> dateRangeEnd
        >> ';' >> timeRangeStart >> ';' >> timeRangeEnd
        >> ';' >> position
        >> ';' >> channel
        >> ';' >> advancePurchase
        >> ';' >> saturdayStay
        >> ';' >> changeFees
        >> ';' >> nonRefundable
        >> ';' >> minimumStay
        >> ';' >> fare
            ;

      fare_id = uint1_4_p[storeFareId(_fareRule)]
        ;

      origin = boost::spirit::qi::repeat(3)[boost::spirit::ascii::char_("A-Z")][storeOrigin(_fareRule)]
        ;
      
      destination =  boost::spirit::qi::repeat(3)[boost::spirit::ascii::char_("A-Z")][storeDestination(_fareRule)]
        ;
      
      dateRangeStart = date[storeDateRangeStart(_fareRule)]
        ;

      dateRangeEnd = date[storeDateRangeEnd(_fareRule)]
        ;
      
      date =  boost::spirit::qi::lexeme[
                                        uint4_p[boost::phoenix::ref(_fareRule._itYear) = boost::spirit::qi::labels::_1]
                                        >> '-'
                                        >> uint2_p[boost::phoenix::ref(_fareRule._itMonth) = boost::spirit::qi::labels::_1]
                                        >> '-'
                                        >> uint2_p[boost::phoenix::ref(_fareRule._itDay) = boost::spirit::qi::labels::_1]
                                        ]
        ;

      timeRangeStart = time[storeStartRangeTime(_fareRule)]
        ;
      
      timeRangeEnd = time[storeEndRangeTime(_fareRule)]
        ;

      time = boost::spirit::qi::lexeme[
                                       uint2_p[boost::phoenix::ref(_fareRule._itHours) = boost::spirit::qi::labels::_1]
                                       >> ':'
                                       >> uint2_p[boost::phoenix::ref(_fareRule._itMinutes) = boost::spirit::qi::labels::_1]
                                       >> !(':' >> (uint2_p)[boost::phoenix::ref(_fareRule._itSeconds) = boost::spirit::qi::labels::_1])
                                       ]
        ;

      position = boost::spirit::qi::repeat(3)[boost::spirit::ascii::char_("A-Z")][storePOS(_fareRule)]
        ;
      

      channel = boost::spirit::qi::repeat(2)[boost::spirit::ascii::char_("A-Z")][storeChannel(_fareRule)]
        ;
    
      advancePurchase = uint1_4_p[storeAdvancePurchase(_fareRule)]
        ;

      saturdayStay = boost::spirit::ascii::char_("A-Z")[storeSaturdayStay(_fareRule)]
        ;

      changeFees = boost::spirit::ascii::char_("A-Z")[storeChangeFees(_fareRule)] 
        ;

      nonRefundable = boost::spirit::ascii::char_("A-Z")[storeNonRefundable(_fareRule)]
        ;
      
      minimumStay = uint1_4_p[storeMinimumStay(_fareRule)]
        ;

      fare = boost::spirit::qi::double_[storeFare(_fareRule)]
        ;
      
      segment = boost::spirit::qi::repeat(2)[boost::spirit::ascii::char_("A-Z")][storeAirlineCode(_fareRule)]
        >> ';'
        >> boost::spirit::ascii::char_("A-Z")[storeClass(_fareRule)]
        ;

      //BOOST_SPIRIT_DEBUG_NODE (FareRuleParser);
      BOOST_SPIRIT_DEBUG_NODE (start);
      BOOST_SPIRIT_DEBUG_NODE (comments);
      BOOST_SPIRIT_DEBUG_NODE (fare_rule);
      BOOST_SPIRIT_DEBUG_NODE (fare_rule_end);
      BOOST_SPIRIT_DEBUG_NODE (fare_key);
      BOOST_SPIRIT_DEBUG_NODE (fare_id);
      BOOST_SPIRIT_DEBUG_NODE (origin);
      BOOST_SPIRIT_DEBUG_NODE (destination);
      BOOST_SPIRIT_DEBUG_NODE (dateRangeStart);
      BOOST_SPIRIT_DEBUG_NODE (dateRangeEnd);
      BOOST_SPIRIT_DEBUG_NODE (date);
      BOOST_SPIRIT_DEBUG_NODE (timeRangeStart);
      BOOST_SPIRIT_DEBUG_NODE (timeRangeEnd);
      BOOST_SPIRIT_DEBUG_NODE (time);
      BOOST_SPIRIT_DEBUG_NODE (position);
      BOOST_SPIRIT_DEBUG_NODE (channel);
      BOOST_SPIRIT_DEBUG_NODE (advancePurchase);
      BOOST_SPIRIT_DEBUG_NODE (saturdayStay);
      BOOST_SPIRIT_DEBUG_NODE (changeFees);
      BOOST_SPIRIT_DEBUG_NODE (nonRefundable);
      BOOST_SPIRIT_DEBUG_NODE (minimumStay);
      BOOST_SPIRIT_DEBUG_NODE (fare);
      BOOST_SPIRIT_DEBUG_NODE (segment);
    }

  }

  /////////////////////////////////////////////////////////////////////////
  //
  //  Entry class for the file parser
  //
  /////////////////////////////////////////////////////////////////////////
    
  // //////////////////////////////////////////////////////////////////////
  FareRuleFileParser::
  FareRuleFileParser (stdair::BomRoot& ioBomRoot,
                      const stdair::Filename_T& iFilename)
    : _filename (iFilename), _bomRoot (ioBomRoot) {
    init();
  }

  // //////////////////////////////////////////////////////////////////////
  void FareRuleFileParser::init() {
    // Check that the file exists and is readable
    const bool doesExistAndIsReadable =
      stdair::BasFileMgr::doesExistAndIsReadable (_filename);

    if (doesExistAndIsReadable == false) {
      STDAIR_LOG_ERROR ("The fare schedule file " << _filename
                        << " does not exist or can not be  read.");
      
      throw FareInputFileNotFoundException ("The fare file " + _filename + " does not exist or can not be read");
    }
  }
    
  // //////////////////////////////////////////////////////////////////////
  bool FareRuleFileParser::generateFareRules () {
      
    STDAIR_LOG_DEBUG ("Parsing fare input file: " << _filename);

    // File to be parsed
    const std::string* lFileName = &_filename;
    const char *lChar = (*lFileName).c_str();
    std::ifstream fileToBeParsed(lChar, std::ios_base::in);

    // Check the filename exists and can be open
    if (fileToBeParsed == false) {
      STDAIR_LOG_ERROR ("The fare file " << _filename << " can not be open."
                          << std::endl);

      throw FareInputFileNotFoundException ("The file " + _filename + " does not exist or can not be read");
    }
    
    // Create an input iterator
    base_iterator_t inputBegin (fileToBeParsed);
    
    // Convert input iterator to an iterator usable by spirit parser  
    iterator_t start (boost::spirit::make_default_multi_pass (inputBegin));
    iterator_t end;

    // Initialise the parser (grammar) with the helper/staging structure.
    FareParserHelper::FareRuleParser lFPParser(_bomRoot, _fareRule);
      
    // Launch the parsing of the file and, thanks to the doEndFare
    // call-back structure, the building of the whole BomRoot BOM

    const bool hasParsingBeenSuccesful = 
       boost::spirit::qi::phrase_parse(start, end, lFPParser, boost::spirit::ascii::space);
      
    if (hasParsingBeenSuccesful == false) {
      // TODO: decide whether to throw an exceqption
      STDAIR_LOG_ERROR ("Parsing of fare input file: " << _filename
                        << " failed");
        
    }
    if  (start != end) {
      // TODO: decide whether to throw an exception
      STDAIR_LOG_ERROR ("Parsing of fare input file: " << _filename
                        << " failed");
    }
    if (hasParsingBeenSuccesful == true && start == end) {
      STDAIR_LOG_DEBUG ("Parsing of fare input file: " << _filename
      << " succeeded");
    }
    return hasParsingBeenSuccesful;
  }
    
}
