# Variables
CC = gcc
CFLAGS = -Wall -Werror -I. -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference
OBJDIR = output
DEPS = constants.h
SRCS = athlete.c def.c entrainement.c historique.c main.c statistiques.c struct.c
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
