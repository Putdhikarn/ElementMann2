
game.exe:
	gcc -o ./build/game.exe main.c game_struct.c game.c map.c tileset.c sprite.c player.c projectile.c level.c enemy.c camera.c -I include -L lib -lraylib -lgdi32 -lwinmm -O2
