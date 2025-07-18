/*
 * Copyright 1993-2024 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO LICENSEE:
 *
 * This source code and/or documentation ("Licensed Deliverables") are
 * subject to NVIDIA intellectual property rights under U.S. and
 * international Copyright laws.
 *
 * These Licensed Deliverables contained herein is PROPRIETARY and
 * CONFIDENTIAL to NVIDIA and is being provided under the terms and
 * conditions of a form of NVIDIA software license agreement by and
 * between NVIDIA and Licensee ("License Agreement") or electronically
 * accepted by Licensee.  Notwithstanding any terms or conditions to
 * the contrary in the License Agreement, reproduction or disclosure
 * of the Licensed Deliverables to any third party without the express
 * written consent of NVIDIA is prohibited.
 *
 * NOTWITHSTANDING ANY TERMS OR CONDITIONS TO THE CONTRARY IN THE
 * LICENSE AGREEMENT, NVIDIA MAKES NO REPRESENTATION ABOUT THE
 * SUITABILITY OF THESE LICENSED DELIVERABLES FOR ANY PURPOSE.  IT IS
 * PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY OF ANY KIND.
 * NVIDIA DISCLAIMS ALL WARRANTIES WITH REGARD TO THESE LICENSED
 * DELIVERABLES, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY,
 * NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * NOTWITHSTANDING ANY TERMS OR CONDITIONS TO THE CONTRARY IN THE
 * LICENSE AGREEMENT, IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY
 * SPECIAL, INDIRECT, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, OR ANY
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THESE LICENSED DELIVERABLES.
 *
 * U.S. Government End Users.  These Licensed Deliverables are a
 * "commercial item" as that term is defined at 48 C.F.R. 2.101 (OCT
 * 1995), consisting of "commercial computer software" and "commercial
 * computer software documentation" as such terms are used in 48
 * C.F.R. 12.212 (SEPT 1995) and is provided to the U.S. Government
 * only as a commercial end item.  Consistent with 48 C.F.R.12.212 and
 * 48 C.F.R. 227.7202-1 through 227.7202-4 (JUNE 1995), all
 * U.S. Government End Users acquire the Licensed Deliverables with
 * only those rights set forth herein.
 *
 * Any use of the Licensed Deliverables in individual and commercial
 * software must include, in the user documentation and internal
 * comments to the code, the above Disclaimer and U.S. Government End
 * Users Notice.
 */

#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#if defined(_MSC_VER)
#pragma message("crt/device_functions.h is an internal header file and must not be used directly.  Please use cuda_runtime_api.h or cuda_runtime.h instead.")
#else
#warning "crt/device_functions.h is an internal header file and must not be used directly.  Please use cuda_runtime_api.h or cuda_runtime.h instead."
#endif
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#define __UNDEF_CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS_DEVICE_FUNCTIONS_H__
#endif

#if !defined(__DEVICE_FUNCTIONS_H__)
#define __DEVICE_FUNCTIONS_H__

/*******************************************************************************
*                                                                              *
*                                                                              *
*                                                                              *
*******************************************************************************/

#if defined(__cplusplus) && defined(__CUDACC__)

#if defined(__CUDACC_RTC__)
#define __DEVICE_FUNCTIONS_DECL__ __device__ __cudart_builtin__
#define __DEVICE_FUNCTIONS_STATIC_DECL__ __device__ __cudart_builtin__
#define __DEVICE_HOST_FUNCTIONS_STATIC_DECL__ __device__ __host__ __cudart_builtin__
#else
#define __DEVICE_FUNCTIONS_DECL__ __device__ __cudart_builtin__
#define __DEVICE_FUNCTIONS_STATIC_DECL__ static __inline__ __device__ __cudart_builtin__
#define __DEVICE_HOST_FUNCTIONS_STATIC_DECL__ static __inline__ __device__ __host__ __cudart_builtin__
#endif /* __CUDACC_RTC__ */

#include "builtin_types.h"
#include "device_types.h"
#include "host_defines.h"


//NOTE: For NVRTC, these declarations have been moved into the compiler (to reduce compile time)
#define EXCLUDE_FROM_RTC

/*******************************************************************************
*                                                                              *
*                                                                              *
*                                                                              *
*******************************************************************************/

