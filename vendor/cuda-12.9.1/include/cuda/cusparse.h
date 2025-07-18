/*
 * Copyright 1993-2023 NVIDIA Corporation.  All rights reserved.
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
#if !defined(CUSPARSE_H_)
#define CUSPARSE_H_

#include <cuComplex.h>        // cuComplex
#include <cuda_runtime_api.h> // cudaStream_t
#include <library_types.h>    // CUDA_R_32F
#include <stdint.h>           // int64_t
#include <stdio.h>            // FILE*

#if defined(__cplusplus)
#   include <cuda_fp16.h>     // __half
#endif // defined(__cplusplus)

//##############################################################################
//# CUSPARSE VERSION INFORMATION
//##############################################################################

#define CUSPARSE_VER_MAJOR 12
#define CUSPARSE_VER_MINOR 5
#define CUSPARSE_VER_PATCH 10
#define CUSPARSE_VER_BUILD 65
#define CUSPARSE_VERSION (CUSPARSE_VER_MAJOR * 1000 + \
                          CUSPARSE_VER_MINOR *  100 + \
                          CUSPARSE_VER_PATCH)

// #############################################################################
// # BASIC MACROS
// #############################################################################

#if !defined(CUSPARSEAPI)
#    if defined(_WIN32)
#        define CUSPARSEAPI __stdcall
#    else
#        define CUSPARSEAPI
#    endif
#endif

//------------------------------------------------------------------------------

#if !defined(_MSC_VER)
#   define CUSPARSE_CPP_VERSION __cplusplus
#elif _MSC_FULL_VER >= 190024210 // Visual Studio 2015 Update 3
#   define CUSPARSE_CPP_VERSION _MSVC_LANG
#else
#   define CUSPARSE_CPP_VERSION 0
#endif

// #############################################################################
// # CUSPARSE_DEPRECATED MACRO
// #############################################################################

#if !defined(DISABLE_CUSPARSE_DEPRECATED)

#   if CUSPARSE_CPP_VERSION >= 201402L

#       define CUSPARSE_DEPRECATED_REPLACE_WITH(new_func)                      \
            [[deprecated("please use " #new_func " instead")]]

#       define CUSPARSE_DEPRECATED                                             \
         [[deprecated("The routine will be removed in the next major release")]]

#       define CUSPARSE_DEPRECATED_TYPE                                        \
         [[deprecated("The type will be removed in the next major release")]]

#       define CUSPARSE_DEPRECATED_TYPE_MSVC

#   elif defined(_MSC_VER)

#       define CUSPARSE_DEPRECATED_REPLACE_WITH(new_func)                      \
            __declspec(deprecated("please use " #new_func " instead"))

#       define CUSPARSE_DEPRECATED                                             \
            __declspec(deprecated(                                             \
                "The routine will be removed in the next major release"))

#       define CUSPARSE_DEPRECATED_TYPE

#       define CUSPARSE_DEPRECATED_TYPE_MSVC
            __declspec(deprecated(                                             \
                "The type will be removed in the next major release"))

#   elif defined(__INTEL_COMPILER) || defined(__clang__) ||                    \
         (defined(__GNUC__) &&                                                 \
          (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)))

#       define CUSPARSE_DEPRECATED_REPLACE_WITH(new_func)                      \
            __attribute__((deprecated("please use " #new_func " instead")))

#       define CUSPARSE_DEPRECATED                                             \
            __attribute__((deprecated(                                         \
                "The routine will be removed in the next major release")))

#       define CUSPARSE_DEPRECATED_TYPE                                        \
            __attribute__((deprecated(                                         \
                "The type will be removed in the next major release")))

#       define CUSPARSE_DEPRECATED_TYPE_MSVC

#   elif defined(__GNUC__)

#       define CUSPARSE_DEPRECATED_REPLACE_WITH(new_func)                      \
            __attribute__((deprecated))

#       define CUSPARSE_DEPRECATED      __attribute__((deprecated))
#       define CUSPARSE_DEPRECATED_TYPE __attribute__((deprecated))
#       define CUSPARSE_DEPRECATED_TYPE_MSVC

#   else

#       define CUSPARSE_DEPRECATED_REPLACE_WITH(new_func)
#       define CUSPARSE_DEPRECATED
#       define CUSPARSE_DEPRECATED_TYPE
#       define CUSPARSE_DEPRECATED_TYPE_MSVC

#   endif // defined(__cplusplus) && __cplusplus >= 201402L
//------------------------------------------------------------------------------

#   if CUSPARSE_CPP_VERSION >= 201703L

#       define CUSPARSE_DEPRECATED_ENUM_REPLACE_WITH(new_enum)                 \
            [[deprecated("please use " #new_enum " instead")]]

#       define CUSPARSE_DEPRECATED_ENUM                                        \
            [[deprecated("The enum will be removed in the next major release")]]

#   elif defined(__clang__) ||                                                 \
         (defined(__GNUC__) && __GNUC__ >= 6 && !defined(__PGI))

#       define CUSPARSE_DEPRECATED_ENUM_REPLACE_WITH(new_enum)                 \
            __attribute__((deprecated("please use " #new_enum " instead")))

#       define CUSPARSE_DEPRECATED_ENUM                                        \
            __attribute__((deprecated(                                         \
                "The enum will be removed in the next major release")))

#   else

#       define CUSPARSE_DEPRECATED_ENUM_REPLACE_WITH(new_enum)
#       define CUSPARSE_DEPRECATED_ENUM

#   endif // defined(__cplusplus) && __cplusplus >= 201402L

#else // defined(DISABLE_CUSPARSE_DEPRECATED)

#   define CUSPARSE_DEPRECATED_REPLACE_WITH(new_func)
#   define CUSPARSE_DEPRECATED
#   define CUSPARSE_DEPRECATED_TYPE
#   define CUSPARSE_DEPRECATED_TYPE_MSVC
#   define CUSPARSE_DEPRECATED_ENUM_REPLACE_WITH(new_enum)
#   define CUSPARSE_DEPRECATED_ENUM

#endif // !defined(DISABLE_CUSPARSE_DEPRECATED)

#undef CUSPARSE_CPP_VERSION

//------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

//##############################################################################
//# OPAQUE DATA STRUCTURES
//##############################################################################

struct cusparseContext;
typedef struct cusparseContext* cusparseHandle_t;

struct cusparseMatDescr;
typedef struct cusparseMatDescr* cusparseMatDescr_t;

struct bsrsv2Info;
typedef CUSPARSE_DEPRECATED_TYPE_MSVC
struct bsrsv2Info* bsrsv2Info_t CUSPARSE_DEPRECATED_TYPE;

struct bsrsm2Info;
typedef CUSPARSE_DEPRECATED_TYPE_MSVC
struct bsrsm2Info* bsrsm2Info_t CUSPARSE_DEPRECATED_TYPE;

struct csric02Info;
typedef CUSPARSE_DEPRECATED_TYPE_MSVC
struct csric02Info* csric02Info_t CUSPARSE_DEPRECATED_TYPE;

struct bsric02Info;
typedef CUSPARSE_DEPRECATED_TYPE_MSVC
struct bsric02Info* bsric02Info_t CUSPARSE_DEPRECATED_TYPE;

struct csrilu02Info;
typedef CUSPARSE_DEPRECATED_TYPE_MSVC
struct csrilu02Info* csrilu02Info_t CUSPARSE_DEPRECATED_TYPE;

struct bsrilu02Info;
typedef CUSPARSE_DEPRECATED_TYPE_MSVC
struct bsrilu02Info* bsrilu02Info_t CUSPARSE_DEPRECATED_TYPE;

struct csru2csrInfo;
typedef CUSPARSE_DEPRECATED_TYPE_MSVC
struct csru2csrInfo* csru2csrInfo_t CUSPARSE_DEPRECATED_TYPE;

struct cusparseColorInfo;
typedef CUSPARSE_DEPRECATED_TYPE_MSVC
struct cusparseColorInfo* cusparseColorInfo_t CUSPARSE_DEPRECATED_TYPE;

struct pruneInfo;
typedef CUSPARSE_DEPRECATED_TYPE_MSVC
struct pruneInfo* pruneInfo_t CUSPARSE_DEPRECATED_TYPE;

//##############################################################################
//# ENUMERATORS
//##############################################################################

typedef enum {
    CUSPARSE_STATUS_SUCCESS                   = 0,
    CUSPARSE_STATUS_NOT_INITIALIZED           = 1,
    CUSPARSE_STATUS_ALLOC_FAILED              = 2,
    CUSPARSE_STATUS_INVALID_VALUE             = 3,
    CUSPARSE_STATUS_ARCH_MISMATCH             = 4,
    CUSPARSE_STATUS_MAPPING_ERROR             = 5,
    CUSPARSE_STATUS_EXECUTION_FAILED          = 6,
    CUSPARSE_STATUS_INTERNAL_ERROR            = 7,
    CUSPARSE_STATUS_MATRIX_TYPE_NOT_SUPPORTED = 8,
    CUSPARSE_STATUS_ZERO_PIVOT                = 9,
    CUSPARSE_STATUS_NOT_SUPPORTED             = 10,
    CUSPARSE_STATUS_INSUFFICIENT_RESOURCES    = 11
} cusparseStatus_t;

typedef enum {
    CUSPARSE_POINTER_MODE_HOST   = 0,
    CUSPARSE_POINTER_MODE_DEVICE = 1
} cusparsePointerMode_t;

typedef enum {
    CUSPARSE_ACTION_SYMBOLIC = 0,
    CUSPARSE_ACTION_NUMERIC  = 1
} cusparseAction_t;

typedef enum {
    CUSPARSE_MATRIX_TYPE_GENERAL    = 0,
    CUSPARSE_MATRIX_TYPE_SYMMETRIC  = 1,
    CUSPARSE_MATRIX_TYPE_HERMITIAN  = 2,
    CUSPARSE_MATRIX_TYPE_TRIANGULAR = 3
} cusparseMatrixType_t;

typedef enum {
    CUSPARSE_FILL_MODE_LOWER = 0,
    CUSPARSE_FILL_MODE_UPPER = 1
} cusparseFillMode_t;

typedef enum {
    CUSPARSE_DIAG_TYPE_NON_UNIT = 0,
    CUSPARSE_DIAG_TYPE_UNIT     = 1
} cusparseDiagType_t;

typedef enum {
    CUSPARSE_INDEX_BASE_ZERO = 0,
    CUSPARSE_INDEX_BASE_ONE  = 1
} cusparseIndexBase_t;

typedef enum {
    CUSPARSE_OPERATION_NON_TRANSPOSE       = 0,
    CUSPARSE_OPERATION_TRANSPOSE           = 1,
    CUSPARSE_OPERATION_CONJUGATE_TRANSPOSE = 2
} cusparseOperation_t;

typedef enum {
    CUSPARSE_DIRECTION_ROW    = 0,
    CUSPARSE_DIRECTION_COLUMN = 1
} cusparseDirection_t;

typedef enum {
    CUSPARSE_SOLVE_POLICY_NO_LEVEL = 0,
    CUSPARSE_SOLVE_POLICY_USE_LEVEL = 1
} cusparseSolvePolicy_t CUSPARSE_DEPRECATED_TYPE;

typedef enum {
    CUSPARSE_COLOR_ALG0 = 0, // default
    CUSPARSE_COLOR_ALG1 = 1
} cusparseColorAlg_t CUSPARSE_DEPRECATED_TYPE;

//##############################################################################
//# INITIALIZATION AND MANAGEMENT ROUTINES
//##############################################################################

cusparseStatus_t CUSPARSEAPI
cusparseCreate(cusparseHandle_t* handle);

cusparseStatus_t CUSPARSEAPI
cusparseDestroy(cusparseHandle_t handle);

cusparseStatus_t CUSPARSEAPI
cusparseGetVersion(cusparseHandle_t handle,
                   int*             version);

cusparseStatus_t CUSPARSEAPI
cusparseGetProperty(libraryPropertyType type,
                    int*                value);

const char* CUSPARSEAPI
cusparseGetErrorName(cusparseStatus_t status);

const char* CUSPARSEAPI
cusparseGetErrorString(cusparseStatus_t status);

cusparseStatus_t CUSPARSEAPI
cusparseSetStream(cusparseHandle_t handle,
                  cudaStream_t     streamId);

cusparseStatus_t CUSPARSEAPI
cusparseGetStream(cusparseHandle_t handle,
                  cudaStream_t*    streamId);

cusparseStatus_t CUSPARSEAPI
cusparseGetPointerMode(cusparseHandle_t       handle,
                       cusparsePointerMode_t* mode);

cusparseStatus_t CUSPARSEAPI
cusparseSetPointerMode(cusparseHandle_t      handle,
                       cusparsePointerMode_t mode);

//##############################################################################
//# LOGGING APIs
//##############################################################################

typedef void (*cusparseLoggerCallback_t)(int         logLevel,
                                         const char* functionName,
                                         const char* message);

cusparseStatus_t CUSPARSEAPI
cusparseLoggerSetCallback(cusparseLoggerCallback_t callback);

cusparseStatus_t CUSPARSEAPI
cusparseLoggerSetFile(FILE* file);

cusparseStatus_t CUSPARSEAPI
cusparseLoggerOpenFile(const char* logFile);

cusparseStatus_t CUSPARSEAPI
cusparseLoggerSetLevel(int level);

cusparseStatus_t CUSPARSEAPI
cusparseLoggerSetMask(int mask);

cusparseStatus_t CUSPARSEAPI
cusparseLoggerForceDisable(void);

//##############################################################################
//# HELPER ROUTINES
//##############################################################################

cusparseStatus_t CUSPARSEAPI
cusparseCreateMatDescr(cusparseMatDescr_t* descrA);

cusparseStatus_t CUSPARSEAPI
cusparseDestroyMatDescr(cusparseMatDescr_t descrA);

cusparseStatus_t CUSPARSEAPI
cusparseSetMatType(cusparseMatDescr_t   descrA,
                   cusparseMatrixType_t type);

cusparseMatrixType_t CUSPARSEAPI
cusparseGetMatType(const cusparseMatDescr_t descrA);

cusparseStatus_t CUSPARSEAPI
cusparseSetMatFillMode(cusparseMatDescr_t descrA,
                       cusparseFillMode_t fillMode);

cusparseFillMode_t CUSPARSEAPI
cusparseGetMatFillMode(const cusparseMatDescr_t descrA);

cusparseStatus_t CUSPARSEAPI
cusparseSetMatDiagType(cusparseMatDescr_t descrA,
                       cusparseDiagType_t diagType);

cusparseDiagType_t CUSPARSEAPI
cusparseGetMatDiagType(const cusparseMatDescr_t descrA);

cusparseStatus_t CUSPARSEAPI
cusparseSetMatIndexBase(cusparseMatDescr_t  descrA,
                        cusparseIndexBase_t base);

cusparseIndexBase_t CUSPARSEAPI
cusparseGetMatIndexBase(const cusparseMatDescr_t descrA);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCreateCsric02Info(csric02Info_t* info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDestroyCsric02Info(csric02Info_t info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCreateBsric02Info(bsric02Info_t* info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDestroyBsric02Info(bsric02Info_t info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCreateCsrilu02Info(csrilu02Info_t* info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDestroyCsrilu02Info(csrilu02Info_t info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCreateBsrilu02Info(bsrilu02Info_t* info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDestroyBsrilu02Info(bsrilu02Info_t info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCreateBsrsv2Info(bsrsv2Info_t* info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDestroyBsrsv2Info(bsrsv2Info_t info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCreateBsrsm2Info(bsrsm2Info_t* info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDestroyBsrsm2Info(bsrsm2Info_t info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCreateCsru2csrInfo(csru2csrInfo_t* info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDestroyCsru2csrInfo(csru2csrInfo_t info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCreateColorInfo(cusparseColorInfo_t* info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDestroyColorInfo(cusparseColorInfo_t info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCreatePruneInfo(pruneInfo_t* info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDestroyPruneInfo(pruneInfo_t info);

//##############################################################################
//# SPARSE LEVEL 2 ROUTINES
//##############################################################################

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseSgemvi(cusparseHandle_t    handle,
               cusparseOperation_t transA,
               int                 m,
               int                 n,
               const float*        alpha,
               const float*        A,
               int                 lda,
               int                 nnz,
               const float*        xVal,
               const int*          xInd,
               const float*        beta,
               float*              y,
               cusparseIndexBase_t idxBase,
               void*               pBuffer);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseSgemvi_bufferSize(cusparseHandle_t    handle,
                          cusparseOperation_t transA,
                          int                 m,
                          int                 n,
                          int                 nnz,
                          int*                pBufferSize);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseDgemvi(cusparseHandle_t    handle,
               cusparseOperation_t transA,
               int                 m,
               int                 n,
               const double*       alpha,
               const double*       A,
               int                 lda,
               int                 nnz,
               const double*       xVal,
               const int*          xInd,
               const double*       beta,
               double*             y,
               cusparseIndexBase_t idxBase,
               void*               pBuffer);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseDgemvi_bufferSize(cusparseHandle_t    handle,
                          cusparseOperation_t transA,
                          int                 m,
                          int                 n,
                          int                 nnz,
                          int*                pBufferSize);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseCgemvi(cusparseHandle_t    handle,
               cusparseOperation_t transA,
               int                 m,
               int                 n,
               const cuComplex*    alpha,
               const cuComplex*    A,
               int                 lda,
               int                 nnz,
               const cuComplex*    xVal,
               const int*          xInd,
               const cuComplex*    beta,
               cuComplex*          y,
               cusparseIndexBase_t idxBase,
               void*               pBuffer);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseCgemvi_bufferSize(cusparseHandle_t    handle,
                          cusparseOperation_t transA,
                          int                 m,
                          int                 n,
                          int                 nnz,
                          int*                pBufferSize);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseZgemvi(cusparseHandle_t       handle,
               cusparseOperation_t    transA,
               int                    m,
               int                    n,
               const cuDoubleComplex* alpha,
               const cuDoubleComplex* A,
               int                    lda,
               int                    nnz,
               const cuDoubleComplex* xVal,
               const int*             xInd,
               const cuDoubleComplex* beta,
               cuDoubleComplex*       y,
               cusparseIndexBase_t    idxBase,
               void*                  pBuffer);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseZgemvi_bufferSize(cusparseHandle_t    handle,
                          cusparseOperation_t transA,
                          int                 m,
                          int                 n,
                          int                 nnz,
                          int*                pBufferSize);

cusparseStatus_t CUSPARSEAPI
cusparseSbsrmv(cusparseHandle_t         handle,
               cusparseDirection_t      dirA,
               cusparseOperation_t      transA,
               int                      mb,
               int                      nb,
               int                      nnzb,
               const float*             alpha,
               const cusparseMatDescr_t descrA,
               const float*             bsrSortedValA,
               const int*               bsrSortedRowPtrA,
               const int*               bsrSortedColIndA,
               int                      blockDim,
               const float*             x,
               const float*             beta,
               float*                   y);

cusparseStatus_t CUSPARSEAPI
cusparseDbsrmv(cusparseHandle_t         handle,
               cusparseDirection_t      dirA,
               cusparseOperation_t      transA,
               int                      mb,
               int                      nb,
               int                      nnzb,
               const double*            alpha,
               const cusparseMatDescr_t descrA,
               const double*            bsrSortedValA,
               const int*               bsrSortedRowPtrA,
               const int*               bsrSortedColIndA,
               int                      blockDim,
               const double*            x,
               const double*            beta,
               double*                  y);

cusparseStatus_t CUSPARSEAPI
cusparseCbsrmv(cusparseHandle_t         handle,
               cusparseDirection_t      dirA,
               cusparseOperation_t      transA,
               int                      mb,
               int                      nb,
               int                      nnzb,
               const cuComplex*         alpha,
               const cusparseMatDescr_t descrA,
               const cuComplex*         bsrSortedValA,
               const int*               bsrSortedRowPtrA,
               const int*               bsrSortedColIndA,
               int                      blockDim,
               const cuComplex*         x,
               const cuComplex*         beta,
               cuComplex*               y);

cusparseStatus_t CUSPARSEAPI
cusparseZbsrmv(cusparseHandle_t         handle,
               cusparseDirection_t      dirA,
               cusparseOperation_t      transA,
               int                      mb,
               int                      nb,
               int                      nnzb,
               const cuDoubleComplex*   alpha,
               const cusparseMatDescr_t descrA,
               const cuDoubleComplex*   bsrSortedValA,
               const int*               bsrSortedRowPtrA,
               const int*               bsrSortedColIndA,
               int                      blockDim,
               const cuDoubleComplex*   x,
               const cuDoubleComplex*   beta,
               cuDoubleComplex*         y);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsrxmv(cusparseHandle_t         handle,
                cusparseDirection_t      dirA,
                cusparseOperation_t      transA,
                int                      sizeOfMask,
                int                      mb,
                int                      nb,
                int                      nnzb,
                const float*             alpha,
                const cusparseMatDescr_t descrA,
                const float*             bsrSortedValA,
                const int*               bsrSortedMaskPtrA,
                const int*               bsrSortedRowPtrA,
                const int*               bsrSortedEndPtrA,
                const int*               bsrSortedColIndA,
                int                      blockDim,
                const float*             x,
                const float*             beta,
                float*                   y);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsrxmv(cusparseHandle_t         handle,
                cusparseDirection_t      dirA,
                cusparseOperation_t      transA,
                int                      sizeOfMask,
                int                      mb,
                int                      nb,
                int                      nnzb,
                const double*            alpha,
                const cusparseMatDescr_t descrA,
                const double*            bsrSortedValA,
                const int*               bsrSortedMaskPtrA,
                const int*               bsrSortedRowPtrA,
                const int*               bsrSortedEndPtrA,
                const int*               bsrSortedColIndA,
                int                      blockDim,
                const double*            x,
                const double*            beta,
                double*                  y);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsrxmv(cusparseHandle_t         handle,
                cusparseDirection_t      dirA,
                cusparseOperation_t      transA,
                int                      sizeOfMask,
                int                      mb,
                int                      nb,
                int                      nnzb,
                const cuComplex*         alpha,
                const cusparseMatDescr_t descrA,
                const cuComplex*         bsrSortedValA,
                const int*               bsrSortedMaskPtrA,
                const int*               bsrSortedRowPtrA,
                const int*               bsrSortedEndPtrA,
                const int*               bsrSortedColIndA,
                int                      blockDim,
                const cuComplex*         x,
                const cuComplex*         beta,
                cuComplex*               y);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsrxmv(cusparseHandle_t         handle,
                cusparseDirection_t      dirA,
                cusparseOperation_t      transA,
                int                      sizeOfMask,
                int                      mb,
                int                      nb,
                int                      nnzb,
                const cuDoubleComplex*   alpha,
                const cusparseMatDescr_t descrA,
                const cuDoubleComplex*   bsrSortedValA,
                const int*               bsrSortedMaskPtrA,
                const int*               bsrSortedRowPtrA,
                const int*               bsrSortedEndPtrA,
                const int*               bsrSortedColIndA,
                int                      blockDim,
                const cuDoubleComplex*   x,
                const cuDoubleComplex*   beta,
                cuDoubleComplex*         y);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseXbsrsv2_zeroPivot(cusparseHandle_t handle,
                          bsrsv2Info_t     info,
                          int*             position);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsrsv2_bufferSize(cusparseHandle_t         handle,
                           cusparseDirection_t      dirA,
                           cusparseOperation_t      transA,
                           int                      mb,
                           int                      nnzb,
                           const cusparseMatDescr_t descrA,
                           float*                   bsrSortedValA,
                           const int*               bsrSortedRowPtrA,
                           const int*               bsrSortedColIndA,
                           int                      blockDim,
                           bsrsv2Info_t             info,
                           int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsrsv2_bufferSize(cusparseHandle_t         handle,
                           cusparseDirection_t      dirA,
                           cusparseOperation_t      transA,
                           int                      mb,
                           int                      nnzb,
                           const cusparseMatDescr_t descrA,
                           double*                  bsrSortedValA,
                           const int*               bsrSortedRowPtrA,
                           const int*               bsrSortedColIndA,
                           int                      blockDim,
                           bsrsv2Info_t             info,
                           int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsrsv2_bufferSize(cusparseHandle_t         handle,
                           cusparseDirection_t      dirA,
                           cusparseOperation_t      transA,
                           int                      mb,
                           int                      nnzb,
                           const cusparseMatDescr_t descrA,
                           cuComplex*               bsrSortedValA,
                           const int*               bsrSortedRowPtrA,
                           const int*               bsrSortedColIndA,
                           int                      blockDim,
                           bsrsv2Info_t             info,
                           int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsrsv2_bufferSize(cusparseHandle_t         handle,
                           cusparseDirection_t      dirA,
                           cusparseOperation_t      transA,
                           int                      mb,
                           int                      nnzb,
                           const cusparseMatDescr_t descrA,
                           cuDoubleComplex*         bsrSortedValA,
                           const int*               bsrSortedRowPtrA,
                           const int*               bsrSortedColIndA,
                           int                      blockDim,
                           bsrsv2Info_t             info,
                           int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsrsv2_bufferSizeExt(cusparseHandle_t         handle,
                              cusparseDirection_t      dirA,
                              cusparseOperation_t      transA,
                              int                      mb,
                              int                      nnzb,
                              const cusparseMatDescr_t descrA,
                              float*                   bsrSortedValA,
                              const int*               bsrSortedRowPtrA,
                              const int*               bsrSortedColIndA,
                              int                      blockSize,
                              bsrsv2Info_t             info,
                              size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsrsv2_bufferSizeExt(cusparseHandle_t         handle,
                              cusparseDirection_t      dirA,
                              cusparseOperation_t      transA,
                              int                      mb,
                              int                      nnzb,
                              const cusparseMatDescr_t descrA,
                              double*                  bsrSortedValA,
                              const int*               bsrSortedRowPtrA,
                              const int*               bsrSortedColIndA,
                              int                      blockSize,
                              bsrsv2Info_t             info,
                              size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsrsv2_bufferSizeExt(cusparseHandle_t         handle,
                              cusparseDirection_t      dirA,
                              cusparseOperation_t      transA,
                              int                      mb,
                              int                      nnzb,
                              const cusparseMatDescr_t descrA,
                              cuComplex*               bsrSortedValA,
                              const int*               bsrSortedRowPtrA,
                              const int*               bsrSortedColIndA,
                              int                      blockSize,
                              bsrsv2Info_t             info,
                              size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsrsv2_bufferSizeExt(cusparseHandle_t         handle,
                              cusparseDirection_t      dirA,
                              cusparseOperation_t      transA,
                              int                      mb,
                              int                      nnzb,
                              const cusparseMatDescr_t descrA,
                              cuDoubleComplex*         bsrSortedValA,
                              const int*               bsrSortedRowPtrA,
                              const int*               bsrSortedColIndA,
                              int                      blockSize,
                              bsrsv2Info_t             info,
                              size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsrsv2_analysis(cusparseHandle_t         handle,
                         cusparseDirection_t      dirA,
                         cusparseOperation_t      transA,
                         int                      mb,
                         int                      nnzb,
                         const cusparseMatDescr_t descrA,
                         const float*             bsrSortedValA,
                         const int*               bsrSortedRowPtrA,
                         const int*               bsrSortedColIndA,
                         int                      blockDim,
                         bsrsv2Info_t             info,
                         cusparseSolvePolicy_t    policy,
                         void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsrsv2_analysis(cusparseHandle_t         handle,
                         cusparseDirection_t      dirA,
                         cusparseOperation_t      transA,
                         int                      mb,
                         int                      nnzb,
                         const cusparseMatDescr_t descrA,
                         const double*            bsrSortedValA,
                         const int*               bsrSortedRowPtrA,
                         const int*               bsrSortedColIndA,
                         int                      blockDim,
                         bsrsv2Info_t             info,
                         cusparseSolvePolicy_t    policy,
                         void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsrsv2_analysis(cusparseHandle_t         handle,
                         cusparseDirection_t      dirA,
                         cusparseOperation_t      transA,
                         int                      mb,
                         int                      nnzb,
                         const cusparseMatDescr_t descrA,
                         const cuComplex*         bsrSortedValA,
                         const int*               bsrSortedRowPtrA,
                         const int*               bsrSortedColIndA,
                         int                      blockDim,
                         bsrsv2Info_t             info,
                         cusparseSolvePolicy_t    policy,
                         void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsrsv2_analysis(cusparseHandle_t         handle,
                         cusparseDirection_t      dirA,
                         cusparseOperation_t      transA,
                         int                      mb,
                         int                      nnzb,
                         const cusparseMatDescr_t descrA,
                         const cuDoubleComplex*   bsrSortedValA,
                         const int*               bsrSortedRowPtrA,
                         const int*               bsrSortedColIndA,
                         int                      blockDim,
                         bsrsv2Info_t             info,
                         cusparseSolvePolicy_t    policy,
                         void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsrsv2_solve(cusparseHandle_t         handle,
                      cusparseDirection_t      dirA,
                      cusparseOperation_t      transA,
                      int                      mb,
                      int                      nnzb,
                      const float*             alpha,
                      const cusparseMatDescr_t descrA,
                      const float*             bsrSortedValA,
                      const int*               bsrSortedRowPtrA,
                      const int*               bsrSortedColIndA,
                      int                      blockDim,
                      bsrsv2Info_t             info,
                      const float*             f,
                      float*                   x,
                      cusparseSolvePolicy_t    policy,
                      void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsrsv2_solve(cusparseHandle_t         handle,
                      cusparseDirection_t      dirA,
                      cusparseOperation_t      transA,
                      int                      mb,
                      int                      nnzb,
                      const double*            alpha,
                      const cusparseMatDescr_t descrA,
                      const double*            bsrSortedValA,
                      const int*               bsrSortedRowPtrA,
                      const int*               bsrSortedColIndA,
                      int                      blockDim,
                      bsrsv2Info_t             info,
                      const double*            f,
                      double*                  x,
                      cusparseSolvePolicy_t    policy,
                      void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsrsv2_solve(cusparseHandle_t         handle,
                      cusparseDirection_t      dirA,
                      cusparseOperation_t      transA,
                      int                      mb,
                      int                      nnzb,
                      const cuComplex*         alpha,
                      const cusparseMatDescr_t descrA,
                      const cuComplex*         bsrSortedValA,
                      const int*               bsrSortedRowPtrA,
                      const int*               bsrSortedColIndA,
                      int                      blockDim,
                      bsrsv2Info_t             info,
                      const cuComplex*         f,
                      cuComplex*               x,
                      cusparseSolvePolicy_t    policy,
                      void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsrsv2_solve(cusparseHandle_t         handle,
                      cusparseDirection_t      dirA,
                      cusparseOperation_t      transA,
                      int                      mb,
                      int                      nnzb,
                      const cuDoubleComplex*   alpha,
                      const cusparseMatDescr_t descrA,
                      const cuDoubleComplex*   bsrSortedValA,
                      const int*               bsrSortedRowPtrA,
                      const int*               bsrSortedColIndA,
                      int                      blockDim,
                      bsrsv2Info_t             info,
                      const cuDoubleComplex*   f,
                      cuDoubleComplex*         x,
                      cusparseSolvePolicy_t    policy,
                      void*                    pBuffer);

//##############################################################################
//# SPARSE LEVEL 3 ROUTINES
//##############################################################################

CUSPARSE_DEPRECATED_REPLACE_WITH(cusparseSpMM) // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseSbsrmm(cusparseHandle_t         handle,
               cusparseDirection_t      dirA,
               cusparseOperation_t      transA,
               cusparseOperation_t      transB,
               int                      mb,
               int                      n,
               int                      kb,
               int                      nnzb,
               const float*             alpha,
               const cusparseMatDescr_t descrA,
               const float* bsrSortedValA,
               const int*   bsrSortedRowPtrA,
               const int*   bsrSortedColIndA,
               const int    blockSize,
               const float* B,
               const int    ldb,
               const float* beta,
               float*       C,
               int          ldc);

CUSPARSE_DEPRECATED_REPLACE_WITH(cusparseSpMM) // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseDbsrmm(cusparseHandle_t         handle,
               cusparseDirection_t      dirA,
               cusparseOperation_t      transA,
               cusparseOperation_t      transB,
               int                      mb,
               int                      n,
               int                      kb,
               int                      nnzb,
               const double*            alpha,
               const cusparseMatDescr_t descrA,
               const double* bsrSortedValA,
               const int*    bsrSortedRowPtrA,
               const int*    bsrSortedColIndA,
               const int     blockSize,
               const double* B,
               const int     ldb,
               const double* beta,
               double*       C,
               int           ldc);

CUSPARSE_DEPRECATED_REPLACE_WITH(cusparseSpMM) // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseCbsrmm(cusparseHandle_t         handle,
               cusparseDirection_t      dirA,
               cusparseOperation_t      transA,
               cusparseOperation_t      transB,
               int                      mb,
               int                      n,
               int                      kb,
               int                      nnzb,
               const cuComplex*         alpha,
               const cusparseMatDescr_t descrA,
               const cuComplex* bsrSortedValA,
               const int*       bsrSortedRowPtrA,
               const int*       bsrSortedColIndA,
               const int        blockSize,
               const cuComplex* B,
               const int        ldb,
               const cuComplex* beta,
               cuComplex*       C,
               int              ldc);

CUSPARSE_DEPRECATED_REPLACE_WITH(cusparseSpMM) // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseZbsrmm(cusparseHandle_t         handle,
                cusparseDirection_t      dirA,
                cusparseOperation_t      transA,
                cusparseOperation_t      transB,
                int                      mb,
                int                      n,
                int                      kb,
                int                      nnzb,
                const cuDoubleComplex*   alpha,
                const cusparseMatDescr_t descrA,
                const cuDoubleComplex*   bsrSortedValA,
                const int*               bsrSortedRowPtrA,
                const int*               bsrSortedColIndA,
                const int                blockSize,
                const cuDoubleComplex*   B,
                const int                ldb,
                const cuDoubleComplex*   beta,
                cuDoubleComplex*         C,
                int                      ldc);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseXbsrsm2_zeroPivot(cusparseHandle_t handle,
                          bsrsm2Info_t     info,
                          int*             position);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsrsm2_bufferSize(cusparseHandle_t         handle,
                           cusparseDirection_t      dirA,
                           cusparseOperation_t      transA,
                           cusparseOperation_t      transXY,
                           int                      mb,
                           int                      n,
                           int                      nnzb,
                           const cusparseMatDescr_t descrA,
                           float*                   bsrSortedVal,
                           const int*               bsrSortedRowPtr,
                           const int*               bsrSortedColInd,
                           int                      blockSize,
                           bsrsm2Info_t             info,
                           int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsrsm2_bufferSize(cusparseHandle_t         handle,
                           cusparseDirection_t      dirA,
                           cusparseOperation_t      transA,
                           cusparseOperation_t      transXY,
                           int                      mb,
                           int                      n,
                           int                      nnzb,
                           const cusparseMatDescr_t descrA,
                           double*                  bsrSortedVal,
                           const int*               bsrSortedRowPtr,
                           const int*               bsrSortedColInd,
                           int                      blockSize,
                           bsrsm2Info_t             info,
                           int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsrsm2_bufferSize(cusparseHandle_t         handle,
                           cusparseDirection_t      dirA,
                           cusparseOperation_t      transA,
                           cusparseOperation_t      transXY,
                           int                      mb,
                           int                      n,
                           int                      nnzb,
                           const cusparseMatDescr_t descrA,
                           cuComplex*               bsrSortedVal,
                           const int*               bsrSortedRowPtr,
                           const int*               bsrSortedColInd,
                           int                      blockSize,
                           bsrsm2Info_t             info,
                           int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsrsm2_bufferSize(cusparseHandle_t         handle,
                           cusparseDirection_t      dirA,
                           cusparseOperation_t      transA,
                           cusparseOperation_t      transXY,
                           int                      mb,
                           int                      n,
                           int                      nnzb,
                           const cusparseMatDescr_t descrA,
                           cuDoubleComplex*         bsrSortedVal,
                           const int*               bsrSortedRowPtr,
                           const int*               bsrSortedColInd,
                           int                      blockSize,
                           bsrsm2Info_t             info,
                           int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsrsm2_bufferSizeExt(cusparseHandle_t         handle,
                              cusparseDirection_t      dirA,
                              cusparseOperation_t      transA,
                              cusparseOperation_t      transB,
                              int                      mb,
                              int                      n,
                              int                      nnzb,
                              const cusparseMatDescr_t descrA,
                              float*                   bsrSortedVal,
                              const int*               bsrSortedRowPtr,
                              const int*               bsrSortedColInd,
                              int                      blockSize,
                              bsrsm2Info_t             info,
                              size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsrsm2_bufferSizeExt(cusparseHandle_t         handle,
                              cusparseDirection_t      dirA,
                              cusparseOperation_t      transA,
                              cusparseOperation_t      transB,
                              int                      mb,
                              int                      n,
                              int                      nnzb,
                              const cusparseMatDescr_t descrA,
                              double*                  bsrSortedVal,
                              const int*               bsrSortedRowPtr,
                              const int*               bsrSortedColInd,
                              int                      blockSize,
                              bsrsm2Info_t             info,
                              size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsrsm2_bufferSizeExt(cusparseHandle_t         handle,
                              cusparseDirection_t      dirA,
                              cusparseOperation_t      transA,
                              cusparseOperation_t      transB,
                              int                      mb,
                              int                      n,
                              int                      nnzb,
                              const cusparseMatDescr_t descrA,
                              cuComplex*               bsrSortedVal,
                              const int*               bsrSortedRowPtr,
                              const int*               bsrSortedColInd,
                              int                      blockSize,
                              bsrsm2Info_t             info,
                              size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsrsm2_bufferSizeExt(cusparseHandle_t         handle,
                              cusparseDirection_t      dirA,
                              cusparseOperation_t      transA,
                              cusparseOperation_t      transB,
                              int                      mb,
                              int                      n,
                              int                      nnzb,
                              const cusparseMatDescr_t descrA,
                              cuDoubleComplex*         bsrSortedVal,
                              const int*               bsrSortedRowPtr,
                              const int*               bsrSortedColInd,
                              int                      blockSize,
                              bsrsm2Info_t             info,
                              size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsrsm2_analysis(cusparseHandle_t         handle,
                         cusparseDirection_t      dirA,
                         cusparseOperation_t      transA,
                         cusparseOperation_t      transXY,
                         int                      mb,
                         int                      n,
                         int                      nnzb,
                         const cusparseMatDescr_t descrA,
                         const float*             bsrSortedVal,
                         const int*               bsrSortedRowPtr,
                         const int*               bsrSortedColInd,
                         int                      blockSize,
                         bsrsm2Info_t             info,
                         cusparseSolvePolicy_t    policy,
                         void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsrsm2_analysis(cusparseHandle_t         handle,
                         cusparseDirection_t      dirA,
                         cusparseOperation_t      transA,
                         cusparseOperation_t      transXY,
                         int                      mb,
                         int                      n,
                         int                      nnzb,
                         const cusparseMatDescr_t descrA,
                         const double*            bsrSortedVal,
                         const int*               bsrSortedRowPtr,
                         const int*               bsrSortedColInd,
                         int                      blockSize,
                         bsrsm2Info_t             info,
                         cusparseSolvePolicy_t    policy,
                         void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsrsm2_analysis(cusparseHandle_t         handle,
                         cusparseDirection_t      dirA,
                         cusparseOperation_t      transA,
                         cusparseOperation_t      transXY,
                         int                      mb,
                         int                      n,
                         int                      nnzb,
                         const cusparseMatDescr_t descrA,
                         const cuComplex*         bsrSortedVal,
                         const int*               bsrSortedRowPtr,
                         const int*               bsrSortedColInd,
                         int                      blockSize,
                         bsrsm2Info_t             info,
                         cusparseSolvePolicy_t    policy,
                         void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsrsm2_analysis(cusparseHandle_t         handle,
                         cusparseDirection_t      dirA,
                         cusparseOperation_t      transA,
                         cusparseOperation_t      transXY,
                         int                      mb,
                         int                      n,
                         int                      nnzb,
                         const cusparseMatDescr_t descrA,
                         const cuDoubleComplex*   bsrSortedVal,
                         const int*               bsrSortedRowPtr,
                         const int*               bsrSortedColInd,
                         int                      blockSize,
                         bsrsm2Info_t             info,
                         cusparseSolvePolicy_t    policy,
                         void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsrsm2_solve(cusparseHandle_t         handle,
                      cusparseDirection_t      dirA,
                      cusparseOperation_t      transA,
                      cusparseOperation_t      transXY,
                      int                      mb,
                      int                      n,
                      int                      nnzb,
                      const float*             alpha,
                      const cusparseMatDescr_t descrA,
                      const float*             bsrSortedVal,
                      const int*               bsrSortedRowPtr,
                      const int*               bsrSortedColInd,
                      int                      blockSize,
                      bsrsm2Info_t             info,
                      const float*             B,
                      int                      ldb,
                      float*                   X,
                      int                      ldx,
                      cusparseSolvePolicy_t    policy,
                      void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsrsm2_solve(cusparseHandle_t         handle,
                      cusparseDirection_t      dirA,
                      cusparseOperation_t      transA,
                      cusparseOperation_t      transXY,
                      int                      mb,
                      int                      n,
                      int                      nnzb,
                      const double*            alpha,
                      const cusparseMatDescr_t descrA,
                      const double*            bsrSortedVal,
                      const int*               bsrSortedRowPtr,
                      const int*               bsrSortedColInd,
                      int                      blockSize,
                      bsrsm2Info_t             info,
                      const double*            B,
                      int                      ldb,
                      double*                  X,
                      int                      ldx,
                      cusparseSolvePolicy_t    policy,
                      void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsrsm2_solve(cusparseHandle_t         handle,
                      cusparseDirection_t      dirA,
                      cusparseOperation_t      transA,
                      cusparseOperation_t      transXY,
                      int                      mb,
                      int                      n,
                      int                      nnzb,
                      const cuComplex*         alpha,
                      const cusparseMatDescr_t descrA,
                      const cuComplex*         bsrSortedVal,
                      const int*               bsrSortedRowPtr,
                      const int*               bsrSortedColInd,
                      int                      blockSize,
                      bsrsm2Info_t             info,
                      const cuComplex*         B,
                      int                      ldb,
                      cuComplex*               X,
                      int                      ldx,
                      cusparseSolvePolicy_t    policy,
                      void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsrsm2_solve(cusparseHandle_t         handle,
                      cusparseDirection_t      dirA,
                      cusparseOperation_t      transA,
                      cusparseOperation_t      transXY,
                      int                      mb,
                      int                      n,
                      int                      nnzb,
                      const cuDoubleComplex*   alpha,
                      const cusparseMatDescr_t descrA,
                      const cuDoubleComplex*   bsrSortedVal,
                      const int*               bsrSortedRowPtr,
                      const int*               bsrSortedColInd,
                      int                      blockSize,
                      bsrsm2Info_t             info,
                      const cuDoubleComplex*   B,
                      int                      ldb,
                      cuDoubleComplex*         X,
                      int                      ldx,
                      cusparseSolvePolicy_t    policy,
                      void*                    pBuffer);

//##############################################################################
//# PRECONDITIONERS
//##############################################################################

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseScsrilu02_numericBoost(cusparseHandle_t handle,
                               csrilu02Info_t   info,
                               int              enable_boost,
                               double*          tol,
                               float*           boost_val);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDcsrilu02_numericBoost(cusparseHandle_t handle,
                               csrilu02Info_t   info,
                               int              enable_boost,
                               double*          tol,
                               double*          boost_val);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCcsrilu02_numericBoost(cusparseHandle_t handle,
                               csrilu02Info_t   info,
                               int              enable_boost,
                               double*          tol,
                               cuComplex*       boost_val);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZcsrilu02_numericBoost(cusparseHandle_t handle,
                               csrilu02Info_t   info,
                               int              enable_boost,
                               double*          tol,
                               cuDoubleComplex* boost_val);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseXcsrilu02_zeroPivot(cusparseHandle_t handle,
                            csrilu02Info_t   info,
                            int*             position);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseScsrilu02_bufferSize(cusparseHandle_t         handle,
                             int                      m,
                             int                      nnz,
                             const cusparseMatDescr_t descrA,
                             float*                   csrSortedValA,
                             const int*               csrSortedRowPtrA,
                             const int*               csrSortedColIndA,
                             csrilu02Info_t           info,
                             int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDcsrilu02_bufferSize(cusparseHandle_t         handle,
                             int                      m,
                             int                      nnz,
                             const cusparseMatDescr_t descrA,
                             double*                  csrSortedValA,
                             const int*               csrSortedRowPtrA,
                             const int*               csrSortedColIndA,
                             csrilu02Info_t           info,
                             int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCcsrilu02_bufferSize(cusparseHandle_t         handle,
                             int                      m,
                             int                      nnz,
                             const cusparseMatDescr_t descrA,
                             cuComplex*               csrSortedValA,
                             const int*               csrSortedRowPtrA,
                             const int*               csrSortedColIndA,
                             csrilu02Info_t           info,
                             int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZcsrilu02_bufferSize(cusparseHandle_t         handle,
                             int                      m,
                             int                      nnz,
                             const cusparseMatDescr_t descrA,
                             cuDoubleComplex*         csrSortedValA,
                             const int*               csrSortedRowPtrA,
                             const int*               csrSortedColIndA,
                             csrilu02Info_t           info,
                             int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseScsrilu02_bufferSizeExt(cusparseHandle_t         handle,
                                int                      m,
                                int                      nnz,
                                const cusparseMatDescr_t descrA,
                                float*                   csrSortedVal,
                                const int*               csrSortedRowPtr,
                                const int*               csrSortedColInd,
                                csrilu02Info_t           info,
                                size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDcsrilu02_bufferSizeExt(cusparseHandle_t         handle,
                                int                      m,
                                int                      nnz,
                                const cusparseMatDescr_t descrA,
                                double*                  csrSortedVal,
                                const int*               csrSortedRowPtr,
                                const int*               csrSortedColInd,
                                csrilu02Info_t           info,
                                size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCcsrilu02_bufferSizeExt(cusparseHandle_t         handle,
                                int                      m,
                                int                      nnz,
                                const cusparseMatDescr_t descrA,
                                cuComplex*               csrSortedVal,
                                const int*               csrSortedRowPtr,
                                const int*               csrSortedColInd,
                                csrilu02Info_t           info,
                                size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZcsrilu02_bufferSizeExt(cusparseHandle_t         handle,
                                int                      m,
                                int                      nnz,
                                const cusparseMatDescr_t descrA,
                                cuDoubleComplex*         csrSortedVal,
                                const int*               csrSortedRowPtr,
                                const int*               csrSortedColInd,
                                csrilu02Info_t           info,
                                size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseScsrilu02_analysis(cusparseHandle_t         handle,
                           int                      m,
                           int                      nnz,
                           const cusparseMatDescr_t descrA,
                           const float*             csrSortedValA,
                           const int*               csrSortedRowPtrA,
                           const int*               csrSortedColIndA,
                           csrilu02Info_t           info,
                           cusparseSolvePolicy_t    policy,
                           void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDcsrilu02_analysis(cusparseHandle_t         handle,
                           int                      m,
                           int                      nnz,
                           const cusparseMatDescr_t descrA,
                           const double*            csrSortedValA,
                           const int*               csrSortedRowPtrA,
                           const int*               csrSortedColIndA,
                           csrilu02Info_t           info,
                           cusparseSolvePolicy_t    policy,
                           void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCcsrilu02_analysis(cusparseHandle_t         handle,
                           int                      m,
                           int                      nnz,
                           const cusparseMatDescr_t descrA,
                           const cuComplex*         csrSortedValA,
                           const int*               csrSortedRowPtrA,
                           const int*               csrSortedColIndA,
                           csrilu02Info_t           info,
                           cusparseSolvePolicy_t    policy,
                           void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZcsrilu02_analysis(cusparseHandle_t         handle,
                           int                      m,
                           int                      nnz,
                           const cusparseMatDescr_t descrA,
                           const cuDoubleComplex*   csrSortedValA,
                           const int*               csrSortedRowPtrA,
                           const int*               csrSortedColIndA,
                           csrilu02Info_t           info,
                           cusparseSolvePolicy_t    policy,
                           void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseScsrilu02(cusparseHandle_t         handle,
                  int                      m,
                  int                      nnz,
                  const cusparseMatDescr_t descrA,
                  float*                   csrSortedValA_valM,
                  const int*            csrSortedRowPtrA,
                  const int*            csrSortedColIndA,
                  csrilu02Info_t        info,
                  cusparseSolvePolicy_t policy,
                  void*                 pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDcsrilu02(cusparseHandle_t         handle,
                  int                      m,
                  int                      nnz,
                  const cusparseMatDescr_t descrA,
                  double*                  csrSortedValA_valM,
                  const int*            csrSortedRowPtrA,
                  const int*            csrSortedColIndA,
                  csrilu02Info_t        info,
                  cusparseSolvePolicy_t policy,
                  void*                 pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCcsrilu02(cusparseHandle_t         handle,
                  int                      m,
                  int                      nnz,
                  const cusparseMatDescr_t descrA,
                  cuComplex*               csrSortedValA_valM,
                  const int*            csrSortedRowPtrA,
                  const int*            csrSortedColIndA,
                  csrilu02Info_t        info,
                  cusparseSolvePolicy_t policy,
                  void*                 pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZcsrilu02(cusparseHandle_t         handle,
                  int                      m,
                  int                      nnz,
                  const cusparseMatDescr_t descrA,
                  cuDoubleComplex*         csrSortedValA_valM,
                  const int*            csrSortedRowPtrA,
                  const int*            csrSortedColIndA,
                  csrilu02Info_t        info,
                  cusparseSolvePolicy_t policy,
                  void*                 pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsrilu02_numericBoost(cusparseHandle_t handle,
                               bsrilu02Info_t   info,
                               int              enable_boost,
                               double*          tol,
                               float*           boost_val);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsrilu02_numericBoost(cusparseHandle_t handle,
                               bsrilu02Info_t   info,
                               int              enable_boost,
                               double*          tol,
                               double*          boost_val);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsrilu02_numericBoost(cusparseHandle_t handle,
                               bsrilu02Info_t   info,
                               int              enable_boost,
                               double*          tol,
                               cuComplex*       boost_val);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsrilu02_numericBoost(cusparseHandle_t handle,
                               bsrilu02Info_t   info,
                               int              enable_boost,
                               double*          tol,
                               cuDoubleComplex* boost_val);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseXbsrilu02_zeroPivot(cusparseHandle_t handle,
                            bsrilu02Info_t   info,
                            int*             position);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsrilu02_bufferSize(cusparseHandle_t         handle,
                             cusparseDirection_t      dirA,
                             int                      mb,
                             int                      nnzb,
                             const cusparseMatDescr_t descrA,
                             float*                   bsrSortedVal,
                             const int*               bsrSortedRowPtr,
                             const int*               bsrSortedColInd,
                             int                      blockDim,
                             bsrilu02Info_t           info,
                             int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsrilu02_bufferSize(cusparseHandle_t         handle,
                             cusparseDirection_t      dirA,
                             int                      mb,
                             int                      nnzb,
                             const cusparseMatDescr_t descrA,
                             double*                  bsrSortedVal,
                             const int*               bsrSortedRowPtr,
                             const int*               bsrSortedColInd,
                             int                      blockDim,
                             bsrilu02Info_t           info,
                             int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsrilu02_bufferSize(cusparseHandle_t         handle,
                             cusparseDirection_t      dirA,
                             int                      mb,
                             int                      nnzb,
                             const cusparseMatDescr_t descrA,
                             cuComplex*               bsrSortedVal,
                             const int*               bsrSortedRowPtr,
                             const int*               bsrSortedColInd,
                             int                      blockDim,
                             bsrilu02Info_t           info,
                             int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsrilu02_bufferSize(cusparseHandle_t         handle,
                             cusparseDirection_t      dirA,
                             int                      mb,
                             int                      nnzb,
                             const cusparseMatDescr_t descrA,
                             cuDoubleComplex*         bsrSortedVal,
                             const int*               bsrSortedRowPtr,
                             const int*               bsrSortedColInd,
                             int                      blockDim,
                             bsrilu02Info_t           info,
                             int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsrilu02_bufferSizeExt(cusparseHandle_t         handle,
                                cusparseDirection_t      dirA,
                                int                      mb,
                                int                      nnzb,
                                const cusparseMatDescr_t descrA,
                                float*                   bsrSortedVal,
                                const int*               bsrSortedRowPtr,
                                const int*               bsrSortedColInd,
                                int                      blockSize,
                                bsrilu02Info_t           info,
                                size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsrilu02_bufferSizeExt(cusparseHandle_t         handle,
                                cusparseDirection_t      dirA,
                                int                      mb,
                                int                      nnzb,
                                const cusparseMatDescr_t descrA,
                                double*                  bsrSortedVal,
                                const int*               bsrSortedRowPtr,
                                const int*               bsrSortedColInd,
                                int                      blockSize,
                                bsrilu02Info_t           info,
                                size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsrilu02_bufferSizeExt(cusparseHandle_t         handle,
                                cusparseDirection_t      dirA,
                                int                      mb,
                                int                      nnzb,
                                const cusparseMatDescr_t descrA,
                                cuComplex*               bsrSortedVal,
                                const int*               bsrSortedRowPtr,
                                const int*               bsrSortedColInd,
                                int                      blockSize,
                                bsrilu02Info_t           info,
                                size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsrilu02_bufferSizeExt(cusparseHandle_t         handle,
                               cusparseDirection_t      dirA,
                               int                      mb,
                               int                      nnzb,
                               const cusparseMatDescr_t descrA,
                               cuDoubleComplex*         bsrSortedVal,
                               const int*               bsrSortedRowPtr,
                               const int*               bsrSortedColInd,
                               int                      blockSize,
                               bsrilu02Info_t           info,
                               size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsrilu02_analysis(cusparseHandle_t         handle,
                           cusparseDirection_t      dirA,
                           int                      mb,
                           int                      nnzb,
                           const cusparseMatDescr_t descrA,
                           float*                   bsrSortedVal,
                           const int*               bsrSortedRowPtr,
                           const int*               bsrSortedColInd,
                           int                      blockDim,
                           bsrilu02Info_t           info,
                           cusparseSolvePolicy_t    policy,
                           void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsrilu02_analysis(cusparseHandle_t         handle,
                           cusparseDirection_t      dirA,
                           int                      mb,
                           int                      nnzb,
                           const cusparseMatDescr_t descrA,
                           double*                  bsrSortedVal,
                           const int*               bsrSortedRowPtr,
                           const int*               bsrSortedColInd,
                           int                      blockDim,
                           bsrilu02Info_t           info,
                           cusparseSolvePolicy_t    policy,
                           void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsrilu02_analysis(cusparseHandle_t         handle,
                           cusparseDirection_t      dirA,
                           int                      mb,
                           int                      nnzb,
                           const cusparseMatDescr_t descrA,
                           cuComplex*               bsrSortedVal,
                           const int*               bsrSortedRowPtr,
                           const int*               bsrSortedColInd,
                           int                      blockDim,
                           bsrilu02Info_t           info,
                           cusparseSolvePolicy_t    policy,
                           void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsrilu02_analysis(cusparseHandle_t         handle,
                           cusparseDirection_t      dirA,
                           int                      mb,
                           int                      nnzb,
                           const cusparseMatDescr_t descrA,
                           cuDoubleComplex*         bsrSortedVal,
                           const int*               bsrSortedRowPtr,
                           const int*               bsrSortedColInd,
                           int                      blockDim,
                           bsrilu02Info_t           info,
                           cusparseSolvePolicy_t    policy,
                           void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsrilu02(cusparseHandle_t         handle,
                  cusparseDirection_t      dirA,
                  int                      mb,
                  int                      nnzb,
                  const cusparseMatDescr_t descrA,
                  float*                   bsrSortedVal,
                  const int*               bsrSortedRowPtr,
                  const int*               bsrSortedColInd,
                  int                      blockDim,
                  bsrilu02Info_t           info,
                  cusparseSolvePolicy_t    policy,
                  void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsrilu02(cusparseHandle_t         handle,
                  cusparseDirection_t      dirA,
                  int                      mb,
                  int                      nnzb,
                  const cusparseMatDescr_t descrA,
                  double*                  bsrSortedVal,
                  const int*               bsrSortedRowPtr,
                  const int*               bsrSortedColInd,
                  int                      blockDim,
                  bsrilu02Info_t           info,
                  cusparseSolvePolicy_t    policy,
                  void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsrilu02(cusparseHandle_t         handle,
                  cusparseDirection_t      dirA,
                  int                      mb,
                  int                      nnzb,
                  const cusparseMatDescr_t descrA,
                  cuComplex*               bsrSortedVal,
                  const int*               bsrSortedRowPtr,
                  const int*               bsrSortedColInd,
                  int                      blockDim,
                  bsrilu02Info_t           info,
                  cusparseSolvePolicy_t    policy,
                  void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsrilu02(cusparseHandle_t         handle,
                  cusparseDirection_t      dirA,
                  int                      mb,
                  int                      nnzb,
                  const cusparseMatDescr_t descrA,
                  cuDoubleComplex*         bsrSortedVal,
                  const int*               bsrSortedRowPtr,
                  const int*               bsrSortedColInd,
                  int                      blockDim,
                  bsrilu02Info_t           info,
                  cusparseSolvePolicy_t    policy,
                  void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseXcsric02_zeroPivot(cusparseHandle_t handle,
                           csric02Info_t    info,
                           int*             position);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseScsric02_bufferSize(cusparseHandle_t         handle,
                            int                      m,
                            int                      nnz,
                            const cusparseMatDescr_t descrA,
                            float*                   csrSortedValA,
                            const int*               csrSortedRowPtrA,
                            const int*               csrSortedColIndA,
                            csric02Info_t            info,
                            int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDcsric02_bufferSize(cusparseHandle_t         handle,
                            int                      m,
                            int                      nnz,
                            const cusparseMatDescr_t descrA,
                            double*                  csrSortedValA,
                            const int*               csrSortedRowPtrA,
                            const int*               csrSortedColIndA,
                            csric02Info_t            info,
                            int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCcsric02_bufferSize(cusparseHandle_t         handle,
                            int                      m,
                            int                      nnz,
                            const cusparseMatDescr_t descrA,
                            cuComplex*               csrSortedValA,
                            const int*               csrSortedRowPtrA,
                            const int*               csrSortedColIndA,
                            csric02Info_t            info,
                            int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZcsric02_bufferSize(cusparseHandle_t         handle,
                            int                      m,
                            int                      nnz,
                            const cusparseMatDescr_t descrA,
                            cuDoubleComplex*         csrSortedValA,
                            const int*               csrSortedRowPtrA,
                            const int*               csrSortedColIndA,
                            csric02Info_t            info,
                            int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseScsric02_bufferSizeExt(cusparseHandle_t         handle,
                               int                      m,
                               int                      nnz,
                               const cusparseMatDescr_t descrA,
                               float*                   csrSortedVal,
                               const int*               csrSortedRowPtr,
                               const int*               csrSortedColInd,
                               csric02Info_t            info,
                               size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDcsric02_bufferSizeExt(cusparseHandle_t         handle,
                               int                      m,
                               int                      nnz,
                               const cusparseMatDescr_t descrA,
                               double*                  csrSortedVal,
                               const int*               csrSortedRowPtr,
                               const int*               csrSortedColInd,
                               csric02Info_t            info,
                               size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCcsric02_bufferSizeExt(cusparseHandle_t         handle,
                               int                      m,
                               int                      nnz,
                               const cusparseMatDescr_t descrA,
                               cuComplex*               csrSortedVal,
                               const int*               csrSortedRowPtr,
                               const int*               csrSortedColInd,
                               csric02Info_t            info,
                               size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZcsric02_bufferSizeExt(cusparseHandle_t         handle,
                               int                      m,
                               int                      nnz,
                               const cusparseMatDescr_t descrA,
                               cuDoubleComplex*         csrSortedVal,
                               const int*               csrSortedRowPtr,
                               const int*               csrSortedColInd,
                               csric02Info_t            info,
                               size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseScsric02_analysis(cusparseHandle_t         handle,
                          int                      m,
                          int                      nnz,
                          const cusparseMatDescr_t descrA,
                          const float*             csrSortedValA,
                          const int*               csrSortedRowPtrA,
                          const int*               csrSortedColIndA,
                          csric02Info_t            info,
                          cusparseSolvePolicy_t    policy,
                          void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDcsric02_analysis(cusparseHandle_t         handle,
                          int                      m,
                          int                      nnz,
                          const cusparseMatDescr_t descrA,
                          const double*            csrSortedValA,
                          const int*               csrSortedRowPtrA,
                          const int*               csrSortedColIndA,
                          csric02Info_t            info,
                          cusparseSolvePolicy_t    policy,
                          void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCcsric02_analysis(cusparseHandle_t         handle,
                          int                      m,
                          int                      nnz,
                          const cusparseMatDescr_t descrA,
                          const cuComplex*         csrSortedValA,
                          const int*               csrSortedRowPtrA,
                          const int*               csrSortedColIndA,
                          csric02Info_t            info,
                          cusparseSolvePolicy_t    policy,
                          void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZcsric02_analysis(cusparseHandle_t         handle,
                          int                      m,
                          int                      nnz,
                          const cusparseMatDescr_t descrA,
                          const cuDoubleComplex*   csrSortedValA,
                          const int*               csrSortedRowPtrA,
                          const int*               csrSortedColIndA,
                          csric02Info_t            info,
                          cusparseSolvePolicy_t    policy,
                          void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseScsric02(cusparseHandle_t         handle,
                 int                      m,
                 int                      nnz,
                 const cusparseMatDescr_t descrA,
                 float*                   csrSortedValA_valM,
                 const int*               csrSortedRowPtrA,
                 const int*               csrSortedColIndA,
                 csric02Info_t            info,
                 cusparseSolvePolicy_t    policy,
                 void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDcsric02(cusparseHandle_t         handle,
                 int                      m,
                 int                      nnz,
                 const cusparseMatDescr_t descrA,
                 double*                  csrSortedValA_valM,
                 const int*               csrSortedRowPtrA,
                 const int*               csrSortedColIndA,
                 csric02Info_t            info,
                 cusparseSolvePolicy_t    policy,
                 void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCcsric02(cusparseHandle_t         handle,
                 int                      m,
                 int                      nnz,
                 const cusparseMatDescr_t descrA,
                 cuComplex*               csrSortedValA_valM,
                 const int*               csrSortedRowPtrA,
                 const int*               csrSortedColIndA,
                 csric02Info_t            info,
                 cusparseSolvePolicy_t    policy,
                 void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZcsric02(cusparseHandle_t         handle,
                 int                      m,
                 int                      nnz,
                 const cusparseMatDescr_t descrA,
                 cuDoubleComplex*         csrSortedValA_valM,
                 const int*               csrSortedRowPtrA,
                 const int*               csrSortedColIndA,
                 csric02Info_t            info,
                 cusparseSolvePolicy_t    policy,
                 void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseXbsric02_zeroPivot(cusparseHandle_t handle,
                           bsric02Info_t    info,
                           int*             position);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsric02_bufferSize(cusparseHandle_t         handle,
                            cusparseDirection_t      dirA,
                            int                      mb,
                            int                      nnzb,
                            const cusparseMatDescr_t descrA,
                            float*                   bsrSortedVal,
                            const int*               bsrSortedRowPtr,
                            const int*               bsrSortedColInd,
                            int                      blockDim,
                            bsric02Info_t            info,
                            int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsric02_bufferSize(cusparseHandle_t         handle,
                            cusparseDirection_t      dirA,
                            int                      mb,
                            int                      nnzb,
                            const cusparseMatDescr_t descrA,
                            double*                  bsrSortedVal,
                            const int*               bsrSortedRowPtr,
                            const int*               bsrSortedColInd,
                            int                      blockDim,
                            bsric02Info_t            info,
                            int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsric02_bufferSize(cusparseHandle_t         handle,
                            cusparseDirection_t      dirA,
                            int                      mb,
                            int                      nnzb,
                            const cusparseMatDescr_t descrA,
                            cuComplex*               bsrSortedVal,
                            const int*               bsrSortedRowPtr,
                            const int*               bsrSortedColInd,
                            int                      blockDim,
                            bsric02Info_t            info,
                            int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsric02_bufferSize(cusparseHandle_t         handle,
                            cusparseDirection_t      dirA,
                            int                      mb,
                            int                      nnzb,
                            const cusparseMatDescr_t descrA,
                            cuDoubleComplex*         bsrSortedVal,
                            const int*               bsrSortedRowPtr,
                            const int*               bsrSortedColInd,
                            int                      blockDim,
                            bsric02Info_t            info,
                            int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsric02_bufferSizeExt(cusparseHandle_t         handle,
                               cusparseDirection_t      dirA,
                               int                      mb,
                               int                      nnzb,
                               const cusparseMatDescr_t descrA,
                               float*                   bsrSortedVal,
                               const int*               bsrSortedRowPtr,
                               const int*               bsrSortedColInd,
                               int                      blockSize,
                               bsric02Info_t            info,
                               size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsric02_bufferSizeExt(cusparseHandle_t         handle,
                               cusparseDirection_t      dirA,
                               int                      mb,
                               int                      nnzb,
                               const cusparseMatDescr_t descrA,
                               double*                  bsrSortedVal,
                               const int*               bsrSortedRowPtr,
                               const int*               bsrSortedColInd,
                               int                      blockSize,
                               bsric02Info_t            info,
                               size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsric02_bufferSizeExt(cusparseHandle_t         handle,
                               cusparseDirection_t      dirA,
                               int                      mb,
                               int                      nnzb,
                               const cusparseMatDescr_t descrA,
                               cuComplex*               bsrSortedVal,
                               const int*               bsrSortedRowPtr,
                               const int*               bsrSortedColInd,
                               int                      blockSize,
                               bsric02Info_t            info,
                               size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsric02_bufferSizeExt(cusparseHandle_t         handle,
                               cusparseDirection_t      dirA,
                               int                      mb,
                               int                      nnzb,
                               const cusparseMatDescr_t descrA,
                               cuDoubleComplex*         bsrSortedVal,
                               const int*               bsrSortedRowPtr,
                               const int*               bsrSortedColInd,
                               int                      blockSize,
                               bsric02Info_t            info,
                               size_t*                  pBufferSize);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsric02_analysis(cusparseHandle_t         handle,
                          cusparseDirection_t      dirA,
                          int                      mb,
                          int                      nnzb,
                          const cusparseMatDescr_t descrA,
                          const float*             bsrSortedVal,
                          const int*               bsrSortedRowPtr,
                          const int*               bsrSortedColInd,
                          int                      blockDim,
                          bsric02Info_t            info,
                          cusparseSolvePolicy_t    policy,
                          void*                    pInputBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsric02_analysis(cusparseHandle_t         handle,
                          cusparseDirection_t      dirA,
                          int                      mb,
                          int                      nnzb,
                          const cusparseMatDescr_t descrA,
                          const double*            bsrSortedVal,
                          const int*               bsrSortedRowPtr,
                          const int*               bsrSortedColInd,
                          int                      blockDim,
                          bsric02Info_t            info,
                          cusparseSolvePolicy_t    policy,
                          void*                    pInputBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsric02_analysis(cusparseHandle_t         handle,
                          cusparseDirection_t      dirA,
                          int                      mb,
                          int                      nnzb,
                          const cusparseMatDescr_t descrA,
                          const cuComplex*         bsrSortedVal,
                          const int*               bsrSortedRowPtr,
                          const int*               bsrSortedColInd,
                          int                      blockDim,
                          bsric02Info_t            info,
                          cusparseSolvePolicy_t    policy,
                          void*                    pInputBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsric02_analysis(cusparseHandle_t         handle,
                          cusparseDirection_t      dirA,
                          int                      mb,
                          int                      nnzb,
                          const cusparseMatDescr_t descrA,
                          const cuDoubleComplex*   bsrSortedVal,
                          const int*               bsrSortedRowPtr,
                          const int*               bsrSortedColInd,
                          int                      blockDim,
                          bsric02Info_t            info,
                          cusparseSolvePolicy_t    policy,
                          void*                    pInputBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSbsric02(cusparseHandle_t         handle,
                 cusparseDirection_t      dirA,
                 int                      mb,
                 int                      nnzb,
                 const cusparseMatDescr_t descrA,
                 float*                   bsrSortedVal,
                 const int*               bsrSortedRowPtr,
                 const int*               bsrSortedColInd,
                 int                      blockDim,
                 bsric02Info_t            info,
                 cusparseSolvePolicy_t    policy,
                 void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDbsric02(cusparseHandle_t         handle,
                 cusparseDirection_t      dirA,
                 int                      mb,
                 int                      nnzb,
                 const cusparseMatDescr_t descrA,
                 double*                  bsrSortedVal,
                 const int*               bsrSortedRowPtr,
                 const int*               bsrSortedColInd,
                 int                      blockDim,
                 bsric02Info_t            info,
                 cusparseSolvePolicy_t    policy,
                 void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCbsric02(cusparseHandle_t         handle,
                 cusparseDirection_t      dirA,
                 int                      mb,
                 int                      nnzb,
                 const cusparseMatDescr_t descrA,
                 cuComplex*               bsrSortedVal,
                 const int*               bsrSortedRowPtr,
                 const int*
                      bsrSortedColInd,
                 int                      blockDim,
                 bsric02Info_t            info,
                 cusparseSolvePolicy_t    policy,
                 void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZbsric02(cusparseHandle_t         handle,
                 cusparseDirection_t      dirA,
                 int                      mb,
                 int                      nnzb,
                 const cusparseMatDescr_t descrA,
                 cuDoubleComplex*         bsrSortedVal,
                 const int*               bsrSortedRowPtr,
                 const int*               bsrSortedColInd,
                 int                      blockDim,
                 bsric02Info_t            info,
                 cusparseSolvePolicy_t    policy,
                 void*                    pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseSgtsv2_bufferSizeExt(cusparseHandle_t handle,
                             int              m,
                             int              n,
                             const float*     dl,
                             const float*     d,
                             const float*     du,
                             const float*     B,
                             int              ldb,
                             size_t*          bufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseDgtsv2_bufferSizeExt(cusparseHandle_t handle,
                             int              m,
                             int              n,
                             const double*    dl,
                             const double*    d,
                             const double*    du,
                             const double*    B,
                             int              ldb,
                             size_t*          bufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseCgtsv2_bufferSizeExt(cusparseHandle_t handle,
                             int              m,
                             int              n,
                             const cuComplex* dl,
                             const cuComplex* d,
                             const cuComplex* du,
                             const cuComplex* B,
                             int              ldb,
                             size_t*          bufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseZgtsv2_bufferSizeExt(cusparseHandle_t       handle,
                             int                    m,
                             int                    n,
                             const cuDoubleComplex* dl,
                             const cuDoubleComplex* d,
                             const cuDoubleComplex* du,
                             const cuDoubleComplex* B,
                             int                    ldb,
                             size_t*                bufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseSgtsv2(cusparseHandle_t handle,
               int              m,
               int              n,
               const float*     dl,
               const float*     d,
               const float*     du,
               float*           B,
               int              ldb,
               void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseDgtsv2(cusparseHandle_t handle,
               int              m,
               int              n,
               const double*    dl,
               const double*    d,
               const double*    du,
               double*          B,
               int              ldb,
               void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseCgtsv2(cusparseHandle_t handle,
               int              m,
               int              n,
               const cuComplex* dl,
               const cuComplex* d,
               const cuComplex* du,
               cuComplex*       B,
               int              ldb,
               void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseZgtsv2(cusparseHandle_t       handle,
               int                    m,
               int                    n,
               const cuDoubleComplex* dl,
               const cuDoubleComplex* d,
               const cuDoubleComplex* du,
               cuDoubleComplex*       B,
               int                    ldb,
               void*                  pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseSgtsv2_nopivot_bufferSizeExt(cusparseHandle_t handle,
                                     int              m,
                                     int              n,
                                     const float*     dl,
                                     const float*     d,
                                     const float*     du,
                                     const float*     B,
                                     int              ldb,
                                     size_t*          bufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseDgtsv2_nopivot_bufferSizeExt(cusparseHandle_t handle,
                                     int              m,
                                     int              n,
                                     const double*    dl,
                                     const double*    d,
                                     const double*    du,
                                     const double*    B,
                                     int              ldb,
                                     size_t*          bufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseCgtsv2_nopivot_bufferSizeExt(cusparseHandle_t handle,
                                     int              m,
                                     int              n,
                                     const cuComplex* dl,
                                     const cuComplex* d,
                                     const cuComplex* du,
                                     const cuComplex* B,
                                     int              ldb,
                                     size_t*          bufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseZgtsv2_nopivot_bufferSizeExt(cusparseHandle_t       handle,
                                     int                    m,
                                     int                    n,
                                     const cuDoubleComplex* dl,
                                     const cuDoubleComplex* d,
                                     const cuDoubleComplex* du,
                                     const cuDoubleComplex* B,
                                     int                    ldb,
                                     size_t*                bufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseSgtsv2_nopivot(cusparseHandle_t handle,
                       int              m,
                       int              n,
                       const float*     dl,
                       const float*     d,
                       const float*     du,
                       float*           B,
                       int              ldb,
                       void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseDgtsv2_nopivot(cusparseHandle_t handle,
                       int              m,
                       int              n,
                       const double*    dl,
                       const double*    d,
                       const double*    du,
                       double*          B,
                       int              ldb,
                       void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseCgtsv2_nopivot(cusparseHandle_t handle,
                       int              m,
                       int              n,
                       const cuComplex* dl,
                       const cuComplex* d,
                       const cuComplex* du,
                       cuComplex*       B,
                       int              ldb,
                       void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseZgtsv2_nopivot(cusparseHandle_t       handle,
                       int                    m,
                       int                    n,
                       const cuDoubleComplex* dl,
                       const cuDoubleComplex* d,
                       const cuDoubleComplex* du,
                       cuDoubleComplex*       B,
                       int                    ldb,
                       void*                  pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseSgtsv2StridedBatch_bufferSizeExt(cusparseHandle_t handle,
                                         int              m,
                                         const float*     dl,
                                         const float*     d,
                                         const float*     du,
                                         const float*     x,
                                         int              batchCount,
                                         int              batchStride,
                                         size_t*          bufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseDgtsv2StridedBatch_bufferSizeExt(cusparseHandle_t handle,
                                         int              m,
                                         const double*    dl,
                                         const double*    d,
                                         const double*    du,
                                         const double*    x,
                                         int              batchCount,
                                         int              batchStride,
                                         size_t*          bufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseCgtsv2StridedBatch_bufferSizeExt(cusparseHandle_t handle,
                                         int              m,
                                         const cuComplex* dl,
                                         const cuComplex* d,
                                         const cuComplex* du,
                                         const cuComplex* x,
                                         int              batchCount,
                                         int              batchStride,
                                         size_t*          bufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseZgtsv2StridedBatch_bufferSizeExt(cusparseHandle_t       handle,
                                         int                    m,
                                         const cuDoubleComplex* dl,
                                         const cuDoubleComplex* d,
                                         const cuDoubleComplex* du,
                                         const cuDoubleComplex* x,
                                         int                    batchCount,
                                         int                    batchStride,
                                         size_t* bufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseSgtsv2StridedBatch(cusparseHandle_t handle,
                           int              m,
                           const float*     dl,
                           const float*     d,
                           const float*     du,
                           float*           x,
                           int              batchCount,
                           int              batchStride,
                           void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseDgtsv2StridedBatch(cusparseHandle_t handle,
                           int              m,
                           const double*    dl,
                           const double*    d,
                           const double*    du,
                           double*          x,
                           int              batchCount,
                           int              batchStride,
                           void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseCgtsv2StridedBatch(cusparseHandle_t handle,
                           int              m,
                           const cuComplex* dl,
                           const cuComplex* d,
                           const cuComplex* du,
                           cuComplex*       x,
                           int              batchCount,
                           int              batchStride,
                           void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseZgtsv2StridedBatch(cusparseHandle_t       handle,
                           int                    m,
                           const cuDoubleComplex* dl,
                           const cuDoubleComplex* d,
                           const cuDoubleComplex* du,
                           cuDoubleComplex*       x,
                           int                    batchCount,
                           int                    batchStride,
                           void*                  pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseSgtsvInterleavedBatch_bufferSizeExt(cusparseHandle_t handle,
                                            int              algo,
                                            int              m,
                                            const float*     dl,
                                            const float*     d,
                                            const float*     du,
                                            const float*     x,
                                            int              batchCount,
                                            size_t*         pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseDgtsvInterleavedBatch_bufferSizeExt(cusparseHandle_t handle,
                                         int              algo,
                                         int              m,
                                         const double*    dl,
                                         const double*    d,
                                         const double*    du,
                                         const double*    x,
                                         int              batchCount,
                                         size_t*          pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseCgtsvInterleavedBatch_bufferSizeExt(cusparseHandle_t handle,
                                            int              algo,
                                            int              m,
                                            const cuComplex* dl,
                                            const cuComplex* d,
                                            const cuComplex* du,
                                            const cuComplex* x,
                                            int              batchCount,
                                            size_t*         pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseZgtsvInterleavedBatch_bufferSizeExt(cusparseHandle_t       handle,
                                            int                    algo,
                                            int                    m,
                                            const cuDoubleComplex* dl,
                                            const cuDoubleComplex* d,
                                            const cuDoubleComplex* du,
                                            const cuDoubleComplex* x,
                                            int                    batchCount,
                                            size_t*        pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseSgtsvInterleavedBatch(cusparseHandle_t handle,
                              int              algo,
                              int              m,
                              float*           dl,
                              float*           d,
                              float*           du,
                              float*           x,
                              int              batchCount,
                              void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseDgtsvInterleavedBatch(cusparseHandle_t handle,
                              int              algo,
                              int              m,
                              double*          dl,
                              double*          d,
                              double*          du,
                              double*          x,
                              int              batchCount,
                              void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseCgtsvInterleavedBatch(cusparseHandle_t handle,
                              int              algo,
                              int              m,
                              cuComplex*       dl,
                              cuComplex*       d,
                              cuComplex*       du,
                              cuComplex*       x,
                              int              batchCount,
                              void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseZgtsvInterleavedBatch(cusparseHandle_t handle,
                              int              algo,
                              int              m,
                              cuDoubleComplex* dl,
                              cuDoubleComplex* d,
                              cuDoubleComplex* du,
                              cuDoubleComplex* x,
                              int              batchCount,
                              void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseSgpsvInterleavedBatch_bufferSizeExt(cusparseHandle_t handle,
                                            int              algo,
                                            int              m,
                                            const float*     ds,
                                            const float*     dl,
                                            const float*     d,
                                            const float*     du,
                                            const float*     dw,
                                            const float*     x,
                                            int              batchCount,
                                            size_t*         pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseDgpsvInterleavedBatch_bufferSizeExt(cusparseHandle_t handle,
                                            int              algo,
                                            int              m,
                                            const double*    ds,
                                            const double*    dl,
                                            const double*    d,
                                            const double*    du,
                                            const double*    dw,
                                            const double*    x,
                                            int              batchCount,
                                            size_t*         pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseCgpsvInterleavedBatch_bufferSizeExt(cusparseHandle_t handle,
                                            int              algo,
                                            int              m,
                                            const cuComplex* ds,
                                            const cuComplex* dl,
                                            const cuComplex* d,
                                            const cuComplex* du,
                                            const cuComplex* dw,
                                            const cuComplex* x,
                                            int              batchCount,
                                            size_t*         pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseZgpsvInterleavedBatch_bufferSizeExt(cusparseHandle_t       handle,
                                            int                    algo,
                                            int                    m,
                                            const cuDoubleComplex* ds,
                                            const cuDoubleComplex* dl,
                                            const cuDoubleComplex* d,
                                            const cuDoubleComplex* du,
                                            const cuDoubleComplex* dw,
                                            const cuDoubleComplex* x,
                                            int                    batchCount,
                                            size_t*         pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseSgpsvInterleavedBatch(cusparseHandle_t handle,
                              int              algo,
                              int              m,
                              float*           ds,
                              float*           dl,
                              float*           d,
                              float*           du,
                              float*           dw,
                              float*           x,
                              int              batchCount,
                              void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseDgpsvInterleavedBatch(cusparseHandle_t handle,
                              int              algo,
                              int              m,
                              double*          ds,
                              double*          dl,
                              double*          d,
                              double*          du,
                              double*          dw,
                              double*          x,
                              int              batchCount,
                              void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseCgpsvInterleavedBatch(cusparseHandle_t handle,
                              int              algo,
                              int              m,
                              cuComplex*       ds,
                              cuComplex*       dl,
                              cuComplex*       d,
                              cuComplex*       du,
                              cuComplex*       dw,
                              cuComplex*       x,
                              int              batchCount,
                              void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseZgpsvInterleavedBatch(cusparseHandle_t handle,
                              int              algo,
                              int              m,
                              cuDoubleComplex* ds,
                              cuDoubleComplex* dl,
                              cuDoubleComplex* d,
                              cuDoubleComplex* du,
                              cuDoubleComplex* dw,
                              cuDoubleComplex* x,
                              int              batchCount,
                              void*            pBuffer);

//##############################################################################
//# EXTRA ROUTINES
//##############################################################################

cusparseStatus_t CUSPARSEAPI
cusparseScsrgeam2_bufferSizeExt(cusparseHandle_t         handle,
                                int                      m,
                                int                      n,
                                const float*             alpha,
                                const cusparseMatDescr_t descrA,
                                int                      nnzA,
                                const float*             csrSortedValA,
                                const int*               csrSortedRowPtrA,
                                const int*               csrSortedColIndA,
                                const float*             beta,
                                const cusparseMatDescr_t descrB,
                                int                      nnzB,
                                const float*             csrSortedValB,
                                const int*               csrSortedRowPtrB,
                                const int*               csrSortedColIndB,
                                const cusparseMatDescr_t descrC,
                                const float*             csrSortedValC,
                                const int*               csrSortedRowPtrC,
                                const int*               csrSortedColIndC,
                                size_t*                  pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseDcsrgeam2_bufferSizeExt(cusparseHandle_t         handle,
                                int                      m,
                                int                      n,
                                const double*            alpha,
                                const cusparseMatDescr_t descrA,
                                int                      nnzA,
                                const double*            csrSortedValA,
                                const int*               csrSortedRowPtrA,
                                const int*               csrSortedColIndA,
                                const double*            beta,
                                const cusparseMatDescr_t descrB,
                                int                      nnzB,
                                const double*            csrSortedValB,
                                const int*               csrSortedRowPtrB,
                                const int*               csrSortedColIndB,
                                const cusparseMatDescr_t descrC,
                                const double*            csrSortedValC,
                                const int*               csrSortedRowPtrC,
                                const int*               csrSortedColIndC,
                                size_t*                  pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseCcsrgeam2_bufferSizeExt(cusparseHandle_t         handle,
                                int                      m,
                                int                      n,
                                const cuComplex*         alpha,
                                const cusparseMatDescr_t descrA,
                                int                      nnzA,
                                const cuComplex*         csrSortedValA,
                                const int*               csrSortedRowPtrA,
                                const int*               csrSortedColIndA,
                                const cuComplex*         beta,
                                const cusparseMatDescr_t descrB,
                                int                      nnzB,
                                const cuComplex*         csrSortedValB,
                                const int*               csrSortedRowPtrB,
                                const int*               csrSortedColIndB,
                                const cusparseMatDescr_t descrC,
                                const cuComplex*         csrSortedValC,
                                const int*               csrSortedRowPtrC,
                                const int*               csrSortedColIndC,
                                size_t*                  pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseZcsrgeam2_bufferSizeExt(cusparseHandle_t         handle,
                                int                      m,
                                int                      n,
                                const cuDoubleComplex*   alpha,
                                const cusparseMatDescr_t descrA,
                                int                      nnzA,
                                const cuDoubleComplex*   csrSortedValA,
                                const int*               csrSortedRowPtrA,
                                const int*               csrSortedColIndA,
                                const cuDoubleComplex*   beta,
                                const cusparseMatDescr_t descrB,
                                int                      nnzB,
                                const cuDoubleComplex*   csrSortedValB,
                                const int*               csrSortedRowPtrB,
                                const int*               csrSortedColIndB,
                                const cusparseMatDescr_t descrC,
                                const cuDoubleComplex*   csrSortedValC,
                                const int*               csrSortedRowPtrC,
                                const int*               csrSortedColIndC,
                                size_t*                  pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseXcsrgeam2Nnz(cusparseHandle_t         handle,
                     int                      m,
                     int                      n,
                     const cusparseMatDescr_t descrA,
                     int                      nnzA,
                     const int*               csrSortedRowPtrA,
                     const int*               csrSortedColIndA,
                     const cusparseMatDescr_t descrB,
                     int                      nnzB,
                     const int*               csrSortedRowPtrB,
                     const int*               csrSortedColIndB,
                     const cusparseMatDescr_t descrC,
                     int*                     csrSortedRowPtrC,
                     int*                     nnzTotalDevHostPtr,
                     void*                    workspace);

cusparseStatus_t CUSPARSEAPI
cusparseScsrgeam2(cusparseHandle_t         handle,
                  int                      m,
                  int                      n,
                  const float*             alpha,
                  const cusparseMatDescr_t descrA,
                  int                      nnzA,
                  const float*             csrSortedValA,
                  const int*               csrSortedRowPtrA,
                  const int*               csrSortedColIndA,
                  const float*             beta,
                  const cusparseMatDescr_t descrB,
                  int                      nnzB,
                  const float*             csrSortedValB,
                  const int*               csrSortedRowPtrB,
                  const int*               csrSortedColIndB,
                  const cusparseMatDescr_t descrC,
                  float*                   csrSortedValC,
                  int*                     csrSortedRowPtrC,
                  int*                     csrSortedColIndC,
                  void*                    pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseDcsrgeam2(cusparseHandle_t         handle,
                  int                      m,
                  int                      n,
                  const double*            alpha,
                  const cusparseMatDescr_t descrA,
                  int                      nnzA,
                  const double*            csrSortedValA,
                  const int*               csrSortedRowPtrA,
                  const int*               csrSortedColIndA,
                  const double*            beta,
                  const cusparseMatDescr_t descrB,
                  int                      nnzB,
                  const double*            csrSortedValB,
                  const int*               csrSortedRowPtrB,
                  const int*               csrSortedColIndB,
                  const cusparseMatDescr_t descrC,
                  double*                  csrSortedValC,
                  int*                     csrSortedRowPtrC,
                  int*                     csrSortedColIndC,
                  void*                    pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseCcsrgeam2(cusparseHandle_t         handle,
                  int                      m,
                  int                      n,
                  const cuComplex*         alpha,
                  const cusparseMatDescr_t descrA,
                  int                      nnzA,
                  const cuComplex*         csrSortedValA,
                  const int*               csrSortedRowPtrA,
                  const int*               csrSortedColIndA,
                  const cuComplex*         beta,
                  const cusparseMatDescr_t descrB,
                  int                      nnzB,
                  const cuComplex*         csrSortedValB,
                  const int*               csrSortedRowPtrB,
                  const int*               csrSortedColIndB,
                  const cusparseMatDescr_t descrC,
                  cuComplex*               csrSortedValC,
                  int*                     csrSortedRowPtrC,
                  int*                     csrSortedColIndC,
                  void*                    pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseZcsrgeam2(cusparseHandle_t         handle,
                  int                      m,
                  int                      n,
                  const cuDoubleComplex*   alpha,
                  const cusparseMatDescr_t descrA,
                  int                      nnzA,
                  const cuDoubleComplex*   csrSortedValA,
                  const int*               csrSortedRowPtrA,
                  const int*               csrSortedColIndA,
                  const cuDoubleComplex*   beta,
                  const cusparseMatDescr_t descrB,
                  int                      nnzB,
                  const cuDoubleComplex*   csrSortedValB,
                  const int*               csrSortedRowPtrB,
                  const int*               csrSortedColIndB,
                  const cusparseMatDescr_t descrC,
                  cuDoubleComplex*         csrSortedValC,
                  int*                     csrSortedRowPtrC,
                  int*                     csrSortedColIndC,
                  void*                    pBuffer);

//##############################################################################
//# SPARSE MATRIX REORDERING
//##############################################################################

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseScsrcolor(cusparseHandle_t         handle,
                  int                      m,
                  int                      nnz,
                  const cusparseMatDescr_t descrA,
                  const float*              csrSortedValA,
                  const int*                csrSortedRowPtrA,
                  const int*                csrSortedColIndA,
                  const float*              fractionToColor,
                  int*                      ncolors,
                  int*                      coloring,
                  int*                      reordering,
                  const cusparseColorInfo_t info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDcsrcolor(cusparseHandle_t         handle,
                  int                      m,
                  int                      nnz,
                  const cusparseMatDescr_t descrA,
                  const double*            csrSortedValA,
                  const int*               csrSortedRowPtrA,
                  const int*               csrSortedColIndA,
                  const double*            fractionToColor,
                  int*                     ncolors,
                  int*                     coloring,
                  int*                     reordering,
                  const cusparseColorInfo_t info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCcsrcolor(cusparseHandle_t         handle,
                  int                      m,
                  int                      nnz,
                  const cusparseMatDescr_t descrA,
                  const cuComplex*          csrSortedValA,
                  const int*                csrSortedRowPtrA,
                  const int*                csrSortedColIndA,
                  const float*              fractionToColor,
                  int*                      ncolors,
                  int*                      coloring,
                  int*                      reordering,
                  const cusparseColorInfo_t info);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZcsrcolor(cusparseHandle_t          handle,
                  int                       m,
                  int                       nnz,
                  const cusparseMatDescr_t  descrA,
                  const cuDoubleComplex*    csrSortedValA,
                  const int*                csrSortedRowPtrA,
                  const int*                csrSortedColIndA,
                  const double*             fractionToColor,
                  int*                      ncolors,
                  int*                      coloring,
                  int*                      reordering,
                  const cusparseColorInfo_t info);

//##############################################################################
//# SPARSE FORMAT CONVERSION
//##############################################################################

cusparseStatus_t CUSPARSEAPI
cusparseSnnz(cusparseHandle_t         handle,
             cusparseDirection_t      dirA,
             int                      m,
             int                      n,
             const cusparseMatDescr_t descrA,
             const float*             A,
             int                      lda,
             int*                     nnzPerRowCol,
             int*                     nnzTotalDevHostPtr);

cusparseStatus_t CUSPARSEAPI
cusparseDnnz(cusparseHandle_t         handle,
             cusparseDirection_t      dirA,
             int                      m,
             int                      n,
             const cusparseMatDescr_t descrA,
             const double*            A,
             int                      lda,
             int*                     nnzPerRowCol,
             int*                     nnzTotalDevHostPtr);

cusparseStatus_t CUSPARSEAPI
cusparseCnnz(cusparseHandle_t         handle,
             cusparseDirection_t      dirA,
             int                      m,
             int                      n,
             const cusparseMatDescr_t descrA,
             const cuComplex*         A,
             int                      lda,
             int*                     nnzPerRowCol,
             int*                     nnzTotalDevHostPtr);

cusparseStatus_t CUSPARSEAPI
cusparseZnnz(cusparseHandle_t         handle,
             cusparseDirection_t      dirA,
             int                      m,
             int                      n,
             const cusparseMatDescr_t descrA,
             const cuDoubleComplex*   A,
             int                      lda,
             int*                     nnzPerRowCol,
             int*                     nnzTotalDevHostPtr);

//##############################################################################
//# SPARSE FORMAT CONVERSION
//##############################################################################

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSnnz_compress(cusparseHandle_t         handle,
                      int                      m,
                      const cusparseMatDescr_t descr,
                      const float*             csrSortedValA,
                      const int*               csrSortedRowPtrA,
                      int*                     nnzPerRow,
                      int*                     nnzC,
                      float                    tol);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDnnz_compress(cusparseHandle_t         handle,
                      int                      m,
                      const cusparseMatDescr_t descr,
                      const double*            csrSortedValA,
                      const int*               csrSortedRowPtrA,
                      int*                     nnzPerRow,
                      int*                     nnzC,
                      double                   tol);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCnnz_compress(cusparseHandle_t         handle,
                      int                      m,
                      const cusparseMatDescr_t descr,
                      const cuComplex*         csrSortedValA,
                      const int*               csrSortedRowPtrA,
                      int*                     nnzPerRow,
                      int*                     nnzC,
                      cuComplex                tol);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZnnz_compress(cusparseHandle_t         handle,
                      int                      m,
                      const cusparseMatDescr_t descr,
                      const cuDoubleComplex*   csrSortedValA,
                      const int*               csrSortedRowPtrA,
                      int*                     nnzPerRow,
                      int*                     nnzC,
                      cuDoubleComplex          tol);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseScsr2csr_compress(cusparseHandle_t         handle,
                          int                      m,
                          int                      n,
                          const cusparseMatDescr_t descrA,
                          const float*             csrSortedValA,
                          const int*               csrSortedColIndA,
                          const int*               csrSortedRowPtrA,
                          int                      nnzA,
                          const int*               nnzPerRow,
                          float*                   csrSortedValC,
                          int*                     csrSortedColIndC,
                          int*                     csrSortedRowPtrC,
                          float                    tol);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDcsr2csr_compress(cusparseHandle_t         handle,
                          int                      m,
                          int                      n,
                          const cusparseMatDescr_t descrA,
                          const double*            csrSortedValA,
                          const int*               csrSortedColIndA,
                          const int*               csrSortedRowPtrA,
                          int                      nnzA,
                          const int*               nnzPerRow,
                          double*                  csrSortedValC,
                          int*                     csrSortedColIndC,
                          int*                     csrSortedRowPtrC,
                          double                   tol);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCcsr2csr_compress(cusparseHandle_t         handle,
                          int                      m,
                          int                      n,
                          const cusparseMatDescr_t descrA,
                          const cuComplex*         csrSortedValA,
                          const int*               csrSortedColIndA,
                          const int*               csrSortedRowPtrA,
                          int                      nnzA,
                          const int*               nnzPerRow,
                          cuComplex*               csrSortedValC,
                          int*                     csrSortedColIndC,
                          int*                     csrSortedRowPtrC,
                          cuComplex                tol);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZcsr2csr_compress(cusparseHandle_t         handle,
                          int                      m,
                          int                      n,
                          const cusparseMatDescr_t descrA,
                          const cuDoubleComplex*   csrSortedValA,
                          const int*               csrSortedColIndA,
                          const int*               csrSortedRowPtrA,
                          int                      nnzA,
                          const int*               nnzPerRow,
                          cuDoubleComplex*         csrSortedValC,
                          int*                     csrSortedColIndC,
                          int*                     csrSortedRowPtrC,
                          cuDoubleComplex          tol);

cusparseStatus_t CUSPARSEAPI
cusparseXcoo2csr(cusparseHandle_t    handle,
                 const int*          cooRowInd,
                 int                 nnz,
                 int                 m,
                 int*                csrSortedRowPtr,
                 cusparseIndexBase_t idxBase);

cusparseStatus_t CUSPARSEAPI
cusparseXcsr2coo(cusparseHandle_t    handle,
                 const int*          csrSortedRowPtr,
                 int                 nnz,
                 int                 m,
                 int*                cooRowInd,
                 cusparseIndexBase_t idxBase);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseXcsr2bsrNnz(cusparseHandle_t         handle,
                    cusparseDirection_t      dirA,
                    int                      m,
                    int                      n,
                    const cusparseMatDescr_t descrA,
                    const int*               csrSortedRowPtrA,
                    const int*               csrSortedColIndA,
                    int                      blockDim,
                    const cusparseMatDescr_t descrC,
                    int*                     bsrSortedRowPtrC,
                    int*                     nnzTotalDevHostPtr);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseScsr2bsr(cusparseHandle_t         handle,
                 cusparseDirection_t      dirA,
                 int                      m,
                 int                      n,
                 const cusparseMatDescr_t descrA,
                 const float*             csrSortedValA,
                 const int*               csrSortedRowPtrA,
                 const int*               csrSortedColIndA,
                 int                      blockDim,
                 const cusparseMatDescr_t descrC,
                 float*                   bsrSortedValC,
                 int*                     bsrSortedRowPtrC,
                 int*                     bsrSortedColIndC);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDcsr2bsr(cusparseHandle_t         handle,
                 cusparseDirection_t      dirA,
                 int                      m,
                 int                      n,
                 const cusparseMatDescr_t descrA,
                 const double*            csrSortedValA,
                 const int*               csrSortedRowPtrA,
                 const int*               csrSortedColIndA,
                 int                      blockDim,
                 const cusparseMatDescr_t descrC,
                 double*                  bsrSortedValC,
                 int*                     bsrSortedRowPtrC,
                 int*                     bsrSortedColIndC);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCcsr2bsr(cusparseHandle_t         handle,
                 cusparseDirection_t      dirA,
                 int                      m,
                 int                      n,
                 const cusparseMatDescr_t descrA,
                 const cuComplex*         csrSortedValA,
                 const int*               csrSortedRowPtrA,
                 const int*               csrSortedColIndA,
                 int                      blockDim,
                 const cusparseMatDescr_t descrC,
                 cuComplex*               bsrSortedValC,
                 int*                     bsrSortedRowPtrC,
                 int*                     bsrSortedColIndC);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZcsr2bsr(cusparseHandle_t         handle,
                 cusparseDirection_t      dirA,
                 int                      m,
                 int                      n,
                 const cusparseMatDescr_t descrA,
                 const cuDoubleComplex*   csrSortedValA,
                 const int*               csrSortedRowPtrA,
                 const int*               csrSortedColIndA,
                 int                      blockDim,
                 const cusparseMatDescr_t descrC,
                 cuDoubleComplex*         bsrSortedValC,
                 int*                     bsrSortedRowPtrC,
                 int*                     bsrSortedColIndC);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseSbsr2csr(cusparseHandle_t         handle,
                 cusparseDirection_t      dirA,
                 int                      mb,
                 int                      nb,
                 const cusparseMatDescr_t descrA,
                 const float*             bsrSortedValA,
                 const int*               bsrSortedRowPtrA,
                 const int*               bsrSortedColIndA,
                 int                      blockDim,
                 const cusparseMatDescr_t descrC,
                 float*                   csrSortedValC,
                 int*                     csrSortedRowPtrC,
                 int*                     csrSortedColIndC);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseDbsr2csr(cusparseHandle_t         handle,
                 cusparseDirection_t      dirA,
                 int                      mb,
                 int                      nb,
                 const cusparseMatDescr_t descrA,
                 const double*            bsrSortedValA,
                 const int*               bsrSortedRowPtrA,
                 const int*               bsrSortedColIndA,
                 int                      blockDim,
                 const cusparseMatDescr_t descrC,
                 double*                  csrSortedValC,
                 int*                     csrSortedRowPtrC,
                 int*                     csrSortedColIndC);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseCbsr2csr(cusparseHandle_t         handle,
                 cusparseDirection_t      dirA,
                 int                      mb,
                 int                      nb,
                 const cusparseMatDescr_t descrA,
                 const cuComplex*         bsrSortedValA,
                 const int*               bsrSortedRowPtrA,
                 const int*               bsrSortedColIndA,
                 int                      blockDim,
                 const cusparseMatDescr_t descrC,
                 cuComplex*               csrSortedValC,
                 int*                     csrSortedRowPtrC,
                 int*                     csrSortedColIndC);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseZbsr2csr(cusparseHandle_t         handle,
                 cusparseDirection_t      dirA,
                 int                      mb,
                 int                      nb,
                 const cusparseMatDescr_t descrA,
                 const cuDoubleComplex*   bsrSortedValA,
                 const int*               bsrSortedRowPtrA,
                 const int*               bsrSortedColIndA,
                 int                      blockDim,
                 const cusparseMatDescr_t descrC,
                 cuDoubleComplex*         csrSortedValC,
                 int*                     csrSortedRowPtrC,
                 int*                     csrSortedColIndC);

cusparseStatus_t CUSPARSEAPI
cusparseSgebsr2gebsc_bufferSize(cusparseHandle_t handle,
                                int              mb,
                                int              nb,
                                int              nnzb,
                                const float*     bsrSortedVal,
                                const int*       bsrSortedRowPtr,
                                const int*       bsrSortedColInd,
                                int              rowBlockDim,
                                int              colBlockDim,
                                int*             pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseDgebsr2gebsc_bufferSize(cusparseHandle_t handle,
                                int              mb,
                                int              nb,
                                int              nnzb,
                                const double*    bsrSortedVal,
                                const int*       bsrSortedRowPtr,
                                const int*       bsrSortedColInd,
                                int              rowBlockDim,
                                int              colBlockDim,
                                int*             pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseCgebsr2gebsc_bufferSize(cusparseHandle_t handle,
                                int              mb,
                                int              nb,
                                int              nnzb,
                                const cuComplex* bsrSortedVal,
                                const int*       bsrSortedRowPtr,
                                const int*       bsrSortedColInd,
                                int              rowBlockDim,
                                int              colBlockDim,
                                int*             pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseZgebsr2gebsc_bufferSize(cusparseHandle_t       handle,
                                int                    mb,
                                int                    nb,
                                int                    nnzb,
                                const cuDoubleComplex* bsrSortedVal,
                                const int*             bsrSortedRowPtr,
                                const int*             bsrSortedColInd,
                                int                    rowBlockDim,
                                int                    colBlockDim,
                                int*                   pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseSgebsr2gebsc_bufferSizeExt(cusparseHandle_t handle,
                                   int              mb,
                                   int              nb,
                                   int              nnzb,
                                   const float*     bsrSortedVal,
                                   const int*       bsrSortedRowPtr,
                                   const int*       bsrSortedColInd,
                                   int              rowBlockDim,
                                   int              colBlockDim,
                                   size_t*          pBufferSize);

cusparseStatus_t CUSPARSEAPI
cusparseDgebsr2gebsc_bufferSizeExt(cusparseHandle_t handle,
                                   int              mb,
                                   int              nb,
                                   int              nnzb,
                                   const double*    bsrSortedVal,
                                   const int*       bsrSortedRowPtr,
                                   const int*       bsrSortedColInd,
                                   int              rowBlockDim,
                                   int              colBlockDim,
                                   size_t*          pBufferSize);

cusparseStatus_t CUSPARSEAPI
cusparseCgebsr2gebsc_bufferSizeExt(cusparseHandle_t handle,
                                   int              mb,
                                   int              nb,
                                   int              nnzb,
                                   const cuComplex* bsrSortedVal,
                                   const int*       bsrSortedRowPtr,
                                   const int*       bsrSortedColInd,
                                   int              rowBlockDim,
                                   int              colBlockDim,
                                   size_t*          pBufferSize);

cusparseStatus_t CUSPARSEAPI
cusparseZgebsr2gebsc_bufferSizeExt(cusparseHandle_t       handle,
                                   int                    mb,
                                   int                    nb,
                                   int                    nnzb,
                                   const cuDoubleComplex* bsrSortedVal,
                                   const int*             bsrSortedRowPtr,
                                   const int*             bsrSortedColInd,
                                   int                    rowBlockDim,
                                   int                    colBlockDim,
                                   size_t*                pBufferSize);

cusparseStatus_t CUSPARSEAPI
cusparseSgebsr2gebsc(cusparseHandle_t handle,
                     int              mb,
                     int              nb,
                     int              nnzb,
                     const float*     bsrSortedVal,
                     const int* bsrSortedRowPtr,
                     const int* bsrSortedColInd,
                     int        rowBlockDim,
                     int        colBlockDim,
                     float*     bscVal,
                     int*       bscRowInd,
                     int*       bscColPtr,
                     cusparseAction_t copyValues,
                     cusparseIndexBase_t idxBase,
                     void*               pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseDgebsr2gebsc(cusparseHandle_t    handle,
                     int                 mb,
                     int                 nb,
                     int                 nnzb,
                     const double*       bsrSortedVal,
                     const int*          bsrSortedRowPtr,
                     const int*          bsrSortedColInd,
                     int                 rowBlockDim,
                     int                 colBlockDim,
                     double*             bscVal,
                     int*                bscRowInd,
                     int*                bscColPtr,
                     cusparseAction_t    copyValues,
                     cusparseIndexBase_t idxBase,
                     void*               pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseCgebsr2gebsc(cusparseHandle_t    handle,
                     int                 mb,
                     int                 nb,
                     int                 nnzb,
                     const cuComplex*    bsrSortedVal,
                     const int*          bsrSortedRowPtr,
                     const int*          bsrSortedColInd,
                     int                 rowBlockDim,
                     int                 colBlockDim,
                     cuComplex*          bscVal,
                     int*                bscRowInd,
                     int*                bscColPtr,
                     cusparseAction_t    copyValues,
                     cusparseIndexBase_t idxBase,
                     void*               pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseZgebsr2gebsc(cusparseHandle_t       handle,
                     int                    mb,
                     int                    nb,
                     int                    nnzb,
                     const cuDoubleComplex* bsrSortedVal,
                     const int*             bsrSortedRowPtr,
                     const int*             bsrSortedColInd,
                     int                    rowBlockDim,
                     int                    colBlockDim,
                     cuDoubleComplex*       bscVal,
                     int*                   bscRowInd,
                     int*                   bscColPtr,
                     cusparseAction_t       copyValues,
                     cusparseIndexBase_t    idxBase,
                     void*                  pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseXgebsr2csr(cusparseHandle_t         handle,
                   cusparseDirection_t      dirA,
                   int                      mb,
                   int                      nb,
                   const cusparseMatDescr_t descrA,
                   const int*               bsrSortedRowPtrA,
                   const int*               bsrSortedColIndA,
                   int                      rowBlockDim,
                   int                      colBlockDim,
                   const cusparseMatDescr_t descrC,
                   int*                     csrSortedRowPtrC,
                   int*                     csrSortedColIndC);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSgebsr2csr(cusparseHandle_t         handle,
                   cusparseDirection_t      dirA,
                   int                      mb,
                   int                      nb,
                   const cusparseMatDescr_t descrA,
                   const float*             bsrSortedValA,
                   const int*               bsrSortedRowPtrA,
                   const int*               bsrSortedColIndA,
                   int                      rowBlockDim,
                   int                      colBlockDim,
                   const cusparseMatDescr_t descrC,
                   float*                   csrSortedValC,
                   int*                     csrSortedRowPtrC,
                   int*                     csrSortedColIndC);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDgebsr2csr(cusparseHandle_t         handle,
                   cusparseDirection_t      dirA,
                   int                      mb,
                   int                      nb,
                   const cusparseMatDescr_t descrA,
                   const double*            bsrSortedValA,
                   const int*               bsrSortedRowPtrA,
                   const int*               bsrSortedColIndA,
                   int                      rowBlockDim,
                   int                      colBlockDim,
                   const cusparseMatDescr_t descrC,
                   double*                  csrSortedValC,
                   int*                     csrSortedRowPtrC,
                   int*                     csrSortedColIndC);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCgebsr2csr(cusparseHandle_t         handle,
                   cusparseDirection_t      dirA,
                   int                      mb,
                   int                      nb,
                   const cusparseMatDescr_t descrA,
                   const cuComplex*         bsrSortedValA,
                   const int*               bsrSortedRowPtrA,
                   const int*               bsrSortedColIndA,
                   int                      rowBlockDim,
                   int                      colBlockDim,
                   const cusparseMatDescr_t descrC,
                   cuComplex*               csrSortedValC,
                   int*                     csrSortedRowPtrC,
                   int*                     csrSortedColIndC);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZgebsr2csr(cusparseHandle_t         handle,
                   cusparseDirection_t      dirA,
                   int                      mb,
                   int                      nb,
                   const cusparseMatDescr_t descrA,
                   const cuDoubleComplex*   bsrSortedValA,
                   const int*               bsrSortedRowPtrA,
                   const int*               bsrSortedColIndA,
                   int                      rowBlockDim,
                   int                      colBlockDim,
                   const cusparseMatDescr_t descrC,
                   cuDoubleComplex*         csrSortedValC,
                   int*                     csrSortedRowPtrC,
                   int*                     csrSortedColIndC);

cusparseStatus_t CUSPARSEAPI
cusparseScsr2gebsr_bufferSize(cusparseHandle_t         handle,
                              cusparseDirection_t      dirA,
                              int                      m,
                              int                      n,
                              const cusparseMatDescr_t descrA,
                              const float*             csrSortedValA,
                              const int*               csrSortedRowPtrA,
                              const int*               csrSortedColIndA,
                              int                      rowBlockDim,
                              int                      colBlockDim,
                              int*                     pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseDcsr2gebsr_bufferSize(cusparseHandle_t         handle,
                              cusparseDirection_t      dirA,
                              int                      m,
                              int                      n,
                              const cusparseMatDescr_t descrA,
                              const double*            csrSortedValA,
                              const int*               csrSortedRowPtrA,
                              const int*               csrSortedColIndA,
                              int                      rowBlockDim,
                              int                      colBlockDim,
                              int*                     pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseCcsr2gebsr_bufferSize(cusparseHandle_t         handle,
                              cusparseDirection_t      dirA,
                              int                      m,
                              int                      n,
                              const cusparseMatDescr_t descrA,
                              const cuComplex*         csrSortedValA,
                              const int*               csrSortedRowPtrA,
                              const int*               csrSortedColIndA,
                              int                      rowBlockDim,
                              int                      colBlockDim,
                              int*                     pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseZcsr2gebsr_bufferSize(cusparseHandle_t         handle,
                              cusparseDirection_t      dirA,
                              int                      m,
                              int                      n,
                              const cusparseMatDescr_t descrA,
                              const cuDoubleComplex*   csrSortedValA,
                              const int*               csrSortedRowPtrA,
                              const int*               csrSortedColIndA,
                              int                      rowBlockDim,
                              int                      colBlockDim,
                              int*                     pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseScsr2gebsr_bufferSizeExt(cusparseHandle_t         handle,
                                 cusparseDirection_t      dirA,
                                 int                      m,
                                 int                      n,
                                 const cusparseMatDescr_t descrA,
                                 const float*             csrSortedValA,
                                 const int*               csrSortedRowPtrA,
                                 const int*               csrSortedColIndA,
                                 int                      rowBlockDim,
                                 int                      colBlockDim,
                                 size_t*                  pBufferSize);

cusparseStatus_t CUSPARSEAPI
cusparseDcsr2gebsr_bufferSizeExt(cusparseHandle_t         handle,
                                 cusparseDirection_t      dirA,
                                 int                      m,
                                 int                      n,
                                 const cusparseMatDescr_t descrA,
                                 const double*            csrSortedValA,
                                 const int*               csrSortedRowPtrA,
                                 const int*               csrSortedColIndA,
                                 int                      rowBlockDim,
                                 int                      colBlockDim,
                                 size_t*                  pBufferSize);

cusparseStatus_t CUSPARSEAPI
cusparseCcsr2gebsr_bufferSizeExt(cusparseHandle_t         handle,
                                 cusparseDirection_t      dirA,
                                 int                      m,
                                 int                      n,
                                 const cusparseMatDescr_t descrA,
                                 const cuComplex*         csrSortedValA,
                                 const int*               csrSortedRowPtrA,
                                 const int*               csrSortedColIndA,
                                 int                      rowBlockDim,
                                 int                      colBlockDim,
                                 size_t*                  pBufferSize);

cusparseStatus_t CUSPARSEAPI
cusparseZcsr2gebsr_bufferSizeExt(cusparseHandle_t         handle,
                                 cusparseDirection_t      dirA,
                                 int                      m,
                                 int                      n,
                                 const cusparseMatDescr_t descrA,
                                 const cuDoubleComplex*   csrSortedValA,
                                 const int*               csrSortedRowPtrA,
                                 const int*               csrSortedColIndA,
                                 int                      rowBlockDim,
                                 int                      colBlockDim,
                                 size_t*                  pBufferSize);

cusparseStatus_t CUSPARSEAPI
cusparseXcsr2gebsrNnz(cusparseHandle_t         handle,
                      cusparseDirection_t      dirA,
                      int                      m,
                      int                      n,
                      const cusparseMatDescr_t descrA,
                      const int*               csrSortedRowPtrA,
                      const int*               csrSortedColIndA,
                      const cusparseMatDescr_t descrC,
                      int*                     bsrSortedRowPtrC,
                      int                      rowBlockDim,
                      int                      colBlockDim,
                      int*                     nnzTotalDevHostPtr,
                      void*                    pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseScsr2gebsr(cusparseHandle_t         handle,
                   cusparseDirection_t      dirA,
                   int                      m,
                   int                      n,
                   const cusparseMatDescr_t descrA,
                   const float*             csrSortedValA,
                   const int*               csrSortedRowPtrA,
                   const int*               csrSortedColIndA,
                   const cusparseMatDescr_t descrC,
                   float*                   bsrSortedValC,
                   int*                     bsrSortedRowPtrC,
                   int*                     bsrSortedColIndC,
                   int                      rowBlockDim,
                   int                      colBlockDim,
                   void*                    pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseDcsr2gebsr(cusparseHandle_t         handle,
                   cusparseDirection_t      dirA,
                   int                      m,
                   int                      n,
                   const cusparseMatDescr_t descrA,
                   const double*            csrSortedValA,
                   const int*               csrSortedRowPtrA,
                   const int*               csrSortedColIndA,
                   const cusparseMatDescr_t descrC,
                   double*                  bsrSortedValC,
                   int*                     bsrSortedRowPtrC,
                   int*                     bsrSortedColIndC,
                   int                      rowBlockDim,
                   int                      colBlockDim,
                   void*                    pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseCcsr2gebsr(cusparseHandle_t         handle,
                   cusparseDirection_t      dirA,
                   int                      m,
                   int                      n,
                   const cusparseMatDescr_t descrA,
                   const cuComplex*         csrSortedValA,
                   const int*               csrSortedRowPtrA,
                   const int*               csrSortedColIndA,
                   const cusparseMatDescr_t descrC,
                   cuComplex*               bsrSortedValC,
                   int*                     bsrSortedRowPtrC,
                   int*                     bsrSortedColIndC,
                   int                      rowBlockDim,
                   int                      colBlockDim,
                   void*                    pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseZcsr2gebsr(cusparseHandle_t         handle,
                   cusparseDirection_t      dirA,
                   int                      m,
                   int                      n,
                   const cusparseMatDescr_t descrA,
                   const cuDoubleComplex*   csrSortedValA,
                   const int*               csrSortedRowPtrA,
                   const int*               csrSortedColIndA,
                   const cusparseMatDescr_t descrC,
                   cuDoubleComplex*         bsrSortedValC,
                   int*                     bsrSortedRowPtrC,
                   int*                     bsrSortedColIndC,
                   int                      rowBlockDim,
                   int                      colBlockDim,
                   void*                    pBuffer);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseSgebsr2gebsr_bufferSize(cusparseHandle_t         handle,
                                cusparseDirection_t      dirA,
                                int                      mb,
                                int                      nb,
                                int                      nnzb,
                                const cusparseMatDescr_t descrA,
                                const float*             bsrSortedValA,
                                const int*               bsrSortedRowPtrA,
                                const int*               bsrSortedColIndA,
                                int                      rowBlockDimA,
                                int                      colBlockDimA,
                                int                      rowBlockDimC,
                                int                      colBlockDimC,
                                int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseDgebsr2gebsr_bufferSize(cusparseHandle_t         handle,
                                cusparseDirection_t      dirA,
                                int                      mb,
                                int                      nb,
                                int                      nnzb,
                                const cusparseMatDescr_t descrA,
                                const double*            bsrSortedValA,
                                const int*               bsrSortedRowPtrA,
                                const int*               bsrSortedColIndA,
                                int                      rowBlockDimA,
                                int                      colBlockDimA,
                                int                      rowBlockDimC,
                                int                      colBlockDimC,
                                int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseCgebsr2gebsr_bufferSize(cusparseHandle_t         handle,
                                cusparseDirection_t      dirA,
                                int                      mb,
                                int                      nb,
                                int                      nnzb,
                                const cusparseMatDescr_t descrA,
                                const cuComplex*         bsrSortedValA,
                                const int*               bsrSortedRowPtrA,
                                const int*               bsrSortedColIndA,
                                int                      rowBlockDimA,
                                int                      colBlockDimA,
                                int                      rowBlockDimC,
                                int                      colBlockDimC,
                                int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseZgebsr2gebsr_bufferSize(cusparseHandle_t         handle,
                                cusparseDirection_t      dirA,
                                int                      mb,
                                int                      nb,
                                int                      nnzb,
                                const cusparseMatDescr_t descrA,
                                const cuDoubleComplex*   bsrSortedValA,
                                const int*               bsrSortedRowPtrA,
                                const int*               bsrSortedColIndA,
                                int                      rowBlockDimA,
                                int                      colBlockDimA,
                                int                      rowBlockDimC,
                                int                      colBlockDimC,
                                int*                     pBufferSizeInBytes);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseSgebsr2gebsr_bufferSizeExt(cusparseHandle_t         handle,
                                   cusparseDirection_t      dirA,
                                   int                      mb,
                                   int                      nb,
                                   int                      nnzb,
                                   const cusparseMatDescr_t descrA,
                                   const float*             bsrSortedValA,
                                   const int*               bsrSortedRowPtrA,
                                   const int*               bsrSortedColIndA,
                                   int                      rowBlockDimA,
                                   int                      colBlockDimA,
                                   int                      rowBlockDimC,
                                   int                      colBlockDimC,
                                   size_t*                  pBufferSize);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseDgebsr2gebsr_bufferSizeExt(cusparseHandle_t         handle,
                                   cusparseDirection_t      dirA,
                                   int                      mb,
                                   int                      nb,
                                   int                      nnzb,
                                   const cusparseMatDescr_t descrA,
                                   const double*            bsrSortedValA,
                                   const int*               bsrSortedRowPtrA,
                                   const int*               bsrSortedColIndA,
                                   int                      rowBlockDimA,
                                   int                      colBlockDimA,
                                   int                      rowBlockDimC,
                                   int                      colBlockDimC,
                                   size_t*                  pBufferSize);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseCgebsr2gebsr_bufferSizeExt(cusparseHandle_t         handle,
                                   cusparseDirection_t      dirA,
                                   int                      mb,
                                   int                      nb,
                                   int                      nnzb,
                                   const cusparseMatDescr_t descrA,
                                   const cuComplex*         bsrSortedValA,
                                   const int*               bsrSortedRowPtrA,
                                   const int*               bsrSortedColIndA,
                                   int                      rowBlockDimA,
                                   int                      colBlockDimA,
                                   int                      rowBlockDimC,
                                   int                      colBlockDimC,
                                   size_t*                  pBufferSize);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseZgebsr2gebsr_bufferSizeExt(cusparseHandle_t         handle,
                                   cusparseDirection_t      dirA,
                                   int                      mb,
                                   int                      nb,
                                   int                      nnzb,
                                   const cusparseMatDescr_t descrA,
                                   const cuDoubleComplex*   bsrSortedValA,
                                   const int*               bsrSortedRowPtrA,
                                   const int*               bsrSortedColIndA,
                                   int                      rowBlockDimA,
                                   int                      colBlockDimA,
                                   int                      rowBlockDimC,
                                   int                      colBlockDimC,
                                   size_t*                  pBufferSize);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseXgebsr2gebsrNnz(cusparseHandle_t         handle,
                        cusparseDirection_t      dirA,
                        int                      mb,
                        int                      nb,
                        int                      nnzb,
                        const cusparseMatDescr_t descrA,
                        const int*               bsrSortedRowPtrA,
                        const int*               bsrSortedColIndA,
                        int                      rowBlockDimA,
                        int                      colBlockDimA,
                        const cusparseMatDescr_t descrC,
                        int*                     bsrSortedRowPtrC,
                        int                      rowBlockDimC,
                        int                      colBlockDimC,
                        int*                     nnzTotalDevHostPtr,
                        void*                    pBuffer);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseSgebsr2gebsr(cusparseHandle_t         handle,
                     cusparseDirection_t      dirA,
                     int                      mb,
                     int                      nb,
                     int                      nnzb,
                     const cusparseMatDescr_t descrA,
                     const float*             bsrSortedValA,
                     const int*               bsrSortedRowPtrA,
                     const int*               bsrSortedColIndA,
                     int                      rowBlockDimA,
                     int                      colBlockDimA,
                     const cusparseMatDescr_t descrC,
                     float*                   bsrSortedValC,
                     int*                     bsrSortedRowPtrC,
                     int*                     bsrSortedColIndC,
                     int                      rowBlockDimC,
                     int                      colBlockDimC,
                     void*                    pBuffer);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseDgebsr2gebsr(cusparseHandle_t         handle,
                     cusparseDirection_t      dirA,
                     int                      mb,
                     int                      nb,
                     int                      nnzb,
                     const cusparseMatDescr_t descrA,
                     const double*            bsrSortedValA,
                     const int*               bsrSortedRowPtrA,
                     const int*               bsrSortedColIndA,
                     int                      rowBlockDimA,
                     int                      colBlockDimA,
                     const cusparseMatDescr_t descrC,
                     double*                  bsrSortedValC,
                     int*                     bsrSortedRowPtrC,
                     int*                     bsrSortedColIndC,
                     int                      rowBlockDimC,
                     int                      colBlockDimC,
                     void*                    pBuffer);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseCgebsr2gebsr(cusparseHandle_t         handle,
                     cusparseDirection_t      dirA,
                     int                      mb,
                     int                      nb,
                     int                      nnzb,
                     const cusparseMatDescr_t descrA,
                     const cuComplex*         bsrSortedValA,
                     const int*               bsrSortedRowPtrA,
                     const int*               bsrSortedColIndA,
                     int                      rowBlockDimA,
                     int                      colBlockDimA,
                     const cusparseMatDescr_t descrC,
                     cuComplex*               bsrSortedValC,
                     int*                     bsrSortedRowPtrC,
                     int*                     bsrSortedColIndC,
                     int                      rowBlockDimC,
                     int                      colBlockDimC,
                     void*                    pBuffer);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseZgebsr2gebsr(cusparseHandle_t         handle,
                     cusparseDirection_t      dirA,
                     int                      mb,
                     int                      nb,
                     int                      nnzb,
                     const cusparseMatDescr_t descrA,
                     const cuDoubleComplex*   bsrSortedValA,
                     const int*               bsrSortedRowPtrA,
                     const int*               bsrSortedColIndA,
                     int                      rowBlockDimA,
                     int                      colBlockDimA,
                     const cusparseMatDescr_t descrC,
                     cuDoubleComplex*         bsrSortedValC,
                     int*                     bsrSortedRowPtrC,
                     int*                     bsrSortedColIndC,
                     int                      rowBlockDimC,
                     int                      colBlockDimC,
                     void*                    pBuffer);

//##############################################################################
//# SPARSE MATRIX SORTING
//##############################################################################

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCreateIdentityPermutation(cusparseHandle_t handle,
                                  int              n,
                                  int*             p);

cusparseStatus_t CUSPARSEAPI
cusparseXcoosort_bufferSizeExt(cusparseHandle_t handle,
                               int              m,
                               int              n,
                               int              nnz,
                               const int*       cooRowsA,
                               const int*       cooColsA,
                               size_t*          pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseXcoosortByRow(cusparseHandle_t handle,
                      int              m,
                      int              n,
                      int              nnz,
                      int*             cooRowsA,
                      int*             cooColsA,
                      int*             P,
                      void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseXcoosortByColumn(cusparseHandle_t handle,
                         int              m,
                         int              n,
                         int              nnz,
                         int*             cooRowsA,
                         int*             cooColsA,
                         int*             P,
                         void*            pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseXcsrsort_bufferSizeExt(cusparseHandle_t handle,
                               int              m,
                               int              n,
                               int              nnz,
                               const int*       csrRowPtrA,
                               const int*       csrColIndA,
                               size_t*          pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseXcsrsort(cusparseHandle_t         handle,
                 int                      m,
                 int                      n,
                 int                      nnz,
                 const cusparseMatDescr_t descrA,
                 const int*               csrRowPtrA,
                 int*                     csrColIndA,
                 int*                     P,
                 void*                    pBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseXcscsort_bufferSizeExt(cusparseHandle_t handle,
                               int              m,
                               int              n,
                               int              nnz,
                               const int*       cscColPtrA,
                               const int*       cscRowIndA,
                               size_t*          pBufferSizeInBytes);

cusparseStatus_t CUSPARSEAPI
cusparseXcscsort(cusparseHandle_t         handle,
                 int                      m,
                 int                      n,
                 int                      nnz,
                 const cusparseMatDescr_t descrA,
                 const int*               cscColPtrA,
                 int*                     cscRowIndA,
                 int*                     P,
                 void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseScsru2csr_bufferSizeExt(cusparseHandle_t handle,
                                int              m,
                                int              n,
                                int              nnz,
                                float*           csrVal,
                                const int*       csrRowPtr,
                                int*             csrColInd,
                                csru2csrInfo_t   info,
                                size_t*          pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDcsru2csr_bufferSizeExt(cusparseHandle_t handle,
                                int              m,
                                int              n,
                                int              nnz,
                                double*          csrVal,
                                const int*       csrRowPtr,
                                int*             csrColInd,
                                csru2csrInfo_t   info,
                                size_t*          pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCcsru2csr_bufferSizeExt(cusparseHandle_t handle,
                                int              m,
                                int              n,
                                int              nnz,
                                cuComplex*       csrVal,
                                const int*       csrRowPtr,
                                int*             csrColInd,
                                csru2csrInfo_t   info,
                                size_t*          pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZcsru2csr_bufferSizeExt(cusparseHandle_t handle,
                                int              m,
                                int              n,
                                int              nnz,
                                cuDoubleComplex* csrVal,
                                const int*       csrRowPtr,
                                int*             csrColInd,
                                csru2csrInfo_t   info,
                                size_t*          pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseScsru2csr(cusparseHandle_t         handle,
                  int                      m,
                  int                      n,
                  int                      nnz,
                  const cusparseMatDescr_t descrA,
                  float*                   csrVal,
                  const int*               csrRowPtr,
                  int*                     csrColInd,
                  csru2csrInfo_t           info,
                  void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDcsru2csr(cusparseHandle_t         handle,
                  int                      m,
                  int                      n,
                  int                      nnz,
                  const cusparseMatDescr_t descrA,
                  double*                  csrVal,
                  const int*               csrRowPtr,
                  int*                     csrColInd,
                  csru2csrInfo_t           info,
                  void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCcsru2csr(cusparseHandle_t         handle,
                  int                      m,
                  int                      n,
                  int                      nnz,
                  const cusparseMatDescr_t descrA,
                  cuComplex*               csrVal,
                  const int*               csrRowPtr,
                  int*                     csrColInd,
                  csru2csrInfo_t           info,
                  void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZcsru2csr(cusparseHandle_t         handle,
                  int                      m,
                  int                      n,
                  int                      nnz,
                  const cusparseMatDescr_t descrA,
                  cuDoubleComplex*         csrVal,
                  const int*               csrRowPtr,
                  int*                     csrColInd,
                  csru2csrInfo_t           info,
                  void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseScsr2csru(cusparseHandle_t         handle,
                  int                      m,
                  int                      n,
                  int                      nnz,
                  const cusparseMatDescr_t descrA,
                  float*                   csrVal,
                  const int*               csrRowPtr,
                  int*                     csrColInd,
                  csru2csrInfo_t           info,
                  void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDcsr2csru(cusparseHandle_t         handle,
                  int                      m,
                  int                      n,
                  int                      nnz,
                  const cusparseMatDescr_t descrA,
                  double*                  csrVal,
                  const int*               csrRowPtr,
                  int*                     csrColInd,
                  csru2csrInfo_t           info,
                  void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseCcsr2csru(cusparseHandle_t         handle,
                  int                      m,
                  int                      n,
                  int                      nnz,
                  const cusparseMatDescr_t descrA,
                  cuComplex*               csrVal,
                  const int*               csrRowPtr,
                  int*                     csrColInd,
                  csru2csrInfo_t           info,
                  void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseZcsr2csru(cusparseHandle_t         handle,
                  int                      m,
                  int                      n,
                  int                      nnz,
                  const cusparseMatDescr_t descrA,
                  cuDoubleComplex*         csrVal,
                  const int*               csrRowPtr,
                  int*                     csrColInd,
                  csru2csrInfo_t           info,
                  void*                    pBuffer);

#if defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseHpruneDense2csr_bufferSizeExt(cusparseHandle_t         handle,
                                      int                      m,
                                      int                      n,
                                      const __half*            A,
                                      int                      lda,
                                      const __half*            threshold,
                                      const cusparseMatDescr_t descrC,
                                      const __half*            csrSortedValC,
                                      const int*               csrSortedRowPtrC,
                                      const int*               csrSortedColIndC,
                                      size_t* pBufferSizeInBytes);
#endif // defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSpruneDense2csr_bufferSizeExt(cusparseHandle_t         handle,
                                      int                      m,
                                      int                      n,
                                      const float*             A,
                                      int                      lda,
                                      const float*             threshold,
                                      const cusparseMatDescr_t descrC,
                                      const float*             csrSortedValC,
                                      const int*               csrSortedRowPtrC,
                                      const int*               csrSortedColIndC,
                                      size_t* pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDpruneDense2csr_bufferSizeExt(cusparseHandle_t         handle,
                                      int                      m,
                                      int                      n,
                                      const double*            A,
                                      int                      lda,
                                      const double*            threshold,
                                      const cusparseMatDescr_t descrC,
                                      const double*            csrSortedValC,
                                      const int*               csrSortedRowPtrC,
                                      const int*               csrSortedColIndC,
                                      size_t*               pBufferSizeInBytes);

#if defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseHpruneDense2csrNnz(cusparseHandle_t         handle,
                           int                      m,
                           int                      n,
                           const __half*            A,
                           int                      lda,
                           const __half*            threshold,
                           const cusparseMatDescr_t descrC,
                           int*                     csrRowPtrC,
                           int*                     nnzTotalDevHostPtr,
                           void*                    pBuffer);
#endif // defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSpruneDense2csrNnz(cusparseHandle_t         handle,
                           int                      m,
                           int                      n,
                           const float*             A,
                           int                      lda,
                           const float*             threshold,
                           const cusparseMatDescr_t descrC,
                           int*                     csrRowPtrC,
                           int*                     nnzTotalDevHostPtr,
                           void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDpruneDense2csrNnz(cusparseHandle_t         handle,
                           int                      m,
                           int                      n,
                           const double*            A,
                           int                      lda,
                           const double*            threshold,
                           const cusparseMatDescr_t descrC,
                           int*                     csrSortedRowPtrC,
                           int*                     nnzTotalDevHostPtr,
                           void*                    pBuffer);

#if defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseHpruneDense2csr(cusparseHandle_t         handle,
                        int                      m,
                        int                      n,
                        const __half*            A,
                        int                      lda,
                        const __half*            threshold,
                        const cusparseMatDescr_t descrC,
                        __half*                  csrSortedValC,
                        const int*               csrSortedRowPtrC,
                        int*                     csrSortedColIndC,
                        void*                    pBuffer);
#endif // defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSpruneDense2csr(cusparseHandle_t         handle,
                        int                      m,
                        int                      n,
                        const float*             A,
                        int                      lda,
                        const float*             threshold,
                        const cusparseMatDescr_t descrC,
                        float*                   csrSortedValC,
                        const int*               csrSortedRowPtrC,
                        int*                     csrSortedColIndC,
                        void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDpruneDense2csr(cusparseHandle_t         handle,
                        int                      m,
                        int                      n,
                        const double*            A,
                        int                      lda,
                        const double*            threshold,
                        const cusparseMatDescr_t descrC,
                        double*                  csrSortedValC,
                        const int*               csrSortedRowPtrC,
                        int*                     csrSortedColIndC,
                        void*                    pBuffer);

#if defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseHpruneCsr2csr_bufferSizeExt(cusparseHandle_t         handle,
                                    int                      m,
                                    int                      n,
                                    int                      nnzA,
                                    const cusparseMatDescr_t descrA,
                                    const __half*            csrSortedValA,
                                    const int*               csrSortedRowPtrA,
                                    const int*               csrSortedColIndA,
                                    const __half*            threshold,
                                    const cusparseMatDescr_t descrC,
                                    const __half*            csrSortedValC,
                                    const int*               csrSortedRowPtrC,
                                    const int*               csrSortedColIndC,
                                    size_t* pBufferSizeInBytes);
#endif // defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSpruneCsr2csr_bufferSizeExt(cusparseHandle_t         handle,
                                    int                      m,
                                    int                      n,
                                    int                      nnzA,
                                    const cusparseMatDescr_t descrA,
                                    const float*             csrSortedValA,
                                    const int*               csrSortedRowPtrA,
                                    const int*               csrSortedColIndA,
                                    const float*             threshold,
                                    const cusparseMatDescr_t descrC,
                                    const float*             csrSortedValC,
                                    const int*               csrSortedRowPtrC,
                                    const int*               csrSortedColIndC,
                                    size_t*                 pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDpruneCsr2csr_bufferSizeExt(cusparseHandle_t         handle,
                                    int                      m,
                                    int                      n,
                                    int                      nnzA,
                                    const cusparseMatDescr_t descrA,
                                    const double*            csrSortedValA,
                                    const int*               csrSortedRowPtrA,
                                    const int*               csrSortedColIndA,
                                    const double*            threshold,
                                    const cusparseMatDescr_t descrC,
                                    const double*            csrSortedValC,
                                    const int*               csrSortedRowPtrC,
                                    const int*               csrSortedColIndC,
                                    size_t*                 pBufferSizeInBytes);

#if defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseHpruneCsr2csrNnz(cusparseHandle_t         handle,
                         int                      m,
                         int                      n,
                         int                      nnzA,
                         const cusparseMatDescr_t descrA,
                         const __half*            csrSortedValA,
                         const int*               csrSortedRowPtrA,
                         const int*               csrSortedColIndA,
                         const __half*            threshold,
                         const cusparseMatDescr_t descrC,
                         int*                     csrSortedRowPtrC,
                         int*                     nnzTotalDevHostPtr,
                         void*                    pBuffer);
#endif // defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSpruneCsr2csrNnz(cusparseHandle_t         handle,
                         int                      m,
                         int                      n,
                         int                      nnzA,
                         const cusparseMatDescr_t descrA,
                         const float*             csrSortedValA,
                         const int*               csrSortedRowPtrA,
                         const int*               csrSortedColIndA,
                         const float*             threshold,
                         const cusparseMatDescr_t descrC,
                         int*                     csrSortedRowPtrC,
                         int*                     nnzTotalDevHostPtr,
                         void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDpruneCsr2csrNnz(cusparseHandle_t         handle,
                          int                      m,
                          int                      n,
                          int                      nnzA,
                          const cusparseMatDescr_t descrA,
                          const double*            csrSortedValA,
                          const int*               csrSortedRowPtrA,
                          const int*               csrSortedColIndA,
                          const double*            threshold,
                          const cusparseMatDescr_t descrC,
                          int*                     csrSortedRowPtrC,
                          int*                     nnzTotalDevHostPtr,
                          void*                    pBuffer);

#if defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseHpruneCsr2csr(cusparseHandle_t         handle,
                      int                      m,
                      int                      n,
                      int                      nnzA,
                      const cusparseMatDescr_t descrA,
                      const __half*            csrSortedValA,
                      const int*               csrSortedRowPtrA,
                      const int*               csrSortedColIndA,
                      const __half*            threshold,
                      const cusparseMatDescr_t descrC,
                      __half*                  csrSortedValC,
                      const int*               csrSortedRowPtrC,
                      int*                     csrSortedColIndC,
                      void*                    pBuffer);
#endif // defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSpruneCsr2csr(cusparseHandle_t         handle,
                      int                      m,
                      int                      n,
                      int                      nnzA,
                      const cusparseMatDescr_t descrA,
                      const float*             csrSortedValA,
                      const int*               csrSortedRowPtrA,
                      const int*               csrSortedColIndA,
                      const float*             threshold,
                      const cusparseMatDescr_t descrC,
                      float*                   csrSortedValC,
                      const int*               csrSortedRowPtrC,
                      int*                     csrSortedColIndC,
                      void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDpruneCsr2csr(cusparseHandle_t         handle,
                      int                      m,
                      int                      n,
                      int                      nnzA,
                      const cusparseMatDescr_t descrA,
                      const double*            csrSortedValA,
                      const int*               csrSortedRowPtrA,
                      const int*               csrSortedColIndA,
                      const double*            threshold,
                      const cusparseMatDescr_t descrC,
                      double*                  csrSortedValC,
                      const int*               csrSortedRowPtrC,
                      int*                     csrSortedColIndC,
                      void*                    pBuffer);

#if defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseHpruneDense2csrByPercentage_bufferSizeExt(
                                   cusparseHandle_t         handle,
                                   int                      m,
                                   int                      n,
                                   const __half*            A,
                                   int                      lda,
                                   float                    percentage,
                                   const cusparseMatDescr_t descrC,
                                   const __half*            csrSortedValC,
                                   const int*               csrSortedRowPtrC,
                                   const int*               csrSortedColIndC,
                                   pruneInfo_t              info,
                                   size_t*                  pBufferSizeInBytes);

#endif // defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSpruneDense2csrByPercentage_bufferSizeExt(
                                   cusparseHandle_t         handle,
                                   int                      m,
                                   int                      n,
                                   const float*             A,
                                   int                      lda,
                                   float                    percentage,
                                   const cusparseMatDescr_t descrC,
                                   const float*             csrSortedValC,
                                   const int*               csrSortedRowPtrC,
                                   const int*               csrSortedColIndC,
                                   pruneInfo_t              info,
                                   size_t*                  pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDpruneDense2csrByPercentage_bufferSizeExt(
                                   cusparseHandle_t         handle,
                                   int                      m,
                                   int                      n,
                                   const double*            A,
                                   int                      lda,
                                   float                    percentage,
                                   const cusparseMatDescr_t descrC,
                                   const double*            csrSortedValC,
                                   const int*               csrSortedRowPtrC,
                                   const int*               csrSortedColIndC,
                                   pruneInfo_t              info,
                                   size_t*                  pBufferSizeInBytes);

#if defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseHpruneDense2csrNnzByPercentage(
                                    cusparseHandle_t         handle,
                                    int                      m,
                                    int                      n,
                                    const __half*            A,
                                    int                      lda,
                                    float                    percentage,
                                    const cusparseMatDescr_t descrC,
                                    int*                     csrRowPtrC,
                                    int*                     nnzTotalDevHostPtr,
                                    pruneInfo_t              info,
                                    void*                    pBuffer);
#endif // defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSpruneDense2csrNnzByPercentage(
                                    cusparseHandle_t         handle,
                                    int                      m,
                                    int                      n,
                                    const float*             A,
                                    int                      lda,
                                    float                    percentage,
                                    const cusparseMatDescr_t descrC,
                                    int*                     csrRowPtrC,
                                    int*                     nnzTotalDevHostPtr,
                                    pruneInfo_t              info,
                                    void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDpruneDense2csrNnzByPercentage(
                                    cusparseHandle_t         handle,
                                    int                      m,
                                    int                      n,
                                    const double*            A,
                                    int                      lda,
                                    float                    percentage,
                                    const cusparseMatDescr_t descrC,
                                    int*                     csrRowPtrC,
                                    int*                     nnzTotalDevHostPtr,
                                    pruneInfo_t              info,
                                    void*                    pBuffer);

#if defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseHpruneDense2csrByPercentage(cusparseHandle_t         handle,
                                    int                      m,
                                    int                      n,
                                    const __half*            A,
                                    int                      lda,
                                    float                    percentage,
                                    const cusparseMatDescr_t descrC,
                                    __half*                  csrSortedValC,
                                    const int*               csrSortedRowPtrC,
                                    int*                     csrSortedColIndC,
                                    pruneInfo_t              info,
                                    void*                    pBuffer);

#endif // defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSpruneDense2csrByPercentage(cusparseHandle_t         handle,
                                    int                      m,
                                    int                      n,
                                    const float*             A,
                                    int                      lda,
                                    float                    percentage,
                                    const cusparseMatDescr_t descrC,
                                    float*                   csrSortedValC,
                                    const int*               csrSortedRowPtrC,
                                    int*                     csrSortedColIndC,
                                    pruneInfo_t              info,
                                    void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDpruneDense2csrByPercentage(cusparseHandle_t         handle,
                                    int                      m,
                                    int                      n,
                                    const double*            A,
                                    int                      lda,
                                    float                    percentage,
                                    const cusparseMatDescr_t descrC,
                                    double*                  csrSortedValC,
                                    const int*               csrSortedRowPtrC,
                                    int*                     csrSortedColIndC,
                                    pruneInfo_t              info,
                                    void*                    pBuffer);

#if defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseHpruneCsr2csrByPercentage_bufferSizeExt(
                                   cusparseHandle_t         handle,
                                   int                      m,
                                   int                      n,
                                   int                      nnzA,
                                   const cusparseMatDescr_t descrA,
                                   const __half*            csrSortedValA,
                                   const int*               csrSortedRowPtrA,
                                   const int*               csrSortedColIndA,
                                   float                    percentage,
                                   const cusparseMatDescr_t descrC,
                                   const __half*            csrSortedValC,
                                   const int*               csrSortedRowPtrC,
                                   const int*               csrSortedColIndC,
                                   pruneInfo_t              info,
                                   size_t*                  pBufferSizeInBytes);

#endif // defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSpruneCsr2csrByPercentage_bufferSizeExt(
                                   cusparseHandle_t         handle,
                                   int                      m,
                                   int                      n,
                                   int                      nnzA,
                                   const cusparseMatDescr_t descrA,
                                   const float*             csrSortedValA,
                                   const int*               csrSortedRowPtrA,
                                   const int*               csrSortedColIndA,
                                   float                    percentage,
                                   const cusparseMatDescr_t descrC,
                                   const float*             csrSortedValC,
                                   const int*               csrSortedRowPtrC,
                                   const int*               csrSortedColIndC,
                                   pruneInfo_t              info,
                                   size_t*                  pBufferSizeInBytes);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDpruneCsr2csrByPercentage_bufferSizeExt(
                                   cusparseHandle_t         handle,
                                   int                      m,
                                   int                      n,
                                   int                      nnzA,
                                   const cusparseMatDescr_t descrA,
                                   const double*            csrSortedValA,
                                   const int*               csrSortedRowPtrA,
                                   const int*               csrSortedColIndA,
                                   float                    percentage,
                                   const cusparseMatDescr_t descrC,
                                   const double*            csrSortedValC,
                                   const int*               csrSortedRowPtrC,
                                   const int*               csrSortedColIndC,
                                   pruneInfo_t              info,
                                   size_t*                  pBufferSizeInBytes);

#if defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseHpruneCsr2csrNnzByPercentage(
                                    cusparseHandle_t         handle,
                                    int                      m,
                                    int                      n,
                                    int                      nnzA,
                                    const cusparseMatDescr_t descrA,
                                    const __half*            csrSortedValA,
                                    const int*               csrSortedRowPtrA,
                                    const int*               csrSortedColIndA,
                                    float                    percentage,
                                    const cusparseMatDescr_t descrC,
                                    int*                     csrSortedRowPtrC,
                                    int*                     nnzTotalDevHostPtr,
                                    pruneInfo_t              info,
                                    void*                    pBuffer);

#endif // defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSpruneCsr2csrNnzByPercentage(
                                    cusparseHandle_t         handle,
                                    int                      m,
                                    int                      n,
                                    int                      nnzA,
                                    const cusparseMatDescr_t descrA,
                                    const float*             csrSortedValA,
                                    const int*               csrSortedRowPtrA,
                                    const int*               csrSortedColIndA,
                                    float                    percentage,
                                    const cusparseMatDescr_t descrC,
                                    int*                     csrSortedRowPtrC,
                                    int*                     nnzTotalDevHostPtr,
                                    pruneInfo_t              info,
                                    void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDpruneCsr2csrNnzByPercentage(
                                    cusparseHandle_t         handle,
                                    int                      m,
                                    int                      n,
                                    int                      nnzA,
                                    const cusparseMatDescr_t descrA,
                                    const double*            csrSortedValA,
                                    const int*               csrSortedRowPtrA,
                                    const int*               csrSortedColIndA,
                                    float                    percentage,
                                    const cusparseMatDescr_t descrC,
                                    int*                     csrSortedRowPtrC,
                                    int*                     nnzTotalDevHostPtr,
                                    pruneInfo_t              info,
                                    void*                    pBuffer);

#if defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseHpruneCsr2csrByPercentage(cusparseHandle_t         handle,
                                  int                      m,
                                  int                      n,
                                  int                      nnzA,
                                  const cusparseMatDescr_t descrA,
                                  const __half*            csrSortedValA,
                                  const int*               csrSortedRowPtrA,
                                  const int*               csrSortedColIndA,
                                  float percentage, /* between 0 to 100 */
                                  const cusparseMatDescr_t descrC,
                                  __half*                  csrSortedValC,
                                  const int*               csrSortedRowPtrC,
                                  int*                     csrSortedColIndC,
                                  pruneInfo_t              info,
                                  void*                    pBuffer);

