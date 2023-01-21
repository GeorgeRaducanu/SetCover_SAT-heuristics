CC = g++
CFLAGS = -Wall -Wextra -std=c++17
LDFLAGS =

build: trial rise redemption

run_trial:
	./trial

run_rise:
	./rise

run_redemption:
	./redemption

trial: set.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

rise: rise.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

redemption: redemption.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

pack:
	zip -FSr 321CA_RaducanuGeorge.zip *.cpp *.hpp *.h Makefile README

clean:
	rm -f trial rise redemption *.o

.PHONY: pack build clean
