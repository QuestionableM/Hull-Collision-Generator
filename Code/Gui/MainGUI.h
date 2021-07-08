#pragma once

#include <string>
#include <Windows.h>
#include <shobjidl.h>

#include <vector>
#include <glm.hpp>

#include <chrono>

namespace HullCollisionGenerator {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainGUI : public System::Windows::Forms::Form
	{
	public:
		std::chrono::system_clock::time_point* gen_timer = nullptr;
		MainGUI();

	protected:
		~MainGUI();

	private:
		System::Windows::Forms::GroupBox^ ModelSettings_GB;
		System::Windows::Forms::TextBox^ ModelPath_TB;
		System::Windows::Forms::Button^ ModelExplorer_BTN;
	private: System::Windows::Forms::TextBox^ SizeZ_TB;

	private: System::Windows::Forms::TextBox^ SizeY_TB;

	private: System::Windows::Forms::TextBox^ SizeX_TB;

		System::Windows::Forms::Label^ ZSz_LBL;
		System::Windows::Forms::Label^ YSz_LBL;
		System::Windows::Forms::Label^ XSz_LBL;
		System::Windows::Forms::Button^ Generate_BTN;
		System::ComponentModel::BackgroundWorker^ GeneratorThread;
	private: System::Windows::Forms::GroupBox^ CollisionSettings_GB;
	private: System::Windows::Forms::ComboBox^ ColType_CB;
	private: System::Windows::Forms::Label^ Progress_LBL;
	private: System::Windows::Forms::Button^ Info_BTN;

		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->ModelSettings_GB = (gcnew System::Windows::Forms::GroupBox());
			this->CollisionSettings_GB = (gcnew System::Windows::Forms::GroupBox());
			this->ColType_CB = (gcnew System::Windows::Forms::ComboBox());
			this->SizeZ_TB = (gcnew System::Windows::Forms::TextBox());
			this->ZSz_LBL = (gcnew System::Windows::Forms::Label());
			this->XSz_LBL = (gcnew System::Windows::Forms::Label());
			this->YSz_LBL = (gcnew System::Windows::Forms::Label());
			this->SizeY_TB = (gcnew System::Windows::Forms::TextBox());
			this->SizeX_TB = (gcnew System::Windows::Forms::TextBox());
			this->ModelPath_TB = (gcnew System::Windows::Forms::TextBox());
			this->ModelExplorer_BTN = (gcnew System::Windows::Forms::Button());
			this->Generate_BTN = (gcnew System::Windows::Forms::Button());
			this->GeneratorThread = (gcnew System::ComponentModel::BackgroundWorker());
			this->Progress_LBL = (gcnew System::Windows::Forms::Label());
			this->Info_BTN = (gcnew System::Windows::Forms::Button());
			this->ModelSettings_GB->SuspendLayout();
			this->CollisionSettings_GB->SuspendLayout();
			this->SuspendLayout();
			// 
			// ModelSettings_GB
			// 
			this->ModelSettings_GB->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->ModelSettings_GB->Controls->Add(this->CollisionSettings_GB);
			this->ModelSettings_GB->Controls->Add(this->ModelPath_TB);
			this->ModelSettings_GB->Controls->Add(this->ModelExplorer_BTN);
			this->ModelSettings_GB->Location = System::Drawing::Point(12, 12);
			this->ModelSettings_GB->Name = L"ModelSettings_GB";
			this->ModelSettings_GB->Size = System::Drawing::Size(360, 153);
			this->ModelSettings_GB->TabIndex = 0;
			this->ModelSettings_GB->TabStop = false;
			this->ModelSettings_GB->Text = L"Model Settings";
			// 
			// CollisionSettings_GB
			// 
			this->CollisionSettings_GB->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->CollisionSettings_GB->Controls->Add(this->ColType_CB);
			this->CollisionSettings_GB->Controls->Add(this->SizeZ_TB);
			this->CollisionSettings_GB->Controls->Add(this->ZSz_LBL);
			this->CollisionSettings_GB->Controls->Add(this->XSz_LBL);
			this->CollisionSettings_GB->Controls->Add(this->YSz_LBL);
			this->CollisionSettings_GB->Controls->Add(this->SizeY_TB);
			this->CollisionSettings_GB->Controls->Add(this->SizeX_TB);
			this->CollisionSettings_GB->Location = System::Drawing::Point(6, 47);
			this->CollisionSettings_GB->Name = L"CollisionSettings_GB";
			this->CollisionSettings_GB->Size = System::Drawing::Size(348, 100);
			this->CollisionSettings_GB->TabIndex = 9;
			this->CollisionSettings_GB->TabStop = false;
			this->CollisionSettings_GB->Text = L"Collision Size";
			// 
			// ColType_CB
			// 
			this->ColType_CB->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->ColType_CB->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ColType_CB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ColType_CB->FormattingEnabled = true;
			this->ColType_CB->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Set Manually", L"Set Automatically" });
			this->ColType_CB->Location = System::Drawing::Point(6, 19);
			this->ColType_CB->Name = L"ColType_CB";
			this->ColType_CB->Size = System::Drawing::Size(336, 24);
			this->ColType_CB->TabIndex = 8;
			// 
			// SizeZ_TB
			// 
			this->SizeZ_TB->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->SizeZ_TB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SizeZ_TB->Location = System::Drawing::Point(234, 72);
			this->SizeZ_TB->MaxLength = 4;
			this->SizeZ_TB->Name = L"SizeZ_TB";
			this->SizeZ_TB->Size = System::Drawing::Size(108, 22);
			this->SizeZ_TB->TabIndex = 4;
			this->SizeZ_TB->TextChanged += gcnew System::EventHandler(this, &MainGUI::Size_TB_TextChanged);
			this->SizeZ_TB->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainGUI::SizeTB_KeyPress);
			// 
			// ZSz_LBL
			// 
			this->ZSz_LBL->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->ZSz_LBL->AutoSize = true;
			this->ZSz_LBL->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ZSz_LBL->Location = System::Drawing::Point(231, 53);
			this->ZSz_LBL->Name = L"ZSz_LBL";
			this->ZSz_LBL->Size = System::Drawing::Size(48, 16);
			this->ZSz_LBL->TabIndex = 7;
			this->ZSz_LBL->Text = L"Size Z:";
			// 
			// XSz_LBL
			// 
			this->XSz_LBL->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->XSz_LBL->AutoSize = true;
			this->XSz_LBL->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->XSz_LBL->Location = System::Drawing::Point(6, 53);
			this->XSz_LBL->Name = L"XSz_LBL";
			this->XSz_LBL->Size = System::Drawing::Size(48, 16);
			this->XSz_LBL->TabIndex = 5;
			this->XSz_LBL->Text = L"Size X:";
			// 
			// YSz_LBL
			// 
			this->YSz_LBL->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->YSz_LBL->AutoSize = true;
			this->YSz_LBL->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->YSz_LBL->Location = System::Drawing::Point(117, 53);
			this->YSz_LBL->Name = L"YSz_LBL";
			this->YSz_LBL->Size = System::Drawing::Size(49, 16);
			this->YSz_LBL->TabIndex = 6;
			this->YSz_LBL->Text = L"Size Y:";
			// 
			// SizeY_TB
			// 
			this->SizeY_TB->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->SizeY_TB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SizeY_TB->Location = System::Drawing::Point(120, 72);
			this->SizeY_TB->MaxLength = 4;
			this->SizeY_TB->Name = L"SizeY_TB";
			this->SizeY_TB->Size = System::Drawing::Size(108, 22);
			this->SizeY_TB->TabIndex = 3;
			this->SizeY_TB->TextChanged += gcnew System::EventHandler(this, &MainGUI::Size_TB_TextChanged);
			this->SizeY_TB->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainGUI::SizeTB_KeyPress);
			// 
			// SizeX_TB
			// 
			this->SizeX_TB->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->SizeX_TB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SizeX_TB->Location = System::Drawing::Point(6, 72);
			this->SizeX_TB->MaxLength = 4;
			this->SizeX_TB->Name = L"SizeX_TB";
			this->SizeX_TB->Size = System::Drawing::Size(108, 22);
			this->SizeX_TB->TabIndex = 2;
			this->SizeX_TB->TextChanged += gcnew System::EventHandler(this, &MainGUI::Size_TB_TextChanged);
			this->SizeX_TB->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainGUI::SizeTB_KeyPress);
			// 
			// ModelPath_TB
			// 
			this->ModelPath_TB->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->ModelPath_TB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ModelPath_TB->Location = System::Drawing::Point(6, 19);
			this->ModelPath_TB->Name = L"ModelPath_TB";
			this->ModelPath_TB->Size = System::Drawing::Size(294, 22);
			this->ModelPath_TB->TabIndex = 1;
			this->ModelPath_TB->TextChanged += gcnew System::EventHandler(this, &MainGUI::ModelPath_TB_TextChanged);
			// 
			// ModelExplorer_BTN
			// 
			this->ModelExplorer_BTN->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ModelExplorer_BTN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->ModelExplorer_BTN->Location = System::Drawing::Point(306, 19);
			this->ModelExplorer_BTN->Name = L"ModelExplorer_BTN";
			this->ModelExplorer_BTN->Size = System::Drawing::Size(48, 22);
			this->ModelExplorer_BTN->TabIndex = 0;
			this->ModelExplorer_BTN->Text = L"...";
			this->ModelExplorer_BTN->UseVisualStyleBackColor = true;
			this->ModelExplorer_BTN->Click += gcnew System::EventHandler(this, &MainGUI::ModelExplorer_BTN_Click);
			// 
			// Generate_BTN
			// 
			this->Generate_BTN->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->Generate_BTN->Enabled = false;
			this->Generate_BTN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Generate_BTN->Location = System::Drawing::Point(254, 172);
			this->Generate_BTN->Name = L"Generate_BTN";
			this->Generate_BTN->Size = System::Drawing::Size(118, 32);
			this->Generate_BTN->TabIndex = 1;
			this->Generate_BTN->Text = L"Generate";
			this->Generate_BTN->UseVisualStyleBackColor = true;
			this->Generate_BTN->Click += gcnew System::EventHandler(this, &MainGUI::Generate_BTN_Click);
			// 
			// GeneratorThread
			// 
			this->GeneratorThread->WorkerReportsProgress = true;
			this->GeneratorThread->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainGUI::GeneratorThread_DoWork);
			this->GeneratorThread->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MainGUI::GeneratorThread_ProgressChanged);
			this->GeneratorThread->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MainGUI::GeneratorThread_RunWorkerCompleted);
			// 
			// Progress_LBL
			// 
			this->Progress_LBL->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->Progress_LBL->AutoSize = true;
			this->Progress_LBL->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Progress_LBL->Location = System::Drawing::Point(9, 191);
			this->Progress_LBL->Name = L"Progress_LBL";
			this->Progress_LBL->Size = System::Drawing::Size(60, 16);
			this->Progress_LBL->TabIndex = 2;
			this->Progress_LBL->Text = L"No Task";
			// 
			// Info_BTN
			// 
			this->Info_BTN->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->Info_BTN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Info_BTN->Location = System::Drawing::Point(173, 172);
			this->Info_BTN->Name = L"Info_BTN";
			this->Info_BTN->Size = System::Drawing::Size(75, 32);
			this->Info_BTN->TabIndex = 3;
			this->Info_BTN->Text = L"Info";
			this->Info_BTN->UseVisualStyleBackColor = true;
			this->Info_BTN->Click += gcnew System::EventHandler(this, &MainGUI::Info_BTN_Click);
			// 
			// MainGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(384, 216);
			this->Controls->Add(this->Info_BTN);
			this->Controls->Add(this->Progress_LBL);
			this->Controls->Add(this->Generate_BTN);
			this->Controls->Add(this->ModelSettings_GB);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MainGUI";
			this->ShowIcon = false;
			this->Text = L"Hull Collision Generator";
			this->ModelSettings_GB->ResumeLayout(false);
			this->ModelSettings_GB->PerformLayout();
			this->CollisionSettings_GB->ResumeLayout(false);
			this->CollisionSettings_GB->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		void Generate_BTN_Click(System::Object^ sender, System::EventArgs^ e);
		void ModelExplorer_BTN_Click(System::Object^ sender, System::EventArgs^ e);

		std::wstring OpenFileName(
			const std::wstring& title,
			FILEOPENDIALOGOPTIONS options,
			LPCWSTR filter,
			HWND owner
		);

		System::Void ModelPath_TB_TextChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void Size_TB_TextChanged(System::Object^ sender, System::EventArgs^ e);

		void UpdateTextData();
		bool FileExists(std::wstring& path);

		System::Void SizeTB_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
		System::Void GeneratorThread_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
		System::Void GeneratorThread_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e);
		System::Void GeneratorThread_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e);

		bool LoadModelVertices(
			std::wstring& path,
			std::vector<glm::vec3>& pt_list,
			glm::vec3& bounds,
			int& mode
		);

		bool GenerateAndWriteCollision(
			std::wstring& file_name,
			std::vector<glm::vec3>& pt_list,
			glm::vec3& bounds,
			int& mode
		);

		void SetLockInterfaceState(bool state);
		System::Void ColType_CB_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void Info_BTN_Click(System::Object^ sender, System::EventArgs^ e);
	};
}