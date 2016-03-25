Compiler:

Arithmetic done.

Function calls done: try a nested function or returning a function.

If/else done.

While, do/while and for done.

All arithmetic, bitwise and logical operators done

Increment and decrement working.

Scoping/shadowing working

Arguments(parameters) working

Global variables.

Assignment operators

Switch, break and continue implemented

Pointers working!

Arrays!

Types partially implemented: long, short, float: char might work sort of

Floating point working: declarations, add, sub, mul, div: float arrays dont work & returning probably doesnt.

Goto has been written but doesnt work due to label issues: some bison issue (very strange) probably a sign from the gods

TODO:

Chars

Stress-test the above: everything needs to be properly properly tested.

General optimisation that will not be done because it isnt marked:
	
	Better use of registers (i.e. stop loading from v0 to t0, back into v0)
	
	Use of registers for STORING variables (s0-s7) : could be very complex
	
	AST level optimisation
	
	More intelligent use of the stack?
	
	Neaten flow control and return statements, currently horrible

... and probably more

STRUCTS : very low priority
