# DIRS
INCDIR = include
BINDIR = bin
SRCDIR = src
BUILDDIR = build
LIBDIR = lib
# LIB OPTIONS
# TARGET
TARGET = $(BINDIR)/gremlins
# EXTENSIONS
SRCEXT = cpp
HEADEREXT = hpp
# SOURCES LIST
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
# OBJECTS
OBJS = $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))
# COMPILER
CC = g++
# FOR CLEANING
RM = /bin/rm
# WARNING FLAG
WARN = -Wall
# DEBUG FLAGS
DEBUG = -g
COMPRESS = -O3
# LINKING FLAGS
INCFLAG = -I $(INCDIR)
LFLAGS = $(DEBUG) $(WARN) $(INCFLAG)
TEST_TYPE = 1
# COMPILATION FLAGS
CFLAGS = $(DEBUG) $(COMPRESS) -c $(WARN) -D_TEST_TYPE_=$(TEST_TYPE) -std=c++11

# ----------------------
# ENTRIES
# ----------------------

main: $(TARGET)

# Main Version
$(TARGET): $(OBJS)
	@echo "Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LFLAGS)"; $(CC) $^ -o $(TARGET) $(LFLAGS)
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INCFLAG) -o $@ $<"; $(CC) $(CFLAGS) $(INCFLAG) -o $@ $<

# DUMMY ENTRIES
clean:
	@echo "Cleaning..."
	@echo " $(RM) -r $(OBJS) $(TARGET)"; $(RM) -r $(OBJS) $(TARGET)

.PHONY: clean
