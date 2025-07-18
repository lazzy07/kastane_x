/******************************************************************************
 * Copyright (c) 2016, NVIDIA CORPORATION.  All rights reserved.
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
#include <thrust/system/cuda/config.h>

#include <cub/block/block_load.cuh>
#include <cub/block/block_scan.cuh>
#include <cub/block/block_store.cuh>
#include <cub/util_temporary_storage.cuh>

#include <thrust/detail/raw_pointer_cast.h>
#include <thrust/system/cuda/detail/util.h>
#include <thrust/system/system_error.h>
#include <thrust/type_traits/is_contiguous_iterator.h>

#include <cuda/std/__type_traits/void_t.h>

#include <nv/target>

THRUST_NAMESPACE_BEGIN

namespace cuda_cub
{
namespace core
{

#ifdef _NVHPC_CUDA
#  if (__NVCOMPILER_CUDA_ARCH__ >= 600)
// deprecated [since 2.8]
#    define THRUST_TUNING_ARCH sm60
#  elif (__NVCOMPILER_CUDA_ARCH__ >= 520)
// deprecated [since 2.8]
#    define THRUST_TUNING_ARCH sm52
#  elif (__NVCOMPILER_CUDA_ARCH__ >= 350)
// deprecated [since 2.8]
#    define THRUST_TUNING_ARCH sm35
#  else
// deprecated [since 2.8]
#    define THRUST_TUNING_ARCH sm30
#  endif
#else
#  if (__CUDA_ARCH__ >= 600)
// deprecated [since 2.8]
#    define THRUST_TUNING_ARCH sm60
#  elif (__CUDA_ARCH__ >= 520)
// deprecated [since 2.8]
#    define THRUST_TUNING_ARCH sm52
#  elif (__CUDA_ARCH__ >= 350)
// deprecated [since 2.8]
#    define THRUST_TUNING_ARCH sm35
#  elif (__CUDA_ARCH__ >= 300)
// deprecated [since 2.8]
#    define THRUST_TUNING_ARCH sm30
#  elif !defined(__CUDA_ARCH__)
// deprecated [since 2.8]
#    define THRUST_TUNING_ARCH sm30
#  endif
#endif

/// Typelist - a container of types
template <typename...>
struct typelist;

// -------------------------------------

// supported SM arch
// ---------------------
struct sm30
{
  enum
  {
    ver      = 300,
    warpSize = 32
  };
};
struct sm35
{
  enum
  {
    ver      = 350,
    warpSize = 32
  };
};
struct sm52
{
  enum
  {
    ver      = 520,
    warpSize = 32
  };
};
struct sm60
{
  enum
  {
    ver      = 600,
    warpSize = 32
  };
};

// list of sm, checked from left to right order
// the rightmost is the lowest sm arch supported
// --------------------------------------------
using sm_list = typelist<sm60, sm52, sm35, sm30>;

// lowest supported SM arch
// --------------------------------------------------------------------------

template <class, class>
struct lowest_supported_sm_arch_impl;

template <class SM, class Head, class... Tail>
struct lowest_supported_sm_arch_impl<SM, typelist<Head, Tail...>>
    : lowest_supported_sm_arch_impl<Head, typelist<Tail...>>
{};
template <class SM>
struct lowest_supported_sm_arch_impl<SM, typelist<>>
{
  using type = SM;
};

using lowest_supported_sm_arch = typename lowest_supported_sm_arch_impl<void, sm_list>::type;

// metafunction to match next viable PtxPlan specialization
// --------------------------------------------------------------------------

__THRUST_DEFINE_HAS_NESTED_TYPE(has_tuning_t, tuning)
__THRUST_DEFINE_HAS_NESTED_TYPE(has_type_t, type)

template <template <class> class, class, class>
struct specialize_plan_impl_loop;
template <template <class> class, class>
struct specialize_plan_impl_match;

// we loop through the sm_list
template <template <class> class P, class SM, class Head, class... Tail>
struct specialize_plan_impl_loop<P, SM, typelist<Head, Tail...>> : specialize_plan_impl_loop<P, SM, typelist<Tail...>>
{};

// until we find first lowest match
template <template <class> class P, class SM, class... Tail>
struct specialize_plan_impl_loop<P, SM, typelist<SM, Tail...>> : specialize_plan_impl_match<P, typelist<SM, Tail...>>
{};

template <class, class>
struct has_sm_tuning_impl;

// specializing for Tunig which needs 1 arg
template <class SM, template <class, class> class Tuning, class _0>
struct has_sm_tuning_impl<SM, Tuning<lowest_supported_sm_arch, _0>> : has_type_t<Tuning<SM, _0>>
{};

// specializing for Tunig which needs 2 args
template <class SM, template <class, class, class> class Tuning, class _0, class _1>
struct has_sm_tuning_impl<SM, Tuning<lowest_supported_sm_arch, _0, _1>> : has_type_t<Tuning<SM, _0, _1>>
{};

template <template <class> class P, class SM>
struct has_sm_tuning : has_sm_tuning_impl<SM, typename P<lowest_supported_sm_arch>::tuning>
{};

// once first match is found in sm_list, all remaining sm are possible
// candidate for tuning, so pick the first available
//   if the plan P has SM-level tuning then pick it,
//   otherwise move on to the next sm in the sm_list
template <template <class> class P, class SM, class... SMs>
struct specialize_plan_impl_match<P, typelist<SM, SMs...>>
    : ::cuda::std::conditional<has_sm_tuning<P, SM>::value, P<SM>, specialize_plan_impl_match<P, typelist<SMs...>>>::type
{};

template <template <class> class Plan, class SM = THRUST_TUNING_ARCH>
struct specialize_plan_msvc10_war
{
  // if Plan has tuning type, this means it has SM-specific tuning
  // so loop through sm_list to find match,
  // otherwise just specialize on provided SM
  using type = ::cuda::std::conditional<has_tuning_t<Plan<lowest_supported_sm_arch>>::value,
                                        specialize_plan_impl_loop<Plan, SM, sm_list>,
                                        Plan<SM>>;
};

template <template <class> class Plan, class SM = THRUST_TUNING_ARCH>
struct specialize_plan : specialize_plan_msvc10_war<Plan, SM>::type::type
{};

/////////////////////////
/////////////////////////
/////////////////////////

// retrieve temp storage size from an Agent
// ---------------------------------------------------------------------------
// metafunction introspects Agent, and if it finds TempStorage type
// it will return its size

template <class Agent, class = void>
struct temp_storage_size
{
  static constexpr std::size_t value = 0;
};

template <class Agent>
struct temp_storage_size<Agent, ::cuda::std::void_t<typename Agent::TempStorage>>
{
  static constexpr std::size_t value = sizeof(typename Agent::TempStorage);
};

// check whether all Agents requires < MAX_SHMEM shared memory
// ---------------------------------------------------------------------------
// if so, we can use simpler kernel for dispatch, which assumes that all
// shared memory is on chip.
// Otherwise, a kernel will be compiled which can also accept virtualized
// shared memory, in case there is not enough on chip. This kernel is about
// 10% slower

template <bool, class, size_t, class>
struct has_enough_shmem_impl;

template <bool V, class A, size_t S, class Head, class... Tail>
struct has_enough_shmem_impl<V, A, S, typelist<Head, Tail...>>
    : has_enough_shmem_impl<V && (temp_storage_size<specialize_plan<A::template PtxPlan, Head>>::value <= S),
                            A,
                            S,
                            typelist<Tail...>>
{};
template <bool V, class A, size_t S>
struct has_enough_shmem_impl<V, A, S, typelist<>>
{
  enum
  {
    value = V
  };
  using type = ::cuda::std::conditional_t<value, thrust::detail::true_type, thrust::detail::false_type>;
};

template <class Agent, size_t MAX_SHMEM>
struct has_enough_shmem : has_enough_shmem_impl<true, Agent, MAX_SHMEM, sm_list>
{};

/////////////////////////
/////////////////////////
/////////////////////////

// AgentPlan structure and helpers
// --------------------------------

struct AgentPlan
{
  int block_threads;
  int items_per_thread;
  int items_per_tile;
  int shared_memory_size;
  int grid_size;

  AgentPlan() = default;

  THRUST_RUNTIME_FUNCTION
  AgentPlan(int block_threads_, int items_per_thread_, int shared_memory_size_, int grid_size_ = 0)
      : block_threads(block_threads_)
      , items_per_thread(items_per_thread_)
      , items_per_tile(items_per_thread * block_threads)
      , shared_memory_size(shared_memory_size_)
      , grid_size(grid_size_)
  {}

  THRUST_RUNTIME_FUNCTION AgentPlan(AgentPlan const& plan)
      : block_threads(plan.block_threads)
      , items_per_thread(plan.items_per_thread)
      , items_per_tile(plan.items_per_tile)
      , shared_memory_size(plan.shared_memory_size)
      , grid_size(plan.grid_size)
  {}

  template <class PtxPlan>
  THRUST_RUNTIME_FUNCTION
  AgentPlan(PtxPlan, typename thrust::detail::disable_if_convertible<PtxPlan, AgentPlan>::type* = nullptr)
      : block_threads(PtxPlan::BLOCK_THREADS)
      , items_per_thread(PtxPlan::ITEMS_PER_THREAD)
      , items_per_tile(PtxPlan::ITEMS_PER_TILE)
      , shared_memory_size(temp_storage_size<PtxPlan>::value)
      , grid_size(0)
  {}
}; // struct AgentPlan

__THRUST_DEFINE_HAS_NESTED_TYPE(has_Plan, Plan)

template <class Agent>
struct return_Plan
{
  using type = typename Agent::Plan;
};

template <class Agent>
struct get_plan
    : ::cuda::std::conditional<has_Plan<Agent>::value, return_Plan<Agent>, thrust::detail::identity_<AgentPlan>>::type
{};

// returns AgentPlan corresponding to a given ptx version
// ------------------------------------------------------

template <class, class>
struct get_agent_plan_impl;

template <class Agent, class SM, class... Tail>
struct get_agent_plan_impl<Agent, typelist<SM, Tail...>>
{
  using Plan = typename get_plan<Agent>::type;
  Plan THRUST_RUNTIME_FUNCTION static get(int ptx_version)
  {
    if (ptx_version >= SM::ver)
    {
      return Plan(specialize_plan<Agent::template PtxPlan, SM>());
    }
    else
    {
      return get_agent_plan_impl<Agent, typelist<Tail...>>::get(ptx_version);
    }
  }
};

template <class Agent>
struct get_agent_plan_impl<Agent, typelist<lowest_supported_sm_arch>>
{
  using Plan = typename get_plan<Agent>::type;
  Plan THRUST_RUNTIME_FUNCTION static get(int /* ptx_version */)
  {
    using Plan = typename get_plan<Agent>::type;
    return Plan(specialize_plan<Agent::template PtxPlan, lowest_supported_sm_arch>());
  }
};

