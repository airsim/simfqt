#ifndef __SIMFQT_SVC_SIMFQT_SERVICE_HPP
#define __SIMFQT_SVC_SIMFQT_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/BasLogParams.hpp>
// SimFQT
#include <simfqt/SIMFQT_Types.hpp>

namespace SIMFQT {

  // Forward declaration
  class SIMFQT_ServiceContext;

  
  /** Interface for the SIMFQT Services. */
  class SIMFQT_Service {
  public:
    // /////////// Business Methods /////////////
    /** Perform a price quotation for the travel request. */
    Price_T priceQuote (const AirlineCode_T&, const PartySize_T&);

    
    // ////////// Constructors and destructors //////////
    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        <br>Moreover, a reference on an output stream is given, so
        that log outputs can be directed onto that stream.       
        @param const stdair::BasLogParams& Parameters for the output log stream.
        @param FareQuoteID_T& ID of the Fare Quote system. */
    SIMFQT_Service (const stdair::BasLogParams&, const FareQuoteID_T&);

    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        <br>Moreover, as no reference on any output stream is given,
        it is assumed that the StdAir log service has already been
        initialised with the proper log output stream by some other
        methods in the calling chain (for instance, when the AIRINV_Service
        is itself being initialised by another library service such as
        SIMCRS_Service).
        @param FareQuoteID_T& ID of the Fare Quote system. */
    SIMFQT_Service (const FareQuoteID_T&);

    /** Destructor. */
    ~SIMFQT_Service();

    
  private:
    // /////// Construction and Destruction helper methods ///////
    /** Default constructor. */
    SIMFQT_Service ();
    /** Default copy constructor. */
    SIMFQT_Service (const SIMFQT_Service&);

    /** Initialise the log. */
    void logInit (const stdair::BasLogParams&);

    /** Initialise.
        @param const FareQuoteID_T& ID of the owner of the FareQuote system. */
    void init (const FareQuoteID_T&);

    /** Finalise. */
    void finalise ();

    
  private:
    // ///////// Service Context /////////
    /** Simfqt context. */
    SIMFQT_ServiceContext* _simfqtServiceContext;
  };
}
#endif // __SIMFQT_SVC_SIMFQT_SERVICE_HPP
