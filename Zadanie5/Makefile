#
# make: all, clean, tar, a, b_prod, b_cons 
#
#=========================================================================
DIR = `basename $(CURDIR)`

#------------------------
NAME1 = zad_a
NAME2 = producent
NAME3 = konsument

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
.PHONY: all a b_prod b_cons

b_cons: $(EXEC3)
	xterm -hold -title "Konsument" -e ./$(EXEC3) my_fifo kons2.txt &
#############################
b_prod: $(EXEC2) 
	xterm -hold -title "Producent" -e ./$(EXEC2) my_fifo prod2.txt &
#############################
a: $(EXEC1)
	./$(EXEC1) 
	diff -s prod.txt kons.txt
#############################
all: $(EXEC1) $(EXEC2) $(EXEC3)
#############################
$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEC2): $(OBJS2)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEC3): $(OBJS3)
	 $(LD) -o $@ $(LDFLAGS) $^
	mkfifo my_fifo
#############################


.PHONY: clean tar
EXECS = $(EXEC1) $(EXEC2) $(EXEC3)
clean:                                                     
	rm -f *.o  *~ $(EXECS) my_fifo
	
#=========================================================================
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
#=========================================================================

