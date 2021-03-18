# This file is part of CPU Energy Meter,
# a tool for measuring energy consumption of Intel CPUs:
# https://github.com/sosy-lab/cpu-energy-meter
#
# SPDX-FileCopyrightText: 2012 Intel Corporation
# SPDX-FileCopyrightText: 2015-2021 Dirk Beyer <https://www.sosy-lab.org>
#
# SPDX-License-Identifier: BSD-3-Clause

VERSION = 1.3-dev

DESTDIR :=
PREFIX := /usr/local
BINDIR = $(PREFIX)/bin

SRC_DIR = ./src
TEST_DIR = ./test
BUILD_DIR = ./build
SCRIPT_DIR = ./scripts
VENDOR_DIR = ./vendor
OBJ_DIR = ./build/obj
BUILD_PATHS = $(BUILD_DIR) $(OBJ_DIR)

# The parameters below are required by CMock
TEST_BUILD_DIR ?= ${BUILD_DIR}/test
TEST_MAKEFILE = ${TEST_BUILD_DIR}/MakefileTestSupport
OBJ = ${OBJ_DIR}

CC =gcc -g
CFLAGS =-I. -I$(SRC_DIR) -std=gnu99 -Wall -Wextra -Wpedantic -Werror -Wno-variadic-macros
TEST_CFLAGS =-DTEST $(CFLAGS) -Wno-unused-parameter
LDFLAGS =-Wl,--no-as-needed -lm -lcap
LIBS =-lm -lcap
export

TARGET_BIN = cpu-energy-meter
_SOURCES = cpu-energy-meter.c cpuinfo.c msr.c rapl.c util.c
SOURCES = $(patsubst %,$(SRC_DIR)/%,$(_SOURCES)) #convert to $SRC_DIR/_SOURCES
_HEADERS = cpuinfo.h intel-family.h msr.h rapl.h rapl-impl.h util.h
HEADERS = $(patsubst %,$(SRC_DIR)/%,$(_HEADERS)) #convert to $SRC_DIR/_HEADERS
TESTFILES = $(wildcard $(TEST_DIR)/*.c)
_OBJECTS = $(_SOURCES:.c=.o)
OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(_OBJECTS)) #convert to $OBJ_DIR/_OBJECTS
AUX = README.md CHANGELOG.md LICENSE .clang-format

.PHONY: default
default: all

.PHONY: all
all: $(BUILD_PATHS) $(TARGET_BIN)

# Create object files from SRC_DIR/*.c in OBJ_DIR/*.o
$(OBJ_DIR)%.o:: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create the cpu-energy-meter binary.
$(TARGET_BIN): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: setup
# Needs to be executed with root-rights ('sudo make setup')
setup:
ifneq ("$(wildcard $(TARGET_BIN))","")
	chgrp msr $(TARGET_BIN)
	chmod 2711 $(TARGET_BIN)
	setcap cap_sys_rawio=ep $(TARGET_BIN)
else
	@echo "No '$(TARGET_BIN)'-bin found. Consider using 'make' first."
endif

.PHONY: test
test: $(BUILD_PATHS)
	ruby scripts/create_makefile.rb
	$(MAKE) -f $(TEST_MAKEFILE) $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: clean
clean:
	rm -f $(TARGET_BIN)
	rm -rf $(BUILD_DIR)

.PHONY: install
install: all
	install -d $(DESTDIR)$(BINDIR)
	install $(TARGET_BIN) $(DESTDIR)$(BINDIR)

.PHONY: uninstall
uninstall:
	-rm -f $(DESTDIR)$(BINDIR)/$(TARGET_BIN)

.PHONY: gprof   # outdated functionality that is currently broken;
                # will be fixed in a future update
gprof: CFLAGS = -pg
gprof: all
	./cpu-energy-meter -e 100 -d 60 >/dev/null 2>&1
	gprof cpu-energy-meter > cpu-energy-meter.gprof
	rm -f gmon.out
	make clean

.PHONY: format-source
format-source:
	clang-format -i $(SOURCES) $(HEADERS)

.PHONY: dist
dist:
	-rm -rf $(DESTDIR)$(TARGET_BIN)-$(VERSION)
	mkdir $(DESTDIR)$(TARGET_BIN)-$(VERSION)
	cp -r --parents $(SOURCES) $(HEADERS) $(TESTFILES) Makefile $(AUX) $(SCRIPT_DIR) $(VENDOR_DIR) $(DESTDIR)$(TARGET_BIN)-$(VERSION)
	tar cf - $(DESTDIR)$(TARGET_BIN)-$(VERSION) | gzip -9c > $(DESTDIR)$(TARGET_BIN)-$(VERSION).tar.gz
	-rm -rf $(DESTDIR)$(TARGET_BIN)-$(VERSION)

.PHONY: distclean
distclean: clean
	rm -f $(DESTDIR)$(TARGET_BIN)
	-rm -rf $(DESTDIR)$(TARGET_BIN)-[0-9]*.[0-9]*
	-rm -f $(DESTDIR)$(TARGET_BIN)-[0-9]*.[0-9]*.tar.gz

# Keep the following intermediate files after make has been executed
.PRECIOUS: $(OBJ_DIR)%.o

