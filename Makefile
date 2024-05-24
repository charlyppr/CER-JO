CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference
OBJDIR = output
SRC_DIR = fichiers
SRCS = $(SRC_DIR)/def.c $(SRC_DIR)/athlete.c $(SRC_DIR)/entrainement.c $(SRC_DIR)/historique.c main.c $(SRC_DIR)/statistiques.c
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
TARGET = $(OBJDIR)/cerjo

# Cible par défaut
all: $(TARGET)

# Création de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# Compilation des fichiers source en objets
$(OBJDIR)/%.o: $(SRC_DIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Création du répertoire des objets s'il n'existe pas
$(OBJDIR):
	mkdir -p $(OBJDIR)

run: all
	./$(TARGET)

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)

# Cibles phony pour éviter les conflits avec des fichiers de même nom
.PHONY: all clean run