#endif // defined(__cplusplus)

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseSpruneCsr2csrByPercentage(cusparseHandle_t         handle,
                                  int                      m,
                                  int                      n,
                                  int                      nnzA,
                                  const cusparseMatDescr_t descrA,
                                  const float*             csrSortedValA,
                                  const int*               csrSortedRowPtrA,
                                  const int*               csrSortedColIndA,
                                  float                    percentage,
                                  const cusparseMatDescr_t descrC,
                                  float*                   csrSortedValC,
                                  const int*               csrSortedRowPtrC,
                                  int*                     csrSortedColIndC,
                                  pruneInfo_t              info,
                                  void*                    pBuffer);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseDpruneCsr2csrByPercentage(cusparseHandle_t         handle,
                                  int                      m,
                                  int                      n,
                                  int                      nnzA,
                                  const cusparseMatDescr_t descrA,
                                  const double*            csrSortedValA,
                                  const int*               csrSortedRowPtrA,
                                  const int*               csrSortedColIndA,
                                  float                    percentage,
                                  const cusparseMatDescr_t descrC,
                                  double*                  csrSortedValC,
                                  const int*               csrSortedRowPtrC,
                                  int*                     csrSortedColIndC,
                                  pruneInfo_t              info,
                                  void*                    pBuffer);

