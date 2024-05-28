CC = gcc
CFLAGS_COMMON = -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference
CFLAGS_OLD = -Wno-format-overflow
CFLAGS_NEW =

# Détecter la version du compilateur
GCC_VERSION_MAJOR := $(shell $(CC) -dumpversion | cut -f1 -d.)
GCC_VERSION_MINOR := $(shell $(CC) -dumpversion | cut -f2 -d.)

# Vérifier la version du compilateur
# Si la version est 10.2.x, ajouter -Wno-format-overflow
ifeq ($(GCC_VERSION_MAJOR), 10)
    ifeq ($(GCC_VERSION_MINOR), 2)
        CFLAGS = $(CFLAGS_COMMON) $(CFLAGS_OLD)
    else
        CFLAGS = $(CFLAGS_COMMON) $(CFLAGS_NEW)
    endif
else ifeq ($(shell expr $(GCC_VERSION_MAJOR) \>= 14), 1)
    CFLAGS = $(CFLAGS_COMMON) $(CFLAGS_NEW)
else
    CFLAGS = $(CFLAGS_COMMON) $(CFLAGS_NEW)
endif

OBJDIR = output
SRC_DIR = fichiers
SRCS = $(wildcard $(SRC_DIR)/*.c) main.c
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
TARGET = cerjo

# Cible par défaut
all: $(TARGET)

# Création de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# Compilation des fichiers source en objets
$(OBJDIR)/%.o: $(SRC_DIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation du fichier main en objet
$(OBJDIR)/main.o: main.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Création du répertoire des objets s'il n'existe pas
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Exécution de l'exécutable
run:
	./$(TARGET)

# Nettoyage des fichiers objets
clean:
	rm -rf $(OBJDIR)/*.o

# Cibles phony pour éviter les conflits avec des fichiers de même nom
.PHONY: all clean run
