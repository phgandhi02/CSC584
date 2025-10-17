# === Recursive wildcard ===
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# === Source and object files ===
src := $(call rwildcard,./src/,*.cpp) $(call rwildcard,./,main.cpp)
obj := $(patsubst %.cpp,%.o,$(src))

# === Output binary ===
TARGET = main

# === C++ standard ===
CXX_STANDARD = -std=c++17

# === SFML static linking flags ===
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lGL -lX11 -lXrandr -lXcursor -lXi -lfreetype -lpthread -ldl -ludev


# === Include paths for different platforms ===
INTELMAC_INCLUDE=-I/usr/local/include
APPLESILICON_INCLUDE=-I/opt/homebrew/include
UBUNTU_INCLUDE=-I/usr/local/include
UBUNTU_APPLESILICON_INCLUDE=-I/usr/include
UBUNTU_INTEL_INCLUDE=-I/usr/include

# === Library paths for different platforms ===
INTELMAC_LIB=-L/usr/local/lib
APPLESILICON_LIB=-L/opt/homebrew/lib
UBUNTU_LIB=-L/usr/local/lib -L/usr/lib -L/usr/lib/x86_64-linux-gnu
UBUNTU_APPLESILICON_LIB=-L/usr/lib/aarch64-linux-gnu
UBUNTU_INTEL_LIB=-L/usr/lib/x86_64-linux-gnu

# === Platform-specific settings ===
MACOS_COMPILER=/usr/bin/clang++
UBUNTU_COMPILER=/usr/bin/g++
MACOS_INCLUDE=$(APPLESILICON_INCLUDE)
MACOS_LIB=$(APPLESILICON_LIB)

# === Detect OS ===
uname_s := $(shell uname -s)

# === Default build target ===
all: $(TARGET)

# === Linking stage ===
$(TARGET): $(obj)
ifeq ($(uname_s),Darwin)
	@echo "Building for macOS..."
	$(MACOS_COMPILER) $(CXX_STANDARD) -o $@ $^ $(MACOS_LIB) $(LDFLAGS)
else ifeq ($(uname_s),Linux)
	@echo "Building for Linux..."
	$(UBUNTU_COMPILER) $(CXX_STANDARD) -o $@ $^ $(UBUNTU_LIB) $(LDFLAGS)
else
	$(error Unsupported OS: $(uname_s))
endif

# === Compilation rule for .cpp -> .o ===
%.o: %.cpp
ifeq ($(uname_s),Darwin)
	@echo "Compiling (macOS): $<"
	$(MACOS_COMPILER) $(CXX_STANDARD) -c $< -o $@ $(MACOS_INCLUDE)
else ifeq ($(uname_s),Linux)
	@echo "Compiling (Linux): $<"
	$(UBUNTU_COMPILER) $(CXX_STANDARD) -c $< -o $@ $(UBUNTU_INCLUDE)
endif

# === Clean up build artifacts ===
.PHONY: clean
clean:
	rm -f $(obj) $(TARGET)
	@echo "Cleaned up build artifacts."

# === Optional: run target ===
.PHONY: run
run: $(TARGET)
	./$(TARGET)
