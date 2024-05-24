CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference
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
