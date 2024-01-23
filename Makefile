ising: clean_ising ising.out
	@./ising.out

ising.out:
	@clang ising.c rand.c -o ising.out -Wall -Wextra -lraylib -lm

clean_ising:
	@rm -f ising.out


ising_windows: clean_ising_windows ising.exe
	@wine ising.exe

ising.exe:
	@x86_64-w64-mingw32-gcc-win32 ising.c rand.c -o ising.exe -I ./raylib/src -L ./raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm

clean_ising_windows:
	@rm -f ising.exe


pendulum: clean_pendulum pendulum.out
	@./pendulum.out

pendulum.out:
	@clang pendulum.c runge_kutta.c -o pendulum.out -Wall -Wextra -lm

clean_pendulum:
	@rm -f pendulum.out


lorenz: clean_lorenz lorenz.out
	@./lorenz.out

lorenz.out:
	@clang lorenz.c runge_kutta.c -o lorenz.out -Wall -Wextra -lm

clean_lorenz:
	@rm -f lorenz.out


animate_double_pendulum: clean_animate_double_pendulum animate_double_pendulum.out
	@./animate_double_pendulum.out

animate_double_pendulum.out:
	@clang animate_double_pendulum.c runge_kutta.c -o animate_double_pendulum.out -Wall -Wextra -lraylib -lm

clean_animate_double_pendulum:
	@rm -f animate_double_pendulum.out


game_of_life: clean_game_of_life game_of_life.out
	@./game_of_life.out

game_of_life.out:
	@clang game_of_life.c -o game_of_life.out -Wall -Wextra -lraylib -lm

clean_game_of_life:
	@rm -f game_of_life.out


game_of_life_windows: clean_game_of_life_windows game_of_life.exe
	@wine game_of_life.exe

game_of_life.exe:
	@x86_64-w64-mingw32-gcc-win32 game_of_life.c -o game_of_life.exe -I ./raylib/src -L ./raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm

clean_game_of_life_windows:
	@rm -f game_of_life.exe
