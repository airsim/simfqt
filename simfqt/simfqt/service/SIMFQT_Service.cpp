// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/bom/BomManager.hpp> // for display()
#include <stdair/service/Logger.hpp>
// Simfqt
#include <simfqt/basic/BasConst_SIMFQT_Service.hpp>
#include <simfqt/command/FareQuoter.hpp>
#include <simfqt/factory/FacSimfqtServiceContext.hpp>
#include <simfqt/service/SIMFQT_ServiceContext.hpp>
#include <simfqt/SIMFQT_Service.hpp>

namespace SIMFQT {

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
  SIMFQT_Service::SIMFQT_Service (const FareQuoteID_T& iFareQuoteID)
    : _simfqtServiceContext (NULL) {

    // Initialise the context
    init (iFareQuoteID);
  }

  // //////////////////////////////////////////////////////////////////////
  SIMFQT_Service::SIMFQT_Service (const stdair::BasLogParams& iLogParams,
                                  const FareQuoteID_T& iFareQuoteID)
    : _simfqtServiceContext (NULL) {
    
    // Set the log file
    logInit (iLogParams);

    // Initialise the (remaining of the) context
    init (iFareQuoteID);
  }

  // //////////////////////////////////////////////////////////////////////
  SIMFQT_Service::~SIMFQT_Service () {
    // Delete/Clean all the objects from memory
    finalise();
  }

  // //////////////////////////////////////////////////////////////////////
  void SIMFQT_Service::logInit (const stdair::BasLogParams& iLogParams) {
    stdair::Logger::init (iLogParams);
  }

  // //////////////////////////////////////////////////////////////////////
  void SIMFQT_Service::init (const FareQuoteID_T& iFareQuoteID) {
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
      STDAIR_LOG_DEBUG ("Price quoting: " << lPriceQuotingMeasure << " - "
                        << lSIMFQT_ServiceContext.display());

    } catch (const std::exception& error) {
      STDAIR_LOG_ERROR ("Exception: "  << error.what());
      throw QuotingException();
    }

    return oPrice;
  }
  
}
