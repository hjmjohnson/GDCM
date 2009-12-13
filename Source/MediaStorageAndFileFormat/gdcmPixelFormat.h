/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef GDCMPIXELFORMAT_H
#define GDCMPIXELFORMAT_H

#include "gdcmTypes.h"
#include <iostream>
#include <assert.h>

namespace gdcm
{

/**
 * \brief PixelFormat
 * \note
 * By default the Pixel Type will be instanciated with the following
 * parameters:
 * - SamplesPerPixel : 1
 * - BitsAllocated : 8
 * - BitsStored : 8
 * - HighBit : 7
 * - PixelRepresentation : 0
 */
class GDCM_EXPORT PixelFormat
{
  friend class Bitmap;
  friend std::ostream& operator<<(std::ostream &_os, const PixelFormat &pf);
public:
  // When adding a type please add its dual type (its unsigned conterpart)
  typedef enum {
    UINT8,
    INT8,
    UINT12,
    INT12,
    UINT16,
    INT16,
    UINT32,  // For some DICOM files (RT or SC)
    INT32,   //                        "   "
    FLOAT16, // sure why not...
    FLOAT32, // good ol' 'float'
    FLOAT64, // aka 'double'
    UNKNOWN // aka BitsAllocated == 0 && PixelRepresentation == 0
  } ScalarType;

  // default cstor:
  explicit PixelFormat (
    unsigned short samplesperpixel = 1,
    unsigned short bitsallocated = 8,
    unsigned short bitsstored = 8,
    unsigned short highbit = 7,
    unsigned short pixelrepresentation = 0 ) :
  SamplesPerPixel(samplesperpixel),
  BitsAllocated(bitsallocated),
  BitsStored(bitsstored),
  HighBit(highbit),
  PixelRepresentation(pixelrepresentation) {}
  // helper, for the common case
  PixelFormat(ScalarType st);
  ~PixelFormat() {}

  // For transparency of use
  operator ScalarType() const { return GetScalarType(); }

  /// Samples Per Pixel
  unsigned short GetSamplesPerPixel() const;
  void SetSamplesPerPixel(unsigned short spp)
    {
    SamplesPerPixel = spp;
    }

  /// BitsAllocated
  unsigned short GetBitsAllocated() const
    {
    return BitsAllocated;
    }
  void SetBitsAllocated(unsigned short ba)
    {
    BitsAllocated = ba;
    }

  /// BitsStored
  unsigned short GetBitsStored() const
    {
    return BitsStored;
    }
  void SetBitsStored(unsigned short bs)
    {
    BitsStored = bs;
    }

  /// HighBit
  unsigned short GetHighBit() const
    {
    return HighBit;
    }
  void SetHighBit(unsigned short hb)
    {
    HighBit = hb;
    }

  /// PixelRepresentation
  unsigned short GetPixelRepresentation() const
    {
    assert( PixelRepresentation == 0
         || PixelRepresentation == 1 );
    return PixelRepresentation;
    }
  void SetPixelRepresentation(unsigned short pr)
    {
    assert( PixelRepresentation == 0
         || PixelRepresentation == 1 );
    PixelRepresentation = pr;
    }

  /// ScalarType does not take into account the sample per pixel
  ScalarType GetScalarType() const;
  // BUG: You need to call SetScalarType *before* SetSamplesPerPixel
  void SetScalarType(ScalarType st);
  const char *GetScalarTypeAsString() const;

  /// return the size of the pixel
  /// This is the number of words it would take to store one pixel
  /// \warning the return value takes into account the SamplesPerPixel
  /// \warning in the rare case when BitsAllocated == 12, the function
  /// assume word padding and value returned will be identical as if BitsAllocated == 16
  uint8_t GetPixelSize() const;

  /// Print
  void Print(std::ostream &os) const;

  /// return the min possible of the pixel
  int64_t GetMin() const;

  /// return the max possible of the pixel
  int64_t GetMax() const;

protected:
  /// When image with 24/24/23 was read, need to validate
  bool Validate();

private:
  // D 0028|0002 [US] [Samples per Pixel] [1]
  unsigned short SamplesPerPixel;
  // D 0028|0100 [US] [Bits Allocated] [8]
  unsigned short BitsAllocated;
  // D 0028|0101 [US] [Bits Stored] [8]
  unsigned short BitsStored;
  // D 0028|0102 [US] [High Bit] [7]
  unsigned short HighBit;
  // D 0028|0103 [US] [Pixel Representation] [0]
  unsigned short PixelRepresentation;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const PixelFormat &pf)
{
  pf.Print( os );
  return os;
}

} // end namespace gdcm

#endif //GDCMPIXELFORMAT_H

