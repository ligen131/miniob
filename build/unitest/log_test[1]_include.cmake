if(EXISTS "/home/ligen/桌面/github/miniob/build/unitest/log_test[1]_tests.cmake")
  include("/home/ligen/桌面/github/miniob/build/unitest/log_test[1]_tests.cmake")
else()
  add_test(log_test_NOT_BUILT log_test_NOT_BUILT)
endif()
