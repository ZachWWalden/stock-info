CFLAGS=-Wall -O3 -g -Wextra -Wno-unused-parameter
CXXFLAGS=$(CFLAGS) -std=c++11
OBJDIR = .build
#SRCS != find . -name "*.cpp"
SRCS=stock-info-main.cpp
OBJDIRS=$(SUBDIRS:%=$(OBJDIR)/%)
OBJECTS := $(SRCS:%.cpp=$(OBJDIR)/%.o)
TARGET=stock-info

DEPDIR = .dep
DEPDIRS=$(SUBDIRS:%=$(DEPDIR)/%)
DEPS := $(SRCS:%.cpp=$(DEPDIR)/%.d)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

# Where our library resides. You mostly only need to change the
# RGB_LIB_DISTRIBUTION, this is where the library is checked out.
RGB_LIB_DISTRIBUTION=..
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

all : $(TARGET)

$(RGB_LIBRARY): FORCE
	@echo "Building RGB Library"
	$(MAKE) -C $(RGB_LIBDIR)

# All the binaries that have the same name as the object file.q
% : %.o $(RGB_LIBRARY)
	@echo "RGB Library"
	$(CXX) $< -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp | $(DEPDIR) $(OBJDIR)
	@echo "Building $@"
	$(CXX) -I$(RGB_INCDIR) -c $(CXXFLAGS) $(DEPFLAGS) -o $@ $<

$(TARGET): $(RGB_LIBRARY) $(OBJECTS)
	@echo "Creating Binary"
	$(CXX) $^ -o $@ $(LDFLAGS)

clean:
	@rm -rf $(OBJDIR) $(DEPDIR) $(TARGET)

FORCE:
.PHONY: FORCE

$(DEPDIR) $(OBJDIR):
	mkdir -p $@
	mkdir -p $(DEPDIRS) $(OBJDIRS)

$(DEPFILES):

include $(wildcard $(DEPFILES))
