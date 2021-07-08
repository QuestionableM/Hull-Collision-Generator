#include "../MainGUI.h"
#include "../InfoGUI.h"

#include <filesystem>
#include <fstream>
#include <msclr/marshal_cppstd.h>

#define MANUAL_COL_DEFINITION 0
#define AUTOMATIC_COL_DEFINITION 1

namespace fs = std::filesystem;

namespace HCG {
	using namespace HullCollisionGenerator;
}

typedef HCG::MainGUI _MainGUI;

_MainGUI::MainGUI() {
	this->InitializeComponent();

	SendMessage(
		static_cast<HWND>(this->ModelPath_TB->Handle.ToPointer()),
		EM_SETCUEBANNER,
		0,
		(LPARAM)L"Model Path"
	);

	this->gen_timer = new std::chrono::system_clock::time_point();

	this->ColType_CB->SelectedIndex = 0;
	this->ColType_CB->SelectedIndexChanged += gcnew System::EventHandler(this, &MainGUI::ColType_CB_SelectedIndexChanged);
}

_MainGUI::~MainGUI() {
	delete this->gen_timer;
	if (components) delete components;
}

void _MainGUI::Generate_BTN_Click(System::Object^ sender, System::EventArgs^ e) {
	std::wstring _WstrModelPath = msclr::interop::marshal_as<std::wstring>(this->ModelPath_TB->Text);

	if (!this->FileExists(_WstrModelPath)) {
		System::Windows::Forms::MessageBox::Show(
			L"The specified path is invalid",
			L"Invalid Path",
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Warning
		);

		return;
	}

	fs::directory_entry path_entr(_WstrModelPath);
	if (!path_entr.is_regular_file()) {
		System::Windows::Forms::MessageBox::Show(
			L"The specified path doesn't lead to a file!",
			L"Invalid Path",
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Warning
		);

		return;
	}

	int cur_mode = this->ColType_CB->SelectedIndex;

	if (cur_mode != 0 && cur_mode != 1)
		cur_mode = 0;

	bool is_auto_mode = (cur_mode == AUTOMATIC_COL_DEFINITION);

	long size_x = is_auto_mode ? 1l : long::Parse(this->SizeX_TB->Text);
	long size_y = is_auto_mode ? 1l : long::Parse(this->SizeY_TB->Text);
	long size_z = is_auto_mode ? 1l : long::Parse(this->SizeZ_TB->Text);

	if (size_x <= 0 || size_y <= 0 || size_z <= 0) {
		System::Windows::Forms::MessageBox::Show(
			L"Collision Size has to be at least 1x1x1",
			L"Invalid Collision",
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Warning
		);

		return;
	}

	System::Array^ ThreadData = gcnew cli::array<System::Object^>(5);

	ThreadData->SetValue(this->ModelPath_TB->Text, (int)0);
	ThreadData->SetValue(size_x, (int)1);
	ThreadData->SetValue(size_y, (int)2);
	ThreadData->SetValue(size_z, (int)3);
	ThreadData->SetValue(this->ColType_CB->SelectedIndex, (int)4);
	
	this->GeneratorThread->RunWorkerAsync(ThreadData);
	this->SetLockInterfaceState(false);
	*this->gen_timer = std::chrono::system_clock::now();
}

void _MainGUI::ModelExplorer_BTN_Click(System::Object^ sender, System::EventArgs^ e) {
	std::wstring _FileName = this->OpenFileName(
		L"Select a 3D Model",
		0,
		L"All Files (*.*)\0*.*\0",
		static_cast<HWND>(this->Handle.ToPointer())
	);

	if (_FileName.empty()) return;

	this->ModelPath_TB->Text = gcnew System::String(_FileName.c_str());
}

std::wstring _MainGUI::OpenFileName(
	const std::wstring& title,
	FILEOPENDIALOGOPTIONS options,
	LPCWSTR filter,
	HWND owner
) {
	std::wstring _Output = L"";

	HRESULT hr = CoInitializeEx(NULL, COINIT_DISABLE_OLE1DDE | COINIT_APARTMENTTHREADED);

	if (SUCCEEDED(hr)) {
		IFileOpenDialog* pFileOpen;

		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr)) {
			pFileOpen->SetOptions(options);
			pFileOpen->SetTitle(title.c_str());
			hr = pFileOpen->Show(owner);

			if (SUCCEEDED(hr)) {
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr)) {
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					if (SUCCEEDED(hr)) {
						_Output = std::wstring(pszFilePath);
						CoTaskMemFree(pszFilePath);
					}

					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}

	return _Output;
}

void _MainGUI::ModelPath_TB_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	this->UpdateTextData();
}

void _MainGUI::Size_TB_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	this->UpdateTextData();
}

void _MainGUI::UpdateTextData() {
	bool ignore_size = (this->ColType_CB->SelectedIndex == MANUAL_COL_DEFINITION);

	bool SizeXText = (this->SizeX_TB->TextLength > 0);
	bool SizeYText = (this->SizeY_TB->TextLength > 0);
	bool SizeZText = (this->SizeZ_TB->TextLength > 0);
	bool size_bool = ((ignore_size && (SizeXText && SizeYText && SizeZText)) || !ignore_size);
	bool ModelPath = (this->ModelPath_TB->TextLength > 0);

	this->Generate_BTN->Enabled = (size_bool && ModelPath);
}