//##############################################################################
//# CSR2CSC
//##############################################################################

typedef enum {
    CUSPARSE_CSR2CSC_ALG_DEFAULT = 1,
    CUSPARSE_CSR2CSC_ALG1 = 1
} cusparseCsr2CscAlg_t;

cusparseStatus_t CUSPARSEAPI
cusparseCsr2cscEx2(cusparseHandle_t     handle,
                   int                  m,
                   int                  n,
                   int                  nnz,
                   const void*          csrVal,
                   const int*           csrRowPtr,
                   const int*           csrColInd,
                   void*                cscVal,
                   int*                 cscColPtr,
                   int*                 cscRowInd,
                   cudaDataType         valType,
                   cusparseAction_t     copyValues,
                   cusparseIndexBase_t  idxBase,
                   cusparseCsr2CscAlg_t alg,
                   void*                buffer);

cusparseStatus_t CUSPARSEAPI
cusparseCsr2cscEx2_bufferSize(cusparseHandle_t     handle,
                              int                  m,
                              int                  n,
                              int                  nnz,
                              const void*          csrVal,
                              const int*           csrRowPtr,
                              const int*           csrColInd,
                              void*                cscVal,
                              int*                 cscColPtr,
                              int*                 cscRowInd,
                              cudaDataType         valType,
                              cusparseAction_t     copyValues,
                              cusparseIndexBase_t  idxBase,
                              cusparseCsr2CscAlg_t alg,
                              size_t*              bufferSize);

