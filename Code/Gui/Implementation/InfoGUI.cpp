#include "../InfoGUI.h"
#include "../../BuildVersion.h"

#include <Windows.h>

namespace HCG {
	using namespace HullCollisionGenerator;
};

typedef HCG::InfoGUI _InfoGui;

#include <string>

_InfoGui::InfoGUI() {
	this->InitializeComponent();

	this->Version_LBL->Text += gcnew System::String((L"." + std::to_wstring(HCG_BUILD_VERSION)).c_str());

#if _WIN64
	this->Version_LBL->Text += L" (x64)";
#else
	this->Version_LBL->Text += L" (x86)";
#endif

#if _DEBUG
	this->Version_LBL->Text += L" DEBUG";
#endif
}

_InfoGui::~InfoGUI() {
	if (components) delete components;
}

void _InfoGui::Author_LLBL_LinkClicked(
	System::Object^ sender,
	System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e
) {
	System::Diagnostics::Process::Start(L"https://github.com/QuestionableM");
}

void _InfoGui::GithubRepo_LLBL_LinkClicked(
	System::Object^ sender,
	System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e
) {
	//add the link to the repository here later
}

void _InfoGui::Assimp_LLBL_LinkClicked(
	System::Object^ sender,
	System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e
) {
	System::Diagnostics::Process::Start(L"https://github.com/assimp/assimp");
}

void _InfoGui::MouseKillFocus(
	System::Object^ sender,
	System::Windows::Forms::MouseEventArgs^ e
) {
	this->Info_TB->SelectionLength = 0;
	SendMessage(
		static_cast<HWND>(this->Info_TB->Handle.ToPointer()),
		WM_KILLFOCUS,
		0,
		NULL
	);
}