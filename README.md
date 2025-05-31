# SimpleRISC Assembler

## 🛠️ Project Overview
This project is a **SimpleRISC Assembler** implemented in **C** and **Python**. It converts assembly instructions written for a simplified RISC (Reduced Instruction Set Computing) architecture into corresponding binary machine code. The assembler handles:
- **Instruction translation**: Supports common RISC instructions like `add`, `sub`, `mul`, `div`, `ld`, `st`, `beq`, `bgt`, `call`, and more.
- **Label handling**: Replaces labels with relative offsets during branching operations.
- **Immediate values and registers**: Converts immediate values and registers into binary representations.
- **Error handling**: Detects invalid instructions, incorrect register usage, and format inconsistencies.

## 🔥 Key Features
✅ **Instruction Translation:**  
- Converts RISC assembly instructions into binary machine code.  
- Supports both R-type (register-based) and I-type (immediate value-based) instructions.  

✅ **Label and Branching Support:**  
- Detects labels and replaces them with relative offsets during assembly.  
- Removes comments and trims unnecessary spaces for clean processing.  

✅ **File Handling:**  
- Reads assembly instructions from `.asm` files.  
- Generates binary output in a `.bin` file.  

✅ **Error Reporting:**  
- Provides error messages for invalid instructions or incorrect register usage.  

## 🚀 How to Run
1. Compile the C code using:  
   ```
   gcc -o assembler For brancing and comments.c   "For brancing and comments.c"
   ```
2. Compile the main file using C :
  ```
  gcc -o assembler assembler.c
  ```
3. Run the executable with the assembly file:
  ```
  ./assembler
  ```
## File Structures: 
- `assembler.c`: Core assembler logic for translating instructions into binary.
- `For brancing and comments.c` : Handles label removal, offset calculation, and comment cleaning.
- `frontnew.exe` : Executable version for easy execution (if applicable).
- `input.asm` : Sample input assembly file.
- `output.asm` : Output of file "For branching and Comments.c"
- `output.bin` : Output binary file after assembly.