// #############################################################################
// # GENERIC APIs - Enumerators and Opaque Data Structures
// #############################################################################

typedef enum {
    CUSPARSE_FORMAT_CSR            = 1, ///< Compressed Sparse Row (CSR)
    CUSPARSE_FORMAT_CSC            = 2, ///< Compressed Sparse Column (CSC)
    CUSPARSE_FORMAT_COO            = 3, ///< Coordinate (COO) - Structure of Arrays
    CUSPARSE_FORMAT_BLOCKED_ELL    = 5, ///< Blocked ELL
    CUSPARSE_FORMAT_BSR            = 6, ///< Blocked Compressed Sparse Row (BSR)
    CUSPARSE_FORMAT_SLICED_ELLPACK = 7 ///< Sliced ELL
} cusparseFormat_t;

typedef enum {
    CUSPARSE_ORDER_COL = 1, ///< Column-Major Order - Matrix memory layout
    CUSPARSE_ORDER_ROW = 2  ///< Row-Major Order - Matrix memory layout
} cusparseOrder_t;

typedef enum {
    CUSPARSE_INDEX_16U = 1, ///< 16-bit unsigned integer for matrix/vector
                            ///< indices
    CUSPARSE_INDEX_32I = 2, ///< 32-bit signed integer for matrix/vector indices
    CUSPARSE_INDEX_64I = 3  ///< 64-bit signed integer for matrix/vector indices
} cusparseIndexType_t;

