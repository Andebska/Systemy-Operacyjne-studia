========================================================================
Autor: Anna Debska,                                   Krakow, 23.03.2024
========================================================================

*Zawartosc:
===========

Katalog Zadanie2 zawiera jeden program w w jezyku C:
-----------------------------------------------------------------

I. Program wywolujacy funkcje fork trzy razy i wypisujacy identyfikatory UID, GID, PID,
 PPID i PGID dla procesu macierzystego i wszystkich procesow potomnych, tak aby proces
 macierzysty przy uzyciu funkcji wait zaczekal na zakonczenie wszystkich procesow potomnych
 oraz aby komunikaty procesow potomnych byly wypisywane przez program uruchamiany przez
 funkcje execlp.

Program sklada sie z dwoch modulow:
1) zadanie2.c - program glowny (program procesu macierzystego)
2) p_potomne.c - program uruchamiany przez funkcje execlp (program procesow potomnych)

---------------------------------------------------------------------------
Jak uruchomic program?
->Aby uruchomic program, nalezy wykonac komendy:
	make all; 
       ./zadanie2 ./p_potomne

->Aby wyszyscic zawartosc katalogu nalezy wykonac komende:
	make clean

->W celu archiwizacji oraz kompresji katalogu nalezy wykonac komende:
	make tar
---------------------------------------------------------------------------
Dodatkowe zadania:

Przy n-krotnym wywolaniu funkcji fork-exec powstanie n procesow potomnych, poniewaz
kazde wywolanie funkcji fork powoduje powstanie dwoch kopii procesow jednak funkcja
exec powoduje zastapienie procesu macierzystego nowym programem wykonywanym przez
proces potomny. W rezultacie kazde wywolanie funkcji fork-exec spowoduje powstanie
tylko jednego procesu potomnego przy kazdym wywolaniu funkcji.