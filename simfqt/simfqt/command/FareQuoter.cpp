// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <exception>
// Simfqt
#include <simfqt/command/FareQuoter.hpp>
#include <simfqt/service/Logger.hpp>

namespace SIMFQT {

  // //////////////////////////////////////////////////////////////////////
  Price_T FareQuoter::
  priceQuote (const FareQuoteID_T& iFareQuoteID,
              const AirlineCode_T& iAirlineCode, const PartySize_T& iPartySize) {
    Price_T oPrice = 0.0;

    try {

      // DEBUG
      SIMFQT_LOG_DEBUG ("The price is " << oPrice
                        << " EUR for the travel request for the airline "
                        << iAirlineCode << " for " << iPartySize
                        << " passengers.");
    
    } catch (const std::exception& lStdError) {
      SIMFQT_LOG_ERROR ("Error: " << lStdError.what());
      throw QuotingException();
    }

    return oPrice;
  }

}
