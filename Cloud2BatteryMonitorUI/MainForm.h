#pragma once

#include <iostream>
#include <hidapi.h>
#include <stdlib.h>
#include "SettingsForm.h"

constexpr auto HEADSET_VENDOR_ID_KINGSTON = 2385;
constexpr auto HEADSET_VENDOR_ID_HP = 1008;

constexpr auto HEADSET_PRODUCT_ID_KINGSTON_CLOUD_II = 5912;
constexpr auto HEADSET_PRODUCT_ID_HP_CLOUD_II = 395;
constexpr auto HEADSET_PRODUCT_ID_HP_CLOUD_II_B = 1686;
constexpr auto HEADSET_PRODUCT_ID_HP_CLOUD_II_CORE = 2453;
constexpr auto HEADSET_PRODUCT_ID_HP_CLOUD_ALPHA = 2445;
constexpr auto HEADSET_PRODUCT_ID_HP_CLOUD_STINGER_II = 3475;
constexpr auto HEADSET_PRODUCT_ID_HP_CLOUD_III_S = 1726;
constexpr auto HEADSET_PRODUCT_ID_HP_CLOUD_III_REV4106 = 3229;
constexpr auto HEADSET_PRODUCT_ID_HP_CLOUD_III_REV4109 = 1463;

const int VENDORS_ARRAY[] = { HEADSET_VENDOR_ID_KINGSTON, HEADSET_VENDOR_ID_HP, HEADSET_VENDOR_ID_HP, HEADSET_VENDOR_ID_HP, HEADSET_VENDOR_ID_HP, HEADSET_VENDOR_ID_HP, HEADSET_VENDOR_ID_HP, HEADSET_VENDOR_ID_HP, HEADSET_VENDOR_ID_HP};
const int PRODUCTS_ARRAY[] = { HEADSET_PRODUCT_ID_KINGSTON_CLOUD_II, HEADSET_PRODUCT_ID_HP_CLOUD_II, HEADSET_PRODUCT_ID_HP_CLOUD_II_CORE, HEADSET_PRODUCT_ID_HP_CLOUD_ALPHA, HEADSET_PRODUCT_ID_HP_CLOUD_II_B, HEADSET_PRODUCT_ID_HP_CLOUD_STINGER_II, HEADSET_PRODUCT_ID_HP_CLOUD_III_S, HEADSET_PRODUCT_ID_HP_CLOUD_III_REV4106, HEADSET_PRODUCT_ID_HP_CLOUD_III_REV4109};

std::string getHeadsetDevicePath(); 
int getBatteryLevel(hid_device*);


