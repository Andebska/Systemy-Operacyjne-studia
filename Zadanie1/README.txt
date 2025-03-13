========================================================================
Autor: Anna Debska,                                   Krakow, 17.03.2024
========================================================================

*Zawartosc:
===========

Katalog programy zawiera piec przykladowych programow w jezyku C:
-----------------------------------------------------------------

I. Program wypisujacy identyfikatory UID, GID, PID, PPID i PGID dla danego procesu.
Program sklada sie z jednego modulu:
1) zadanie_a.c - program glowny

II. Program wywolujacy funkcje fork trzy razy i wypisujacy identyfikatory UID, GID, PID,
 PPID i PGID dla procesu macierzystego i wszystkich procesow potomnych, tak aby proces
 macierzysty przy uzyciu funkcji wait zaczekal na zakonczenie wszystkich procesow potomnych.
Program sklada sie z jednego modulu:
1) zadanie_b.c - program glowny

III. Program wywolujacy funkcje fork trzy razy i wypisujacy identyfikatory UID, GID, PID, PPID 
 i PGID dla procesu macierzystego i wszystkich procesow potomnych, tak aby procesy potomne przy
 uzyciu funkcji sleep byly adoptowane przez proces init.
Program sklada sie z jednego modulu:
1) zadanie_c.c - program glowny

IV. Program wywolujacy funkcje fork trzy razy i wypisujacy identyfikatory UID, GID, PID, PPID 
 i PGID dla procesu macierzystego i wszystkich procesow potomnych, tak aby przy uzyciu funkcji
 sleep procesy pojawialy sie na ekranie grupowane pokoleniami od najstarszego do najmlodszego,
 a proces macierzysty konczyl sie dopiero po procesach potomnych. 
Program sklada sie z jednego modulu:
1) zadanie_d.c - program glowny

V. Program wywolujacy funkcje fork trzy razy i wypisujacy identyfikatory UID, GID, PID, PPID 
 i PGID dla procesu macierzystego i wszystkich procesow potomnych, tak aby ka¿dy proces potomny
 stawal sie liderem swojej w³asnej grupy procesow
Program sklada sie z jednego modulu:1) zadanie_e.c - program glowny

---------------------------------------------------------------------------
Jak uruchomic programy?
->Aby uruchomic 1 program, nalezy wykonac komendy:
	make all; ./zadanie_a
->Aby uruchomic 2 program, nalezy wykonac komendy:
	make all; ./zadanie_b
->Aby uruchomic 3 program, nalezy wykonac komendy:
	make all; ./zadanie_c
->Aby uruchomic 4 program, nalezy wykonac komendy:
	make all; ./zadanie_d
->Aby uruchomic 5 program, nalezy wykonac komendy:
	make all; ./zadanie_e

->Aby wyszyscic zawartosc katalogu nalezy wykonac komende:
	make clean

->W celu archiwizacji oraz kompresji katalogu nalezy wykonac komende:
	make tar
---------------------------------------------------------------------------
Dodatkowe zadania:

c) Osierocone procesy s¹ adoptowane przez proces demon.

d) Drzewo genealogiczne procesow:
   
   Proces macierzysty (PID: 63356, PPID: 62568, PGID: 63356)
   |
   |__ Proces potomny 1 (PID: 63359 , PPID: 63356, PGID: 63356)
   |   |__ Proces potomny 4 (PID: 63409, PPID: 63359, PGID: 63356)
   |   |   |__ Proces potomny 7 (PID: 63424, PPID: 63356, PGID: 63356)
   |   |__ Proces potomny 5 (PID: 63459, PPID: 63409, PGID: 63356)
   |
   |
   |__ Proces potomny 2 (PID: 63485, PPID: 63359, PGID: 63356)
   |
   |
   |__ Proces potomny 3 (PID: 63486, PPID: 63424, PGID: 63356)
       |__ Proces potomny 6 (PID: 63499, PPID: 63356, PGID: 63356)

e) Przy n-krotnym wywylaniu funkcji fork () powstanie 2^n procesow potomnych, poniewaz
   proces macierzyty wchodzac do funkcji fork() prowadzi do powstania dwoch kopii: procesu 
   macierzystego oraz procesu potomnego. Kazdy z powstalych procesow takze moze wejsc do 
   funkcji i spowodowac powstanie kolejnych dwoch procesow (na jeden proces), wiec z kazdym
   kolejnym wywolaniem funkcji procesow bedzie 2 razy wiecej.
