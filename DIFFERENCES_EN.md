# Differences from Original Windows Calculator Implementation

This document describes the main differences between this calculator implementation and the standard Windows Calculator.

## Implemented Features

### Basic Arithmetic Operations
- ✅ **Addition (+)** - Fully implemented
- ✅ **Subtraction (-)** - Fully implemented
- ✅ **Multiplication (*)** - Fully implemented
- ✅ **Division (/)** - Fully implemented with zero division check

### Input and Editing Operations
- ✅ **Digit Input (0-9)** - Fully implemented
- ✅ **Decimal Point (.)** - Implemented with protection against double input
- ✅ **Sign Change (+/-)** - Fully implemented
- ✅ **Backspace (⌫)** - Implemented to delete the last digit
- ✅ **CE (Clear Entry)** - Clears current input
- ✅ **C (Clear)** - Complete calculator reset

### Display Features
- ✅ **Thousands Separators** - Automatic comma insertion (1,234,567)
- ✅ **Auxiliary Field** - Operation history display
- ✅ **Dynamic Font Sizing** - Automatic reduction for long numbers
- ✅ **16 Character Limit** - Overflow protection

### Logic Features
- ✅ **Repeated "=" Press** - Repeats the last operation
- ✅ **Chain Operations** - Support for sequential calculations
- ✅ **Zero Trimming** - Automatic removal of insignificant trailing zeros

## Unimplemented Features

### Advanced Operations
- ❌ **Percent (%)** - Button present but function not implemented
  - Defined in `operations_t` enum as `PERCENT`
  - Has empty case in switch statement
  - Not connected to GUI (line 153 commented out)

- ❌ **Reciprocal (1/x)** - Not implemented
  - Button present in GUI
  - No corresponding enum value
  - Not connected to handler (line 157 commented out)

- ❌ **Square (x²)** - Not implemented
  - Button present in GUI
  - `SQR` exists in enum but unused
  - Not connected to handler (line 158 commented out)

- ❌ **Square Root (√x)** - Not implemented
  - Button present in GUI
  - `SQRT` exists in enum but unused
  - Not connected to handler (line 159 commented out)

### Missing Windows Calculator Features
This implementation does **not** include the following features from the full Windows Calculator:
- ❌ Memory functions (M+, M-, MR, MC, MS)
- ❌ Scientific mode (sin, cos, tan, log, ln, exp, etc.)
- ❌ Programmer mode (bitwise operations, number systems)
- ❌ Calculation history
- ❌ Unit converter
- ❌ Date calculation
- ❌ Parentheses support for complex expressions

## Implementation Differences

### Architectural Features

1. **Separation of Logic and Interface**
   - Calculator logic in separate files (`CalcLogic.cpp`, `CalcLogic.h`)
   - GUI implemented using Qt6
   - `BackEndWrapper` class bridges GUI and logic

2. **Number Format**
   - Uses comma (,) as thousands separator
   - Uses dot (.) as decimal separator
   - Windows Calculator uses system locale

3. **String Handling**
   - Internal representation via `std::string`
   - `add_commas()` function for formatting
   - `remove_str_from_str()` function for cleanup

4. **Expression Parsing**
   - Simple parser in `perform_calc()` function
   - Handles strings in format "number operation number ="
   - Does not use stack or expression tree

### Implementation Limitations

1. **Only One Operation at a Time**
   - Does not support complex expressions like "2 + 3 * 4"
   - Each operation executes immediately when entering the next one

2. **Limited Precision**
   - Uses `double` for calculations
   - 16 character input limit
   - May lose precision with large numbers

3. **Simplified Error Handling**
   - Only checks for division by zero
   - No overflow checking
   - No invalid input handling

## User Interface Features

### Implemented
- Adaptive window size (360-550 pixels)
- Automatic font scaling (48 to 60 pixels)
- 4x6 button grid
- Two displays (main and auxiliary)

### Differences from Windows Calculator
- Simplified design without themes
- No animations
- Fixed button set
- No dropdown menu
- No operation history in sidebar

## Testing

The project includes unit tests using CppUTest framework:
- Number input tests
- Arithmetic operation tests
- Editing operation tests (CE, C, Backspace)
- Sign change tests
- Repeated "=" press tests
- Formatting tests (commas, decimal point)

## Conclusion

This implementation represents a **simplified version** of the standard calculator, focusing on basic arithmetic operations. Main differences:

1. **Missing advanced mathematical functions** (%, 1/x, x², √x)
2. **No memory functions**
3. **Simplified architecture** with direct operation execution
4. **Minimalist interface** without additional modes

Advantages of this implementation:
- Code simplicity and clarity
- Good test coverage
- Clean separation of logic and GUI
- Adaptive interface

This implementation is suitable for:
- Educational purposes
- Embedding in other applications
- Foundation for feature expansion
