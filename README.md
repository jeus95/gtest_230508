

# Google Test
 - Google Test Framework
 - Google Mock Framework

## Google Test 빌드
 > 정적 라이브러리로 빌드해서 많이 사용합니다. 

1) 동적 라이브러리: libgtest.so
 : 라이브러리의 구현이 실행 파일에 포함되지 않고, 실행 시에 동적으로 로드해서
   사용합니다.
   - 라이브러리가 변경되어도 실행 파일을 다시 컴파일할 필요가 없습니다.
   - 실행 파일과 함께 라이브러리도 함께 제공되어야 합니다.

2) 정적 라이브러리: libgtest.a
 : 라이브러리의 구현이 실행 파일에 포함됩니다.
  - 라이브러리가 변경되면, 실행 파일을 다시 컴파일해야 합니다.
  - 실행 파일을 단독으로 제공하면 됩니다.

```
# gtest-all.cc
$ g++ -c ./googletest/googletest/src/gtest-all.cc -I ./googletest/googletest/include/ -I ./googletest/googletest/

# gtest_main.cc
$ g++ -c ./googletest/googletest/src/gtest_main.cc -I ./googletest/googletest/include

# libgtest.a
$ ar rcv libgtest.a gtest-all.o gtest_main.o

```

## GoogleMock 빌드
> GoogleTest에 의존성이 있습니다.

```
# gtest-all.cc
$ g++ -c ./googletest/googletest/src/gtest-all.cc -I ./googletest/googletest/include/ -I ./googletest/googletest/

# gmock-all.cc
$ g++ -c ./googletest/googlemock/src/gmock-all.cc \
-I ./googletest/googlemock/include/ \
-I ./googletest/googlemock/ \
-I ./googletest/googletest/include/

# gmock_main.cc
$ g++ -c ./googletest/googlemock/src/gmock_main.cc \
-I ./googletest/googlemock/include/ \
-I ./googletest/googletest/include

# libgtest.a
$ ar rcv libgtest.a gtest-all.o gmock-all.o gmock_main.o

```