template <class Agent>
THRUST_RUNTIME_FUNCTION typename get_plan<Agent>::type get_agent_plan(int ptx_version)
{
  NV_IF_TARGET(NV_IS_DEVICE,
               (THRUST_UNUSED_VAR(ptx_version); using plan_type = typename get_plan<Agent>::type;
                using ptx_plan                                  = typename Agent::ptx_plan;
                return plan_type{ptx_plan{}};), // NV_IS_HOST:
               (return get_agent_plan_impl<Agent, sm_list>::get(ptx_version);));
}

// XXX keep this dead-code for now as a gentle reminder
//     that kernel launch which reats plan values is the most robust
//     mechanism to extract sm-specific tuning parameters
// TODO: since we are unable to afford kernel launch + cudaMemcpy ON EVERY
//       algorithm invocation, we need to design a good caching strategy
//       such that when the algorithm is called multiple times, only the
//       first invocation will invoke kernel launch + cudaMemcpy, but
//       the subsequent invocations, will just read cached values from host mem
//       If launched from device, this is just a device-function call
//       no caching is required.
// ----------------------------------------------------------------------------
// if we don't know ptx version, we can call kernel
// to retrieve AgentPlan from device code. Slower, but guaranteed to work
// -----------------------------------------------------------------------
#if 0
  template<class Agent>
  void __global__ get_agent_plan_kernel(AgentPlan *plan);

  static _CCCL_DEVICE AgentPlan agent_plan_device;

  template<class Agent>
  AgentPlan _CCCL_DEVICE get_agent_plan_dev()
  {
    AgentPlan plan;
    plan.block_threads      = Agent::ptx_plan::BLOCK_THREADS;
    plan.items_per_thread   = Agent::ptx_plan::ITEMS_PER_THREAD;
    plan.items_per_tile     = Agent::ptx_plan::ITEMS_PER_TILE;
    plan.shared_memory_size = temp_storage_size<typename Agent::ptx_plan>::value;
    return plan;
  }

  template <class Agent, class F>
  AgentPlan _CCCL_HOST_DEVICE _CCCL_FORCEINLINE
  xget_agent_plan_impl(F f, cudaStream_t s, void* d_ptr)
  {
    AgentPlan plan;
#  ifdef __CUDA_ARCH__
    plan = get_agent_plan_dev<Agent>();
#  else
    static cub::Mutex mutex;
    bool lock = false;
    if (d_ptr == 0)
    {
      lock = true;
      cudaGetSymbolAddress(&d_ptr, agent_plan_device);
    }
    if (lock)
      mutex.Lock();
    f<<<1,1,0,s>>>((AgentPlan*)d_ptr);
    cudaMemcpyAsync((void*)&plan,
                    d_ptr,
                    sizeof(AgentPlan),
                    cudaMemcpyDeviceToHost,
                    s);
    if (lock)
      mutex.Unlock();
    cudaStreamSynchronize(s);
#  endif
    return plan;
  }

  template <class Agent>
  AgentPlan THRUST_RUNTIME_FUNCTION
  get_agent_plan(cudaStream_t s = 0, void *ptr = 0)
  {
    return xget_agent_plan_impl<Agent>(get_agent_plan_kernel<Agent>,
                                        s,
                                        ptr);
  }

  template<class Agent>
  void __global__ get_agent_plan_kernel(AgentPlan *plan)
  {
    *plan = get_agent_plan_dev<Agent>();
  }