bool _MainGUI::FileExists(std::wstring& path) {
	try {
		bool _exists = fs::exists(path);

		return _exists;
	}
	catch (...) {}

	return false;
}

void _MainGUI::SizeTB_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (System::Char::IsDigit(e->KeyChar) || e->KeyChar == 0x08 || e->KeyChar == 0x01) return;

	e->Handled = true;
}

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

std::wstring Utf8ToWide(const std::string& str) {
	int count = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(), NULL, 0);
	std::wstring wstr(count, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(), &wstr[0], count);
	return wstr;
}

std::string WideToUtf8(const std::wstring& wstr) {
	int count = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.length(), NULL, 0, NULL, NULL);
	std::string str(count, 0);
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
	return str;
}

void _MainGUI::GeneratorThread_DoWork(
	System::Object^ sender,
	System::ComponentModel::DoWorkEventArgs^ e
) {
	System::Array^ DataArr = safe_cast<System::Array^>(e->Argument);

	System::String^ ModelPathS = safe_cast<System::String^>(DataArr->GetValue((int)0));
	long SizeX = safe_cast<long>(DataArr->GetValue((int)1));
	long SizeY = safe_cast<long>(DataArr->GetValue((int)2));
	long SizeZ = safe_cast<long>(DataArr->GetValue((int)3));
	int col_type = safe_cast<int>(DataArr->GetValue((int)4));

	std::wstring ModelPathWstr = msclr::interop::marshal_as<std::wstring>(ModelPathS);

	std::vector<glm::vec3> point_list = {};
	glm::vec3 pt_bounds = { 0.0f, 0.0f, 0.0f };

	if (col_type == MANUAL_COL_DEFINITION)
		pt_bounds = { SizeX, SizeY, SizeZ };

	this->GeneratorThread->ReportProgress(0);
	if (!this->LoadModelVertices(ModelPathWstr, point_list, pt_bounds, col_type)) {
		e->Result = 1;
		return;
	}

	this->GeneratorThread->ReportProgress(1);
	if (!this->GenerateAndWriteCollision(ModelPathWstr, point_list, pt_bounds, col_type)) {
		e->Result = 2;
		return;
	}

	this->GeneratorThread->ReportProgress(2);
}

void _MainGUI::GeneratorThread_RunWorkerCompleted(
	System::Object^ sender,
	System::ComponentModel::RunWorkerCompletedEventArgs^ e
) {
	if (e->Result != nullptr) {
		int error_code = safe_cast<int>(e->Result);

		System::String^ ErrorMsg;

		switch (error_code) {
		case 1:
			ErrorMsg = L"Something went wrong while trying to convert the specified file to a hull collision.\n\nPossible issues: the specified file is not a 3d model";
			break;
		case 2:
			ErrorMsg = L"Something went wrong while trying to write the hull collision to the file";
			break;
		default:
			ErrorMsg = L"UnknownError";
			break;
		}

		System::Windows::Forms::MessageBox::Show(
			ErrorMsg,
			"Error",
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Warning
		);
	}
	else {
		auto cur_time = std::chrono::system_clock::now();
		long long elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - *this->gen_timer).count();

		System::Windows::Forms::MessageBox::Show(
			gcnew System::String((L"A collision has been successfully generated!\n\nElapsed time: " + std::to_wstring(elapsed_time) + L"ms").c_str()),
			"Success",
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Information
		);
	}

	this->Progress_LBL->Text = L"No Task";
	this->SetLockInterfaceState(true);
}

const static std::vector<std::wstring> ProgressValues = {
	L"Loading Model...",
	L"Writing Collision...",
	L"Finishing Process..."
};

void _MainGUI::GeneratorThread_ProgressChanged(
	System::Object^ sender,
	System::ComponentModel::ProgressChangedEventArgs^ e
) {
	int cur_idx = e->ProgressPercentage;
	const std::wstring& cur_text = ProgressValues[cur_idx];

	this->Progress_LBL->Text = gcnew System::String(cur_text.c_str());
}