extern "C"
{
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Calculate the most significant 32 bits of the product of the two 32-bit integers.
 *
 * Calculate the most significant 32 bits of the 64-bit product \p x * \p y, where \p x and \p y
 * are 32-bit integers.
 *
 * \return Returns the most significant 32 bits of the product \p x * \p y.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ int                    __mulhi(int x, int y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Calculate the most significant 32 bits of the product of the two 32-bit unsigned integers.
 *
 * Calculate the most significant 32 bits of the 64-bit product \p x * \p y, where \p x and \p y
 * are 32-bit unsigned integers. 
 *
 * \return Returns the most significant 32 bits of the product \p x * \p y.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __umulhi(unsigned int x, unsigned int y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Calculate the most significant 64 bits of the product of the two 64-bit integers.
 *
 * Calculate the most significant 64 bits of the 128-bit product \p x * \p y, where \p x and \p y
 * are 64-bit integers. 
 *
 * \return Returns the most significant 64 bits of the product \p x * \p y.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ long long int          __mul64hi(long long int x, long long int y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Calculate the most significant 64 bits of the product of the two 64 unsigned bit integers.
 *
 * Calculate the most significant 64 bits of the 128-bit product \p x * \p y, where \p x and \p y
 * are 64-bit unsigned integers. 
 *
 * \return Returns the most significant 64 bits of the product \p x * \p y.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned long long int __umul64hi(unsigned long long int x, unsigned long long int y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Reinterpret bits in an integer as a float.
 *
 * Reinterpret the bits in the signed integer value \p x as a single-precision
 * floating-point value.
 * \return Returns reinterpreted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __int_as_float(int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Reinterpret bits in a float as a signed integer.
 *
 * Reinterpret the bits in the single-precision floating-point value \p x
 * as a signed integer.
 * \return Returns reinterpreted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ int                    __float_as_int(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Reinterpret bits in an unsigned integer as a float.
 *
 * Reinterpret the bits in the unsigned integer value \p x as a single-precision
 * floating-point value.
 * \return Returns reinterpreted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __uint_as_float(unsigned int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Reinterpret bits in a float as a unsigned integer.
 *
 * Reinterpret the bits in the single-precision floating-point value \p x
 * as a unsigned integer.
 * \return Returns reinterpreted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __float_as_uint(float x);
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ void                   __syncthreads(void);
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ void                   __prof_trigger(int);
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ void                   __threadfence(void);
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ void                   __threadfence_block(void);
__DEVICE_FUNCTIONS_DECL__ 
#if defined(__GNUC__) || defined(__CUDACC_RTC__)
__attribute__((__noreturn__))
#elif defined(_MSC_VER)
__declspec(noreturn)
#endif  /* defined(__GNUC__) || defined(__CUDACC_RTC__) */
__device_builtin__ void                   __trap(void);
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ void                   __brkpt();
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Clamp the input argument to [+0.0, 1.0].
 *
 * Clamp the input argument \p x to be within the interval [+0.0, 1.0].
 * \return 
 * - __saturatef(\p x) returns +0 if \cuda_math_formula x \le 0 \end_cuda_math_formula.
 * - __saturatef(\p x) returns 1 if \cuda_math_formula x \ge 1 \end_cuda_math_formula.
 * - __saturatef(\p x) returns \p x if \cuda_math_formula 0 < x < 1 \end_cuda_math_formula.
 * - __saturatef(NaN) returns +0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __saturatef(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Calculate 
 * \cuda_math_formula |x - y| + z \end_cuda_math_formula
 * , the sum of absolute difference.
 *
 * Calculate 
 * \cuda_math_formula |x - y| + z \end_cuda_math_formula
 * , the 32-bit sum of the third argument \p z plus and the absolute 
 * value of the difference between the first argument, \p x, and second 
 * argument, \p y.
 * 
 * Inputs \p x and \p y are signed 32-bit integers, input \p z is 
 * a 32-bit unsigned integer.
 *
 * \return Returns 
 * \cuda_math_formula |x - y| + z \end_cuda_math_formula.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __sad(int x, int y, unsigned int z);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Calculate 
 * \cuda_math_formula |x - y| + z \end_cuda_math_formula
 * , the sum of absolute difference.
 *
 * Calculate 
 * \cuda_math_formula |x - y| + z \end_cuda_math_formula
 * , the 32-bit sum of the third argument \p z plus and the absolute 
 * value of the difference between the first argument, \p x, and second 
 * argument, \p y.
 * 
 * Inputs \p x, \p y, and \p z are unsigned 32-bit integers.
 * 
 * \return Returns 
 * \cuda_math_formula |x - y| + z \end_cuda_math_formula.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __usad(unsigned int x, unsigned int y, unsigned int z);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Calculate the least significant 32 bits of the product of the least significant 24 bits of two integers.
 *
 * Calculate the least significant 32 bits of the product of the least significant 24 bits of \p x and \p y.
 * The high order 8 bits of \p x and \p y are ignored.
 *
 * \return Returns the least significant 32 bits of the product \p x * \p y.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ int                    __mul24(int x, int y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Calculate the least significant 32 bits of the product of the least significant 24 bits of two unsigned integers.
 *
 * Calculate the least significant 32 bits of the product of the least significant 24 bits of \p x and \p y.
 * The high order 8 bits of  \p x and  \p y are ignored. 
 *
 * \return Returns the least significant 32 bits of the product \p x * \p y.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __umul24(unsigned int x, unsigned int y);
/**
 * \ingroup CUDA_MATH_SINGLE
 * \brief Divide two floating-point values.
 *
 * Compute \p x divided by \p y.
 *
 * \return Returns \p x / \p y.
 * - Follows the regular division operation behavior by default.
 * - If \p -use_fast_math is specified and is not amended by
 * an explicit \p -prec_div=true, uses ::__fdividef() for higher
 * performance
 *
 * \note_accuracy_single
 * \note_fastmath
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  fdividef(float x, float y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Calculate the fast approximate division of the input arguments.
 *
 * Calculate the fast approximate division of \p x by \p y.
 *
 * \return Returns \p x / \p y.
 * - __fdividef(
 * \cuda_math_formula \infty \end_cuda_math_formula
 * , \p y) returns NaN for 
 * \cuda_math_formula 2^{126} < |y| < 2^{128} \end_cuda_math_formula.
 * - __fdividef(\p x, \p y) returns 0 for 
 * \cuda_math_formula 2^{126} < |y| < 2^{128} \end_cuda_math_formula
 *  and finite
 * \cuda_math_formula x \end_cuda_math_formula.
 * \see __fdiv_rn() for further special case behavior specification.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fdividef(float x, float y);
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ double                 fdivide(double x, double y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Calculate the fast approximate sine of the input argument.
 *
 * Calculate the fast approximate sine of the input argument \p x, measured in radians.
 *
 * \return Returns the approximate sine of \p x.
 *
 * \see sinf() for further special case behavior specification.
 * \note_accuracy_single_intrinsic
 * \note Output in the denormal range is flushed to sign preserving 0.0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ __cudart_builtin__ float                  __sinf(float x) __THROW;
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Calculate the fast approximate cosine of the input argument.
 *
 * Calculate the fast approximate cosine of the input argument \p x, measured in radians.
 *
 * \return Returns the approximate cosine of \p x.
 *
 * \see cosf() for further special case behavior specification.
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ __cudart_builtin__ float                  __cosf(float x) __THROW;
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Calculate the fast approximate tangent of the input argument.
 *
 * Calculate the fast approximate tangent of the input argument \p x, measured in radians.
 *
 * \return Returns the approximate tangent of \p x.
 *
 * \note_accuracy_single_intrinsic
 * \note The result is computed as the fast divide of ::__sinf()
 * by ::__cosf(). Denormal output is flushed to sign-preserving 0.0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ __cudart_builtin__ float                  __tanf(float x) __THROW;
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Calculate the fast approximate hyperbolic tangent of the input argument.
 *
 * Calculate the fast approximate hyperbolic tangent of the input argument \p x, measured in radians.
 *
 * \return Returns the approximate hyperbolic tangent of \p x.
 *
 * \see tanhf() for further special case behavior specification.
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ __cudart_builtin__ float                  __tanhf(float x) __THROW;
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Calculate the fast approximate of sine and cosine of the first input argument.
 *
 * Calculate the fast approximate of sine and cosine of the first input argument \p x (measured
 * in radians). The results for sine and cosine are written into the second 
 * argument, \p sptr, and, respectively, third argument, \p cptr.
 *
 * \see __sinf() and __cosf().
 * \note_accuracy_single_intrinsic
 * \note Denorm input/output is flushed to sign preserving 0.0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ __cudart_builtin__ void                   __sincosf(float x, float *sptr, float *cptr) __THROW;
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Calculate the fast approximate base 
 * \cuda_math_formula e \end_cuda_math_formula
 *  exponential of the input argument.
 *
 * Calculate the fast approximate base 
 * \cuda_math_formula e \end_cuda_math_formula
 *  exponential of the input argument \p x, 
 * \cuda_math_formula e^x \end_cuda_math_formula.
 *
 * \return Returns an approximation to 
 * \cuda_math_formula e^x \end_cuda_math_formula.
 * \see expf() for further special case behavior specification.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ __cudart_builtin__ float                  __expf(float x) __THROW;
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Calculate the fast approximate base 10 exponential of the input argument.
 *
 * Calculate the fast approximate base 10 exponential of the input argument \p x, 
 * \cuda_math_formula 10^x \end_cuda_math_formula.
 *
 * \return Returns an approximation to 
 * \cuda_math_formula 10^x \end_cuda_math_formula.
 * \see exp10f() for further special case behavior specification.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ __cudart_builtin__ float                  __exp10f(float x) __THROW;
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Calculate the fast approximate base 2 logarithm of the input argument.
 *
 * Calculate the fast approximate base 2 logarithm of the input argument \p x.
 *
 * \return Returns an approximation to 
 * \cuda_math_formula \log_2(x) \end_cuda_math_formula.
 * \see log2f() for further special case behavior specification.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ __cudart_builtin__ float                  __log2f(float x) __THROW;
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Calculate the fast approximate base 10 logarithm of the input argument.
 *
 * Calculate the fast approximate base 10 logarithm of the input argument \p x.
 *
 * \return Returns an approximation to 
 * \cuda_math_formula \log_{10}(x) \end_cuda_math_formula.
 * \see log10f() for further special case behavior specification.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ __cudart_builtin__ float                  __log10f(float x) __THROW;
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Calculate the fast approximate base 
 * \cuda_math_formula e \end_cuda_math_formula
 *  logarithm of the input argument.
 *
 * Calculate the fast approximate base 
 * \cuda_math_formula e \end_cuda_math_formula
 *  logarithm of the input argument \p x.
 *
 * \return Returns an approximation to 
 * \cuda_math_formula \log_e(x) \end_cuda_math_formula.
 * \see logf() for further special case behavior specification.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ __cudart_builtin__ float                  __logf(float x) __THROW;
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Calculate the fast approximate of 
 * \cuda_math_formula x^y \end_cuda_math_formula.
 *
 * Calculate the fast approximate of \p x, the first input argument, 
 * raised to the power of \p y, the second input argument, 
 * \cuda_math_formula x^y \end_cuda_math_formula.
 *
 * \return Returns an approximation to 
 * \cuda_math_formula x^y \end_cuda_math_formula.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ __cudart_builtin__ float                  __powf(float x, float y) __THROW;
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a float to a signed integer in round-to-nearest-even mode.
 *
 * Convert the single-precision floating-point value \p x to a signed integer
 * in round-to-nearest-even mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ int                    __float2int_rn(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a float to a signed integer in round-towards-zero mode.
 *
 * Convert the single-precision floating-point value \p x to a signed integer
 * in round-towards-zero mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ int                    __float2int_rz(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a float to a signed integer in round-up mode.
 *
 * Convert the single-precision floating-point value \p x to a signed integer
 * in round-up (to positive infinity) mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ int                    __float2int_ru(float);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a float to a signed integer in round-down mode.
 *
 * Convert the single-precision floating-point value \p x to a signed integer
 * in round-down (to negative infinity) mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ int                    __float2int_rd(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a float to an unsigned integer in round-to-nearest-even mode.
 *
 * Convert the single-precision floating-point value \p x to an unsigned integer
 * in round-to-nearest-even mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __float2uint_rn(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a float to an unsigned integer in round-towards-zero mode.
 *
 * Convert the single-precision floating-point value \p x to an unsigned integer
 * in round-towards-zero mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __float2uint_rz(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a float to an unsigned integer in round-up mode.
 *
 * Convert the single-precision floating-point value \p x to an unsigned integer
 * in round-up (to positive infinity) mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __float2uint_ru(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a float to an unsigned integer in round-down mode.
 *
 * Convert the single-precision floating-point value \p x to an unsigned integer
 * in round-down (to negative infinity) mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __float2uint_rd(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a signed integer to a float in round-to-nearest-even mode.
 *
 * Convert the signed integer value \p x to a single-precision floating-point value
 * in round-to-nearest-even mode.
 * \return Returns converted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __int2float_rn(int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a signed integer to a float in round-towards-zero mode.
 *
 * Convert the signed integer value \p x to a single-precision floating-point value
 * in round-towards-zero mode.
 * \return Returns converted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __int2float_rz(int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a signed integer to a float in round-up mode.
 *
 * Convert the signed integer value \p x to a single-precision floating-point value
 * in round-up (to positive infinity) mode.
 * \return Returns converted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __int2float_ru(int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a signed integer to a float in round-down mode.
 *
 * Convert the signed integer value \p x to a single-precision floating-point value
 * in round-down (to negative infinity) mode.
 * \return Returns converted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __int2float_rd(int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert an unsigned integer to a float in round-to-nearest-even mode.
 *
 * Convert the unsigned integer value \p x to a single-precision floating-point value
 * in round-to-nearest-even mode.
 * \return Returns converted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __uint2float_rn(unsigned int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert an unsigned integer to a float in round-towards-zero mode.
 *
 * Convert the unsigned integer value \p x to a single-precision floating-point value
 * in round-towards-zero mode.
 * \return Returns converted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __uint2float_rz(unsigned int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert an unsigned integer to a float in round-up mode.
 *
 * Convert the unsigned integer value \p x to a single-precision floating-point value
 * in round-up (to positive infinity) mode.
 * \return Returns converted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __uint2float_ru(unsigned int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert an unsigned integer to a float in round-down mode.
 *
 * Convert the unsigned integer value \p x to a single-precision floating-point value
 * in round-down (to negative infinity) mode.
 * \return Returns converted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __uint2float_rd(unsigned int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a float to a signed 64-bit integer in round-to-nearest-even mode.
 *
 * Convert the single-precision floating-point value \p x to a signed 64-bit integer
 * in round-to-nearest-even mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ long long int          __float2ll_rn(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a float to a signed 64-bit integer in round-towards-zero mode.
 *
 * Convert the single-precision floating-point value \p x to a signed 64-bit integer
 * in round-towards-zero mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ long long int          __float2ll_rz(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a float to a signed 64-bit integer in round-up mode.
 *
 * Convert the single-precision floating-point value \p x to a signed 64-bit integer
 * in round-up (to positive infinity) mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ long long int          __float2ll_ru(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a float to a signed 64-bit integer in round-down mode.
 *
 * Convert the single-precision floating-point value \p x to a signed 64-bit integer
 * in round-down (to negative infinity) mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ long long int          __float2ll_rd(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a float to an unsigned 64-bit integer in round-to-nearest-even mode.
 *
 * Convert the single-precision floating-point value \p x to an unsigned 64-bit integer
 * in round-to-nearest-even mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned long long int __float2ull_rn(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a float to an unsigned 64-bit integer in round-towards-zero mode.
 *
 * Convert the single-precision floating-point value \p x to an unsigned 64-bit integer
 * in round-towards-zero mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned long long int __float2ull_rz(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a float to an unsigned 64-bit integer in round-up mode.
 *
 * Convert the single-precision floating-point value \p x to an unsigned 64-bit integer
 * in round-up (to positive infinity) mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned long long int __float2ull_ru(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a float to an unsigned 64-bit integer in round-down mode.
 *
 * Convert the single-precision floating-point value \p x to an unsigned 64-bit integer
 * in round-down (to negative infinity) mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned long long int __float2ull_rd(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a signed 64-bit integer to a float in round-to-nearest-even mode.
 *
 * Convert the signed 64-bit integer value \p x to a single-precision floating-point value
 * in round-to-nearest-even mode.
 * \return Returns converted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __ll2float_rn(long long int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a signed integer to a float in round-towards-zero mode.
 *
 * Convert the signed integer value \p x to a single-precision floating-point value
 * in round-towards-zero mode.
 * \return Returns converted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __ll2float_rz(long long int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a signed integer to a float in round-up mode.
 *
 * Convert the signed integer value \p x to a single-precision floating-point value
 * in round-up (to positive infinity) mode.
 * \return Returns converted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __ll2float_ru(long long int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a signed integer to a float in round-down mode.
 *
 * Convert the signed integer value \p x to a single-precision floating-point value
 * in round-down (to negative infinity) mode.
 * \return Returns converted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __ll2float_rd(long long int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert an unsigned integer to a float in round-to-nearest-even mode.
 *
 * Convert the unsigned integer value \p x to a single-precision floating-point value
 * in round-to-nearest-even mode.
 * \return Returns converted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __ull2float_rn(unsigned long long int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert an unsigned integer to a float in round-towards-zero mode.
 *
 * Convert the unsigned integer value \p x to a single-precision floating-point value
 * in round-towards-zero mode.
 * \return Returns converted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __ull2float_rz(unsigned long long int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert an unsigned integer to a float in round-up mode.
 *
 * Convert the unsigned integer value \p x to a single-precision floating-point value
 * in round-up (to positive infinity) mode.
 * \return Returns converted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __ull2float_ru(unsigned long long int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert an unsigned integer to a float in round-down mode.
 *
 * Convert the unsigned integer value \p x to a single-precision floating-point value
 * in round-down (to negative infinity) mode.
 * \return Returns converted value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __ull2float_rd(unsigned long long int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Add two floating-point values in round-to-nearest-even mode.
 * 
 * Compute the sum of \p x and \p y in round-to-nearest-even rounding mode.
 *
 * \return Returns \p x + \p y.
 * - __fadd_rn(\p x, \p y) is equivalent to __fadd_rn(\p y, \p x).
 * - __fadd_rn(\p x, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \pm\infty \end_cuda_math_formula for finite \p x.
 * - __fadd_rn(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \pm\infty \end_cuda_math_formula.
 * - __fadd_rn(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \mp\infty \end_cuda_math_formula) returns NaN.
 * - __fadd_rn(\cuda_math_formula \pm 0 \end_cuda_math_formula, \cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fadd_rn(\p x, \p -x) returns \cuda_math_formula +0 \end_cuda_math_formula for finite \p x, including \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 * \note_nofma
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fadd_rn(float x, float y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Add two floating-point values in round-towards-zero mode.
 * 
 * Compute the sum of \p x and \p y in round-towards-zero mode.
 *
 * \return Returns \p x + \p y.
 * - __fadd_rz(\p x, \p y) is equivalent to __fadd_rz(\p y, \p x).
 * - __fadd_rz(\p x, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \pm\infty \end_cuda_math_formula for finite \p x.
 * - __fadd_rz(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \pm\infty \end_cuda_math_formula.
 * - __fadd_rz(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \mp\infty \end_cuda_math_formula) returns NaN.
 * - __fadd_rz(\cuda_math_formula \pm 0 \end_cuda_math_formula, \cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fadd_rz(\p x, \p -x) returns \cuda_math_formula +0 \end_cuda_math_formula for finite \p x, including \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 * \note_nofma
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fadd_rz(float x, float y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Add two floating-point values in round-up mode.
 * 
 * Compute the sum of \p x and \p y in round-up (to positive infinity) mode.
 *
 * \return Returns \p x + \p y.
 * - __fadd_ru(\p x, \p y) is equivalent to __fadd_ru(\p y, \p x).
 * - __fadd_ru(\p x, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \pm\infty \end_cuda_math_formula for finite \p x.
 * - __fadd_ru(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \pm\infty \end_cuda_math_formula.
 * - __fadd_ru(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \mp\infty \end_cuda_math_formula) returns NaN.
 * - __fadd_ru(\cuda_math_formula \pm 0 \end_cuda_math_formula, \cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fadd_ru(\p x, \p -x) returns \cuda_math_formula +0 \end_cuda_math_formula for finite \p x, including \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 * \note_nofma
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fadd_ru(float x, float y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Add two floating-point values in round-down mode.
 * 
 * Compute the sum of \p x and \p y in round-down (to negative infinity) mode.
 *
 * \return Returns \p x + \p y.
 * - __fadd_rd(\p x, \p y) is equivalent to __fadd_rd(\p y, \p x).
 * - __fadd_rd(\p x, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \pm\infty \end_cuda_math_formula for finite \p x.
 * - __fadd_rd(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \pm\infty \end_cuda_math_formula.
 * - __fadd_rd(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \mp\infty \end_cuda_math_formula) returns NaN.
 * - __fadd_rd(\cuda_math_formula \pm 0 \end_cuda_math_formula, \cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fadd_rd(\p x, \p -x) returns \cuda_math_formula -0 \end_cuda_math_formula for finite \p x, including \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 * \note_nofma
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fadd_rd(float x, float y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Subtract two floating-point values in round-to-nearest-even mode.
 * 
 * Compute the difference of \p x and \p y in round-to-nearest-even rounding mode.
 *
 * \return Returns \p x - \p y.
 * - __fsub_rn(\cuda_math_formula \pm\infty \end_cuda_math_formula, \p y) returns \cuda_math_formula \pm\infty \end_cuda_math_formula for finite \p y.
 * - __fsub_rn(\p x, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \mp\infty \end_cuda_math_formula for finite \p x.
 * - __fsub_rn(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns NaN.
 * - __fsub_rn(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \mp\infty \end_cuda_math_formula) returns \cuda_math_formula \pm\infty \end_cuda_math_formula.
 * - __fsub_rn(\cuda_math_formula \pm 0 \end_cuda_math_formula, \cuda_math_formula \mp 0 \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fsub_rn(\p x, \p x) returns \cuda_math_formula +0 \end_cuda_math_formula for finite \p x, including \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 * \note_nofma
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fsub_rn(float x, float y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Subtract two floating-point values in round-towards-zero mode.
 * 
 * Compute the difference of \p x and \p y in round-towards-zero mode.
 *
 * \return Returns \p x - \p y.
 * - __fsub_rz(\cuda_math_formula \pm\infty \end_cuda_math_formula, \p y) returns \cuda_math_formula \pm\infty \end_cuda_math_formula for finite \p y.
 * - __fsub_rz(\p x, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \mp\infty \end_cuda_math_formula for finite \p x.
 * - __fsub_rz(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns NaN.
 * - __fsub_rz(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \mp\infty \end_cuda_math_formula) returns \cuda_math_formula \pm\infty \end_cuda_math_formula.
 * - __fsub_rz(\cuda_math_formula \pm 0 \end_cuda_math_formula, \cuda_math_formula \mp 0 \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fsub_rz(\p x, \p x) returns \cuda_math_formula +0 \end_cuda_math_formula for finite \p x, including \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 * \note_nofma
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fsub_rz(float x, float y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Subtract two floating-point values in round-up mode.
 * 
 * Compute the difference of \p x and \p y in round-up (to positive infinity) mode.
 *
 * \return Returns \p x - \p y.
 * - __fsub_ru(\cuda_math_formula \pm\infty \end_cuda_math_formula, \p y) returns \cuda_math_formula \pm\infty \end_cuda_math_formula for finite \p y.
 * - __fsub_ru(\p x, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \mp\infty \end_cuda_math_formula for finite \p x.
 * - __fsub_ru(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns NaN.
 * - __fsub_ru(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \mp\infty \end_cuda_math_formula) returns \cuda_math_formula \pm\infty \end_cuda_math_formula.
 * - __fsub_ru(\cuda_math_formula \pm 0 \end_cuda_math_formula, \cuda_math_formula \mp 0 \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fsub_ru(\p x, \p x) returns \cuda_math_formula +0 \end_cuda_math_formula for finite \p x, including \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 * \note_nofma
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fsub_ru(float x, float y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Subtract two floating-point values in round-down mode.
 * 
 * Compute the difference of \p x and \p y in round-down (to negative infinity) mode.
 *
 * \return Returns \p x - \p y.
 * - __fsub_rd(\cuda_math_formula \pm\infty \end_cuda_math_formula, \p y) returns \cuda_math_formula \pm\infty \end_cuda_math_formula for finite \p y.
 * - __fsub_rd(\p x, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \mp\infty \end_cuda_math_formula for finite \p x.
 * - __fsub_rd(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns NaN.
 * - __fsub_rd(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \mp\infty \end_cuda_math_formula) returns \cuda_math_formula \pm\infty \end_cuda_math_formula.
 * - __fsub_rd(\cuda_math_formula \pm 0 \end_cuda_math_formula, \cuda_math_formula \mp 0 \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fsub_rd(\p x, \p x) returns \cuda_math_formula -0 \end_cuda_math_formula for finite \p x, including \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 * \note_nofma
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fsub_rd(float x, float y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Multiply two floating-point values in round-to-nearest-even mode.
 * 
 * Compute the product of \p x and \p y in round-to-nearest-even mode.
 *
 * \return Returns \p x * \p y.
 * - sign of the product \p x * \p y is XOR of the signs of \p x and \p y when neither inputs nor result are NaN.
 * - __fmul_rn(\p x, \p y) is equivalent to __fmul_rn(\p y, \p x).
 * - __fmul_rn(\p x, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \infty \end_cuda_math_formula of appropriate sign for \p x \cuda_math_formula \neq 0 \end_cuda_math_formula.
 * - __fmul_rn(\cuda_math_formula \pm 0 \end_cuda_math_formula, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns NaN.
 * - __fmul_rn(\cuda_math_formula \pm 0 \end_cuda_math_formula, \p y) returns \cuda_math_formula 0 \end_cuda_math_formula of appropriate sign for finite \p y.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 * \note_nofma
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fmul_rn(float x, float y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Multiply two floating-point values in round-towards-zero mode.
 * 
 * Compute the product of \p x and \p y in round-towards-zero mode.
 *
 * \return Returns \p x * \p y.
 * - sign of the product \p x * \p y is XOR of the signs of \p x and \p y when neither inputs nor result are NaN.
 * - __fmul_rz(\p x, \p y) is equivalent to __fmul_rz(\p y, \p x).
 * - __fmul_rz(\p x, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \infty \end_cuda_math_formula of appropriate sign for \p x \cuda_math_formula \neq 0 \end_cuda_math_formula.
 * - __fmul_rz(\cuda_math_formula \pm 0 \end_cuda_math_formula, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns NaN.
 * - __fmul_rz(\cuda_math_formula \pm 0 \end_cuda_math_formula, \p y) returns \cuda_math_formula 0 \end_cuda_math_formula of appropriate sign for finite \p y.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 * \note_nofma
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fmul_rz(float x, float y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Multiply two floating-point values in round-up mode.
 * 
 * Compute the product of \p x and \p y in round-up (to positive infinity) mode.
 *
 * \return Returns \p x * \p y.
 * - sign of the product \p x * \p y is XOR of the signs of \p x and \p y when neither inputs nor result are NaN.
 * - __fmul_ru(\p x, \p y) is equivalent to __fmul_ru(\p y, \p x).
 * - __fmul_ru(\p x, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \infty \end_cuda_math_formula of appropriate sign for \p x \cuda_math_formula \neq 0 \end_cuda_math_formula.
 * - __fmul_ru(\cuda_math_formula \pm 0 \end_cuda_math_formula, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns NaN.
 * - __fmul_ru(\cuda_math_formula \pm 0 \end_cuda_math_formula, \p y) returns \cuda_math_formula 0 \end_cuda_math_formula of appropriate sign for finite \p y.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 * \note_nofma
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fmul_ru(float x, float y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Multiply two floating-point values in round-down mode.
 * 
 * Compute the product of \p x and \p y in round-down (to negative infinity) mode.
 *
 * \return Returns \p x * \p y.
 * - sign of the product \p x * \p y is XOR of the signs of \p x and \p y when neither inputs nor result are NaN.
 * - __fmul_rd(\p x, \p y) is equivalent to __fmul_rd(\p y, \p x).
 * - __fmul_rd(\p x, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \infty \end_cuda_math_formula of appropriate sign for \p x \cuda_math_formula \neq 0 \end_cuda_math_formula.
 * - __fmul_rd(\cuda_math_formula \pm 0 \end_cuda_math_formula, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns NaN.
 * - __fmul_rd(\cuda_math_formula \pm 0 \end_cuda_math_formula, \p y) returns \cuda_math_formula 0 \end_cuda_math_formula of appropriate sign for finite \p y.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 * \note_nofma
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fmul_rd(float x, float y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Compute 
 * \cuda_math_formula x \times y + z \end_cuda_math_formula
 *  as a single operation, in round-to-nearest-even mode.
 * 
 * Computes the value of 
 * \cuda_math_formula x \times y + z \end_cuda_math_formula
 *  as a single ternary operation, rounding the
 * result once in round-to-nearest-even mode.
 *
 * \return Returns the rounded value of 
 * \cuda_math_formula x \times y + z \end_cuda_math_formula
 *  as a single operation.
 * - __fmaf_rn(
 * \cuda_math_formula \pm \infty \end_cuda_math_formula
 * , 
 * \cuda_math_formula \pm 0 \end_cuda_math_formula
 * , \p z) returns NaN.
 * - __fmaf_rn(
 * \cuda_math_formula \pm 0 \end_cuda_math_formula
 * , 
 * \cuda_math_formula \pm \infty \end_cuda_math_formula
 * , \p z) returns NaN.
 * - __fmaf_rn(\p x, \p y, 
 * \cuda_math_formula -\infty \end_cuda_math_formula
 * ) returns NaN if 
 * \cuda_math_formula x \times y \end_cuda_math_formula
 *  is an exact 
 * \cuda_math_formula +\infty \end_cuda_math_formula.
 * - __fmaf_rn(\p x, \p y, 
 * \cuda_math_formula +\infty \end_cuda_math_formula
 * ) returns NaN if 
 * \cuda_math_formula x \times y \end_cuda_math_formula
 *  is an exact 
 * \cuda_math_formula -\infty \end_cuda_math_formula.
 * - __fmaf_rn(\p x, \p y, \cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula if \cuda_math_formula x \times y \end_cuda_math_formula is exact \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fmaf_rn(\p x, \p y, \cuda_math_formula \mp 0 \end_cuda_math_formula) returns \cuda_math_formula +0 \end_cuda_math_formula if \cuda_math_formula x \times y \end_cuda_math_formula is exact \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fmaf_rn(\p x, \p y, \p z) returns \cuda_math_formula +0 \end_cuda_math_formula if \cuda_math_formula x \times y + z \end_cuda_math_formula is exactly zero and \cuda_math_formula z \neq 0 \end_cuda_math_formula.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fmaf_rn(float x, float y, float z);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Compute 
 * \cuda_math_formula x \times y + z \end_cuda_math_formula
 *  as a single operation, in round-towards-zero mode.
 * 
 * Computes the value of 
 * \cuda_math_formula x \times y + z \end_cuda_math_formula
 *  as a single ternary operation, rounding the
 * result once in round-towards-zero mode.
 *
 * \return Returns the rounded value of 
 * \cuda_math_formula x \times y + z \end_cuda_math_formula
 *  as a single operation.
 * - __fmaf_rz(
 * \cuda_math_formula \pm \infty \end_cuda_math_formula
 * , 
 * \cuda_math_formula \pm 0 \end_cuda_math_formula
 * , \p z) returns NaN.
 * - __fmaf_rz(
 * \cuda_math_formula \pm 0 \end_cuda_math_formula
 * , 
 * \cuda_math_formula \pm \infty \end_cuda_math_formula
 * , \p z) returns NaN.
 * - __fmaf_rz(\p x, \p y, 
 * \cuda_math_formula -\infty \end_cuda_math_formula
 * ) returns NaN if 
 * \cuda_math_formula x \times y \end_cuda_math_formula
 *  is an exact 
 * \cuda_math_formula +\infty \end_cuda_math_formula.
 * - __fmaf_rz(\p x, \p y, 
 * \cuda_math_formula +\infty \end_cuda_math_formula
 * ) returns NaN if 
 * \cuda_math_formula x \times y \end_cuda_math_formula
 *  is an exact 
 * \cuda_math_formula -\infty \end_cuda_math_formula.
 * - __fmaf_rz(\p x, \p y, \cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula if \cuda_math_formula x \times y \end_cuda_math_formula is exact \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fmaf_rz(\p x, \p y, \cuda_math_formula \mp 0 \end_cuda_math_formula) returns \cuda_math_formula +0 \end_cuda_math_formula if \cuda_math_formula x \times y \end_cuda_math_formula is exact \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fmaf_rz(\p x, \p y, \p z) returns \cuda_math_formula +0 \end_cuda_math_formula if \cuda_math_formula x \times y + z \end_cuda_math_formula is exactly zero and \cuda_math_formula z \neq 0 \end_cuda_math_formula.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fmaf_rz(float x, float y, float z);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Compute 
 * \cuda_math_formula x \times y + z \end_cuda_math_formula
 *  as a single operation, in round-up mode.
 * 
 * Computes the value of 
 * \cuda_math_formula x \times y + z \end_cuda_math_formula
 *  as a single ternary operation, rounding the
 * result once in round-up (to positive infinity) mode.
 *
 * \return Returns the rounded value of 
 * \cuda_math_formula x \times y + z \end_cuda_math_formula
 *  as a single operation.
 * - __fmaf_ru(
 * \cuda_math_formula \pm \infty \end_cuda_math_formula
 * , 
 * \cuda_math_formula \pm 0 \end_cuda_math_formula
 * , \p z) returns NaN.
 * - __fmaf_ru(
 * \cuda_math_formula \pm 0 \end_cuda_math_formula
 * , 
 * \cuda_math_formula \pm \infty \end_cuda_math_formula
 * , \p z) returns NaN.
 * - __fmaf_ru(\p x, \p y, 
 * \cuda_math_formula -\infty \end_cuda_math_formula
 * ) returns NaN if 
 * \cuda_math_formula x \times y \end_cuda_math_formula
 *  is an exact 
 * \cuda_math_formula +\infty \end_cuda_math_formula.
 * - __fmaf_ru(\p x, \p y, 
 * \cuda_math_formula +\infty \end_cuda_math_formula
 * ) returns NaN if 
 * \cuda_math_formula x \times y \end_cuda_math_formula
 *  is an exact 
 * \cuda_math_formula -\infty \end_cuda_math_formula.
 * - __fmaf_ru(\p x, \p y, \cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula if \cuda_math_formula x \times y \end_cuda_math_formula is exact \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fmaf_ru(\p x, \p y, \cuda_math_formula \mp 0 \end_cuda_math_formula) returns \cuda_math_formula +0 \end_cuda_math_formula if \cuda_math_formula x \times y \end_cuda_math_formula is exact \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fmaf_ru(\p x, \p y, \p z) returns \cuda_math_formula +0 \end_cuda_math_formula if \cuda_math_formula x \times y + z \end_cuda_math_formula is exactly zero and \cuda_math_formula z \neq 0 \end_cuda_math_formula.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fmaf_ru(float x, float y, float z);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Compute 
 * \cuda_math_formula x \times y + z \end_cuda_math_formula
 *  as a single operation, in round-down mode.
 * 
 * Computes the value of 
 * \cuda_math_formula x \times y + z \end_cuda_math_formula
 *  as a single ternary operation, rounding the
 * result once in round-down (to negative infinity) mode.
 *
 * \return Returns the rounded value of 
 * \cuda_math_formula x \times y + z \end_cuda_math_formula
 *  as a single operation.
 * - __fmaf_rd(
 * \cuda_math_formula \pm \infty \end_cuda_math_formula
 * , 
 * \cuda_math_formula \pm 0 \end_cuda_math_formula
 * , \p z) returns NaN.
 * - __fmaf_rd(
 * \cuda_math_formula \pm 0 \end_cuda_math_formula
 * , 
 * \cuda_math_formula \pm \infty \end_cuda_math_formula
 * , \p z) returns NaN.
 * - __fmaf_rd(\p x, \p y, 
 * \cuda_math_formula -\infty \end_cuda_math_formula
 * ) returns NaN if 
 * \cuda_math_formula x \times y \end_cuda_math_formula
 *  is an exact 
 * \cuda_math_formula +\infty \end_cuda_math_formula.
 * - __fmaf_rd(\p x, \p y, 
 * \cuda_math_formula +\infty \end_cuda_math_formula
 * ) returns NaN if 
 * \cuda_math_formula x \times y \end_cuda_math_formula
 *  is an exact 
 * \cuda_math_formula -\infty \end_cuda_math_formula.
 * - __fmaf_rd(\p x, \p y, \cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula if \cuda_math_formula x \times y \end_cuda_math_formula is exact \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fmaf_rd(\p x, \p y, \cuda_math_formula \mp 0 \end_cuda_math_formula) returns \cuda_math_formula -0 \end_cuda_math_formula if \cuda_math_formula x \times y \end_cuda_math_formula is exact \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fmaf_rd(\p x, \p y, \p z) returns \cuda_math_formula -0 \end_cuda_math_formula if \cuda_math_formula x \times y + z \end_cuda_math_formula is exactly zero and \cuda_math_formula z \neq 0 \end_cuda_math_formula.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fmaf_rd(float x, float y, float z);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Compute 
 * \cuda_math_formula \frac{1}{x} \end_cuda_math_formula
 *  in round-to-nearest-even mode.
 * 
 * Compute the reciprocal of \p x in round-to-nearest-even mode.
 *
 * \return Returns 
 * \cuda_math_formula \frac{1}{x} \end_cuda_math_formula.
 * - __frcp_rn(\cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \pm\infty \end_cuda_math_formula.
 * - __frcp_rn(\cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __frcp_rn(NaN) returns NaN.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __frcp_rn(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Compute 
 * \cuda_math_formula \frac{1}{x} \end_cuda_math_formula
 *  in round-towards-zero mode.
 * 
 * Compute the reciprocal of \p x in round-towards-zero mode.
 *
 * \return Returns 
 * \cuda_math_formula \frac{1}{x} \end_cuda_math_formula.
 * - __frcp_rz(\cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \pm\infty \end_cuda_math_formula.
 * - __frcp_rz(\cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __frcp_rz(NaN) returns NaN.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __frcp_rz(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Compute 
 * \cuda_math_formula \frac{1}{x} \end_cuda_math_formula
 *  in round-up mode.
 * 
 * Compute the reciprocal of \p x in round-up (to positive infinity) mode.
 *
 * \return Returns 
 * \cuda_math_formula \frac{1}{x} \end_cuda_math_formula.
 * - __frcp_ru(\cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \pm\infty \end_cuda_math_formula.
 * - __frcp_ru(\cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __frcp_ru(NaN) returns NaN.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __frcp_ru(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Compute 
 * \cuda_math_formula \frac{1}{x} \end_cuda_math_formula
 *  in round-down mode.
 * 
 * Compute the reciprocal of \p x in round-down (to negative infinity) mode.
 *
 * \return Returns 
 * \cuda_math_formula \frac{1}{x} \end_cuda_math_formula.
 * - __frcp_rd(\cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \pm\infty \end_cuda_math_formula.
 * - __frcp_rd(\cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __frcp_rd(NaN) returns NaN.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __frcp_rd(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Compute 
 * \cuda_math_formula \sqrt{x} \end_cuda_math_formula
 *  in round-to-nearest-even mode.
 * 
 * Compute the square root of \p x in round-to-nearest-even mode.
 *
 * \return Returns 
 * \cuda_math_formula \sqrt{x} \end_cuda_math_formula.
 * - __fsqrt_rn(\cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fsqrt_rn(\cuda_math_formula +\infty \end_cuda_math_formula) returns \cuda_math_formula +\infty \end_cuda_math_formula.
 * - __fsqrt_rn(\p x) returns NaN for \p x < 0.
 * - __fsqrt_rn(NaN) returns NaN.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fsqrt_rn(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Compute 
 * \cuda_math_formula \sqrt{x} \end_cuda_math_formula
 *  in round-towards-zero mode.
 * 
 * Compute the square root of \p x in round-towards-zero mode.
 *
 * \return Returns 
 * \cuda_math_formula \sqrt{x} \end_cuda_math_formula.
 * - __fsqrt_rz(\cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fsqrt_rz(\cuda_math_formula +\infty \end_cuda_math_formula) returns \cuda_math_formula +\infty \end_cuda_math_formula.
 * - __fsqrt_rz(\p x) returns NaN for \p x < 0.
 * - __fsqrt_rz(NaN) returns NaN.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fsqrt_rz(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Compute 
 * \cuda_math_formula \sqrt{x} \end_cuda_math_formula
 *  in round-up mode.
 * 
 * Compute the square root of \p x in round-up (to positive infinity) mode.
 *
 * \return Returns 
 * \cuda_math_formula \sqrt{x} \end_cuda_math_formula.
 * - __fsqrt_ru(\cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fsqrt_ru(\cuda_math_formula +\infty \end_cuda_math_formula) returns \cuda_math_formula +\infty \end_cuda_math_formula.
 * - __fsqrt_ru(\p x) returns NaN for \p x < 0.
 * - __fsqrt_ru(NaN) returns NaN.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fsqrt_ru(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Compute 
 * \cuda_math_formula \sqrt{x} \end_cuda_math_formula
 *  in round-down mode.
 * 
 * Compute the square root of \p x in round-down (to negative infinity) mode.
 *
 * \return Returns 
 * \cuda_math_formula \sqrt{x} \end_cuda_math_formula.
 * - __fsqrt_rd(\cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \pm 0 \end_cuda_math_formula.
 * - __fsqrt_rd(\cuda_math_formula +\infty \end_cuda_math_formula) returns \cuda_math_formula +\infty \end_cuda_math_formula.
 * - __fsqrt_rd(\p x) returns NaN for \p x < 0.
 * - __fsqrt_rd(NaN) returns NaN.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fsqrt_rd(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Compute
 * \cuda_math_formula 1/\sqrt{x} \end_cuda_math_formula
 *  in round-to-nearest-even mode.
 * 
 * Compute the reciprocal square root of \p x in round-to-nearest-even mode.
 *
 * \return Returns
 * \cuda_math_formula 1/\sqrt{x} \end_cuda_math_formula.
 * - __frsqrt_rn(\cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \pm\infty \end_cuda_math_formula.
 * - __frsqrt_rn(\cuda_math_formula +\infty \end_cuda_math_formula) returns \cuda_math_formula +0 \end_cuda_math_formula.
 * - __frsqrt_rn(\p x) returns NaN for \p x < 0.
 * - __frsqrt_rn(NaN) returns NaN.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __frsqrt_rn(float x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Divide two floating-point values in round-to-nearest-even mode.
 *
 * Divide two floating-point values \p x by \p y in round-to-nearest-even mode.
 *
 * \return Returns \p x / \p y.
 * - sign of the quotient \p x / \p y is XOR of the signs of \p x and \p y when neither inputs nor result are NaN.
 * - __fdiv_rn(\cuda_math_formula \pm 0 \end_cuda_math_formula, \cuda_math_formula \pm 0 \end_cuda_math_formula) returns NaN.
 * - __fdiv_rn(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns NaN.
 * - __fdiv_rn(\p x, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula 0 \end_cuda_math_formula of appropriate sign for finite \p x.
 * - __fdiv_rn(\cuda_math_formula \pm\infty \end_cuda_math_formula, \p y) returns \cuda_math_formula \infty \end_cuda_math_formula of appropriate sign for finite \p y.
 * - __fdiv_rn(\p x, \cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \infty \end_cuda_math_formula of appropriate sign for \p x \cuda_math_formula \neq 0 \end_cuda_math_formula.
 * - __fdiv_rn(\cuda_math_formula \pm 0 \end_cuda_math_formula, \p y) returns \cuda_math_formula 0 \end_cuda_math_formula of appropriate sign for \p y \cuda_math_formula \neq 0 \end_cuda_math_formula.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fdiv_rn(float x, float y);
/**      
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Divide two floating-point values in round-towards-zero mode.
 *
 * Divide two floating-point values \p x by \p y in round-towards-zero mode.
 *
 * \return Returns \p x / \p y.
 * - sign of the quotient \p x / \p y is XOR of the signs of \p x and \p y when neither inputs nor result are NaN.
 * - __fdiv_rz(\cuda_math_formula \pm 0 \end_cuda_math_formula, \cuda_math_formula \pm 0 \end_cuda_math_formula) returns NaN.
 * - __fdiv_rz(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns NaN.
 * - __fdiv_rz(\p x, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula 0 \end_cuda_math_formula of appropriate sign for finite \p x.
 * - __fdiv_rz(\cuda_math_formula \pm\infty \end_cuda_math_formula, \p y) returns \cuda_math_formula \infty \end_cuda_math_formula of appropriate sign for finite \p y.
 * - __fdiv_rz(\p x, \cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \infty \end_cuda_math_formula of appropriate sign for \p x \cuda_math_formula \neq 0 \end_cuda_math_formula.
 * - __fdiv_rz(\cuda_math_formula \pm 0 \end_cuda_math_formula, \p y) returns \cuda_math_formula 0 \end_cuda_math_formula of appropriate sign for \p y \cuda_math_formula \neq 0 \end_cuda_math_formula.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fdiv_rz(float x, float y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Divide two floating-point values in round-up mode.
 * 
 * Divide two floating-point values \p x by \p y in round-up (to positive infinity) mode.
 *    
 * \return Returns \p x / \p y.
 * - sign of the quotient \p x / \p y is XOR of the signs of \p x and \p y when neither inputs nor result are NaN.
 * - __fdiv_ru(\cuda_math_formula \pm 0 \end_cuda_math_formula, \cuda_math_formula \pm 0 \end_cuda_math_formula) returns NaN.
 * - __fdiv_ru(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns NaN.
 * - __fdiv_ru(\p x, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula 0 \end_cuda_math_formula of appropriate sign for finite \p x.
 * - __fdiv_ru(\cuda_math_formula \pm\infty \end_cuda_math_formula, \p y) returns \cuda_math_formula \infty \end_cuda_math_formula of appropriate sign for finite \p y.
 * - __fdiv_ru(\p x, \cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \infty \end_cuda_math_formula of appropriate sign for \p x \cuda_math_formula \neq 0 \end_cuda_math_formula.
 * - __fdiv_ru(\cuda_math_formula \pm 0 \end_cuda_math_formula, \p y) returns \cuda_math_formula 0 \end_cuda_math_formula of appropriate sign for \p y \cuda_math_formula \neq 0 \end_cuda_math_formula.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fdiv_ru(float x, float y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_SINGLE
 * \brief Divide two floating-point values in round-down mode.
 *
 * Divide two floating-point values \p x by \p y in round-down (to negative infinity) mode.
 *
 * \return Returns \p x / \p y.
 * - sign of the quotient \p x / \p y is XOR of the signs of \p x and \p y when neither inputs nor result are NaN.
 * - __fdiv_rd(\cuda_math_formula \pm 0 \end_cuda_math_formula, \cuda_math_formula \pm 0 \end_cuda_math_formula) returns NaN.
 * - __fdiv_rd(\cuda_math_formula \pm\infty \end_cuda_math_formula, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns NaN.
 * - __fdiv_rd(\p x, \cuda_math_formula \pm\infty \end_cuda_math_formula) returns \cuda_math_formula 0 \end_cuda_math_formula of appropriate sign for finite \p x.
 * - __fdiv_rd(\cuda_math_formula \pm\infty \end_cuda_math_formula, \p y) returns \cuda_math_formula \infty \end_cuda_math_formula of appropriate sign for finite \p y.
 * - __fdiv_rd(\p x, \cuda_math_formula \pm 0 \end_cuda_math_formula) returns \cuda_math_formula \infty \end_cuda_math_formula of appropriate sign for \p x \cuda_math_formula \neq 0 \end_cuda_math_formula.
 * - __fdiv_rd(\cuda_math_formula \pm 0 \end_cuda_math_formula, \p y) returns \cuda_math_formula 0 \end_cuda_math_formula of appropriate sign for \p y \cuda_math_formula \neq 0 \end_cuda_math_formula.
 * - If either argument is NaN, NaN is returned.
 *
 * \note_accuracy_single_intrinsic
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ float                  __fdiv_rd(float x, float y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Return the number of consecutive high-order zero bits in a 32-bit integer.
 *
 * Count the number of consecutive leading zero bits, starting at the most significant bit (bit 31) of \p x.
 *
 * \return Returns a value between 0 and 32 inclusive representing the number of zero bits.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ int                    __clz(int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Find the position of the least significant bit set to 1 in a 32-bit integer.
 *
 * Find the position of the first (least significant) bit set to 1 in \p x, where the least significant
 * bit position is 1. 
 *
 * \return Returns a value between 0 and 32 inclusive representing the position of the first bit set.
 * - __ffs(0) returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ int                    __ffs(int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Count the number of bits that are set to 1 in a 32-bit integer.
 *
 * Count the number of bits that are set to 1 in \p x.
 *
 * \return Returns a value between 0 and 32 inclusive representing the number of set bits.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ int                    __popc(unsigned int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Reverse the bit order of a 32-bit unsigned integer.
 *
 * Reverses the bit order of the 32-bit unsigned integer \p x.
 *
 * \return Returns the bit-reversed value of \p x. i.e. bit N of the return value corresponds to bit 31-N of \p x.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __brev(unsigned int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Count the number of consecutive high-order zero bits in a 64-bit integer.
 *
 * Count the number of consecutive leading zero bits, starting at the most significant bit (bit 63) of \p x.
 *
 * \return Returns a value between 0 and 64 inclusive representing the number of zero bits.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ int                    __clzll(long long int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Find the position of the least significant bit set to 1 in a 64-bit integer.
 *
 * Find the position of the first (least significant) bit set to 1 in \p x, where the least significant
 * bit position is 1. 
 *
 * \return Returns a value between 0 and 64 inclusive representing the position of the first bit set.
 * - __ffsll(0) returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ int                    __ffsll(long long int x);


/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Count the number of bits that are set to 1 in a 64-bit integer.
 *
 * Count the number of bits that are set to 1 in \p x.
 *
 * \return Returns a value between 0 and 64 inclusive representing the number of set bits.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ int                    __popcll(unsigned long long int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Reverse the bit order of a 64-bit unsigned integer.
 *
 * Reverses the bit order of the 64-bit unsigned integer \p x.
 *
 * \return Returns the bit-reversed value of \p x. i.e. bit N of the return value corresponds to bit 63-N of \p x.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned long long int __brevll(unsigned long long int x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Return selected bytes from two 32-bit unsigned integers.
 *
 * \return Returns a 32-bit integer consisting of four bytes from eight input bytes provided in the two
 * input integers \p x and \p y, as specified by a selector, \p s.
 *
 * Create 8-byte source
 * - uint64_t \p tmp64 = ((uint64_t)\p y << 32) | \p x;
 *
 * Extract selector bits
 * - \p selector0 = (\p s >>  0) & 0x7;
 * - \p selector1 = (\p s >>  4) & 0x7;
 * - \p selector2 = (\p s >>  8) & 0x7;
 * - \p selector3 = (\p s >> 12) & 0x7;
 *
 * Return 4 selected bytes from 8-byte source:
 * - \p res[07:00] = \p tmp64[\p selector0];
 * - \p res[15:08] = \p tmp64[\p selector1];
 * - \p res[23:16] = \p tmp64[\p selector2];
 * - \p res[31:24] = \p tmp64[\p selector3];
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __byte_perm(unsigned int x, unsigned int y, unsigned int s);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Compute average of signed input arguments, avoiding overflow
 * in the intermediate sum.
 *
 * Compute average of signed input arguments \p x and \p y 
 * as ( \p x + \p y ) >> 1, avoiding overflow in the intermediate sum.
 *
 * \return Returns a signed integer value representing the signed 
 * average value of the two inputs.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ int                    __hadd(int x, int y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Compute rounded average of signed input arguments, avoiding
 * overflow in the intermediate sum.
 *
 * Compute average of signed input arguments \p x and \p y 
 * as ( \p x + \p y + 1 ) >> 1, avoiding overflow in the intermediate
 * sum.
 *
 * \return Returns a signed integer value representing the signed 
 * rounded average value of the two inputs.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ int                    __rhadd(int x, int y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Compute average of unsigned input arguments, avoiding overflow
 * in the intermediate sum.
 *
 * Compute average of unsigned input arguments \p x and \p y 
 * as ( \p x + \p y ) >> 1, avoiding overflow in the intermediate sum.
 *
 * \return Returns an unsigned integer value representing the unsigned 
 * average value of the two inputs.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __uhadd(unsigned int x, unsigned int y);
/**
 * \ingroup CUDA_MATH_INTRINSIC_INT
 * \brief Compute rounded average of unsigned input arguments, avoiding
 * overflow in the intermediate sum.
 *
 * Compute average of unsigned input arguments \p x and \p y 
 * as ( \p x + \p y + 1 ) >> 1, avoiding overflow in the intermediate
 * sum.
 *
 * \return Returns an unsigned integer value representing the unsigned 
 * rounded average value of the two inputs.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __urhadd(unsigned int x, unsigned int y);

/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a double to a signed int in round-towards-zero mode.
 *
 * Convert the double-precision floating-point value \p x to a
 * signed integer value in round-towards-zero mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ int                    __double2int_rz(double x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a double to an unsigned int in round-towards-zero mode.
 *
 * Convert the double-precision floating-point value \p x to an
 * unsigned integer value in round-towards-zero mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __double2uint_rz(double x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a double to a signed 64-bit int in round-towards-zero mode.
 *
 * Convert the double-precision floating-point value \p x to a
 * signed 64-bit integer value in round-towards-zero mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ long long int          __double2ll_rz(double x);
/**
 * \ingroup CUDA_MATH_INTRINSIC_CAST
 * \brief Convert a double to an unsigned 64-bit int in round-towards-zero mode.
 *
 * Convert the double-precision floating-point value \p x to an
 * unsigned 64-bit integer value in round-towards-zero mode.
 * \return Returns converted value.
 * \note_fp_to_int_out_of_range_undefined
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned long long int __double2ull_rz(double x);
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __pm0(void);
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __pm1(void);
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __pm2(void);
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int           __pm3(void);

/*******************************************************************************
 *                                                                             *
 *                        FP16 SIMD functions                                  *
 *                                                                             *
 *******************************************************************************/

 //  #include "fp16.h"


/*******************************************************************************
 *                                                                             *
 *                                SIMD functions                               *
 *                                                                             *
 *******************************************************************************/

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-halfword absolute value: |a|.
 *
 * Splits 4 bytes of argument into 2 parts, each consisting of 2 bytes,
 * then computes absolute value for each of parts.
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vabs2(unsigned int a);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-halfword absolute value with signed saturation: |a|.
 *
 * Splits 4 bytes of argument into 2 parts, each consisting of 2 bytes,
 * then computes absolute value with signed saturation for each of parts.
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vabsss2(unsigned int a);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword (un)signed addition, with wrap-around: a + b.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes,
 * then performs unsigned addition on corresponding parts.
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vadd2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword addition with signed saturation: a + b.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes,
 * then performs addition with signed saturation on corresponding parts.
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vaddss2 (unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword addition with unsigned saturation: a + b.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes,
 * then performs addition with unsigned saturation on corresponding parts.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vaddus2 (unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword signed rounded average computation.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes,
 * then computes signed rounded average of corresponding parts. Partial results are
 * recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vavgs2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword unsigned rounded average computation.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes,
 * then computes unsigned rounded average of corresponding parts. Partial results are
 * recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vavgu2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword unsigned average computation.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes,
 * then computes unsigned average of corresponding parts. Partial results are
 * recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vhaddu2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword (un)signed comparison: a == b ? 0xffff : 0.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts result is ffff if they are equal, and 0000 otherwise.
 * For example __vcmpeq2(0x1234aba5, 0x1234aba6) returns 0xffff0000.
 * \return Returns 0xffff computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmpeq2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword signed comparison: a >= b ? 0xffff : 0.
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts result is ffff if 'a' part >= 'b' part, and 0000 otherwise.
 * For example __vcmpges2(0x1234aba5, 0x1234aba6) returns 0xffff0000.
 * \return Returns 0xffff if a >= b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmpges2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword unsigned comparison: a >= b ? 0xffff : 0.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts result is ffff if 'a' part >= 'b' part, and 0000 otherwise.
 * For example __vcmpgeu2(0x1234aba5, 0x1234aba6) returns 0xffff0000.
 * \return Returns 0xffff if a >= b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmpgeu2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword signed comparison: a > b ? 0xffff : 0.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts result is ffff if 'a' part > 'b' part, and 0000 otherwise.
 * For example __vcmpgts2(0x1234aba5, 0x1234aba6) returns 0x00000000.
 * \return Returns 0xffff if a > b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmpgts2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword unsigned comparison: a > b ? 0xffff : 0.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts result is ffff if 'a' part > 'b' part, and 0000 otherwise.
 * For example __vcmpgtu2(0x1234aba5, 0x1234aba6) returns 0x00000000.
 * \return Returns 0xffff if a > b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmpgtu2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword signed comparison: a <= b ? 0xffff : 0.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts result is ffff if 'a' part <= 'b' part, and 0000 otherwise.
 * For example __vcmples2(0x1234aba5, 0x1234aba6) returns 0xffffffff.
 * \return Returns 0xffff if a <= b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmples2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword unsigned comparison: a <= b ? 0xffff : 0.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts result is ffff if 'a' part <= 'b' part, and 0000 otherwise.
 * For example __vcmpleu2(0x1234aba5, 0x1234aba6) returns 0xffffffff.
 * \return Returns 0xffff if a <= b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmpleu2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword signed comparison: a < b ? 0xffff : 0.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts result is ffff if 'a' part < 'b' part, and 0000 otherwise.
 * For example __vcmplts2(0x1234aba5, 0x1234aba6) returns 0x0000ffff.
 * \return Returns 0xffff if a < b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmplts2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword unsigned comparison: a < b ? 0xffff : 0.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts result is ffff if 'a' part < 'b' part, and 0000 otherwise.
 * For example __vcmpltu2(0x1234aba5, 0x1234aba6) returns 0x0000ffff.
 * \return Returns 0xffff if a < b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmpltu2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword (un)signed comparison: a != b ? 0xffff : 0.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts result is ffff if 'a' part != 'b' part, and 0000 otherwise.
 * For example __vcmplts2(0x1234aba5, 0x1234aba6) returns 0x0000ffff.
 * \return Returns 0xffff if a != b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmpne2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-halfword absolute difference of unsigned integer: |a - b|.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function computes absolute difference. Partial results
 * are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vabsdiffu2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword signed maximum computation.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function computes signed maximum. Partial results
 * are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vmaxs2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword unsigned maximum computation.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function computes unsigned maximum. Partial results
 * are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vmaxu2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword signed minimum computation.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function computes signed minimum. Partial results
 * are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vmins2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword unsigned minimum computation.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function computes unsigned minimum. Partial results
 * are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vminu2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword (un)signed comparison: returns 1 if both parts compare equal.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function performs comparison 'a' part == 'b' part.
 * If both equalities are satisfied, function returns 1.
 * \return Returns 1 if a = b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vseteq2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword signed comparison: returns 1 if both parts compare greater than or equal.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function performs comparison 'a' part >= 'b' part.
 * If both inequalities are satisfied, function returns 1.
 * \return Returns 1 if a >= b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetges2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword unsigned comparison: returns 1 if both parts compare greater than or equal.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function performs comparison 'a' part >= 'b' part.
 * If both inequalities are satisfied, function returns 1.
 * \return Returns 1 if a >= b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetgeu2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword signed comparison: returns 1 if both parts compare greater than.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function performs comparison 'a' part > 'b' part.
 * If both inequalities are satisfied, function returns 1.
 * \return Returns 1 if a > b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetgts2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword unsigned comparison: returns 1 if both parts compare greater than.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function performs comparison 'a' part > 'b' part.
 * If both inequalities are satisfied, function returns 1.
 * \return Returns 1 if a > b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetgtu2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword unsigned comparison: returns 1 if both parts compare less than or equal.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function performs comparison 'a' part <= 'b' part.
 * If both inequalities are satisfied, function returns 1.
 * \return Returns 1 if a <= b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetles2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword signed comparison: returns 1 if both parts compare less than or equal.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function performs comparison 'a' part <= 'b' part.
 * If both inequalities are satisfied, function returns 1.
 * \return Returns 1 if a <= b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetleu2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword signed comparison: returns 1 if both parts compare less than.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function performs comparison 'a' part <= 'b' part.
 * If both inequalities are satisfied, function returns 1.
 * \return Returns 1 if a < b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetlts2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword unsigned comparison: returns 1 if both parts compare less than.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function performs comparison 'a' part <= 'b' part.
 * If both inequalities are satisfied, function returns 1.
 * \return Returns 1 if a < b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetltu2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword (un)signed comparison: returns 1 if both parts compare not equal.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function performs comparison 'a' part != 'b' part.
 * If both conditions are satisfied, function returns 1.
 * \return Returns 1 if a != b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetne2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-halfword sum of abs diff of unsigned.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function computes absolute differences and returns
 * sum of those differences.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsadu2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword (un)signed subtraction, with wrap-around: a - b.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function performs subtraction. Partial results
 * are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsub2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword (un)signed subtraction, with signed saturation: a - b.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function performs subtraction with signed saturation.
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsubss2 (unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword subtraction with unsigned saturation: a - b.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function performs subtraction with unsigned saturation.
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsubus2 (unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-halfword negation.
 *
 * Splits 4 bytes of argument into 2 parts, each consisting of 2 bytes.
 * For each part function computes negation. Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vneg2(unsigned int a);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-halfword negation with signed saturation.
 *
 * Splits 4 bytes of argument into 2 parts, each consisting of 2 bytes.
 * For each part function computes negation. Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vnegss2(unsigned int a);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-halfword absolute difference of signed integer: |a - b|.
 *
 * Splits 4 bytes of each into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function computes absolute difference.
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vabsdiffs2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword sum of absolute difference of signed.
 *
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * For corresponding parts function computes absolute difference and sum it up.
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsads2(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-byte absolute value: |a|.
 *
 * Splits argument by bytes. Computes absolute value of each byte.
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vabs4(unsigned int a);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-byte absolute value with signed saturation: |a|.
 *
 * Splits 4 bytes of argument into 4 parts, each consisting of 1 byte,
 * then computes absolute value with signed saturation for each of parts.
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vabsss4(unsigned int a);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte (un)signed addition: a + b.
 *
 * Splits 'a' into 4 bytes, then performs unsigned addition on each of these
 * bytes with the corresponding byte from 'b', ignoring overflow.
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vadd4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte addition with signed saturation: a + b.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte,
 * then performs addition with signed saturation on corresponding parts.
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vaddss4 (unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte addition with unsigned saturation: a + b.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte,
 * then performs addition with unsigned saturation on corresponding parts.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vaddus4 (unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-byte signed rounded average.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * then computes signed rounded average of corresponding parts. Partial results are
 * recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vavgs4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte unsigned rounded average.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * then computes unsigned rounded average of corresponding parts. Partial results are
 * recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vavgu4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-byte unsigned average.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * then computes unsigned average of corresponding parts. Partial results are
 * recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vhaddu4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte (un)signed comparison: a == b ? 0xff : 0.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts result is ff if they are equal, and 00 otherwise.
 * For example __vcmpeq4(0x1234aba5, 0x1234aba6) returns 0xffffff00.
 * \return Returns 0xff if a = b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmpeq4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte signed comparison: a >= b ? 0xff : 0.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts result is ff if 'a' part >= 'b' part, and 00 otherwise.
 * For example __vcmpges4(0x1234aba5, 0x1234aba6) returns 0xffffff00.
 * \return Returns 0xff if a >= b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmpges4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte unsigned comparison: a >= b ? 0xff : 0.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts result is ff if 'a' part >= 'b' part, and 00 otherwise.
 * For example __vcmpgeu4(0x1234aba5, 0x1234aba6) returns 0xffffff00.
 * \return Returns 0xff if a >= b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmpgeu4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte signed comparison: a > b ? 0xff : 0.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts result is ff if 'a' part > 'b' part, and 00 otherwise.
 * For example __vcmpgts4(0x1234aba5, 0x1234aba6) returns 0x00000000.
 * \return Returns 0xff if a > b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmpgts4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte unsigned comparison: a > b ? 0xff : 0.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts result is ff if 'a' part > 'b' part, and 00 otherwise.
 * For example __vcmpgtu4(0x1234aba5, 0x1234aba6) returns 0x00000000.
 * \return Returns 0xff if a > b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmpgtu4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte signed comparison: a <= b ? 0xff : 0.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts result is ff if 'a' part <= 'b' part, and 00 otherwise.
 * For example __vcmples4(0x1234aba5, 0x1234aba6) returns 0xffffffff.
 * \return Returns 0xff if a <= b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmples4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte unsigned comparison: a <= b ? 0xff : 0.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts result is ff if 'a' part <= 'b' part, and 00 otherwise.
 * For example __vcmpleu4(0x1234aba5, 0x1234aba6) returns 0xffffffff.
 * \return Returns 0xff if a <= b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmpleu4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte signed comparison: a < b ? 0xff : 0.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts result is ff if 'a' part < 'b' part, and 00 otherwise.
 * For example __vcmplts4(0x1234aba5, 0x1234aba6) returns 0x000000ff.
 * \return Returns 0xff if a < b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmplts4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte unsigned comparison: a < b ? 0xff : 0.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts result is ff if 'a' part < 'b' part, and 00 otherwise.
 * For example __vcmpltu4(0x1234aba5, 0x1234aba6) returns 0x000000ff.
 * \return Returns 0xff if a < b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmpltu4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte (un)signed comparison: a != b ? 0xff : 0.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts result is ff if 'a' part != 'b' part, and 00 otherwise.
 * For example __vcmplts4(0x1234aba5, 0x1234aba6) returns 0x000000ff.
 * \return Returns 0xff if a != b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vcmpne4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-byte absolute difference of unsigned integer: |a - b|.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function computes absolute difference. Partial results
 * are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vabsdiffu4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-byte signed maximum.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function computes signed maximum. Partial results
 * are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vmaxs4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-byte unsigned maximum.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function computes unsigned maximum. Partial results
 * are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vmaxu4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-byte signed minimum.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function computes signed minimum. Partial results
 * are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vmins4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-byte unsigned minimum.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function computes unsigned minimum. Partial results
 * are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vminu4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte (un)signed comparison: returns 1 if all 4 pairs compare equal.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function performs comparison 'a' part == 'b' part.
 * If both equalities are satisfied, function returns 1.
 * \return Returns 1 if a = b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vseteq4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte signed comparison: returns 1 if all 4 pairs compare less than or equal.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function performs comparison 'a' part <= 'b' part.
 * If both inequalities are satisfied, function returns 1.
 * \return Returns 1 if a <= b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetles4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte unsigned comparison: returns 1 if all 4 pairs compare less than or equal.
 *
 * Splits 4 bytes of each argument into 4 part, each consisting of 1 byte.
 * For corresponding parts function performs comparison 'a' part <= 'b' part.
 * If both inequalities are satisfied, function returns 1.
 * \return Returns 1 if a <= b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetleu4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte signed comparison: returns 1 if all 4 pairs compare less than.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function performs comparison 'a' part <= 'b' part.
 * If both inequalities are satisfied, function returns 1.
 * \return Returns 1 if a < b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetlts4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte unsigned comparison: returns 1 if all 4 pairs compare less than.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function performs comparison 'a' part <= 'b' part.
 * If both inequalities are satisfied, function returns 1.
 * \return Returns 1 if a < b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetltu4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte signed comparison: returns 1 if all 4 pairs compare greater than or equal.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function performs comparison 'a' part >= 'b' part.
 * If both inequalities are satisfied, function returns 1.
 * \return Returns 1 if a >= b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetges4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte unsigned comparison: returns 1 if all 4 pairs compare greater than or equal.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function performs comparison 'a' part >= 'b' part.
 * If both inequalities are satisfied, function returns 1.
 * \return Returns 1 if a >= b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetgeu4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte signed comparison: returns 1 if all 4 pairs compare greater than.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function performs comparison 'a' part > 'b' part.
 * If both inequalities are satisfied, function returns 1.
 * \return Returns 1 if a > b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetgts4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte unsigned comparison: returns 1 if all 4 pairs compare greater than.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function performs comparison 'a' part > 'b' part.
 * If both inequalities are satisfied, function returns 1.
 * \return Returns 1 if a > b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetgtu4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte (un)signed comparison: returns 1 if all 4 pairs compare not equal.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function performs comparison 'a' part != 'b' part.
 * If both conditions are satisfied, function returns 1.
 * \return Returns 1 if a != b, else returns 0.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsetne4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-byte sum of abs difference of unsigned.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function computes absolute differences and returns
 * sum of those differences.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsadu4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte subtraction: a - b.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function performs subtraction. Partial results
 * are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsub4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte subtraction with signed saturation: a - b.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function performs subtraction with signed saturation.
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsubss4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte subtraction with unsigned saturation: a - b.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function performs subtraction with unsigned saturation.
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsubus4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte negation.
 *
 * Splits 4 bytes of argument into 4 parts, each consisting of 1 byte.
 * For each part function computes negation. Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vneg4(unsigned int a);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-byte negation with signed saturation.
 *
 * Splits 4 bytes of argument into 4 parts, each consisting of 1 byte.
 * For each part function computes negation. Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vnegss4(unsigned int a);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-byte absolute difference of signed integer: |a - b|.
 *
 * Splits 4 bytes of each into 4 parts, each consisting of 1 byte.
 * For corresponding parts function computes absolute difference.
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vabsdiffs4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes per-byte sum of abs difference of signed.
 *
 * Splits 4 bytes of each argument into 4 parts, each consisting of 1 byte.
 * For corresponding parts function computes absolute difference and sum it up.
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_FUNCTIONS_DECL__ __device_builtin__ unsigned int __vsads4(unsigned int a, unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes max(max(a, b), 0)
 *
 * Calculates the maximum of \p a and \p b of two signed ints, if this is less than \p 0 then \p 0 is returned.
 * \return Returns computed value.
 */

__DEVICE_HOST_FUNCTIONS_STATIC_DECL__ int __vimax_s32_relu(const int a, const int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword max(max(a, b), 0)
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as signed shorts.
 * For corresponding parts function performs a max with relu ( = max(a_part, b_part, 0) ). Partial results
 * are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __vimax_s16x2_relu(const unsigned int a, const unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes max(min(a, b), 0)
 *
 * Calculates the minimum of \p a and \p b of two signed ints, if this is less than \p 0 then \p 0 is returned.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  int __vimin_s32_relu(const int a, const int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword max(min(a, b), 0)
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as signed shorts.
 * For corresponding parts function performs a min with relu ( = max(min(a_part, b_part), 0) ). Partial results
 * are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __vimin_s16x2_relu(const unsigned int a, const unsigned int b);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes max(max(a, b), c)
 * 
 * Calculates the 3-way max of signed integers \p a, \p b and \p c.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  int __vimax3_s32(const int a, const int b, const int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword max(max(a, b), c)
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as signed shorts.
 * For corresponding parts function performs a 3-way max ( = max(max(a_part, b_part), c_part) ).
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __vimax3_s16x2(const unsigned int a, const unsigned int b, const unsigned int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes max(max(a, b), c)
 * 
 * Calculates the 3-way max of unsigned integers \p a, \p b and \p c.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __vimax3_u32(const unsigned int a, const unsigned int b, const unsigned int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword max(max(a, b), c)
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as unsigned shorts.
 * For corresponding parts function performs a 3-way max ( = max(max(a_part, b_part), c_part) ).
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __vimax3_u16x2(const unsigned int a, const unsigned int b, const unsigned int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes min(min(a, b), c)
 * 
 * Calculates the 3-way min of signed integers \p a, \p b and \p c.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  int __vimin3_s32(const int a, const int b, const int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword min(min(a, b), c)
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as signed shorts.
 * For corresponding parts function performs a 3-way min ( = min(min(a_part, b_part), c_part) ).
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __vimin3_s16x2(const unsigned int a, const unsigned int b, const unsigned int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes min(min(a, b), c)
 * 
 * Calculates the 3-way min of unsigned integers \p a, \p b and \p c.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __vimin3_u32(const unsigned int a, const unsigned int b, const unsigned int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword min(min(a, b), c)
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as unsigned shorts.
 * For corresponding parts function performs a 3-way min ( = min(min(a_part, b_part), c_part) ).
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __vimin3_u16x2(const unsigned int a, const unsigned int b, const unsigned int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes max(max(max(a, b), c), 0)
 *
 * Calculates the maximum of three signed ints, if this is less than \p 0 then \p 0 is returned.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  int __vimax3_s32_relu(const int a, const int b, const int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword max(max(max(a, b), c), 0)
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as signed shorts.
 * For corresponding parts function performs a three-way max with relu ( = max(a_part, b_part, c_part, 0) ).
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __vimax3_s16x2_relu(const unsigned int a, const unsigned int b, const unsigned int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes max(min(min(a, b), c), 0)
 *
 * Calculates the minimum of three signed ints, if this is less than \p 0 then \p 0 is returned.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  int __vimin3_s32_relu(const int a, const int b, const int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword max(min(min(a, b), c), 0)
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as signed shorts.
 * For corresponding parts function performs a three-way min with relu ( = max(min(a_part, b_part, c_part), 0) ).
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __vimin3_s16x2_relu(const unsigned int a, const unsigned int b, const unsigned int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes max(a + b, c)
 *
 * Calculates the sum of signed integers \p a and \p b and takes the max with \p c.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  int __viaddmax_s32(const int a, const int b, const int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword max(a + b, c)
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as signed shorts.
 * For corresponding parts function performs an add and compare: max(a_part + b_part), c_part)
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __viaddmax_s16x2(const unsigned int a, const unsigned int b, const unsigned int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes max(a + b, c)
 *
 * Calculates the sum of unsigned integers \p a and \p b and takes the max with \p c.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __viaddmax_u32(const unsigned int a, const unsigned int b, const unsigned int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword max(a + b, c)
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as unsigned shorts.
 * For corresponding parts function performs an add and compare: max(a_part + b_part), c_part)
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __viaddmax_u16x2(const unsigned int a, const unsigned int b, const unsigned int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes min(a + b, c)
 *
 * Calculates the sum of signed integers \p a and \p b and takes the min with \p c.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  int __viaddmin_s32(const int a, const int b, const int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword min(a + b, c)
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as signed shorts.
 * For corresponding parts function performs an add and compare: min(a_part + b_part), c_part)
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __viaddmin_s16x2(const unsigned int a, const unsigned int b, const unsigned int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes min(a + b, c)
 *
 * Calculates the sum of unsigned integers \p a and \p b and takes the min with \p c.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __viaddmin_u32(const unsigned int a, const unsigned int b, const unsigned int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword min(a + b, c)
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as unsigned shorts.
 * For corresponding parts function performs an add and compare: min(a_part + b_part), c_part)
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __viaddmin_u16x2(const unsigned int a, const unsigned int b, const unsigned int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes max(max(a + b, c), 0)
 *
 * Calculates the sum of signed integers \p a and \p b and takes the max with \p c.
 * If the result is less than \p 0 then \p 0 is returned.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  int __viaddmax_s32_relu(const int a, const int b, const int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword max(max(a + b, c), 0)
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as signed shorts.
 * For corresponding parts function performs an add, followed by a max with relu: max(max(a_part + b_part), c_part), 0)
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __viaddmax_s16x2_relu(const unsigned int a, const unsigned int b, const unsigned int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes max(min(a + b, c), 0)
 *
 * Calculates the sum of signed integers \p a and \p b and takes the min with \p c.
 * If the result is less than \p 0 then \p 0 is returned.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  int __viaddmin_s32_relu(const int a, const int b, const int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword max(min(a + b, c), 0)
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as signed shorts.
 * For corresponding parts function performs an add, followed by a min with relu: max(min(a_part + b_part), c_part), 0)
 * Partial results are recombined and returned as unsigned int.
 * \return Returns computed value.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __viaddmin_s16x2_relu(const unsigned int a, const unsigned int b, const unsigned int c);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes max(a, b), also sets the value pointed to by pred to (a >= b).
 *
 * Calculates the maximum of \p a and \p b of two signed ints. Also sets the value pointed to by \p pred to the value (a >= b).
 * \return Returns computed values.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  int __vibmax_s32(const int a, const int b, bool* const pred);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes max(a, b), also sets the value pointed to by pred to (a >= b).
 *
 * Calculates the maximum of \p a and \p b of two unsigned ints. Also sets the value pointed to by \p pred to the value (a >= b).
 * \return Returns computed values.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __vibmax_u32(const unsigned int a, const unsigned int b, bool* const pred);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes min(a, b), also sets the value pointed to by pred to (a <= b).
 *
 * Calculates the minimum of \p a and \p b of two signed ints. Also sets the value pointed to by \p pred to the value (a <= b).
 * \return Returns computed values.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  int __vibmin_s32(const int a, const int b, bool* const pred);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Computes min(a, b), also sets the value pointed to by pred to (a <= b).
 *
 * Calculates the minimum of \p a and \p b of two unsigned ints. Also sets the value pointed to by \p pred to the value (a <= b).
 * \return Returns computed values.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __vibmin_u32(const unsigned int a, const unsigned int b, bool* const pred);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword max(a, b), also sets the value pointed to by pred_hi and pred_lo to the per-halfword result of (a >= b).
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as signed shorts.
 * For corresponding parts function performs a maximum ( = max(a_part, b_part) ).
 * Partial results are recombined and returned as unsigned int.
 * Sets the value pointed to by \p pred_hi to the value (a_high_part >= b_high_part).
 * Sets the value pointed to by \p pred_lo to the value (a_low_part >= b_low_part).
 * \return Returns computed values.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __vibmax_s16x2(const unsigned int a, const unsigned int b, bool* const pred_hi, bool* const pred_lo);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword max(a, b), also sets the value pointed to by pred_hi and pred_lo to the per-halfword result of (a >= b).
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as unsigned shorts.
 * For corresponding parts function performs a maximum ( = max(a_part, b_part) ).
 * Partial results are recombined and returned as unsigned int.
 * Sets the value pointed to by \p pred_hi to the value (a_high_part >= b_high_part).
 * Sets the value pointed to by \p pred_lo to the value (a_low_part >= b_low_part).
 * \return Returns computed values.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __vibmax_u16x2(const unsigned int a, const unsigned int b, bool* const pred_hi, bool* const pred_lo);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword min(a, b), also sets the value pointed to by pred_hi and pred_lo to the per-halfword result of (a <= b).
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as signed shorts.
 * For corresponding parts function performs a maximum ( = max(a_part, b_part) ).
 * Partial results are recombined and returned as unsigned int.
 * Sets the value pointed to by \p pred_hi to the value (a_high_part <= b_high_part).
 * Sets the value pointed to by \p pred_lo to the value (a_low_part <= b_low_part).
 * \return Returns computed values.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __vibmin_s16x2(const unsigned int a, const unsigned int b, bool* const pred_hi, bool* const pred_lo);

/**
 * \ingroup CUDA_MATH_INTRINSIC_SIMD
 * \brief Performs per-halfword min(a, b), also sets the value pointed to by pred_hi and pred_lo to the per-halfword result of (a <= b).
 * 
 * Splits 4 bytes of each argument into 2 parts, each consisting of 2 bytes.
 * These 2 byte parts are interpreted as unsigned shorts.
 * For corresponding parts function performs a maximum ( = max(a_part, b_part) ).
 * Partial results are recombined and returned as unsigned int.
 * Sets the value pointed to by \p pred_hi to the value (a_high_part <= b_high_part).
 * Sets the value pointed to by \p pred_lo to the value (a_low_part <= b_low_part).
 * \return Returns computed values.
 */
__DEVICE_HOST_FUNCTIONS_STATIC_DECL__  unsigned int __vibmin_u16x2(const unsigned int a, const unsigned int b, bool* const pred_hi, bool* const pred_lo);

/*******************************************************************************
 *                                                                             *
 *                            END SIMD functions                               *
 *                                                                             *
 *******************************************************************************/
} //extern "c"
#undef EXCLUDE_FROM_RTC

#undef __DEVICE_FUNCTIONS_DECL__
#undef __DEVICE_FUNCTIONS_STATIC_DECL__
#undef __DEVICE_HOST_FUNCTIONS_STATIC_DECL__

#endif /* __cplusplus && __CUDACC__ */

/*******************************************************************************
*                                                                              *
*                                                                              *
*                                                                              *
*******************************************************************************/

#if !defined(__CUDACC_RTC__)
#include "device_functions.hpp"
#endif /* !defined(__CUDACC_RTC__) */

#include "device_atomic_functions.h"
#include "device_double_functions.h"
#include "sm_20_atomic_functions.h"
#include "sm_32_atomic_functions.h"
#include "sm_35_atomic_functions.h"
#include "sm_60_atomic_functions.h"
#include "sm_20_intrinsics.h"
#include "sm_30_intrinsics.h"
#include "sm_32_intrinsics.h"
#include "sm_35_intrinsics.h"
#include "sm_61_intrinsics.h"
#include "sm_70_rt.h"
#include "sm_80_rt.h"
#include "sm_90_rt.h"
#include "sm_100_rt.h"
#ifndef __CUDACC_RTC_MINIMAL__
#include "texture_indirect_functions.h"
#include "surface_indirect_functions.h"
#endif  /* !__CUDACC_RTC_MINIMAL__ */
#include "cudacc_ext.h"

#ifdef __CUDACC__
extern "C" __host__ __device__  unsigned CUDARTAPI __cudaPushCallConfiguration(dim3 gridDim,
                                      dim3 blockDim = 1, 
                                      size_t sharedMem = 0, 
                                      struct CUstream_st *stream = 0);

#if !defined(__CUDACC_RTC__) &&!defined(__NV_LEGACY_LAUNCH)
extern "C" cudaError_t CUDARTAPI __cudaGetKernel(cudaKernel_t *, const void *);

extern "C"  cudaError_t CUDARTAPI __cudaLaunchKernel(
        cudaKernel_t kernel,
        dim3 gridDim,
        dim3 blockDim,
        void **args,
        size_t sharedMem,
        cudaStream_t stream
);

extern "C" cudaError_t CUDARTAPI __cudaLaunchKernel_ptsz(
        cudaKernel_t kernel,
        dim3 gridDim,
        dim3 blockDim,
        void **args,
        size_t sharedMem,
        cudaStream_t stream
);

//referenced from compiler generated kernel launch code
static inline cudaError_t __cudaLaunchKernel_helper(
                                  cudaKernel_t kernel,
                                  dim3 gridDim,
                                  dim3 blockDim,
                                  void **args,
                                  size_t sharedMem,
                                  cudaStream_t stream)
{
#if defined(__CUDART_API_PER_THREAD_DEFAULT_STREAM)
  return __cudaLaunchKernel_ptsz(kernel, gridDim, blockDim, args, sharedMem,
                                 stream);
#else  /* !__CUDART_API_PER_THREAD_DEFAULT_STREAM */
  return __cudaLaunchKernel(kernel, gridDim, blockDim, args, sharedMem,
                            stream);
#endif  /* __CUDART_API_PER_THREAD_DEFAULT_STREAM */
}
#endif  /* !defined(__CUDACC_RTC__) && !defined(__NV_LEGACY_LAUNCH) */

enum {
  __NV_ATOMIC_RELAXED,
  __NV_ATOMIC_CONSUME,
  __NV_ATOMIC_ACQUIRE,
  __NV_ATOMIC_RELEASE,
  __NV_ATOMIC_ACQ_REL,
  __NV_ATOMIC_SEQ_CST
};

enum {
  __NV_THREAD_SCOPE_THREAD,
  __NV_THREAD_SCOPE_BLOCK,
  __NV_THREAD_SCOPE_CLUSTER,
  __NV_THREAD_SCOPE_DEVICE,
  __NV_THREAD_SCOPE_SYSTEM
};

#endif  /* __CUDACC__ */

#endif /* !__DEVICE_FUNCTIONS_H__ */

#if defined(__UNDEF_CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS_DEVICE_FUNCTIONS_H__)
#undef __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#undef __UNDEF_CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS_DEVICE_FUNCTIONS_H__
#endif
