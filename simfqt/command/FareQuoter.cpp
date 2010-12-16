// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/service/Logger.hpp>
// Simfqt
#include <simfqt/command/FareQuoter.hpp>

namespace SIMFQT {

  // //////////////////////////////////////////////////////////////////////
  Price_T FareQuoter::
  priceQuote (stdair::TravelSolutionList_T& ioTravelSolutionList) {

    Price_T oPrice = 1000.0;
    try { 

      // DEBUG
      STDAIR_LOG_DEBUG ("The price is " << oPrice
                        << " EUR for the travel request for the airline ");
    
    } catch (const std::exception& lStdError) {
      STDAIR_LOG_ERROR ("Error: " << lStdError.what());
      throw QuotingException();
    }

    return oPrice;
  }

}
