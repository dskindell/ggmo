
.PHONY: all prepare clean

CFLAGS    = -I.. -Igoogletest/googletest/include -Igoogletest/googlemock/include

all: ggmo_test

obj/libgtest.a:
	[ -d googletest ] || \
	    git clone -b master --single-branch https://github.com/google/googletest.git
	[ -d obj ] || mkdir -p obj
	$(CXX) $(CFLAGS) -Igoogletest/googletest -c -o obj/gtest-all.o googletest/googletest/src/gtest-all.cc
	$(CXX) $(CFLAGS) -Igoogletest/googlemock -c -o obj/gmock-all.o googletest/googlemock/src/gmock-all.cc
	$(CXX) $(CFLAGS) -Igoogletest/googlemock -c -o obj/gmock_main.o googletest/googlemock/src/gmock_main.cc
	$(AR) rcs $@ obj/gtest-all.o obj/gmock-all.o obj/gmock_main.o

ggmo_test: ggmo_test.cpp ../ggmo.h obj/libgtest.a
	$(CXX) $(CFLAGS) -o $@ $< -Lobj -lgtest -lpthread

clean:
	-rm -rf googletest obj
	-rm ggmo_test

