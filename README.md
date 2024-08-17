# IAS Machine Simulation

## Overview

This project simulates an IAS (Institute for Advanced Study) machine, a theoretical computer model designed in the 1950s. The simulation includes basic operations such as load, store, arithmetic operations, jumps, and custom factorial and comparison functions. The machine uses a simple instruction set to perform operations on memory.Assembly code for pemutations is also given for your convenience.

## Instructions Format

The instruction format is defined as follows:

- **LHS**: Left-hand side of the instruction, used for certain operations.
- **RHS**: Right-hand side of the instruction, used for certain operations.
- **Data**: Holds data for memory operations.

## Registers

- **MainMemory**: Array to simulate the main memory of the machine.
- **PC**: Program Counter array to keep track of instruction addresses.
- **MAR**: Memory Address Register.
- **IR**: Instruction Register.
- **IBR**: Instruction Buffer Register.
- **MBR**: Memory Buffer Register.
- **ACC**: Accumulator Register.
- **MQ**: Multiplier Quotient Register.
- **PC_index**: Index for the Program Counter array.
- **left_flag**: Flag indicating if the instruction is for the left side.

## Functions

- `Fact(int n)`: Computes the factorial of a number `n`.
- `fetch(int value_at_pc)`: Fetches the instruction from memory based on the Program Counter value.
- `decode_execute(int IR, int MAR)`: Decodes and executes the instruction based on the opcode in the Instruction Register.
- `PrintStatus_Instruction()`: Prints the status of the instruction registers.
- `PrintStatus_Exectuion()`: Prints the status of the execution including ACC, MQ, and MBR.
- `permutate(int n, int r)`: Computes permutations of `n` and `r`.

## Instructions

### Memory-Based Instructions

- **LoadMQ**: Transfers the value of MQ to ACC.
- **STOR M(X)**: Stores the value of ACC into memory location M(X).
- **LOAD M(X)**: Loads the value from memory location M(X) into ACC.
- **-LOAD M(X)**: Loads the negated value from memory location M(X) into ACC.
- **LOAD -| M(X)|**: Loads the negative absolute value from memory location M(X) into ACC.
- **LOAD |M(X)|**: Loads the absolute value from memory location M(X) into ACC.

### Jump-Based Instructions

- **JUMP to LHS M(X)**: Jumps to the left-hand side instruction.
- **JUMP to RHS M(X)**: Jumps to the right-hand side instruction.
- **JUMP TO LHS M(X) if AC is non-negative**: Conditional jump based on the value of ACC.
- **JUMP to RHS M(X) if AC is non-negative**: Conditional jump based on the value of ACC.

### Modified Store Instructions

- **add M(X)**: Adds the value from memory location M(X) to ACC.
- **add |M(X)|**: Adds the absolute value from memory location M(X) to ACC.
- **sub M(X)**: Subtracts the value from memory location M(X) from ACC.
- **sub |M(X)|**: Subtracts the absolute value from memory location M(X) from ACC.
- **Left Shift**: Performs a left shift on ACC.
- **Right Shift**: Performs a right shift on ACC.
- **MUL M(x)**: Multiplies ACC by the value from memory location M(X).
- **DIV M(X)**: Divides ACC by the value from memory location M(X).

### New Instructions

- **FACT M(x)**: Computes the factorial of the value from memory location M(X) and stores it in ACC.
- **COMPARE M(x)**: Compares ACC with the value from memory location M(X) and adjusts PC_index if needed.

## Usage

1. Compile the code using a C compiler.
2. Run the executable.
3. Follow the on-screen instructions to compute permutations or switch off the machine.

## Example

To compute permutations of `n` and `r`:

1. Select option 1.
2. Enter the values of `n` and `r`.
3. The machine will display the number of permutations.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

