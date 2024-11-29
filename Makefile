main: src/main.cpp
	mkdir -p build && g++ -g -o build/main src/utils.cpp src/main.cpp -I./include -Wl,-rpath=$(MVCAM_COMMON_RUNENV)/64 -L$(MVCAM_COMMON_RUNENV)/64 -lMvCameraControl -fconcepts
	

clean:
	rm -rf ./build

run: 
	./build/main
