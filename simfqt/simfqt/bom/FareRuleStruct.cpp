// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/service/Logger.hpp>
// SIMFQT
#include <simfqt/SIMFQT_Types.hpp>
#include <simfqt/bom/FareRuleStruct.hpp>

namespace SIMFQT {

  // ////////////////////////////////////////////////////////////////////
  FareRuleStruct::FareRuleStruct ()
    :_fareId(0), _origin(""), _destination(""),
     _dateRangeStart(stdair::DEFAULT_DATE),
     _dateRangeEnd(stdair::DEFAULT_DATE),
     _timeRangeStart(stdair::DEFAULT_EPSILON_DURATION),
     _timeRangeEnd(stdair::DEFAULT_EPSILON_DURATION),
     _pos (""), _advancePurchase(0), _saturdayStay("T"),
     _changeFees("T"), _nonRefundable("T"),
     _minimumStay(0), _fare(0),
     _airlineCode(""), _classCode("") {

  }

  // ////////////////////////////////////////////////////////////////////
  stdair::Date_T FareRuleStruct::getDate() const {
    return stdair::Date_T (_itYear, _itMonth, _itDay);
  }

  // ////////////////////////////////////////////////////////////////////
  stdair::Duration_T FareRuleStruct::getTime() const {
    return boost::posix_time::hours (_itHours)
      + boost::posix_time::minutes (_itMinutes)
      + boost::posix_time::seconds (_itSeconds);
  }
  
 
  // ////////////////////////////////////////////////////////////////////
  const std::string FareRuleStruct::describe () const {
    std::ostringstream ostr;
    return ostr.str();
  }

}

