#ifndef __SIMFQT_BAS_BASCOMPARSERTYPES_HPP
#define __SIMFQT_BAS_BASCOMPARSERTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost Spirit (Parsing)
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

namespace SIMFQT {

  // ///////////////////////////////////////////////////////////////////////
  //
  //  Definition of Basic Types
  //
  // ///////////////////////////////////////////////////////////////////////
    
  // The types of iterator, scanner and rule are then derived from
  // the parsing unit.
  typedef std::istreambuf_iterator<char> base_iterator_t;
  typedef boost::spirit::multi_pass<base_iterator_t> iterator_t;  
  

  // ///////////////////////////////////////////////////////////////////////
  //
  //  Parser related types
  //
  // ///////////////////////////////////////////////////////////////////////
  /** 1-digit-integer parser */
  typedef boost::spirit::qi::int_parser<unsigned int, 10, 1, 1> int1_p_t;
    
  /** 2-digit-integer parser */
  typedef boost::spirit::qi::uint_parser<unsigned int, 10, 2, 2> uint2_p_t;
    
  /** 4-digit-integer parser */
  typedef boost::spirit::qi::uint_parser<unsigned int, 10, 4, 4> uint4_p_t;

  /** Up-to-4-digit-integer parser */
  typedef boost::spirit::qi::uint_parser<unsigned int, 10, 1, 4> uint1_4_p_t;
   
}
#endif // __SIMFQT_BAS_BASCOMPARSERTYPES_HPP
