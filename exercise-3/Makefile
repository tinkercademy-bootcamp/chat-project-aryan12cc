SRC_FILES := $(wildcard src/tcp_echo_*.cc)
OUTPUTS := $(patsubst src/tcp_echo_%.cc, build/%.out, $(SRC_FILES))
BUILD_FOLDER := build
CXX_FLAGS := -std=c++23 -g -fsanitize=address
LD_FLAGS := -fsanitize=address

all: $(BUILD_FOLDER) $(OUTPUTS)

$(BUILD_FOLDER):
	mkdir -p $(BUILD_FOLDER)

build/%.out: src/tcp_echo_%.cc
	g++ $(CXX_FLAGS) -std=c++23 $< -o $@ $(LD_FLAGS)

clean:
	rm -rf $(BUILD_FOLDER)