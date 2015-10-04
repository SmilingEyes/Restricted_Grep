# Your program must compile with 'make'
# You must not change this file.

CC = gcc
FLAGS = -std=c99 -O0 -Wall -Werror -g -pedantic 

rgrep: 
	$(CC) $(FLAGS) rgrep.c -o rgrep

clean:
	rm -rf rgrep *.dSYM

check: clean rgrep
	test "`echo "getrekt.txt" | ./rgrep 'getrekt'`" = "getrekt.txt" 
	test "`echo "l\nr.txt" | ./rgrep 'l'`" = "l"
	test "`echo "lorem" | ./rgrep '........'`" = ""
	test "`echo "godzillaaaaaaaa.firebeam" | ./rgrep 'godzilla+.firebeam'`" = "godzillaaaaaaaa.firebeam"
	test "`echo "kelvinlwinatucm" | ./rgrep 'kelvinlwin..ucm'`" = "kelvinlwinatucm"
	test "`echo "iamscrewed.tiff" | ./rgrep 'iamscrewed.tif+'`" = "iamscrewed.tiff"
	test "`echo "minimum" | ./rgrep 'mi?nimum'`" = "minimum"
	test "`echo "abracadabra" | ./rgrep 'a?bra'`" = "abracadabra"
	test "`echo "logoless.c++" | ./rgrep 'logoles..c\+\+'`" = "logoless.c++"
	test "`echo "GGOODD" | ./rgrep '.+.+.+'`" = "GGOODD"
	test "`echo "ile.de" | ./rgrep 'ile\.de'`" = "ile.de"
	test "`echo "ile.de" | ./rgrep '.+?ile.?+.de'`" = "ile.de"
	test "`echo "ile.de" | ./rgrep '...\.d?e?'`" = "ile.de"
	test "`echo "aa" | ./rgrep 'a?a'`" = "aa"	
	test "`echo "pow" | ./rgrep 'pow'`" = "pow"
	test "`echo "aa" | ./rgrep 'a?a+'`" = "aa"	
	@echo "Passed sanity check or base cases! "
