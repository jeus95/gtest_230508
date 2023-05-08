

# Google Test
 - Google Test Framework
 - Google Mock Framework

## Google Test 빌드
 > 정적 라이브러리로 빌드해서 많이 사용합니다. 

```
# gtest-all.cc
$ g++ -c ./googletest/googletest/src/gtest-all.cc -I ./googletest/googletest/include/ -I ./googletest/googletest/

# libgtest.a
$ ar rcv libgtest.a gtest-all.o 

```
