/* -*- c++ -*- */
/*
 * Copyright 2012, 2014 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

/*!
 * \page volk_16ic_deinterleave_16i_x2
 *
 * \b Overview
 *
 * Deinterleaves the complex 16 bit vector into I & Q vector data.
 *
 * <b>Dispatcher Prototype</b>
 * \code
 * void volk_16ic_deinterleave_16i_x2(int16_t* iBuffer, int16_t* qBuffer, const lv_16sc_t* complexVector, unsigned int num_points)
 * \endcode
 *
 * \b Inputs
 * \li complexVector: The complex input vector.
 * \li num_points: The number of complex data values to be deinterleaved.
 *
 * \b Outputs
 * \li iBuffer: The I buffer output data.
 * \li qBuffer: The Q buffer output data.
 *
 * \b Example
 * \code
 * int N = 10000;
 *
 * volk_16ic_deinterleave_16i_x2();
 *
 * volk_free(x);
 * volk_free(t);
 * \endcode
 */

#ifndef INCLUDED_volk_16ic_deinterleave_16i_x2_a_H
#define INCLUDED_volk_16ic_deinterleave_16i_x2_a_H

#include <inttypes.h>
#include <stdio.h>

#ifdef LV_HAVE_SSSE3
#include <tmmintrin.h>

static inline void
volk_16ic_deinterleave_16i_x2_a_ssse3(int16_t* iBuffer, int16_t* qBuffer, const lv_16sc_t* complexVector, unsigned int num_points)
{
  unsigned int number = 0;
  const int8_t* complexVectorPtr = (int8_t*)complexVector;
  int16_t* iBufferPtr = iBuffer;
  int16_t* qBufferPtr = qBuffer;

  __m128i iMoveMask1 = _mm_set_epi8(0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 13, 12, 9, 8, 5, 4, 1, 0);
  __m128i iMoveMask2 = _mm_set_epi8(13, 12, 9, 8, 5, 4, 1, 0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80);

  __m128i qMoveMask1 = _mm_set_epi8(0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 15, 14, 11, 10, 7, 6, 3, 2);
  __m128i qMoveMask2 = _mm_set_epi8(15, 14, 11, 10, 7, 6, 3, 2, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80);

  __m128i complexVal1, complexVal2, iOutputVal, qOutputVal;

  unsigned int eighthPoints = num_points / 8;

  for(number = 0; number < eighthPoints; number++){
    complexVal1 = _mm_load_si128((__m128i*)complexVectorPtr);  complexVectorPtr += 16;
    complexVal2 = _mm_load_si128((__m128i*)complexVectorPtr);  complexVectorPtr += 16;

    iOutputVal = _mm_or_si128( _mm_shuffle_epi8(complexVal1, iMoveMask1) , _mm_shuffle_epi8(complexVal2, iMoveMask2));
    qOutputVal = _mm_or_si128( _mm_shuffle_epi8(complexVal1, qMoveMask1) , _mm_shuffle_epi8(complexVal2, qMoveMask2));

    _mm_store_si128((__m128i*)iBufferPtr, iOutputVal);
    _mm_store_si128((__m128i*)qBufferPtr, qOutputVal);

    iBufferPtr += 8;
    qBufferPtr += 8;
  }

  number = eighthPoints * 8;
  int16_t* int16ComplexVectorPtr = (int16_t*)complexVectorPtr;
  for(; number < num_points; number++){
    *iBufferPtr++ = *int16ComplexVectorPtr++;
    *qBufferPtr++ = *int16ComplexVectorPtr++;
  }
}
#endif /* LV_HAVE_SSSE3 */

#ifdef LV_HAVE_SSE2
#include <emmintrin.h>