namespace Cloud2BatteryMonitorUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		System::Windows::Forms::Timer^ timerRefresh = gcnew System::Windows::Forms::Timer();
		bool lowBatteryPopupShown = false;

		//a variable to hold offline icon permanently
		System::Drawing::Icon^ defaultOfflineIcon;

		//holds the currently generated tray icon so it can be disposed safely on refresh
		System::Drawing::Icon^ currentTrayGeneratedIcon = nullptr;

		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			
			//load the offline icon exactly once into memory
			defaultOfflineIcon = System::Drawing::Icon::ExtractAssociatedIcon("icons\\headset_icon_light.ico");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}

			//dispose of the current generated tray icon if it exists
			if (currentTrayGeneratedIcon != nullptr)
			{
				delete currentTrayGeneratedIcon;
				currentTrayGeneratedIcon = nullptr;
			}

			//dispose of the cached offline icon when the app closes
			delete defaultOfflineIcon;
		}
	
	//for cleaning the icon leak
	private:
			[System::Runtime::InteropServices::DllImportAttribute("user32.dll")]
			static bool DestroyIcon(System::IntPtr handle);

	private: System::Windows::Forms::Label^ lbStatus;
	protected:
	private: System::Windows::Forms::Label^ lbHeadsetInfoManu;
	private: System::Windows::Forms::Label^ lbBatteryLevel;
	private: System::Windows::Forms::Label^ lbHeadsetInfoProd;
	private: System::Windows::Forms::NotifyIcon^ iconSystemTray;
	private: System::Windows::Forms::Button^ btnRefresh;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuNotifyIcon;



	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ menuTitleFile;
	private: System::Windows::Forms::ToolStripMenuItem^ itemFileRefresh;
	private: System::Windows::Forms::ToolStripMenuItem^ itemFileHide;
	private: System::Windows::Forms::ToolStripSeparator^ separatorFile;
	private: System::Windows::Forms::ToolStripMenuItem^ itemFileExit;
	private: System::Windows::Forms::ToolStripMenuItem^ menuTitleOptions;
	private: System::Windows::Forms::ToolStripMenuItem^ itemOptionsSettings;
	private: System::Windows::Forms::ToolStripSeparator^ separatorOptions;
	private: System::Windows::Forms::ToolStripMenuItem^ itemOptionsBatIcon;
	private: System::Windows::Forms::ToolStripMenuItem^ itemOptionsAutostart;
	private: System::Windows::Forms::ToolStripMenuItem^ menuTitleHelp;
	private: System::Windows::Forms::ToolStripMenuItem^ itemHelpProjectPage;
	private: System::Windows::Forms::ToolStripMenuItem^ itemHelpReportIssue;
	private: System::Windows::Forms::ToolStripSeparator^ separatorHelp;
	private: System::Windows::Forms::ToolStripMenuItem^ itemHelpAbout;
	private: System::Windows::Forms::ToolStripMenuItem^ itemTrayStatus;
	private: System::Windows::Forms::ToolStripSeparator^ separatorTrayStatus;
	private: System::Windows::Forms::ToolStripMenuItem^ itemOpen;
	private: System::Windows::Forms::ToolStripMenuItem^ itemSettings;
	private: System::Windows::Forms::ToolStripMenuItem^ itemRefresh;
	private: System::Windows::Forms::ToolStripSeparator^ separatorTrayToggles;
	private: System::Windows::Forms::ToolStripMenuItem^ itemTrayBatIcon;
	private: System::Windows::Forms::ToolStripMenuItem^ itemTrayAutostart;
	private: System::Windows::Forms::ToolStripSeparator^ separatorTrayExit;
	private: System::Windows::Forms::ToolStripMenuItem^ itemExit;











	private: System::ComponentModel::IContainer^ components;
	protected:
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->lbStatus = (gcnew System::Windows::Forms::Label());
			this->lbHeadsetInfoManu = (gcnew System::Windows::Forms::Label());
			this->lbBatteryLevel = (gcnew System::Windows::Forms::Label());
			this->lbHeadsetInfoProd = (gcnew System::Windows::Forms::Label());
			this->iconSystemTray = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->contextMenuNotifyIcon = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->btnRefresh = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->menuTitleFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->itemFileRefresh = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->itemFileHide = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->separatorFile = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->itemFileExit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuTitleOptions = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->itemOptionsSettings = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->separatorOptions = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->itemOptionsBatIcon = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->itemOptionsAutostart = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuTitleHelp = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->itemHelpProjectPage = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->itemHelpReportIssue = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->separatorHelp = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->itemHelpAbout = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->itemTrayStatus = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->separatorTrayStatus = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->itemRefresh = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->itemSettings = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->itemOpen = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->separatorTrayToggles = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->itemTrayBatIcon = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->itemTrayAutostart = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->separatorTrayExit = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->itemExit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextMenuNotifyIcon->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// lbStatus
			// 
			this->lbStatus->AutoSize = true;
			this->lbStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbStatus->Location = System::Drawing::Point(12, 32);
			this->lbStatus->Name = L"lbStatus";
			this->lbStatus->Size = System::Drawing::Size(146, 18);
			this->lbStatus->TabIndex = 0;
			this->lbStatus->Text = L"No headset found.";
			// 
			// lbHeadsetInfoManu
			// 
			this->lbHeadsetInfoManu->AutoSize = true;
			this->lbHeadsetInfoManu->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lbHeadsetInfoManu->Location = System::Drawing::Point(12, 59);
			this->lbHeadsetInfoManu->Name = L"lbHeadsetInfoManu";
			this->lbHeadsetInfoManu->Size = System::Drawing::Size(91, 18);
			this->lbHeadsetInfoManu->TabIndex = 4;
			this->lbHeadsetInfoManu->Text = L"Headset info";
			this->lbHeadsetInfoManu->Visible = false;
			// 
			// lbBatteryLevel
			// 
			this->lbBatteryLevel->AutoSize = true;
			this->lbBatteryLevel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbBatteryLevel->Location = System::Drawing::Point(12, 104);
			this->lbBatteryLevel->Name = L"lbBatteryLevel";
			this->lbBatteryLevel->Size = System::Drawing::Size(91, 18);
			this->lbBatteryLevel->TabIndex = 5;
			this->lbBatteryLevel->Text = L"Battery level:";
			this->lbBatteryLevel->Visible = false;
			// 
			// lbHeadsetInfoProd
			// 
			this->lbHeadsetInfoProd->AutoSize = true;
			this->lbHeadsetInfoProd->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lbHeadsetInfoProd->Location = System::Drawing::Point(12, 77);
			this->lbHeadsetInfoProd->Name = L"lbHeadsetInfoProd";
			this->lbHeadsetInfoProd->Size = System::Drawing::Size(91, 18);
			this->lbHeadsetInfoProd->TabIndex = 7;
			this->lbHeadsetInfoProd->Text = L"Headset info";
			this->lbHeadsetInfoProd->Visible = false;
			// 
			// iconSystemTray
			// 
			this->iconSystemTray->ContextMenuStrip = this->contextMenuNotifyIcon;
			this->iconSystemTray->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"iconSystemTray.Icon")));
			this->iconSystemTray->Text = L"Battery monitor";
			this->iconSystemTray->Visible = true;
			this->iconSystemTray->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::TrayIcon_DoubleClick);
			// 
			// contextMenuNotifyIcon
			// 
			this->contextMenuNotifyIcon->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(10) {
				this->itemTrayStatus,
					this->separatorTrayStatus, this->itemOpen, this->itemRefresh, this->itemSettings, this->separatorTrayToggles, this->itemTrayBatIcon,
					this->itemTrayAutostart, this->separatorTrayExit, this->itemExit
			});
			this->contextMenuNotifyIcon->Name = L"contextMenuStrip1";
			this->contextMenuNotifyIcon->ShowCheckMargin = true;
			this->contextMenuNotifyIcon->ShowImageMargin = false;
			this->contextMenuNotifyIcon->Size = System::Drawing::Size(200, 198);
			this->contextMenuNotifyIcon->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::ContextMenuNotifyIcon_Opening);
			// 
			// btnRefresh
			// 
			this->btnRefresh->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnRefresh->BackColor = System::Drawing::Color::DarkGray;
			this->btnRefresh->FlatAppearance->BorderColor = System::Drawing::Color::DimGray;
			this->btnRefresh->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnRefresh->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRefresh->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnRefresh.Image")));
			this->btnRefresh->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btnRefresh->Location = System::Drawing::Point(258, 29);
			this->btnRefresh->Name = L"btnRefresh";
			this->btnRefresh->Size = System::Drawing::Size(83, 27);
			this->btnRefresh->TabIndex = 8;
			this->btnRefresh->Text = L"Refresh";
			this->btnRefresh->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btnRefresh->UseVisualStyleBackColor = false;
			this->btnRefresh->Click += gcnew System::EventHandler(this, &MainForm::BtnRefresh_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->menuTitleFile,
					this->menuTitleOptions, this->menuTitleHelp
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(353, 24);
			this->menuStrip1->TabIndex = 9;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// menuTitleFile
			// 
			this->menuTitleFile->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->itemFileRefresh,
					this->itemFileHide, this->separatorFile, this->itemFileExit
			});
			this->menuTitleFile->Name = L"menuTitleFile";
			this->menuTitleFile->Size = System::Drawing::Size(37, 20);
			this->menuTitleFile->Text = L"&File";
			// 
			// itemFileRefresh
			// 
			this->itemFileRefresh->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnRefresh.Image")));
			this->itemFileRefresh->Name = L"itemFileRefresh";
			this->itemFileRefresh->ShortcutKeys = System::Windows::Forms::Keys::F5;
			this->itemFileRefresh->Size = System::Drawing::Size(180, 22);
			this->itemFileRefresh->Text = L"&Refresh";
			this->itemFileRefresh->Click += gcnew System::EventHandler(this, &MainForm::BtnRefresh_Click);
			// 
			// itemFileHide
			// 
			this->itemFileHide->Name = L"itemFileHide";
			this->itemFileHide->Size = System::Drawing::Size(180, 22);
			this->itemFileHide->Text = L"&Hide to tray";
			this->itemFileHide->Click += gcnew System::EventHandler(this, &MainForm::ItemHide_Click);
			// 
			// separatorFile
			// 
			this->separatorFile->Name = L"separatorFile";
			this->separatorFile->Size = System::Drawing::Size(177, 6);
			// 
			// itemFileExit
			// 
			this->itemFileExit->Name = L"itemFileExit";
			this->itemFileExit->Size = System::Drawing::Size(180, 22);
			this->itemFileExit->Text = L"E&xit";
			this->itemFileExit->Click += gcnew System::EventHandler(this, &MainForm::ItemExit_Click);
			// 
			// menuTitleOptions
			// 
			this->menuTitleOptions->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->itemOptionsSettings,
					this->separatorOptions, this->itemOptionsBatIcon, this->itemOptionsAutostart
			});
			this->menuTitleOptions->Name = L"menuTitleOptions";
			this->menuTitleOptions->Size = System::Drawing::Size(61, 20);
			this->menuTitleOptions->Text = L"&Options";
			this->menuTitleOptions->DropDownOpening += gcnew System::EventHandler(this, &MainForm::MenuTitleOptions_DropDownOpening);
			// 
			// itemOptionsSettings
			// 
			this->itemOptionsSettings->Name = L"itemOptionsSettings";
			this->itemOptionsSettings->ShortcutKeyDisplayString = L"Ctrl+,";
			this->itemOptionsSettings->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Oemcomma));
			this->itemOptionsSettings->Size = System::Drawing::Size(200, 22);
			this->itemOptionsSettings->Text = L"&Settings...";
			this->itemOptionsSettings->Click += gcnew System::EventHandler(this, &MainForm::Settings_Click);
			// 
			// separatorOptions
			// 
			this->separatorOptions->Name = L"separatorOptions";
			this->separatorOptions->Size = System::Drawing::Size(197, 6);
			// 
			// itemOptionsBatIcon
			// 
			this->itemOptionsBatIcon->Name = L"itemOptionsBatIcon";
			this->itemOptionsBatIcon->Size = System::Drawing::Size(200, 22);
			this->itemOptionsBatIcon->Text = L"Use &battery tray icon";
			this->itemOptionsBatIcon->Click += gcnew System::EventHandler(this, &MainForm::ItemBatIcon_Click);
			// 
			// itemOptionsAutostart
			// 
			this->itemOptionsAutostart->Name = L"itemOptionsAutostart";
			this->itemOptionsAutostart->Size = System::Drawing::Size(200, 22);
			this->itemOptionsAutostart->Text = L"Start with &Windows";
			this->itemOptionsAutostart->Click += gcnew System::EventHandler(this, &MainForm::ItemAutostart_Click);
			// 
			// menuTitleHelp
			// 
			this->menuTitleHelp->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->itemHelpProjectPage,
					this->itemHelpReportIssue, this->separatorHelp, this->itemHelpAbout
			});
			this->menuTitleHelp->Name = L"menuTitleHelp";
			this->menuTitleHelp->Size = System::Drawing::Size(44, 20);
			this->menuTitleHelp->Text = L"&Help";
			// 
			// itemHelpProjectPage
			// 
			this->itemHelpProjectPage->Name = L"itemHelpProjectPage";
			this->itemHelpProjectPage->Size = System::Drawing::Size(200, 22);
			this->itemHelpProjectPage->Text = L"Project page on &GitHub";
			this->itemHelpProjectPage->Click += gcnew System::EventHandler(this, &MainForm::ItemHelpProjectPage_Click);
			// 
			// itemHelpReportIssue
			// 
			this->itemHelpReportIssue->Name = L"itemHelpReportIssue";
			this->itemHelpReportIssue->Size = System::Drawing::Size(200, 22);
			this->itemHelpReportIssue->Text = L"&Report an issue";
			this->itemHelpReportIssue->Click += gcnew System::EventHandler(this, &MainForm::ItemHelpReportIssue_Click);
			// 
			// separatorHelp
			// 
			this->separatorHelp->Name = L"separatorHelp";
			this->separatorHelp->Size = System::Drawing::Size(197, 6);
			// 
			// itemHelpAbout
			// 
			this->itemHelpAbout->Name = L"itemHelpAbout";
			this->itemHelpAbout->Size = System::Drawing::Size(200, 22);
			this->itemHelpAbout->Text = L"&About...";
			this->itemHelpAbout->Click += gcnew System::EventHandler(this, &MainForm::ItemHelpAbout_Click);
			// 
			// itemTrayStatus
			// 
			this->itemTrayStatus->Enabled = false;
			this->itemTrayStatus->Name = L"itemTrayStatus";
			this->itemTrayStatus->Size = System::Drawing::Size(199, 22);
			this->itemTrayStatus->Text = L"No headset detected";
			// 
			// separatorTrayStatus
			// 
			this->separatorTrayStatus->Name = L"separatorTrayStatus";
			this->separatorTrayStatus->Size = System::Drawing::Size(196, 6);
			// 
			// itemRefresh
			// 
			this->itemRefresh->Name = L"itemRefresh";
			this->itemRefresh->Size = System::Drawing::Size(199, 22);
			this->itemRefresh->Text = L"&Refresh now";
			this->itemRefresh->Click += gcnew System::EventHandler(this, &MainForm::BtnRefresh_Click);
			// 
			// itemSettings
			// 
			this->itemSettings->Name = L"itemSettings";
			this->itemSettings->Size = System::Drawing::Size(199, 22);
			this->itemSettings->Text = L"&Settings...";
			this->itemSettings->Click += gcnew System::EventHandler(this, &MainForm::Settings_Click);
			// 
			// itemOpen
			// 
			this->itemOpen->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.0F, System::Drawing::FontStyle::Bold));
			this->itemOpen->Name = L"itemOpen";
			this->itemOpen->Size = System::Drawing::Size(199, 22);
			this->itemOpen->Text = L"&Open";
			this->itemOpen->Click += gcnew System::EventHandler(this, &MainForm::ItemOpen_Click);
			// 
			// separatorTrayToggles
			// 
			this->separatorTrayToggles->Name = L"separatorTrayToggles";
			this->separatorTrayToggles->Size = System::Drawing::Size(196, 6);
			// 
			// itemTrayBatIcon
			// 
			this->itemTrayBatIcon->Name = L"itemTrayBatIcon";
			this->itemTrayBatIcon->Size = System::Drawing::Size(199, 22);
			this->itemTrayBatIcon->Text = L"Use &battery tray icon";
			this->itemTrayBatIcon->Click += gcnew System::EventHandler(this, &MainForm::ItemBatIcon_Click);
			// 
			// itemTrayAutostart
			// 
			this->itemTrayAutostart->Name = L"itemTrayAutostart";
			this->itemTrayAutostart->Size = System::Drawing::Size(199, 22);
			this->itemTrayAutostart->Text = L"Start with &Windows";
			this->itemTrayAutostart->Click += gcnew System::EventHandler(this, &MainForm::ItemAutostart_Click);
			// 
			// separatorTrayExit
			// 
			this->separatorTrayExit->Name = L"separatorTrayExit";
			this->separatorTrayExit->Size = System::Drawing::Size(196, 6);
			// 
			// itemExit
			// 
			this->itemExit->Name = L"itemExit";
			this->itemExit->Size = System::Drawing::Size(199, 22);
			this->itemExit->Text = L"E&xit";
			this->itemExit->Click += gcnew System::EventHandler(this, &MainForm::ItemExit_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Silver;
			this->ClientSize = System::Drawing::Size(353, 137);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->btnRefresh);
			this->Controls->Add(this->lbHeadsetInfoProd);
			this->Controls->Add(this->lbBatteryLevel);
			this->Controls->Add(this->lbHeadsetInfoManu);
			this->Controls->Add(this->lbStatus);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(369, 176);
			this->MinimumSize = System::Drawing::Size(369, 176);
			this->Name = L"MainForm";
			this->Text = L"HyperX Cloud II Battery Monitor";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->Shown += gcnew System::EventHandler(this, &MainForm::Form_Shown);
			this->Resize += gcnew System::EventHandler(this, &MainForm::MainForm_Resize);
			this->contextMenuNotifyIcon->ResumeLayout(false);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

