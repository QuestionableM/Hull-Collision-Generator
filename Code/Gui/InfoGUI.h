#pragma once

namespace HullCollisionGenerator {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class InfoGUI : public System::Windows::Forms::Form
	{
	public:
		InfoGUI();

	protected:
		~InfoGUI();

	private:
		System::Windows::Forms::TextBox^ Info_TB;
		System::Windows::Forms::Label^ Version_LBL;
		System::Windows::Forms::LinkLabel^ GithubRepo_LLBL;
		System::Windows::Forms::LinkLabel^ Author_LLBL;
	private: System::Windows::Forms::LinkLabel^ Assimp_LLBL;
		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->Info_TB = (gcnew System::Windows::Forms::TextBox());
			this->Version_LBL = (gcnew System::Windows::Forms::Label());
			this->GithubRepo_LLBL = (gcnew System::Windows::Forms::LinkLabel());
			this->Author_LLBL = (gcnew System::Windows::Forms::LinkLabel());
			this->Assimp_LLBL = (gcnew System::Windows::Forms::LinkLabel());
			this->SuspendLayout();
			// 
			// Info_TB
			// 
			this->Info_TB->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Info_TB->BackColor = System::Drawing::SystemColors::Menu;
			this->Info_TB->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->Info_TB->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->Info_TB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Info_TB->Location = System::Drawing::Point(12, 12);
			this->Info_TB->Multiline = true;
			this->Info_TB->Name = L"Info_TB";
			this->Info_TB->ReadOnly = true;
			this->Info_TB->ShortcutsEnabled = false;
			this->Info_TB->Size = System::Drawing::Size(346, 49);
			this->Info_TB->TabIndex = 0;
			this->Info_TB->TabStop = false;
			this->Info_TB->Text = L"This tool allows you to create hull collisions for Scrap Mechanic with ease. All "
				L"you need is a collision model!";
			this->Info_TB->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &InfoGUI::MouseKillFocus);
			this->Info_TB->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &InfoGUI::MouseKillFocus);
			// 
			// Version_LBL
			// 
			this->Version_LBL->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->Version_LBL->AutoSize = true;
			this->Version_LBL->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Version_LBL->Location = System::Drawing::Point(12, 114);
			this->Version_LBL->Name = L"Version_LBL";
			this->Version_LBL->Size = System::Drawing::Size(77, 16);
			this->Version_LBL->TabIndex = 1;
			this->Version_LBL->Text = L"Version: 1.0";
			// 
			// GithubRepo_LLBL
			// 
			this->GithubRepo_LLBL->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->GithubRepo_LLBL->AutoSize = true;
			this->GithubRepo_LLBL->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->GithubRepo_LLBL->Location = System::Drawing::Point(249, 114);
			this->GithubRepo_LLBL->Name = L"GithubRepo_LLBL";
			this->GithubRepo_LLBL->Size = System::Drawing::Size(109, 16);
			this->GithubRepo_LLBL->TabIndex = 3;
			this->GithubRepo_LLBL->TabStop = true;
			this->GithubRepo_LLBL->Text = L"Github repository";
			this->GithubRepo_LLBL->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &InfoGUI::GithubRepo_LLBL_LinkClicked);
			// 
			// Author_LLBL
			// 
			this->Author_LLBL->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->Author_LLBL->AutoSize = true;
			this->Author_LLBL->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Author_LLBL->LinkArea = System::Windows::Forms::LinkArea(11, 17);
			this->Author_LLBL->Location = System::Drawing::Point(12, 94);
			this->Author_LLBL->Name = L"Author_LLBL";
			this->Author_LLBL->Size = System::Drawing::Size(186, 20);
			this->Author_LLBL->TabIndex = 4;
			this->Author_LLBL->TabStop = true;
			this->Author_LLBL->Text = L"Created by Questionable Mark";
			this->Author_LLBL->UseCompatibleTextRendering = true;
			this->Author_LLBL->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &InfoGUI::Author_LLBL_LinkClicked);
			// 
			// Assimp_LLBL
			// 
			this->Assimp_LLBL->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->Assimp_LLBL->AutoSize = true;
			this->Assimp_LLBL->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Assimp_LLBL->LinkArea = System::Windows::Forms::LinkArea(19, 6);
			this->Assimp_LLBL->Location = System::Drawing::Point(12, 72);
			this->Assimp_LLBL->Margin = System::Windows::Forms::Padding(3, 0, 3, 2);
			this->Assimp_LLBL->Name = L"Assimp_LLBL";
			this->Assimp_LLBL->Size = System::Drawing::Size(153, 20);
			this->Assimp_LLBL->TabIndex = 5;
			this->Assimp_LLBL->TabStop = true;
			this->Assimp_LLBL->Text = L"Object loader lib: Assimp";
			this->Assimp_LLBL->UseCompatibleTextRendering = true;
			this->Assimp_LLBL->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &InfoGUI::Assimp_LLBL_LinkClicked);
			// 
			// InfoGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(370, 139);
			this->Controls->Add(this->Assimp_LLBL);
			this->Controls->Add(this->Author_LLBL);
			this->Controls->Add(this->GithubRepo_LLBL);
			this->Controls->Add(this->Version_LBL);
			this->Controls->Add(this->Info_TB);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"InfoGUI";
			this->ShowIcon = false;
			this->Text = L"Info";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		System::Void Author_LLBL_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e);
		System::Void GithubRepo_LLBL_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e);
		System::Void Assimp_LLBL_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e);
		System::Void MouseKillFocus(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	};
}
