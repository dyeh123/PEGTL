// Copyright (c) 2016-2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAOCPP_PEGTL_INCLUDE_REWIND_MODE_HH
#define TAOCPP_PEGTL_INCLUDE_REWIND_MODE_HH

#include "config.hh"

namespace tao
{
   namespace TAOCPP_PEGTL_NAMESPACE
   {
      enum class rewind_mode : char
      {
         ACTIVE,
         REQUIRED,
         DONTCARE
      };

   } // namespace TAOCPP_PEGTL_NAMESPACE

} // namespace tao

#endif