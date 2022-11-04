# Target library
lib := libuthread.a
objs	:= queue.o context.o preempt.o uthread.o
#dfiles := queue.d

CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
#CFlags	+= -g
# deps adapted code from professor makefile
#deps := $(patsubst %.o,%.d,$(objs))
#-include $(deps)

all: $(lib)

## TODO: Phase1

$(lib): $(objs)
	ar rcs libuthread.a $(objs)
#do the ars thingy

%.o: %.c queue.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(all) $(objs)