static inline void
volk_16ic_deinterleave_16i_x2_a_sse2(int16_t* iBuffer, int16_t* qBuffer, const lv_16sc_t* complexVector, unsigned int num_points)
{
  unsigned int number = 0;
  const int16_t* complexVectorPtr = (int16_t*)complexVector;
  int16_t* iBufferPtr = iBuffer;
  int16_t* qBufferPtr = qBuffer;
  __m128i complexVal1, complexVal2, iComplexVal1, iComplexVal2, qComplexVal1, qComplexVal2, iOutputVal, qOutputVal;
  __m128i lowMask = _mm_set_epi32(0x0, 0x0, 0xFFFFFFFF, 0xFFFFFFFF);
  __m128i highMask = _mm_set_epi32(0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0);

  unsigned int eighthPoints = num_points / 8;

  for(number = 0; number < eighthPoints; number++){
    complexVal1 = _mm_load_si128((__m128i*)complexVectorPtr);  complexVectorPtr += 8;
    complexVal2 = _mm_load_si128((__m128i*)complexVectorPtr);  complexVectorPtr += 8;

    iComplexVal1 = _mm_shufflelo_epi16(complexVal1, _MM_SHUFFLE(3,1,2,0));

    iComplexVal1 = _mm_shufflehi_epi16(iComplexVal1, _MM_SHUFFLE(3,1,2,0));

    iComplexVal1 = _mm_shuffle_epi32(iComplexVal1, _MM_SHUFFLE(3,1,2,0));

    iComplexVal2 = _mm_shufflelo_epi16(complexVal2, _MM_SHUFFLE(3,1,2,0));

    iComplexVal2 = _mm_shufflehi_epi16(iComplexVal2, _MM_SHUFFLE(3,1,2,0));

    iComplexVal2 = _mm_shuffle_epi32(iComplexVal2, _MM_SHUFFLE(2,0,3,1));

    iOutputVal = _mm_or_si128(_mm_and_si128(iComplexVal1, lowMask), _mm_and_si128(iComplexVal2, highMask));

    _mm_store_si128((__m128i*)iBufferPtr, iOutputVal);

    qComplexVal1 = _mm_shufflelo_epi16(complexVal1, _MM_SHUFFLE(2,0,3,1));

    qComplexVal1 = _mm_shufflehi_epi16(qComplexVal1, _MM_SHUFFLE(2,0,3,1));

    qComplexVal1 = _mm_shuffle_epi32(qComplexVal1, _MM_SHUFFLE(3,1,2,0));

    qComplexVal2 = _mm_shufflelo_epi16(complexVal2, _MM_SHUFFLE(2,0,3,1));

    qComplexVal2 = _mm_shufflehi_epi16(qComplexVal2, _MM_SHUFFLE(2,0,3,1));

    qComplexVal2 = _mm_shuffle_epi32(qComplexVal2, _MM_SHUFFLE(2,0,3,1));

    qOutputVal = _mm_or_si128(_mm_and_si128(qComplexVal1, lowMask), _mm_and_si128(qComplexVal2, highMask));

    _mm_store_si128((__m128i*)qBufferPtr, qOutputVal);

    iBufferPtr += 8;
    qBufferPtr += 8;
  }

  number = eighthPoints * 8;
  for(; number < num_points; number++){
    *iBufferPtr++ = *complexVectorPtr++;
    *qBufferPtr++ = *complexVectorPtr++;
  }
}
#endif /* LV_HAVE_SSE2 */

#ifdef LV_HAVE_GENERIC

static inline void
volk_16ic_deinterleave_16i_x2_generic(int16_t* iBuffer, int16_t* qBuffer, const lv_16sc_t* complexVector, unsigned int num_points)
{
  const int16_t* complexVectorPtr = (const int16_t*)complexVector;
  int16_t* iBufferPtr = iBuffer;
  int16_t* qBufferPtr = qBuffer;
  unsigned int number;
  for(number = 0; number < num_points; number++){
    *iBufferPtr++ = *complexVectorPtr++;
    *qBufferPtr++ = *complexVectorPtr++;
  }
}
#endif /* LV_HAVE_GENERIC */

#ifdef LV_HAVE_ORC

extern void
volk_16ic_deinterleave_16i_x2_a_orc_impl(int16_t* iBuffer, int16_t* qBuffer, const lv_16sc_t* complexVector, unsigned int num_points);
static inline void
volk_16ic_deinterleave_16i_x2_u_orc(int16_t* iBuffer, int16_t* qBuffer, const lv_16sc_t* complexVector, unsigned int num_points)
{
  volk_16ic_deinterleave_16i_x2_a_orc_impl(iBuffer, qBuffer, complexVector, num_points);
}
#endif /* LV_HAVE_ORC */

#endif /* INCLUDED_volk_16ic_deinterleave_16i_x2_a_H */
