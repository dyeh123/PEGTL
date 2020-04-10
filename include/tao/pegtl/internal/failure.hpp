// Copyright (c) 2014-2020 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAO_PEGTL_INTERNAL_FAILURE_HPP
#define TAO_PEGTL_INTERNAL_FAILURE_HPP

#include "../config.hpp"

#include "enable_control.hpp"

#include "../rule_list.hpp"

namespace TAO_PEGTL_NAMESPACE::internal
{
   struct failure
   {
      using rule_t = failure;
      using subs_t = empty_list;

      template< typename Input >
      [[nodiscard]] static bool match( Input& /*unused*/ ) noexcept
      {
         return false;
      }
   };

   template<>
   inline constexpr bool enable_control< failure > = false;

}  // namespace TAO_PEGTL_NAMESPACE::internal

#endif