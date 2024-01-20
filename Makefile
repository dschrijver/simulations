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


double_pendulum: clean_double_pendulum double_pendulum.out
	@./double_pendulum.out

double_pendulum.out:
	@clang double_pendulum.c runge_kutta.c -o double_pendulum.out -Wall -Wextra -lm

clean_double_pendulum:
	@rm -f double_pendulum.out


multiple_double_pendulums: clean_multiple_double_pendulums multiple_double_pendulums.out
	@./multiple_double_pendulums.out

multiple_double_pendulums.out:
	@clang multiple_double_pendulums.c runge_kutta.c -o multiple_double_pendulums.out -Wall -Wextra -lm

clean_multiple_double_pendulums:
	@rm -f multiple_double_pendulums.out


animate_double_pendulum: clean_animate_double_pendulum animate_double_pendulum.out
	@./animate_double_pendulum.out

animate_double_pendulum.out:
	@clang animate_double_pendulum.c runge_kutta.c -o animate_double_pendulum.out -Wall -Wextra -lraylib -lm

clean_animate_double_pendulum:
	@rm -f animate_double_pendulum.out
