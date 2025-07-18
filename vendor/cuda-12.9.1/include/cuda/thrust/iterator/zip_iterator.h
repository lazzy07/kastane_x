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

/*! \file thrust/iterator/zip_iterator.h
 *  \brief An iterator which returns a tuple of the result of dereferencing
 *         a tuple of iterators when dereferenced
 */

/*
 * Copyright David Abrahams and Thomas Becker 2000-2006.
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying NOTICE file for the complete license)
 *
 * For more information, see http://www.boost.org
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
#include <thrust/detail/type_traits.h>
#include <thrust/iterator/detail/zip_iterator_base.h>
#include <thrust/iterator/iterator_facade.h>

THRUST_NAMESPACE_BEGIN

/*! \addtogroup iterators
 *  \{
 */

/*! \addtogroup fancyiterator Fancy Iterators
 *  \ingroup iterators
 *  \{
 */

/*! \p zip_iterator is an iterator which represents a pointer into a range
 *  of \p tuples whose elements are themselves taken from a \p tuple of input
 *  iterators. This iterator is useful for creating a virtual array of structures
 *  while achieving the same performance and bandwidth as the structure of arrays
 *  idiom. \p zip_iterator also facilitates kernel fusion by providing a convenient
 *  means of amortizing the execution of the same operation over multiple ranges.
 *
 *  The following code snippet demonstrates how to create a \p zip_iterator
 *  which represents the result of "zipping" multiple ranges together.
 *
 *  \code
 *  #include <thrust/iterator/zip_iterator.h>
 *  #include <thrust/tuple.h>
 *  #include <thrust/device_vector.h>
 *  ...
 *  thrust::device_vector<int> int_v{0, 1, 2};
 *  thrust::device_vector<float> float_v{0.0f, 1.0f, 2.0f};
 *  thrust::device_vector<char> char_v{'a', 'b', 'c'};
 *
 *  // aliases for iterators
 *  using IntIterator = thrust::device_vector<int>::iterator;
 *  using FloatIterator = thrust::device_vector<float>::iterator;
 *  using CharIterator = thrust::device_vector<char>::iterator;
 *
 *  // alias for a tuple of these iterators
 *  using IteratorTuple = thrust::tuple<IntIterator, FloatIterator, CharIterator>;
 *
 *  // alias the zip_iterator of this tuple
 *  using ZipIterator = thrust::zip_iterator<IteratorTuple>;
 *
 *  // finally, create the zip_iterator
 *  ZipIterator iter(thrust::make_tuple(int_v.begin(), float_v.begin(), char_v.begin()));
 *
 *  *iter;   // returns (0, 0.0f, 'a')
 *  iter[0]; // returns (0, 0.0f, 'a')
 *  iter[1]; // returns (1, 1.0f, 'b')
 *  iter[2]; // returns (2, 2.0f, 'c')
 *
 *  thrust::get<0>(iter[2]); // returns 2
 *  thrust::get<1>(iter[0]); // returns 0.0f
 *  thrust::get<2>(iter[1]); // returns 'b'
 *
 *  // iter[3] is an out-of-bounds error
 *  \endcode
 *
 *  Defining the type of a \p zip_iterator can be complex. The next code example demonstrates
 *  how to use the \p make_zip_iterator function with the \p make_tuple function to avoid
 *  explicitly specifying the type of the \p zip_iterator. This example shows how to use
 *  \p zip_iterator to copy multiple ranges with a single call to \p thrust::copy.
 *
 *  \code
 *  #include <thrust/zip_iterator.h>
 *  #include <thrust/tuple.h>
 *  #include <thrust/device_vector.h>
 *
 *  int main()
 *  {
 *    thrust::device_vector<int> int_in{0, 1, 2}, int_out(3);
 *    thrust::device_vector<float> float_in{0.0f, 10.0f, 20.0f}, float_out(3);
 *
 *    thrust::copy(thrust::make_zip_iterator(thrust::make_tuple(int_in.begin(), float_in.begin())),
 *                 thrust::make_zip_iterator(thrust::make_tuple(int_in.end(),   float_in.end())),
 *                 thrust::make_zip_iterator(thrust::make_tuple(int_out.begin(),float_out.begin())));
 *
 *    // int_out is now [0, 1, 2]
 *    // float_out is now [0.0f, 10.0f, 20.0f]
 *
 *    return 0;
 *  }
 *  \endcode
 *
 *  \see make_zip_iterator
 *  \see make_tuple
 *  \see tuple
 *  \see get
 */
