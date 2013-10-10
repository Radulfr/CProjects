LNKFLAGS = 

DIREXE = exec/
DIRHEA = include/
DIRSRC = src/

NEXEC1 = TyrionGame


all : $(NEXEC1) $(NEXEC2) $(NEXEC3)

$(NEXEC1) : $(DIRSRC)Juego.c $(DIRHEA)orders.h
	gcc $(LNKFLAGS) -I $(DIRHEA) -o $(DIREXE)$(NEXEC1) $(DIRSRC)Juego.c


