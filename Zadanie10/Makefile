#
# make: all, run, clean, tar
#
#=========================================================================
DIR = `basename $(CURDIR)`

#------------------------
NAME1 = zadanie10

#----------------------
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o
#----------------------

#############################
COFLAGS = -Wall -pedantic 
LDFLAGS = -Wall -pedantic  
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
	 $(LD) $(LDFLAGS) -o $@ $^
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