bool _MainGUI::LoadModelVertices(
	std::wstring& path,
	std::vector<glm::vec3>& pt_list,
	glm::vec3& bounds,
	int& mode
) {
	try {
		Assimp::Importer _Importer;

		const aiScene* ModelScene = _Importer.ReadFile(
			WideToUtf8(path).c_str(),
			aiProcess_RemoveComponent |
			aiProcess_RemoveRedundantMaterials |
			aiProcess_JoinIdenticalVertices |
			aiProcess_FindDegenerates |
			aiProcess_OptimizeMeshes |
			aiProcess_FindInvalidData
		);

		if (ModelScene && ModelScene->HasMeshes()) {

			for (uint32_t a = 0; a < ModelScene->mNumMeshes; a++) {
				const aiMesh* CurMesh = ModelScene->mMeshes[a];

				pt_list.reserve(CurMesh->mNumVertices);
				for (uint32_t b = 0; b < CurMesh->mNumVertices; b++) {
					const aiVector3D vert = CurMesh->mVertices[b];

					glm::vec3 NewVec = glm::vec3(vert.x, vert.y, vert.z) * 2.0f;
					pt_list.push_back(NewVec);

					if (mode != AUTOMATIC_COL_DEFINITION) continue;

					bounds.x = std::fmaxf(bounds.x, std::fabs(NewVec.x));
					bounds.y = std::fmaxf(bounds.y, std::fabs(NewVec.y));
					bounds.z = std::fmaxf(bounds.z, std::fabs(NewVec.z));
				}
			}

			_Importer.FreeScene();
		}
		else {
			_Importer.FreeScene();
			return false;
		}
	}
	catch (...) {
		return false;
	}

	return true;
}

bool _MainGUI::GenerateAndWriteCollision(
	std::wstring& file_name,
	std::vector<glm::vec3>& pt_list,
	glm::vec3& bounds,
	int& mode
) {
	const std::wstring output_path = L"./Collisions";

	if (!fs::exists(output_path))
		fs::create_directory(output_path);

	fs::directory_entry dir_entr(file_name);
	fs::path path_str = dir_entr.path();
	std::wstring f_name = path_str.has_stem() ? path_str.stem().wstring() : L"UnknownCollision";

	std::ofstream out_file(output_path + L"/" + f_name + L".json");
	if (out_file.is_open()) {
		float bound_x = std::ceilf(bounds.x);
		float bound_y = std::ceilf(bounds.y);
		float bound_z = std::ceilf(bounds.z);

		out_file << "/*\n";
		out_file << "\tGenerated by the tool created by Questionable Mark\n";
		out_file << "\tOriginal file name: " << WideToUtf8(f_name) << "\n";
		out_file << "*/\n\n{\n\t\"hull\":{\n\t\t";
		out_file << "\"x\": " << (int)bound_x << ", \"y\": " << (int)bound_y << ", \"z\": " << (int)bound_z << ", \"margin\": 0.05,\n";
		out_file << "\t\t\"pointList\": [\n";

		for (unsigned int a = 0; a < pt_list.size(); a++) {
			if (a > 0) out_file.write(",\n", 2);

			glm::vec3& col_pt = pt_list[a];

			std::string x_str = std::to_string(col_pt.x / bound_x);
			std::string y_str = std::to_string(col_pt.y / bound_y);
			std::string z_str = std::to_string(col_pt.z / bound_z);

			std::string col_str = "\t\t\t{";
			col_str.append("\"x\": ", 5);
			col_str.append(x_str.c_str(), x_str.length());
			col_str.append(", \"y\": ", 7);
			col_str.append(y_str.c_str(), y_str.length());
			col_str.append(", \"z\": ", 7);
			col_str.append(z_str.c_str(), z_str.length());
			col_str.append("}");

			out_file.write(col_str.c_str(), col_str.length());
		}

		out_file << "\n\t\t]\n\t}\n}\n\n";
		
		out_file << "/*\n";

		auto cur_time = std::chrono::system_clock::now();
		long long elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - *this->gen_timer).count();

		out_file << "\tElapsed time: " << elapsed_time << "ms\n";
		out_file << "\tAmount of collision points: " << pt_list.size() << "\n";
		out_file << "*/";

		out_file.close();

		return true;
	}

	return false;
}

void _MainGUI::SetLockInterfaceState(bool state) {
	this->ModelPath_TB->Enabled = state;
	this->SizeX_TB->Enabled = state;
	this->SizeY_TB->Enabled = state;
	this->SizeZ_TB->Enabled = state;
	this->ModelExplorer_BTN->Enabled = state;
	this->ColType_CB->Enabled = state;
	this->Info_BTN->Enabled = state;

	this->Generate_BTN->Enabled = (state && this->ModelPath_TB->TextLength > 0);
}

void _MainGUI::ColType_CB_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	int sel_idx = this->ColType_CB->SelectedIndex;

	bool panel_enabled = (sel_idx == MANUAL_COL_DEFINITION);

	this->SizeX_TB->Visible = panel_enabled;
	this->SizeY_TB->Visible = panel_enabled;
	this->SizeZ_TB->Visible = panel_enabled;
	this->XSz_LBL->Visible = panel_enabled;
	this->YSz_LBL->Visible = panel_enabled;
	this->ZSz_LBL->Visible = panel_enabled;
	
	this->ClientSize = System::Drawing::Size(384, panel_enabled ? 216 : 166);
	this->CollisionSettings_GB->Size = System::Drawing::Size(348, panel_enabled ? 100 : 50);
	this->CollisionSettings_GB->Location = System::Drawing::Point(6, 47);

	this->UpdateTextData();
}

void _MainGUI::Info_BTN_Click(System::Object^ sender, System::EventArgs^ e) {
	HCG::InfoGUI^ info_gui = gcnew HCG::InfoGUI();
	info_gui->ShowDialog();

	delete info_gui;
}