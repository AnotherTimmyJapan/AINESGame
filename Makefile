NAME = game
SRC_DIR = src
OBJ_DIR = obj

CC = cc65
AS = ca65
LD = ld65

CFLAGS = -t nes -Oir
ASFLAGS = -t nes
LDFLAGS = -C nes.cfg

# This will find crt0.s AND main.c and turn them into .o files
SOURCES_C = $(wildcard $(SRC_DIR)/*.c)
SOURCES_S = $(wildcard $(SRC_DIR)/*.s)
OBJS = $(OBJ_DIR)/crt0.o $(SOURCES_C:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean

all: $(NAME).nes

# Rule for C files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $(OBJ_DIR)/$*.s
	$(AS) $(ASFLAGS) $(OBJ_DIR)/$*.s -o $@

# Rule for ASM files (like crt0.s)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(OBJ_DIR)
	$(AS) $(ASFLAGS) $< -o $@

# The Linker command now uses $(OBJS) to include EVERYTHING
$(NAME).nes: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) nes.lib -o $@

clean:
	rm -rf $(OBJ_DIR) $(NAME).nes
