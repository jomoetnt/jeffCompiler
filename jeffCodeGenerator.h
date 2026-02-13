#pragma once
class jeffCodeGenerator
{
public:
	jeffCodeGenerator();
	~jeffCodeGenerator();

	// generate x86 instructions
	void generatex86();
	// generate RISC-V instructions
	void generateRISCV();

	// output assembly code
	void outputAssembly();
	// output executable for Windows
	void outputPE();
	// output executable for Linux
	void outputELF();

};

