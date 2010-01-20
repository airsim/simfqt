// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// Boost
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
// StdAir
#include <stdair/basic/BasChronometer.hpp>
// Simfqt
#include <simfqt/basic/BasConst_SIMFQT_Service.hpp>
#include <simfqt/command/FareQuoter.hpp>
#include <simfqt/factory/FacSimfqtServiceContext.hpp>
#include <simfqt/service/SIMFQT_ServiceContext.hpp>
#include <simfqt/service/Logger.hpp>
#include <simfqt/SIMFQT_Service.hpp>

namespace SIMFQT {

  // //////////////////////////////////////////////////////////////////////
  SIMFQT_Service::
  SIMFQT_Service (std::ostream& ioLogStream, const FareQuoteID_T& iFareQuoteID)
    : _simfqtServiceContext (NULL) {
    init (ioLogStream, iFareQuoteID);
  }

  // //////////////////////////////////////////////////////////////////////
  SIMFQT_Service::SIMFQT_Service ()
    : _simfqtServiceContext (NULL) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  SIMFQT_Service::SIMFQT_Service (const SIMFQT_Service& iService) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  SIMFQT_Service::~SIMFQT_Service () {
    // Delete/Clean all the objects from memory
    finalise();
  }

  // //////////////////////////////////////////////////////////////////////
  void logInit (const LOG::EN_LogLevel iLogLevel,
                std::ostream& ioLogOutputFile) {
    Logger::instance().setLogParameters (iLogLevel, ioLogOutputFile);
  }

  // //////////////////////////////////////////////////////////////////////
  void SIMFQT_Service::init (std::ostream& ioLogStream,
                             const FareQuoteID_T& iFareQuoteID) {
    // Set the log file
    logInit (LOG::DEBUG, ioLogStream);

    // Initialise the context
    SIMFQT_ServiceContext& lSIMFQT_ServiceContext = 
      FacSimfqtServiceContext::instance().create (iFareQuoteID);
    _simfqtServiceContext = &lSIMFQT_ServiceContext;
  }
  
  // //////////////////////////////////////////////////////////////////////
  void SIMFQT_Service::finalise () {
    assert (_simfqtServiceContext != NULL);
  }

  // //////////////////////////////////////////////////////////////////////
  Price_T SIMFQT_Service::priceQuote (const AirlineCode_T& iAirlineCode,
                                      const PartySize_T& iPartySize) {
    Price_T oPrice = 0.0;
    
    if (_simfqtServiceContext == NULL) {
      throw NonInitialisedServiceException();
    }
    assert (_simfqtServiceContext != NULL);
    SIMFQT_ServiceContext& lSIMFQT_ServiceContext= *_simfqtServiceContext;

    try {
      
      // Retrieve the Fare Quote system ID
      const FareQuoteID_T& lFareQuoteID =
        lSIMFQT_ServiceContext.getFareQuoteID();
      
      // Delegate the price quotation to the dedicated command
      stdair::BasChronometer lPriceQuotingChronometer;
      lPriceQuotingChronometer.start();
      oPrice = FareQuoter::priceQuote (lFareQuoteID, iAirlineCode, iPartySize);
      const double lPriceQuotingMeasure = lPriceQuotingChronometer.elapsed();
      
      // DEBUG
      SIMFQT_LOG_DEBUG ("Price quoting: " << lPriceQuotingMeasure << " - "
                        << lSIMFQT_ServiceContext.display());

    } catch (const std::exception& error) {
      SIMFQT_LOG_ERROR ("Exception: "  << error.what());
      throw QuotingException();
    }

    return oPrice;
  }
  
}
