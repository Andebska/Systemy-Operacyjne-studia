#
# make: runs, rund1, rund2, all, clean, tar 
#
#=========================================================================
DIR = `basename $(CURDIR)`

#------------------------
NAME1 = producent
NAME2 = konsument
NAME3 = macierzysty
#----------------------
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o
#----------------------
EXEC2 = $(NAME2)
OBJS2 = $(NAME2).o
#----------------------
EXEC3 = $(NAME3)
OBJS3 = $(NAME3).o
#----------------------

COFLAGS = -Wall -pedantic -O
LDFLAGS = -Wall -pedantic -O
CO = gcc
LD = $(CO)

#----------------------

LIB_DIR = ./lib
STATIC_LIB = $(LIB_DIR)/libsharedLibrary.a
DYNAMIC_LIB = $(LIB_DIR)/libsharedLibrary.so

#----------------------

#############################
%.o: %.c
	$(CO) $(COFLAGS) -c $<
#############################
.PHONY: all clean tar runs rund1 rund2
#############################
all: $(STATIC_LIB) $(DYNAMIC_LIB) $(EXEC1) $(EXEC2) $(EXEC3)
#############################
$(EXEC1): $(OBJS1) $(STATIC_LIB)
	$(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEC2): $(OBJS2) $(STATIC_LIB)
	$(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEC3): $(OBJS3) $(STATIC_LIB)
	$(LD) -o $@ $(LDFLAGS) $^
#############################
$(STATIC_LIB): sharedLibrary.o
	ar rcs $@ $^
#############################
$(DYNAMIC_LIB): sharedLibrary.o
	$(LD) -shared -o $@ $^
#############################
.PHONY: clean tar
EXECS = $(EXEC1) $(EXEC2) $(EXEC3)
clean:
	rm -f *.o *~ $(EXECS) $(STATIC_LIB) $(DYNAMIC_LIB)

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))

#############################
runs: $(STATIC_LIB) $(EXEC3)
	@echo "Uruchamianie programu z biblioteka statyczna:"
	./$(EXEC3) static
	diff -s prod.txt kons.txt
#############################
rund1: $(DYNAMIC_LIB) $(EXEC3)
	@echo "Uruchamianie programu z biblioteka dynamiczna (opcja 1 - przekazanie lokalizacji przez opcje linkera):"
	./$(EXEC3) dynamic
	diff -s prod.txt kons.txt
#############################
rund2: $(DYNAMIC_LIB) $(EXEC3)
	@echo "Uruchamianie programu z biblioteka dynamiczna (opcja 2 - przekazanie lokalizacji przez zmienna srodowiskowa):"
	LD_LIBRARY_PATH=$(LIB_DIR) ./$(EXEC3) dynamic
	diff -s prod.txt kons.txt
#############################
