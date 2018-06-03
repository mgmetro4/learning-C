# Files and notes used to learn C

## How are C files ran?
1. Source code is saved in a .c file
2. C compiler converts source code to an object file; .o
3. Linker (modern day compilers do this) takes object file and 'links' it to C library files and creates an application; .exe


## Files and Notes


### dummy.c - The smallest, most basic C file. Just an empty main function.

----

### variables.c - Keywords and byte sizes
Sizes using GNU Compiler Collection (GCC) - sizes depend on compiler:
```
      int (4)       char (1)     long (4)      signed
    float (4)     double (8)    short (2)    unsigned
```
  - char's hold single characters within single quotations. Chars are actually type int.
  - doubles are more precise than floats because they use more bits.
  - signed means it can possess a negative value.
  - unsigned means 0 or positive only. Used to increase range in the positive direction.
  - longs lengthen size in bits.
  - shorts shorten size in bits.
  - You cannot have a short or long long double within GCC. Long Double = 12  bytes.
  - long long = 8 bytes. Can't have a short short with GCC.
  - Can't have long or short floats.

----

### io.c - Common Input/Output (I/O) Functions
#### INPUT
1. `getchar()`
   - Fetch a character from the standard input stream. Chars are **type int**.
   - **Stream Oriented**. That means executing several `getchar()` will appear as one to the user if the number of chars given by the user = asked for - 1 because the newline character is saved in the stream. Any extras are kept in the stream and saved for later in order.
   - Exits input catching with a **newline**.

3. `scanf(<placeholder>, <&variable> or <array>)`
   - Cast input from type string to whatever placeholder is used
   - prints input by itself immediately .
   - will only read until the **first whitespace**. Enter is used to end input fetching, however.
   - **Stream Oriented**. Will take from stream first, before asking.

4. `fgets(<array>, <number of chars including final NULL>, <input>=stdin for standard input)`
   - is better because it does not stop at first whitespace
   - **Stream Oriented**. Will read newline character from scanf if scanf is used before hand. Don't forget to clear the buffer!
   - not good for numbers

#### OUTPUT
1. `puts()` - Simply sends strings to output with an automatic newline at the end. Located within `<stdio.h>`
2. `printf()` - Does not automatically include a newline at the end of the string. Can make use of placeholders. Located within `<stdio.h>`.
3. `putchar(<char> or <int>)` - Send an ASCII character to standard output.

**NOTE:** Strings are held in double quotations ("") and single characters are held in single quotations (''). "C" is a string.

  #### Placeholders
  1. `%d` - integers
  2. `%f` - floating-point values
  3. `%s` - strings
  4. `%c` - a single character
  5. `%%` - a percent sign

  #### Escaped Characters
  1. `\n` - newline
  2. `\t` - tab
  3. `\\` - escaped backslash
  4. `\"` - escaped double quotation
  5. `\'` - escaped single quotation. Does not have to be escaped within a string

------

### Math Notes
- Increment Operator = `++`
- Decrement Operator = `--`
- `math.h` contains `sqrt()` - uses floats
- there is no exponent operator! Instead, use `pow(base, power)`

------

### Random Notes
- `stdlib.h` is the Standard Library
- contains `rand()` which produces pseudo random integers. Have to seed the function to get different random values
  - a common trick is to use the computer's inner time value:
    `srand( (unsigned) time(NULL) )`
