find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_market test_market.cc)
target_link_libraries(test_market libmarket)
target_include_directories(test_market PUBLIC "${PROJECT_SOURCE_DIR}/src")

add_test(test_market test_market)
