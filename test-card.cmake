#
# Copyright 2015 by Philip N. Garner
#
# See the file COPYING for the licence associated with this software.
#
# Author(s):
#   Phil Garner, January 2015
#

# Set up the test to compare reference and output files
set(CMD ./test-card)
set(REF test-card-ref.txt)
set(OUT test-card-out.txt)

# Run the test
execute_process(
  COMMAND ${CMD}
  OUTPUT_FILE ${OUT}
  RESULT_VARIABLE RETURN_TESTS
  )
if(RETURN_TESTS)
  message(FATAL_ERROR "Test returned non-zero value ${RETURN_TESTS}")
endif()

# Use CMake to compare the reference and output files
execute_process(
  COMMAND ${CMAKE_COMMAND} -E compare_files ${OUT} ${REF}
  RESULT_VARIABLE RETURN_COMPARE
  )
if(RETURN_COMPARE)
  message(FATAL_ERROR "Test failed: ${REF} and ${OUT} differ")
endif()
