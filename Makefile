# Makefile for ansi linguistica 5.0


CPP = g++
#CFLAGS =  -Wall -g

 
 
all:   read_to_trie.o  trie.h trie.cpp stringcollection.h stringcollection.cpp
	${CPP} -g    read_to_trie.cpp trie.cpp  stringcollection.cpp stringsurrogate.cpp CompareFunc.cpp parse.cpp StringFunc.cpp -o ReadToTrie   

 
#CompareFunc.o: generaldefinitions.h
#	${CPP} ${CFLAGS} -c CompareFunc.cpp


parse.o: parse.h
	${CPP}  ${CFLAGS} -c   parse.cpp

StringFunc.o:     StringFunc.h  stringsurrogate.h stringsurrogate.cpp generaldefinitions.h suffixcollection.cpp
	${CPP} ${CFLAGS} -c   StringFunc.cpp

stringsurrogate.o:   stringsurrogate.h parse.h StringFunc.h  generaldefinitions.h
	${CPP} ${CFLAGS} -c  stringsurrogate.cpp



trie.o:  trie.cpp trie.h stringsurrogate.h generaldefinitions.h
	${CPP} ${CFLAGS}  -c trie.cpp

stringcollection.o: stringcollection.cpp
	${CPP} ${CFLAGS} -c stringcollection.cpp

#CollectionTemplate.o:  CollectionTemplate.h
#	${CPP}  ${CFLAGS} -c   CollectionTemplate.tcc
 