#endif

/////////////////////////
/////////////////////////
/////////////////////////

THRUST_RUNTIME_FUNCTION inline int get_sm_count()
{
  int dev_id;
  cuda_cub::throw_on_error(cudaGetDevice(&dev_id),
                           "get_sm_count :"
                           "failed to cudaGetDevice");

  cudaError_t status;
  int i32value;
  status = cudaDeviceGetAttribute(&i32value, cudaDevAttrMultiProcessorCount, dev_id);
  cuda_cub::throw_on_error(status,
                           "get_sm_count:"
                           "failed to sm_count");
  return i32value;
}

THRUST_RUNTIME_FUNCTION inline size_t get_max_shared_memory_per_block()
{
  int dev_id;
  cuda_cub::throw_on_error(cudaGetDevice(&dev_id),
                           "get_max_shared_memory_per_block :"
                           "failed to cudaGetDevice");

  cudaError_t status;
  int i32value;
  status = cudaDeviceGetAttribute(&i32value, cudaDevAttrMaxSharedMemoryPerBlock, dev_id);
  cuda_cub::throw_on_error(status,
                           "get_max_shared_memory_per_block :"
                           "failed to get max shared memory per block");

  return static_cast<size_t>(i32value);
}

THRUST_RUNTIME_FUNCTION inline size_t virtual_shmem_size(size_t shmem_per_block)
{
  size_t max_shmem_per_block = core::get_max_shared_memory_per_block();
  if (shmem_per_block > max_shmem_per_block)
  {
    return shmem_per_block;
  }
  else
  {
    return 0;
  }
}

