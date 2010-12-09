// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/factory/FacBomManager.hpp>
#include <stdair/service/Logger.hpp>
// SIMFQT
#include <simfqt/bom/FareRuleStruct.hpp>
#include <simfqt/bom/AirportPair.hpp>
#include <simfqt/command/FareRuleGenerator.hpp>

namespace SIMFQT {

  // //////////////////////////////////////////////////////////////////////
  void FareRuleGenerator::
  createFareRule (stdair::BomRoot& ioBomRoot,
                  const FareRuleStruct& iFareRuleStruct) {

    // Set the segment-period primary key.
    const stdair::AirportCode_T& lBoardPoint = iFareRuleStruct._origin;
    const stdair::AirportCode_T& lOffPoint = iFareRuleStruct._destination;
    const AirportPairKey lAirportPairKey (lBoardPoint, lOffPoint);
  
    // If the AirportPairKey object corresponding to the fare rule set
    // having the same origin and destination airport does not exist, create
    // it and link it to the ioBomRoot object.
    AirportPair* lAirportPair_ptr = stdair::BomManager::
      getObjectPtr<AirportPair> (ioBomRoot, lAirportPairKey.toString());
    if (lAirportPair_ptr == NULL) {
      lAirportPair_ptr =
        &stdair::FacBom<AirportPair>::instance().create (lAirportPairKey);
      stdair::FacBomManager::
        instance().addToListAndMap (ioBomRoot, *lAirportPair_ptr);
      stdair::FacBomManager::
      instance().linkWithParent (ioBomRoot, *lAirportPair_ptr);
    }
    assert (lAirportPair_ptr != NULL);

    const stdair::Date_T& lDateRangeStart = iFareRuleStruct._dateRangeStart;
    const stdair::Date_T& lDateRangeEnd = iFareRuleStruct._dateRangeEnd;
    const stdair::DatePeriod_T lDatePeriod (lDateRangeStart, lDateRangeEnd);

    // const stdair::AirlineCode_T& lPos = iFareRuleStruct._pos;
    // const stdair::Duration_T& lTimeRangeStart = iFareRuleStruct._timeRangeStart;
    const stdair::Duration_T& lTimeRangeEnd = iFareRuleStruct._timeRangeEnd;
    const stdair::AirlineCode_T& lPos = iFareRuleStruct._pos;
    const stdair::ChannelLabel_T& lChannel = iFareRuleStruct._channel;
    const stdair::DayDuration_T& lAdvancePurchase = iFareRuleStruct._advancePurchase;
    const stdair::SaturdayStay_T& lSaturdayStay =iFareRuleStruct._saturdayStay;
    const stdair::ChangeFees_T& lChangeFees = iFareRuleStruct._changeFees;
    const stdair::NonRefundable_T& lNonRefundable = iFareRuleStruct._nonRefundable;
    const stdair::DayDuration_T& lMinimumStay = iFareRuleStruct._minimumStay;
    const stdair::Fare_T& lFare = iFareRuleStruct._fare;
    
  }
        
}
