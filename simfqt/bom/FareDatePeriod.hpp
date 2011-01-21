#ifndef __SIMFQT_BOM_FAREDATEPERIOD_HPP
#define __SIMFQT_BOM_FAREDATEPERIOD_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomAbstract.hpp>
// SIMFQT
#include <simfqt/bom/FareDatePeriodKey.hpp>
#include <simfqt/bom/FareDatePeriodTypes.hpp>

// Forward declaration
namespace stdair {
  template <typename BOM> class FacBom;
  class FacBomManager;
}

namespace SIMFQT {

  /** Class representing the actual attributes for a fare date-period. */
  class FareDatePeriod : public stdair::BomAbstract {
    template <typename BOM> friend class stdair::FacBom;
    friend class stdair::FacBomManager;

  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef FareDatePeriodKey Key_T;
  
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the  key. */
    const std::string describeKey() const { return _key.toString(); }

  public:
    // ////////// Getters ////////////
    const Key_T& getKey() const { return _key; }
    const stdair::DatePeriod_T& getDatePeriod() const {
      return _key.getDatePeriod();
    }
    stdair::BomAbstract* const getParent() const { return _parent; }
    const  stdair::HolderMap_T& getHolderMap() const { return _holderMap; }

  public:
    // ////////////// Business methods ///////////////
    /** Check if the given departure date is included in the departure period
        of the segment path. */
    bool isDepartureDateValid (const stdair::Date_T&) const;
    
  protected:
    /** Default constructors. */
    FareDatePeriod (const Key_T&);
    FareDatePeriod (const FareDatePeriod&);
    /** Destructor. */
    ~FareDatePeriod();

  protected:
    // Attributes
    Key_T _key;
    stdair::BomAbstract* _parent;
    stdair::HolderMap_T _holderMap;

  };

}
#endif // __SIMFQT_BOM_FAREDATEPERIOD_HPP

