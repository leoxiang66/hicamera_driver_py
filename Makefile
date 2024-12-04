# Installation paths
PREFIX = /usr/local
INCLUDE_DIR = $(PREFIX)/include/hikvision_api
LIB_DIR = $(PREFIX)/lib

main: src/main.cpp
	mkdir -p build
	g++ -g -o build/main src/utils.cpp src/main.cpp src/timer.cpp -I./include -Wl,-rpath=$(MVCAM_COMMON_RUNENV)/64 -L$(MVCAM_COMMON_RUNENV)/64 -lMvCameraControl -fconcepts -lpthread

clean:
	rm -rf ./build

install:
	# Install headers
	mkdir -p $(INCLUDE_DIR)
	cp include/*.h $(INCLUDE_DIR)
	# Compile and install static library
	g++ -c src/utils.cpp src/timer.cpp -I./include
	ar rcs $(LIB_DIR)/libhikvision_api.a utils.o timer.o
	rm -f utils.o timer.o

uninstall:
	# Remove installed headers and library
	rm -rf $(INCLUDE_DIR)
	rm -f $(LIB_DIR)/libhikvision_api.a

run:
	./build/main