THRUST_RUNTIME_FUNCTION inline size_t vshmem_size(size_t shmem_per_block, size_t num_blocks)
{
  size_t max_shmem_per_block = core::get_max_shared_memory_per_block();
  if (shmem_per_block > max_shmem_per_block)
  {
    return shmem_per_block * num_blocks;
  }
  else
  {
    return 0;
  }
}

// LoadIterator
// ------------
// if trivial iterator is passed, wrap loads into LDG
//
template <class PtxPlan, class It>
struct LoadIterator
{
  using value_type = typename iterator_traits<It>::value_type;
  using size_type  = typename iterator_traits<It>::difference_type;

  using type =
    ::cuda::std::conditional_t<is_contiguous_iterator<It>::value,
                               cub::CacheModifiedInputIterator<PtxPlan::LOAD_MODIFIER, value_type, size_type>,
                               It>;
}; // struct Iterator

template <class PtxPlan, class It>
typename LoadIterator<PtxPlan, It>::type _CCCL_DEVICE _CCCL_FORCEINLINE
make_load_iterator_impl(It it, thrust::detail::true_type /* is_trivial */)
{
  return raw_pointer_cast(&*it);
}

template <class PtxPlan, class It>
typename LoadIterator<PtxPlan, It>::type _CCCL_DEVICE _CCCL_FORCEINLINE
make_load_iterator_impl(It it, thrust::detail::false_type /* is_trivial */)
{
  return it;
}

