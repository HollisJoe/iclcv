#ifndef ICL_INPLACE_LOGICAL_OP
#define ICL_INPLACE_LOGICAL_OP

#include <ICLFilter/InplaceOp.h>

namespace icl{
  
  /// Filter class for logical in-place operations  \ingroup INPLACE
  /** The InplaceLogicalOp class provides functionalities for
      arbitrary logical in-place operations on images. The operator
      can be set to implement a certain operation using a given
      optype value. Logical (non-bit-wise) operations result in 
      images of value 0 or 255.\n
      Operation list can be split into two sections: 
      
      - pure logical operations (AND OR XOR and NOT)
      - bit-wise operations (bit-wise-AND bit-wise-OR bit-wise-XOR and bit-wise-NOT)
      
      Pure Logical operations are available for all types; bit-wise operations
      make no sense on floating point data, hence these operations are available
      for integer types only.
      
      Supported operator types (implementation on pixel value P and operator value
      V in braces)
      - <b>andOp</b> "logical and" ((P&&V)*255)
      - <b>orOp</b> "logical or" ((P||V)*255)
      - <b>xorOp</b> "logical and" ((!!P xor !!V)*255)
      - <b>notOp</b> "logical not" ((!P)*255) operator value is not used in this case
      - <b>binAndOp</b> "binary and" (P&V) [integer types only]
      - <b>binOrOp</b> "binary or" ((P|V) [integer types only]
      - <b>binXorOp</b> "binary and" (P^V) [integer types only]
      - <b>binNotOp</b> "binary not" (~P) operator value is not used in this case
        [integer types only]

      \section IPP-Optimization
      
      IPP-Optimization is possible, but not yet implemented.
      
  */
  class InplaceLogicalOp : public InplaceOp{
    public:

    enum optype{
      andOp=0,   ///< logical "and" 
      orOp=1,    ///< logical "or"
      xorOp=2,   ///< logical "xor" 
      notOp=3,   ///< logical "not" 
      binAndOp=4,///< binary "and" (for integer types only)
      binOrOp=5, ///< binary "or" (for integer types only)
      binXorOp=6,///< binary "xor" (for integer types only)
      binNotOp=7 ///< binary "not" (for integer types only)
    };

    
    /// Creates a new InplaceLogicalOp instance with given optype and value
    InplaceLogicalOp(optype t, icl64f value=0):
    m_eOpType(t),m_dValue(value){}
    
    /// applies this operation in-place on given source image
    virtual ImgBase *apply(ImgBase *src);
    
    /// returns current value
    icl64f getValue() const { return m_dValue; }
    
    /// set current value
    void setValue(icl64f val){ m_dValue = val; }
    
    /// returns current optype
    optype getOpType() const { return m_eOpType; }
    
    /// set current optype
    void setOpType(optype t) { m_eOpType = t; }
    
    private:
    
    /// optype
    optype m_eOpType;
    
    /// value
    icl64f m_dValue;
  };
}

#endif