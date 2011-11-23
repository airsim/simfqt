#ifndef __SIMFQT_CMD_FAREPARSERGRAMMAR_DEF_HPP
#define __SIMFQT_CMD_FAREPARSERGRAMMAR_DEF_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <vector>
#include <fstream>
// StdAir
#include <stdair/bom/BomRoot.hpp>
#include <stdair/basic/BasParserTypes.hpp>
// SIMFQT
#include <simfqt/command/FareParserHelper.hpp>


namespace SIMFQT {

  namespace FareParserHelper {

    // ///////////////////////////////////////////////////////////////////
    //
    //  Utility Parsers
    //
    // ///////////////////////////////////////////////////////////////////
    /** Namespaces. */
    namespace bsq = boost::spirit::qi;
    namespace bsa = boost::spirit::ascii;
    
    /** 1-digit-integer parser */
    stdair::int1_p_t int1_p;
    
    /** 2-digit-integer parser */
    stdair::uint2_p_t uint2_p;

    /** 4-digit-integer parser */
    stdair::uint4_p_t uint4_p;
    
    /** Up-to-4-digit-integer parser */
    stdair::uint1_4_p_t uint1_4_p;

    /** Time element parsers. */
    stdair::hour_p_t hour_p;
    stdair::minute_p_t minute_p;
    stdair::second_p_t second_p;

    /** Date element parsers. */
    stdair::year_p_t year_p;
    stdair::month_p_t month_p;
    stdair::day_p_t day_p;
        
    // //////////////////////////////////////////////////////////////////
    //  (Boost Spirit) Grammar Definition
    // //////////////////////////////////////////////////////////////////

    // //////////////////////////////////////////////////////////////////
    template <typename Iterator>
    FareRuleParser<Iterator>::FareRuleParser (stdair::BomRoot& ioBomRoot,
                                    FareRuleStruct& iofareRule) :
      FareRuleParser::base_type(start),
      _bomRoot(ioBomRoot), _fareRule(iofareRule) {

      start = *(comments | fare_rule);

      comments = (bsq::lexeme[bsq::repeat(2)[bsa::char_('/')]
                              >> +(bsa::char_ - bsq::eol)
                              >> bsq::eol]
                  | bsq::lexeme[bsa::char_('/') >>bsa::char_('*') 
                                >> +(bsa::char_ - bsa::char_('*')) 
                                >> bsa::char_('*') >> bsa::char_('/')]);

      fare_rule = fare_key
        >> +( ';' >> segment )
        >> fare_rule_end[doEndFare(_bomRoot, _fareRule)];

      fare_rule_end = bsa::char_(';');

      fare_key = fare_id
        >> ';' >> origin >> ';' >> destination
        >> ';' >> tripType
        >> ';' >> dateRangeStart >> ';' >> dateRangeEnd
        >> ';' >> timeRangeStart >> ';' >> timeRangeEnd
        >> ';' >> point_of_sale >>  ';' >> cabinCode >> ';' >> channel
        >> ';' >> advancePurchase >> ';' >> saturdayStay
        >> ';' >> changeFees >> ';' >> nonRefundable
        >> ';' >> minimumStay >> ';' >> fare;

      fare_id = uint1_4_p[storeFareId(_fareRule)];

      origin = bsq::repeat(3)[bsa::char_("A-Z")][storeOrigin(_fareRule)];
      
      destination =  
        bsq::repeat(3)[bsa::char_("A-Z")][storeDestination(_fareRule)];

      tripType =
        bsq::repeat(2)[bsa::char_("A-Z")][storeTripType(_fareRule)];
      
      dateRangeStart = date[storeDateRangeStart(_fareRule)];

      dateRangeEnd = date[storeDateRangeEnd(_fareRule)];
      
      date = bsq::lexeme
        [year_p[boost::phoenix::ref(_fareRule._itYear) = bsq::labels::_1]
        >> '-'
        >> month_p[boost::phoenix::ref(_fareRule._itMonth) = bsq::labels::_1]
        >> '-'
        >> day_p[boost::phoenix::ref(_fareRule._itDay) = bsq::labels::_1] ];

      timeRangeStart = time[storeStartRangeTime(_fareRule)];
      
      timeRangeEnd = time[storeEndRangeTime(_fareRule)];

      time =  bsq::lexeme
        [hour_p[boost::phoenix::ref(_fareRule._itHours) = bsq::labels::_1]
        >> ':'
        >> minute_p[boost::phoenix::ref(_fareRule._itMinutes) = bsq::labels::_1]      
        >> - (':' >> second_p[boost::phoenix::ref(_fareRule._itSeconds) = bsq::labels::_1]) ];
      
      point_of_sale = bsq::repeat(3)[bsa::char_("A-Z")][storePOS(_fareRule)];

      cabinCode = bsa::char_("A-Z")[storeCabinCode(_fareRule)];
            
      channel = bsq::repeat(2)[bsa::char_("A-Z")][storeChannel(_fareRule)];
      
      advancePurchase = uint1_4_p[storeAdvancePurchase(_fareRule)];

      saturdayStay = bsa::char_("A-Z")[storeSaturdayStay(_fareRule)];

      changeFees = bsa::char_("A-Z")[storeChangeFees(_fareRule)];

      nonRefundable = bsa::char_("A-Z")[storeNonRefundable(_fareRule)];
      
      minimumStay = uint1_4_p[storeMinimumStay(_fareRule)];

      fare = bsq::double_[storeFare(_fareRule)];
      
      segment = bsq::repeat(2)[bsa::char_("A-Z")][storeAirlineCode(_fareRule)]
        >> ';'
        >> bsq::repeat(1,bsq::inf)[bsa::char_("A-Z")][storeClass(_fareRule)];

    }
  }
    
}

#endif // __SIMFQT_CMD_FAREPARSERGRAMMAR_DEF_HPP
