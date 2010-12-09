// //////////////////////////////////////////////////////////////////////
#ifndef __SIMFQT_BOM_AIPRPORTPAIRTYPES_HPP
#define __SIMFQT_BOM_AIPRPORTPAIRTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// SIMFQT
#include <stdair/STDAIR_Types.hpp>

namespace SIMFQT {

  // Forward declarations.
  class AirportPair;
  
  /** Define the airport-pair list. */
  typedef std::list<AirportPair*> AirportPairList_T;

  /** Define the airport-pair map. */
  typedef std::map<const stdair::MapKey_T, AirportPair*> SegmentPeriodMap_T;

  /** Define the list of pair<MapKey_T, AirportPair>. */
  typedef std::pair<stdair::MapKey_T, AirportPair*> AirportPairWithKey_T;
  typedef std::list<AirportPairWithKey_T> AirportPairDetailedList_T;
}
#endif // __SIMFQT_BOM_AIPRPORTPAIRTYPES_HPP

