#ifndef __SIMFQT_SVC_SIMFQT_SERVICE_HPP
#define __SIMFQT_SVC_SIMFQT_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// Simfqt
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
        @param std::ostream& Output log stream (for instance, std::cout)
        @param FareQuoteID_T& ID of the Fare Quote system. */
    SIMFQT_Service (std::ostream& ioLogStream, const FareQuoteID_T&);

    /** Destructor. */
    ~SIMFQT_Service();

    
  private:
    // /////// Construction and Destruction helper methods ///////
    /** Default constructor. */
    SIMFQT_Service ();
    /** Default copy constructor. */
    SIMFQT_Service (const SIMFQT_Service&);

    /** Initialise. */
    void init (std::ostream& ioLogStream, const FareQuoteID_T&);

    /** Finalise. */
    void finalise ();

    
  private:
    // ///////// Service Context /////////
    /** Simfqt context. */
    SIMFQT_ServiceContext* _simfqtServiceContext;
  };
}
#endif // __SIMFQT_SVC_SIMFQT_SERVICE_HPP
