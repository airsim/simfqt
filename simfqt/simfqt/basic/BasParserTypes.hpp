#ifndef __SIMFQT_BAS_BASCOMPARSERTYPES_HPP
#define __SIMFQT_BAS_BASCOMPARSERTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <limits>
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
  typedef boost::spirit::qi::uint_parser<int, 10, 2, 2> uint2_p_t;
    
  /** 4-digit-integer parser */
  typedef boost::spirit::qi::uint_parser<int, 10, 4, 4> uint4_p_t;

  /** Up-to-4-digit-integer parser */
  typedef boost::spirit::qi::uint_parser<int, 10, 1, 4> uint1_4_p_t;

  /** Time parser. */
  template <int MIN = 0, int MAX = 0>
  struct date_time_element {
    unsigned int _value;

    // Constructors.
    date_time_element () { }
    date_time_element (const date_time_element& t)
      : _value (t._value) { }
    date_time_element (int i) : _value (i) { }
    void check () const {
      if (_value < MIN || _value > MAX) {
        STDAIR_LOG_ERROR ("The value: " << _value
                          << " is out of range ("
                          << MIN << ", " << MAX << ")");
        throw stdair::ParserException ();
      }
    }
  };
  
  typedef date_time_element<0, 23> hour_t;
  typedef date_time_element<0, 59> minute_t;
  typedef date_time_element<0, 59> second_t;
  typedef date_time_element<1900, 2100> year_t;
  typedef date_time_element<1, 12> month_t;
  typedef date_time_element<1, 31> day_t;
  typedef boost::spirit::qi::uint_parser<hour_t, 10, 2, 2> hour_p_t;
  typedef boost::spirit::qi::uint_parser<minute_t, 10, 2, 2> minute_p_t;
  typedef boost::spirit::qi::uint_parser<second_t, 10, 2, 2> second_p_t;
  typedef boost::spirit::qi::uint_parser<year_t, 10, 4, 4> year_p_t;
  typedef boost::spirit::qi::uint_parser<month_t, 10, 2, 2> month_p_t;
  typedef boost::spirit::qi::uint_parser<day_t, 10, 2, 2> day_p_t;
  

  template <int MIN, int MAX>
  inline date_time_element<MIN, MAX> operator* (const date_time_element<MIN, MAX>& h1, const date_time_element<MIN, MAX>& h2) {
    return date_time_element<MIN, MAX> (h1._value * h2._value);
  }
  template <int MIN, int MAX>
  inline date_time_element<MIN, MAX> operator+ (const date_time_element<MIN, MAX>& h1, const date_time_element<MIN, MAX>& h2) {
    return date_time_element<MIN, MAX> (h1._value + h2._value);
  }
}
#endif // __SIMFQT_BAS_BASCOMPARSERTYPES_HPP
