OBJS = parser.tab.o lex.re2c.o main.o

calc: $(OBJS)
	   $(CC) -o calc $(OBJS)

parser.tab.c: parser.y
			bison -d -b parser parser.y

lex.re2c.c: lex.re
			re2c -i -o lex.re2c.c lex.re

clean:
	rm *.o lex.re2c.c parser.tab.c parser.tab.h
