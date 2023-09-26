#include "pch.h"
#include "SKCModLoader.h"

const void* const KosDecPtr = (void*)0x41034B;
__declspec(naked) void KosDec()
{
	__asm
	{
		push esi
		call [KosDecPtr]
		pop esi
		ret
	}
}

void FixPachinkoPal()
{
	uint16_t* palstart = reg_a1.UWord;
	KosDec();
	uint16_t* palend = reg_a1.UWord;
	for (; palstart < palend; ++palstart)
		*palstart = _byteswap_ushort(*palstart);
}

extern "C"
{
	__declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
	{
		WriteCall((void*)0x44CFFF, FixPachinkoPal);
	}

	__declspec(dllexport) ModInfo SKCModInfo = { ModLoaderVer };
}