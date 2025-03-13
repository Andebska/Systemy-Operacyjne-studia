#
# make: all, clean, tar  
#
#=========================================================================
DIR = `basename $(CURDIR)`

#------------------------
NAME1 = zadanie4
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
.PHONY: all
all: $(EXEC1)
	./$(EXEC1) prod.txt kons.txt
	diff -s prod.txt kons.txt
#############################
$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################

.PHONY: clean tar

clean:                                                     
	rm -f *.o  *~ $(EXEC1)
#=========================================================================
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
#=========================================================================

