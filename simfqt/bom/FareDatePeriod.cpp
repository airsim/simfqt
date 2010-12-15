// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/service/Logger.hpp>
// SIMFQT
#include <simfqt/bom/FareDatePeriod.hpp>

namespace SIMFQT {

  // ////////////////////////////////////////////////////////////////////
  FareDatePeriod::FareDatePeriod (const Key_T& iKey)
    : _key (iKey), _parent (NULL)  {
  }

  // ////////////////////////////////////////////////////////////////////
  FareDatePeriod::~FareDatePeriod () {
  }
  
  // ////////////////////////////////////////////////////////////////////
  std::string FareDatePeriod::toString() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }
}

