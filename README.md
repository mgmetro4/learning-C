# Files and notes used to learn C

## How are C files ran?
1. Source code is saved in a .c file
2. C compiler converts source code to an object file; .o
3. Linker (modern day compilers do this) takes object file and 'links' it to C library files and creates an application; .exe

### dummy.c
The smallest, most basic C file. Just an empty main function.

----

### outputs.c
Popular functions to send strings to standard output.
1. `puts()` - Simply sends strings to output with an automatic newline at the end. Located within <stdio.h>
2. `printf()` - Does not automatically include a newline at the end of the string. Can make use of placeholders. Located within <stdio.h>.
3. `putchar()`

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
  5. `\'` - escaped single quotation. Does not have to be escaped within a string.
  
  ----

### variables.c
Keywords and byte sizes (sizes can depend on compiler):
```
    int (4)       char (1)       long (4)      signed
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