//------------------------------------------------------------------------------

struct cusparseSpVecDescr;
struct cusparseDnVecDescr;
struct cusparseSpMatDescr;
struct cusparseDnMatDescr;

typedef struct cusparseSpVecDescr* cusparseSpVecDescr_t;
typedef struct cusparseDnVecDescr* cusparseDnVecDescr_t;
typedef struct cusparseSpMatDescr* cusparseSpMatDescr_t;
typedef struct cusparseDnMatDescr* cusparseDnMatDescr_t;

typedef struct cusparseSpVecDescr const* cusparseConstSpVecDescr_t;
typedef struct cusparseDnVecDescr const* cusparseConstDnVecDescr_t;
typedef struct cusparseSpMatDescr const* cusparseConstSpMatDescr_t;
typedef struct cusparseDnMatDescr const* cusparseConstDnMatDescr_t;

// #############################################################################
// # SPARSE VECTOR DESCRIPTOR
// #############################################################################

cusparseStatus_t CUSPARSEAPI
cusparseCreateSpVec(cusparseSpVecDescr_t* spVecDescr,
                    int64_t               size,
                    int64_t               nnz,
                    void*                 indices,
                    void*                 values,
                    cusparseIndexType_t   idxType,
                    cusparseIndexBase_t   idxBase,
                    cudaDataType          valueType);

