// Copyright (c) 2014-2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAOCPP_PEGTL_INCLUDE_INTERNAL_STRING_HH
#define TAOCPP_PEGTL_INCLUDE_INTERNAL_STRING_HH

#include <utility>
#include <cstring>

#include "../config.hh"

#include "result_on_found.hh"
#include "skip_control.hh"
#include "bump_help.hh"
#include "trivial.hh"

#include "../analysis/counted.hh"

namespace tao
{
   namespace TAOCPP_PEGTL_NAMESPACE
   {
      namespace internal
      {
         inline bool unsafe_equals( const char * s, const std::initializer_list< char > & l )
         {
            return std::memcmp( s, & * l.begin(), l.size() ) == 0;
         }

         template< char ... Cs >
         struct string;

         template< char ... Cs >
         struct skip_control< string< Cs ... > > : std::true_type {};

         template<>
         struct string<>
               : trivial< true > {};

         template< char ... Cs >
         struct string
         {
            using analyze_t = analysis::counted< analysis::rule_type::ANY, sizeof ... ( Cs ) >;

            template< typename Input >
            static bool match( Input & in )
            {
               if ( in.size( sizeof ... ( Cs ) ) >= sizeof ... ( Cs ) ) {
                  if ( unsafe_equals( in.begin(), { Cs ... } ) ) {
                     bump_help< result_on_found::SUCCESS, Input, char, Cs ... >( in, sizeof ... ( Cs ) );
                     return true;
                  }
               }
               return false;
            }
         };

      } // namespace internal

   } // namespace TAOCPP_PEGTL_NAMESPACE

} // namespace tao

#endif