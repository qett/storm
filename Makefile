MODULES := rain demo
CFLAGS	+= $(patsubst %, -I%, $(MODULES)) -std=c++11 -stdlib=libc++
LIBS	:= -lGL -lGLU -lglfw -lGLEW
SRC	:=

.PHONY: clean distclean all

include $(patsubst %, %/module.mk, $(MODULES))

OBJ := $(patsubst %.cc, %.o, $(filter %.cc, $(SRC)))

ldemo: $(OBJ)
	clang++ -std=c++11 -stdlib=libc++ $(OBJ) -o $@ $(LIBS)

ifneq "$(MAKECMDGOALS)" "clean"
ifneq "$(MAKECMDGOALS)" "distclean"

include $(OBJ:.o=.d)

endif
endif

%.o: %.cc
	clang++ -c $(CFLAGS) -o $@ $<

%.d: %.cc
	./calcdeps.sh `dirname $*.cc` $(CFLAGS) $*.cc > $@

distclean: clean
	rm -f $(OBJ:.o=.d)

clean:
	rm -f $(OBJ)
	rm -f ldemo




