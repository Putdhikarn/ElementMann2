CC = gcc
CFLAGS = -I include -O2
LDFLAGS = -L lib -lraylib -lgdi32 -lwinmm

SRCS = main.c game_struct.c game.c map.c tileset.c sprite.c player.c projectile.c level.c enemy.c camera.c
OBJDIR = build/obj
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

TARGET = build/game.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
