// Copyright (c) 2015-2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#include <tao/pegtl/file_parser.hh>

#if defined(_POSIX_MAPPED_FILES)

#include "test.hh"

namespace tao
{
   namespace pegtl
   {
      void unit_test()
      {
         const internal::file_opener fo( "Makefile" );
         ::close( fo.m_fd );  // Provoke exception, nobody would normally do this.
         try {
            fo.size();
            std::cerr << "pegtl: unit test failed for [ internal::file_opener ] " << std::endl;
            ++failed;
         }
         catch ( const std::exception & ) {
         }
      }

   } // namespace pegtl

} // namespace tao

#include "main.hh"

#else

int main( int, char ** )
{
   return 0;
}

#endif