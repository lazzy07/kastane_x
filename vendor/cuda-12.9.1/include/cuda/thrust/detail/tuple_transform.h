/*
 *  Copyright 2008-2013 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#pragma once

#include <thrust/detail/config.h>

#if defined(_CCCL_IMPLICIT_SYSTEM_HEADER_GCC)
#  pragma GCC system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_CLANG)
#  pragma clang system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_MSVC)
#  pragma system_header
#endif // no system header

#include <thrust/detail/tuple_meta_transform.h>
#include <thrust/tuple.h>

THRUST_NAMESPACE_BEGIN

namespace detail
{

template <typename Tuple,
          template <typename>
          class UnaryMetaFunction,
          typename UnaryFunction,
          typename IndexSequence = thrust::make_index_sequence<thrust::tuple_size<Tuple>::value>>
struct tuple_transform_functor;

template <typename Tuple, template <typename> class UnaryMetaFunction, typename UnaryFunction, size_t... Is>
struct tuple_transform_functor<Tuple, UnaryMetaFunction, UnaryFunction, thrust::index_sequence<Is...>>
{
  static _CCCL_HOST_DEVICE typename tuple_meta_transform<Tuple, UnaryMetaFunction>::type
  do_it_on_the_host_or_device(const Tuple& t, UnaryFunction f)
  {
    using XfrmTuple = typename tuple_meta_transform<Tuple, UnaryMetaFunction>::type;

    return XfrmTuple(f(thrust::get<Is>(t))...);
  }
};

template <template <typename> class UnaryMetaFunction, typename Tuple, typename UnaryFunction>
typename tuple_meta_transform<Tuple, UnaryMetaFunction>::type _CCCL_HOST_DEVICE
tuple_host_device_transform(const Tuple& t, UnaryFunction f)
{
  return tuple_transform_functor<Tuple, UnaryMetaFunction, UnaryFunction>::do_it_on_the_host_or_device(t, f);
}

} // namespace detail

THRUST_NAMESPACE_END