template <class PtxPlan, class It>
typename LoadIterator<PtxPlan, It>::type _CCCL_DEVICE _CCCL_FORCEINLINE make_load_iterator(PtxPlan const&, It it)
{
  return make_load_iterator_impl<PtxPlan>(it, typename is_contiguous_iterator<It>::type());
}

template <class>
struct get_arch;

template <template <class> class Plan, class Arch>
struct get_arch<Plan<Arch>>
{
  using type = Arch;
};

// BlockLoad
// -----------
// a helper metaprogram that returns type of a block loader
template <class PtxPlan, class It, class T = typename iterator_traits<It>::value_type>
struct BlockLoad
{
  using type =
    cub::BlockLoad<T,
                   PtxPlan::BLOCK_THREADS,
                   PtxPlan::ITEMS_PER_THREAD,
                   PtxPlan::LOAD_ALGORITHM,
                   1,
                   1,
                   get_arch<PtxPlan>::type::ver>;
};

// BlockStore
// -----------
// a helper metaprogram that returns type of a block loader
template <class PtxPlan, class It, class T = typename iterator_traits<It>::value_type>
struct BlockStore
{
  using type =
    cub::BlockStore<T,
                    PtxPlan::BLOCK_THREADS,
                    PtxPlan::ITEMS_PER_THREAD,
                    PtxPlan::STORE_ALGORITHM,
                    1,
                    1,
                    get_arch<PtxPlan>::type::ver>;
};

// cuda_optional
// --------------
// used for function that return cudaError_t along with the result
//
// TODO(bgruber): this looks rather like an expected than an optional. Use ::cuda::std::expected in C++14.
template <class T>
class cuda_optional
{
  cudaError_t status_{cudaSuccess};
  T value_{};

public:
  cuda_optional() = default;

  _CCCL_HOST_DEVICE cuda_optional(T v, cudaError_t status = cudaSuccess)
      : status_(status)
      , value_(v)
  {}

  bool _CCCL_HOST_DEVICE isValid() const
  {
    return cudaSuccess == status_;
  }

  cudaError_t _CCCL_HOST_DEVICE status() const
  {
    return status_;
  }

  _CCCL_HOST_DEVICE T const& value() const
  {
    return value_;
  }

  _CCCL_HOST_DEVICE operator T const&() const
  {
    return value_;
  }
};

THRUST_RUNTIME_FUNCTION inline int get_ptx_version()
{
  int ptx_version = 0;
  if (cub::PtxVersion(ptx_version) != cudaSuccess)
  {
    // Failure might mean that there's no device found
    const int current_device = cub::CurrentDevice();
    if (current_device < 0)
    {
      cuda_cub::throw_on_error(cudaErrorNoDevice, "No GPU is available\n");
    }

    // Any subsequent failure means the provided device binary does not match
    // the generated function code
    int major = 0, minor = 0;
    cudaError_t attr_status;

    attr_status = cudaDeviceGetAttribute(&major, cudaDevAttrComputeCapabilityMajor, current_device);
    cuda_cub::throw_on_error(attr_status,
                             "get_ptx_version :"
                             "failed to get major CUDA device compute capability version.");

    attr_status = cudaDeviceGetAttribute(&minor, cudaDevAttrComputeCapabilityMinor, current_device);
    cuda_cub::throw_on_error(attr_status,
                             "get_ptx_version :"
                             "failed to get minor CUDA device compute capability version.");

    // Index from which SM code has to start in the message below
    int code_offset = 37;
    char str[]      = "This program was not compiled for SM     \n";

    auto print_1_helper = [&](int v) {
      str[code_offset] = static_cast<char>(v) + '0';
      code_offset++;
    };

    // Assume two digits will be enough
    auto print_2_helper = [&](int v) {
      if (v / 10 != 0)
      {
        print_1_helper(v / 10);
      }
      print_1_helper(v % 10);
    };

    print_2_helper(major);
    print_2_helper(minor);

    cuda_cub::throw_on_error(cudaErrorInvalidDevice, str);
  }

  return ptx_version;
}

