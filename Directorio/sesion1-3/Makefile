# Objetivos (targets) de compilación
PROG1 = prog1
PROG2 = prog2
PROG1_O1 = prog1_O1
PROG1_O2 = prog1_O2
PROG1_O3 = prog1_O3
PROG1_PROF = prog1_prof
PROG1_O3_PROF = prog1_O3_prof

# Ficheros objetos
OBJS_PROG1 = prog1.o
OBJS_PROG2 = prog2.o

# Compilador y enlazador
CC = gcc
LD = gcc

# Flags que se le pasan al compilador y al enlazador
FLAGS = -Wall
LDFLAGS =
$(PROG1):         CFLAGS = $(FLAGS)
$(PROG2):         CFLAGS = $(FLAGS)
$(PROG1_O1):      CFLAGS = $(FLAGS) -O1
$(PROG1_O2):      CFLAGS = $(FLAGS) -O1
$(PROG1_O3):      CFLAGS = $(FLAGS) -O1
$(PROG1_PROF):    CFLAGS = $(FLAGS) -pg
$(PROG1_PROF):    LDFLAGS = -pg
$(PROG1_O3_PROF): CFLAGS = $(FLAGS) -O3 -pg
$(PROG1_O3_PROF): LDFLAGS = -pg


# Reglas de compilación de los programas
$(PROG1): $(OBJS_PROG1)

$(PROG2): $(OBJS_PROG2)

$(PROG1_O1): $(OBJS_PROG1)
	$(CC) $(LDFLAGS) $^ -o $@

$(PROG1_O2): $(OBJS_PROG1)
	$(CC) $(LDFLAGS) $^ -o $@

$(PROG1_O3): $(OBJS_PROG1)
	$(CC) $(LDFLAGS) $^ -o $@

$(PROG1_PROF): $(OBJS_PROG1)
	$(CC) $(LDFLAGS) $^ -o $@

$(PROG1_O3_PROF): $(OBJS_PROG1)
	$(CC) $(LDFLAGS) $^ -o $@

# Limpieza
clean :
	rm -f $(OBJS_PROG1) $(OBJS_PROG2)
