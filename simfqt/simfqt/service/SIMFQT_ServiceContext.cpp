// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iostream>
#include <sstream>
// Simfqt
#include <simfqt/basic/BasConst_SIMFQT_Service.hpp>
#include <simfqt/service/SIMFQT_ServiceContext.hpp>

namespace SIMFQT {

  // //////////////////////////////////////////////////////////////////////
  SIMFQT_ServiceContext::SIMFQT_ServiceContext ()
    : _fareQuoteID (DEFAULT_FARE_QUOTER_ID) {
  }

  // //////////////////////////////////////////////////////////////////////
  SIMFQT_ServiceContext::
  SIMFQT_ServiceContext (const FareQuoteID_T& iFareQuoteID)
    : _fareQuoteID (iFareQuoteID) {
  }

  // //////////////////////////////////////////////////////////////////////
  SIMFQT_ServiceContext::~SIMFQT_ServiceContext() {
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string SIMFQT_ServiceContext::shortDisplay() const {
    std::ostringstream oStr;
    oStr << "SIMFQT_ServiceContext: " << std::endl
         << "Fare Quote system ID: " << _fareQuoteID
         << std::endl;
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string SIMFQT_ServiceContext::display() const {
    std::ostringstream oStr;
    oStr << shortDisplay();
    return oStr.str();
  }

}
