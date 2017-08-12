#!/bin/bash

echo "Start to compile ..."

if [ -f $1.c -a -e PreProcessor ]
then
	./PreProcessor $1.c $1.pp.c
	echo "1. PreProcessing finished!"
else 
	echo "PreProcessor or $1.c does not exist!"
	exit
fi

if [ -f $1.pp.c -a -e Scanner ]
then
	./Scanner $1.pp.c $1.token.xml
	echo "2. Tokenization finished!"
else
	echo "Scanner or $1.pp.c does not exist!"
	exit
fi

if [ -f $1.token.xml -a -e Parser ]
then
	./Parser $1.token.xml $1.tree.xml
	echo "3. Parsing finished!"
else
	echo "Parser or $1.token.xml does not exist!"
	exit
fi

if [ -f $1.tree.xml -a -e SemanticAnalyser ]
then
	./SemanticAnalyser $1.tree.xml $1.tree2.xml
	echo "4. SemanticAnalyser Analysis finished!"
else
	echo "SemanticAnalyser or $1.tree.xml does not exist!"
	exit
fi

if [ -f $1.tree2.xml -a -e IR_Generator ]
then
	./IR_Generator $1.tree2.xml $1.ir.xml
	echo "5. Intermediate code generate finished!"
else
	echo "IR_Generator or $1.tree2.xml does not exist!"
	exit
fi

if [ -f $1.ir.xml -a -e Optimizer ]
then
	./Optimizer $1.ir.xml $1.ir2.xml
	echo "6. Optimization finished!"
else
	echo "Optimizer or $1.ir.xml does not exist!"
	exit
fi

if [ -f $1.ir2.xml -a -e Code_Generator ]
then
	./Code_Generator $1.ir2.xml $1.code.s
	echo "7. RISC Code generate finished!"
else
	echo "Code_Generator or $1.ir2.xml does not exist!"
	exit
fi

echo "Compiling completed!"