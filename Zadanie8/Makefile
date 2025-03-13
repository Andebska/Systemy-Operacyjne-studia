#
# make: all, run, clean, tar
#
#=========================================================================
DIR = `basename $(CURDIR)`

#------------------------
NAME1 = serwer
NAME2 = klient

#----------------------
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o
#----------------------
EXEC2 = $(NAME2)
OBJS2 = $(NAME2).o
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

run: $(EXEC1) $(EXEC2)
	xterm -hold -title SERWER -bg grey -fg black -e ./$(EXEC1) &
	xterm -hold -title KLIENT1 -bg pink -fg black -e ./$(EXEC2) &
	xterm -hold -title KLIENT2 -bg pink -fg black -e ./$(EXEC2) &
#############################
all: $(EXEC1) $(EXEC2) 
#############################
$(EXEC1): $(OBJS1) mq_library.o
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEC2): $(OBJS2) mq_library.o
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
mq_library.o: mq_library.c
	$(CO) $(COFLAGS) -c $< -o $@
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

