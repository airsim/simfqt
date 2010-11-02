 // //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <vector>
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
    void storeFareId::operator() (unsigned int iFareId) const {
       _fareRule._fareId = iFareId;

       //STDAIR_LOG_DEBUG ( "Fare Id: " << _fareRule._fareId);

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
    void storeOrigin::operator() (iterator_t iStr,
                                  iterator_t iStrEnd) const {
       stdair::AirportCode_T lOrigin (iStr, iStrEnd);
       //STDAIR_LOG_DEBUG ( "Origin: " << lOrigin);
       _fareRule._origin = lOrigin;
    }

    // //////////////////////////////////////////////////////////////////
    storeDestination ::
    storeDestination (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeDestination::operator() (iterator_t iStr,
                                       iterator_t iStrEnd) const {
       stdair::AirportCode_T lDestination (iStr, iStrEnd);
       //STDAIR_LOG_DEBUG ( "Destination: " << lDestination);
       _fareRule._destination = lDestination;
    }
    
    // //////////////////////////////////////////////////////////////////
    storeDateRangeStart::
    storeDateRangeStart (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeDateRangeStart::operator() (iterator_t iStr,
                                          iterator_t iStrEnd) const {
      _fareRule._dateRangeStart = _fareRule.getDate();
      //STDAIR_LOG_DEBUG ("Date Range Start: "<< _fareRule._dateRangeStart);
    }

    // //////////////////////////////////////////////////////////////////
    storeDateRangeEnd::
    storeDateRangeEnd(FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeDateRangeEnd::operator() (iterator_t iStr,
                                        iterator_t iStrEnd) const {
       _fareRule._dateRangeEnd = _fareRule.getDate();
       //STDAIR_LOG_DEBUG ("Date Range End: " << _fareRule._dateRangeEnd);
    }

    // //////////////////////////////////////////////////////////////////
    storeStartRangeTime::
    storeStartRangeTime (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeStartRangeTime::operator() (iterator_t iStr,
                                          iterator_t iStrEnd) const {
      _fareRule._timeRangeStart = _fareRule.getTime();
      //STDAIR_LOG_DEBUG ("Time Range Start: " << _fareRule._timeRangeStart);
      // Reset the number of seconds
      _fareRule._itSeconds = 0;
    }

    // //////////////////////////////////////////////////////////////////
    storeEndRangeTime::
    storeEndRangeTime (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeEndRangeTime::operator() (iterator_t iStr,
                                        iterator_t iStrEnd) const {
      _fareRule._timeRangeEnd = _fareRule.getTime();
      // STDAIR_LOG_DEBUG ("Time Range End: " << _fareRule._timeRangeEnd);
      // Reset the number of seconds
      _fareRule._itSeconds = 0;
    }
   
    // //////////////////////////////////////////////////////////////////
    storePOS ::
    storePOS (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storePOS::operator() (iterator_t iStr,
                                    iterator_t iStrEnd) const {
      stdair::AirlineCode_T lPOS (iStr, iStrEnd);
      _fareRule._pos = lPOS;
      //STDAIR_LOG_DEBUG ("POS: " << _fareRule._pos);
    }

    // //////////////////////////////////////////////////////////////////
    storeChannel ::
    storeChannel (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeChannel::operator() (iterator_t iStr,
                                   iterator_t iStrEnd) const {
      stdair::ChannelLabel_T lChannel (iStr, iStrEnd);
      _fareRule._channel = lChannel;
      if (lChannel != "IN" && lChannel != "IF"
          && lChannel != "DN" && lChannel != "DF") {
        STDAIR_LOG_DEBUG ("Invalid channel " << lChannel);
      }
      // STDAIR_LOG_DEBUG ("Channel: " << _fareRule._channel);
    }
    
    // //////////////////////////////////////////////////////////////////
    storeAdvancePurchase ::
    storeAdvancePurchase (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeAdvancePurchase::operator() (unsigned int iAdancePurchase) const {
      _fareRule._advancePurchase = iAdancePurchase;
      //STDAIR_LOG_DEBUG ( "Advance Purchase: " << _fareRule._advancePurchase);
    }
    
    // //////////////////////////////////////////////////////////////////
    storeSaturdayStay ::
    storeSaturdayStay (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeSaturdayStay::operator() (char iSaturdayStay) const {
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
      //STDAIR_LOG_DEBUG ("Saturday Stay: " << _fareRule._saturdayStay);
    }

    // //////////////////////////////////////////////////////////////////
    storeChangeFees ::
    storeChangeFees (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeChangeFees::operator() (char iChangefees) const {
      
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
      //STDAIR_LOG_DEBUG ("Change fees: " << _fareRule._changeFees);
    }
    
    // //////////////////////////////////////////////////////////////////
    storeNonRefundable ::
    storeNonRefundable (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeNonRefundable::operator() (char iNonRefundable) const {
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
       // STDAIR_LOG_DEBUG ("Non refundable: " << _fareRule._nonRefundable);
    }
    
    // //////////////////////////////////////////////////////////////////
    storeMinimumStay ::
    storeMinimumStay (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeMinimumStay::operator() (unsigned int iMinStay) const {
      _fareRule._minimumStay = iMinStay;
      //STDAIR_LOG_DEBUG ("Minimum Stay: " << _fareRule._minimumStay );
    }

    // //////////////////////////////////////////////////////////////////
    storeFare ::
    storeFare (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeFare::operator() (double iFare) const {
      _fareRule._fare = iFare;
      // STDAIR_LOG_DEBUG ("Fare: " << _fareRule._fare);
    }

    // //////////////////////////////////////////////////////////////////
    storeAirlineCode ::
    storeAirlineCode (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeAirlineCode::operator() (iterator_t iStr,
                                       iterator_t iStrEnd) const {

      bool lAlreadyInTheList = false;
      stdair::AirlineCode_T lAirlineCode (iStr, iStrEnd);
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
      // STDAIR_LOG_DEBUG ( "Airline code: " << lAirlineCode);
    }

    // //////////////////////////////////////////////////////////////////
    storeClass ::
    storeClass (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeClass::operator() (char iChar) const {
      std::ostringstream ostr;
      ostr << iChar;
      std::string classCodeStr = ostr.str();
      const stdair::ClassCode_T lClassCode (classCodeStr);
      _fareRule._classCodeList.push_back(lClassCode);
      // Insertion of this class Code in the whole classCode name
      std::ostringstream ostrr;
      ostrr << _fareRule._classCode << classCodeStr;
      _fareRule._classCode = ostrr.str();
      //STDAIR_LOG_DEBUG ("Class Code: " << lClassCode << std::endl);
        
    }
    
    // //////////////////////////////////////////////////////////////////
    doEndFare::
    doEndFare (stdair::BomRoot& ioBomRoot,
               FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule),
        _bomRoot (ioBomRoot) {
    }
    
    // //////////////////////////////////////////////////////////////////

    void doEndFare::operator() (iterator_t iStr,
                                iterator_t iStrEnd) const {

      // Generation of the fare rule object.
      FareRuleGenerator::createFareRule (_bomRoot, _fareRule);
    }
      
    // ///////////////////////////////////////////////////////////////////
    //
    //  Utility Parsers
    //
    // ///////////////////////////////////////////////////////////////////
  
    /** 2-digit-integer parser */
    uint2_p_t uint2_p;
    
    /** 4-digit-integer parser */
    uint4_p_t uint4_p;

    /** Up-to-4-digit-integer parser */
    uint1_4_p_t uint1_4_p;

    /** Sequence of (capital) alphabetic characters: chset_p("A-Z") */
    chset_t alpha_cap_set_p ("A-Z");
    
    /** Airport Parser: repeat_p(3)[chset_p("0-9A-Z")] */
    repeat_p_t airport_p (chset_t("0-9A-Z").derived(), 3, 3);

    /** Year Parser: limit_d(2000u, 2099u)[uint4_p] */
    bounded4_p_t year_p (uint4_p.derived(), 2000u, 2099u);
      
    /** Month Parser: limit_d(1u, 12u)[uint2_p] */
    bounded2_p_t month_p (uint2_p.derived(), 1u, 12u);

    /** Day Parser: limit_d(1u, 31u)[uint2_p] */
    bounded2_p_t day_p (uint2_p.derived(), 1u, 31u);
      
    /** Hour Parser: limit_d(0u, 23u)[uint2_p] */
    bounded2_p_t hours_p (uint2_p.derived(), 0u, 23u);

    /** Minute Parser: limit_d(0u, 59u)[uint2_p] */
    bounded2_p_t minutes_p (uint2_p.derived(), 0u, 59u);

    /** Second Parser: limit_d(0u, 59u)[uint2_p] */
    bounded2_p_t seconds_p (uint2_p.derived(), 0u, 59u);

    /** Airline Code Parser: repeat_p(2,3)[chset_p("0-9A-Z")] */
    repeat_p_t airline_code_p (chset_t("0-9A-Z").derived(), 2, 3);

    /** Channel type Parser: repeat_p(2,3)[chset_p("A-ZA-Z")] */
    repeat_p_t channel_type_p (chset_t("A-Z").derived(), 2, 3);

    // //////////////////////////////////////////////////////////////////
    //  (Boost Spirit) Grammar Definition
    // //////////////////////////////////////////////////////////////////

    // //////////////////////////////////////////////////////////////////
    FareRuleParser::
    FareRuleParser (stdair::BomRoot& ioBomRoot,
                        FareRuleStruct& ioFareRule) 
      : _bomRoot (ioBomRoot),
        _fareRule (ioFareRule) {
    }

    // //////////////////////////////////////////////////////////////////
    template<typename ScannerT>
    FareRuleParser::definition<ScannerT>::
    definition (FareRuleParser const& self) {

        fare_rule_list = *( comments | fare_rule )
          ;

        comments = boost::spirit::classic::comment_p("//")
          | boost::spirit::classic::comment_p("/*", "*/")
          ;

        fare_rule = fare_key
          >> +( ';' >> segment )
          >> fare_rule_end[doEndFare(self._bomRoot, self._fareRule)]
          ;

        fare_rule_end = boost::spirit::classic::ch_p(';')
          ;

        fare_key = fare_id
          >> ';' >> (airport_p)[storeOrigin(self._fareRule)]
          >> ';' >> (airport_p)[storeDestination(self._fareRule)]
          >> ';' >> date[storeDateRangeStart(self._fareRule)]
          >> ';' >> date[storeDateRangeEnd(self._fareRule)]
          >> ';' >> time[storeStartRangeTime(self._fareRule)]
          >> ';' >> time[storeEndRangeTime(self._fareRule)]
          >> ';' >> (airport_p)[storePOS(self._fareRule)]
          >> ';' >> (channel_type_p)[storeChannel(self._fareRule)]
          >> ';' >> (uint1_4_p)[storeAdvancePurchase(self._fareRule)]
          >> ';' >> (alpha_cap_set_p)[storeSaturdayStay(self._fareRule)]
          >> ';' >> (alpha_cap_set_p)[storeChangeFees(self._fareRule)]
          >> ';' >> (alpha_cap_set_p)[storeNonRefundable(self._fareRule)]
          >> ';' >> (uint1_4_p)[storeMinimumStay(self._fareRule)]
          >> ';' >> (boost::spirit::classic::ureal_p)[storeFare(self._fareRule)]
          ;

        fare_id = boost::spirit::classic::lexeme_d[
                   (uint1_4_p)[storeFareId(self._fareRule)]]
           ;
        
        date = boost::spirit::classic::lexeme_d[
           (year_p)[boost::spirit::classic::assign_a(self._fareRule._itYear)]
           >> '-'
           >> (month_p)[boost::spirit::classic::assign_a(self._fareRule._itMonth)]
           >> '-'
           >> (day_p)[boost::spirit::classic::assign_a(self._fareRule._itDay)]]
          ;
           
        time = boost::spirit::classic::lexeme_d[
           (hours_p)[boost::spirit::classic::assign_a(self._fareRule._itHours)]
           >> ':'
           >> (minutes_p)[boost::spirit::classic::assign_a(self._fareRule._itMinutes)]
           >> !(':' >> (seconds_p)[boost::spirit::classic::assign_a(self._fareRule._itSeconds)])]
           ;

        segment = boost::spirit::classic::lexeme_d[
           (airline_code_p)[storeAirlineCode(self._fareRule)]]
          >> ';' >> (alpha_cap_set_p)[storeClass(self._fareRule)]
          ;

      //BOOST_SPIRIT_DEBUG_NODE (FareRuleParser);
      BOOST_SPIRIT_DEBUG_NODE (fare_rule_list);
      BOOST_SPIRIT_DEBUG_NODE (comments);
      BOOST_SPIRIT_DEBUG_NODE (fare_rule);
      BOOST_SPIRIT_DEBUG_NODE (fare_id);
      BOOST_SPIRIT_DEBUG_NODE (fare_key);
      BOOST_SPIRIT_DEBUG_NODE (segment);
      BOOST_SPIRIT_DEBUG_NODE (fare_rule_end);
      BOOST_SPIRIT_DEBUG_NODE (date);
      BOOST_SPIRIT_DEBUG_NODE (time);
      
    }

    // //////////////////////////////////////////////////////////////////
    template<typename ScannerT>
    boost::spirit::classic::rule<ScannerT> const&
    FareRuleParser::definition<ScannerT>::start() const {
      return fare_rule_list;
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
                        << " does not exist or can not be read.");
      
      throw FareInputFileNotFoundException ("The fare file " + _filename + " does not exist or can not be read");
    }
    
    // Open the file
    _startIterator = iterator_t (_filename);

    // Check the filename exists and can be open
    if (!_startIterator) {
      STDAIR_LOG_ERROR ("The fare file " << _filename << " can not be open."
                          << std::endl);

      throw FareInputFileNotFoundException ("The file " + _filename + " does not exist or can not be read");
    }

    // Create an EOF iterator
    _endIterator = _startIterator.make_end();
  }
    
  // //////////////////////////////////////////////////////////////////////
  bool FareRuleFileParser::generateFareRules () {
    bool oResult = false;
      
    STDAIR_LOG_DEBUG ("Parsing fare input file: " << _filename);

    // Initialise the parser (grammar) with the helper/staging structure.
    FareParserHelper::FareRuleParser lFPParser (_bomRoot, _fareRule);
      
    // Launch the parsing of the file and, thanks to the doEndFare
    // call-back structure, the building of the whole BomRoot BOM
    boost::spirit::classic::parse_info<iterator_t> info =
      boost::spirit::classic::parse (_startIterator, _endIterator, lFPParser, 
                                     boost::spirit::classic::space_p);

    // Retrieves whether or not the parsing was successful
    oResult = info.hit;
      
    const std::string hasBeenFullyReadStr = (info.full == true)?"":"not ";
    if (oResult == true) {
      STDAIR_LOG_DEBUG ("Parsing of fare input file: " << _filename
                        << " succeeded: read " << info.length
                        << " characters. The input file has "
                        << hasBeenFullyReadStr
                        << "been fully read. Stop point: " << info.stop);
        
    } else {
      // TODO: decide whether to throw an exception
      STDAIR_LOG_ERROR ("Parsing of fare input file: " << _filename
                        << " failed: read " << info.length
                        << " characters. The input file has "
                        << hasBeenFullyReadStr
                        << "been fully read. Stop point: " << info.stop);
    }
    return oResult;
  }
    
}
