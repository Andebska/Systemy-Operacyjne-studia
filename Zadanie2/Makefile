
#
# make: all, clean, tar  
#
#=========================================================================
DIR = `basename $(CURDIR)`

#------------------------
NAME1 = zadanie2
NAME2 = p_potomne
#----------------------
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o
#############################
EXEC2 = $(NAME2)
OBJS2 = $(NAME2).o
#############################

COFLAGS = -Wall -pedantic -O
LDFLAGS = -Wall -pedantic -O
CO = gcc
LD = $(CO)
#############################
%.o: %.c
	$(CO) $(COFLAGS) -c $<
#############################
.PHONY: all
all: $(EXEC1) $(EXEC2)
#############################
$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEC2): $(OBJS2)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################

.PHONY: clean tar

EXECS = $(EXEC1) $(EXEC2)
clean:                                                     
	rm -f *.o  *~ $(EXECS)
#=========================================================================
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
#=========================================================================