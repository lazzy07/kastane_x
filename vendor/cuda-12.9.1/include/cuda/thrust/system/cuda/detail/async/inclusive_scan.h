/******************************************************************************
 * Copyright (c) 2020, NVIDIA CORPORATION.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the NVIDIA CORPORATION nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NVIDIA CORPORATION BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#pragma once

#include <thrust/detail/config.h>

#if defined(_CCCL_IMPLICIT_SYSTEM_HEADER_GCC)
#  pragma GCC system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_CLANG)
#  pragma clang system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_MSVC)
#  pragma system_header
#endif // no system header
#include <thrust/detail/cpp14_required.h>

#if _CCCL_STD_VER >= 2014

#  if _CCCL_HAS_CUDA_COMPILER

#    include <thrust/system/cuda/config.h>

#    include <thrust/distance.h>
#    include <thrust/iterator/iterator_traits.h>
#    include <thrust/system/cuda/detail/async/customization.h>
#    include <thrust/system/cuda/detail/util.h>
#    include <thrust/system/cuda/future.h>

#    include <cuda/std/type_traits>

#    include <type_traits>

// TODO specialize for thrust::plus to use e.g. InclusiveSum instead of IncScan

_CCCL_SUPPRESS_DEPRECATED_PUSH
THRUST_NAMESPACE_BEGIN
namespace system
{
namespace cuda
{
namespace detail
{

template <typename DerivedPolicy, typename ForwardIt, typename Size, typename OutputIt, typename BinaryOp>
unique_eager_event
async_inclusive_scan_n(execution_policy<DerivedPolicy>& policy, ForwardIt first, Size n, OutputIt out, BinaryOp op)
{
  using AccumT     = typename thrust::iterator_traits<ForwardIt>::value_type;
  using Dispatch32 = cub::DispatchScan<ForwardIt, OutputIt, BinaryOp, cub::NullType, std::int32_t, AccumT>;
  using Dispatch64 = cub::DispatchScan<ForwardIt, OutputIt, BinaryOp, cub::NullType, std::int64_t, AccumT>;

  auto const device_alloc = get_async_device_allocator(policy);
  unique_eager_event ev;

  // Determine temporary device storage requirements.
  cudaError_t status;
  size_t tmp_size = 0;
  {
    THRUST_INDEX_TYPE_DISPATCH2(
      status,
      Dispatch32::Dispatch,
      Dispatch64::Dispatch,
      n,
      (nullptr, tmp_size, first, out, op, cub::NullType{}, n_fixed, nullptr));
    thrust::cuda_cub::throw_on_error(
      status,
      "after determining tmp storage "
      "requirements for inclusive_scan");
  }

  // Allocate temporary storage.
  auto content        = uninitialized_allocate_unique_n<std::uint8_t>(device_alloc, tmp_size);
  void* const tmp_ptr = raw_pointer_cast(content.get());

  // Set up stream with dependencies.
  cudaStream_t const user_raw_stream = thrust::cuda_cub::stream(policy);

  if (thrust::cuda_cub::default_stream() != user_raw_stream)
  {
    ev = make_dependent_event(
      std::tuple_cat(std::make_tuple(std::move(content), unique_stream(nonowning, user_raw_stream)),
                     extract_dependencies(std::move(thrust::detail::derived_cast(policy)))));
  }
  else
  {
    ev = make_dependent_event(std::tuple_cat(
      std::make_tuple(std::move(content)), extract_dependencies(std::move(thrust::detail::derived_cast(policy)))));
  }

  // Run scan.
  {
    THRUST_INDEX_TYPE_DISPATCH2(
      status,
      Dispatch32::Dispatch,
      Dispatch64::Dispatch,
      n,
      (tmp_ptr, tmp_size, first, out, op, cub::NullType{}, n_fixed, user_raw_stream));
    thrust::cuda_cub::throw_on_error(status, "after dispatching inclusive_scan kernel");
  }

  return ev;
}

template <typename DerivedPolicy,
          typename ForwardIt,
          typename Size,
          typename OutputIt,
          typename InitialValueType,
          typename BinaryOp>
unique_eager_event async_inclusive_scan_n(
  execution_policy<DerivedPolicy>& policy, ForwardIt first, Size n, OutputIt out, InitialValueType init, BinaryOp op)
{
  using InputValueT = cub::detail::InputValue<InitialValueType>;
  using AccumT      = typename ::cuda::std::
    __accumulator_t<BinaryOp, typename ::cuda::std::iterator_traits<ForwardIt>::value_type, InitialValueType>;
  constexpr bool ForceInclusive = true;

  using Dispatch32 = cub::DispatchScan<
    ForwardIt,
    OutputIt,
    BinaryOp,
    InputValueT,
    std::int32_t,
    AccumT,
    cub::detail::scan::
      policy_hub<cub::detail::value_t<ForwardIt>, cub::detail::value_t<OutputIt>, AccumT, std::int32_t, BinaryOp>,
    ForceInclusive>;
  using Dispatch64 = cub::DispatchScan<
    ForwardIt,
    OutputIt,
    BinaryOp,
    InputValueT,
    std::int64_t,
    AccumT,
    cub::detail::scan::
      policy_hub<cub::detail::value_t<ForwardIt>, cub::detail::value_t<OutputIt>, AccumT, std::int64_t, BinaryOp>,
    ForceInclusive>;

  InputValueT init_value(init);

  auto const device_alloc = get_async_device_allocator(policy);
  unique_eager_event ev;

  // Determine temporary device storage requirements.
  cudaError_t status;
  size_t tmp_size = 0;
  {
    THRUST_INDEX_TYPE_DISPATCH2(
      status,
      Dispatch32::Dispatch,
      Dispatch64::Dispatch,
      n,
      (nullptr, tmp_size, first, out, op, init_value, n_fixed, nullptr));
    thrust::cuda_cub::throw_on_error(
      status,
      "after determining tmp storage "
      "requirements for inclusive_scan");
  }

  // Allocate temporary storage.
  auto content        = uninitialized_allocate_unique_n<std::uint8_t>(device_alloc, tmp_size);
  void* const tmp_ptr = raw_pointer_cast(content.get());

  // Set up stream with dependencies.
  cudaStream_t const user_raw_stream = thrust::cuda_cub::stream(policy);

  if (thrust::cuda_cub::default_stream() != user_raw_stream)
  {
    ev = make_dependent_event(
      std::tuple_cat(std::make_tuple(std::move(content), unique_stream(nonowning, user_raw_stream)),
                     extract_dependencies(std::move(thrust::detail::derived_cast(policy)))));
  }
  else
  {
    ev = make_dependent_event(std::tuple_cat(
      std::make_tuple(std::move(content)), extract_dependencies(std::move(thrust::detail::derived_cast(policy)))));
  }

  // Run scan.
  {
    THRUST_INDEX_TYPE_DISPATCH2(
      status,
      Dispatch32::Dispatch,
      Dispatch64::Dispatch,
      n,
      (tmp_ptr, tmp_size, first, out, op, init_value, n_fixed, user_raw_stream));
    thrust::cuda_cub::throw_on_error(status, "after dispatching inclusive_scan kernel");
  }

  return ev;
}

} // namespace detail
} // namespace cuda
} // namespace system

namespace cuda_cub
{

// ADL entry point.
template <typename DerivedPolicy, typename ForwardIt, typename Sentinel, typename OutputIt, typename BinaryOp>
auto async_inclusive_scan(
  execution_policy<DerivedPolicy>& policy, ForwardIt first, Sentinel&& last, OutputIt&& out, BinaryOp&& op)
  THRUST_RETURNS(thrust::system::cuda::detail::async_inclusive_scan_n(
    policy, first, thrust::distance(first, THRUST_FWD(last)), THRUST_FWD(out), THRUST_FWD(op)))

  // ADL entry point.
  template <typename DerivedPolicy,
            typename ForwardIt,
            typename Sentinel,
            typename OutputIt,
            typename InitialValueType,
            typename BinaryOp>
  auto async_inclusive_scan(
    execution_policy<DerivedPolicy>& policy,
    ForwardIt first,
    Sentinel&& last,
    OutputIt&& out,
    InitialValueType&& init,
    BinaryOp&& op)
    THRUST_RETURNS(thrust::system::cuda::detail::async_inclusive_scan_n(
      policy, first, thrust::distance(first, THRUST_FWD(last)), THRUST_FWD(out), THRUST_FWD(init), THRUST_FWD(op)))

} // namespace cuda_cub

_CCCL_SUPPRESS_DEPRECATED_POP
THRUST_NAMESPACE_END

#  endif // _CCCL_CUDA_COMPILER

#endif // C++14
