LNKFLAGS = 

DIREXE = exec/
DIRHEA = include/
DIRSRC = src/

NEXEC1 = JonSnow


all : $(NEXEC1) $(NEXEC2) $(NEXEC3)

$(NEXEC1) : $(DIRSRC)JS.c $(DIRHEA)orders.h
	gcc $(LNKFLAGS) -I $(DIRHEA) -o $(DIREXE)$(NEXEC1) $(DIRSRC)JS.c


