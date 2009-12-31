// STL
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
// SIMFQT
#include <simfqt/SIMFQT_Service.hpp>
#include <simfqt/config/simfqt-paths.hpp>

// ///////// M A I N ////////////
int main (int argc, char* argv[]) {

  try {
    
    // Airline code
    std::string lAirlineCode ("LH");
    
    // Number of passengers in the travelling group
    SIMFQT::PartySize_T lPartySize = 5;
    
    // Output log File
    std::string lLogFilename ("priceQuote.log");

    // Set the log parameters
    std::ofstream logOutputFile;
    // Open and clean the log outputfile
    logOutputFile.open (lLogFilename.c_str());
    logOutputFile.clear();
    
    // Initialise the list of classes/buckets
    SIMFQT::SIMFQT_Service simfqtService (logOutputFile, lAirlineCode);

    // Perform a price quotation
    simfqtService.priceQuote (lAirlineCode, lPartySize);
    
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;	
}
