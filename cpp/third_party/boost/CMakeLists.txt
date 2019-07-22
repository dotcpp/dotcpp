file(GLOB_RECURSE BOOST_SYSTEM "system/detail/*.cpp")
file(GLOB_RECURSE BOOST_DATETIME "date_time/*.cpp")
file(GLOB_RECURSE BOOST_ARCHIVE "archive/impl/src/*.cpp")
file(GLOB_RECURSE BOOST_FILESYSTEM "filesystem/src/*.cpp")
file(GLOB_RECURSE BOOST_TEST "test/impl/*.ipp")

set_source_files_properties(${BOOST_TEST} PROPERTIES LANGUAGE CXX)
set_source_files_properties(${BOOST_TEST} PROPERTIES COMPILE_FLAGS "-x c++")
add_library(BoostLib ${BOOST_SYSTEM} ${BOOST_DATETIME} ${BOOST_ARCHIVE} ${BOOST_FILESYSTEM} ${BOOST_TEST})

set(CMAKE_CXX_FLAGS "-fPIC")