cusparseStatus_t CUSPARSEAPI
cusparseCreateConstSpVec(cusparseConstSpVecDescr_t* spVecDescr,
                         int64_t                    size,
                         int64_t                    nnz,
                         const void*                indices,
                         const void*                values,
                         cusparseIndexType_t        idxType,
                         cusparseIndexBase_t        idxBase,
                         cudaDataType               valueType);

cusparseStatus_t CUSPARSEAPI
cusparseDestroySpVec(cusparseConstSpVecDescr_t spVecDescr);

cusparseStatus_t CUSPARSEAPI
cusparseSpVecGet(cusparseSpVecDescr_t spVecDescr,
                 int64_t*             size,
                 int64_t*             nnz,
                 void**               indices,
                 void**               values,
                 cusparseIndexType_t* idxType,
                 cusparseIndexBase_t* idxBase,
                 cudaDataType*        valueType);

cusparseStatus_t CUSPARSEAPI
cusparseConstSpVecGet(cusparseConstSpVecDescr_t spVecDescr,
                      int64_t*             size,
                      int64_t*             nnz,
                      const void**         indices,
                      const void**         values,
                      cusparseIndexType_t* idxType,
                      cusparseIndexBase_t* idxBase,
                      cudaDataType*        valueType);

cusparseStatus_t CUSPARSEAPI
cusparseSpVecGetIndexBase(cusparseConstSpVecDescr_t spVecDescr,
                          cusparseIndexBase_t*      idxBase);

