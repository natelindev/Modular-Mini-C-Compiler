# Modular-Mini-C-Compiler

## Introduction

This is a modular mini C compiler.

It can translate a subset of C language into MIPS assembly language.

Currently it's unfinished ,there are still a lot of work to do. Help is welcomed.

Basic Module Functions are as follows.

**PreProcessor**: delete comments.

**Scanner**:  Tokenize the input stream.

**Parser**: Generate Parse tree.

**SemanticAnalyser**: Reduce the size and length of parse tree, make it into AST.

**IR_Generator**: Translate the AST into IR (Intermediate Representation). In this case, we use linear three address IR.

**Optimizer**: Not yet implemented. Will function as IR optimizer in order to reduce Time/Space Complexity in the future.

**Code_Generator**: Generate RISC assembly code from IR.

**XML_suit**: Parse the XML input and Generate the XML output. Note that XML format can be found at `XML_examples` directory.

*[Warning] There are still a lot of work to be done, currently the XML input and output of each module is handled by the their own version of XML suit, this will be fixed in the future.* 



## Usage

Suppose you have a file named test.c

<u>Put the module binary in the root directory, and then</u> (eg. `Scanner.exe`)

#### Windows

```powershell
run.bat test
```

#### Unix(Including macOS & Linux)

```shell
$./run.sh test
```

If it prompts that the permission is denied.

Please execute this command first:

```Shell
$chmod 755 run.sh
```



## Thanks

Inspired by [bit-minic-compiler](https://github.com/jiweixing/bit-minic-compiler)  



## Disclaimer

- No code from bit-mini-compiler is taken to this project
- This project is for educational purpose only,  I'm not responsible for the consequences of error assembly code it generated.

