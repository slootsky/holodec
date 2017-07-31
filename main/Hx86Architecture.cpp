
#include "Hx86FunctionAnalyzer.h"
#include "HInstrDefinition.h"

using namespace holodec;


holox86::HArchitecture holox86::x86architecture {"x86", "x86", 32, 8, {
		[] (HBinary * binary) {
			static HFunctionAnalyzer* analyzer = nullptr;
			if (analyzer == nullptr) {
				printf ("Create New Object\n");
				analyzer = new holox86::Hx86FunctionAnalyzer (&holox86::x86architecture);
			}
			if (analyzer->canAnalyze (binary)) {
				HFunctionAnalyzer* temp = analyzer;
				analyzer = nullptr;
				return temp;
			}
			return (HFunctionAnalyzer*) nullptr;
		}
	},
	{
		{"rax", 64, 0, true, {	{"eax", 32, 0, true, {	{"ax", 16, 0, {{"al", 8, 0}, {"ah", 8, 8}}}}}}},
		{"rbx", 64, 0, true, {	{"ebx", 32, 0, true, {	{"bx", 16, 0, {{"bl", 8, 0}, {"bh", 8, 8}}}}}}},
		{"rcx", 64, 0, true, {	{"ecx", 32, 0, true, {	{"cx", 16, 0, {{"cl", 8, 0}, {"ch", 8, 8}}}}}}},
		{"rdx", 64, 0, true, {	{"edx", 32, 0, true, {	{"dx", 16, 0, {{"dl", 8, 0}, {"dh", 8, 8}}}}}}},
		{"r8", 64, 0, true,	{	{"r8d", 32, 0, true, {	{"r8w", 16, 0, {{"r8b", 8, 0}}}}}}},
		{"r9", 64, 0, true, {	{"r9d", 32, 0, true, {	{"r9w", 16, 0, {{"r9b", 8, 0}}}}}}},
		{"r10", 64, 0, true, {	{"r10d", 32, 0, true, {	{"r10w", 16, 0, {{"r10b", 8, 0}}}}}}},
		{"r11", 64, 0, true, {	{"r11d", 32, 0, true, {	{"r11w", 16, 0, {{"r11b", 8, 0}}}}}}},
		{"r12", 64, 0, true, {	{"r12d", 32, 0, true, {	{"r12w", 16, 0, {{"r12b", 8, 0}}}}}}},
		{"r13", 64, 0, true, {	{"r13d", 32, 0, true, {	{"r13w", 16, 0, {{"r13b", 8, 0}}}}}}},
		{"r14", 64, 0, true, {	{"r14d", 32, 0, true, {	{"r14w", 16, 0, {{"r14b", 8, 0}}}}}}},
		{"r15", 64, 0, true, {	{"r15d", 32, 0, true, {	{"r15w", 16, 0, {{"r15b", 8, 0}}}}}}},

		{"rbp", 64, 0, true, {	{"ebp", 32, 0, true, {	{"bp", 16, 0}}}}},
		{"rsi", 64, 0, true, {	{"esi", 32, 0, true, {	{"si", 16, 0}}}}},
		{"rdi", 64, 0, true, {	{"edi", 32, 0, true, {	{"di", 16, 0}}}}},
		{"rsp", 64, 0, true, {	{"esp", 32, 0, true, {	{"sp", 16, 0}}}}},
		{"rip", 64, 0, true, {	{"eip", 32, 0, true, {	{"ip", 16, 0}}}}},

		{
			"rflags", 64, 0,
			{	{
					"eflags", 32, 0,
					{	{
							"flags", 16, 0,
							{	{"cf", 1, 0}, {"pf", 1, 2}, {"af", 1, 4}, {"zf", 1, 6}, {"sf", 1, 7}, {"tf", 1, 8}, {"if", 1, 9},
								{"df", 1, 10}, {"of", 1, 11}, {"iopl", 2, 12}, {"nt", 1, 14}
							}
						}, {"rf", 1, 16}, {"vm", 1, 17}, {"ac", 1, 18}, {"vif", 1, 19}, {"vip", 1, 20}, {"id", 1, 21}
					}
				},
			}
		},

		{"st0", 80, 0, {	{"mm0", 64, 0}}},
		{"st1", 80, 0, {	{"mm1", 64, 0}}},
		{"st2", 80, 0, {	{"mm2", 64, 0}}},
		{"st3", 80, 0, {	{"mm3", 64, 0}}},
		{"st4", 80, 0, {	{"mm4", 64, 0}}},
		{"st5", 80, 0, {	{"mm5", 64, 0}}},
		{"st6", 80, 0, {	{"mm6", 64, 0}}},
		{"st7", 80, 0, {	{"mm7", 64, 0}}},

		{"cs", 16, 0},
		{"ds", 16, 0},
		{"ss", 16, 0},
		{"es", 16, 0},
		{"fs", 16, 0},
		{"gs", 16, 0},

		{"dr0", 64, 0}, {"dr1", 64, 0}, {"dr2", 64, 0}, {"dr3", 64, 0},
		{"dr4", 64, 0}, {"dr5", 64, 0}, {"dr6", 64, 0}, {"dr7", 64, 0},
		//{"dr8", X86_REG_DH8, 64, 0}, {"dr9", X86_REG_DH9, 64, 0}, {"dr10", X86_REG_DH10, 64, 0}, {"dr11", X86_REG_DH11, 64, 0},
		//{"dr12", X86_REG_DH12, 64, 0}, {"dr13", X86_REG_DH13, 64, 0}, {"dr14", X86_REG_DH14, 64, 0}, {"dr15", X86_REG_DH15, 64, 0},

		//cr0 - cr15 control register
		//sw,cw,tw,fp_ip,...

		//{"cr0", X86_REG_CH0, 512, 0},

		{"zmm0", 512, 0, true, {{"ymm0", 512, 0, true, {{"xmm0", 128, 0, true}}}}},
		{"zmm1", 512, 0, true, {{"ymm1", 512, 0, true, {{"xmm1", 128, 0, true}}}}},
		{"zmm2", 512, 0, true, {{"ymm2", 512, 0, true, {{"xmm2", 128, 0, true}}}}},
		{"zmm3", 512, 0, true, {{"ymm3", 512, 0, true, {{"xmm3", 128, 0, true}}}}},
		{"zmm4", 512, 0, true, {{"ymm4", 512, 0, true, {{"xmm4", 128, 0, true}}}}},
		{"zmm5", 512, 0, true, {{"ymm5", 512, 0, true, {{"xmm5", 128, 0, true}}}}},
		{"zmm6", 512, 0, true, {{"ymm6", 512, 0, true, {{"xmm6", 128, 0, true}}}}},
		{"zmm7", 512, 0, true, {{"ymm7", 512, 0, true, {{"xmm7", 128, 0, true}}}}},
		{"zmm8", 512, 0, true, {{"ymm8", 512, 0, true, {{"xmm8", 128, 0, true}}}}},
		{"zmm9", 512, 0, true, {{"ymm9", 512, 0, true, {{"xmm9", 128, 0, true}}}}},
		{"zmm10", 512, 0, true, {{"ymm10", 512, 0, true, {{"xmm10", 128, 0, true}}}}},
		{"zmm11", 512, 0, true, {{"ymm11", 512, 0, true, {{"xmm11", 128, 0, true}}}}},
		{"zmm12", 512, 0, true, {{"ymm12", 512, 0, true, {{"xmm12", 128, 0, true}}}}},
		{"zmm13", 512, 0, true, {{"ymm13", 512, 0, true, {{"xmm13", 128, 0, true}}}}},
		{"zmm14", 512, 0, true, {{"ymm14", 512, 0, true, {{"xmm14", 128, 0, true}}}}},
		{"zmm15", 512, 0, true, {{"ymm15", 512, 0, true, {{"xmm15", 128, 0, true}}}}},
		{"zmm16", 512, 0},
		{"zmm17", 512, 0},
		{"zmm18", 512, 0},
		{"zmm19", 512, 0},
		{"zmm20", 512, 0},
		{"zmm21", 512, 0},
		{"zmm22", 512, 0},
		{"zmm23", 512, 0},
		{"zmm24", 512, 0},
		{"zmm25", 512, 0},
		{"zmm26", 512, 0},
		{"zmm27", 512, 0},
		{"zmm28", 512, 0},
		{"zmm29", 512, 0},
		{"zmm30", 512, 0},
		{"zmm31", 512, 0}
	},
	{
		{X86_INS_INVALID,		{"invalid", {0, 0, 0, 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOV,		{"mov", {0, 0, "=(#arg[1],#arg[2])", 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVABS,		{"movabs", {0, 0, "=(#arg[1],#arg[2])", 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVDQA,		{"movdqa", {0, 0, "=(#arg[1],#arg[2])", 0}}},
		{X86_INS_MOVDQU,		{"movdqu", {0, 0, "=(#arg[1],#arg[2])", 0}}},
		{X86_INS_MOVQ,	{"movq", {0, 0, "=(#arg[1],#arg[2])", 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVD,	{"movd", {0, 0, "=(#arg[1],#arg[2])", 0}, H_INSTR_TYPE_MOV}},

		{
			X86_INS_MOVBE,		{
				"movbe", {
					0, 0,
					"#seq("
					"?(==(#bsize(#arg[1]),16),#nop,=(#arg[1],#app(#arg[2][8,8],#arg[2][0,8]))),"
					"?(==(#bsize(#arg[1]),32),#nop,=(#arg[1],#app(#arg[2][24,8],#arg[2][16,8],#arg[2][8,8],#arg[2][0,8]))),"
					"?(==(#bsize(#arg[1]),64),#nop,=(#arg[1],#app(#arg[2][56,8],#arg[2][48,8],#arg[2][40,8],#arg[2][32,8],#arg[2][24,8],#arg[2][16,8],#arg[2][8,8],#arg[2][0,8])))"
					")", 0
				}, H_INSTR_TYPE_MOV
			}
		},
		{
			X86_INS_MOVDDUP,		{
				"movddup", {
					0, 0,
					"#seq("
					"?(==(#bsize(#arg[2]),64),#nop,=(#arg[1],#app(#arg[2],#arg[2]))),"
					"?(==(#bsize(#arg[2]),128),#nop,=(#arg[1],#app(#arg[2][0,64],#arg[2][0,64])))"
					")",
					0
				}, H_INSTR_TYPE_MOV
			}
		},
		{X86_INS_MOVHLPS,		{"movhlps", {0, 0, "=(#arg[1][0,64],#arg[2][64,64])", 0}, H_INSTR_TYPE_MOV}},
		{
			X86_INS_MOVHPD,		{
				"movhpd", {
					0, 0,
					"#seq("
					"?(==(#bsize(#arg[1]),64),#nop,=(#arg[1],#arg[2][64,64])),"
					"?(==(#bsize(#arg[1]),128),#nop,=(#arg[1][64,64],#arg[2]))"
					")",
					0
				}, H_INSTR_TYPE_MOV
			}
		},
		{
			X86_INS_MOVHPS,		{
				"movhps", {
					0, 0,
					"#seq("
					"?(==(#bsize(#arg[1]),64),#nop,=(#arg[1],#arg[2][64,64])),"
					"?(==(#bsize(#arg[1]),128),#nop,=(#arg[1][64,64],#arg[2]))"
					")"
					, 0
				}, H_INSTR_TYPE_MOV
			}
		},
		{X86_INS_MOVLHPS,		{"movlhps", {0, 0, "=(#arg[1][64,64],#arg[2][0,64])", 0}}},
		{
			X86_INS_MOVLPD,		{
				"movlpd", {
					0, 0,
					"#seq("
					"?(==(#bsize(#arg[1]),64),#nop,=(#arg[1],#arg[2][0,64])),"
					"?(==(#bsize(#arg[1]),128),#nop,=(#arg[1][0,64],#arg[2]))"
					")", 0
				}, H_INSTR_TYPE_MOV
			}
		},
		{
			X86_INS_MOVLPS,		{
				"movlps", {
					0, 0,
					"#seq("
					"?(==(#bsize(#arg[1]),64),#nop,=(#arg[1],#arg[2][0,64])),"
					"?(==(#bsize(#arg[1]),128),#nop,=(#arg[1][0,64],#arg[2]))"
					")", 0
				}, H_INSTR_TYPE_MOV
			}
		},
		{X86_INS_MOVMSKPD,		{"movskpd", {0, 0, "=(#arg[1],#app(#arg[2][63],#arg[2][127]))", 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVMSKPS,		{"movskps", {0, 0, "=(#arg[1],#app(#arg[2][31],#arg[2][63],#arg[2][95],#arg[2][127]))", 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVNTDQA,		{"movntdqa", {0, 0, "=(#arg[1],#arg[2])", 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVNTDQ,		{"movntdq", {0, 0, "=(#arg[1],#arg[2])", 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVNTI,		{"movnti", {0, 0, "=(#arg[1],#arg[2])", 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVNTPD,		{"movntpd", {0, 0, "=(#arg[1],#arg[2])", 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVNTPS,		{"movntps", {0, 0, "=(#arg[1],#arg[2])", 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVNTSD,		{"movntsd", {0, 0, "=(#arg[1],#arg[2])", 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVNTSS,		{"movntss", {0, 0, "=(#arg[1],#arg[2])", 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVSHDUP,		{"movshdup", {0, 0, "=(#arg[1],#app(#arg[2][32,32],#arg[2][32,32],#arg[2][96,32],#arg[2][96,32]))", 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVSLDUP,		{"movsldup", {0, 0, "=(#arg[1],#app(#arg[2][0,32],#arg[2][0,32],#arg[2][64,32],#arg[2][64,32]))", 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVSXD,		{"movsxd", {0, 0, "=(#arg[1],#sext(#arg[2],#bsize(#arg[1])))", 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVUPD,		{"movupd", {0, 0, "=(#arg[1],#arg[2])", 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVUPS,		{"movups", {0, 0, "=(#arg[1],#arg[2])", 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_LEA,	{"lea", {0, 0, "=(#arg[1],#val(#arg[2]))", 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_CMOVE,	{"cmovz", {0, 0, "?($zf,#nop,=(#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_E}},

		{X86_INS_CMOVNE,	{"cmovne", {0, 0, "?($zf,=(#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_NE}},

		{X86_INS_CMOVA,	{"cmova", {0, 0, "?(#and($cf,$zf),#nop,=(#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_A}},

		{X86_INS_CMOVBE,	{"cmovbe", {0, 0, "?(#or($cf,$zf),#nop,=(#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_BE}},

		{X86_INS_CMOVG,	{"cmovg", {0, 0, "?(#and(#not($zf),==($sf,$of)),#nop,=(#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_G}},

		{X86_INS_CMOVGE,	{"cmovge", {0, 0, "?(==($sf,$of),#nop,=(#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_GE}},


		{X86_INS_CMOVL,	{"cmovge", {0, 0, "?(==($sf,$of),=(#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_L}},
		{X86_INS_CMOVLE,	{"cmovle", {0, 0, "?(#or($zf,<>($sf,$of)),#nop,=(#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_LE}},

		//{X86_INS_CMOVC,	{"cmovc", {0, 0, "?($cf) #arg[1] = #arg[2]", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_C}},
		//{X86_INS_CMOVNC,	{"cmovnc", {0, 0, "?(#not($cf)) #arg[1] = #arg[2]", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_NC}},

		{X86_INS_CMOVB,	{"cmovb", {0, 0, "?($cf,#nop,=(#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_B}},

		{X86_INS_CMOVAE,	{"cmovae", {0, 0, "?($cf,=(#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_AE}},

		{X86_INS_CMOVO,	{"cmovo", {0, 0, "?($of,#nop,=(#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_O}},

		{X86_INS_CMOVNO,	{"cmovno", {0, 0, "?($of,=(#arg[1],#arg[2])) ", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_NO}},

		{X86_INS_CMOVS,	{"cmovs", {0, 0, "?($sf,#nop,=(#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_NEG}},

		{X86_INS_CMOVNS,	{"cmovns", {0, 0, "?($sf,=(#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_POS}},

		{X86_INS_CMOVP,	{"cmovp", {0, 0, "?($pf,#nop,=(#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_UNK}},

		{X86_INS_CMOVNP,	{"cmovp", {0, 0, "?($pf,#arg[1],#arg[2])", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_UNK}},

		{X86_INS_JMP,		{"jmp", {0, "#jmp(#arg[1])", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_TRUE}},

		{X86_INS_JE,		{"je", {0, "?($zf,#nop,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_E}},

		{X86_INS_JNE,		{"jne", {0, "?($zf,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_NE}},

		{X86_INS_JA,		{"ja", {0, "?(#and($cf,$zf),#nop,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_A}},

		{X86_INS_JAE,		{"jae", {0, "?($cf,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_AE}},

		{X86_INS_JB,		{"jb", {0, "?($cf,#nop,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_B}},

		{X86_INS_JBE,		{"jbe", {0, "?(#or($cf,$zf),#nop,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_BE}},

		{X86_INS_JG,		{"jg", {0, "?(#and(#not($zf),==($sf,$of)),#nop,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_G}},

		{X86_INS_JGE,		{"jge", {0, "?(==($sf,$of),#nop,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_GE}},

		{X86_INS_JL,		{"jl", {0, "?(==($sf,$of),#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_L}},

		{X86_INS_JLE,		{"jle", {0, "?(#or($zf,<>($sf,$of)),#nop,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_LE}},

		{X86_INS_JO,		{"jo", {0, "?($of,#nop,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_O}},

		{X86_INS_JNO,		{"jno", {0, "?($of,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_NO}},

		{X86_INS_JS,		{"js", {0, "?($sf,#nop,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_NEG}},

		{X86_INS_JNS,		{"jns", {0, "?($sf,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_POS}},

		{X86_INS_JP,		{"jp", {0, "?($pf,#nop,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_UNK}},

		{X86_INS_JNP,		{"jnp", {0, "?($pf,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_UNK}},

		{X86_INS_JCXZ,	{"jcxz", {0, "?(==($cx,0),#nop,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_CMP, H_INSTR_COND_E}},
		{X86_INS_JECXZ,	{"jecxz", {0, "?(==($ecx,0),#nop,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_CMP, H_INSTR_COND_E}},
		{X86_INS_JRCXZ,	{"jrcxz", {0, "?(==($rcx,0),#nop,#jmp(#arg[1]))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_CMP, H_INSTR_COND_E}},

		{X86_INS_XCHG,	{"xchg", {0, 0, "#seq(=(#t[1],#arg[1]),=(#arg[1],#arg[2]),=(#arg[2],#t[1]))", 0}, H_INSTR_TYPE_XCHG}},

		{X86_INS_BSWAP,	{"bswap", {0, "=(#arg[1],#app(#arg[1][24,8],#arg[1][16,8],#arg[1][8,8],#arg[1][0,8]))", 0, 0}, H_INSTR_TYPE_SWAP}},

		{X86_INS_XADD,	{"xadd", {0, 0, "#seq(#rec[xchg](#arg[1],#arg[2]),#rec[add](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_XCHG, H_INSTR_TYPE_ADD}},

		//X86_INS_CMPXCHG16B,
		{
			X86_INS_CMPXCHG,	{
				"cmpxchg", {
					0, 0,
					"#seq("
					"?(==(#bsize(#arg[1]),8),#nop,"
					"#seq("
					"=($zf,==($al,#arg[1])),"
					"=($cf,#c),=($pf,#p),=($af,#a),=($sf,#s),=($of,#o),"
					"?($zf,=(#arg[1],$al),=(#arg[1],#arg[2]))"
					")"
					"),"
					"?(==(#bsize(#arg[1]),16),#nop,"
					"#seq("
					"=($zf,==($ax,#arg[1])),"
					"=($cf,#c),=($pf,#p),=($af,#a),=($sf,#s),=($of,#o),"
					"?($zf,=(#arg[1],$ax),=(#arg[1],#arg[2]))"
					")"
					"),"
					"?(==(#bsize(#arg[1]),32),#nop,"
					"#seq("
					"=($zf,==($eax,#arg[1])),"
					"=($cf,#c),=($pf,#p),=($af,#a),=($sf,#s),=($of,#o),"
					"?($zf,=(#arg[1],$eax),=(#arg[1],#arg[2]))"
					")"
					")"
					")", 0
				}, H_INSTR_TYPE_XCHG, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_E
			}
		},
		{
			X86_INS_CMPXCHG8B, {
				"cmpxchg8g", {
					0,
					"#seq(=($zf,==(#app($eax,$edx),#arg[1])),"
					"?($zf,#seq(=($eax,#arg[1][0,32]),=($edx,#arg[1][32,32])),=(#arg[1],#app($ebx,$ecx))))"
					, 0, 0
				}, H_INSTR_TYPE_XCHG, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_E
			}
		},
		{
			X86_INS_CMPXCHG16B, {
				"cmpxchg16g", {
					0,
					"#seq(=($zf,==(#app($rax,$rdx),#arg[1])),"
					"?($zf,#seq(=($rax,#arg[1][0,64]),=($rdx,#arg[1][64,64])),=(#arg[1],#app($rbx,$rcx))))"
					, 0, 0
				}, H_INSTR_TYPE_XCHG, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_E
			}
		},

		{X86_INS_PUSH,	{"push", {0, "#seq(=($rsp,-($rsp,#size(#arg[1]))),#st($rsp,#arg[1]))", 0, 0}, H_INSTR_TYPE_PUSH}},
		{X86_INS_POP,		{"pop", {0, "#seq(=(#arg[1],#ld($rsp)),=($rsp,+($rsp,#size(#arg[1]))))", 0, 0}, H_INSTR_TYPE_POP}},

		{X86_INS_PUSHAW,	{"pushad", {0, "#seq(=(#t[1],$esp),#rec[push]($eax),#rec[push]($ecx),#rec[push]($edx),#rec[push]($edx),#rec[push]($ebx),#rec[push](#t[1]),#rec[push]($ebp),#rec[push]($esi),#rec[push]($edi))", 0, 0}, H_INSTR_TYPE_PUSH}},
		{X86_INS_PUSHAL,	{"pusha", {0, "#seq(=(#t[1],$sp),#rec[push]($ax),#rec[push]($cx),#rec[push]($dx),#rec[push]($dx),#rec[push]($bx),#rec[push](#t[1]),#rec[push]($bp),#rec[push]($si),#rec[push]($di))", 0, 0}, H_INSTR_TYPE_PUSH}},

		{X86_INS_POPAW,	{"popad", {0, "#seq(#rec[pop]($edi),#rec[pop]($esi),#rec[pop]($ebp),=($esp,+($esp,4)),#rec[pop]($ebx),#rec[pop]($edx),#rec[pop]($ecx),#rec[pop]($eax))", 0, 0}, H_INSTR_TYPE_PUSH}},
		{X86_INS_POPAL,	{"popa", {0, "#seq(#rec[pop]($di),#rec[pop]($si),#rec[pop]($bp),=($esp,+($esp,2)),#rec[pop]($bx),#rec[pop]($dx),#rec[pop]($cx),#rec[pop]($ax))", 0, 0}, H_INSTR_TYPE_PUSH}},

		{X86_INS_RET,		{"ret", {"#ret", "#seq(=($rsp,-($rsp,*(#arg[1],8))),#ret)", 0, 0}, H_INSTR_TYPE_RET, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_TRUE}},
		{X86_INS_IRET, {"iret", {"#ret", "#seq(=($rsp,-($rsp,*(#arg[1],8))),#ret)", 0, 0}, H_INSTR_TYPE_RET, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_TRUE}},
		{X86_INS_IRETD, {"iretd", {"#ret", "#seq(=($rsp,-($rsp,*(#arg[1],8))),#ret)", 0, 0}, H_INSTR_TYPE_RET, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_TRUE}},
		{X86_INS_IRETQ, {"iretq", {"#ret", "#seq(=($rsp,-($rsp,*(#arg[1],8))),#ret)", 0, 0}, H_INSTR_TYPE_RET, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_TRUE}},
		{X86_INS_RETF, {"retf", {"#ret", "#seq(=($rsp,-($rsp,*(#arg[1],8))),#ret)", 0, 0}, H_INSTR_TYPE_RET, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_TRUE}},
		{X86_INS_RETFQ, {"retfq", {"#ret", "#seq(=($rsp,-($rsp,*(#arg[1],8))),#ret)", 0, 0}, H_INSTR_TYPE_RET, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_TRUE}},

		{X86_INS_HLT, {"hlt", {0, 0, 0, 0}}},
		
		{X86_INS_CBW,		{"cbw", {"=($ax,#sext($al,#bsize($ax)))", 0, 0, 0}, H_INSTR_TYPE_EXTEND}},
		{X86_INS_CWDE,		{"cwde", {"=($eax,#ext($ax,#bsize($eax)))", 0, 0, 0}, H_INSTR_TYPE_EXTEND}},
		{X86_INS_CDQE, 		{"cdqe", {"=($rax,#sext($eax,#bsize($rax)))", 0, 0, 0}, H_INSTR_TYPE_EXTEND}},

		{X86_INS_CWD,		{"cwd", {"=($dx,#sext($ax,#bsize($dx)))", 0, 0, 0}, H_INSTR_TYPE_EXTEND}},
		{X86_INS_CDQ,		{"cdq", {"=($edx,#sext($eax,#bsize($edx)))", 0, 0, 0}, H_INSTR_TYPE_EXTEND}},
		{X86_INS_CQO, 		{"cqo", {"=($rdx,#sext($rax,#bsize($rdx)))", 0, 0, 0}, H_INSTR_TYPE_EXTEND}},

		{X86_INS_MOVSX,	{"movsx", {0, 0, "=(#arg[1],#sext(#arg[2],#bsize(#arg[1])))", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_EXTEND}},
		{X86_INS_MOVZX,	{"movzx", {0, 0, "=(#arg[1],#ext(#arg[2],#bsize(#arg[1])))", 0}, H_INSTR_TYPE_MOV, H_INSTR_TYPE_EXTEND}},

		{X86_INS_ADD,		{"add", {0, 0, "#seq(=(#arg[1],+(#arg[1],#arg[2])),=($zf,#z),=($pf,#p),=($sf,#s),=($of,#o),=($cf,#c),=($af,#a))", 0}, H_INSTR_TYPE_ADD}},
		{X86_INS_ADC,		{"adc", {0, 0, "#seq(=(#arg[1],+(#arg[1],#arg[2],$cf)),=($zf,#z),=($pf,#p),=($sf,#s),=($of,#o),=($cf,#c),=($af,#a))", 0}, H_INSTR_TYPE_ADD}},

		{X86_INS_SUB,		{"sub", {0, 0, "#seq(=(#arg[1],-(#arg[1],#arg[2])),=($zf,#z),=($pf,#p),=($sf,#s),=($of,#o),=($cf,#c),=($af,#a))", 0}, H_INSTR_TYPE_SUB}},
		{X86_INS_SBB,		{"sbb", {0, 0, "#seq(=(#arg[1],-(#arg[1],#arg[2],$cf)),=($zf,#z),=($pf,#p),=($sf,#s),=($of,#o),=($cf,#c),=($af,#a))", 0}, H_INSTR_TYPE_SUB}},

		{X86_INS_ADCX,	{"adcx", {0, 0, "#seq(=(#arg[1],+(#arg[1],#arg[2],$cf)),=($zf,#z),=($pf,#p),=($sf,#s),=($of,#o),=($cf,#c),=($af,#a))", 0}, H_INSTR_TYPE_ADD}},
		{X86_INS_ADOX,	{"adox", {0, 0, "#seq(=(#arg[1],+(#arg[1],#arg[2],$of)),=($zf,#z),=($pf,#p),=($sf,#s),=($of,#o),=($cf,#c),=($af,#a))", 0}, H_INSTR_TYPE_ADD}},

		{
			X86_INS_MUL,	{
				"mul", {
					0,
					"#seq("
					"?(==(#bsize(#arg[1]),8),#nop,#seq(=($ax,*($al,#arg[1])),=($cf,#c),=($of,#o))),"
					"?(==(#bsize(#arg[1]),16),#nop,#seq(=(#t[1],*($ax,#arg[1])),=($cf,#c),=($of,#o),=($dx,#t[1][0,16]),=($ax,#t[1][16,16]))),"
					"?(==(#bsize(#arg[1]),32),#nop,#seq(=(#t[1],*($eax,#arg[1])),=($cf,#c),=($of,#o),=($edx,#t[1][0,32]),=($eax,#t[1][32,32])))"
					",#undef($sf,$zf,$af,$pf))",
					0, 0
				}, H_INSTR_TYPE_MUL
			}
		},
		{
			X86_INS_IMUL,	{
				"imul", {
					0,
					"#seq("
					"?(==(#bsize(#arg[1]),8),#nop,#seq(=($ax,*($al,#arg[1])),=($cf,#c),=($of,#o))),"
					"?(==(#bsize(#arg[1]),16),#nop,#seq(=(#t[1],*($ax,#arg[1])),=($cf,#c),=($of,#o),=($dx,#t[1][0,16]),=($ax,#t[1][16,16]))),"
					"?(==(#bsize(#arg[1]),32),#nop,#seq(=(#t[1],*($eax,#arg[1])),=($cf,#c),=($of,#o),=($edx,#t[1][0,32]),=($eax,#t[1][32,32]))),"
					"#undef($zf,$af,$pf))",
					"#seq(=(#arg[1],#smul(#arg[1],#sext(#arg[2],#bsize(#arg[1])))),=($cf,#c),=($of,#o),#undef($zf,$af,$pf))",
					"#seq(=(#arg[1],#smul(#arg[1],#sext(#arg[3],#bsize(#arg[2])))),=($cf,#c),=($of,#o),#undef($zf,$af,$pf))"
				}, H_INSTR_TYPE_MUL
			}
		},
		{
			X86_INS_IDIV,	{
				"idiv", {
					0,
					"#seq("
					"?(==(#bsize(#arg[1]),8),#nop,#seq(=(#t[1],$ax),=($al,#sdiv(#t[1],#arg[1])),=($ah,#smod(#t[1],#arg[1])))),"
					"?(==(#bsize(#arg[1]),16),#nop,#seq(=(#t[1],#app($dx,$ax)),=($ax,#sdiv(#t[1],#arg[1])),=($dx,#smod(#t[1],#arg[1])))),"
					"?(==(#bsize(#arg[1]),32),#nop,#seq(=(#t[1],#app($edx,$eax)),=($eax,#sdiv(#t[1],#arg[1])),=($edx,#smod(#t[1],#arg[1]))))"
					",#undef($cf,$of,$sf,$zf,$af,$pf))",
					0, 0
				}, H_INSTR_TYPE_DIV
			}
		},
		{
			X86_INS_DIV,	{
				"div", {
					0,
					"#seq("
					"?(==(#bsize(#arg[1]),8),#nop,#seq(=(#t[1],$ax),=($eax,#div(#t[1],#arg[1])),=($edx,#mod(#t[1],#arg[1])))),"
					"?(==(#bsize(#arg[1]),16),#nop,#seq(=(#t[1],#app($dx,$ax)),=($eax,#div(#t[1],#arg[1])),=($edx,#mod(#t[1],#arg[1])))),"
					"?(==(#bsize(#arg[1]),32),#nop,#seq(=(#t[1],#app($edx,$eax)),=($eax,#div(#t[1],#arg[1])),=($edx,#mod(#t[1],#arg[1]))))"
					",#undef($cf,$of,$sf,$zf,$af,$pf))",
					0, 0
				}, H_INSTR_TYPE_DIV
			}
		},
		{X86_INS_NOP,		{"nop", {"#nop", "#nop", 0, 0}}},

		{X86_INS_INC,		{"inc", {0, 0, "#seq(=(#arg[1],+(#arg[1],1)),=($zf,#z),=($pf,#p),=($sf,#s),=($of,#o),=($af,#a))", 0}, H_INSTR_TYPE_ADD}},
		{X86_INS_DEC,		{"dec", {0, 0, "#seq(=(#arg[1],-(#arg[1],1)),=($zf,#z),=($pf,#p),=($sf,#s),=($of,#o),=($af,#a))", 0}, H_INSTR_TYPE_SUB}},

		{X86_INS_NEG,		{"neg", {0, 0, "#seq(=($cf,<>(#arg[1],0)),=(#arg[1],-(0,#arg[1])),=($zf,#z),=($pf,#p),=($sf,#s),=($of,#o),=($af,#a))", 0}, H_INSTR_TYPE_NEG}},

		{X86_INS_CMP,		{"cmp", {0, 0, "#seq(=(#t[1],#arg[1]),#rec[sub](#t[1],#sext(#arg[2],#bsize(#arg[1]))))", 0}, H_INSTR_TYPE_CMP}},

		{X86_INS_AND,		{"and", {0, 0, "#seq(=(#arg[1],#band(#arg[1],#arg[2])),=($of,0),=($cf,0),=($sf,#s),=($zf,#z),=($pf,#p),#undef($af))", 0}, H_INSTR_TYPE_AND}},
		{X86_INS_ANDPD,		{"andpd", {0, 0, "=(#arg[1],#band(#arg[1],#arg[2]))", 0}}},
		{X86_INS_ANDPS,		{"andps", {0, 0, "=(#arg[1],#band(#arg[1],#arg[2]))", 0}}},
		{X86_INS_PAND,		{"pand", {0, 0, "=(#arg[1],#band(#arg[1],#arg[2]))", 0}}},
//TODO flags undef checkpoint
		{X86_INS_ANDN,		{"andn", {0, 0, "=(#arg[1],#band(#bnot(#arg[1]),#arg[2]))", 0}}},
		{X86_INS_ANDNPD,		{"andnpd", {0, 0, "=(#arg[1],#band(#bnot(#arg[1]),#arg[2]))", 0}}},
		{X86_INS_ANDNPS,		{"andnps", {0, 0, "=(#arg[1],#band(#bnot(#arg[1]),#arg[2]))", 0}}},
		{X86_INS_PANDN,		{"pandn", {0, 0, "#seq(=(#arg[1],#band(#bnot(#arg[1]),#arg[2])),=($of,0),=($cf,0),=($sf,#s),=($zf,#z))", 0}}},


		{X86_INS_OR,		{"or", {0, 0, "#seq(=(#arg[1],#bor(#arg[1],#arg[2])),=($of,0),=($cf,0),=($sf,#s),=($zf,#z),=($pf,#p))", 0}, H_INSTR_TYPE_OR}},
		{X86_INS_ORPD,		{"orpd", {0, 0, "=(#arg[1],#bor(#arg[1],#arg[2]))", 0}}},
		{X86_INS_ORPS,		{"orps", {0, 0, "=(#arg[1],#bor(#arg[1],#arg[2]))", 0}}},
		{X86_INS_POR,		{"por", {0, 0, "=(#arg[1],#bor(#arg[1],#arg[2]))", 0}}},

		{X86_INS_XOR,		{"xor", {0, 0, "#seq(=(#arg[1],#bxor(#arg[1],#arg[2])),=($of,0),=($cf,0),=($sf,#s),=($zf,#z),=($pf,#p))", 0}, H_INSTR_TYPE_XOR}},
		{X86_INS_XORPD,		{"xorpd", {0, 0, "=(#arg[1],#bxor(#arg[1],#arg[2]))", 0}}},
		{X86_INS_XORPS,		{"xorps", {0, 0, "=(#arg[1],#bxor(#arg[1],#arg[2]))", 0}}},
		{X86_INS_PXOR,		{"pxor", {0, 0, "=(#arg[1],#bxor(#arg[1],#arg[2]))", 0}}},

		{X86_INS_NOT,		{"not", {0, "=(#arg[1],#bnot(#arg[1]))", 0, 0}, H_INSTR_TYPE_NOT}},

		{
			X86_INS_SAR, {
				"sar", {
					0,
					"#seq(=(#t[1],#sar(#arg[1],1)),"
					"=($zf,#z),=($pf,#p),=($sf,#s),=($of,#o),=($af,#a),"
					"=(#arg[1],#t[1]),=($cf,#t[1][#bsize(#arg[1])]))",
					//"?(<(#arg[2],#bsize(#arg[1]))) #skip = 100;" Maybe not?
					"#seq(=(#t[1],#sar(#arg[1],#arg[2])),"
					"=($zf,#z),=($pf,#p),=($sf,#s),=($of,#o),=($af,#a),"
					"=(#arg[1],#t[1]),=($cf,#t[1][#bsize(#arg[1])]))", 0
				}, H_INSTR_TYPE_SHH
			}
		},

		{
			X86_INS_SHR, {
				"shr", {
					0,
					"#seq(=(#t[1],#shr(#arg[1],1)),"
					"=($zf,#z),=($pf,#p),=($sf,#s),=($of,#o),=($af,#a),"
					"=(#arg[1],#t[1]),=($cf,#t[1][#bsize(#arg[1])]))",
					//"?(<(#arg[2],#bsize(#arg[1]))) #skip = 100;" Maybe not?
					"#seq(=(#t[1],#shr(#arg[1],#arg[2])),"
					"=($zf,#z),=($pf,#p),=($sf,#s),=($of,#o),=($af,#a),"
					"=(#arg[1],#t[1]),=($cf,#t[1][#bsize(#arg[1])]))", 0
				}, H_INSTR_TYPE_SHH
			}
		},

		{
			X86_INS_SAL, {
				"sal", {
					0,
					"#seq(=(#t[1],#sal(#arg[1],1)),"
					"=($zf,#z),=($pf,#p),=($sf,#s),=($of,#o),=($af,#a),"
					"=(#arg[1],#t[1]),=($cf,#t[1][#bsize(#arg[1])]))",
					//"?(<(#arg[2],#bsize(#arg[1]))) #skip = 100;" Maybe not?
					"#seq(=(#t[1],#sal(#arg[1],#arg[2])),"
					"=($zf,#z),=($pf,#p),=($sf,#s),=($of,#o),=($af,#a),"
					"=(#arg[1],#t[1]),=($cf,#t[1][#bsize(#arg[1])]))", 0
				}, H_INSTR_TYPE_SHL
			}
		},

		{
			X86_INS_SHL, {
				"shl", {
					0,
					"#seq(=(#t[1],#shl(#arg[1],1)),"
					"=($zf,#z),=($pf,#p),=($sf,#s),=($of,#o),=($af,#a),"
					"=(#arg[1],#t[1]),=($cf,#t[1][#bsize(#arg[1])]))",
					//"?(<(#arg[2],#bsize(#arg[1]))) #skip = 100;" Maybe not?
					"#seq(=(#t[1],#shl(#arg[1],#arg[2])),"
					"=($zf,#z),=($pf,#p),=($sf,#s),=($of,#o),=($af,#a),"
					"=(#arg[1],#t[1]),=($cf,#t[1][#bsize(#arg[1])]))", 0
				}, H_INSTR_TYPE_SHL
			}
		},

		//TODO flags
		{X86_INS_SHRD,	{"shrd", { 0, 0, "=(#arg[1],#shr(#app(#arg[1],#arg[2]),$cl))", "=(#arg[1],#app(#shr(#arg[1],#arg[2]),#arg[3]))"}, H_INSTR_TYPE_SHH}},
		{X86_INS_SHLD,	{"shld", { 0, 0, "=(#arg[1],#shl(#app(#arg[1],#arg[2]),$cl))", "=(#arg[1],#app(#shl(#arg[1],#arg[2]),#arg[3]))"}, H_INSTR_TYPE_SHL}},

		//TODO flags for rotates
		{X86_INS_ROR,	{"ror", {0, "=(#arg[1],#ror(#arg[1],1))", "=(#arg[1],#ror(#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_ROR}},
		{X86_INS_ROL,	{"rol", {0, "=(#arg[1],#rol(#arg[1],1))", "=(#arg[1],#rol(#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_ROL}},
		{
			X86_INS_RCR, {
				"rcr", {
					0,
					"#seq(=(#t[1],#ror(#app(#arg[1],$cf),1)),=(#arg[1],#t[1]),=($cf,#t[1][#bsize(#arg[1])]))",
					"#seq(=(#t[1],#ror(#app(#arg[1],$cf),#arg[2])),=(#arg[1],#t[1]),=($cf,#t[1][#bsize(#arg[1])]))", 0
				}, H_INSTR_TYPE_ROR
			}
		},
		{
			X86_INS_RCL, {
				"rcl", {
					0,
					"#seq(=(#t[1],#rol(#app(#arg[1],$cf),1)),=(#arg[1],#t[1]),=($cf,#t[1][#bsize(#arg[1])]))",
					"#seq(=(#t[1],#rol(#app(#arg[1],$cf),#arg[2])),=(#arg[1],#t[1]),=($cf,#t[1][#bsize(#arg[1])]))", 0
				}, H_INSTR_TYPE_ROL
			}
		},

		{X86_INS_BT,	{"bt", {0, 0, "=($cf,#arg[1][#arg[2]])", 0}, H_INSTR_TYPE_BITTEST}},
		{X86_INS_BTS,	{"bts", {0, 0, "#seq(=($cf,#arg[1][#arg[2]]),=(#arg[1][#arg[2]],1))", 0}, H_INSTR_TYPE_BITTEST, H_INSTR_TYPE_BITSET}},
		{X86_INS_BTR,	{"btr", {0, 0, "#seq(=($cf,#arg[1][#arg[2]]),=(#arg[1][#arg[2]],0))", 0}, H_INSTR_TYPE_BITTEST, H_INSTR_TYPE_BITRESET}},
		{X86_INS_BTC,	{"btc", {0, 0, "#seq(=($cf,#arg[1][#arg[2]]),=(#arg[1][#arg[2]],#not(#arg[1][#arg[2]])))", 0}, H_INSTR_TYPE_BITTEST, H_INSTR_TYPE_CPL}},

		{X86_INS_LOOP,	{"loop", {0, "#seq(=($ecx,-($ecx,1)),?($ecx,#nop,#rjmp(#arg[1])))", 0, 0}, H_INSTR_TYPE_JMP}},


		{X86_INS_LOOPE,	{"loope", {0, "#seq(=($ecx,-($ecx,1)),?(#and($ecx,$zf),#nop,#rjmp(#arg[1])))", 0, 0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_E}},

		{X86_INS_LOOPNE, {"loopne", {0, "#seq(=($ecx,-($ecx,1)),?(#and($ecx,#not($zf)),#nop,#rjmp(#arg[1])))", 0,  0}, H_INSTR_TYPE_JMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_NE}},

		{X86_INS_CALL,	{"call", {0, "#call(#arg[1])", 0, 0}, H_INSTR_TYPE_CALL}},

		{X86_INS_INT,	{"int", {0, "#syscall(#arg[1])", 0, 0}, H_INSTR_TYPE_SYSCALL, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_TRUE}},
		{X86_INS_INTO,	{"into", {"#syscall()", 0, 0, 0}, H_INSTR_TYPE_SYSCALL, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_TRUE}},

		{X86_INS_BOUND,	{"bound", {0, 0, "#seq(=(#t[1],#ld(#arg[2])),=(#t[2],#ld(+(#arg[2],#size(#arg[1])),#size(#arg[1]))),?(#or(<(#arg[1],#t[1]),>(#arg[1],#t[2])),#nop,#trap))", 0}}},

		{X86_INS_ENTER,	{"enter", {0, "#seq(#rec[push]($ebp),#rec[mov]($ebp,$esp),#rec[sub]($esp,#arg[1]))", 0, 0}}},
		{X86_INS_LEAVE,	{"leave", {"#seq(#rec[mov]($esp,$ebp),#rec[pop]($ebp))", 0, 0, 0}}},

		{X86_INS_SETE,	{"sete", {0, "=(#arg[1],$zf)", 0, 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_SETNE,	{"setne", {0, "=(#arg[1],#not($zf))", 0, 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_SETA,	{"seta", {0, "=(#arg[1],#not(#or($cf,$zf)))", 0, 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_SETAE,	{"setae", {0, "=(#arg[1],#not($cf))", 0, 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_SETB,	{"setae", {0, "=(#arg[1],$cf)", 0, 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_SETBE,	{"setbe", {0, "=(#arg[1],#or($cf,$zf))", 0, 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_SETG,	{"setg", {0, "=(#arg[1],#and(#not($zf),==($sf,$of)))", 0, 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_SETGE,	{"setge", {0, "=(#arg[1],==($sf,$of))", 0, 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_SETL,	{"setl", {0, "=(#arg[1],<>($sf,$of))", 0, 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_SETLE,	{"setle", {0, "=(#arg[1],#or($zf,<>($sf,$of)))", 0, 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_SETS,	{"sets", {0, "=(#arg[1],$sf)", 0, 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_SETNS,	{"setns", {0, "=(#arg[1],#not($sf))", 0, 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_SETO,	{"seto", {0, "=(#arg[1],$of)", 0, 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_SETNO,	{"setno", {0, "=(#arg[1],#not($of))", 0, 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_SETP,	{"setp", {0, "=(#arg[1],$pf)", 0, 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_SETNP,	{"setnp", {0, "=(#arg[1],#not($pf))", 0, 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_TEST,	{"test", {0, 0, "#seq(=(#t[1],#band(#arg[1],#arg[2])),=($cf,0),=($of,0),=($pf,#p),=($zf,#z),=($sf,#s))", 0}, H_INSTR_TYPE_AND}},

		{X86_INS_BSF,		{"bsf", {0, 0, 0, 0}}},
		{X86_INS_BSR,		{"bsr", {0, 0, 0, 0}}},
		{X86_INS_CRC32,	{"crc32", {0, 0, 0, 0}}},
		{X86_INS_POPCNT,	{"popcnt", {0, 0, 0, 0}}},

		{X86_INS_STC,		{"stc", {"=($cf,1)", 0, 0, 0}, H_INSTR_TYPE_BITSET}},
		{X86_INS_CLC,		{"clc", {"=($cf,0)", 0, 0, 0}, H_INSTR_TYPE_BITRESET}},
		{X86_INS_CMC,		{"cmc", {"=($cf,#not($cf))", 0, 0, 0}, H_INSTR_TYPE_CPL}},

		{X86_INS_STD,		{"std", {"=($df,1)", 0, 0, 0}, H_INSTR_TYPE_BITSET}},
		{X86_INS_CLD,		{"cld", {"=($df,0)", 0, 0, 0}, H_INSTR_TYPE_BITRESET}},

		{X86_INS_LAHF,	{"lahf", {"=($ah,$eflags)", 0, 0, 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_SAHF,	{"sahf", {"=($eflags,$ah)", 0, 0, 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_PUSHF,	{"pushf", {"#rec[push]($flags)", 0, 0, 0}, H_INSTR_TYPE_PUSH}},
		{X86_INS_PUSHFD,	{"pushfd", {"#rec[push]($eflags)", 0, 0, 0}, H_INSTR_TYPE_PUSH}},
		{X86_INS_PUSHFQ,	{"pushfq", {"#rec[push]($rflags)", 0, 0, 0}, H_INSTR_TYPE_PUSH}},

		{X86_INS_POPF,	{"popf", {"#rec[pop]($flags)", 0, 0, 0}, H_INSTR_TYPE_POP}},
		{X86_INS_POPFD,	{"popfd", {"#rec[pop]($eflags)", 0, 0, 0}, H_INSTR_TYPE_POP}},
		{X86_INS_POPFQ,	{"popfq", {"#rec[pop]($rflags)", 0, 0, 0}, H_INSTR_TYPE_POP}},

		{X86_INS_STI,		{"sti", {"=($if,1)", 0, 0, 0}, H_INSTR_TYPE_BITSET}},
		{X86_INS_CLI,		{"cli", {"=($if,0)", 0, 0, 0}, H_INSTR_TYPE_BITRESET}},

		//TODO
		{X86_INS_AAA,		{"aaa", {0, 0, 0, 0}}},
		{X86_INS_AAD,		{"aad", {0, 0, 0, 0}}},
		{X86_INS_AAM,		{"aam", {0, 0, 0, 0}}},
		{X86_INS_AAS,		{"aas", {0, 0, 0, 0}}},
		{X86_INS_DAA, 		{"daa", {0, 0, 0, 0}}},
		{X86_INS_DAS, 		{"das", {0, 0, 0, 0}}},

		{X86_INS_FABS,		{"fabs", {"=($st0,#fmul($st0,-1))", 0, 0, 0}}},
		{X86_INS_ADDPD,		{"addpd", {0, 0, "=(#arg[1],#app(#fadd(#arg[1][0,64],#arg[2][0,64]),#fadd(#arg[1][64,64],#arg[2][64,64])))", 0}}},
		{
			X86_INS_ADDPS,		{
				"addps", {
					0, 0, "=(#arg[1],#app(#fadd(#arg[1][0,32],#arg[2][0,32]),#fadd(#arg[1][32,32],#arg[2][32,32]),"
					"#fadd(#arg[1][64,32],#arg[2][64,32]),#fadd(#arg[1][96,32],#arg[2][96,32])))", 0
				}
			}
		},
		{X86_INS_ADDSD,		{"addsd", {0, 0, "=(#arg[1][0,64],#fadd(#arg[1][0,64],#arg[2][0,64]))", 0}}},
		{X86_INS_ADDSS,		{"addss", {0, 0, "=(#arg[1][0,32],#fadd(#arg[1][0,32],#arg[2][0,32]))", 0}}},
		{X86_INS_ADDSUBPD,		{"addsubpd", {0, 0, "=(#arg[1],#app(#fsub(#arg[1][0,64],#arg[2][0,64]),#fadd(#arg[1][64,64],#arg[2][64,64])))", 0}}},
		{
			X86_INS_ADDSUBPS,		{
				"addsubps", {
					0, 0, "=(#arg[1],#app(#fsub(#arg[1][0,32],#arg[2][0,32]),#fadd(#arg[1][32,32],#arg[2][32,32]),"
					"#fsub(#arg[1][64,32],#arg[2][64,32]),#fadd(#arg[1][96,32],#arg[2][96,32])))", 0
				}
			}
		},
		{X86_INS_FADD,		{"fadd", {0, "=($st0,#fadd($st0,#arg[1]))", "=(#arg[1],#fadd(#arg[1],#arg[2]))", 0}}},
		{X86_INS_FIADD,		{"fiadd", {0, "=($st0,#fadd($st0,#fext(#arg[1],#bsize($st0))))", 0, 0}}},
		{X86_INS_FADDP,		{"faddp", {"#seq(=($st0,#fadd($st0,$st1),=($rsp,+($rsp,1))))", "#seq(=($st0,#fadd($st0,#arg[1])),=($rsp,+($rsp,1)))", "#seq(=(#arg[1],#fadd(#arg[1],#arg[2])),=($rsp,+($rsp,1)))", 0}}},

		{X86_INS_CVTDQ2PD, {"cvtdq2pd", {0, 0, "=(#arg[1],#app(#fext(#i2f(#arg[2][0,32]),64),#fext(#i2f(#arg[2][32,32]),64)))", 0}}},
		{X86_INS_CVTDQ2PS, {"cvtdq2ps", {0, 0, "=(#arg[1],#app(#i2f(#arg[2][0,32]),#i2f(#arg[2][32,32]),#i2f(#arg[2][64,32]),#i2f(#arg[2][96,32])))", 0}}},
		{X86_INS_CVTPD2DQ, {"cvtpd2dq", {0, 0, "=(#arg[1],#app(#f2i(#arg[2][0,32]),#f2i(#arg[2][32,32]),#ext(0,64)))", 0}}},
		{X86_INS_CVTPD2PS, {"cvtpd2ps", {0, 0, "=(#arg[1],#app(#fext(#arg[2][0,64],32),#fext(#arg[2][64,64],32)))", 0}}},
		{X86_INS_CVTPS2DQ, {"cvtps2dq", {0, 0, "=(#arg[1],#app(#f2i(#arg[2][0,32]),#f2i(#arg[2][32,32]),#f2i(#arg[2][64,32]),#f2i(#arg[2][96,32])))", 0}}},
		{X86_INS_CVTPS2PD, {"cvtps2pd", {0, 0, "=(#arg[1],#app(#fext(#arg[2][0,32],64),#fext(#arg[2][32,32],64)))", 0}}},
		{X86_INS_CVTSD2SI, {"cvtsd2si", {0, 0, "=(#arg[1][0,32],#f2i(#arg[2][0,64],32))", 0}}},
		{X86_INS_CVTSD2SS, {"cvtsd2ss", {0, 0, "=(#arg[1][0,32],#fext(#arg[2][0,64],32))", 0}}},
		{X86_INS_CVTSI2SD, {"cvtsi2sd", {0, 0, "=(#arg[1][0,64],#i2f(#arg[2][0,32],64))", 0}}},
		{X86_INS_CVTSI2SS, {"cvtsi2ss", {0, 0, "=(#arg[1][0,32],#i2f(#arg[2][0,32]))", 0}}},
		{X86_INS_CVTSS2SD, {"cvtss2sd", {0, 0, "=(#arg[1][0,64],#fext(#arg[2][0,32],64))", 0}}},
		{X86_INS_CVTSS2SI, {"cvtss2si", {0, 0, "=(#arg[1][0,32],#f2i(#arg[2][0,32]))", 0}}},
		{X86_INS_CVTTPD2DQ, {"cvttpd2dq", {0, 0, "=(#arg[1],#app(#ext(#f2i(#arg[2][0,64]),32),#ext(#f2i(#arg[2][64,64]),32),#ext(0,64)))", 0}}},
		{X86_INS_CVTTPS2DQ, {"cvttps2dq", {0, 0, "=(#arg[1],#app(#f2i(#arg[2][0,32]),#f2i(#arg[2][32,32]),#f2i(#arg[2][64,32]),#f2i(#arg[2][96,32])))", 0}}},
		{X86_INS_CVTTSD2SI, {"cvttsd2si", {0, 0, "=(#arg[1][0,32],#f2i(#arg[2][0,64],32))", 0}}},
		{X86_INS_CVTTSS2SI, {"cvttss2si", {0, 0, "=(#arg[1][0,32],#f2i(#arg[2][0,64],32))", 0}}},

		{X86_INS_AESDECLAST,		{"aesdeclast", {0, 0, 0, 0}, H_INSTR_TYPE_CRYPTO}},
		{X86_INS_AESDEC,		{"aesdec", {0, 0, 0, 0}, H_INSTR_TYPE_CRYPTO}},
		{X86_INS_AESENCLAST,		{"aesenclast", {0, 0, 0, 0}, H_INSTR_TYPE_CRYPTO}},
		{X86_INS_AESENC,		{"aesenc", {0, 0, 0, 0}, H_INSTR_TYPE_CRYPTO}},
		{X86_INS_AESIMC,		{"aesimc", {0, 0, 0, 0}, H_INSTR_TYPE_CRYPTO}},
		{X86_INS_AESKEYGENASSIST,		{"aeskeygenassist", {0, 0, 0, 0}, H_INSTR_TYPE_CRYPTO}},


		{X86_INS_INSB, {"insb", {0, 0, 0, 0}}},
		{X86_INS_INSD, {"insd", {0, 0, 0, 0}}},
		{X86_INS_INSW, {"insw", {0, 0, 0, 0}}},

		{X86_INS_INSB | CUSOM_X86_INSTR_EXTR_REP, {"rep insb", {0, 0, 0, 0}}},
		{X86_INS_INSD | CUSOM_X86_INSTR_EXTR_REP, {"rep insd", {0, 0, 0, 0}}},
		{X86_INS_INSD | CUSOM_X86_INSTR_EXTR_REP, {"rep insw", {0, 0, 0, 0}}},

		{X86_INS_MOVSB,		{"movsb", {0, 0, 0, 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVSW,		{"movsw", {0, 0, 0, 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVSD,		{"movsd", {0, 0, 0, 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVSQ,		{"movsq", {0, 0, 0, 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_MOVSB | CUSOM_X86_INSTR_EXTR_REP,		{"rep movsb", {0, 0, 0, 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVSW | CUSOM_X86_INSTR_EXTR_REP,		{"rep movsw", {0, 0, 0, 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVSD | CUSOM_X86_INSTR_EXTR_REP,		{"rep movsd", {0, 0, 0, 0}, H_INSTR_TYPE_MOV}},
		{X86_INS_MOVSQ | CUSOM_X86_INSTR_EXTR_REP,		{"rep movsq", {0, 0, 0, 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_OUTSB, {"outsb", {0, 0, 0, 0}}},
		{X86_INS_OUTSD, {"outsd", {0, 0, 0, 0}}},
		{X86_INS_OUTSW, {"outsw", {0, 0, 0, 0}}},

		{X86_INS_OUTSB | CUSOM_X86_INSTR_EXTR_REP, {"rep outsb", {0, 0, 0, 0}}},
		{X86_INS_OUTSD | CUSOM_X86_INSTR_EXTR_REP, {"rep outsd", {0, 0, 0, 0}}},
		{X86_INS_OUTSW | CUSOM_X86_INSTR_EXTR_REP, {"rep outsw", {0, 0, 0, 0}}},

		{X86_INS_LODSB, {"lodsb", {0, 0, "#seq(=(#arg[1],#ld(#arg[2])),=($rdi,?($df,+($rdi,1),-($rdi,1))))", 0}, H_INSTR_TYPE_LOAD}},
		{X86_INS_LODSW, {"lodsw", {0, 0, "#seq(=(#arg[1],#ld(#arg[2])),=($rdi,?($df,+($rdi,2),-($rdi,2))))", 0}, H_INSTR_TYPE_LOAD}},
		{X86_INS_LODSD, {"lodsd", {0, 0, "#seq(=(#arg[1],#ld(#arg[2])),=($rdi,?($df,+($rdi,4),-($rdi,4))))", 0}, H_INSTR_TYPE_LOAD}},
		{X86_INS_LODSQ, {"lodsq", {0, 0, "#seq(=(#arg[1],#ld(#arg[2])),=($rdi,?($df,+($rdi,8),-($rdi,8))))", 0}, H_INSTR_TYPE_LOAD}},

		{X86_INS_LODSB | CUSOM_X86_INSTR_EXTR_REP, {"rep lodsb", {0, 0, "#rep($rcx,#rec[lodsb](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_LOAD}},
		{X86_INS_LODSW | CUSOM_X86_INSTR_EXTR_REP, {"rep lodsw", {0, 0, "#rep($rcx,#rec[lodsw](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_LOAD}},
		{X86_INS_LODSD | CUSOM_X86_INSTR_EXTR_REP, {"rep lodsd", {0, 0, "#rep($rcx,#rec[lodsd](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_LOAD}},
		{X86_INS_LODSQ | CUSOM_X86_INSTR_EXTR_REP, {"rep lodsq", {0, 0, "#rep($rcx,#rec[lodsq](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_LOAD}},

		{X86_INS_STOSB, {"stosb", {0, 0, "#seq(#st(#arg[2],#arg[1]),=($rdi,?($df,+($rdi,1),-($rdi,1))))", 0}, H_INSTR_TYPE_STORE}},
		{X86_INS_STOSW, {"stosw", {0, 0, "#seq(#st(#arg[2],#arg[1]),=($rdi,?($df,+($rdi,2),-($rdi,2))))", 0}, H_INSTR_TYPE_STORE}},
		{X86_INS_STOSD, {"stosd", {0, 0, "#seq(#st(#arg[2],#arg[1]),=($rdi,?($df,+($rdi,4),-($rdi,4))))", 0}, H_INSTR_TYPE_STORE}},
		{X86_INS_STOSQ, {"stosq", {0, 0, "#seq(#st(#arg[2],#arg[1]),=($rdi,?($df,+($rdi,8),-($rdi,8))))", 0}, H_INSTR_TYPE_STORE}},

		{X86_INS_STOSB | CUSOM_X86_INSTR_EXTR_REP, {"rep stosb", {0, 0, "#rep($rcx,#rec[stosb](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_STORE}},
		{X86_INS_STOSW | CUSOM_X86_INSTR_EXTR_REP, {"rep stosw", {0, 0, "#rep($rcx,#rec[stosw](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_STORE}},
		{X86_INS_STOSD | CUSOM_X86_INSTR_EXTR_REP, {"rep stosd", {0, 0, "#rep($rcx,#rec[stosd](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_STORE}},
		{X86_INS_STOSQ | CUSOM_X86_INSTR_EXTR_REP, {"rep stosq", {0, 0, "#rep($rcx,#rec[stosq](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_STORE}},

		{X86_INS_CMPSB, {"cmpsb", {0, 0, "#seq(#rec[cmp](#arg[1],#arg[2]),=($rdi,?($df,+($rdi,1),-($rdi,1))))", 0}, H_INSTR_TYPE_CMP}},
		{X86_INS_CMPSW, {"cmpsw", {0, 0, "#seq(#rec[cmp](#arg[1],#arg[2]),=($rdi,?($df,+($rdi,2),-($rdi,2))))", 0}, H_INSTR_TYPE_CMP}},
		{X86_INS_CMPSD, {"cmpsd", {0, 0, "#seq(#rec[cmp](#arg[1],#arg[2]),=($rdi,?($df,+($rdi,4),-($rdi,4))))", 0}, H_INSTR_TYPE_CMP}},
		{X86_INS_CMPSQ, {"cmpsq", {0, 0, "#seq(#rec[cmp](#arg[1],#arg[2]),=($rdi,?($df,+($rdi,8),-($rdi,8))))", 0}, H_INSTR_TYPE_CMP}},

		{X86_INS_CMPSB | CUSOM_X86_INSTR_EXTR_REPE, {"repe cmpsb", {0, 0, "#rep(#and($rcx,$zf),#rec[scasb](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_CMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_E}},
		{X86_INS_CMPSW | CUSOM_X86_INSTR_EXTR_REPE, {"repe cmpsw", {0, 0, "#rep(#and($rcx,$zf),#rec[scasw](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_CMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_E}},
		{X86_INS_CMPSD | CUSOM_X86_INSTR_EXTR_REPE, {"repe cmpsd", {0, 0, "#rep(#and($rcx,$zf),#rec[scasd](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_CMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_E}},
		{X86_INS_CMPSQ | CUSOM_X86_INSTR_EXTR_REPE, {"repe cmpsq", {0, 0, "#rep(#and($rcx,$zf),#rec[scasq](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_CMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_E}},

		{X86_INS_CMPSB | CUSOM_X86_INSTR_EXTR_REPNE, {"repne cmpsb", {0, 0, "#rep(#and($rcx,#not($zf)),#rec[scasb](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_CMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_NE}},
		{X86_INS_CMPSW | CUSOM_X86_INSTR_EXTR_REPNE, {"repne cmpsw", {0, 0, "#rep(#and($rcx,#not($zf)),#rec[scasw](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_CMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_NE}},
		{X86_INS_CMPSD | CUSOM_X86_INSTR_EXTR_REPNE, {"repne cmpsd", {0, 0, "#rep(#and($rcx,#not($zf)),#rec[scasd](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_CMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_NE}},
		{X86_INS_CMPSQ | CUSOM_X86_INSTR_EXTR_REPNE, {"repne cmpsq", {0, 0, "#rep(#and($rcx,#not($zf)),#rec[scasq](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_CMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_NE}},

		{X86_INS_SCASB, {"scasb", {0, 0, "#seq(#rec[cmp](#arg[1],#arg[2]),=($rdi,?($df,+($rdi,1),-($rdi,1))))", 0}, H_INSTR_TYPE_CMP}},
		{X86_INS_SCASW, {"scasw", {0, 0, "#seq(#rec[cmp](#arg[1],#arg[2]),=($rdi,?($df,+($rdi,2),-($rdi,2))))", 0}, H_INSTR_TYPE_CMP}},
		{X86_INS_SCASD, {"scasd", {0, 0, "#seq(#rec[cmp](#arg[1],#arg[2]),=($rdi,?($df,+($rdi,4),-($rdi,4))))", 0}, H_INSTR_TYPE_CMP}},
		{X86_INS_SCASQ, {"scasq", {0, 0, "#seq(#rec[cmp](#arg[1],#arg[2]),=($rdi,?($df,+($rdi,8),-($rdi,8))))", 0}, H_INSTR_TYPE_CMP}},

		{X86_INS_SCASB | CUSOM_X86_INSTR_EXTR_REPE, {"repe scasb", {0, 0, "#rep(#and($rcx,$zf),#rec[scasb](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_CMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_E}},
		{X86_INS_SCASW | CUSOM_X86_INSTR_EXTR_REPE, {"repe scasw", {0, 0, "#rep(#and($rcx,$zf),#rec[scasw](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_CMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_E}},
		{X86_INS_SCASD | CUSOM_X86_INSTR_EXTR_REPE, {"repe scasd", {0, 0, "#rep(#and($rcx,$zf),#rec[scasd](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_CMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_E}},
		{X86_INS_SCASQ | CUSOM_X86_INSTR_EXTR_REPE, {"repe scasq", {0, 0, "#rep(#and($rcx,$zf),#rec[scasq](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_CMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_E}},

		{X86_INS_SCASB | CUSOM_X86_INSTR_EXTR_REPNE, {"repne scasb", {0, 0, "#rep(#and($rcx,#not($zf)),#rec[scasb](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_CMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_NE}},
		{X86_INS_SCASW | CUSOM_X86_INSTR_EXTR_REPNE, {"repne scasw", {0, 0, "#rep(#and($rcx,#not($zf)),#rec[scasw](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_CMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_NE}},
		{X86_INS_SCASD | CUSOM_X86_INSTR_EXTR_REPNE, {"repne scasd", {0, 0, "#rep(#and($rcx,#not($zf)),#rec[scasd](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_CMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_NE}},
		{X86_INS_SCASQ | CUSOM_X86_INSTR_EXTR_REPNE, {"repne scasq", {0, 0, "#rep(#and($rcx,#not($zf)),#rec[scasq](#arg[1],#arg[2]))", 0}, H_INSTR_TYPE_CMP, H_INSTR_TYPE_UNKNOWN, H_INSTR_COND_NE}},

		{X86_INS_CMPSS, {"cmpss", {0, 0, 0, 0}}},

		{X86_INS_MOVSS,		{"movs", {0, 0, 0, 0}, H_INSTR_TYPE_MOV}},

		{X86_INS_ARPL,		{"arpl", {0, 0, 0, 0}}},
		{X86_INS_BEXTR,		{"bextr", {0, 0, 0, 0}}},
		{X86_INS_BLCFILL,	{"blcfill", {0, 0, 0, 0}}},
		{X86_INS_BLCI,		{"blci", {0, 0, 0, 0}}},
		{X86_INS_BLCIC,		{"blcic", {0, 0, 0, 0}}},
		{X86_INS_BLCMSK,	{"blcmsk", {0, 0, 0, 0}}},
		{X86_INS_BLCS,		{"blcs", {0, 0, 0, 0}}},
		{X86_INS_BLENDPD,	{"blendpd", {0, 0, 0, 0}}},
		{X86_INS_BLENDPS,	{"blendps", {0, 0, 0, 0}}},
		{X86_INS_BLENDVPD,	{"blendvpd", {0, 0, 0, 0}}},
		{X86_INS_BLENDVPS,	{"blendvps", {0, 0, 0, 0}}},
		{X86_INS_BLSFILL,	{"blsfill", {0, 0, 0, 0}}},
		{X86_INS_BLSI,		{"blsi", {0, 0, 0, 0}}},
		{X86_INS_BLSIC, {"blsic", {0, 0, 0, 0}}},
		{X86_INS_BLSMSK, {"blsmsk", {0, 0, 0, 0}}},
		{X86_INS_BLSR, {"blsr", {0, 0, 0, 0}}},
		{X86_INS_BZHI, {"bzhi", {0, 0, 0, 0}}},
		{X86_INS_FCHS, {"fchs", {0, 0, 0, 0}}},
		{X86_INS_CLAC, {"clac", {0, 0, 0, 0}}},
		{X86_INS_CLFLUSH, {"clflush", {0, 0, 0, 0}}},
		{X86_INS_CLGI, {"clgi", {0, 0, 0, 0}}},
		{X86_INS_CLTS, {"clts", {0, 0, 0, 0}}},
		{X86_INS_FCMOVBE, {"fcmovbe", {0, 0, 0, 0}}},
		{X86_INS_FCMOVB, {"fcmovb", {0, 0, 0, 0}}},
		{X86_INS_FCMOVE, {"fcmove", {0, 0, 0, 0}}},
		{X86_INS_FCMOVNBE, {"fcmovnbe", {0, 0, 0, 0}}},
		{X86_INS_FCMOVNB, {"fcmovnb", {0, 0, 0, 0}}},
		{X86_INS_FCMOVNE, {"fcmovne", {0, 0, 0, 0}}},
		{X86_INS_FCMOVNU, {"fcmovnu", {0, 0, 0, 0}}},
		{X86_INS_FCMOVU, {"fcmovu", {0, 0, 0, 0}}},
		{X86_INS_CMPPD, {"cmppd", {0, 0, 0, 0}}},
		{X86_INS_CMPPS, {"cmpps", {0, 0, 0, 0}}},
		{X86_INS_COMISD, {"comisd", {0, 0, 0, 0}}},
		{X86_INS_COMISS, {"comiss", {0, 0, 0, 0}}},
		{X86_INS_FCOMP, {"fcomp", {0, 0, 0, 0}}},
		{X86_INS_FCOMPI, {"fcompi", {0, 0, 0, 0}}},
		{X86_INS_FCOMI, {"fcomi", {0, 0, 0, 0}}},
		{X86_INS_FCOM, {"fcom", {0, 0, 0, 0}}},
		{X86_INS_FCOS, {"fcos", {0, 0, 0, 0}}},
		{X86_INS_CPUID, {"cpuid", {0, 0, 0, 0}}},
		{X86_INS_DATA16, {"data16", {0, 0, 0, 0}}},
		{X86_INS_DIVPD, {"divpd", {0, 0, 0, 0}}},
		{X86_INS_DIVPS, {"divps", {0, 0, 0, 0}}},
		{X86_INS_FDIVR, {"fdivr", {0, 0, 0, 0}}},
		{X86_INS_FIDIVR, {"fidivr", {0, 0, 0, 0}}},
		{X86_INS_FDIVRP, {"fdivrp", {0, 0, 0, 0}}},
		{X86_INS_DIVSD, {"divsd", {0, 0, 0, 0}}},
		{X86_INS_DIVSS, {"divss", {0, 0, 0, 0}}},
		{X86_INS_FDIV, {"fdiv", {0, 0, 0, 0}}},
		{X86_INS_FIDIV, {"fidiv", {0, 0, 0, 0}}},
		{X86_INS_FDIVP, {"fdivp", {0, 0, 0, 0}}},
		{X86_INS_DPPD, {"dppd", {0, 0, 0, 0}}},
		{X86_INS_DPPS, {"dpps", {0, 0, 0, 0}}},
		{X86_INS_ENCLS, {"encls", {0, 0, 0, 0}}},
		{X86_INS_ENCLU, {"enclu", {0, 0, 0, 0}}},
		{X86_INS_EXTRACTPS, {"extractps", {0, 0, 0, 0}}},
		{X86_INS_EXTRQ, {"extrq", {0, 0, 0, 0}}},
		{X86_INS_F2XM1, {"f2xm1", {0, 0, 0, 0}}},
		{X86_INS_LCALL, {"lcall", {0, 0, 0, 0}}},
		{X86_INS_LJMP, {"ljmp", {0, 0, 0, 0}}},
		{X86_INS_FBLD, {"fbld", {0, 0, 0, 0}}},
		{X86_INS_FBSTP, {"fbstp", {0, 0, 0, 0}}},
		{X86_INS_FCOMPP, {"fcompp", {0, 0, 0, 0}}},
		{X86_INS_FDECSTP, {"fdecstp", {0, 0, 0, 0}}},
		{X86_INS_FEMMS, {"femms", {0, 0, 0, 0}}},
		{X86_INS_FFREE, {"ffree", {0, 0, 0, 0}}},
		{X86_INS_FICOM, {"ficom", {0, 0, 0, 0}}},
		{X86_INS_FICOMP, {"ficomp", {0, 0, 0, 0}}},
		{X86_INS_FINCSTP, {"fincstp", {0, 0, 0, 0}}},
		{X86_INS_FLDCW, {"fldcw", {0, 0, 0, 0}}},
		{X86_INS_FLDENV, {"fldenv", {0, 0, 0, 0}}},
		{X86_INS_FLDL2E, {"fldl2e", {0, 0, 0, 0}}},
		{X86_INS_FLDL2T, {"fldl2t", {0, 0, 0, 0}}},
		{X86_INS_FLDLG2, {"fldlg2", {0, 0, 0, 0}}},
		{X86_INS_FLDLN2, {"fldln2", {0, 0, 0, 0}}},
		{X86_INS_FLDPI, {"fldpi", {0, 0, 0, 0}}},
		{X86_INS_FNCLEX, {"fnclex", {0, 0, 0, 0}}},
		{X86_INS_FNINIT, {"fninit", {0, 0, 0, 0}}},
		{X86_INS_FNOP, {"fnop", {0, 0, 0, 0}}},
		{X86_INS_FNSTCW, {"fnstcw", {0, 0, 0, 0}}},
		{X86_INS_FNSTSW, {"fnstsw", {0, 0, 0, 0}}},
		{X86_INS_FPATAN, {"fpatan", {0, 0, 0, 0}}},
		{X86_INS_FPREM, {"fprem", {0, 0, 0, 0}}},
		{X86_INS_FPREM1, {"fprem1", {0, 0, 0, 0}}},
		{X86_INS_FPTAN, {"fptan", {0, 0, 0, 0}}},
		{X86_INS_FRNDINT, {"frndint", {0, 0, 0, 0}}},
		{X86_INS_FRSTOR, {"frstor", {0, 0, 0, 0}}},
		{X86_INS_FNSAVE, {"fnsave", {0, 0, 0, 0}}},
		{X86_INS_FSCALE, {"fscale", {0, 0, 0, 0}}},
		{X86_INS_FSETPM, {"fsetpm", {0, 0, 0, 0}}},
		{X86_INS_FSINCOS, {"fsincos", {0, 0, 0, 0}}},
		{X86_INS_FNSTENV, {"fnstenv", {0, 0, 0, 0}}},
		{X86_INS_FXAM, {"fxam", {0, 0, 0, 0}}},
		{X86_INS_FXRSTOR, {"fxrstor", {0, 0, 0, 0}}},
		{X86_INS_FXRSTOR64, {"fxrstor64", {0, 0, 0, 0}}},
		{X86_INS_FXSAVE, {"fxsave", {0, 0, 0, 0}}},
		{X86_INS_FXSAVE64, {"fxsave64", {0, 0, 0, 0}}},
		{X86_INS_FXTRACT, {"fxtract", {0, 0, 0, 0}}},
		{X86_INS_FYL2X, {"fyl2x", {0, 0, 0, 0}}},
		{X86_INS_FYL2XP1, {"fyl2xp1", {0, 0, 0, 0}}},
		{X86_INS_MOVAPD, {"movapd", {0, 0, 0, 0}}},
		{X86_INS_MOVAPS, {"movaps", {0, 0, 0, 0}}},
		{X86_INS_VMOVAPD, {"vmovapd", {0, 0, 0, 0}}},
		{X86_INS_VMOVAPS, {"vmovaps", {0, 0, 0, 0}}},
		{X86_INS_GETSEC, {"getsec", {0, 0, 0, 0}}},
		{X86_INS_HADDPD, {"haddpd", {0, 0, 0, 0}}},
		{X86_INS_HADDPS, {"haddps", {0, 0, 0, 0}}},
		{X86_INS_HSUBPD, {"hsubpd", {0, 0, 0, 0}}},
		{X86_INS_HSUBPS, {"hsubps", {0, 0, 0, 0}}},
		{X86_INS_FILD, {"fild", {0, 0, 0, 0}}},
		{X86_INS_IN, {"in", {0, 0, 0, 0}}},
		{X86_INS_INSERTPS, {"insertps", {0, 0, 0, 0}}},
		{X86_INS_INSERTQ, {"insertq", {0, 0, 0, 0}}},
		{X86_INS_INT1, {"int1", {0, 0, 0, 0}}},
		{X86_INS_INT3, {"int3", {0, 0, 0, 0}}},
		{X86_INS_INVD, {"invd", {0, 0, 0, 0}}},
		{X86_INS_INVEPT, {"invept", {0, 0, 0, 0}}},
		{X86_INS_INVLPG, {"invlpg", {0, 0, 0, 0}}},
		{X86_INS_INVLPGA, {"invlpga", {0, 0, 0, 0}}},
		{X86_INS_INVPCID, {"invpcid", {0, 0, 0, 0}}},
		{X86_INS_INVVPID, {"invvpid", {0, 0, 0, 0}}},
		{X86_INS_FISTTP, {"fisttp", {0, 0, 0, 0}}},
		{X86_INS_FIST, {"fist", {0, 0, 0, 0}}},
		{X86_INS_FISTP, {"fistp", {0, 0, 0, 0}}},
		{X86_INS_UCOMISD, {"ucomisd", {0, 0, 0, 0}}},
		{X86_INS_UCOMISS, {"ucomiss", {0, 0, 0, 0}}},
		{X86_INS_VCMP, {"vcmp", {0, 0, 0, 0}}},
		{X86_INS_VCOMISD, {"vcomisd", {0, 0, 0, 0}}},
		{X86_INS_VCOMISS, {"vcomiss", {0, 0, 0, 0}}},
		{X86_INS_VCVTSD2SS, {"vcvtsd2ss", {0, 0, 0, 0}}},
		{X86_INS_VCVTSI2SD, {"vcvtsi2sd", {0, 0, 0, 0}}},
		{X86_INS_VCVTSI2SS, {"vcvtsi2ss", {0, 0, 0, 0}}},
		{X86_INS_VCVTSS2SD, {"vcvtss2sd", {0, 0, 0, 0}}},
		{X86_INS_VCVTTSD2SI, {"vcvttsd2si", {0, 0, 0, 0}}},
		{X86_INS_VCVTTSD2USI, {"vcvttsd2usi", {0, 0, 0, 0}}},
		{X86_INS_VCVTTSS2SI, {"vcvttss2si", {0, 0, 0, 0}}},
		{X86_INS_VCVTTSS2USI, {"vcvttss2usi", {0, 0, 0, 0}}},
		{X86_INS_VCVTUSI2SD, {"vcvtusi2sd", {0, 0, 0, 0}}},
		{X86_INS_VCVTUSI2SS, {"vcvtusi2ss", {0, 0, 0, 0}}},
		{X86_INS_VUCOMISD, {"vucomisd", {0, 0, 0, 0}}},
		{X86_INS_VUCOMISS, {"vucomiss", {0, 0, 0, 0}}},
		{X86_INS_KANDB, {"kandb", {0, 0, 0, 0}}},
		{X86_INS_KANDD, {"kandd", {0, 0, 0, 0}}},
		{X86_INS_KANDNB, {"kandnb", {0, 0, 0, 0}}},
		{X86_INS_KANDND, {"kandnd", {0, 0, 0, 0}}},
		{X86_INS_KANDNQ, {"kandnq", {0, 0, 0, 0}}},
		{X86_INS_KANDNW, {"kandnw", {0, 0, 0, 0}}},
		{X86_INS_KANDQ, {"kandq", {0, 0, 0, 0}}},
		{X86_INS_KANDW, {"kandw", {0, 0, 0, 0}}},
		{X86_INS_KMOVB, {"kmovb", {0, 0, 0, 0}}},
		{X86_INS_KMOVD, {"kmovd", {0, 0, 0, 0}}},
		{X86_INS_KMOVQ, {"kmovq", {0, 0, 0, 0}}},
		{X86_INS_KMOVW, {"kmovw", {0, 0, 0, 0}}},
		{X86_INS_KNOTD, {"knotd", {0, 0, 0, 0}}},
		{X86_INS_KNOTQ, {"knotq", {0, 0, 0, 0}}},
		{X86_INS_KNOTW, {"knotw", {0, 0, 0, 0}}},
		{X86_INS_KORB, {"korb", {0, 0, 0, 0}}},
		{X86_INS_KORD, {"kord", {0, 0, 0, 0}}},
		{X86_INS_KORQ, {"korq", {0, 0, 0, 0}}},
		{X86_INS_KORTESTW, {"kortestw", {0, 0, 0, 0}}},
		{X86_INS_KORW, {"korw", {0, 0, 0, 0}}},
		{X86_INS_KSHIFTLW, {"kshiftlw", {0, 0, 0, 0}}},
		{X86_INS_KSHIFTRW, {"kshiftrw", {0, 0, 0, 0}}},
		{X86_INS_KUNPCKBW, {"kunpckbw", {0, 0, 0, 0}}},
		{X86_INS_KXNORB, {"kxnorb", {0, 0, 0, 0}}},
		{X86_INS_KXNORD, {"kxnord", {0, 0, 0, 0}}},
		{X86_INS_KXNORQ, {"kxnorq", {0, 0, 0, 0}}},
		{X86_INS_KXNORW, {"kxnorw", {0, 0, 0, 0}}},
		{X86_INS_KXORB, {"kxorb", {0, 0, 0, 0}}},
		{X86_INS_KXORD, {"kxord", {0, 0, 0, 0}}},
		{X86_INS_KXORQ, {"kxorq", {0, 0, 0, 0}}},
		{X86_INS_KXORW, {"kxorw", {0, 0, 0, 0}}},
		{X86_INS_LAR, {"lar", {0, 0, 0, 0}}},
		{X86_INS_LDDQU, {"lddqu", {0, 0, 0, 0}}},
		{X86_INS_LDMXCSR, {"ldmxcsr", {0, 0, 0, 0}}},
		{X86_INS_LDS, {"lds", {0, 0, 0, 0}}},
		{X86_INS_FLDZ, {"fldz", {0, 0, 0, 0}}},
		{X86_INS_FLD1, {"fld1", {0, 0, 0, 0}}},
		{X86_INS_FLD, {"fld", {0, 0, 0, 0}}},
		{X86_INS_LES, {"les", {0, 0, 0, 0}}},
		{X86_INS_LFENCE, {"lfence", {0, 0, 0, 0}}},
		{X86_INS_LFS, {"lfs", {0, 0, 0, 0}}},
		{X86_INS_LGDT, {"lgdt", {0, 0, 0, 0}}},
		{X86_INS_LGS, {"lgs", {0, 0, 0, 0}}},
		{X86_INS_LIDT, {"lidt", {0, 0, 0, 0}}},
		{X86_INS_LLDT, {"lldt", {0, 0, 0, 0}}},
		{X86_INS_LMSW, {"lmsw", {0, 0, 0, 0}}},
		{X86_INS_LSL, {"lsl", {0, 0, 0, 0}}},
		{X86_INS_LSS, {"lss", {0, 0, 0, 0}}},
		{X86_INS_LTR, {"ltr", {0, 0, 0, 0}}},
		{X86_INS_LZCNT, {"lzcnt", {0, 0, 0, 0}}},
		{X86_INS_MASKMOVDQU, {"maskmovdqu", {0, 0, 0, 0}}},
		{X86_INS_MAXPD, {"maxpd", {0, 0, 0, 0}}},
		{X86_INS_MAXPS, {"maxps", {0, 0, 0, 0}}},
		{X86_INS_MAXSD, {"maxsd", {0, 0, 0, 0}}},
		{X86_INS_MAXSS, {"maxss", {0, 0, 0, 0}}},
		{X86_INS_MFENCE, {"mfence", {0, 0, 0, 0}}},
		{X86_INS_MINPD, {"minpd", {0, 0, 0, 0}}},
		{X86_INS_MINPS, {"minps", {0, 0, 0, 0}}},
		{X86_INS_MINSD, {"minsd", {0, 0, 0, 0}}},
		{X86_INS_MINSS, {"minss", {0, 0, 0, 0}}},
		{X86_INS_CVTPD2PI, {"cvtpd2pi", {0, 0, 0, 0}}},
		{X86_INS_CVTPI2PD, {"cvtpi2pd", {0, 0, 0, 0}}},
		{X86_INS_CVTPI2PS, {"cvtpi2ps", {0, 0, 0, 0}}},
		{X86_INS_CVTPS2PI, {"cvtps2pi", {0, 0, 0, 0}}},
		{X86_INS_CVTTPD2PI, {"cvttpd2pi", {0, 0, 0, 0}}},
		{X86_INS_CVTTPS2PI, {"cvttps2pi", {0, 0, 0, 0}}},
		{X86_INS_EMMS, {"emms", {0, 0, 0, 0}}},
		{X86_INS_MASKMOVQ, {"maskmovq", {0, 0, 0, 0}}},
		{X86_INS_MOVDQ2Q, {"movdq2q", {0, 0, 0, 0}}},
		{X86_INS_MOVNTQ, {"movntq", {0, 0, 0, 0}}},
		{X86_INS_MOVQ2DQ, {"movq2dq", {0, 0, 0, 0}}},
		{X86_INS_PABSB, {"pabsb", {0, 0, 0, 0}}},
		{X86_INS_PABSD, {"pabsd", {0, 0, 0, 0}}},
		{X86_INS_PABSW, {"pabsw", {0, 0, 0, 0}}},
		{X86_INS_PACKSSDW, {"packssdw", {0, 0, 0, 0}}},
		{X86_INS_PACKSSWB, {"packsswb", {0, 0, 0, 0}}},
		{X86_INS_PACKUSWB, {"packuswb", {0, 0, 0, 0}}},
		{X86_INS_PADDB, {"paddb", {0, 0, 0, 0}}},
		{X86_INS_PADDD, {"paddd", {0, 0, 0, 0}}},
		{X86_INS_PADDQ, {"paddq", {0, 0, 0, 0}}},
		{X86_INS_PADDSB, {"paddsb", {0, 0, 0, 0}}},
		{X86_INS_PADDSW, {"paddsw", {0, 0, 0, 0}}},
		{X86_INS_PADDUSB, {"paddusb", {0, 0, 0, 0}}},
		{X86_INS_PADDUSW, {"paddusw", {0, 0, 0, 0}}},
		{X86_INS_PADDW, {"paddw", {0, 0, 0, 0}}},
		{X86_INS_PALIGNR, {"palignr", {0, 0, 0, 0}}},
		{X86_INS_PAVGB, {"pavgb", {0, 0, 0, 0}}},
		{X86_INS_PAVGW, {"pavgw", {0, 0, 0, 0}}},
		{X86_INS_PCMPEQB, {"pcmpeqb", {0, 0, 0, 0}}},
		{X86_INS_PCMPEQD, {"pcmpeqd", {0, 0, 0, 0}}},
		{X86_INS_PCMPEQW, {"pcmpeqw", {0, 0, 0, 0}}},
		{X86_INS_PCMPGTB, {"pcmpgtb", {0, 0, 0, 0}}},
		{X86_INS_PCMPGTD, {"pcmpgtd", {0, 0, 0, 0}}},
		{X86_INS_PCMPGTW, {"pcmpgtw", {0, 0, 0, 0}}},
		{X86_INS_PEXTRW, {"pextrw", {0, 0, 0, 0}}},
		{X86_INS_PHADDSW, {"phaddsw", {0, 0, 0, 0}}},
		{X86_INS_PHADDW, {"phaddw", {0, 0, 0, 0}}},
		{X86_INS_PHADDD, {"phaddd", {0, 0, 0, 0}}},
		{X86_INS_PHSUBD, {"phsubd", {0, 0, 0, 0}}},
		{X86_INS_PHSUBSW, {"phsubsw", {0, 0, 0, 0}}},
		{X86_INS_PHSUBW, {"phsubw", {0, 0, 0, 0}}},
		{X86_INS_PINSRW, {"pinsrw", {0, 0, 0, 0}}},
		{X86_INS_PMADDUBSW, {"pmaddubsw", {0, 0, 0, 0}}},
		{X86_INS_PMADDWD, {"pmaddwd", {0, 0, 0, 0}}},
		{X86_INS_PMAXSW, {"pmaxsw", {0, 0, 0, 0}}},
		{X86_INS_PMAXUB, {"pmaxub", {0, 0, 0, 0}}},
		{X86_INS_PMINSW, {"pminsw", {0, 0, 0, 0}}},
		{X86_INS_PMINUB, {"pminub", {0, 0, 0, 0}}},
		{X86_INS_PMOVMSKB, {"pmovmskb", {0, 0, 0, 0}}},
		{X86_INS_PMULHRSW, {"pmulhrsw", {0, 0, 0, 0}}},
		{X86_INS_PMULHUW, {"pmulhuw", {0, 0, 0, 0}}},
		{X86_INS_PMULHW, {"pmulhw", {0, 0, 0, 0}}},
		{X86_INS_PMULLW, {"pmullw", {0, 0, 0, 0}}},
		{X86_INS_PMULUDQ, {"pmuludq", {0, 0, 0, 0}}},
		{X86_INS_PSADBW, {"psadbw", {0, 0, 0, 0}}},
		{X86_INS_PSHUFB, {"pshufb", {0, 0, 0, 0}}},
		{X86_INS_PSHUFW, {"pshufw", {0, 0, 0, 0}}},
		{X86_INS_PSIGNB, {"psignb", {0, 0, 0, 0}}},
		{X86_INS_PSIGND, {"psignd", {0, 0, 0, 0}}},
		{X86_INS_PSIGNW, {"psignw", {0, 0, 0, 0}}},
		{X86_INS_PSLLD, {"pslld", {0, 0, 0, 0}}},
		{X86_INS_PSLLQ, {"psllq", {0, 0, 0, 0}}},
		{X86_INS_PSLLW, {"psllw", {0, 0, 0, 0}}},
		{X86_INS_PSRAD, {"psrad", {0, 0, 0, 0}}},
		{X86_INS_PSRAW, {"psraw", {0, 0, 0, 0}}},
		{X86_INS_PSRLD, {"psrld", {0, 0, 0, 0}}},
		{X86_INS_PSRLQ, {"psrlq", {0, 0, 0, 0}}},
		{X86_INS_PSRLW, {"psrlw", {0, 0, 0, 0}}},
		{X86_INS_PSUBB, {"psubb", {0, 0, 0, 0}}},
		{X86_INS_PSUBD, {"psubd", {0, 0, 0, 0}}},
		{X86_INS_PSUBQ, {"psubq", {0, 0, 0, 0}}},
		{X86_INS_PSUBSB, {"psubsb", {0, 0, 0, 0}}},
		{X86_INS_PSUBSW, {"psubsw", {0, 0, 0, 0}}},
		{X86_INS_PSUBUSB, {"psubusb", {0, 0, 0, 0}}},
		{X86_INS_PSUBUSW, {"psubusw", {0, 0, 0, 0}}},
		{X86_INS_PSUBW, {"psubw", {0, 0, 0, 0}}},
		{X86_INS_PUNPCKHBW, {"punpckhbw", {0, 0, 0, 0}}},
		{X86_INS_PUNPCKHDQ, {"punpckhdq", {0, 0, 0, 0}}},
		{X86_INS_PUNPCKHWD, {"punpckhwd", {0, 0, 0, 0}}},
		{X86_INS_PUNPCKLBW, {"punpcklbw", {0, 0, 0, 0}}},
		{X86_INS_PUNPCKLDQ, {"punpckldq", {0, 0, 0, 0}}},
		{X86_INS_PUNPCKLWD, {"punpcklwd", {0, 0, 0, 0}}},
		{X86_INS_MONITOR, {"monitor", {0, 0, 0, 0}}},
		{X86_INS_MONTMUL, {"montmul", {0, 0, 0, 0}}},
		{X86_INS_MPSADBW, {"mpsadbw", {0, 0, 0, 0}}},
		{X86_INS_MULPD, {"mulpd", {0, 0, 0, 0}}},
		{X86_INS_MULPS, {"mulps", {0, 0, 0, 0}}},
		{X86_INS_MULSD, {"mulsd", {0, 0, 0, 0}}},
		{X86_INS_MULSS, {"mulss", {0, 0, 0, 0}}},
		{X86_INS_MULX, {"mulx", {0, 0, 0, 0}}},
		{X86_INS_FMUL, {"fmul", {0, 0, 0, 0}}},
		{X86_INS_FIMUL, {"fimul", {0, 0, 0, 0}}},
		{X86_INS_FMULP, {"fmulp", {0, 0, 0, 0}}},
		{X86_INS_MWAIT, {"mwait", {0, 0, 0, 0}}},
		{X86_INS_NEG, {"neg", {0, 0, 0, 0}}},
		{X86_INS_NOP, {"nop", {0, 0, 0, 0}}},
		{X86_INS_OUT, {"out", {0, 0, 0, 0}}},
		{X86_INS_PACKUSDW, {"packusdw", {0, 0, 0, 0}}},
		{X86_INS_PAUSE, {"pause", {0, 0, 0, 0}}},
		{X86_INS_PAVGUSB, {"pavgusb", {0, 0, 0, 0}}},
		{X86_INS_PBLENDVB, {"pblendvb", {0, 0, 0, 0}}},
		{X86_INS_PBLENDW, {"pblendw", {0, 0, 0, 0}}},
		{X86_INS_PCLMULQDQ, {"pclmulqdq", {0, 0, 0, 0}}},
		{X86_INS_PCMPEQQ, {"pcmpeqq", {0, 0, 0, 0}}},
		{X86_INS_PCMPESTRI, {"pcmpestri", {0, 0, 0, 0}}},
		{X86_INS_PCMPESTRM, {"pcmpestrm", {0, 0, 0, 0}}},
		{X86_INS_PCMPGTQ, {"pcmpgtq", {0, 0, 0, 0}}},
		{X86_INS_PCMPISTRI, {"pcmpistri", {0, 0, 0, 0}}},
		{X86_INS_PCMPISTRM, {"pcmpistrm", {0, 0, 0, 0}}},
		{X86_INS_PDEP, {"pdep", {0, 0, 0, 0}}},
		{X86_INS_PEXT, {"pext", {0, 0, 0, 0}}},
		{X86_INS_PEXTRB, {"pextrb", {0, 0, 0, 0}}},
		{X86_INS_PEXTRD, {"pextrd", {0, 0, 0, 0}}},
		{X86_INS_PEXTRQ, {"pextrq", {0, 0, 0, 0}}},
		{X86_INS_PF2ID, {"pf2id", {0, 0, 0, 0}}},
		{X86_INS_PF2IW, {"pf2iw", {0, 0, 0, 0}}},
		{X86_INS_PFACC, {"pfacc", {0, 0, 0, 0}}},
		{X86_INS_PFADD, {"pfadd", {0, 0, 0, 0}}},
		{X86_INS_PFCMPEQ, {"pfcmpeq", {0, 0, 0, 0}}},
		{X86_INS_PFCMPGE, {"pfcmpge", {0, 0, 0, 0}}},
		{X86_INS_PFCMPGT, {"pfcmpgt", {0, 0, 0, 0}}},
		{X86_INS_PFMAX, {"pfmax", {0, 0, 0, 0}}},
		{X86_INS_PFMIN, {"pfmin", {0, 0, 0, 0}}},
		{X86_INS_PFMUL, {"pfmul", {0, 0, 0, 0}}},
		{X86_INS_PFNACC, {"pfnacc", {0, 0, 0, 0}}},
		{X86_INS_PFPNACC, {"pfpnacc", {0, 0, 0, 0}}},
		{X86_INS_PFRCPIT1, {"pfrcpit1", {0, 0, 0, 0}}},
		{X86_INS_PFRCPIT2, {"pfrcpit2", {0, 0, 0, 0}}},
		{X86_INS_PFRCP, {"pfrcp", {0, 0, 0, 0}}},
		{X86_INS_PFRSQIT1, {"pfrsqit1", {0, 0, 0, 0}}},
		{X86_INS_PFRSQRT, {"pfrsqrt", {0, 0, 0, 0}}},
		{X86_INS_PFSUBR, {"pfsubr", {0, 0, 0, 0}}},
		{X86_INS_PFSUB, {"pfsub", {0, 0, 0, 0}}},
		{X86_INS_PHMINPOSUW, {"phminposuw", {0, 0, 0, 0}}},
		{X86_INS_PI2FD, {"pi2fd", {0, 0, 0, 0}}},
		{X86_INS_PI2FW, {"pi2fw", {0, 0, 0, 0}}},
		{X86_INS_PINSRB, {"pinsrb", {0, 0, 0, 0}}},
		{X86_INS_PINSRD, {"pinsrd", {0, 0, 0, 0}}},
		{X86_INS_PINSRQ, {"pinsrq", {0, 0, 0, 0}}},
		{X86_INS_PMAXSB, {"pmaxsb", {0, 0, 0, 0}}},
		{X86_INS_PMAXSD, {"pmaxsd", {0, 0, 0, 0}}},
		{X86_INS_PMAXUD, {"pmaxud", {0, 0, 0, 0}}},
		{X86_INS_PMAXUW, {"pmaxuw", {0, 0, 0, 0}}},
		{X86_INS_PMINSB, {"pminsb", {0, 0, 0, 0}}},
		{X86_INS_PMINSD, {"pminsd", {0, 0, 0, 0}}},
		{X86_INS_PMINUD, {"pminud", {0, 0, 0, 0}}},
		{X86_INS_PMINUW, {"pminuw", {0, 0, 0, 0}}},
		{X86_INS_PMOVSXBD, {"pmovsxbd", {0, 0, 0, 0}}},
		{X86_INS_PMOVSXBQ, {"pmovsxbq", {0, 0, 0, 0}}},
		{X86_INS_PMOVSXBW, {"pmovsxbw", {0, 0, 0, 0}}},
		{X86_INS_PMOVSXDQ, {"pmovsxdq", {0, 0, 0, 0}}},
		{X86_INS_PMOVSXWD, {"pmovsxwd", {0, 0, 0, 0}}},
		{X86_INS_PMOVSXWQ, {"pmovsxwq", {0, 0, 0, 0}}},
		{X86_INS_PMOVZXBD, {"pmovzxbd", {0, 0, 0, 0}}},
		{X86_INS_PMOVZXBQ, {"pmovzxbq", {0, 0, 0, 0}}},
		{X86_INS_PMOVZXBW, {"pmovzxbw", {0, 0, 0, 0}}},
		{X86_INS_PMOVZXDQ, {"pmovzxdq", {0, 0, 0, 0}}},
		{X86_INS_PMOVZXWD, {"pmovzxwd", {0, 0, 0, 0}}},
		{X86_INS_PMOVZXWQ, {"pmovzxwq", {0, 0, 0, 0}}},
		{X86_INS_PMULDQ, {"pmuldq", {0, 0, 0, 0}}},
		{X86_INS_PMULHRW, {"pmulhrw", {0, 0, 0, 0}}},
		{X86_INS_PMULLD, {"pmulld", {0, 0, 0, 0}}},
		{X86_INS_PREFETCH, {"prefetch", {0, 0, 0, 0}}},
		{X86_INS_PREFETCHNTA, {"prefetchnta", {0, 0, 0, 0}}},
		{X86_INS_PREFETCHT0, {"prefetcht0", {0, 0, 0, 0}}},
		{X86_INS_PREFETCHT1, {"prefetcht1", {0, 0, 0, 0}}},
		{X86_INS_PREFETCHT2, {"prefetcht2", {0, 0, 0, 0}}},
		{X86_INS_PREFETCHW, {"prefetchw", {0, 0, 0, 0}}},
		{X86_INS_PSHUFD, {"pshufd", {0, 0, 0, 0}}},
		{X86_INS_PSHUFHW, {"pshufhw", {0, 0, 0, 0}}},
		{X86_INS_PSHUFLW, {"pshuflw", {0, 0, 0, 0}}},
		{X86_INS_PSLLDQ, {"pslldq", {0, 0, 0, 0}}},
		{X86_INS_PSRLDQ, {"psrldq", {0, 0, 0, 0}}},
		{X86_INS_PSWAPD, {"pswapd", {0, 0, 0, 0}}},
		{X86_INS_PTEST, {"ptest", {0, 0, 0, 0}}},
		{X86_INS_PUNPCKHQDQ, {"punpckhqdq", {0, 0, 0, 0}}},
		{X86_INS_PUNPCKLQDQ, {"punpcklqdq", {0, 0, 0, 0}}},
		{X86_INS_RCPPS, {"rcpps", {0, 0, 0, 0}}},
		{X86_INS_RCPSS, {"rcpss", {0, 0, 0, 0}}},
		{X86_INS_RDFSBASE, {"rdfsbase", {0, 0, 0, 0}}},
		{X86_INS_RDGSBASE, {"rdgsbase", {0, 0, 0, 0}}},
		{X86_INS_RDMSR, {"rdmsr", {0, 0, 0, 0}}},
		{X86_INS_RDPMC, {"rdpmc", {0, 0, 0, 0}}},
		{X86_INS_RDRAND, {"rdrand", {0, 0, 0, 0}}},
		{X86_INS_RDSEED, {"rdseed", {0, 0, 0, 0}}},
		{X86_INS_RDTSC, {"rdtsc", {0, 0, 0, 0}}},
		{X86_INS_RDTSCP, {"rdtscp", {0, 0, 0, 0}}},
		{X86_INS_RORX, {"rorx", {0, 0, 0, 0}}},
		{X86_INS_ROUNDPD, {"roundpd", {0, 0, 0, 0}}},
		{X86_INS_ROUNDPS, {"roundps", {0, 0, 0, 0}}},
		{X86_INS_ROUNDSD, {"roundsd", {0, 0, 0, 0}}},
		{X86_INS_ROUNDSS, {"roundss", {0, 0, 0, 0}}},
		{X86_INS_RSM, {"rsm", {0, 0, 0, 0}}},
		{X86_INS_RSQRTPS, {"rsqrtps", {0, 0, 0, 0}}},
		{X86_INS_RSQRTSS, {"rsqrtss", {0, 0, 0, 0}}},
		{X86_INS_SALC, {"salc", {0, 0, 0, 0}}},
		{X86_INS_SARX, {"sarx", {0, 0, 0, 0}}},
		{X86_INS_SFENCE, {"sfence", {0, 0, 0, 0}}},
		{X86_INS_SGDT, {"sgdt", {0, 0, 0, 0}}},
		{X86_INS_SHA1MSG1, {"sha1msg1", {0, 0, 0, 0}}},
		{X86_INS_SHA1MSG2, {"sha1msg2", {0, 0, 0, 0}}},
		{X86_INS_SHA1NEXTE, {"sha1nexte", {0, 0, 0, 0}}},
		{X86_INS_SHA1RNDS4, {"sha1rnds4", {0, 0, 0, 0}}},
		{X86_INS_SHA256MSG1, {"sha256msg1", {0, 0, 0, 0}}},
		{X86_INS_SHA256MSG2, {"sha256msg2", {0, 0, 0, 0}}},
		{X86_INS_SHA256RNDS2, {"sha256rnds2", {0, 0, 0, 0}}},
		{X86_INS_SHLX, {"shlx", {0, 0, 0, 0}}},
		{X86_INS_SHRX, {"shrx", {0, 0, 0, 0}}},
		{X86_INS_SHUFPD, {"shufpd", {0, 0, 0, 0}}},
		{X86_INS_SHUFPS, {"shufps", {0, 0, 0, 0}}},
		{X86_INS_SIDT, {"sidt", {0, 0, 0, 0}}},
		{X86_INS_FSIN, {"fsin", {0, 0, 0, 0}}},
		{X86_INS_SKINIT, {"skinit", {0, 0, 0, 0}}},
		{X86_INS_SLDT, {"sldt", {0, 0, 0, 0}}},
		{X86_INS_SMSW, {"smsw", {0, 0, 0, 0}}},
		{X86_INS_SQRTPD, {"sqrtpd", {0, 0, 0, 0}}},
		{X86_INS_SQRTPS, {"sqrtps", {0, 0, 0, 0}}},
		{X86_INS_SQRTSD, {"sqrtsd", {0, 0, 0, 0}}},
		{X86_INS_SQRTSS, {"sqrtss", {0, 0, 0, 0}}},
		{X86_INS_FSQRT, {"fsqrt", {0, 0, 0, 0}}},
		{X86_INS_STAC, {"stac", {0, 0, 0, 0}}},
		{X86_INS_STGI, {"stgi", {0, 0, 0, 0}}},
		{X86_INS_STMXCSR, {"stmxcsr", {0, 0, 0, 0}}},
		{X86_INS_STR, {"str", {0, 0, 0, 0}}},
		{X86_INS_FST, {"fst", {0, 0, 0, 0}}},
		{X86_INS_FSTP, {"fstp", {0, 0, 0, 0}}},
		{X86_INS_FSTPNCE, {"fstpnce", {0, 0, 0, 0}}},
		{X86_INS_SUBPD, {"subpd", {0, 0, 0, 0}}},
		{X86_INS_SUBPS, {"subps", {0, 0, 0, 0}}},
		{X86_INS_FSUBR, {"fsubr", {0, 0, 0, 0}}},
		{X86_INS_FISUBR, {"fisubr", {0, 0, 0, 0}}},
		{X86_INS_FSUBRP, {"fsubrp", {0, 0, 0, 0}}},
		{X86_INS_SUBSD, {"subsd", {0, 0, 0, 0}}},
		{X86_INS_SUBSS, {"subss", {0, 0, 0, 0}}},
		{X86_INS_FSUB, {"fsub", {0, 0, 0, 0}}},
		{X86_INS_FISUB, {"fisub", {0, 0, 0, 0}}},
		{X86_INS_FSUBP, {"fsubp", {0, 0, 0, 0}}},
		{X86_INS_SWAPGS, {"swapgs", {0, 0, 0, 0}}},
		{X86_INS_SYSCALL, {"syscall", {0, 0, 0, 0}}},
		{X86_INS_SYSENTER, {"sysenter", {0, 0, 0, 0}}},
		{X86_INS_SYSEXIT, {"sysexit", {0, 0, 0, 0}}},
		{X86_INS_SYSRET, {"sysret", {0, 0, 0, 0}}},
		{X86_INS_T1MSKC, {"t1mskc", {0, 0, 0, 0}}},
		{X86_INS_UD2, {"ud2", {0, 0, 0, 0}}},
		{X86_INS_FTST, {"ftst", {0, 0, 0, 0}}},
		{X86_INS_TZCNT, {"tzcnt", {0, 0, 0, 0}}},
		{X86_INS_TZMSK, {"tzmsk", {0, 0, 0, 0}}},
		{X86_INS_FUCOMPI, {"fucompi", {0, 0, 0, 0}}},
		{X86_INS_FUCOMI, {"fucomi", {0, 0, 0, 0}}},
		{X86_INS_FUCOMPP, {"fucompp", {0, 0, 0, 0}}},
		{X86_INS_FUCOMP, {"fucomp", {0, 0, 0, 0}}},
		{X86_INS_FUCOM, {"fucom", {0, 0, 0, 0}}},
		{X86_INS_UD2B, {"ud2b", {0, 0, 0, 0}}},
		{X86_INS_UNPCKHPD, {"unpckhpd", {0, 0, 0, 0}}},
		{X86_INS_UNPCKHPS, {"unpckhps", {0, 0, 0, 0}}},
		{X86_INS_UNPCKLPD, {"unpcklpd", {0, 0, 0, 0}}},
		{X86_INS_UNPCKLPS, {"unpcklps", {0, 0, 0, 0}}},
		{X86_INS_VADDPD, {"vaddpd", {0, 0, 0, 0}}},
		{X86_INS_VADDPS, {"vaddps", {0, 0, 0, 0}}},
		{X86_INS_VADDSD, {"vaddsd", {0, 0, 0, 0}}},
		{X86_INS_VADDSS, {"vaddss", {0, 0, 0, 0}}},
		{X86_INS_VADDSUBPD, {"vaddsubpd", {0, 0, 0, 0}}},
		{X86_INS_VADDSUBPS, {"vaddsubps", {0, 0, 0, 0}}},
		{X86_INS_VAESDECLAST, {"vaesdeclast", {0, 0, 0, 0}}},
		{X86_INS_VAESDEC, {"vaesdec", {0, 0, 0, 0}}},
		{X86_INS_VAESENCLAST, {"vaesenclast", {0, 0, 0, 0}}},
		{X86_INS_VAESENC, {"vaesenc", {0, 0, 0, 0}}},
		{X86_INS_VAESIMC, {"vaesimc", {0, 0, 0, 0}}},
		{X86_INS_VAESKEYGENASSIST, {"vaeskeygenassist", {0, 0, 0, 0}}},
		{X86_INS_VALIGND, {"valignd", {0, 0, 0, 0}}},
		{X86_INS_VALIGNQ, {"valignq", {0, 0, 0, 0}}},
		{X86_INS_VANDNPD, {"vandnpd", {0, 0, 0, 0}}},
		{X86_INS_VANDNPS, {"vandnps", {0, 0, 0, 0}}},
		{X86_INS_VANDPD, {"vandpd", {0, 0, 0, 0}}},
		{X86_INS_VANDPS, {"vandps", {0, 0, 0, 0}}},
		{X86_INS_VBLENDMPD, {"vblendmpd", {0, 0, 0, 0}}},
		{X86_INS_VBLENDMPS, {"vblendmps", {0, 0, 0, 0}}},
		{X86_INS_VBLENDPD, {"vblendpd", {0, 0, 0, 0}}},
		{X86_INS_VBLENDPS, {"vblendps", {0, 0, 0, 0}}},
		{X86_INS_VBLENDVPD, {"vblendvpd", {0, 0, 0, 0}}},
		{X86_INS_VBLENDVPS, {"vblendvps", {0, 0, 0, 0}}},
		{X86_INS_VBROADCASTF128, {"vbroadcastf128", {0, 0, 0, 0}}},
		{X86_INS_VBROADCASTI128, {"vbroadcasti128", {0, 0, 0, 0}}},
		{X86_INS_VBROADCASTI32X4, {"vbroadcasti32x4", {0, 0, 0, 0}}},
		{X86_INS_VBROADCASTI64X4, {"vbroadcasti64x4", {0, 0, 0, 0}}},
		{X86_INS_VBROADCASTSD, {"vbroadcastsd", {0, 0, 0, 0}}},
		{X86_INS_VBROADCASTSS, {"vbroadcastss", {0, 0, 0, 0}}},
		{X86_INS_VCMPPD, {"vcmppd", {0, 0, 0, 0}}},
		{X86_INS_VCMPPS, {"vcmpps", {0, 0, 0, 0}}},
		{X86_INS_VCMPSD, {"vcmpsd", {0, 0, 0, 0}}},
		{X86_INS_VCMPSS, {"vcmpss", {0, 0, 0, 0}}},
		{X86_INS_VCVTDQ2PD, {"vcvtdq2pd", {0, 0, 0, 0}}},
		{X86_INS_VCVTDQ2PS, {"vcvtdq2ps", {0, 0, 0, 0}}},
		{X86_INS_VCVTPD2DQX, {"vcvtpd2dqx", {0, 0, 0, 0}}},
		{X86_INS_VCVTPD2DQ, {"vcvtpd2dq", {0, 0, 0, 0}}},
		{X86_INS_VCVTPD2PSX, {"vcvtpd2psx", {0, 0, 0, 0}}},
		{X86_INS_VCVTPD2PS, {"vcvtpd2ps", {0, 0, 0, 0}}},
		{X86_INS_VCVTPD2UDQ, {"vcvtpd2udq", {0, 0, 0, 0}}},
		{X86_INS_VCVTPH2PS, {"vcvtph2ps", {0, 0, 0, 0}}},
		{X86_INS_VCVTPS2DQ, {"vcvtps2dq", {0, 0, 0, 0}}},
		{X86_INS_VCVTPS2PD, {"vcvtps2pd", {0, 0, 0, 0}}},
		{X86_INS_VCVTPS2PH, {"vcvtps2ph", {0, 0, 0, 0}}},
		{X86_INS_VCVTPS2UDQ, {"vcvtps2udq", {0, 0, 0, 0}}},
		{X86_INS_VCVTSD2SI, {"vcvtsd2si", {0, 0, 0, 0}}},
		{X86_INS_VCVTSD2USI, {"vcvtsd2usi", {0, 0, 0, 0}}},
		{X86_INS_VCVTSS2SI, {"vcvtss2si", {0, 0, 0, 0}}},
		{X86_INS_VCVTSS2USI, {"vcvtss2usi", {0, 0, 0, 0}}},
		{X86_INS_VCVTTPD2DQX, {"vcvttpd2dqx", {0, 0, 0, 0}}},
		{X86_INS_VCVTTPD2DQ, {"vcvttpd2dq", {0, 0, 0, 0}}},
		{X86_INS_VCVTTPD2UDQ, {"vcvttpd2udq", {0, 0, 0, 0}}},
		{X86_INS_VCVTTPS2DQ, {"vcvttps2dq", {0, 0, 0, 0}}},
		{X86_INS_VCVTTPS2UDQ, {"vcvttps2udq", {0, 0, 0, 0}}},
		{X86_INS_VCVTUDQ2PD, {"vcvtudq2pd", {0, 0, 0, 0}}},
		{X86_INS_VCVTUDQ2PS, {"vcvtudq2ps", {0, 0, 0, 0}}},
		{X86_INS_VDIVPD, {"vdivpd", {0, 0, 0, 0}}},
		{X86_INS_VDIVPS, {"vdivps", {0, 0, 0, 0}}},
		{X86_INS_VDIVSD, {"vdivsd", {0, 0, 0, 0}}},
		{X86_INS_VDIVSS, {"vdivss", {0, 0, 0, 0}}},
		{X86_INS_VDPPD, {"vdppd", {0, 0, 0, 0}}},
		{X86_INS_VDPPS, {"vdpps", {0, 0, 0, 0}}},
		{X86_INS_VERR, {"verr", {0, 0, 0, 0}}},
		{X86_INS_VERW, {"verw", {0, 0, 0, 0}}},
		{X86_INS_VEXTRACTF128, {"vextractf128", {0, 0, 0, 0}}},
		{X86_INS_VEXTRACTF32X4, {"vextractf32x4", {0, 0, 0, 0}}},
		{X86_INS_VEXTRACTF64X4, {"vextractf64x4", {0, 0, 0, 0}}},
		{X86_INS_VEXTRACTI128, {"vextracti128", {0, 0, 0, 0}}},
		{X86_INS_VEXTRACTI32X4, {"vextracti32x4", {0, 0, 0, 0}}},
		{X86_INS_VEXTRACTI64X4, {"vextracti64x4", {0, 0, 0, 0}}},
		{X86_INS_VEXTRACTPS, {"vextractps", {0, 0, 0, 0}}},
		{X86_INS_VFMADD132PD, {"vfmadd132pd", {0, 0, 0, 0}}},
		{X86_INS_VFMADD132PS, {"vfmadd132ps", {0, 0, 0, 0}}},
		{X86_INS_VFMADD213PD, {"vfmadd213pd", {0, 0, 0, 0}}},
		{X86_INS_VFMADD213PS, {"vfmadd213ps", {0, 0, 0, 0}}},
		{X86_INS_VFMADDPD, {"vfmaddpd", {0, 0, 0, 0}}},
		{X86_INS_VFMADD231PD, {"vfmadd231pd", {0, 0, 0, 0}}},
		{X86_INS_VFMADDPS, {"vfmaddps", {0, 0, 0, 0}}},
		{X86_INS_VFMADD231PS, {"vfmadd231ps", {0, 0, 0, 0}}},
		{X86_INS_VFMADDSD, {"vfmaddsd", {0, 0, 0, 0}}},
		{X86_INS_VFMADD213SD, {"vfmadd213sd", {0, 0, 0, 0}}},
		{X86_INS_VFMADD132SD, {"vfmadd132sd", {0, 0, 0, 0}}},
		{X86_INS_VFMADD231SD, {"vfmadd231sd", {0, 0, 0, 0}}},
		{X86_INS_VFMADDSS, {"vfmaddss", {0, 0, 0, 0}}},
		{X86_INS_VFMADD213SS, {"vfmadd213ss", {0, 0, 0, 0}}},
		{X86_INS_VFMADD132SS, {"vfmadd132ss", {0, 0, 0, 0}}},
		{X86_INS_VFMADD231SS, {"vfmadd231ss", {0, 0, 0, 0}}},
		{X86_INS_VFMADDSUB132PD, {"vfmaddsub132pd", {0, 0, 0, 0}}},
		{X86_INS_VFMADDSUB132PS, {"vfmaddsub132ps", {0, 0, 0, 0}}},
		{X86_INS_VFMADDSUB213PD, {"vfmaddsub213pd", {0, 0, 0, 0}}},
		{X86_INS_VFMADDSUB213PS, {"vfmaddsub213ps", {0, 0, 0, 0}}},
		{X86_INS_VFMADDSUBPD, {"vfmaddsubpd", {0, 0, 0, 0}}},
		{X86_INS_VFMADDSUB231PD, {"vfmaddsub231pd", {0, 0, 0, 0}}},
		{X86_INS_VFMADDSUBPS, {"vfmaddsubps", {0, 0, 0, 0}}},
		{X86_INS_VFMADDSUB231PS, {"vfmaddsub231ps", {0, 0, 0, 0}}},
		{X86_INS_VFMSUB132PD, {"vfmsub132pd", {0, 0, 0, 0}}},
		{X86_INS_VFMSUB132PS, {"vfmsub132ps", {0, 0, 0, 0}}},
		{X86_INS_VFMSUB213PD, {"vfmsub213pd", {0, 0, 0, 0}}},
		{X86_INS_VFMSUB213PS, {"vfmsub213ps", {0, 0, 0, 0}}},
		{X86_INS_VFMSUBADD132PD, {"vfmsubadd132pd", {0, 0, 0, 0}}},
		{X86_INS_VFMSUBADD132PS, {"vfmsubadd132ps", {0, 0, 0, 0}}},
		{X86_INS_VFMSUBADD213PD, {"vfmsubadd213pd", {0, 0, 0, 0}}},
		{X86_INS_VFMSUBADD213PS, {"vfmsubadd213ps", {0, 0, 0, 0}}},
		{X86_INS_VFMSUBADDPD, {"vfmsubaddpd", {0, 0, 0, 0}}},
		{X86_INS_VFMSUBADD231PD, {"vfmsubadd231pd", {0, 0, 0, 0}}},
		{X86_INS_VFMSUBADDPS, {"vfmsubaddps", {0, 0, 0, 0}}},
		{X86_INS_VFMSUBADD231PS, {"vfmsubadd231ps", {0, 0, 0, 0}}},
		{X86_INS_VFMSUBPD, {"vfmsubpd", {0, 0, 0, 0}}},
		{X86_INS_VFMSUB231PD, {"vfmsub231pd", {0, 0, 0, 0}}},
		{X86_INS_VFMSUBPS, {"vfmsubps", {0, 0, 0, 0}}},
		{X86_INS_VFMSUB231PS, {"vfmsub231ps", {0, 0, 0, 0}}},
		{X86_INS_VFMSUBSD, {"vfmsubsd", {0, 0, 0, 0}}},
		{X86_INS_VFMSUB213SD, {"vfmsub213sd", {0, 0, 0, 0}}},
		{X86_INS_VFMSUB132SD, {"vfmsub132sd", {0, 0, 0, 0}}},
		{X86_INS_VFMSUB231SD, {"vfmsub231sd", {0, 0, 0, 0}}},
		{X86_INS_VFMSUBSS, {"vfmsubss", {0, 0, 0, 0}}},
		{X86_INS_VFMSUB213SS, {"vfmsub213ss", {0, 0, 0, 0}}},
		{X86_INS_VFMSUB132SS, {"vfmsub132ss", {0, 0, 0, 0}}},
		{X86_INS_VFMSUB231SS, {"vfmsub231ss", {0, 0, 0, 0}}},
		{X86_INS_VFNMADD132PD, {"vfnmadd132pd", {0, 0, 0, 0}}},
		{X86_INS_VFNMADD132PS, {"vfnmadd132ps", {0, 0, 0, 0}}},
		{X86_INS_VFNMADD213PD, {"vfnmadd213pd", {0, 0, 0, 0}}},
		{X86_INS_VFNMADD213PS, {"vfnmadd213ps", {0, 0, 0, 0}}},
		{X86_INS_VFNMADDPD, {"vfnmaddpd", {0, 0, 0, 0}}},
		{X86_INS_VFNMADD231PD, {"vfnmadd231pd", {0, 0, 0, 0}}},
		{X86_INS_VFNMADDPS, {"vfnmaddps", {0, 0, 0, 0}}},
		{X86_INS_VFNMADD231PS, {"vfnmadd231ps", {0, 0, 0, 0}}},
		{X86_INS_VFNMADDSD, {"vfnmaddsd", {0, 0, 0, 0}}},
		{X86_INS_VFNMADD213SD, {"vfnmadd213sd", {0, 0, 0, 0}}},
		{X86_INS_VFNMADD132SD, {"vfnmadd132sd", {0, 0, 0, 0}}},
		{X86_INS_VFNMADD231SD, {"vfnmadd231sd", {0, 0, 0, 0}}},
		{X86_INS_VFNMADDSS, {"vfnmaddss", {0, 0, 0, 0}}},
		{X86_INS_VFNMADD213SS, {"vfnmadd213ss", {0, 0, 0, 0}}},
		{X86_INS_VFNMADD132SS, {"vfnmadd132ss", {0, 0, 0, 0}}},
		{X86_INS_VFNMADD231SS, {"vfnmadd231ss", {0, 0, 0, 0}}},
		{X86_INS_VFNMSUB132PD, {"vfnmsub132pd", {0, 0, 0, 0}}},
		{X86_INS_VFNMSUB132PS, {"vfnmsub132ps", {0, 0, 0, 0}}},
		{X86_INS_VFNMSUB213PD, {"vfnmsub213pd", {0, 0, 0, 0}}},
		{X86_INS_VFNMSUB213PS, {"vfnmsub213ps", {0, 0, 0, 0}}},
		{X86_INS_VFNMSUBPD, {"vfnmsubpd", {0, 0, 0, 0}}},
		{X86_INS_VFNMSUB231PD, {"vfnmsub231pd", {0, 0, 0, 0}}},
		{X86_INS_VFNMSUBPS, {"vfnmsubps", {0, 0, 0, 0}}},
		{X86_INS_VFNMSUB231PS, {"vfnmsub231ps", {0, 0, 0, 0}}},
		{X86_INS_VFNMSUBSD, {"vfnmsubsd", {0, 0, 0, 0}}},
		{X86_INS_VFNMSUB213SD, {"vfnmsub213sd", {0, 0, 0, 0}}},
		{X86_INS_VFNMSUB132SD, {"vfnmsub132sd", {0, 0, 0, 0}}},
		{X86_INS_VFNMSUB231SD, {"vfnmsub231sd", {0, 0, 0, 0}}},
		{X86_INS_VFNMSUBSS, {"vfnmsubss", {0, 0, 0, 0}}},
		{X86_INS_VFNMSUB213SS, {"vfnmsub213ss", {0, 0, 0, 0}}},
		{X86_INS_VFNMSUB132SS, {"vfnmsub132ss", {0, 0, 0, 0}}},
		{X86_INS_VFNMSUB231SS, {"vfnmsub231ss", {0, 0, 0, 0}}},
		{X86_INS_VFRCZPD, {"vfrczpd", {0, 0, 0, 0}}},
		{X86_INS_VFRCZPS, {"vfrczps", {0, 0, 0, 0}}},
		{X86_INS_VFRCZSD, {"vfrczsd", {0, 0, 0, 0}}},
		{X86_INS_VFRCZSS, {"vfrczss", {0, 0, 0, 0}}},
		{X86_INS_VORPD, {"vorpd", {0, 0, 0, 0}}},
		{X86_INS_VORPS, {"vorps", {0, 0, 0, 0}}},
		{X86_INS_VXORPD, {"vxorpd", {0, 0, 0, 0}}},
		{X86_INS_VXORPS, {"vxorps", {0, 0, 0, 0}}},
		{X86_INS_VGATHERDPD, {"vgatherdpd", {0, 0, 0, 0}}},
		{X86_INS_VGATHERDPS, {"vgatherdps", {0, 0, 0, 0}}},
		{X86_INS_VGATHERPF0DPD, {"vgatherpf0dpd", {0, 0, 0, 0}}},
		{X86_INS_VGATHERPF0DPS, {"vgatherpf0dps", {0, 0, 0, 0}}},
		{X86_INS_VGATHERPF0QPD, {"vgatherpf0qpd", {0, 0, 0, 0}}},
		{X86_INS_VGATHERPF0QPS, {"vgatherpf0qps", {0, 0, 0, 0}}},
		{X86_INS_VGATHERPF1DPD, {"vgatherpf1dpd", {0, 0, 0, 0}}},
		{X86_INS_VGATHERPF1DPS, {"vgatherpf1dps", {0, 0, 0, 0}}},
		{X86_INS_VGATHERPF1QPD, {"vgatherpf1qpd", {0, 0, 0, 0}}},
		{X86_INS_VGATHERPF1QPS, {"vgatherpf1qps", {0, 0, 0, 0}}},
		{X86_INS_VGATHERQPD, {"vgatherqpd", {0, 0, 0, 0}}},
		{X86_INS_VGATHERQPS, {"vgatherqps", {0, 0, 0, 0}}},
		{X86_INS_VHADDPD, {"vhaddpd", {0, 0, 0, 0}}},
		{X86_INS_VHADDPS, {"vhaddps", {0, 0, 0, 0}}},
		{X86_INS_VHSUBPD, {"vhsubpd", {0, 0, 0, 0}}},
		{X86_INS_VHSUBPS, {"vhsubps", {0, 0, 0, 0}}},
		{X86_INS_VINSERTF128, {"vinsertf128", {0, 0, 0, 0}}},
		{X86_INS_VINSERTF32X4, {"vinsertf32x4", {0, 0, 0, 0}}},
		{X86_INS_VINSERTF64X4, {"vinsertf64x4", {0, 0, 0, 0}}},
		{X86_INS_VINSERTI128, {"vinserti128", {0, 0, 0, 0}}},
		{X86_INS_VINSERTI32X4, {"vinserti32x4", {0, 0, 0, 0}}},
		{X86_INS_VINSERTI64X4, {"vinserti64x4", {0, 0, 0, 0}}},
		{X86_INS_VINSERTPS, {"vinsertps", {0, 0, 0, 0}}},
		{X86_INS_VLDDQU, {"vlddqu", {0, 0, 0, 0}}},
		{X86_INS_VLDMXCSR, {"vldmxcsr", {0, 0, 0, 0}}},
		{X86_INS_VMASKMOVDQU, {"vmaskmovdqu", {0, 0, 0, 0}}},
		{X86_INS_VMASKMOVPD, {"vmaskmovpd", {0, 0, 0, 0}}},
		{X86_INS_VMASKMOVPS, {"vmaskmovps", {0, 0, 0, 0}}},
		{X86_INS_VMAXPD, {"vmaxpd", {0, 0, 0, 0}}},
		{X86_INS_VMAXPS, {"vmaxps", {0, 0, 0, 0}}},
		{X86_INS_VMAXSD, {"vmaxsd", {0, 0, 0, 0}}},
		{X86_INS_VMAXSS, {"vmaxss", {0, 0, 0, 0}}},
		{X86_INS_VMCALL, {"vmcall", {0, 0, 0, 0}}},
		{X86_INS_VMCLEAR, {"vmclear", {0, 0, 0, 0}}},
		{X86_INS_VMFUNC, {"vmfunc", {0, 0, 0, 0}}},
		{X86_INS_VMINPD, {"vminpd", {0, 0, 0, 0}}},
		{X86_INS_VMINPS, {"vminps", {0, 0, 0, 0}}},
		{X86_INS_VMINSD, {"vminsd", {0, 0, 0, 0}}},
		{X86_INS_VMINSS, {"vminss", {0, 0, 0, 0}}},
		{X86_INS_VMLAUNCH, {"vmlaunch", {0, 0, 0, 0}}},
		{X86_INS_VMLOAD, {"vmload", {0, 0, 0, 0}}},
		{X86_INS_VMMCALL, {"vmmcall", {0, 0, 0, 0}}},
		{X86_INS_VMOVQ, {"vmovq", {0, 0, 0, 0}}},
		{X86_INS_VMOVDDUP, {"vmovddup", {0, 0, 0, 0}}},
		{X86_INS_VMOVD, {"vmovd", {0, 0, 0, 0}}},
		{X86_INS_VMOVDQA32, {"vmovdqa32", {0, 0, 0, 0}}},
		{X86_INS_VMOVDQA64, {"vmovdqa64", {0, 0, 0, 0}}},
		{X86_INS_VMOVDQA, {"vmovdqa", {0, 0, 0, 0}}},
		{X86_INS_VMOVDQU16, {"vmovdqu16", {0, 0, 0, 0}}},
		{X86_INS_VMOVDQU32, {"vmovdqu32", {0, 0, 0, 0}}},
		{X86_INS_VMOVDQU64, {"vmovdqu64", {0, 0, 0, 0}}},
		{X86_INS_VMOVDQU8, {"vmovdqu8", {0, 0, 0, 0}}},
		{X86_INS_VMOVDQU, {"vmovdqu", {0, 0, 0, 0}}},
		{X86_INS_VMOVHLPS, {"vmovhlps", {0, 0, 0, 0}}},
		{X86_INS_VMOVHPD, {"vmovhpd", {0, 0, 0, 0}}},
		{X86_INS_VMOVHPS, {"vmovhps", {0, 0, 0, 0}}},
		{X86_INS_VMOVLHPS, {"vmovlhps", {0, 0, 0, 0}}},
		{X86_INS_VMOVLPD, {"vmovlpd", {0, 0, 0, 0}}},
		{X86_INS_VMOVLPS, {"vmovlps", {0, 0, 0, 0}}},
		{X86_INS_VMOVMSKPD, {"vmovmskpd", {0, 0, 0, 0}}},
		{X86_INS_VMOVMSKPS, {"vmovmskps", {0, 0, 0, 0}}},
		{X86_INS_VMOVNTDQA, {"vmovntdqa", {0, 0, 0, 0}}},
		{X86_INS_VMOVNTDQ, {"vmovntdq", {0, 0, 0, 0}}},
		{X86_INS_VMOVNTPD, {"vmovntpd", {0, 0, 0, 0}}},
		{X86_INS_VMOVNTPS, {"vmovntps", {0, 0, 0, 0}}},
		{X86_INS_VMOVSD, {"vmovsd", {0, 0, 0, 0}}},
		{X86_INS_VMOVSHDUP, {"vmovshdup", {0, 0, 0, 0}}},
		{X86_INS_VMOVSLDUP, {"vmovsldup", {0, 0, 0, 0}}},
		{X86_INS_VMOVSS, {"vmovss", {0, 0, 0, 0}}},
		{X86_INS_VMOVUPD, {"vmovupd", {0, 0, 0, 0}}},
		{X86_INS_VMOVUPS, {"vmovups", {0, 0, 0, 0}}},
		{X86_INS_VMPSADBW, {"vmpsadbw", {0, 0, 0, 0}}},
		{X86_INS_VMPTRLD, {"vmptrld", {0, 0, 0, 0}}},
		{X86_INS_VMPTRST, {"vmptrst", {0, 0, 0, 0}}},
		{X86_INS_VMREAD, {"vmread", {0, 0, 0, 0}}},
		{X86_INS_VMRESUME, {"vmresume", {0, 0, 0, 0}}},
		{X86_INS_VMRUN, {"vmrun", {0, 0, 0, 0}}},
		{X86_INS_VMSAVE, {"vmsave", {0, 0, 0, 0}}},
		{X86_INS_VMULPD, {"vmulpd", {0, 0, 0, 0}}},
		{X86_INS_VMULPS, {"vmulps", {0, 0, 0, 0}}},
		{X86_INS_VMULSD, {"vmulsd", {0, 0, 0, 0}}},
		{X86_INS_VMULSS, {"vmulss", {0, 0, 0, 0}}},
		{X86_INS_VMWRITE, {"vmwrite", {0, 0, 0, 0}}},
		{X86_INS_VMXOFF, {"vmxoff", {0, 0, 0, 0}}},
		{X86_INS_VMXON, {"vmxon", {0, 0, 0, 0}}},
		{X86_INS_VPABSB, {"vpabsb", {0, 0, 0, 0}}},
		{X86_INS_VPABSD, {"vpabsd", {0, 0, 0, 0}}},
		{X86_INS_VPABSQ, {"vpabsq", {0, 0, 0, 0}}},
		{X86_INS_VPABSW, {"vpabsw", {0, 0, 0, 0}}},
		{X86_INS_VPACKSSDW, {"vpackssdw", {0, 0, 0, 0}}},
		{X86_INS_VPACKSSWB, {"vpacksswb", {0, 0, 0, 0}}},
		{X86_INS_VPACKUSDW, {"vpackusdw", {0, 0, 0, 0}}},
		{X86_INS_VPACKUSWB, {"vpackuswb", {0, 0, 0, 0}}},
		{X86_INS_VPADDB, {"vpaddb", {0, 0, 0, 0}}},
		{X86_INS_VPADDD, {"vpaddd", {0, 0, 0, 0}}},
		{X86_INS_VPADDQ, {"vpaddq", {0, 0, 0, 0}}},
		{X86_INS_VPADDSB, {"vpaddsb", {0, 0, 0, 0}}},
		{X86_INS_VPADDSW, {"vpaddsw", {0, 0, 0, 0}}},
		{X86_INS_VPADDUSB, {"vpaddusb", {0, 0, 0, 0}}},
		{X86_INS_VPADDUSW, {"vpaddusw", {0, 0, 0, 0}}},
		{X86_INS_VPADDW, {"vpaddw", {0, 0, 0, 0}}},
		{X86_INS_VPALIGNR, {"vpalignr", {0, 0, 0, 0}}},
		{X86_INS_VPANDD, {"vpandd", {0, 0, 0, 0}}},
		{X86_INS_VPANDND, {"vpandnd", {0, 0, 0, 0}}},
		{X86_INS_VPANDNQ, {"vpandnq", {0, 0, 0, 0}}},
		{X86_INS_VPANDN, {"vpandn", {0, 0, 0, 0}}},
		{X86_INS_VPANDQ, {"vpandq", {0, 0, 0, 0}}},
		{X86_INS_VPAND, {"vpand", {0, 0, 0, 0}}},
		{X86_INS_VPAVGB, {"vpavgb", {0, 0, 0, 0}}},
		{X86_INS_VPAVGW, {"vpavgw", {0, 0, 0, 0}}},
		{X86_INS_VPBLENDD, {"vpblendd", {0, 0, 0, 0}}},
		{X86_INS_VPBLENDMD, {"vpblendmd", {0, 0, 0, 0}}},
		{X86_INS_VPBLENDMQ, {"vpblendmq", {0, 0, 0, 0}}},
		{X86_INS_VPBLENDVB, {"vpblendvb", {0, 0, 0, 0}}},
		{X86_INS_VPBLENDW, {"vpblendw", {0, 0, 0, 0}}},
		{X86_INS_VPBROADCASTB, {"vpbroadcastb", {0, 0, 0, 0}}},
		{X86_INS_VPBROADCASTD, {"vpbroadcastd", {0, 0, 0, 0}}},
		{X86_INS_VPBROADCASTMB2Q, {"vpbroadcastmb2q", {0, 0, 0, 0}}},
		{X86_INS_VPBROADCASTMW2D, {"vpbroadcastmw2d", {0, 0, 0, 0}}},
		{X86_INS_VPBROADCASTQ, {"vpbroadcastq", {0, 0, 0, 0}}},
		{X86_INS_VPBROADCASTW, {"vpbroadcastw", {0, 0, 0, 0}}},
		{X86_INS_VPCLMULQDQ, {"vpclmulqdq", {0, 0, 0, 0}}},
		{X86_INS_VPCMOV, {"vpcmov", {0, 0, 0, 0}}},
		{X86_INS_VPCMP, {"vpcmp", {0, 0, 0, 0}}},
		{X86_INS_VPCMPD, {"vpcmpd", {0, 0, 0, 0}}},
		{X86_INS_VPCMPEQB, {"vpcmpeqb", {0, 0, 0, 0}}},
		{X86_INS_VPCMPEQD, {"vpcmpeqd", {0, 0, 0, 0}}},
		{X86_INS_VPCMPEQQ, {"vpcmpeqq", {0, 0, 0, 0}}},
		{X86_INS_VPCMPEQW, {"vpcmpeqw", {0, 0, 0, 0}}},
		{X86_INS_VPCMPESTRI, {"vpcmpestri", {0, 0, 0, 0}}},
		{X86_INS_VPCMPESTRM, {"vpcmpestrm", {0, 0, 0, 0}}},
		{X86_INS_VPCMPGTB, {"vpcmpgtb", {0, 0, 0, 0}}},
		{X86_INS_VPCMPGTD, {"vpcmpgtd", {0, 0, 0, 0}}},
		{X86_INS_VPCMPGTQ, {"vpcmpgtq", {0, 0, 0, 0}}},
		{X86_INS_VPCMPGTW, {"vpcmpgtw", {0, 0, 0, 0}}},
		{X86_INS_VPCMPISTRI, {"vpcmpistri", {0, 0, 0, 0}}},
		{X86_INS_VPCMPISTRM, {"vpcmpistrm", {0, 0, 0, 0}}},
		{X86_INS_VPCMPQ, {"vpcmpq", {0, 0, 0, 0}}},
		{X86_INS_VPCMPUD, {"vpcmpud", {0, 0, 0, 0}}},
		{X86_INS_VPCMPUQ, {"vpcmpuq", {0, 0, 0, 0}}},
		{X86_INS_VPCOMB, {"vpcomb", {0, 0, 0, 0}}},
		{X86_INS_VPCOMD, {"vpcomd", {0, 0, 0, 0}}},
		{X86_INS_VPCOMQ, {"vpcomq", {0, 0, 0, 0}}},
		{X86_INS_VPCOMUB, {"vpcomub", {0, 0, 0, 0}}},
		{X86_INS_VPCOMUD, {"vpcomud", {0, 0, 0, 0}}},
		{X86_INS_VPCOMUQ, {"vpcomuq", {0, 0, 0, 0}}},
		{X86_INS_VPCOMUW, {"vpcomuw", {0, 0, 0, 0}}},
		{X86_INS_VPCOMW, {"vpcomw", {0, 0, 0, 0}}},
		{X86_INS_VPCONFLICTD, {"vpconflictd", {0, 0, 0, 0}}},
		{X86_INS_VPCONFLICTQ, {"vpconflictq", {0, 0, 0, 0}}},
		{X86_INS_VPERM2F128, {"vperm2f128", {0, 0, 0, 0}}},
		{X86_INS_VPERM2I128, {"vperm2i128", {0, 0, 0, 0}}},
		{X86_INS_VPERMD, {"vpermd", {0, 0, 0, 0}}},
		{X86_INS_VPERMI2D, {"vpermi2d", {0, 0, 0, 0}}},
		{X86_INS_VPERMI2PD, {"vpermi2pd", {0, 0, 0, 0}}},
		{X86_INS_VPERMI2PS, {"vpermi2ps", {0, 0, 0, 0}}},
		{X86_INS_VPERMI2Q, {"vpermi2q", {0, 0, 0, 0}}},
		{X86_INS_VPERMIL2PD, {"vpermil2pd", {0, 0, 0, 0}}},
		{X86_INS_VPERMIL2PS, {"vpermil2ps", {0, 0, 0, 0}}},
		{X86_INS_VPERMILPD, {"vpermilpd", {0, 0, 0, 0}}},
		{X86_INS_VPERMILPS, {"vpermilps", {0, 0, 0, 0}}},
		{X86_INS_VPERMPD, {"vpermpd", {0, 0, 0, 0}}},
		{X86_INS_VPERMPS, {"vpermps", {0, 0, 0, 0}}},
		{X86_INS_VPERMQ, {"vpermq", {0, 0, 0, 0}}},
		{X86_INS_VPERMT2D, {"vpermt2d", {0, 0, 0, 0}}},
		{X86_INS_VPERMT2PD, {"vpermt2pd", {0, 0, 0, 0}}},
		{X86_INS_VPERMT2PS, {"vpermt2ps", {0, 0, 0, 0}}},
		{X86_INS_VPERMT2Q, {"vpermt2q", {0, 0, 0, 0}}},
		{X86_INS_VPEXTRB, {"vpextrb", {0, 0, 0, 0}}},
		{X86_INS_VPEXTRD, {"vpextrd", {0, 0, 0, 0}}},
		{X86_INS_VPEXTRQ, {"vpextrq", {0, 0, 0, 0}}},
		{X86_INS_VPEXTRW, {"vpextrw", {0, 0, 0, 0}}},
		{X86_INS_VPGATHERDD, {"vpgatherdd", {0, 0, 0, 0}}},
		{X86_INS_VPGATHERDQ, {"vpgatherdq", {0, 0, 0, 0}}},
		{X86_INS_VPGATHERQD, {"vpgatherqd", {0, 0, 0, 0}}},
		{X86_INS_VPGATHERQQ, {"vpgatherqq", {0, 0, 0, 0}}},
		{X86_INS_VPHADDBD, {"vphaddbd", {0, 0, 0, 0}}},
		{X86_INS_VPHADDBQ, {"vphaddbq", {0, 0, 0, 0}}},
		{X86_INS_VPHADDBW, {"vphaddbw", {0, 0, 0, 0}}},
		{X86_INS_VPHADDDQ, {"vphadddq", {0, 0, 0, 0}}},
		{X86_INS_VPHADDD, {"vphaddd", {0, 0, 0, 0}}},
		{X86_INS_VPHADDSW, {"vphaddsw", {0, 0, 0, 0}}},
		{X86_INS_VPHADDUBD, {"vphaddubd", {0, 0, 0, 0}}},
		{X86_INS_VPHADDUBQ, {"vphaddubq", {0, 0, 0, 0}}},
		{X86_INS_VPHADDUBW, {"vphaddubw", {0, 0, 0, 0}}},
		{X86_INS_VPHADDUDQ, {"vphaddudq", {0, 0, 0, 0}}},
		{X86_INS_VPHADDUWD, {"vphadduwd", {0, 0, 0, 0}}},
		{X86_INS_VPHADDUWQ, {"vphadduwq", {0, 0, 0, 0}}},
		{X86_INS_VPHADDWD, {"vphaddwd", {0, 0, 0, 0}}},
		{X86_INS_VPHADDWQ, {"vphaddwq", {0, 0, 0, 0}}},
		{X86_INS_VPHADDW, {"vphaddw", {0, 0, 0, 0}}},
		{X86_INS_VPHMINPOSUW, {"vphminposuw", {0, 0, 0, 0}}},
		{X86_INS_VPHSUBBW, {"vphsubbw", {0, 0, 0, 0}}},
		{X86_INS_VPHSUBDQ, {"vphsubdq", {0, 0, 0, 0}}},
		{X86_INS_VPHSUBD, {"vphsubd", {0, 0, 0, 0}}},
		{X86_INS_VPHSUBSW, {"vphsubsw", {0, 0, 0, 0}}},
		{X86_INS_VPHSUBWD, {"vphsubwd", {0, 0, 0, 0}}},
		{X86_INS_VPHSUBW, {"vphsubw", {0, 0, 0, 0}}},
		{X86_INS_VPINSRB, {"vpinsrb", {0, 0, 0, 0}}},
		{X86_INS_VPINSRD, {"vpinsrd", {0, 0, 0, 0}}},
		{X86_INS_VPINSRQ, {"vpinsrq", {0, 0, 0, 0}}},
		{X86_INS_VPINSRW, {"vpinsrw", {0, 0, 0, 0}}},
		{X86_INS_VPLZCNTD, {"vplzcntd", {0, 0, 0, 0}}},
		{X86_INS_VPLZCNTQ, {"vplzcntq", {0, 0, 0, 0}}},
		{X86_INS_VPMACSDD, {"vpmacsdd", {0, 0, 0, 0}}},
		{X86_INS_VPMACSDQH, {"vpmacsdqh", {0, 0, 0, 0}}},
		{X86_INS_VPMACSDQL, {"vpmacsdql", {0, 0, 0, 0}}},
		{X86_INS_VPMACSSDD, {"vpmacssdd", {0, 0, 0, 0}}},
		{X86_INS_VPMACSSDQH, {"vpmacssdqh", {0, 0, 0, 0}}},
		{X86_INS_VPMACSSDQL, {"vpmacssdql", {0, 0, 0, 0}}},
		{X86_INS_VPMACSSWD, {"vpmacsswd", {0, 0, 0, 0}}},
		{X86_INS_VPMACSSWW, {"vpmacssww", {0, 0, 0, 0}}},
		{X86_INS_VPMACSWD, {"vpmacswd", {0, 0, 0, 0}}},
		{X86_INS_VPMACSWW, {"vpmacsww", {0, 0, 0, 0}}},
		{X86_INS_VPMADCSSWD, {"vpmadcsswd", {0, 0, 0, 0}}},
		{X86_INS_VPMADCSWD, {"vpmadcswd", {0, 0, 0, 0}}},
		{X86_INS_VPMADDUBSW, {"vpmaddubsw", {0, 0, 0, 0}}},
		{X86_INS_VPMADDWD, {"vpmaddwd", {0, 0, 0, 0}}},
		{X86_INS_VPMASKMOVD, {"vpmaskmovd", {0, 0, 0, 0}}},
		{X86_INS_VPMASKMOVQ, {"vpmaskmovq", {0, 0, 0, 0}}},
		{X86_INS_VPMAXSB, {"vpmaxsb", {0, 0, 0, 0}}},
		{X86_INS_VPMAXSD, {"vpmaxsd", {0, 0, 0, 0}}},
		{X86_INS_VPMAXSQ, {"vpmaxsq", {0, 0, 0, 0}}},
		{X86_INS_VPMAXSW, {"vpmaxsw", {0, 0, 0, 0}}},
		{X86_INS_VPMAXUB, {"vpmaxub", {0, 0, 0, 0}}},
		{X86_INS_VPMAXUD, {"vpmaxud", {0, 0, 0, 0}}},
		{X86_INS_VPMAXUQ, {"vpmaxuq", {0, 0, 0, 0}}},
		{X86_INS_VPMAXUW, {"vpmaxuw", {0, 0, 0, 0}}},
		{X86_INS_VPMINSB, {"vpminsb", {0, 0, 0, 0}}},
		{X86_INS_VPMINSD, {"vpminsd", {0, 0, 0, 0}}},
		{X86_INS_VPMINSQ, {"vpminsq", {0, 0, 0, 0}}},
		{X86_INS_VPMINSW, {"vpminsw", {0, 0, 0, 0}}},
		{X86_INS_VPMINUB, {"vpminub", {0, 0, 0, 0}}},
		{X86_INS_VPMINUD, {"vpminud", {0, 0, 0, 0}}},
		{X86_INS_VPMINUQ, {"vpminuq", {0, 0, 0, 0}}},
		{X86_INS_VPMINUW, {"vpminuw", {0, 0, 0, 0}}},
		{X86_INS_VPMOVDB, {"vpmovdb", {0, 0, 0, 0}}},
		{X86_INS_VPMOVDW, {"vpmovdw", {0, 0, 0, 0}}},
		{X86_INS_VPMOVMSKB, {"vpmovmskb", {0, 0, 0, 0}}},
		{X86_INS_VPMOVQB, {"vpmovqb", {0, 0, 0, 0}}},
		{X86_INS_VPMOVQD, {"vpmovqd", {0, 0, 0, 0}}},
		{X86_INS_VPMOVQW, {"vpmovqw", {0, 0, 0, 0}}},
		{X86_INS_VPMOVSDB, {"vpmovsdb", {0, 0, 0, 0}}},
		{X86_INS_VPMOVSDW, {"vpmovsdw", {0, 0, 0, 0}}},
		{X86_INS_VPMOVSQB, {"vpmovsqb", {0, 0, 0, 0}}},
		{X86_INS_VPMOVSQD, {"vpmovsqd", {0, 0, 0, 0}}},
		{X86_INS_VPMOVSQW, {"vpmovsqw", {0, 0, 0, 0}}},
		{X86_INS_VPMOVSXBD, {"vpmovsxbd", {0, 0, 0, 0}}},
		{X86_INS_VPMOVSXBQ, {"vpmovsxbq", {0, 0, 0, 0}}},
		{X86_INS_VPMOVSXBW, {"vpmovsxbw", {0, 0, 0, 0}}},
		{X86_INS_VPMOVSXDQ, {"vpmovsxdq", {0, 0, 0, 0}}},
		{X86_INS_VPMOVSXWD, {"vpmovsxwd", {0, 0, 0, 0}}},
		{X86_INS_VPMOVSXWQ, {"vpmovsxwq", {0, 0, 0, 0}}},
		{X86_INS_VPMOVUSDB, {"vpmovusdb", {0, 0, 0, 0}}},
		{X86_INS_VPMOVUSDW, {"vpmovusdw", {0, 0, 0, 0}}},
		{X86_INS_VPMOVUSQB, {"vpmovusqb", {0, 0, 0, 0}}},
		{X86_INS_VPMOVUSQD, {"vpmovusqd", {0, 0, 0, 0}}},
		{X86_INS_VPMOVUSQW, {"vpmovusqw", {0, 0, 0, 0}}},
		{X86_INS_VPMOVZXBD, {"vpmovzxbd", {0, 0, 0, 0}}},
		{X86_INS_VPMOVZXBQ, {"vpmovzxbq", {0, 0, 0, 0}}},
		{X86_INS_VPMOVZXBW, {"vpmovzxbw", {0, 0, 0, 0}}},
		{X86_INS_VPMOVZXDQ, {"vpmovzxdq", {0, 0, 0, 0}}},
		{X86_INS_VPMOVZXWD, {"vpmovzxwd", {0, 0, 0, 0}}},
		{X86_INS_VPMOVZXWQ, {"vpmovzxwq", {0, 0, 0, 0}}},
		{X86_INS_VPMULDQ, {"vpmuldq", {0, 0, 0, 0}}},
		{X86_INS_VPMULHRSW, {"vpmulhrsw", {0, 0, 0, 0}}},
		{X86_INS_VPMULHUW, {"vpmulhuw", {0, 0, 0, 0}}},
		{X86_INS_VPMULHW, {"vpmulhw", {0, 0, 0, 0}}},
		{X86_INS_VPMULLD, {"vpmulld", {0, 0, 0, 0}}},
		{X86_INS_VPMULLW, {"vpmullw", {0, 0, 0, 0}}},
		{X86_INS_VPMULUDQ, {"vpmuludq", {0, 0, 0, 0}}},
		{X86_INS_VPORD, {"vpord", {0, 0, 0, 0}}},
		{X86_INS_VPORQ, {"vporq", {0, 0, 0, 0}}},
		{X86_INS_VPOR, {"vpor", {0, 0, 0, 0}}},
		{X86_INS_VPPERM, {"vpperm", {0, 0, 0, 0}}},
		{X86_INS_VPROTB, {"vprotb", {0, 0, 0, 0}}},
		{X86_INS_VPROTD, {"vprotd", {0, 0, 0, 0}}},
		{X86_INS_VPROTQ, {"vprotq", {0, 0, 0, 0}}},
		{X86_INS_VPROTW, {"vprotw", {0, 0, 0, 0}}},
		{X86_INS_VPSADBW, {"vpsadbw", {0, 0, 0, 0}}},
		{X86_INS_VPSCATTERDD, {"vpscatterdd", {0, 0, 0, 0}}},
		{X86_INS_VPSCATTERDQ, {"vpscatterdq", {0, 0, 0, 0}}},
		{X86_INS_VPSCATTERQD, {"vpscatterqd", {0, 0, 0, 0}}},
		{X86_INS_VPSCATTERQQ, {"vpscatterqq", {0, 0, 0, 0}}},
		{X86_INS_VPSHAB, {"vpshab", {0, 0, 0, 0}}},
		{X86_INS_VPSHAD, {"vpshad", {0, 0, 0, 0}}},
		{X86_INS_VPSHAQ, {"vpshaq", {0, 0, 0, 0}}},
		{X86_INS_VPSHAW, {"vpshaw", {0, 0, 0, 0}}},
		{X86_INS_VPSHLB, {"vpshlb", {0, 0, 0, 0}}},
		{X86_INS_VPSHLD, {"vpshld", {0, 0, 0, 0}}},
		{X86_INS_VPSHLQ, {"vpshlq", {0, 0, 0, 0}}},
		{X86_INS_VPSHLW, {"vpshlw", {0, 0, 0, 0}}},
		{X86_INS_VPSHUFB, {"vpshufb", {0, 0, 0, 0}}},
		{X86_INS_VPSHUFD, {"vpshufd", {0, 0, 0, 0}}},
		{X86_INS_VPSHUFHW, {"vpshufhw", {0, 0, 0, 0}}},
		{X86_INS_VPSHUFLW, {"vpshuflw", {0, 0, 0, 0}}},
		{X86_INS_VPSIGNB, {"vpsignb", {0, 0, 0, 0}}},
		{X86_INS_VPSIGND, {"vpsignd", {0, 0, 0, 0}}},
		{X86_INS_VPSIGNW, {"vpsignw", {0, 0, 0, 0}}},
		{X86_INS_VPSLLDQ, {"vpslldq", {0, 0, 0, 0}}},
		{X86_INS_VPSLLD, {"vpslld", {0, 0, 0, 0}}},
		{X86_INS_VPSLLQ, {"vpsllq", {0, 0, 0, 0}}},
		{X86_INS_VPSLLVD, {"vpsllvd", {0, 0, 0, 0}}},
		{X86_INS_VPSLLVQ, {"vpsllvq", {0, 0, 0, 0}}},
		{X86_INS_VPSLLW, {"vpsllw", {0, 0, 0, 0}}},
		{X86_INS_VPSRAD, {"vpsrad", {0, 0, 0, 0}}},
		{X86_INS_VPSRAQ, {"vpsraq", {0, 0, 0, 0}}},
		{X86_INS_VPSRAVD, {"vpsravd", {0, 0, 0, 0}}},
		{X86_INS_VPSRAVQ, {"vpsravq", {0, 0, 0, 0}}},
		{X86_INS_VPSRAW, {"vpsraw", {0, 0, 0, 0}}},
		{X86_INS_VPSRLDQ, {"vpsrldq", {0, 0, 0, 0}}},
		{X86_INS_VPSRLD, {"vpsrld", {0, 0, 0, 0}}},
		{X86_INS_VPSRLQ, {"vpsrlq", {0, 0, 0, 0}}},
		{X86_INS_VPSRLVD, {"vpsrlvd", {0, 0, 0, 0}}},
		{X86_INS_VPSRLVQ, {"vpsrlvq", {0, 0, 0, 0}}},
		{X86_INS_VPSRLW, {"vpsrlw", {0, 0, 0, 0}}},
		{X86_INS_VPSUBB, {"vpsubb", {0, 0, 0, 0}}},
		{X86_INS_VPSUBD, {"vpsubd", {0, 0, 0, 0}}},
		{X86_INS_VPSUBQ, {"vpsubq", {0, 0, 0, 0}}},
		{X86_INS_VPSUBSB, {"vpsubsb", {0, 0, 0, 0}}},
		{X86_INS_VPSUBSW, {"vpsubsw", {0, 0, 0, 0}}},
		{X86_INS_VPSUBUSB, {"vpsubusb", {0, 0, 0, 0}}},
		{X86_INS_VPSUBUSW, {"vpsubusw", {0, 0, 0, 0}}},
		{X86_INS_VPSUBW, {"vpsubw", {0, 0, 0, 0}}},
		{X86_INS_VPTESTMD, {"vptestmd", {0, 0, 0, 0}}},
		{X86_INS_VPTESTMQ, {"vptestmq", {0, 0, 0, 0}}},
		{X86_INS_VPTESTNMD, {"vptestnmd", {0, 0, 0, 0}}},
		{X86_INS_VPTESTNMQ, {"vptestnmq", {0, 0, 0, 0}}},
		{X86_INS_VPTEST, {"vptest", {0, 0, 0, 0}}},
		{X86_INS_VPUNPCKHBW, {"vpunpckhbw", {0, 0, 0, 0}}},
		{X86_INS_VPUNPCKHDQ, {"vpunpckhdq", {0, 0, 0, 0}}},
		{X86_INS_VPUNPCKHQDQ, {"vpunpckhqdq", {0, 0, 0, 0}}},
		{X86_INS_VPUNPCKHWD, {"vpunpckhwd", {0, 0, 0, 0}}},
		{X86_INS_VPUNPCKLBW, {"vpunpcklbw", {0, 0, 0, 0}}},
		{X86_INS_VPUNPCKLDQ, {"vpunpckldq", {0, 0, 0, 0}}},
		{X86_INS_VPUNPCKLQDQ, {"vpunpcklqdq", {0, 0, 0, 0}}},
		{X86_INS_VPUNPCKLWD, {"vpunpcklwd", {0, 0, 0, 0}}},
		{X86_INS_VPXORD, {"vpxord", {0, 0, 0, 0}}},
		{X86_INS_VPXORQ, {"vpxorq", {0, 0, 0, 0}}},
		{X86_INS_VPXOR, {"vpxor", {0, 0, 0, 0}}},
		{X86_INS_VRCP14PD, {"vrcp14pd", {0, 0, 0, 0}}},
		{X86_INS_VRCP14PS, {"vrcp14ps", {0, 0, 0, 0}}},
		{X86_INS_VRCP14SD, {"vrcp14sd", {0, 0, 0, 0}}},
		{X86_INS_VRCP14SS, {"vrcp14ss", {0, 0, 0, 0}}},
		{X86_INS_VRCP28PD, {"vrcp28pd", {0, 0, 0, 0}}},
		{X86_INS_VRCP28PS, {"vrcp28ps", {0, 0, 0, 0}}},
		{X86_INS_VRCP28SD, {"vrcp28sd", {0, 0, 0, 0}}},
		{X86_INS_VRCP28SS, {"vrcp28ss", {0, 0, 0, 0}}},
		{X86_INS_VRCPPS, {"vrcpps", {0, 0, 0, 0}}},
		{X86_INS_VRCPSS, {"vrcpss", {0, 0, 0, 0}}},
		{X86_INS_VRNDSCALEPD, {"vrndscalepd", {0, 0, 0, 0}}},
		{X86_INS_VRNDSCALEPS, {"vrndscaleps", {0, 0, 0, 0}}},
		{X86_INS_VRNDSCALESD, {"vrndscalesd", {0, 0, 0, 0}}},
		{X86_INS_VRNDSCALESS, {"vrndscaless", {0, 0, 0, 0}}},
		{X86_INS_VROUNDPD, {"vroundpd", {0, 0, 0, 0}}},
		{X86_INS_VROUNDPS, {"vroundps", {0, 0, 0, 0}}},
		{X86_INS_VROUNDSD, {"vroundsd", {0, 0, 0, 0}}},
		{X86_INS_VROUNDSS, {"vroundss", {0, 0, 0, 0}}},
		{X86_INS_VRSQRT14PD, {"vrsqrt14pd", {0, 0, 0, 0}}},
		{X86_INS_VRSQRT14PS, {"vrsqrt14ps", {0, 0, 0, 0}}},
		{X86_INS_VRSQRT14SD, {"vrsqrt14sd", {0, 0, 0, 0}}},
		{X86_INS_VRSQRT14SS, {"vrsqrt14ss", {0, 0, 0, 0}}},
		{X86_INS_VRSQRT28PD, {"vrsqrt28pd", {0, 0, 0, 0}}},
		{X86_INS_VRSQRT28PS, {"vrsqrt28ps", {0, 0, 0, 0}}},
		{X86_INS_VRSQRT28SD, {"vrsqrt28sd", {0, 0, 0, 0}}},
		{X86_INS_VRSQRT28SS, {"vrsqrt28ss", {0, 0, 0, 0}}},
		{X86_INS_VRSQRTPS, {"vrsqrtps", {0, 0, 0, 0}}},
		{X86_INS_VRSQRTSS, {"vrsqrtss", {0, 0, 0, 0}}},
		{X86_INS_VSCATTERDPD, {"vscatterdpd", {0, 0, 0, 0}}},
		{X86_INS_VSCATTERDPS, {"vscatterdps", {0, 0, 0, 0}}},
		{X86_INS_VSCATTERPF0DPD, {"vscatterpf0dpd", {0, 0, 0, 0}}},
		{X86_INS_VSCATTERPF0DPS, {"vscatterpf0dps", {0, 0, 0, 0}}},
		{X86_INS_VSCATTERPF0QPD, {"vscatterpf0qpd", {0, 0, 0, 0}}},
		{X86_INS_VSCATTERPF0QPS, {"vscatterpf0qps", {0, 0, 0, 0}}},
		{X86_INS_VSCATTERPF1DPD, {"vscatterpf1dpd", {0, 0, 0, 0}}},
		{X86_INS_VSCATTERPF1DPS, {"vscatterpf1dps", {0, 0, 0, 0}}},
		{X86_INS_VSCATTERPF1QPD, {"vscatterpf1qpd", {0, 0, 0, 0}}},
		{X86_INS_VSCATTERPF1QPS, {"vscatterpf1qps", {0, 0, 0, 0}}},
		{X86_INS_VSCATTERQPD, {"vscatterqpd", {0, 0, 0, 0}}},
		{X86_INS_VSCATTERQPS, {"vscatterqps", {0, 0, 0, 0}}},
		{X86_INS_VSHUFPD, {"vshufpd", {0, 0, 0, 0}}},
		{X86_INS_VSHUFPS, {"vshufps", {0, 0, 0, 0}}},
		{X86_INS_VSQRTPD, {"vsqrtpd", {0, 0, 0, 0}}},
		{X86_INS_VSQRTPS, {"vsqrtps", {0, 0, 0, 0}}},
		{X86_INS_VSQRTSD, {"vsqrtsd", {0, 0, 0, 0}}},
		{X86_INS_VSQRTSS, {"vsqrtss", {0, 0, 0, 0}}},
		{X86_INS_VSTMXCSR, {"vstmxcsr", {0, 0, 0, 0}}},
		{X86_INS_VSUBPD, {"vsubpd", {0, 0, 0, 0}}},
		{X86_INS_VSUBPS, {"vsubps", {0, 0, 0, 0}}},
		{X86_INS_VSUBSD, {"vsubsd", {0, 0, 0, 0}}},
		{X86_INS_VSUBSS, {"vsubss", {0, 0, 0, 0}}},
		{X86_INS_VTESTPD, {"vtestpd", {0, 0, 0, 0}}},
		{X86_INS_VTESTPS, {"vtestps", {0, 0, 0, 0}}},
		{X86_INS_VUNPCKHPD, {"vunpckhpd", {0, 0, 0, 0}}},
		{X86_INS_VUNPCKHPS, {"vunpckhps", {0, 0, 0, 0}}},
		{X86_INS_VUNPCKLPD, {"vunpcklpd", {0, 0, 0, 0}}},
		{X86_INS_VUNPCKLPS, {"vunpcklps", {0, 0, 0, 0}}},
		{X86_INS_VZEROALL, {"vzeroall", {0, 0, 0, 0}}},
		{X86_INS_VZEROUPPER, {"vzeroupper", {0, 0, 0, 0}}},
		{X86_INS_WAIT, {"wait", {0, 0, 0, 0}}},
		{X86_INS_WBINVD, {"wbinvd", {0, 0, 0, 0}}},
		{X86_INS_WRFSBASE, {"wrfsbase", {0, 0, 0, 0}}},
		{X86_INS_WRGSBASE, {"wrgsbase", {0, 0, 0, 0}}},
		{X86_INS_WRMSR, {"wrmsr", {0, 0, 0, 0}}},
		{X86_INS_XABORT, {"xabort", {0, 0, 0, 0}}},
		{X86_INS_XACQUIRE, {"xacquire", {0, 0, 0, 0}}},
		{X86_INS_XBEGIN, {"xbegin", {0, 0, 0, 0}}},
		{X86_INS_FXCH, {"fxch", {0, 0, 0, 0}}},
		{X86_INS_XCRYPTCBC, {"xcryptcbc", {0, 0, 0, 0}}},
		{X86_INS_XCRYPTCFB, {"xcryptcfb", {0, 0, 0, 0}}},
		{X86_INS_XCRYPTCTR, {"xcryptctr", {0, 0, 0, 0}}},
		{X86_INS_XCRYPTECB, {"xcryptecb", {0, 0, 0, 0}}},
		{X86_INS_XCRYPTOFB, {"xcryptofb", {0, 0, 0, 0}}},
		{X86_INS_XEND, {"xend", {0, 0, 0, 0}}},
		{X86_INS_XGETBV, {"xgetbv", {0, 0, 0, 0}}},
		{X86_INS_XLATB, {"xlatb", {0, 0, 0, 0}}},
		{X86_INS_XRELEASE, {"xrelease", {0, 0, 0, 0}}},
		{X86_INS_XRSTOR, {"xrstor", {0, 0, 0, 0}}},
		{X86_INS_XRSTOR64, {"xrstor64", {0, 0, 0, 0}}},
		{X86_INS_XSAVE, {"xsave", {0, 0, 0, 0}}},
		{X86_INS_XSAVE64, {"xsave64", {0, 0, 0, 0}}},
		{X86_INS_XSAVEOPT, {"xsaveopt", {0, 0, 0, 0}}},
		{X86_INS_XSAVEOPT64, {"xsaveopt64", {0, 0, 0, 0}}},
		{X86_INS_XSETBV, {"xsetbv", {0, 0, 0, 0}}},
		{X86_INS_XSHA1, {"xsha1", {0, 0, 0, 0}}},
		{X86_INS_XSHA256, {"xsha256", {0, 0, 0, 0}}},
		{X86_INS_XSTORE, {"xst"}},
	},
};
