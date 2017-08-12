@echo off
echo Start to compile ...

if exist "%1.c" if exist "PreProcessor.exe" PreProcessor.exe %1.c %1.pp.c & echo 1. PreProcessing finished!
if not exist "%1.c" echo %1.c does not exist! & exit /b
if not exist "PreProcessor.exe" echo PreProcessor.exe does not exist! & exit /b

if exist "%1.pp.c" if exist "Scanner.exe" Scanner.exe %1.pp.c %1.token.xml & echo 2. Tokenization finished!
if not exist "%1.pp.c" echo %1.pp.c does not exist! & exit /b
if not exist "Scanner.exe" echo Scanner.exe does not exist! & exit /b

if exist "%1.token.xml" if exist "Parser.exe" Parser.exe %1.token.xml %1.tree.xml & echo 3. Parsing finished!
if not exist "%1.token.xml" echo Parser or %1.token.xml does not exist! & exit /b
if not exist "Parser.exe" echo Parser.exe does not exist! & exit /b

if exist "%1.tree.xml" if exist "SemanticAnalyser.exe" SemanticAnalyser.exe %1.tree.xml %1.tree2.xml & echo 4. Semantic Analysis finished!
if not exist "%1.tree.xml" echo %1.tree.xml does not exist! & exit /b
if not exist "SemanticAnalyser.exe" echo SemanticAnalyser.exe does not exist! & exit /b

if exist "%1.tree2.xml" if exist "IR_Generator.exe" IR_Generator.exe %1.tree2.xml %1.ir.xml & echo 5. Intermediate Representation generation finished!
if not exist "%1.tree2.xml" echo %1.tree2.xml does not exist! & exit /b
if not exist "IR_Generator.exe" echo IR_Generator.exe does not exist! & exit /b

if exist "%1.ir.xml" if exist "Optimizer.exe" Optimizer.exe %1.ir.xml %1.ir2.xml & echo 6. Optimization finished!
if not exist "%1.ir.xml" echo %1.ir.xml does not exist! & exit /b
if not exist "Optimizer.exe" echo Optimizer.exe does not exist! & exit /b

if exist "%1.ir2.xml" if exist "Code_Generator.exe" Code_Generator.exe %1.ir2.xml %1.code.s & echo 7. RISC Code generation finished!
if not exist "%1.ir2.xml" echo %1.ir2.xml does not exist! & exit /b
if not exist "Code_Generator.exe" echo Code_Generator.exe does not exist! & exit /b

echo Compiling completed!