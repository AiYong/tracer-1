# Copyright (c) 2017, Daniel Mensinger
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of the Daniel Mensinger nor the
#       names of its contributors may be used to endorse or promote products
#       derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL Daniel Mensinger LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

include(FindPackageHandleStandardArgs)

find_path(
  DLFCN_INC
    NAMES dlfcn.h
    HINTS ${DLFCN_ROOT}/include
)

find_library(
  DLFCN_DW_LIB_SHARED
    NAMES dl
    HINTS
      /usr/lib
      ${DLFCN_ROOT}/lib
)

find_library(
  DLFCN_DW_LIB_STATIC
    NAMES libdl.a
    HINTS
      /usr/lib
      ${DLFCN_ROOT}/lib
)

find_package_handle_standard_args(
  DLFCN
  REQUIRED_VARS DLFCN_INC DLFCN_DW_LIB_SHARED DLFCN_DW_LIB_STATIC
)

if( DLFCN_FOUND )
  set( DLFCN_INCLUDE_DIRS ${DLFCN_INC} )
  set( DLFCN_LIBRARIES    ${DLFCN_DW_LIB_SHARED} )
  set( DLFCN_STATIC_LIB   ${DLFCN_DW_LIB_STATIC} )

  if( NOT TARGET DLFCN::DLFCN )
    add_library(DLFCN::DLFCN UNKNOWN IMPORTED)
    set_target_properties( DLFCN::DLFCN
      PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${DLFCN_INCLUDE_DIRS}"
        IMPORTED_LOCATION             "${DLFCN_LIBRARIES}"
    )
  endif( NOT TARGET DLFCN::DLFCN )
endif()
