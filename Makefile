FAKELIBC = ./fake_libc_include
SRC=$(wildcard in/*.c)
GENERATED=$(patsubst in/%.c, out/%.c, $(SRC))

all : $(GENERATED) tags parse

out/%.c : in/%.c
	gcc -nostdinc -E -std=c99 -D'__attribute__(x)=' -D'__MX_LIBRARY__' -Iinclude -I$(FAKELIBC) $< > $@ || rm $@

tags : $(wildcard in/*)
	ctags -R in/

parse : $(GENERATED)
	python just_parse.py out/*.c

clean :
	rm -f out/*.c tags
