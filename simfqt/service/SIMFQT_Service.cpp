// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// Boost
#include <boost/make_shared.hpp>
// StdAir
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/bom/BomDisplay.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/STDAIR_Service.hpp>
// Simfqt
#include <simfqt/basic/BasConst_SIMFQT_Service.hpp>
#include <simfqt/factory/FacSimfqtServiceContext.hpp>
#include <simfqt/command/FareParser.hpp>
#include <simfqt/command/FareQuoter.hpp>
#include <simfqt/service/SIMFQT_ServiceContext.hpp>
#include <simfqt/SIMFQT_Service.hpp>

namespace SIMFQT {

  // //////////////////////////////////////////////////////////////////////
  SIMFQT_Service::SIMFQT_Service() : _simfqtServiceContext (NULL) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  SIMFQT_Service::SIMFQT_Service (const SIMFQT_Service& iService) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  SIMFQT_Service::SIMFQT_Service (const stdair::BasLogParams& iLogParams)
    : _simfqtServiceContext (NULL) {
    
    // Initialise the STDAIR service handler
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr =
      initStdAirService (iLogParams);
    
    // Initialise the service context
    initServiceContext();

    // Add the StdAir service context to the SIMFQT service context
    // \note SIMFQT owns the STDAIR service resources here.
    const bool ownStdairService = true;
    addStdAirService (lSTDAIR_Service_ptr, ownStdairService);
    
    // Initialise the (remaining of the) context
    initSimfqtService();
  }

  // ////////////////////////////////////////////////////////////////////
  SIMFQT_Service::SIMFQT_Service (const stdair::BasLogParams& iLogParams,
                                  const stdair::BasDBParams& iDBParams)
    : _simfqtServiceContext (NULL) {
    
    // Initialise the STDAIR service handler
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr =
      initStdAirService (iLogParams, iDBParams);
    
    // Initialise the service context
    initServiceContext();

    // Add the StdAir service context to the SIMFQT service context
    // \note SIMFQT owns the STDAIR service resources here.
    const bool ownStdairService = true;
    addStdAirService (lSTDAIR_Service_ptr, ownStdairService);
    
    // Initialise the (remaining of the) context
    initSimfqtService();
  }

  // ////////////////////////////////////////////////////////////////////
  SIMFQT_Service::
  SIMFQT_Service (stdair::STDAIR_ServicePtr_T ioSTDAIR_Service_ptr)
    : _simfqtServiceContext (NULL) {

    // Initialise the service context
    initServiceContext();

    // Store the STDAIR service object within the (SIMFQT) service context
    // \note Simfqt does not own the STDAIR service resources here.
    const bool doesNotOwnStdairService = false;
    addStdAirService (ioSTDAIR_Service_ptr, doesNotOwnStdairService);
    
    // Initialise the context
    initSimfqtService();
  }

  // //////////////////////////////////////////////////////////////////////
  SIMFQT_Service::~SIMFQT_Service() {
    // Delete/Clean all the objects from memory
    finalise();
  }

  // //////////////////////////////////////////////////////////////////////
  void SIMFQT_Service::finalise() {
    assert (_simfqtServiceContext != NULL);
    // Reset the (Boost.)Smart pointer pointing on the STDAIR_Service object.
    _simfqtServiceContext->reset();
  }

  // //////////////////////////////////////////////////////////////////////
  void SIMFQT_Service::initServiceContext() {
    // Initialise the service context
    SIMFQT_ServiceContext& lSIMFQT_ServiceContext = 
      FacSimfqtServiceContext::instance().create();
    _simfqtServiceContext = &lSIMFQT_ServiceContext;
  }

  // ////////////////////////////////////////////////////////////////////
  void SIMFQT_Service::
  addStdAirService (stdair::STDAIR_ServicePtr_T ioSTDAIR_Service_ptr,
                    const bool iOwnStdairService) {

    // Retrieve the SimFQT service context
    assert (_simfqtServiceContext != NULL);
    SIMFQT_ServiceContext& lSIMFQT_ServiceContext = *_simfqtServiceContext;

    // Store the STDAIR service object within the (SimFQT) service context
    lSIMFQT_ServiceContext.setSTDAIR_Service (ioSTDAIR_Service_ptr,
                                              iOwnStdairService);
  }
  