cusparseStatus_t CUSPARSEAPI
cusparseSpVecGetValues(cusparseSpVecDescr_t spVecDescr,
                       void**               values);

cusparseStatus_t CUSPARSEAPI
cusparseConstSpVecGetValues(cusparseConstSpVecDescr_t spVecDescr,
                            const void**              values);

cusparseStatus_t CUSPARSEAPI
cusparseSpVecSetValues(cusparseSpVecDescr_t spVecDescr,
                       void*                values);

// #############################################################################
// # DENSE VECTOR DESCRIPTOR
// #############################################################################

cusparseStatus_t CUSPARSEAPI
cusparseCreateDnVec(cusparseDnVecDescr_t* dnVecDescr,
                    int64_t               size,
                    void*                 values,
                    cudaDataType          valueType);

cusparseStatus_t CUSPARSEAPI
cusparseCreateConstDnVec(cusparseConstDnVecDescr_t* dnVecDescr,
                         int64_t                    size,
                         const void*                values,
                         cudaDataType               valueType);

cusparseStatus_t CUSPARSEAPI
cusparseDestroyDnVec(cusparseConstDnVecDescr_t dnVecDescr);

cusparseStatus_t CUSPARSEAPI
cusparseDnVecGet(cusparseDnVecDescr_t dnVecDescr,
                 int64_t*             size,
                 void**               values,
                 cudaDataType*        valueType);

cusparseStatus_t CUSPARSEAPI
cusparseConstDnVecGet(cusparseConstDnVecDescr_t dnVecDescr,
                      int64_t*                  size,
                      const void**              values,
                      cudaDataType*             valueType);

cusparseStatus_t CUSPARSEAPI
cusparseDnVecGetValues(cusparseDnVecDescr_t dnVecDescr,
                       void**               values);

cusparseStatus_t CUSPARSEAPI
cusparseConstDnVecGetValues(cusparseConstDnVecDescr_t dnVecDescr,
                            const void**              values);

cusparseStatus_t CUSPARSEAPI
cusparseDnVecSetValues(cusparseDnVecDescr_t dnVecDescr,
                       void*                values);

// #############################################################################
// # SPARSE MATRIX DESCRIPTOR
// #############################################################################

cusparseStatus_t CUSPARSEAPI
cusparseDestroySpMat(cusparseConstSpMatDescr_t spMatDescr);

 cusparseStatus_t CUSPARSEAPI
cusparseSpMatGetFormat(cusparseConstSpMatDescr_t spMatDescr,
                       cusparseFormat_t*         format);

cusparseStatus_t CUSPARSEAPI
cusparseSpMatGetIndexBase(cusparseConstSpMatDescr_t spMatDescr,
                          cusparseIndexBase_t*      idxBase);

cusparseStatus_t CUSPARSEAPI
cusparseSpMatGetValues(cusparseSpMatDescr_t spMatDescr,
                       void**               values);

cusparseStatus_t CUSPARSEAPI
cusparseConstSpMatGetValues(cusparseConstSpMatDescr_t spMatDescr,
                            const void**               values);

cusparseStatus_t CUSPARSEAPI
cusparseSpMatSetValues(cusparseSpMatDescr_t spMatDescr,
                       void*                values);

cusparseStatus_t CUSPARSEAPI
cusparseSpMatGetSize(cusparseConstSpMatDescr_t spMatDescr,
                     int64_t*                  rows,
                     int64_t*                  cols,
                     int64_t*                  nnz);

cusparseStatus_t CUSPARSEAPI
cusparseSpMatGetStridedBatch(cusparseConstSpMatDescr_t spMatDescr,
                             int*                      batchCount);

cusparseStatus_t CUSPARSEAPI
cusparseCooSetStridedBatch(cusparseSpMatDescr_t spMatDescr,
                           int                  batchCount,
                           int64_t              batchStride);

cusparseStatus_t CUSPARSEAPI
cusparseCsrSetStridedBatch(cusparseSpMatDescr_t spMatDescr,
                           int                  batchCount,
                           int64_t              offsetsBatchStride,
                           int64_t              columnsValuesBatchStride);

cusparseStatus_t CUSPARSEAPI
cusparseBsrSetStridedBatch(cusparseSpMatDescr_t spMatDescr,
                           int                  batchCount,
                           int64_t              offsetsBatchStride,
                           int64_t              columnsBatchStride,
                           int64_t              ValuesBatchStride);

typedef enum {
    CUSPARSE_SPMAT_FILL_MODE,
    CUSPARSE_SPMAT_DIAG_TYPE
} cusparseSpMatAttribute_t;

cusparseStatus_t CUSPARSEAPI
cusparseSpMatGetAttribute(cusparseConstSpMatDescr_t spMatDescr,
                          cusparseSpMatAttribute_t  attribute,
                          void*                     data,
                          size_t                    dataSize);

cusparseStatus_t CUSPARSEAPI
cusparseSpMatSetAttribute(cusparseSpMatDescr_t     spMatDescr,
                          cusparseSpMatAttribute_t attribute,
                          void*                    data,
                          size_t                   dataSize);

//------------------------------------------------------------------------------
// ### CSR ###

cusparseStatus_t CUSPARSEAPI
cusparseCreateCsr(cusparseSpMatDescr_t* spMatDescr,
                  int64_t               rows,
                  int64_t               cols,
                  int64_t               nnz,
                  void*                 csrRowOffsets,
                  void*                 csrColInd,
                  void*                 csrValues,
                  cusparseIndexType_t   csrRowOffsetsType,
                  cusparseIndexType_t   csrColIndType,
                  cusparseIndexBase_t   idxBase,
                  cudaDataType          valueType);

cusparseStatus_t CUSPARSEAPI
cusparseCreateConstCsr(cusparseConstSpMatDescr_t* spMatDescr,
                       int64_t                    rows,
                       int64_t                    cols,
                       int64_t                    nnz,
                       const void*                csrRowOffsets,
                       const void*                csrColInd,
                       const void*                csrValues,
                       cusparseIndexType_t        csrRowOffsetsType,
                       cusparseIndexType_t        csrColIndType,
                       cusparseIndexBase_t        idxBase,
                       cudaDataType               valueType);

cusparseStatus_t CUSPARSEAPI
cusparseCreateCsc(cusparseSpMatDescr_t* spMatDescr,
                  int64_t               rows,
                  int64_t               cols,
                  int64_t               nnz,
                  void*                 cscColOffsets,
                  void*                 cscRowInd,
                  void*                 cscValues,
                  cusparseIndexType_t   cscColOffsetsType,
                  cusparseIndexType_t   cscRowIndType,
                  cusparseIndexBase_t   idxBase,
                  cudaDataType          valueType);

cusparseStatus_t CUSPARSEAPI
cusparseCreateConstCsc(cusparseConstSpMatDescr_t* spMatDescr,
                       int64_t                    rows,
                       int64_t                    cols,
                       int64_t                    nnz,
                       const void*                cscColOffsets,
                       const void*                cscRowInd,
                       const void*                cscValues,
                       cusparseIndexType_t        cscColOffsetsType,
                       cusparseIndexType_t        cscRowIndType,
                       cusparseIndexBase_t        idxBase,
                       cudaDataType               valueType);

cusparseStatus_t CUSPARSEAPI
cusparseCsrGet(cusparseSpMatDescr_t spMatDescr,
               int64_t*             rows,
               int64_t*             cols,
               int64_t*             nnz,
               void**               csrRowOffsets,
               void**               csrColInd,
               void**               csrValues,
               cusparseIndexType_t* csrRowOffsetsType,
               cusparseIndexType_t* csrColIndType,
               cusparseIndexBase_t* idxBase,
               cudaDataType*        valueType);

cusparseStatus_t CUSPARSEAPI
cusparseConstCsrGet(cusparseConstSpMatDescr_t spMatDescr,
                    int64_t*                  rows,
                    int64_t*                  cols,
                    int64_t*                  nnz,
                    const void**              csrRowOffsets,
                    const void**              csrColInd,
                    const void**              csrValues,
                    cusparseIndexType_t*      csrRowOffsetsType,
                    cusparseIndexType_t*      csrColIndType,
                    cusparseIndexBase_t*      idxBase,
                    cudaDataType*             valueType);

cusparseStatus_t CUSPARSEAPI
cusparseCscGet(cusparseSpMatDescr_t spMatDescr,
               int64_t*             rows,
               int64_t*             cols,
               int64_t*             nnz,
               void**               cscColOffsets,
               void**               cscRowInd,
               void**               cscValues,
               cusparseIndexType_t* cscColOffsetsType,
               cusparseIndexType_t* cscRowIndType,
               cusparseIndexBase_t* idxBase,
               cudaDataType*        valueType);

cusparseStatus_t CUSPARSEAPI
cusparseConstCscGet(cusparseConstSpMatDescr_t spMatDescr,
                    int64_t*                  rows,
                    int64_t*                  cols,
                    int64_t*                  nnz,
                    const void**              cscColOffsets,
                    const void**              cscRowInd,
                    const void**              cscValues,
                    cusparseIndexType_t*      cscColOffsetsType,
                    cusparseIndexType_t*      cscRowIndType,
                    cusparseIndexBase_t*      idxBase,
                    cudaDataType*             valueType);

cusparseStatus_t CUSPARSEAPI
cusparseCsrSetPointers(cusparseSpMatDescr_t spMatDescr,
                       void*                csrRowOffsets,
                       void*                csrColInd,
                       void*                csrValues);

cusparseStatus_t CUSPARSEAPI
cusparseCscSetPointers(cusparseSpMatDescr_t spMatDescr,
                       void*                cscColOffsets,
                       void*                cscRowInd,
                       void*                cscValues);

//------------------------------------------------------------------------------
// ### BSR ###

cusparseStatus_t CUSPARSEAPI
cusparseCreateBsr(cusparseSpMatDescr_t* spMatDescr,
                  int64_t               brows,
                  int64_t               bcols,
                  int64_t               bnnz,
                  int64_t               rowBlockSize,
                  int64_t               colBlockSize,
                  void*                 bsrRowOffsets,
                  void*                 bsrColInd,
                  void*                 bsrValues,
                  cusparseIndexType_t   bsrRowOffsetsType,
                  cusparseIndexType_t   bsrColIndType,
                  cusparseIndexBase_t   idxBase,
                  cudaDataType          valueType,
                  cusparseOrder_t       order);

cusparseStatus_t CUSPARSEAPI
cusparseCreateConstBsr(cusparseConstSpMatDescr_t* spMatDescr,
                       int64_t                    brows,
                       int64_t                    bcols,
                       int64_t                    bnnz,
                       int64_t                    rowBlockDim,
                       int64_t                    colBlockDim,
                       const void*                bsrRowOffsets,
                       const void*                bsrColInd,
                       const void*                bsrValues,
                       cusparseIndexType_t        bsrRowOffsetsType,
                       cusparseIndexType_t        bsrColIndType,
                       cusparseIndexBase_t        idxBase,
                       cudaDataType               valueType,
                       cusparseOrder_t            order);

//------------------------------------------------------------------------------
// ### COO ###

cusparseStatus_t CUSPARSEAPI
cusparseCreateCoo(cusparseSpMatDescr_t* spMatDescr,
                  int64_t               rows,
                  int64_t               cols,
                  int64_t               nnz,
                  void*                 cooRowInd,
                  void*                 cooColInd,
                  void*                 cooValues,
                  cusparseIndexType_t   cooIdxType,
                  cusparseIndexBase_t   idxBase,
                  cudaDataType          valueType);

cusparseStatus_t CUSPARSEAPI
cusparseCreateConstCoo(cusparseConstSpMatDescr_t* spMatDescr,
                       int64_t                    rows,
                       int64_t                    cols,
                       int64_t                    nnz,
                       const void*                cooRowInd,
                       const void*                cooColInd,
                       const void*                cooValues,
                       cusparseIndexType_t        cooIdxType,
                       cusparseIndexBase_t        idxBase,
                       cudaDataType               valueType);

cusparseStatus_t CUSPARSEAPI
cusparseCooGet(cusparseSpMatDescr_t spMatDescr,
               int64_t*             rows,
               int64_t*             cols,
               int64_t*             nnz,
               void**               cooRowInd,  // COO row indices
               void**               cooColInd,  // COO column indices
               void**               cooValues,  // COO values
               cusparseIndexType_t* idxType,
               cusparseIndexBase_t* idxBase,
               cudaDataType*        valueType);

cusparseStatus_t CUSPARSEAPI
cusparseConstCooGet(cusparseConstSpMatDescr_t spMatDescr,
                    int64_t*                  rows,
                    int64_t*                  cols,
                    int64_t*                  nnz,
                    const void**              cooRowInd,  // COO row indices
                    const void**              cooColInd,  // COO column indices
                    const void**              cooValues,  // COO values
                    cusparseIndexType_t*      idxType,
                    cusparseIndexBase_t*      idxBase,
                    cudaDataType*             valueType);

cusparseStatus_t CUSPARSEAPI
cusparseCooSetPointers(cusparseSpMatDescr_t spMatDescr,
                       void*                cooRows,
                       void*                cooColumns,
                       void*                cooValues);

//------------------------------------------------------------------------------
// ### BLOCKED ELL ###

cusparseStatus_t CUSPARSEAPI
cusparseCreateBlockedEll(cusparseSpMatDescr_t* spMatDescr,
                         int64_t               rows,
                         int64_t               cols,
                         int64_t               ellBlockSize,
                         int64_t               ellCols,
                         void*                 ellColInd,
                         void*                 ellValue,
                         cusparseIndexType_t   ellIdxType,
                         cusparseIndexBase_t   idxBase,
                         cudaDataType          valueType);

cusparseStatus_t CUSPARSEAPI
cusparseCreateConstBlockedEll(cusparseConstSpMatDescr_t* spMatDescr,
                              int64_t                    rows,
                              int64_t                    cols,
                              int64_t                    ellBlockSize,
                              int64_t                    ellCols,
                              const void*                ellColInd,
                              const void*                ellValue,
                              cusparseIndexType_t        ellIdxType,
                              cusparseIndexBase_t        idxBase,
                              cudaDataType               valueType);

cusparseStatus_t CUSPARSEAPI
cusparseBlockedEllGet(cusparseSpMatDescr_t spMatDescr,
                      int64_t*             rows,
                      int64_t*             cols,
                      int64_t*             ellBlockSize,
                      int64_t*             ellCols,
                      void**               ellColInd,
                      void**               ellValue,
                      cusparseIndexType_t* ellIdxType,
                      cusparseIndexBase_t* idxBase,
                      cudaDataType*        valueType);

cusparseStatus_t CUSPARSEAPI
cusparseConstBlockedEllGet(cusparseConstSpMatDescr_t spMatDescr,
                           int64_t*                  rows,
                           int64_t*                  cols,
                           int64_t*                  ellBlockSize,
                           int64_t*                  ellCols,
                           const void**              ellColInd,
                           const void**              ellValue,
                           cusparseIndexType_t*      ellIdxType,
                           cusparseIndexBase_t*      idxBase,
                           cudaDataType*             valueType);

//------------------------------------------------------------------------------
// ### Sliced ELLPACK ###

cusparseStatus_t CUSPARSEAPI
cusparseCreateSlicedEll(cusparseSpMatDescr_t*   spMatDescr,
                        int64_t                 rows,
                        int64_t                 cols,
                        int64_t                 nnz,
                        int64_t                 sellValuesSize,
                        int64_t                 sliceSize,
	                void*                   sellSliceOffsets,
                        void*                   sellColInd,
                        void*                   sellValues,
			cusparseIndexType_t     sellSliceOffsetsType,
                        cusparseIndexType_t     sellColIndType,
                        cusparseIndexBase_t     idxBase,
                        cudaDataType            valueType);

cusparseStatus_t CUSPARSEAPI
cusparseCreateConstSlicedEll(cusparseConstSpMatDescr_t* spMatDescr,
                             int64_t                    rows,
                             int64_t                    cols,
                             int64_t                    nnz,
                             int64_t                    sellValuesSize,
                             int64_t                    sliceSize,
                             const void*                sellSliceOffsets,
                             const void*                sellColInd,
                             const void*                sellValues,
                             cusparseIndexType_t        sellSliceOffsetsType,
                             cusparseIndexType_t        sellColIndType,
                             cusparseIndexBase_t        idxBase,
                             cudaDataType               valueType);

// #############################################################################
// # DENSE MATRIX DESCRIPTOR
// #############################################################################

cusparseStatus_t CUSPARSEAPI
cusparseCreateDnMat(cusparseDnMatDescr_t* dnMatDescr,
                    int64_t               rows,
                    int64_t               cols,
                    int64_t               ld,
                    void*                 values,
                    cudaDataType          valueType,
                    cusparseOrder_t       order);

cusparseStatus_t CUSPARSEAPI
cusparseCreateConstDnMat(cusparseConstDnMatDescr_t* dnMatDescr,
                         int64_t                    rows,
                         int64_t                    cols,
                         int64_t                    ld,
                         const void*                values,
                         cudaDataType               valueType,
                         cusparseOrder_t            order);

cusparseStatus_t CUSPARSEAPI
cusparseDestroyDnMat(cusparseConstDnMatDescr_t dnMatDescr);

cusparseStatus_t CUSPARSEAPI
cusparseDnMatGet(cusparseDnMatDescr_t dnMatDescr,
                 int64_t*             rows,
                 int64_t*             cols,
                 int64_t*             ld,
                 void**               values,
                 cudaDataType*        type,
                 cusparseOrder_t*     order);

