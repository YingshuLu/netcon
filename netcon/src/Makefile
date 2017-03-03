SHELL = /bin/sh
CC := g++
BUILDDIR := ./Build/objs
OUTPUT := ../output
ALLDIRS := $(shell ls -R | grep '^\./.*$$' | awk '{gsub(":","");print}')
#vpath %.cpp $(ALLDIRS)
#vpath %.h  $(ALLDIRS)
SRCS := $(foreach dir, $(ALLDIRS), $(wildcard $(dir)/*.cpp))
SRCS += $(wildcard ./*.cpp)
INCS := $(foreach dir, $(ALLDIRS), $(wildcard $(dir)/*.h))
INCS += $(foreach dir, $(ALLDIRS), $(wildcard $(dir)/*.hpp))
OLDOBJS := $(patsubst %.cpp, %.o, $(SRCS))
OBJSLIST := $(notdir $(OLDOBJS))
OBJS := $(foreach obj, $(OBJSLIST), $(BUILDDIR)/$(obj))

CPPFLAGS := -fPIC -shared
INCFLAGS := $(foreach dir, $(ALLDIRS), -I$(dir))

TARGET := $(OUTPUT)/netcon
all:$(TARGET)

$(TARGET):$(SRCS)
	$(CC)  $(INCFLAGS) $^ -o $@

#$(OLDOBJS):%.o:%.cpp
#	$(CC) -c  $(INCFLAGS) $< -o $@

.PHONY: clean cleanall print

print:
	@echo TARGET=$(TARGET)
	@echo OBJSLIST=$(OBJSLIST)
	@echo OBJS=$(OBJS)
	@echo SRCS=$(SRCS)
	@echo PATH=$(PATH)

clean:
	-rm -f $(OBJS) $(OLDOBJS)

cleanall: clean
	-rm -f $(TARGET)
