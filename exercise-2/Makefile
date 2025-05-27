SRC_FILES := $(wildcard src/tcp_echo_*.cc)
OUTPUTS := $(patsubst src/tcp_echo_%.cc, build/%.out, $(SRC_FILES))
BUILD_FOLDER := build

all: $(BUILD_FOLDER) $(OUTPUTS)

$(BUILD_FOLDER):
	mkdir -p $(BUILD_FOLDER)

build/%.out: src/tcp_echo_%.cc
	g++ -g -std=c++23 $< -o $@

clean:
	rm -rf $(BUILD_FOLDER)