  // //////////////////////////////////////////////////////////////////////
  stdair::STDAIR_ServicePtr_T SIMFQT_Service::
  initStdAirService (const stdair::BasLogParams& iLogParams,
                     const stdair::BasDBParams& iDBParams) {

    /**
     * Initialise the STDAIR service handler.
     *
     * \note The track of the object memory is kept thanks to the
     * Boost Smart Pointers component.
     */
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr = 
      boost::make_shared<stdair::STDAIR_Service> (iLogParams, iDBParams);
    assert (lSTDAIR_Service_ptr != NULL);
    
    return lSTDAIR_Service_ptr;
  }
  
  // //////////////////////////////////////////////////////////////////////
  stdair::STDAIR_ServicePtr_T SIMFQT_Service::
  initStdAirService (const stdair::BasLogParams& iLogParams) {

    /**
     * Initialise the STDAIR service handler.
     *
     * \note The track of the object memory is kept thanks to the
     * Boost Smart Pointers component.
     */
    stdair::STDAIR_ServicePtr_T lSTDAIR_Service_ptr = 
      boost::make_shared<stdair::STDAIR_Service> (iLogParams);
    assert (lSTDAIR_Service_ptr != NULL);

    return lSTDAIR_Service_ptr;
  }
  
  // ////////////////////////////////////////////////////////////////////
  void SIMFQT_Service::initSimfqtService() {
    // Do nothing at this stage. A sample BOM tree may be built by
    // calling the buildSampleBom() method
  }

  // ////////////////////////////////////////////////////////////////////
  void SIMFQT_Service::
  parseAndLoad (const FareFilePath& iFareFilename) { 

    // Retrieve the SimFQT service context
    if (_simfqtServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The SimFQT service "
                                                    "has not been initialised");
    }
    assert (_simfqtServiceContext != NULL);

    // Retrieve the SimFQT service context and whether it owns the Stdair
    // service
    SIMFQT_ServiceContext& lSIMFQT_ServiceContext = *_simfqtServiceContext;
    const bool doesOwnStdairService =
      lSIMFQT_ServiceContext.getOwnStdairServiceFlag();

    // Retrieve the StdAir service object from the (SimFQT) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lSIMFQT_ServiceContext.getSTDAIR_Service();

    // Retrieve the persistent BOM root object.
    stdair::BomRoot& lPersistentBomRoot = 
      lSTDAIR_Service.getPersistentBomRoot();
    
    /**
     * 1. Initialise the airline inventories
     */
    FareParser::fareRuleGeneration (iFareFilename, lPersistentBomRoot);    

    /**
     * 2. Delegate the complementary building of objects and links by the
     *    appropriate levels/components
     * 
     * \note: Currently, no more things to do by SimFQT at that stage,
     *        as there is no child
     */ 
    
    /**
     * 3. Build the complementary links
     */
    buildComplementaryLinks (lPersistentBomRoot);

