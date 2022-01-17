fp:	main.o deque.o fighter.o fightspecs.o runspecs.o stats.o
	gcc -o fp main.o deque.o fighter.o fightspecs.o runspecs.o stats.o -lpthread



main.o:	main.c defs.h
	gcc -c main.c

deque.o:	deque.c defs.h
	gcc -c deque.c

fighter.o:	fighter.c defs.h
	gcc -c fighter.c

fightspecs.o:	fightspecs.c defs.h
	gcc -c fightspecs.c

runspecs.o:	runspecs.c defs.h
	gcc -c runspecs.c

stats.o:	stats.c defs.h
	gcc -c stats.c

clean:
	rm -f main.o deque.o fighter.o fightspecs.o runspecs.o stats.o fp