THRUST_RUNTIME_FUNCTION inline cudaError_t sync_stream(cudaStream_t stream)
{
  return cub::SyncStream(stream);
}

inline void _CCCL_DEVICE sync_threadblock()
{
  __syncthreads();
}

// Deprecated [Since 2.8]
#define CUDA_CUB_RET_IF_FAIL(e)                \
  {                                            \
    auto const error = (e);                    \
    if (cub::Debug(error, __FILE__, __LINE__)) \
      return error;                            \
  }

// uninitialized
// -------
// stores type in uninitialized form
//
template <class T>
struct uninitialized
{
  using DeviceWord = typename cub::UnitWord<T>::DeviceWord;

  enum
  {
    WORDS = sizeof(T) / sizeof(DeviceWord)
  };

  DeviceWord storage[WORDS];

  _CCCL_HOST_DEVICE _CCCL_FORCEINLINE T& get()
  {
    return reinterpret_cast<T&>(*this);
  }

  _CCCL_HOST_DEVICE _CCCL_FORCEINLINE operator T&()
  {
    return get();
  }
};

// uninitialized_array
// --------------
// allocates uninitialized data on stack
template <class T, size_t N>
struct uninitialized_array
{
  using value_type = T;
  using ref        = T[N];
  enum
  {
    SIZE = N
  };

private:
  char data_[N * sizeof(T)];

public:
  _CCCL_HOST_DEVICE T* data()
  {
    return data_;
  }
  _CCCL_HOST_DEVICE const T* data() const
  {
    return data_;
  }
  _CCCL_HOST_DEVICE T& operator[](unsigned int idx)
  {
    return ((T*) data_)[idx];
  }
  _CCCL_HOST_DEVICE T const& operator[](unsigned int idx) const
  {
    return ((T*) data_)[idx];
  }
  _CCCL_HOST_DEVICE T& operator[](int idx)
  {
    return ((T*) data_)[idx];
  }
  _CCCL_HOST_DEVICE T const& operator[](int idx) const
  {
    return ((T*) data_)[idx];
  }
  _CCCL_HOST_DEVICE unsigned int size() const
  {
    return N;
  }
  _CCCL_HOST_DEVICE operator ref&()
  {
    return *reinterpret_cast<ref*>(data_);
  }
  _CCCL_HOST_DEVICE ref& get_ref()
  {
    return (ref&) *this;
  }
};

_CCCL_HOST_DEVICE _CCCL_FORCEINLINE size_t align_to(size_t n, size_t align)
{
  return ((n + align - 1) / align) * align;
}

namespace host
{
inline cuda_optional<size_t> get_max_shared_memory_per_block()
{
  cudaError_t status = cudaSuccess;
  int dev_id         = 0;
  status             = cudaGetDevice(&dev_id);
  if (status != cudaSuccess)
  {
    return cuda_optional<size_t>(0, status);
  }

  int max_shmem = 0;
  status        = cudaDeviceGetAttribute(&max_shmem, cudaDevAttrMaxSharedMemoryPerBlock, dev_id);
  if (status != cudaSuccess)
  {
    return cuda_optional<size_t>(0, status);
  }
  return cuda_optional<size_t>(max_shmem, status);
}
} // namespace host

template <int ALLOCATIONS>
THRUST_RUNTIME_FUNCTION cudaError_t alias_storage(
  void* storage_ptr, size_t& storage_size, void* (&allocations)[ALLOCATIONS], size_t (&allocation_sizes)[ALLOCATIONS])
{
  return cub::detail::AliasTemporaries(storage_ptr, storage_size, allocations, allocation_sizes);
}

} // namespace core
using core::sm30;
using core::sm35;
using core::sm52;
using core::sm60;
} // namespace cuda_cub

THRUST_NAMESPACE_END
