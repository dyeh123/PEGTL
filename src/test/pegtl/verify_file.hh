// Copyright (c) 2014-2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAOCPP_PEGTL_INCLUDE_TEST_VERIFY_FILE_HH
#define TAOCPP_PEGTL_INCLUDE_TEST_VERIFY_FILE_HH

#include <tao/pegtl.hh>

namespace tao
{
   namespace pegtl
   {
      struct file_content : seq< TAOCPP_PEGTL_STRING( "dummy content" ), eol, discard > {};
      struct file_grammar : seq< rep_min_max< 11, 11, file_content >, eof > {};

      template< typename Rule >
      struct file_action
            : nothing< Rule > {};

      template<>
      struct file_action< eof >
      {
         template< typename Input >
         static void apply( const Input &, bool & flag )
         {
            flag = true;
         }
      };

      template< typename Rule >
      struct file_control
            : normal< Rule > {};

      template<>
      struct file_control< eof >
            : normal< eof >
      {
         template< typename Input >
         static void success( const Input &, bool & flag )
         {
            flag = true;
         }
      };

      template< typename T >
      void verify_file()
      {
         {
            const std::string f{ "src/test/pegtl/no_such_file.txt" };
            try {
               T p{ f };
               TEST_ASSERT( !"no error on opening non-existing file" );
            }
            catch( const input_error & ) {
            }
         } {
            const std::string f{ "src/test/pegtl/file_data.txt" };
            T p{ f };
            TEST_ASSERT( p.source() == f );
            TEST_ASSERT( p.template parse< file_grammar >() );
            TEST_ASSERT( p.source() == f );
         } {
            const std::string f{ "src/test/pegtl/file_data.txt" };
            T p{ f };
            bool flag = true;
            TEST_ASSERT( p.source() == f );
            TEST_ASSERT( p.template parse< file_grammar >( flag ) );
            TEST_ASSERT( flag == true );
         } {
            const std::string f{ "src/test/pegtl/file_data.txt" };
            T p{ f };
            bool flag = false;
            TEST_ASSERT( p.source() == f );
            TEST_ASSERT( p.template parse< file_grammar >( flag ) );
            TEST_ASSERT( flag == false );
         } {
            const std::string f{ "src/test/pegtl/file_data.txt" };
            T p{ f };
            bool flag = false;
            TEST_ASSERT( p.source() == f );
            const bool result = p.template parse< file_grammar, file_action >( flag );
            TEST_ASSERT( result );
            TEST_ASSERT( flag == true );
         } {
            const std::string f{ "src/test/pegtl/file_data.txt" };
            T p{ f };
            bool flag = false;
            TEST_ASSERT( p.source() == f );
            const bool result = p.template parse< file_grammar, nothing, file_control >( flag );
            TEST_ASSERT( result );
            TEST_ASSERT( flag == true );
         }
      }

   } // namespace pegtl

} // namespace tao

#endif