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
	$(CPP) -o $@ $^ $(CFLAGS) $(OPT) -fopenmp

$(OBJDIR)/main.o: main.cc process_buffered.hh
	$(CPP) $< -c -o $@ $(CFLAGS) -I$(IDIR) $(OPT)

$(OBJDIR)/process_buffered.o: process_buffered.cc read_halo.hh\
															grid_halo.hh sfr_buffered.hh\
															lum_buffered.hh cic_buffered.hh\
															map.hh
	$(CPP) $< -c -o $@ $(CFLAGS) -I$(IDIR) $(OPT)

$(OBJDIR)/read_halos_buffered.o: read_halos_buffered.cc
	$(CPP) $< -c -o $@ $(CFLAGS) -I$(IDIR) $(OPT)

$(OBJDIR)/grid_halos_buffered.o: grid_halos_buffered.cc
	$(CPP) $< -c -o $@ $(CFLAGS) -I$(IDIR) $(OPT) -fopenmp

$(OBJDIR)/sfr_buffered.o: sfr_buffered.cc
	$(CPP) $< -c -o $@ $(CFLAGS) -I$(IDIR) $(OPT) -fopenmp

$(OBJDIR)/lum_buffered.o: lum_buffered.cc
	$(CPP) $< -c -o $@ $(CFLAGS) -I$(IDIR) $(OPT) -fopenmp

$(OBJDIR)/cloud_in_cell_buffered.o: cloud_in_cell_buffered.cc
	$(CPP) $< -c -o $@ $(CFLAGS) -I$(IDIR) $(OPT)

$(OBJDIR)/Map.o: Map.cc
	$(CPP) $< -c -o $@ $(CFLAGS) -I$(IDIR) $(OPT)

$(OBJS): | $(OBJDIR)
$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: clean
clean:
	-rm -r LIM_p3m_halos $(OBJDIR)

