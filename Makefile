# Project Name
NAME = game

# Folders
SRC_DIR = src
OBJ_DIR = obj

# Tools
CC = cc65
AS = ca65
LD = ld65

# Flags
CFLAGS = -t nes -Oir
ASFLAGS = -t nes
LDFLAGS = -C nes.cfg

# Files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
ASMS = $(SOURCES:.c=.s)
OBJS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean

all: $(NAME).nes

# Step 1: Compile C to Assembly
$(SRC_DIR)/%.s: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Step 2: Assemble Assembly to Object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(OBJ_DIR)
	$(AS) $(ASFLAGS) $< -o $@

# Linking - Added -t none so it doesn't try to pull the default library's crt0
$(NAME).nes: $(OBJS)
	$(LD) -C nes.cfg $^ nes.lib -o $@

clean:
	rm -rf $(OBJ_DIR) $(SRC_DIR)/*.s $(NAME).nes
