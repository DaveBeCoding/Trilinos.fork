#ifndef __KOKKOSBATCHED_GEMV_TEAM_IMPL_HPP__
#define __KOKKOSBATCHED_GEMV_TEAM_IMPL_HPP__

/// \author Kyungjoo Kim (kyukim@sandia.gov)

#include "KokkosBatched_Util.hpp"
#include "KokkosBatched_Gemv_Team_Internal.hpp"

namespace KokkosBatched {

///
/// Team Impl
/// =========

///
/// Implemented:
/// NT, T
///
/// Not yet implemented
/// CT

///
/// NT
///

template <typename MemberType>
struct TeamGemv<MemberType, Trans::NoTranspose, Algo::Gemv::Unblocked> {
  template <typename ScalarType, typename AViewType, typename xViewType,
            typename yViewType>
  KOKKOS_INLINE_FUNCTION static int invoke(
      const MemberType &member, const ScalarType alpha, const AViewType &A,
      const xViewType &x, const ScalarType beta, const yViewType &y) {
    if (AViewType::Rank == 2)
      return TeamGemvInternal<Algo::Gemv::Unblocked>::invoke(
          member, A.extent(0), A.extent(1), alpha, A.data(), A.stride_0(),
          A.stride_1(), x.data(), x.stride_0(), beta, y.data(), y.stride_0());
    else
      return TeamGemvInternal<Algo::Gemv::Unblocked>::template invoke<
          MemberType, ScalarType, typename AViewType::array_layout,
          typename AViewType::non_const_value_type>(
          member, A.extent(0), A.extent(1), A.extent(2), alpha, A.data(),
          A.stride_0(), A.stride_1(), A.stride_2(), x.data(), x.stride_0(),
          x.stride_1(), beta, y.data(), y.stride_0(), y.stride_1());
  }
};

template <typename MemberType>
struct TeamGemv<MemberType, Trans::NoTranspose, Algo::Gemv::Blocked> {
  template <typename ScalarType, typename AViewType, typename xViewType,
            typename yViewType>
  KOKKOS_INLINE_FUNCTION static int invoke(
      const MemberType &member, const ScalarType alpha, const AViewType &A,
      const xViewType &x, const ScalarType beta, const yViewType &y) {
    return TeamGemvInternal<Algo::Gemv::Blocked>::invoke(
        member, A.extent(0), A.extent(1), alpha, A.data(), A.stride_0(),
        A.stride_1(), x.data(), x.stride_0(), beta, y.data(), y.stride_0());
  }
};

///
/// T
///

template <typename MemberType>
struct TeamGemv<MemberType, Trans::Transpose, Algo::Gemv::Unblocked> {
  template <typename ScalarType, typename AViewType, typename xViewType,
            typename yViewType>
  KOKKOS_INLINE_FUNCTION static int invoke(
      const MemberType &member, const ScalarType alpha, const AViewType &A,
      const xViewType &x, const ScalarType beta, const yViewType &y) {
    if (AViewType::Rank == 2)
      return TeamGemvInternal<Algo::Gemv::Unblocked>::invoke(
          member, A.extent(1), A.extent(0), alpha, A.data(), A.stride_1(),
          A.stride_0(), x.data(), x.stride_0(), beta, y.data(), y.stride_0());
    else
      return TeamGemvInternal<Algo::Gemv::Unblocked>::template invoke<
          MemberType, ScalarType, typename AViewType::array_layout,
          typename AViewType::non_const_value_type>(
          member, A.extent(0), A.extent(2), A.extent(1), alpha, A.data(),
          A.stride_0(), A.stride_2(), A.stride_1(), x.data(), x.stride_0(),
          x.stride_1(), beta, y.data(), y.stride_0(), y.stride_1());
  }
};

template <typename MemberType>
struct TeamGemv<MemberType, Trans::Transpose, Algo::Gemv::Blocked> {
  template <typename ScalarType, typename AViewType, typename xViewType,
            typename yViewType>
  KOKKOS_INLINE_FUNCTION static int invoke(
      const MemberType &member, const ScalarType alpha, const AViewType &A,
      const xViewType &x, const ScalarType beta, const yViewType &y) {
    return TeamGemvInternal<Algo::Gemv::Blocked>::invoke(
        member, A.extent(1), A.extent(0), alpha, A.data(), A.stride_1(),
        A.stride_0(), x.data(), x.stride_0(), beta, y.data(), y.stride_0());
  }
};

}  // namespace KokkosBatched

#endif