#define NO_DEVICE_STRING "No headset device detected."
#define BATTERY_LEVEL_STRING "Battery level: "
#define FONT "Tahoma"
#define PROJECT_URL "https://github.com/auto94/HyperX-Cloud-2-Battery-Monitor"

	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) 
	{
		//gets the path as a string instead of hid_device_info* which caused memory leak every cycle
		std::string devicePath = getHeadsetDevicePath();

		if (!devicePath.empty())
		{
			hid_device* headsetDevice = hid_open_path(devicePath.c_str());

			if (headsetDevice != NULL) 
			{
				int batteryLevel = getBatteryLevel(headsetDevice);
				SettingsHelper* settingsHelper = new SettingsHelper();

				if (settingsHelper->getLowBatteryPopupEnabled() &&
					batteryLevel > 0 &&
					batteryLevel <= settingsHelper->getLowBatteryPopupLevel())
				{
					if (!lowBatteryPopupShown)
					{
						this->iconSystemTray->BalloonTipTitle = "Battery monitor";
						this->iconSystemTray->BalloonTipText = "Battery level low: " + batteryLevel + "%";
						this->iconSystemTray->ShowBalloonTip(5000);
						lowBatteryPopupShown = true;
					}
				}
				else
				{
					lowBatteryPopupShown = false;
				}

				// If the app is minized, only refresh the icon.
				if (this->WindowState != FormWindowState::Minimized) 
				{
					wchar_t manufacturer[20];
					hid_get_manufacturer_string(headsetDevice, manufacturer, 20);
					wchar_t productName[50];
					hid_get_product_string(headsetDevice, productName, 50);

					const wchar_t* const pManuStr = manufacturer;
					System::String^ const strManu = gcnew System::String(pManuStr);
					this->lbHeadsetInfoManu->Visible = true;
					this->lbHeadsetInfoManu->Text = strManu;

					const wchar_t* const pProdStr = productName;
					System::String^ const strProd = gcnew System::String(pProdStr);
					this->lbHeadsetInfoProd->Visible = true;
					this->lbHeadsetInfoProd->Text = strProd;

					// If battery level returned is 0 => headset is turned off but USB is in PC.
					if (batteryLevel == 0) {
						this->lbStatus->Text = "Headset found but not active.";
						this->lbBatteryLevel->Visible = false;
					}
					else {
						this->btnRefresh->Visible = false;
						this->lbStatus->Text = "Headset found.";
						this->lbBatteryLevel->Visible = true;
						this->lbBatteryLevel->Text = "Battery level: " + batteryLevel + " %";
					}
				}

				wchar_t productName[50];
				hid_get_product_string(headsetDevice, productName, 50);

				System::String^ batStr2 = gcnew System::String(to_string(batteryLevel).c_str());
				System::String^ prodStr = gcnew System::String(productName);
				RefreshTrayIcon(batStr2, prodStr);

				if (batteryLevel == 0)
				{
					this->itemTrayStatus->Text = prodStr + ": not active";
				}
				else
				{
					this->itemTrayStatus->Text = prodStr + ": " + batteryLevel + "%";
				}
				delete settingsHelper;
				//close the connection only if it was opened.
				hid_close(headsetDevice);

			}
			else 
			{
				this->iconSystemTray->Text = NO_DEVICE_STRING;
				//use loaded offline icon
				this->iconSystemTray->Icon = defaultOfflineIcon;
				this->lbStatus->Text = "Could not connect to headset.";
				this->itemTrayStatus->Text = "Could not connect to headset";
				this->btnRefresh->Visible = true;
				lowBatteryPopupShown = false;
			}
		}
		else 
		{
			this->iconSystemTray->Text = NO_DEVICE_STRING;
			//use loaded offline icon
			this->iconSystemTray->Icon = defaultOfflineIcon;
			this->lbStatus->Text = "No headset device detected.";
			this->itemTrayStatus->Text = "No headset detected";
			this->btnRefresh->Visible = true;
			lowBatteryPopupShown = false;
		}

		if (timerRefresh->Enabled == false) 
		{
			// Prep and start the refresh timer.
			setupTimer();

			MainForm::FormClosing += gcnew FormClosingEventHandler(this, &MainForm::MainForm_Closing);
		}
	}

	private: System::Void Form_Shown(System::Object^ sender, System::EventArgs^ e)
	{
		System::Array^ args = Environment::GetCommandLineArgs();
		if (args->Length > 1) 
		{
			// For application silent start (auto start)
			if (String::Equals(args->GetValue(1), "-hidden")) 
			{
				this->WindowState = FormWindowState::Minimized;
				this->Hide();
			}
		}
	}

	private: System::Void TrayIcon_DoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) 
	{
		// Opens the application
		RestoreFromTray();
		this->MainForm_Load(sender, e);
	}

	private: void RestoreFromTray()
	{
		// The form has a fixed size, so restore it to normal (not maximized) and bring it to the front.
		Show();
		this->WindowState = System::Windows::Forms::FormWindowState::Normal;
		Activate();
	}

	private: System::Void MainForm_Closing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
	{
		// Remove the system tray icon (otherwise it remaing visible until mouse hover over).
		this->iconSystemTray->Visible = false;
	}

	private: System::Void MainForm_Resize(System::Object^ sender, System::EventArgs^ e)
	{
		// When minimized, hide app from taskbar.
		if (this->WindowState == System::Windows::Forms::FormWindowState::Minimized) {
			Hide();
		}
	}

	private: System::Void RefreshTrayIcon(System::String^ batteryLevel, System::String^ productName)
	{
		int battLvl = System::Int32::Parse(batteryLevel);
		String^ trayText = productName + "\n";
		SettingsHelper* settingsHelper = new SettingsHelper();

		if (battLvl > 0 && battLvl <= 100)
		{
			//a place to store the unmanaged handle
			System::IntPtr hIcon;

			if (settingsHelper->getBatIcon())
			{
				//catch the handle from the Battery icon generator
				hIcon = RefreshTrayBattery(battLvl, settingsHelper);
			}
			else
			{
				//catch the handle from the Number icon generator
				hIcon = RefreshTrayNumber(batteryLevel, settingsHelper);
			}

			//dispose of the previous generated tray icon before creating a new one
			if (currentTrayGeneratedIcon != nullptr)
			{
				delete currentTrayGeneratedIcon;
				currentTrayGeneratedIcon = nullptr;
			}

			//create a temporary wrapper from the unmanaged handle,
			//clone it so the tray owns a safe managed copy,
			//then destroy the original unmanaged handle
			System::Drawing::Icon^ tempIcon = System::Drawing::Icon::FromHandle(hIcon);
			currentTrayGeneratedIcon = safe_cast<System::Drawing::Icon^>(tempIcon->Clone());

			this->iconSystemTray->Icon = currentTrayGeneratedIcon;

			delete tempIcon;
			DestroyIcon(hIcon);

			trayText += BATTERY_LEVEL_STRING + batteryLevel + "%";
			this->iconSystemTray->Text = trayText;
		}
		else
		{
			trayText += BATTERY_LEVEL_STRING + "N/A";

			//dispose of the previous generated tray icon when switching to offline icon
			if (currentTrayGeneratedIcon != nullptr)
			{
				delete currentTrayGeneratedIcon;
				currentTrayGeneratedIcon = nullptr;
			}

			//use loaded offline icon
			this->iconSystemTray->Icon = defaultOfflineIcon;
			this->iconSystemTray->Text = trayText;
		}

		delete settingsHelper;
	}

	private: System::IntPtr RefreshTrayNumber(System::String^ batteryLevel, SettingsHelper* settingsHelper)
	{
		int battLvl = System::Int32::Parse(batteryLevel);
		System::Drawing::Font^ iconFont;
		if (battLvl == 100) 
		{
			iconFont = gcnew System::Drawing::Font(FONT, 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel);
		}
		else if (battLvl < 10) 
		{
			iconFont = gcnew System::Drawing::Font(FONT, 13, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel);
		}
		else 
		{
			iconFont = gcnew System::Drawing::Font(FONT, 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel);
		}

		System::Drawing::Brush^ iconBrush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::White);
		System::Drawing::Bitmap^ textBitmap = gcnew System::Drawing::Bitmap(16, 16);
		System::Drawing::Graphics^ iconGraphics;
		iconGraphics = iconGraphics->FromImage(textBitmap);

		if (battLvl > 49) 
		{
			iconBrush = gcnew System::Drawing::SolidBrush(settingsHelper->getColorHighText());
			iconGraphics->Clear(settingsHelper->getColorHigh());
		}
		else if (battLvl > 19) 
		{
			iconBrush = gcnew System::Drawing::SolidBrush(settingsHelper->getColorMedText());
			iconGraphics->Clear(settingsHelper->getColorMed());
		}
		else 
		{
			iconBrush = gcnew System::Drawing::SolidBrush(settingsHelper->getColorLowText());
			iconGraphics->Clear(settingsHelper->getColorLow());
		}

		System::Drawing::SizeF strSize = iconGraphics->MeasureString(batteryLevel, iconFont);

		iconGraphics->TextRenderingHint = System::Drawing::Text::TextRenderingHint::SingleBitPerPixelGridFit;
		iconGraphics->DrawString(batteryLevel, iconFont, iconBrush, (17 - strSize.Width) / 2, (17 - strSize.Height) / 2);

		delete iconBrush;
		delete iconFont;
		delete iconGraphics;

		System::IntPtr hIcon = textBitmap->GetHicon(); // Extract the handle first
		delete textBitmap; //dispose of the managed bitmap

		return hIcon; //return the extracted handle
	}

	private: System::IntPtr RefreshTrayBattery(int battLvl, SettingsHelper* settingsHelper)
	{
		// For icon fill height, round the battery level to the nearest 10, then divide it by 10. One is added later as that is the minimum.
		int fillHeight = ((battLvl / 10) * 10) / 10;

		System::Drawing::Brush^ batFillBrush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::White);
		System::Drawing::Brush^ batOutlineBrush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Blue);

		if (battLvl > 49)
		{
			batOutlineBrush = gcnew System::Drawing::SolidBrush(settingsHelper->getColorHighText());
			batFillBrush = gcnew System::Drawing::SolidBrush(settingsHelper->getColorHigh());
		}
		else if (battLvl > 19)
		{
			batOutlineBrush = gcnew System::Drawing::SolidBrush(settingsHelper->getColorMedText());
			batFillBrush = gcnew System::Drawing::SolidBrush(settingsHelper->getColorMed());
		}
		else
		{
			batOutlineBrush = gcnew System::Drawing::SolidBrush(settingsHelper->getColorLowText());
			batFillBrush = gcnew System::Drawing::SolidBrush(settingsHelper->getColorLow());
		}

		System::Drawing::Bitmap^ batBitmap = gcnew System::Drawing::Bitmap(16, 16);
		System::Drawing::Graphics^ batGraphics = System::Drawing::Graphics::FromImage(batBitmap);

		// Draw outline of battery
		System::Drawing::Pen^ batPen = gcnew System::Drawing::Pen(batOutlineBrush);
		batGraphics->DrawRectangle(batPen, 2, 3, 11, 12);
		batGraphics->FillRectangle(batOutlineBrush, 6, 0, 4, 2);

		// Fill in the level
		batGraphics->FillRectangle(batFillBrush, 3, 14 - fillHeight, 10, fillHeight + 1);

		delete batFillBrush;
		delete batOutlineBrush;
		delete batGraphics;
		delete batPen;
		
		System::IntPtr hIcon = batBitmap->GetHicon(); // Extract the handle first
		delete batBitmap; // Dispose of the managed bitmap

		return hIcon; // Return the extracted handle
	}

	private: System::Void BtnRefresh_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		//Refresh UI/Search for headset
		MainForm_Load(sender, e);
	}

	private: System::Void ItemExit_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		this->iconSystemTray->Visible = false;
		System::Environment::Exit(1);
	}

	private: System::Void ItemOpen_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		RestoreFromTray();
		this->MainForm_Load(sender, e);
	}

	private: System::Void ItemHide_Click(System::Object^ sender, System::EventArgs^ e)
	{
		// MainForm_Resize hides the window once it is minimized.
		this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
	}

	private: System::Void ContextMenuNotifyIcon_Opening(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
	{
		SyncToggleItems();
	}

	private: System::Void MenuTitleOptions_DropDownOpening(System::Object^ sender, System::EventArgs^ e)
	{
		SyncToggleItems();
	}

	private: void SyncToggleItems()
	{
		// Settings can change from the settings form too, so read them each time a menu opens.
		SettingsHelper* settingsHelper = new SettingsHelper();
		bool batIcon = settingsHelper->getBatIcon();
		bool autostart = settingsHelper->getAutostart();
		delete settingsHelper;

		this->itemOptionsBatIcon->Checked = batIcon;
		this->itemTrayBatIcon->Checked = batIcon;
		this->itemOptionsAutostart->Checked = autostart;
		this->itemTrayAutostart->Checked = autostart;
	}

	private: System::Void ItemBatIcon_Click(System::Object^ sender, System::EventArgs^ e)
	{
		SettingsHelper* settingsHelper = new SettingsHelper();
		settingsHelper->setBatIcon(!settingsHelper->getBatIcon());
		settingsHelper->saveSettings();
		delete settingsHelper;

		// Redraw the tray icon in the new style.
		MainForm_Load(sender, e);
	}

	private: System::Void ItemAutostart_Click(System::Object^ sender, System::EventArgs^ e)
	{
		// saveSettings() adds or removes the registry autostart entry.
		SettingsHelper* settingsHelper = new SettingsHelper();
		settingsHelper->setAutostart(!settingsHelper->getAutostart());
		settingsHelper->saveSettings();
		delete settingsHelper;
	}

	private: System::Void Settings_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		SettingsForm^ SettingsForm1 = gcnew SettingsForm();
		System::Windows::Forms::DialogResult result = SettingsForm1->ShowDialog();
		delete SettingsForm1; 
		if (result == System::Windows::Forms::DialogResult::OK) 
		{
			MainForm_Load(gcnew System::Object(), gcnew System::EventArgs());
			setupTimer();
		}
	}

	private: System::Void ItemHelpProjectPage_Click(System::Object^ sender, System::EventArgs^ e)
	{
		OpenUrl(PROJECT_URL);
	}

	private: System::Void ItemHelpReportIssue_Click(System::Object^ sender, System::EventArgs^ e)
	{
		OpenUrl(PROJECT_URL "/issues/new/choose");
	}

	private: System::Void ItemHelpAbout_Click(System::Object^ sender, System::EventArgs^ e)
	{
		System::Windows::Forms::DialogResult result = MessageBox::Show(this,
			"HyperX Cloud Battery Monitor\n\n"
			"Shows the battery level of HyperX Cloud wireless headsets in the system tray.\n\n"
			"Released under the MIT license.\n\n"
			"Open the project page on GitHub?",
			"About", MessageBoxButtons::YesNo, MessageBoxIcon::Information);

		if (result == System::Windows::Forms::DialogResult::Yes)
		{
			OpenUrl(PROJECT_URL);
		}
	}

	private: void OpenUrl(System::String^ url)
	{
		// Opens the URL in the default browser without flashing a console window.
		try
		{
			System::Diagnostics::Process::Start(url);
		}
		catch (System::Exception^)
		{
			MessageBox::Show(url, "Could not open link", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}

	private: void setupTimer() 
	{
		SettingsHelper* settingsHelper = new SettingsHelper();
		if (timerRefresh->Enabled == true) 
		{
			timerRefresh->Stop();
		}
		else 
		{
			timerRefresh->Tick += gcnew EventHandler(this, &MainForm::MainForm_Load);
		}
		timerRefresh->Interval = (60 * 1000 * settingsHelper->getRefreshMinutes());
		timerRefresh->Start();

		delete settingsHelper;
	}
};
}
