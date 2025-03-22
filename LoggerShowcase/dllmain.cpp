// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include <format> // for this to work we need to use C++20

#include "Logger.h"

HMODULE myhModule;

DWORD __stdcall EjectThread(LPVOID lpParameter) {
	Sleep(100);
	FreeLibraryAndExitThread(myhModule, 0);
	Sleep(100);
	return 0;
}

//"main" loop
int WINAPI main()
{
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout); // output only

	Logger logger("S:\\Videos\\40 Logging\\log.csv");

	logger.log("Warning", "Hook failed", "Present hook failed. Access violation.");

	for (int i = 0; i < 50; i++) {
		logger.log("Info", "Keyboard", "Key pressed: " + std::to_string(i));
	}

	for (int i = 0; i < 111; i++) {
		std::string details = "Matrix: \n";
			for (int j = 0; j < 4; j++) {
				details += std::format("-[ {:.3f} {:.3f} {:.3f} {:.3f} ]\n", static_cast<float>(j), static_cast<float>(j), static_cast<float>(j), static_cast<float>(j));
			}

		logger.log("Info", "SetConstantBuffers", details);
	}

	logger.log("Warning", "Global", "Dont u dare copy protected memory!");
	logger.log("Warning", "Again", "This is your last warning. Dont u dare ...");
	logger.log("Error", "DirectX", "Failed to create device.");
	logger.log("Error", "DirectX", "Failed to create swap chain.");
	logger.log("Error", "Critical", "U done it now bro.");

	// Main Loop
	std::cout << "[0] Exit\n[1] Print all\n[2] Types\n[3] Titles\n[4] Filtered (Errors)\n[5] Delete logs." << std::endl;
	while (1) {
		Sleep(100);
		if (GetAsyncKeyState(VK_NUMPAD0))
		{
			break;
		}
		else if (GetAsyncKeyState(VK_NUMPAD1))
		{
			logger.print();
			std::cout << "[0] Exit\n[1] Print all\n[2] Types\n[3] Titles\n[4] Filtered (Errors)" << std::endl;
		}
		else if (GetAsyncKeyState(VK_NUMPAD2))
		{
			logger.print(true);
			std::cout << "[0] Exit\n[1] Print all\n[2] Types\n[3] Titles\n[4] Filtered (Errors)" << std::endl;
		}
		else if (GetAsyncKeyState(VK_NUMPAD3))
		{
			logger.print(true, "Title");
			std::cout << "[0] Exit\n[1] Print all\n[2] Types\n[3] Titles\n[4] Filtered (Errors)" << std::endl;
		}
		else if (GetAsyncKeyState(VK_NUMPAD4))
		{
			logger.print(false, "", "Error");
			std::cout << "[0] Exit\n[1] Print all\n[2] Types\n[3] Titles\n[4] Filtered (Errors)" << std::endl;
		}
		else if (GetAsyncKeyState(VK_NUMPAD5))
		{
			logger.deleteLogs();
			std::cout << "Aaaand its gone" << std::endl;
		}
	}
	if (fp) { fclose(fp); }
	FreeConsole();

	CreateThread(0, 0, EjectThread, 0, 0, 0);

	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        myhModule = hModule;
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)main, NULL, 0, NULL);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

