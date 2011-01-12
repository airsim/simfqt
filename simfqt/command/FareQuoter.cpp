// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <ostream>
// StdAir
#include <stdair/basic/BasParserTypes.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/factory/FacBomManager.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/bom/key_types.hpp>
// SIMFQT
#include <simfqt/command/FareQuoter.hpp>
#include <simfqt/bom/AirportPair.hpp>

namespace SIMFQT {  

  // //////////////////////////////////////////////////////////////////////  
  template <typename ITERATOR>
  const bool parseSegmentDateKey(ITERATOR iFirst, 
				 ITERATOR iLast,
				 std::vector<std::string>& oResult) {

    const bool hasParsingBeenSuccesful = 
      boost::spirit::qi::phrase_parse(iFirst, iLast,
				      
		 // Begin grammar  
		 (
		 +(boost::spirit::ascii::char_ - boost::spirit::ascii::char_(',')) % ','
		 )
		 ,
		 // End grammar 

		 boost::spirit::ascii::space, oResult);

    // Fail if we did not get a full match
    if (iFirst != iLast) 
      return false;

    return hasParsingBeenSuccesful;
  }
  
  // //////////////////////////////////////////////////////////////////////
  void FareQuoter::
  priceQuote (stdair::TravelSolutionStruct& ioTravelSolution, 
	      stdair::BomRoot& iBomRoot) {

<<<<<<< HEAD
    Price_T lPrice = 1000.0;
    ioTravelSolution.setFare(lPrice);
    try { 

      // DEBUG
      STDAIR_LOG_DEBUG ("The price is " << lPrice
                        << " EUR for the travel request for the airline ");
    
=======
    try {   

      // Get the list of segment-date keys of the traval solution. 
      stdair::KeyList_T lSegmentDateKeyList = 
	ioTravelSolution.getSegmentDateKeyList();

      if (!lSegmentDateKeyList.empty()) { 
	// Get the first segment-date key of the traval solution. 
	std::string lFirstSegmentDateKey = lSegmentDateKeyList.front(); 

	// Parse the first segment-date key into a vector of strings.  
	std::vector<std::string> lResultParsing(4, " ");
	const bool hasParsingBeenSuccesful = 
	  parseSegmentDateKey(lFirstSegmentDateKey.begin(), 
			      lFirstSegmentDateKey.end(),
			      lResultParsing);

	if (hasParsingBeenSuccesful) {  

	  // Get the Airport pair string of the travel solution.
	  std::ostringstream lAirportPairStr; 
	  lAirportPairStr << lResultParsing.back() << std::endl; 

	  // Search for the fare rules having the same origin and destination 
	  // airport as the travel solution
	  const AirportPair* lAirportPair_ptr = stdair::BomManager::
	    getObjectPtr<AirportPair> (iBomRoot, lAirportPairStr.str());  
	  assert (lAirportPair_ptr != NULL); 

	  // Set a random price (for now) to the traval solution.
	  Price_T lPrice  = 600.0;
	  ioTravelSolution.setFare(lPrice);     
	
	  // DEBUG
	  STDAIR_LOG_DEBUG ("The price is " << lPrice
			    << " EUR for the travel request for the airline "
			    << lResultParsing.front());
	}

      }
     
>>>>>>> src
    } catch (const std::exception& lStdError) {
      STDAIR_LOG_ERROR ("Error: " << lStdError.what());
      throw QuotingException();
    }
<<<<<<< HEAD

=======
>>>>>>> src
  }
}
