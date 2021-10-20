add_test( test_bitmap.test_bitmap [==[/home/ligen/桌面/github/miniob/build/bin/bitmap_test]==] [==[--gtest_filter=test_bitmap.test_bitmap]==] --gtest_also_run_disabled_tests)
set_tests_properties( test_bitmap.test_bitmap PROPERTIES WORKING_DIRECTORY [==[/home/ligen/桌面/github/miniob/build/unitest]==])
set( bitmap_test_TESTS test_bitmap.test_bitmap)
