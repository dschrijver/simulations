ising: clean_ising ising.out
	@./ising.out

ising.out:
	@clang ising.c rand.c -o ising.out -Wall -Wextra -lm

clean_ising:
	@rm -f ising.out

rungekutta: clean_rungekutta rungekutta.out
	@./rungekutta.out

rungekutta.out:
	@clang rungekutta.c "../gnuplot_i/gnuplot_i.c" -o rungekutta.out -Wall -Wextra

clean_rungekutta:
	@rm -f rungekutta.out
