add_library(particle_lib particle.cpp)
target_compile_features(particle_lib PUBLIC cxx_std_17)
target_include_directories(particle_lib PUBLIC ../include)

add_library(manyBody_lib manyBodySystem.cpp)
target_compile_features(manyBody_lib PUBLIC cxx_std_17)
target_include_directories(manyBody_lib PUBLIC ../include)

find_package(Eigen3 3.4 REQUIRED)
find_package(OpenMP REQUIRED)

target_link_libraries(particle_lib PUBLIC Eigen3::Eigen OpenMP::OpenMP_CXX)
target_link_libraries(manyBody_lib PUBLIC Eigen3::Eigen OpenMP::OpenMP_CXX particle_lib)


#set(PHAS0100ASSIGNMENT1_LIBRARY_NAME PHAS0100ASSIGNMENT1)

#set(PHAS0100ASSIGNMENT1_LIBRARY_SRCS
 # golGameClass.cpp
  #golGridClass.cpp
  #golFunctions.cpp
  #golException.cpp
#)

#set(PHAS0100ASSIGNMENT1_LIBRARY_HDRS
 # golExceptionMacro.h
#)

#add_library(${PHAS0100ASSIGNMENT1_LIBRARY_NAME} ${PHAS0100ASSIGNMENT1_LIBRARY_HDRS} ${PHAS0100ASSIGNMENT1_LIBRARY_SRCS})

#target_link_libraries(${PHAS0100ASSIGNMENT1_LIBRARY_NAME} PRIVATE ${ALL_THIRD_PARTY_LIBRARIES})
