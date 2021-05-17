CC = gcc
CFLAGS = -Wall

APP = psd

BIND = bin
SRCD = src
OBJD = obj
ADDD = add

APPPATH = $(BIND)/$(APP)

CPATH = $(wildcard src/*.c)
OPATH = $(patsubst src/%.c, obj/%.o, $(CPATH))

CAPATH = $(wildcard src/add/*.c)
OAPATH = $(patsubst src/add/%.c, obj/add/%.o, $(CAPATH))

STATICLIBPATH = $(OBJD)/mainlib.a

$(APPPATH) : $(OPATH) $(STATICLIBPATH)
	$(CC) $(CFLAGS) -o $@ $^

$(STATICLIBPATH) : $(OAPATH)
	ar r $@ $^

$(OPATH) : obj/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OAPATH) : obj/add/%.o : src/add/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY : clean
clean :
	$(RM) $(APPPATH) $(STATICLIBPATH)
	find $(OBJD) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJD) -name '*.d' -exec $(RM) '{}' \;