cusparseStatus_t CUSPARSEAPI
cusparseConstDnMatGet(cusparseConstDnMatDescr_t dnMatDescr,
                      int64_t*                  rows,
                      int64_t*                  cols,
                      int64_t*                  ld,
                      const void**              values,
                      cudaDataType*             type,
                      cusparseOrder_t*          order);

cusparseStatus_t CUSPARSEAPI
cusparseDnMatGetValues(cusparseDnMatDescr_t dnMatDescr,
                       void**               values);

cusparseStatus_t CUSPARSEAPI
cusparseConstDnMatGetValues(cusparseConstDnMatDescr_t dnMatDescr,
                            const void**              values);

cusparseStatus_t CUSPARSEAPI
cusparseDnMatSetValues(cusparseDnMatDescr_t dnMatDescr,
                       void*                values);

cusparseStatus_t CUSPARSEAPI
cusparseDnMatSetStridedBatch(cusparseDnMatDescr_t dnMatDescr,
                             int                  batchCount,
                             int64_t              batchStride);

cusparseStatus_t CUSPARSEAPI
cusparseDnMatGetStridedBatch(cusparseConstDnMatDescr_t dnMatDescr,
                             int*                      batchCount,
                             int64_t*                  batchStride);

// #############################################################################
// # VECTOR-VECTOR OPERATIONS
// #############################################################################

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseAxpby(cusparseHandle_t          handle,
              const void*               alpha,
              cusparseConstSpVecDescr_t vecX,
              const void*               beta,
              cusparseDnVecDescr_t      vecY);

cusparseStatus_t CUSPARSEAPI
cusparseGather(cusparseHandle_t          handle,
               cusparseConstDnVecDescr_t vecY,
               cusparseSpVecDescr_t      vecX);

cusparseStatus_t CUSPARSEAPI
cusparseScatter(cusparseHandle_t          handle,
                cusparseConstSpVecDescr_t vecX,
                cusparseDnVecDescr_t      vecY);

CUSPARSE_DEPRECATED
cusparseStatus_t CUSPARSEAPI
cusparseRot(cusparseHandle_t     handle,
            const void*          c_coeff,
            const void*          s_coeff,
            cusparseSpVecDescr_t vecX,
            cusparseDnVecDescr_t vecY);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseSpVV_bufferSize(cusparseHandle_t          handle,
                        cusparseOperation_t       opX,
                        cusparseConstSpVecDescr_t vecX,
                        cusparseConstDnVecDescr_t vecY,
                        const void*               result,
                        cudaDataType              computeType,
                        size_t*                   bufferSize);

CUSPARSE_DEPRECATED // deprecated in CTK 12.8
cusparseStatus_t CUSPARSEAPI
cusparseSpVV(cusparseHandle_t          handle,
             cusparseOperation_t       opX,
             cusparseConstSpVecDescr_t vecX,
             cusparseConstDnVecDescr_t vecY,
             void*                     result,
             cudaDataType              computeType,
             void*                     externalBuffer);

// #############################################################################
// # SPARSE TO DENSE
// #############################################################################

typedef enum {
    CUSPARSE_SPARSETODENSE_ALG_DEFAULT = 0
} cusparseSparseToDenseAlg_t;

cusparseStatus_t CUSPARSEAPI
cusparseSparseToDense_bufferSize(cusparseHandle_t           handle,
                                 cusparseConstSpMatDescr_t  matA,
                                 cusparseDnMatDescr_t       matB,
                                 cusparseSparseToDenseAlg_t alg,
                                 size_t*                    bufferSize);

cusparseStatus_t CUSPARSEAPI
cusparseSparseToDense(cusparseHandle_t           handle,
                      cusparseConstSpMatDescr_t  matA,
                      cusparseDnMatDescr_t       matB,
                      cusparseSparseToDenseAlg_t alg,
                      void*                      externalBuffer);

// #############################################################################
// # DENSE TO SPARSE
// #############################################################################

typedef enum {
    CUSPARSE_DENSETOSPARSE_ALG_DEFAULT = 0
} cusparseDenseToSparseAlg_t;

cusparseStatus_t CUSPARSEAPI
cusparseDenseToSparse_bufferSize(cusparseHandle_t           handle,
                                 cusparseConstDnMatDescr_t  matA,
                                 cusparseSpMatDescr_t       matB,
                                 cusparseDenseToSparseAlg_t alg,
                                 size_t*                    bufferSize);

cusparseStatus_t CUSPARSEAPI
cusparseDenseToSparse_analysis(cusparseHandle_t           handle,
                               cusparseConstDnMatDescr_t  matA,
                               cusparseSpMatDescr_t       matB,
                               cusparseDenseToSparseAlg_t alg,
                               void*                      externalBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseDenseToSparse_convert(cusparseHandle_t           handle,
                              cusparseConstDnMatDescr_t  matA,
                              cusparseSpMatDescr_t       matB,
                              cusparseDenseToSparseAlg_t alg,
                              void*                      externalBuffer);

// #############################################################################
// # SPARSE MATRIX-VECTOR MULTIPLICATION
// #############################################################################

typedef enum {
    CUSPARSE_SPMV_ALG_DEFAULT = 0,
    CUSPARSE_SPMV_CSR_ALG1    = 2,
    CUSPARSE_SPMV_CSR_ALG2    = 3,
    CUSPARSE_SPMV_COO_ALG1    = 1,
    CUSPARSE_SPMV_COO_ALG2    = 4,
    CUSPARSE_SPMV_SELL_ALG1   = 5
} cusparseSpMVAlg_t;

cusparseStatus_t CUSPARSEAPI
cusparseSpMV(cusparseHandle_t          handle,
             cusparseOperation_t       opA,
             const void*               alpha,
             cusparseConstSpMatDescr_t matA,
             cusparseConstDnVecDescr_t vecX,
             const void*               beta,
             cusparseDnVecDescr_t      vecY,
             cudaDataType              computeType,
             cusparseSpMVAlg_t         alg,
             void*                     externalBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseSpMV_bufferSize(cusparseHandle_t          handle,
                        cusparseOperation_t       opA,
                        const void*               alpha,
                        cusparseConstSpMatDescr_t matA,
                        cusparseConstDnVecDescr_t vecX,
                        const void*               beta,
                        cusparseDnVecDescr_t      vecY,
                        cudaDataType              computeType,
                        cusparseSpMVAlg_t         alg,
                        size_t*                   bufferSize);

cusparseStatus_t CUSPARSEAPI
cusparseSpMV_preprocess(cusparseHandle_t          handle,
                        cusparseOperation_t       opA,
                        const void*               alpha,
                        cusparseConstSpMatDescr_t matA,
                        cusparseConstDnVecDescr_t vecX,
                        const void*               beta,
                        cusparseDnVecDescr_t      vecY,
                        cudaDataType              computeType,
                        cusparseSpMVAlg_t         alg,
                        void*                     externalBuffer);
// #############################################################################
// # SPARSE TRIANGULAR VECTOR SOLVE
// #############################################################################

typedef enum {
    CUSPARSE_SPSV_ALG_DEFAULT = 0,
} cusparseSpSVAlg_t;

typedef enum {
    CUSPARSE_SPSV_UPDATE_GENERAL  = 0,
    CUSPARSE_SPSV_UPDATE_DIAGONAL = 1
} cusparseSpSVUpdate_t;

struct cusparseSpSVDescr;
typedef struct cusparseSpSVDescr* cusparseSpSVDescr_t;

cusparseStatus_t CUSPARSEAPI
cusparseSpSV_createDescr(cusparseSpSVDescr_t* descr);

cusparseStatus_t CUSPARSEAPI
cusparseSpSV_destroyDescr(cusparseSpSVDescr_t descr);

cusparseStatus_t CUSPARSEAPI
cusparseSpSV_bufferSize(cusparseHandle_t          handle,
                        cusparseOperation_t       opA,
                        const void*               alpha,
                        cusparseConstSpMatDescr_t matA,
                        cusparseConstDnVecDescr_t vecX,
                        cusparseDnVecDescr_t      vecY,
                        cudaDataType              computeType,
                        cusparseSpSVAlg_t         alg,
                        cusparseSpSVDescr_t       spsvDescr,
                        size_t*                   bufferSize);

cusparseStatus_t CUSPARSEAPI
cusparseSpSV_analysis(cusparseHandle_t          handle,
                      cusparseOperation_t       opA,
                      const void*               alpha,
                      cusparseConstSpMatDescr_t matA,
                      cusparseConstDnVecDescr_t vecX,
                      cusparseDnVecDescr_t      vecY,
                      cudaDataType              computeType,
                      cusparseSpSVAlg_t         alg,
                      cusparseSpSVDescr_t       spsvDescr,
                      void*                     externalBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseSpSV_solve(cusparseHandle_t          handle,
                   cusparseOperation_t       opA,
                   const void*               alpha,
                   cusparseConstSpMatDescr_t matA,
                   cusparseConstDnVecDescr_t vecX,
                   cusparseDnVecDescr_t      vecY,
                   cudaDataType              computeType,
                   cusparseSpSVAlg_t         alg,
                   cusparseSpSVDescr_t       spsvDescr);

cusparseStatus_t CUSPARSEAPI
cusparseSpSV_updateMatrix(cusparseHandle_t      handle,
				          cusparseSpSVDescr_t   spsvDescr,
                          void*                 newValues,
                          cusparseSpSVUpdate_t  updatePart);



// #############################################################################
// # SPARSE TRIANGULAR MATRIX SOLVE
// #############################################################################

typedef enum {
    CUSPARSE_SPSM_ALG_DEFAULT = 0,
} cusparseSpSMAlg_t;

typedef enum {
    CUSPARSE_SPSM_UPDATE_GENERAL  = 0,
    CUSPARSE_SPSM_UPDATE_DIAGONAL = 1
} cusparseSpSMUpdate_t;

struct cusparseSpSMDescr;
typedef struct cusparseSpSMDescr* cusparseSpSMDescr_t;

cusparseStatus_t CUSPARSEAPI
cusparseSpSM_createDescr(cusparseSpSMDescr_t* descr);

cusparseStatus_t CUSPARSEAPI
cusparseSpSM_destroyDescr(cusparseSpSMDescr_t descr);

cusparseStatus_t CUSPARSEAPI
cusparseSpSM_bufferSize(cusparseHandle_t          handle,
                        cusparseOperation_t       opA,
                        cusparseOperation_t       opB,
                        const void*               alpha,
                        cusparseConstSpMatDescr_t matA,
                        cusparseConstDnMatDescr_t matB,
                        cusparseDnMatDescr_t      matC,
                        cudaDataType              computeType,
                        cusparseSpSMAlg_t         alg,
                        cusparseSpSMDescr_t       spsmDescr,
                        size_t*                   bufferSize);

cusparseStatus_t CUSPARSEAPI
cusparseSpSM_analysis(cusparseHandle_t          handle,
                      cusparseOperation_t       opA,
                      cusparseOperation_t       opB,
                      const void*               alpha,
                      cusparseConstSpMatDescr_t matA,
                      cusparseConstDnMatDescr_t matB,
                      cusparseDnMatDescr_t      matC,
                      cudaDataType              computeType,
                      cusparseSpSMAlg_t         alg,
                      cusparseSpSMDescr_t       spsmDescr,
                      void*                     externalBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseSpSM_solve(cusparseHandle_t          handle,
                   cusparseOperation_t       opA,
                   cusparseOperation_t       opB,
                   const void*               alpha,
                   cusparseConstSpMatDescr_t matA,
                   cusparseConstDnMatDescr_t matB,
                   cusparseDnMatDescr_t      matC,
                   cudaDataType              computeType,
                   cusparseSpSMAlg_t         alg,
                   cusparseSpSMDescr_t       spsmDescr);

cusparseStatus_t CUSPARSEAPI
cusparseSpSM_updateMatrix(cusparseHandle_t      handle,
				          cusparseSpSMDescr_t   spsmDescr,
                          void*                 newValues,
                          cusparseSpSMUpdate_t  updatePart);

// #############################################################################
// # SPARSE MATRIX-MATRIX MULTIPLICATION
// #############################################################################

typedef enum {
    CUSPARSE_SPMM_ALG_DEFAULT      = 0,
    CUSPARSE_SPMM_COO_ALG1         = 1,
    CUSPARSE_SPMM_COO_ALG2         = 2,
    CUSPARSE_SPMM_COO_ALG3         = 3,
    CUSPARSE_SPMM_COO_ALG4         = 5,
    CUSPARSE_SPMM_CSR_ALG1         = 4,
    CUSPARSE_SPMM_CSR_ALG2         = 6,
    CUSPARSE_SPMM_CSR_ALG3         = 12,
    CUSPARSE_SPMM_BLOCKED_ELL_ALG1 = 13,
    CUSPARSE_SPMM_BSR_ALG1         = 14
} cusparseSpMMAlg_t;

cusparseStatus_t CUSPARSEAPI
cusparseSpMM_bufferSize(cusparseHandle_t          handle,
                        cusparseOperation_t       opA,
                        cusparseOperation_t       opB,
                        const void*               alpha,
                        cusparseConstSpMatDescr_t matA,
                        cusparseConstDnMatDescr_t matB,
                        const void*               beta,
                        cusparseDnMatDescr_t      matC,
                        cudaDataType              computeType,
                        cusparseSpMMAlg_t         alg,
                        size_t*                   bufferSize);

cusparseStatus_t CUSPARSEAPI
cusparseSpMM_preprocess(cusparseHandle_t          handle,
                        cusparseOperation_t       opA,
                        cusparseOperation_t       opB,
                        const void*               alpha,
                        cusparseConstSpMatDescr_t matA,
                        cusparseConstDnMatDescr_t matB,
                        const void*               beta,
                        cusparseDnMatDescr_t      matC,
                        cudaDataType              computeType,
                        cusparseSpMMAlg_t         alg,
                        void*                     externalBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseSpMM(cusparseHandle_t          handle,
             cusparseOperation_t       opA,
             cusparseOperation_t       opB,
             const void*               alpha,
             cusparseConstSpMatDescr_t matA,
             cusparseConstDnMatDescr_t matB,
             const void*               beta,
             cusparseDnMatDescr_t      matC,
             cudaDataType              computeType,
             cusparseSpMMAlg_t         alg,
             void*                     externalBuffer);

// #############################################################################
// # SPARSE MATRIX - SPARSE MATRIX MULTIPLICATION (SpGEMM)
// #############################################################################

typedef enum {
    CUSPARSE_SPGEMM_DEFAULT                 = 0,
    CUSPARSE_SPGEMM_CSR_ALG_DETERMINITIC    = 1,
    CUSPARSE_SPGEMM_CSR_ALG_NONDETERMINITIC = 2,
    CUSPARSE_SPGEMM_ALG1                    = 3,
    CUSPARSE_SPGEMM_ALG2                    = 4,
    CUSPARSE_SPGEMM_ALG3                    = 5
} cusparseSpGEMMAlg_t;

struct cusparseSpGEMMDescr;
typedef struct cusparseSpGEMMDescr* cusparseSpGEMMDescr_t;

cusparseStatus_t CUSPARSEAPI
cusparseSpGEMM_createDescr(cusparseSpGEMMDescr_t* descr);

cusparseStatus_t CUSPARSEAPI
cusparseSpGEMM_destroyDescr(cusparseSpGEMMDescr_t descr);

cusparseStatus_t CUSPARSEAPI
cusparseSpGEMM_workEstimation(cusparseHandle_t          handle,
                              cusparseOperation_t       opA,
                              cusparseOperation_t       opB,
                              const void*               alpha,
                              cusparseConstSpMatDescr_t matA,
                              cusparseConstSpMatDescr_t matB,
                              const void*               beta,
                              cusparseSpMatDescr_t      matC,
                              cudaDataType              computeType,
                              cusparseSpGEMMAlg_t       alg,
                              cusparseSpGEMMDescr_t     spgemmDescr,
                              size_t*                   bufferSize1,
                              void*                     externalBuffer1);

cusparseStatus_t CUSPARSEAPI
cusparseSpGEMM_getNumProducts(cusparseSpGEMMDescr_t spgemmDescr,
                              int64_t*              num_prods);

cusparseStatus_t CUSPARSEAPI
cusparseSpGEMM_estimateMemory(cusparseHandle_t          handle,
                              cusparseOperation_t       opA,
                              cusparseOperation_t       opB,
                              const void*               alpha,
                              cusparseConstSpMatDescr_t matA,
                              cusparseConstSpMatDescr_t matB,
                              const void*               beta,
                              cusparseSpMatDescr_t      matC,
                              cudaDataType              computeType,
                              cusparseSpGEMMAlg_t       alg,
                              cusparseSpGEMMDescr_t     spgemmDescr,
                              float                     chunk_fraction,
                              size_t*                   bufferSize3,
                              void*                     externalBuffer3,
                              size_t*                   bufferSize2);

cusparseStatus_t CUSPARSEAPI
cusparseSpGEMM_compute(cusparseHandle_t          handle,
                       cusparseOperation_t       opA,
                       cusparseOperation_t       opB,
                       const void*               alpha,
                       cusparseConstSpMatDescr_t matA,
                       cusparseConstSpMatDescr_t matB,
                       const void*               beta,
                       cusparseSpMatDescr_t      matC,
                       cudaDataType              computeType,
                       cusparseSpGEMMAlg_t       alg,
                       cusparseSpGEMMDescr_t     spgemmDescr,
                       size_t*                   bufferSize2,
                       void*                     externalBuffer2);

cusparseStatus_t CUSPARSEAPI
cusparseSpGEMM_copy(cusparseHandle_t          handle,
                    cusparseOperation_t       opA,
                    cusparseOperation_t       opB,
                    const void*               alpha,
                    cusparseConstSpMatDescr_t matA,
                    cusparseConstSpMatDescr_t matB,
                    const void*               beta,
                    cusparseSpMatDescr_t      matC,
                    cudaDataType              computeType,
                    cusparseSpGEMMAlg_t       alg,
                    cusparseSpGEMMDescr_t     spgemmDescr);

// #############################################################################
// # SPARSE MATRIX - SPARSE MATRIX MULTIPLICATION (SpGEMM) STRUCTURE REUSE
// #############################################################################

cusparseStatus_t CUSPARSEAPI
cusparseSpGEMMreuse_workEstimation(cusparseHandle_t          handle,
                                   cusparseOperation_t       opA,
                                   cusparseOperation_t       opB,
                                   cusparseConstSpMatDescr_t matA,
                                   cusparseConstSpMatDescr_t matB,
                                   cusparseSpMatDescr_t      matC,
                                   cusparseSpGEMMAlg_t       alg,
                                   cusparseSpGEMMDescr_t     spgemmDescr,
                                   size_t*                   bufferSize1,
                                   void*                     externalBuffer1);

cusparseStatus_t CUSPARSEAPI
cusparseSpGEMMreuse_nnz(cusparseHandle_t          handle,
                        cusparseOperation_t       opA,
                        cusparseOperation_t       opB,
                        cusparseConstSpMatDescr_t matA,
                        cusparseConstSpMatDescr_t matB,
                        cusparseSpMatDescr_t      matC,
                        cusparseSpGEMMAlg_t       alg,
                        cusparseSpGEMMDescr_t     spgemmDescr,
                        size_t*                   bufferSize2,
                        void*                     externalBuffer2,
                        size_t*                   bufferSize3,
                        void*                     externalBuffer3,
                        size_t*                   bufferSize4,
                        void*                     externalBuffer4);

cusparseStatus_t CUSPARSEAPI
cusparseSpGEMMreuse_copy(cusparseHandle_t          handle,
                         cusparseOperation_t       opA,
                         cusparseOperation_t       opB,
                         cusparseConstSpMatDescr_t matA,
                         cusparseConstSpMatDescr_t matB,
                         cusparseSpMatDescr_t      matC,
                         cusparseSpGEMMAlg_t       alg,
                         cusparseSpGEMMDescr_t     spgemmDescr,
                         size_t*                   bufferSize5,
                         void*                     externalBuffer5);

cusparseStatus_t CUSPARSEAPI
cusparseSpGEMMreuse_compute(cusparseHandle_t          handle,
                            cusparseOperation_t       opA,
                            cusparseOperation_t       opB,
                            const void*               alpha,
                            cusparseConstSpMatDescr_t matA,
                            cusparseConstSpMatDescr_t matB,
                            const void*               beta,
                            cusparseSpMatDescr_t      matC,
                            cudaDataType              computeType,
                            cusparseSpGEMMAlg_t       alg,
                            cusparseSpGEMMDescr_t     spgemmDescr);

// #############################################################################
// # SAMPLED DENSE-DENSE MATRIX MULTIPLICATION
// #############################################################################

typedef enum {
    CUSPARSE_SDDMM_ALG_DEFAULT = 0
} cusparseSDDMMAlg_t;

cusparseStatus_t CUSPARSEAPI
cusparseSDDMM_bufferSize(cusparseHandle_t          handle,
                         cusparseOperation_t       opA,
                         cusparseOperation_t       opB,
                         const void*               alpha,
                         cusparseConstDnMatDescr_t matA,
                         cusparseConstDnMatDescr_t matB,
                         const void*               beta,
                         cusparseSpMatDescr_t      matC,
                         cudaDataType              computeType,
                         cusparseSDDMMAlg_t        alg,
                         size_t*                   bufferSize);

cusparseStatus_t CUSPARSEAPI
cusparseSDDMM_preprocess(cusparseHandle_t          handle,
                         cusparseOperation_t       opA,
                         cusparseOperation_t       opB,
                         const void*               alpha,
                         cusparseConstDnMatDescr_t matA,
                         cusparseConstDnMatDescr_t matB,
                         const void*               beta,
                         cusparseSpMatDescr_t      matC,
                         cudaDataType              computeType,
                         cusparseSDDMMAlg_t        alg,
                         void*                     externalBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseSDDMM(cusparseHandle_t          handle,
              cusparseOperation_t       opA,
              cusparseOperation_t       opB,
              const void*               alpha,
              cusparseConstDnMatDescr_t matA,
              cusparseConstDnMatDescr_t matB,
              const void*               beta,
              cusparseSpMatDescr_t      matC,
              cudaDataType              computeType,
              cusparseSDDMMAlg_t        alg,
              void*                     externalBuffer);

// #############################################################################
// # GENERIC APIs WITH CUSTOM OPERATORS (PREVIEW)
// #############################################################################

struct cusparseSpMMOpPlan;
typedef struct cusparseSpMMOpPlan*       cusparseSpMMOpPlan_t;

typedef enum {
    CUSPARSE_SPMM_OP_ALG_DEFAULT
} cusparseSpMMOpAlg_t;

cusparseStatus_t CUSPARSEAPI
cusparseSpMMOp_createPlan(cusparseHandle_t          handle,
                          cusparseSpMMOpPlan_t*     plan,
                          cusparseOperation_t       opA,
                          cusparseOperation_t       opB,
                          cusparseConstSpMatDescr_t matA,
                          cusparseConstDnMatDescr_t matB,
                          cusparseDnMatDescr_t      matC,
                          cudaDataType              computeType,
                          cusparseSpMMOpAlg_t       alg,
                          const void*               addOperationNvvmBuffer,
                          size_t                    addOperationBufferSize,
                          const void*               mulOperationNvvmBuffer,
                          size_t                    mulOperationBufferSize,
                          const void*               epilogueNvvmBuffer,
                          size_t                    epilogueBufferSize,
                          size_t*                   SpMMWorkspaceSize);

cusparseStatus_t CUSPARSEAPI
cusparseSpMMOp(cusparseSpMMOpPlan_t plan,
               void*                externalBuffer);

cusparseStatus_t CUSPARSEAPI
cusparseSpMMOp_destroyPlan(cusparseSpMMOpPlan_t plan);

//------------------------------------------------------------------------------

#if defined(__cplusplus)
} // extern "C"
#endif // defined(__cplusplus)

#undef CUSPARSE_DEPRECATED_REPLACE_WITH
#undef CUSPARSE_DEPRECATED
#undef CUSPARSE_DEPRECATED_TYPE
#undef CUSPARSE_DEPRECATED_TYPE_MSVC
#undef CUSPARSE_DEPRECATED_ENUM_REPLACE_WITH
#undef CUSPARSE_DEPRECATED_ENUM

#endif // !defined(CUSPARSE_H_)
