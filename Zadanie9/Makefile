#
# make: all, run, clean, tar
#
#=========================================================================
DIR = `basename $(CURDIR)`

#------------------------
NAME1 = watki

#----------------------
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o
#----------------------

#############################
COFLAGS = -Wall -pedantic -O
LDFLAGS = -Wall -pedantic -O
CO = gcc
LD = $(CO)
#############################
%.o: %.c
	$(CO) $(COFLAGS) -c $<
#############################
.PHONY: all run

run: $(EXEC1)
	./$(EXEC1)
#############################
all: $(EXEC1)
#############################
$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
.PHONY: clean tar
EXECS = $(EXEC1)
clean:                                                     
	rm -f *.o  *~ $(EXECS)
	
#=========================================================================
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
#=========================================================================

