########################
# GENERIC C++ MAKEFILE #
# -------------------- #
#     By Sam Gibson    #
#        24/4/17       #
########################

IDIR = include
SDIR = Src
CC = g++
CFLAGS = -I$(IDIR) -Wall -std=c++11 -g

PROJ_NAME = omdbcpp

ODIR = obj
LDIR = lib

BUILDDIR = build

LIBS = 

DEPS := $(shell find $(IDIR) -name '*.h')

SOURCES := $(shell find $(SDIR) $(LDIR) -name '*.cpp')

OBJECT_FILES = $(SOURCES:%.cpp=$(ODIR)/%.o)

MKDIR_P = mkdir -p

# OBJ = $(addprefix $(ODIR)/, $(notdir $(SOURCES:%.cpp=%.o)))

.PHONY: clean directories

all: $(PROJ_NAME)
	@echo Copying assets...
	@mkdir -p $(BUILDDIR)/$(ASSETDIR)
	cp -a $(ASSETDIR)/. $(BUILDDIR)/$(ASSETDIR)
	@echo Build success!

$(PROJ_NAME): $(OBJECT_FILES)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -o $(BUILDDIR)/$(PROJ_NAME) $^ $(LIBS) -L$(LDIR)

$(OBJECT_FILES): $(ODIR)/%.o: %.cpp $(DEPS)
	@echo Compiling $<
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(PROJ_NAME)
	rm -rf $(BUILDDIR)
	find $(ODIR) -type f -name '*.o' -delete