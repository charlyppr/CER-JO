CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference
OBJDIR = output
DEPS = def.h constants.h struct.h
SRCS = def.c athlete.c entrainement.c historique.c main.c statistiques.c
OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))
TARGET = $(OBJDIR)/cerjo

# Cible par défaut
all: $(TARGET)

# Création de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# Compilation des fichiers source en objets
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Création du répertoire des objets s'il n'existe pas
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)

# Cibles phony pour éviter les conflits avec des fichiers de même nom
.PHONY: all clean