#ifndef __SIMFQT_SVC_SIMFQTSERVICECONTEXT_HPP
#define __SIMFQT_SVC_SIMFQTSERVICECONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Simfqt
#include <simfqt/SIMFQT_Types.hpp>
#include <simfqt/service/ServiceAbstract.hpp>

namespace SIMFQT {

  /** Class holding the context of the Simfqt services. */
  class SIMFQT_ServiceContext : public ServiceAbstract {
    friend class FacSimfqtServiceContext;
  public:
    // ///////// Getters //////////
    /** Get the Fare Quote system ID. */
    const FareQuoteID_T& getFareQuoteID () const {
      return _fareQuoteID;
    }

    
    // ///////// Setters //////////
    /** Set the Fare Quote system ID. */
    void setAirlineCode (const FareQuoteID_T& iFareQuoteID) {
      _fareQuoteID = iFareQuoteID;
    }


    // ///////// Display Methods //////////
    /** Display the short SIMFQT_ServiceContext content. */
    const std::string shortDisplay() const;
    
    /** Display the full SIMFQT_ServiceContext content. */
    const std::string display() const;

    
  private:
    // /////// Construction / initialisation ////////
    /** Constructors. */
    SIMFQT_ServiceContext ();
    SIMFQT_ServiceContext (const FareQuoteID_T&);
    SIMFQT_ServiceContext (const SIMFQT_ServiceContext&);

    /** Destructor. */
    ~SIMFQT_ServiceContext();

  private:
    // //////////// Attributes //////////////////
    /** Fare Quote system ID. */
    FareQuoteID_T _fareQuoteID;
  };

}
#endif // __SIMFQT_SVC_SIMFQTSERVICECONTEXT_HPP
