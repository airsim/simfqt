#ifndef __SIMFQT_BOM_FARERULESTRUCT_HPP
#define __SIMFQT_BOM_FARERULESTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/basic/BasParserTypes.hpp>
// SIMFQT
#include <simfqt/SIMFQT_Types.hpp>

namespace SIMFQT {

  /** Utility Structure for the parsing of Flight-Period structures. */
  struct FareRuleStruct : public stdair::StructAbstract {
  public:
 
    /** Default constructor. */
    FareRuleStruct ();

    /** Get the date from the staging details. */
    stdair::Date_T getDate() const;

    /** Get the time from the staging details. */
    stdair::Duration_T getTime() const;
    
    /** Display of the structure. */
    const std::string describe() const;
    
    // ////////////////// Attributes /////////////////
    /** Staging Date. */
    stdair::year_t _itYear;
    stdair::month_t _itMonth;
    stdair::day_t _itDay;
      
    /** Staging Time. */
    //long _itHours;
    stdair::hour_t _itHours;
    stdair::minute_t _itMinutes;
    stdair::second_t _itSeconds;

    
    unsigned long int _nbOfAirlines;
    
    /** Fare ID. */
    SIMFQT::FareQuoteID_T _fareId;

    /** Origin. */
    stdair::AirportCode_T _origin;

    /** Destination. */
    stdair::AirportCode_T _destination;

    /** Start Range date available for this fare rule.*/
    stdair::Date_T _dateRangeStart;

    /** Start Range date available for this fare rule.*/
    stdair::Date_T _dateRangeEnd;
    
    /** Start time from the time range available for this fare rule.*/
    stdair::Duration_T _timeRangeStart;
     
    /** End time from the time range available for this fare rule.*/
    stdair::Duration_T _timeRangeEnd;
    
     /** Point-of-sale. */
    stdair::AirlineCode_T _pos;
    
    /** Channel distribution. */
    stdair::ChannelLabel_T _channel;
    
    /** Number of days that the ticket is sold before the  flightDate.*/
    stdair::DayDuration_T _advancePurchase;
    
    /** Boolean saying whether a saturday is considered during the stay .*/
    stdair::SaturdayStay_T _saturdayStay;

    /** Boolean saying whether the change fees option is requested or not.*/
    stdair::ChangeFees_T _changeFees;

    /** Boolean saying whether the refundable option is requested or not.*/
    stdair::NonRefundable_T _nonRefundable;
     
    /** Number of days that the customer spent into the destination city.*/
    stdair::DayDuration_T _minimumStay;
    
    /** Price.*/
    stdair::PriceValue_T _fare;

    /** Airline code */
    stdair::AirlineCode_T _airlineCode;

    /** Code */
    stdair::ClassCode_T _classCode;

    /** Airline Code List*/
    stdair::AirlineCodeList_T _airlineCodeList;
    
    /** Class Code List*/
    stdair::ClassCodeList_T _classCodeList;

  };

}
#endif // __SIMFQT_BOM_FARERULESTRUCT_HPP
