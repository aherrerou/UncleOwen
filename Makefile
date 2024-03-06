uncleOwen : Android.o Field.o Farm.o Util.o uncleOwen.o
	    g++ -Wall -g Android.o Field.o Farm.o Util.o uncleOwen.o -o uncleOwen

Android.o : Android.cc Android.h
	g++ -Wall -g -c Android.cc
	
Field.o : Field.cc Field.h
	g++ -Wall -g -c Field.cc

Farm.o : Farm.cc Farm.h
	g++ -Wall -g -c Farm.cc
	
Util.o : Util.cc Util.h
	g++ -Wall -g -c Util.cc
	
uncleOwen.o: uncleOwen.cc Farm.h Util.h
		g++ -Wall -g -c uncleOwen.cc
		
