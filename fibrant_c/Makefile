# --- Settings --- #
BUILD_DIR=build
CC=gcc
CFLAGS=-Wall -O3
AR=ar rc
RANLIB=ranlib
RM=rm -rf

# --- Non-Settings --- #
BIN=$(BUILD_DIR)/bin
LIB=$(BUILD_DIR)/lib

FIBER=$(BIN)/fiber
FIBER_O= \
	$(BUILD_DIR)/fiber/main.o

LIBFIBRANT=$(LIB)/libfibrant.a
LIBFIBRANT_O= \
	$(BUILD_DIR)/libfibrant/expr.o

UTIL=$(LIB)/util.a
UTIL_O= \
	$(BUILD_DIR)/util/args.o

# Build everything.
all: $(FIBER) $(LIBFIBRANT) $(UTIL)

# Build the CLI.
$(FIBER): $(FIBER_O) $(LIBFIBRANT) $(UTIL)
	$(CC) -o $@ $(FIBER_O) $(LIBFIBRANT) $(UTIL)

# Build the library.
$(LIBFIBRANT): $(LIBFIBRANT_O) $(UTIL)
	$(AR) $@ $(LIBFIBRANT_O) $(UTIL)
	$(RANLIB) $@

# Build the utility library.
$(UTIL): $(UTIL_O)
	$(AR) $@ $?
	$(RANLIB) $@

# Make the build directory.
$(BUILD_DIR):
	mkdir $(BUILD_DIR)
	mkdir $(BIN)
	mkdir $(LIB)
	mkdir $(BUILD_DIR)/fiber
	mkdir $(BUILD_DIR)/libfibrant
	mkdir $(BUILD_DIR)/util

# Remove the build directory.
clean:
	$(RM) $(BUILD_DIR)

# Build rules for object files.
$(BUILD_DIR)/libfibrant/expr.o: libfibrant/expr.c $(BUILD_DIR)
	$(CC) -c $< -o $@

$(BUILD_DIR)/fiber/main.o: fiber/main.c $(BUILD_DIR)
	$(CC) -c $< -o $@

$(BUILD_DIR)/util/args.o: util/args.c $(BUILD_DIR)
	$(CC) -c $< -o $@
