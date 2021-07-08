#include <Windows.h>

#include "Gui/MainGUI.h"

namespace HCG {
	using namespace HullCollisionGenerator;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	CoUninitialize();

	HCG::Application::EnableVisualStyles();
	HCG::Application::SetCompatibleTextRenderingDefault(false);
	HCG::Application::Run(gcnew HCG::MainGUI);

	return 0;
}