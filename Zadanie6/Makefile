#
# make: all, clean, tar 
#
#=========================================================================
DIR = `basename $(CURDIR)`

#------------------------
NAME1 = powielacz
NAME2 = potomny
NAME3 = test

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
#############################
all: $(EXEC1) $(EXEC2) $(EXEC3)
#############################
$(EXEC1): $(OBJS1) sem_lib.o
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEC2): $(OBJS2) sem_lib.o
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEC3): $(OBJS3) sem_lib.o
	 $(LD) -o $@ $(LDFLAGS) $^
#############################

sem_lib.o: sem_lib.c
	$(CO) $(COFLAGS) -c $< -o $@
#############################
.PHONY: clean tar
EXECS = $(EXEC1) $(EXEC2) $(EXEC3)
clean:                                                     
	rm -f *.o  *~ $(EXECS) *.txt
	
#=========================================================================
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
#=========================================================================

