run:
	cmake -B build && cmake --build build && ./build/Orion
	cmake -B build -DCMAKE_BUILD_TYPE=Debug && cmake --build build && ./build/Orion

test:
	cmake -B tests && cmake --build tests && ./tests/Debug/ClientTests