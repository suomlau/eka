all: kayttaja

kayttaja: dllaskin.o laskin.o kayttaja.o
	g++ dllaskin.o laskin.o kayttaja.o -o kayttaja

dllaskin.o: dllaskin.cpp
	g++ -c dllaskin.cpp

laskin.o: laskin.cpp
	g++ -c laskin.cpp

kayttaja.o: kayttaja.cpp
	g++ -c kayttaja.cpp

clean:
	rm -rf *o kayttaja