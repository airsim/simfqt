#ifndef __STDAIR_BOM_SEGMENTCABINSTRUCTURE_HPP
#define __STDAIR_BOM_SEGMENTCABINSTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStructureDummy.hpp>
#include <stdair/bom/BomContentDummy.hpp>
#include <stdair/bom/BookingClassStructure.hpp>

namespace stdair {
  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific SegmentCabin class (for instance,
      in the AIRSCHED library). */
  template <class BOM_CONTENT>
  class SegmentCabinStructure : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;
    friend class BomStructure;
    
  public:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM content type. */
    typedef BOM_CONTENT Content_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef typename BOM_CONTENT::BomKey_T BomKey_T;

    /** Definition allowing to retrieve the associated parent
        BOM structure type. */
    typedef typename BOM_CONTENT::Parent_T::BomStructure_T ParentBomStructure_T;

    /** Definition allowing to retrieve the  children type of the
        BOM_CONTENT. */
    typedef typename BOM_CONTENT::ContentChild_T ContentChild_T;
    
    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector <BookingClassStructure<ContentChild_T>,
                                BomStructureDummy> ChildrenBomTypeList_T;

    /** Definition allowing to retrieve the default children bom holder type. */
    typedef BomChildrenHolderImp<BomContentDummy> DefaultChildrenBomHolder_T;

    /** Definition allowing to retrive the  children bom holder type. */
    typedef BomChildrenHolderImp<ContentChild_T> ChildrenBomHolder_T;

    /** Define the associated leg-cabin holder type. */
    typedef BomChildrenHolderImp<typename BOM_CONTENT::LegCabinContent_T> LegCabinHolder_T;

  public:
    // /////////// Getters /////////////
    /** Get the (parent) SegmentDateStructure object. */
    ParentBomStructure_T* getSegmentDateStructurePtr() const {
      return _parent;
    }
    
    /** Get the (parent) SegmentDateStructure object. */
    ParentBomStructure_T& getSegmentDateStructure() const {
      assert (_parent != NULL);
      return *_parent;
    }
    
    /** Get the segment-date key. */
    const BomKey_T& getKey() const {
      assert (_content != NULL);
      return _content->getKey();
    }

    /** Get the list of segment-cabins. */
    const ChildrenBomHolder_T& getChildrenList() const {
      return *_childrenList;
    }

    /** Get the list of segment-cabins. */
    void getChildrenList (ChildrenBomHolder_T*& ioChildrenList) {
      ioChildrenList = _childrenList;
    }
    
  private:
    // /////////// Setters /////////////
    /** Set the (parent) SegmentDateStructure object. */
    void setSegmentDateStructure (ParentBomStructure_T& ioSegmentDateStructure) {
      _parent = &ioSegmentDateStructure;
    }
    
    /** Default children list setter. */
    void setChildrenList (DefaultChildrenBomHolder_T&) { }

    /** Set the segment-cabin children list. */
    void setChildrenList (ChildrenBomHolder_T& ioChildrenList) {
      _childrenList = &ioChildrenList;
    }

    /** Set the leg-cabin holder. */
    void setLegCabinHolder (LegCabinHolder_T& ioLegCabinHolder) {
      _legCabinHolder = &ioLegCabinHolder;
    }
    
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { 
      ioOut << toString() << std::endl;
    }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const { return describeKey(); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return getKey().toString(); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return getKey().toString(); }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    SegmentCabinStructure () : _parent (NULL), _content (NULL),
                               _childrenList (NULL), _legCabinHolder (NULL) { }
    SegmentCabinStructure (const SegmentCabinStructure&);

    /** Destructor. */
    virtual ~SegmentCabinStructure() { }

  private:
    // Attributes
    /** Parent segment-date. */
    ParentBomStructure_T* _parent;

    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;
    
    /** List of segment-cabins. */
    ChildrenBomHolder_T* _childrenList;

    /** Holder of associated leg-cabins. */
    LegCabinHolder_T* _legCabinHolder;
  };

}
#endif // __STDAIR_BOM_SEGMENTCABINSTRUCTURE_HPP
