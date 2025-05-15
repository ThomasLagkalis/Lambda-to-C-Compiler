# Lambda to C Compiler: Language Syntax Reference

## Compilation and Execution

To compile, run the following code:

```bash
make bison
```

This produces the executable mycompiler.Then touch a ```.la``` file (e.g. ```example.la```) and write in it your lambda code. Finally, to execute the translation run:

```bash
./mycompiler < example.la
``` 

## Requirements
- **Flex**: For lexical analysis (token generation)
- **Bison**: For syntactic analysis (parsing)
- **GCC**: For compiling the generated C code
- **C99 Standard**: Target compilation standard

## Lambda Language description

### Identifiers
- Start with a letter, followed by letters, digits, or underscores
- Cannot be keywords (case-sensitive)

### Keywords
`integer`, `scalar`, `str`, `bool`, `True`, `False`, `const`, `if`, `else`, `endif`, `for`, `in`, `endfor`, `while`, `endwhile`, `break`, `continue`, `not`, `and`, `or`, `def`, `enddef`, `main`, `return`, `comp`, `endcomp`, `of`

### Constants
- **Integer**: `42` (no leading zeros)
- **Float**: `3.14`, `1e-5`
- **Boolean**: `True`, `False`
- **String**: `"text"` with `\n`, `\t`, `\\`, `\"` escapes

### Operators & Delimiters
- Arithmetic: `+`, `-`, `*`, `/`, `%`, `**`
- Relational: "==", "!=", "<", "<=", ">", ">="
- Logical: `and`, `or`, `not`
- Assignment: `=`, `+=`, `-=`, `*=`, `/=`, `%=`
- Delimiters: `;`, `()`, `,`, `[]`, `:`

## Program Structure
```lambda
-- Optional declarations
comp MyType: #x:integer; endcomp;
const PI = 3.14: scalar;

-- Required main function
def main():
    x: integer = 1;
    writeInt(x);
enddef;
