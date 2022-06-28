CPP     = g++
CFLAGS  = -std=gnu++11
SRC     = ./src
IDIR    = ./include
_OBJS   = $(patsubst $(SRC)/%.cc, %.o, $(wildcard $(SRC)/*.cc))
OBJDIR := objdir
OBJS	 := $(patsubst %, $(OBJDIR)/%, $(_OBJS))
OPT     = -O2

vpath %.cc $(SRC)
vpath %.hh  $(IDIR)

LIM_p3m_halos: $(OBJS)
	$(CPP) -o $@ $^ $(CFLAGS) $(OPT)

$(OBJDIR)/main.o: main.cc read_halo.hh grid_halo.hh\
									write_map.hh process.hh
	$(CPP) $< -c -o $@ $(CFLAGS) -I$(IDIR) $(OPT)

$(OBJDIR)/read_halos.o: read_halos.cc
	$(CPP) $< -c -o $@ $(CFLAGS) -I$(IDIR) $(OPT)

$(OBJDIR)/grid_halos.o: grid_halos.cc
	$(CPP) $< -c -o $@ $(CFLAGS) -I$(IDIR) $(OPT)

$(OBJDIR)/process.o: process.cc
	$(CPP) $< -c -o $@ $(CFLAGS) -I$(IDIR) $(OPT)

$(OBJDIR)/write_map.o: write_map.cc
	$(CPP) $< -c -o $@ $(CFLAGS) -I$(IDIR) $(OPT)

$(OBJS): | $(OBJDIR)
$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: clean
clean:
	-rm -r LIM_p3m_halos $(OBJDIR)



