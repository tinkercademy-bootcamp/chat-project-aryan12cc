SRC_FILES := $(wildcard src/tcp_echo_*.cpp)
OUTPUTS := $(patsubst src/tcp_echo_%.cpp, build/%.out, $(SRC_FILES))
BUILD_FOLDER := build
CXX_FLAGS := -std=c++23 -g -fsanitize=address
LD_FLAGS := -fsanitize=address
COMMON_FILES := src/net_operations/net_operations.cpp

all: $(BUILD_FOLDER) $(OUTPUTS)

$(BUILD_FOLDER):
	mkdir -p $(BUILD_FOLDER)

build/%.out: src/tcp_echo_%.cpp
	g++ $(CXX_FLAGS) $(COMMON_FILES) $< -o $@ $(LD_FLAGS)

clean:
	rm -rf $(BUILD_FOLDER)