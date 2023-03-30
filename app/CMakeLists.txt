add_executable(solarSystemSimulator solarSystemSimulator.cpp)
target_compile_features(solarSystemSimulator PUBLIC cxx_std_17)
target_include_directories(solarSystemSimulator PUBLIC ../include)

add_executable(nBodySystemSimulator nBodySystemSimulator.cpp)
target_compile_features(nBodySystemSimulator PUBLIC cxx_std_17)
target_include_directories(nBodySystemSimulator PUBLIC ../include)

find_package(Eigen3 3.4 REQUIRED)
find_package(OpenMP REQUIRED)

target_link_libraries(solarSystemSimulator PUBLIC Eigen3::Eigen OpenMP::OpenMP_CXX particle_lib manyBody_lib)
target_compile_options(solarSystemSimulator PRIVATE -O0)

target_link_libraries(nBodySystemSimulator PUBLIC Eigen3::Eigen OpenMP::OpenMP_CXX particle_lib manyBody_lib)
target_compile_options(nBodySystemSimulator PRIVATE -O0)