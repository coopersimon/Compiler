Compiler:

Arithmetic done. (mostly tested)

Function calls done. (mostly tested)

If/else done. (mostly tested)

While, do/while and for done. (For has not been fully tested!)

All arithmetic, bitwise and logical operators done (not fully tested)

Increment and decrement working. (mostly tested)

Scoping/shadowing working (not fully tested)

Arguments(parameters) working (mostly tested)

Global variables. (assignments need to be reimplemented)

Assignment operators (not fully tested but mostly good)

Switch, break and continue implemented (not at all tested)

Pointers working! (slightly tested) : now broken, need to take a look at pointer declaration & relation to type

Arrays implemented but needs to be properly tested.

Groundwork for types has been completed.

Goto has been written but doesnt work due to label issues: some bison issue (very strange)

TODO:

Stress-test the above: everything needs to be properly properly tested.

General optimisation:
	
	Better use of registers (i.e. stop loading from v0 to t0, back into v0)
	
	Use of registers for STORING variables (s0-s7) : could be very complex
	
	AST level optimisation
	
	More intelligent use of the stack?
	
	Neaten flow control and return statements, currently horrible

... and probably more

TYPES: proper implementation (could be hellish)

STRUCTS : very low priority
