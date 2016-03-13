#
# Copyright 2016 by Philip N. Garner
#
# See the file COPYING for the licence associated with this software.
#
# Author(s):
#   Phil Garner, March 2016
#

# Card library
add_library(card-shared SHARED card.cpp)
set_target_properties(card-shared
  PROPERTIES OUTPUT_NAME "card"
  PUBLIC_HEADER "card.h"
  INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/lube"
  )
target_link_libraries(card-shared ${TARGET_LIBS})

# The Windows Address Book module
add_library(wab-lib MODULE wabfile.cpp)
set_target_properties(wab-lib
  PROPERTIES OUTPUT_NAME "wab"
  )
target_link_libraries(wab-lib card-shared)
list(APPEND MODULE_TARGETS wab-lib)

# The vCard module
add_library(vcf-lib MODULE vcffile.cpp)
set_target_properties(vcf-lib
  PROPERTIES OUTPUT_NAME "vcf"
  )
target_link_libraries(vcf-lib card-shared)
list(APPEND MODULE_TARGETS vcf-lib)

# The LDIF module
add_library(ldif-lib MODULE ldiffile.cpp)
set_target_properties(ldif-lib
  PROPERTIES OUTPUT_NAME "ldif"
  )
target_link_libraries(ldif-lib card-shared)
list(APPEND MODULE_TARGETS ldif-lib)
