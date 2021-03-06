#ifndef __SIMFQT_CMD_FAREPARSER_HPP
#define __SIMFQT_CMD_FAREPARSER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/command/CmdAbstract.hpp>
// SimFQT
#include <simfqt/SIMFQT_Types.hpp>

// Forward declarations.
namespace stdair {
  class BomRoot;
}

namespace SIMFQT {
  
  /** Class wrapping the parser entry point. */
  class FareParser : public stdair::CmdAbstract {
  public:
    /** Parses the CSV file describing the fares for the
        simulator, and generates the fare bom tree accordingly.
        @param const FareFilePath& The file-name of the CSV-formatted 
        fare input file.
        @param stdair::BomRoot& Root of the BOM tree. */
    static void fareRuleGeneration (const FareFilePath&, stdair::BomRoot&);
  };
}
#endif // __SIMFQT_CMD_FAREPARSER_HPP
