ising: clean_ising ising.out
	@./ising.out

ising.out:
	@clang ising.c rand.c -o ising.out -Wall -Wextra -lm

clean_ising:
	@rm -f ising.out

pendulum: clean_pendulum pendulum.out
	@./pendulum.out

pendulum.out:
	@clang pendulum.c runge_kutta.c "gnuplot_i/gnuplot_i.c" -o pendulum.out -Wall -Wextra -lm

clean_pendulum:
	@rm -f pendulum.out

lorenz: clean_lorenz lorenz.out
	@./lorenz.out

lorenz.out:
	@clang lorenz.c runge_kutta.c "gnuplot_i/gnuplot_i.c" -o lorenz.out -Wall -Wextra -lm

clean_lorenz:
	@rm -f lorenz.out
