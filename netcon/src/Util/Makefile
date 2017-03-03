SHELL = /bin/sh
CC := g++
BUILDDIR := ../Build/objs
ALLDIRS := $(shell ls -R | grep '^\./.*$$' | awk '{gsub(":","");print}')
SRCS := $(foreach dir, $(ALLDIRS), $(wildcard $(dir)/*.cpp))
INCS := $(foreach dir, $(ALLDIRS), $(wildcard $(dir)/*.h))
INCS += $(foreach dir, $(ALLDIRS), $(wildcard $(dir)/*.hpp))
OLDOBJS := $(patsubst %.cpp, %.o, $(SRCS))
OBJSLIST := $(notdir $(OLDOBJS))
OBJS := $(foreach obj, $(OBJSLIST), $(BUILDDIR)/$(obj))


CPPFLAGS := -fPIC -shared
INCFLAGS := $(foreach dir, $(ALLDIRS), -I$(dir))

all:$(OBJS)

$(OBJS):$(SRCS)
	$(CC) -c $(INCFLAGS) $< -o $@


.PHONY: clean cleanall print

print:
	@echo OBJSLIST=$(OBJSLIST)
	@echo OBJS=$(OBJS)
	@echo SRCS=$(SRCS)
clean:
	-rm -f $(OBJS)

cleanall: clean
