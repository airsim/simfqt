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
#include <simfqt/command/FareParserGrammar_Def.hpp>
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
      _fareRule.setFareID (iFareId);
      
      // DEBUG
      //STDAIR_LOG_DEBUG ( "Fare Id: " << _fareRule.getFareID ());
      const stdair::AirlineCode_T lEmptyAirlineCode ("");
      _fareRule.setAirlineCode(lEmptyAirlineCode);
      _fareRule.clearAirlineCodeList();
      const stdair::ClassCode_T lEmptyClassCode ("");
      _fareRule.setClassCode(lEmptyClassCode);
      _fareRule.clearClassCodeList();
      _fareRule._itSeconds = 0; 
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
       const stdair::AirportCode_T lOrigin (iChar.begin(), iChar.end());
       _fareRule.setOrigin (lOrigin);
       // DEBUG
       //STDAIR_LOG_DEBUG ( "Origin: " << _fareRule.getOrigin ());
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
       const stdair::AirportCode_T lDestination (iChar.begin(), iChar.end());
       _fareRule.setDestination (lDestination);
       // DEBUG
       //STDAIR_LOG_DEBUG ( "Destination: " << _fareRule.getDestination ());
    }

    // //////////////////////////////////////////////////////////////////
    storeTripType ::
    storeTripType (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeTripType::operator() (std::vector<char> iChar,
                                       boost::spirit::qi::unused_type,
                                       boost::spirit::qi::unused_type) const {
      const stdair::TripType_T lTripType (iChar.begin(), iChar.end());
      if (lTripType == "OW" || lTripType == "RT") {
        _fareRule.setTripType (lTripType);
      } else {
        // ERROR
        STDAIR_LOG_ERROR ("Invalid trip type  " << lTripType);
      }                       
      // DEBUG
      //STDAIR_LOG_DEBUG ("TripType: " << _fareRule.getTripType ());
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
      const stdair::Date_T& lDateStart = _fareRule.calculateDate ();
      _fareRule.setDateRangeStart (lDateStart);
      // DEBUG
      //STDAIR_LOG_DEBUG ("Date Range Start: " << _fareRule.getDateRangeStart ());
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
      const stdair::Date_T& lDateEnd = _fareRule.calculateDate ();
      // As a Boost date period (DatePeriod_T) defines the last day of
      // the period to be end-date - one day, we have to add one day to that
      // end date before.
      const stdair::DateOffset_T oneDay (1);
      const stdair::Date_T lBoostDateEnd = lDateEnd + oneDay;
      _fareRule.setDateRangeEnd (lBoostDateEnd);
       // DEBUG
      //STDAIR_LOG_DEBUG ("Date Range End: " << _fareRule.getDateRangeEnd ());
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
      const stdair::Duration_T& lTimeStart = _fareRule.calculateTime ();
      _fareRule.setTimeRangeStart (lTimeStart);
      // DEBUG
      //STDAIR_LOG_DEBUG ("Time Range Start: " << _fareRule.getTimeRangeStart ());
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
      const stdair::Duration_T& lTimeEnd = _fareRule.calculateTime ();
      _fareRule.setTimeRangeEnd (lTimeEnd);
      // DEBUG
      //STDAIR_LOG_DEBUG ("Time Range End: " << _fareRule.getTimeRangeEnd ());
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
      const stdair::CityCode_T lPOS (iChar.begin(), iChar.end());
      if (lPOS == _fareRule.getOrigin() || lPOS == _fareRule.getDestination()) {
        _fareRule.setPOS (lPOS);
      } else if (lPOS == "ROW") {
        const stdair::CityCode_T lPOSROW ("ROW");
        _fareRule.setPOS (lPOSROW);
      } else {
        // ERROR
        STDAIR_LOG_ERROR ("Invalid point of sale " << lPOS);
      }
      // DEBUG
      //STDAIR_LOG_DEBUG ("POS: " << _fareRule.getPOS ());
    }

    // //////////////////////////////////////////////////////////////////
    storeCabinCode ::
    storeCabinCode (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeCabinCode::operator() (char iChar,
                                     boost::spirit::qi::unused_type,
                                     boost::spirit::qi::unused_type) const {
      std::ostringstream ostr;
      ostr << iChar;
      const std::string cabinCodeStr = ostr.str();
      const stdair::CabinCode_T& lCabinCode (cabinCodeStr);
      _fareRule.setCabinCode (lCabinCode);
     
      // DEBUG
      //STDAIR_LOG_DEBUG ("Cabin Code: " << _fareRule.getCabinCode ());                 
    
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
      const stdair::ChannelLabel_T lChannel (iChar.begin(), iChar.end());
      if (lChannel != "IN" && lChannel != "IF"
          && lChannel != "DN" && lChannel != "DF") {
        // ERROR
        STDAIR_LOG_ERROR ("Invalid channel " << lChannel);
      }
      _fareRule.setChannel (lChannel);
      // DEBUG
      //STDAIR_LOG_DEBUG ("Channel: " << _fareRule.getChannel ());
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
      const stdair::DayDuration_T& lAdancePurchase = iAdancePurchase;
      _fareRule.setAdvancePurchase (lAdancePurchase);
      // DEBUG
      //STDAIR_LOG_DEBUG ( "Advance Purchase: " << _fareRule.getAdvancePurchase ());
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
          // DEBUG
          STDAIR_LOG_DEBUG ("Invalid saturdayStay char " << iSaturdayStay);
        }
      }
      const stdair::SaturdayStay_T lSaturdayStay (lBool);
      _fareRule.setSaturdayStay (lSaturdayStay);
      // DEBUG
      //STDAIR_LOG_DEBUG ("Saturday Stay: " << _fareRule.getSaturdayStay ());
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
          // DEBUG
          STDAIR_LOG_DEBUG ("Invalid change fees char " << iChangefees);
        }
      }
      const stdair::ChangeFees_T lChangefees (lBool);
      _fareRule.setChangeFees (lChangefees);
      // DEBUG
      //STDAIR_LOG_DEBUG ("Change fees: " << _fareRule.getChangeFees ());
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
           // DEBUG
           STDAIR_LOG_DEBUG ("Invalid non refundable char " << iNonRefundable);
         }
       }
       const stdair::NonRefundable_T lNonRefundable (lBool);
       _fareRule.setNonRefundable (lNonRefundable);
       // DEBUG
       //STDAIR_LOG_DEBUG ("Non refundable: " << _fareRule.getNonRefundable ());
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
      const stdair::DayDuration_T lMinStay = iMinStay;
      _fareRule.setMinimumStay (lMinStay);
      // DEBUG
      //STDAIR_LOG_DEBUG ("Minimum Stay: " << _fareRule.getMinimumStay ());
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
     const stdair::PriceValue_T lFare = iFare;
      _fareRule.setFare (lFare);
      // DEBUG
      //STDAIR_LOG_DEBUG ("Fare: " << _fareRule.getFare ());
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

      const stdair::AirlineCode_T lAirlineCode (iChar.begin(), iChar.end());
      // Insertion of this airline Code list in the whole AirlineCode name
      _fareRule.addAirlineCode (lAirlineCode);
      // DEBUG
      //STDAIR_LOG_DEBUG ( "Airline code: " << lAirlineCode);
    }

    // //////////////////////////////////////////////////////////////////
    storeClass ::
    storeClass (FareRuleStruct& ioFareRule)
      : ParserSemanticAction (ioFareRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeClass::operator() (std::vector<char> iChar,
                                 boost::spirit::qi::unused_type,
                                 boost::spirit::qi::unused_type) const {
      std::ostringstream ostr;
      for (std::vector<char>::const_iterator lItVector = iChar.begin();
         lItVector != iChar.end();
         lItVector++) {
        ostr << *lItVector;
      }
      const std::string classCodeStr = ostr.str();
      const stdair::ClassCode_T lClassCode (classCodeStr);
      // Insertion of this class Code list in the whole classCode name
      _fareRule.addClassCode (lClassCode);
      // DEBUG
      //STDAIR_LOG_DEBUG ("Class Code: " << lClassCode);
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
      // DEBUG
      //STDAIR_LOG_DEBUG ("Do End");
      // Generation of the fare rule object.
      FareRuleGenerator::createAirportPair (_bomRoot, _fareRule);
      STDAIR_LOG_DEBUG(_fareRule.describe());
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
      
      throw FareInputFileNotFoundException ("The fare file " + _filename
                                            + " does not exist or can not be read");
    }
  }
    
  // //////////////////////////////////////////////////////////////////////
  void FareRuleFileParser::generateFareRules () {
      
    STDAIR_LOG_DEBUG ("Parsing fare input file: " << _filename);

    // File to be parsed
    const std::string* lFileName = &_filename;
    const char *lChar = (*lFileName).c_str();
    std::ifstream fileToBeParsed(lChar, std::ios_base::in);

    // Check if the filename exist and can be open
    if (fileToBeParsed == false) {
      STDAIR_LOG_ERROR ("The fare file " << _filename << " can not be open."
                          << std::endl);

      throw FareInputFileNotFoundException ("The file " + _filename
                                            + " does not exist or can not be read");
    }
    
    // Create an input iterator
    stdair::base_iterator_t inputBegin (fileToBeParsed);

    // Convert input iterator to an iterator usable by spirit parser  
    stdair::iterator_t 
      start (boost::spirit::make_default_multi_pass (inputBegin));
    stdair::iterator_t end;

    // Initialise the parser (grammar) with the helper/staging structure.
    FareParserHelper::FareRuleParser<stdair::iterator_t> lFPParser(_bomRoot, _fareRule);
      
    // Launch the parsing of the file and, thanks to the doEndFare
    // call-back structure, the building of the whole BomRoot BOM
    const bool hasParsingBeenSuccesful = 
       boost::spirit::qi::phrase_parse (start, end, lFPParser,
                                        boost::spirit::ascii::space);
      
    if (hasParsingBeenSuccesful == false) {
      STDAIR_LOG_ERROR ("Parsing of fare input file: " << _filename
                        << " failed");
      throw FareFileParsingFailedException ("Parsing of fare input file: "
                                            + _filename + " failed");
    }
    
    if  (start != end) {
      STDAIR_LOG_ERROR ("Parsing of fare input file: " << _filename
                        << " failed");
      throw FareFileParsingFailedException ("Parsing of fare input file: "
                                            + _filename + " failed");
    }
    
    if (hasParsingBeenSuccesful == true && start == end) {
      STDAIR_LOG_DEBUG ("Parsing of fare input file: " << _filename
      << " succeeded");
    }
 
  }
    
}