template <typename IteratorTuple>
class _CCCL_DECLSPEC_EMPTY_BASES zip_iterator : public detail::zip_iterator_base<IteratorTuple>::type
{
public:
  /*! The underlying iterator tuple type. Alias to zip_iterator's first template argument.
   */
  using iterator_tuple = IteratorTuple;

  /*! Default constructor does nothing.
   */
#if _CCCL_COMPILER(MSVC2017)
  inline _CCCL_HOST_DEVICE zip_iterator() {}
#else // ^^^ _CCCL_COMPILER(MSVC2017) ^^^ / vvv !_CCCL_COMPILER(MSVC2017) vvv
  zip_iterator() = default;
#endif // !_CCCL_COMPILER(MSVC2017)

  /*! This constructor creates a new \p zip_iterator from a
   *  \p tuple of iterators.
   *
   *  \param iterator_tuple The \p tuple of iterators to copy from.
   */
  inline _CCCL_HOST_DEVICE zip_iterator(IteratorTuple iterator_tuple);

  /*! This copy constructor creates a new \p zip_iterator from another
   *  \p zip_iterator.
   *
   *  \param other The \p zip_iterator to copy.
   */
  template <typename OtherIteratorTuple, detail::enable_if_convertible_t<OtherIteratorTuple, IteratorTuple, int> = 0>
  inline _CCCL_HOST_DEVICE zip_iterator(const zip_iterator<OtherIteratorTuple>& other)
      : m_iterator_tuple(other.get_iterator_tuple())
  {}

  /*! This method returns a \c const reference to this \p zip_iterator's
   *  \p tuple of iterators.
   *
   *  \return A \c const reference to this \p zip_iterator's \p tuple
   *          of iterators.
   */
  inline _CCCL_HOST_DEVICE const IteratorTuple& get_iterator_tuple() const;

  /*! \cond
   */

private:
  using super_t = typename detail::zip_iterator_base<IteratorTuple>::type;

  friend class iterator_core_access;

  // Dereferencing returns a tuple built from the dereferenced
  // iterators in the iterator tuple.
  _CCCL_HOST_DEVICE typename super_t::reference dereference() const;

  // Two zip_iterators are equal if the two first iterators of the
  // tuple are equal. Note this differs from Boost's implementation, which
  // considers the entire tuple.
  template <typename OtherIteratorTuple>
  inline _CCCL_HOST_DEVICE bool equal(const zip_iterator<OtherIteratorTuple>& other) const;

  // Advancing a zip_iterator means to advance all iterators in the tuple
  inline _CCCL_HOST_DEVICE void advance(typename super_t::difference_type n);

  // Incrementing a zip iterator means to increment all iterators in the tuple
  inline _CCCL_HOST_DEVICE void increment();

  // Decrementing a zip iterator means to decrement all iterators in the tuple
  inline _CCCL_HOST_DEVICE void decrement();

  // Distance is calculated using the first iterator in the tuple.
  template <typename OtherIteratorTuple>
  inline _CCCL_HOST_DEVICE typename super_t::difference_type
  distance_to(const zip_iterator<OtherIteratorTuple>& other) const;

  // The iterator tuple.
  IteratorTuple m_iterator_tuple;

  /*! \endcond
   */
}; // end zip_iterator

/*! \p make_zip_iterator creates a \p zip_iterator from a \p tuple
 *  of iterators.
 *
 *  \param t The \p tuple of iterators to copy.
 *  \return A newly created \p zip_iterator which zips the iterators encapsulated in \p t.
 *
 *  \see zip_iterator
 */
template <typename... Iterators>
inline _CCCL_HOST_DEVICE zip_iterator<thrust::tuple<Iterators...>> make_zip_iterator(thrust::tuple<Iterators...> t);

/*! \p make_zip_iterator creates a \p zip_iterator from
 *  iterators.
 *
 *  \param its The iterators to copy.
 *  \return A newly created \p zip_iterator which zips the iterators.
 *
 *  \see zip_iterator
 */
template <typename... Iterators>
inline _CCCL_HOST_DEVICE zip_iterator<thrust::tuple<Iterators...>> make_zip_iterator(Iterators... its);

/*! \} // end fancyiterators
 */

/*! \} // end iterators
 */

THRUST_NAMESPACE_END

#include <thrust/iterator/detail/zip_iterator.inl>
