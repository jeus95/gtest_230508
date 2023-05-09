#!/bin/sh
g++ $1 -I ./googletest/googletest/include -L. -lgtest -pthread \
-DGTEST_LEAK_TEST
