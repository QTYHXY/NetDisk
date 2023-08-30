src = $(wildcard *.c,../share/wrap.c)
obj = $(patsubst ./%.c, ./%.o, $(src))  # ./obj/add.o ./obj/sub.o ...

PWD = $(shell pwd)

CPPFLAGS += -I $(PWD)/../../inc/client

LDFLAGS += -L $(PWD)/../../lib
LDFLAGS += -lui

a.out: $(obj)
	gcc $^ -o $@ $(myArgs) 

$(obj):./obj/%.o:./src/%.c
	gcc -c $< -o $@ $(myArgs) -I $(inc_path)  

clean:
	-rm -rf $(obj) a.out

.PHONY: clean ALL