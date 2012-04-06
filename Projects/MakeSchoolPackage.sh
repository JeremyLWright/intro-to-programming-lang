#!/bin/sh
FOLDERNAME=1000738685_jeremy_p2
rm -rf $FOLDERNAME
mkdir $FOLDERNAME
flex -o$FOLDERNAME/XLexer.cpp --header-file=$FOLDERNAME/XLexer.hpp Xlanguage.l 
bison -o$FOLDERNAME/XParser.cpp -d XGrammar.y
cp *.cpp $FOLDERNAME
cp *.h $FOLDERNAME
cp Makefile_Template $FOLDERNAME/Makefile
zip -b . $FOLDERNAME $FOLDERNAME/*