    /**
     * 4. Have SimFQT clone the whole persistent BOM tree, only when the StdAir
     *    service is owned by the current component (SimFQT here)
     */
    if (doesOwnStdairService == true) {
      //
      clonePersistentBom ();
    }
  }
 
  // ////////////////////////////////////////////////////////////////////
  void SIMFQT_Service::buildSampleBom() {

    // Retrieve the SimFQT service context
    if (_simfqtServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The SimFQT service "
                                                    "has not been initialised");
    }
    assert (_simfqtServiceContext != NULL);

    // Retrieve the SimFQT service context and whether it owns the Stdair
    // service
    SIMFQT_ServiceContext& lSIMFQT_ServiceContext = *_simfqtServiceContext;
    const bool doesOwnStdairService =
      lSIMFQT_ServiceContext.getOwnStdairServiceFlag();

    // Retrieve the StdAir service object from the (SimFQT) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lSIMFQT_ServiceContext.getSTDAIR_Service(); 

    // Retrieve the persistent BOM root object.
    stdair::BomRoot& lPersistentBomRoot = 
      lSTDAIR_Service.getPersistentBomRoot();
    
    /**
     * 1. Have StdAir build the whole BOM tree, only when the StdAir service is
     *    owned by the current component (SimFQT here)
     */
    if (doesOwnStdairService == true) {
      //
      lSTDAIR_Service.buildSampleBom();
    } 

    /**
     * 2. Delegate the complementary building of objects and links by the
     *    appropriate levels/components
     * 
     * \note: Currently, no more things to do by SimFQT at that stage,
     *        as there is no child
     */ 

    /**
     * 3. Build the complementary links at the SimFQT level 
     */ 
    buildComplementaryLinks (lPersistentBomRoot);

    /**
     * 4. Have SimFQT clone the whole persistent BOM tree, only when the StdAir
     *    service is owned by the current component (SimFQT here)
     */
    if (doesOwnStdairService == true) {
      //
      clonePersistentBom ();
    }
  } 

  // ////////////////////////////////////////////////////////////////////
  void SIMFQT_Service::clonePersistentBom () {

    // Retrieve the SimFQT service context
    if (_simfqtServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The SimFQT service "
                                                    "has not been initialised");
    }
    assert (_simfqtServiceContext != NULL);

    // Retrieve the SimFQT service context and whether it owns the Stdair
    // service
    SIMFQT_ServiceContext& lSIMFQT_ServiceContext = *_simfqtServiceContext;
    const bool doesOwnStdairService =
      lSIMFQT_ServiceContext.getOwnStdairServiceFlag();

    // Retrieve the StdAir service object from the (SimFQT) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lSIMFQT_ServiceContext.getSTDAIR_Service();
    
    /**
     * Have StdAir clone the whole persistent BOM tree, only when the StdAir
     * service is owned by the current component (SimFQT here)
     */
    if (doesOwnStdairService == true) {
      //
      lSTDAIR_Service.clonePersistentBom (); 
    }  

    /**
     * Build the complementary links at the SimFQT level 
     */
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();   
    buildComplementaryLinks (lBomRoot);
  } 

  // ////////////////////////////////////////////////////////////////////
  void SIMFQT_Service::buildComplementaryLinks (stdair::BomRoot& ioBomRoot) {
    // Currently, no more things to do by SimFQT at that stage.
  }

  // //////////////////////////////////////////////////////////////////////
  stdair::BookingRequestStruct SIMFQT_Service::buildBookingRequest(const bool isForCRS) {

    // Retrieve the SIMFQT service context
    if (_simfqtServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Simfqt service has not "
                                                    "been initialised");
    }
    assert (_simfqtServiceContext != NULL);

    SIMFQT_ServiceContext& lSIMFQT_ServiceContext = *_simfqtServiceContext;
  
    // Retrieve the STDAIR service object from the (Simfqt) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lSIMFQT_ServiceContext.getSTDAIR_Service();

    // Delegate the BOM building to the dedicated service
    stdair::BookingRequestStruct oBookingRequest =
      lSTDAIR_Service.buildSampleBookingRequest (isForCRS);

    return oBookingRequest;
  }

  // //////////////////////////////////////////////////////////////////////
  void SIMFQT_Service::
  buildSampleTravelSolutions(stdair::TravelSolutionList_T& ioTravelSolutionList){

    // Retrieve the SIMFQT service context
    if (_simfqtServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Simfqt service has not "
                                                    "been initialised");
    }
    assert (_simfqtServiceContext != NULL);

    SIMFQT_ServiceContext& lSIMFQT_ServiceContext = *_simfqtServiceContext;
    
    // Retrieve the STDAIR service object from the (Simfqt) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lSIMFQT_ServiceContext.getSTDAIR_Service();

    // Delegate the BOM building to the dedicated service
    lSTDAIR_Service.buildSampleTravelSolutionForPricing (ioTravelSolutionList);
  }


  // ////////////////////////////////////////////////////////////////////
  std::string SIMFQT_Service::csvDisplay() const {

    // Retrieve the SIMFQT service context
    if (_simfqtServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The SimFQT service "
                                                    "has not been initialised");
    }
    assert (_simfqtServiceContext != NULL);

    SIMFQT_ServiceContext& lSIMFQT_ServiceContext = *_simfqtServiceContext;
  
    // Retrieve the STDAIR service object from the (SimFQT) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lSIMFQT_ServiceContext.getSTDAIR_Service();

    // Get the root of the BOM tree, on which all of the other BOM objects
    // are attached
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    // Delegate the BOM display to the dedicated service
    std::ostringstream oCSVStr;
    stdair::BomDisplay::csvSimFQTAirRACDisplay (oCSVStr, lBomRoot);
    return oCSVStr.str(); 
  }

  // //////////////////////////////////////////////////////////////////////
  std::string SIMFQT_Service::
  csvDisplay (const stdair::TravelSolutionList_T& ioTravelSolutionList) const {

    // Retrieve the Simfqt service context
    if (_simfqtServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Simfqt service has not "
                                                    "been initialised");
    }
    assert (_simfqtServiceContext != NULL);

    // Retrieve the Simfqt service context
    SIMFQT_ServiceContext& lSIMFQT_ServiceContext = *_simfqtServiceContext;
  
    // Retrieve the STDAIR service object from the (Simfqt) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lSIMFQT_ServiceContext.getSTDAIR_Service();

    // Delegate the BOM building to the dedicated service
    return lSTDAIR_Service.csvDisplay (ioTravelSolutionList);
  }

  // //////////////////////////////////////////////////////////////////////
  std::string SIMFQT_Service::
  csvDisplay (const stdair::AirportCode_T& iOrigin,
              const stdair::AirportCode_T& iDestination,
              const stdair::Date_T& iDepartureDate) const {

    // Retrieve the SIMFQT service context
    if (_simfqtServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Simfqt service "
                                                    "has not been initialised");
    }
    assert (_simfqtServiceContext != NULL);

    SIMFQT_ServiceContext& lSIMFQT_ServiceContext = *_simfqtServiceContext;
  
    // Retrieve the STDAIR service object from the (SIMFQT) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lSIMFQT_ServiceContext.getSTDAIR_Service();

    // Delegate the BOM display to the dedicated service
    return lSTDAIR_Service.csvDisplay (iOrigin, iDestination,
                                       iDepartureDate);
  }

  // //////////////////////////////////////////////////////////////////////
  std::string SIMFQT_Service::list() const {

    // Retrieve the SIMFQT service context
    if (_simfqtServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Simfqt service "
                                                    "has not been initialised");
    }
    assert (_simfqtServiceContext != NULL);

    SIMFQT_ServiceContext& lSIMFQT_ServiceContext = *_simfqtServiceContext;
  
    // Retrieve the STDAIR service object from the (SIMFQT) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lSIMFQT_ServiceContext.getSTDAIR_Service();

    // Delegate the BOM display to the dedicated service
    return lSTDAIR_Service.listAirportPairDateRange ();
  }

  // ////////////////////////////////////////////////////////////////////
  bool SIMFQT_Service::
  check (const stdair::AirportCode_T& iOrigin,
         const stdair::AirportCode_T& iDestination,
         const stdair::Date_T& iDepartureDate) const {
    std::ostringstream oFlightListStr;

    if (_simfqtServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The Simfqt service "
                                                    "has not been initialised");
    }
    assert (_simfqtServiceContext != NULL);
    SIMFQT_ServiceContext& lSIMFQT_ServiceContext = *_simfqtServiceContext;

    // Retrieve the STDAIR service object from the (SIMFQT) service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lSIMFQT_ServiceContext.getSTDAIR_Service();

    // Delegate the BOM display to the dedicated service
    return lSTDAIR_Service.check (iOrigin, iDestination, iDepartureDate);
  }

  // ////////////////////////////////////////////////////////////////////
  void SIMFQT_Service::
  quotePrices (const stdair::BookingRequestStruct& iBookingRequest,
               stdair::TravelSolutionList_T& ioTravelSolutionList) {
    
    // Retrieve the Simfqt service context
    if (_simfqtServiceContext == NULL) {
      throw stdair::NonInitialisedServiceException ("The SimFQT service "
                                                    "has not been initialised");
    }
    assert (_simfqtServiceContext != NULL);

    SIMFQT_ServiceContext& lSIMFQT_ServiceContext = *_simfqtServiceContext;

    // Retrieve the StdAir service context
    stdair::STDAIR_Service& lSTDAIR_Service =
      lSIMFQT_ServiceContext.getSTDAIR_Service();
    
    // Get the root of the BOM tree, on which all of the other BOM objects
    // will be attached
    stdair::BomRoot& lBomRoot = lSTDAIR_Service.getBomRoot();

    // Delegate the action to the dedicated command
    stdair::BasChronometer lFareQuoteRetrievalChronometer;
    lFareQuoteRetrievalChronometer.start();
    FareQuoter::priceQuote (iBookingRequest, ioTravelSolutionList, lBomRoot);

    // DEBUG
    const double lFareQuoteRetrievalMeasure =
      lFareQuoteRetrievalChronometer.elapsed();
    STDAIR_LOG_DEBUG ("Fare Quote retrieving: " << lFareQuoteRetrievalMeasure
                      << " - " << lSIMFQT_ServiceContext.display());
  }
  
}
