// Copyright (C) 2003-2008 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/

#ifndef __CONFIGDIALOG_h__
#define __CONFIGDIALOG_h__

#include <iostream>
#include <vector>

#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/filepicker.h>
#include <wx/gbsizer.h>
#include <wx/progdlg.h>

class ConfigDialog : public wxDialog
{
	public:
		ConfigDialog(wxWindow *parent, wxWindowID id = 1,
			const wxString &title = wxT("Wii Remote Plugin Configuration"),
			const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
			long style = wxDEFAULT_DIALOG_STYLE | wxWANTS_CHARS);
		virtual ~ConfigDialog();

		// General open, close and event functions
		void CloseClick(wxCommandEvent& event);
		void UpdateGUI(int Slot = 0); void UpdateGUIButtonMapping(int controller); void UpdateControls();
		void OnKeyDown(wxKeyEvent& event);
		void LoadFile(); void SaveFile();
		
		// Timers
		wxTimer *m_TimeoutTimer, *m_ShutDownTimer, *m_TimeoutOnce, *m_ButtonMappingTimer, *m_UpdatePad;

		// General status
		wxStaticText * m_TextUpdateRate;
		
		// Wiimote status
		wxGauge *m_GaugeBattery, *m_GaugeRoll[2], *m_GaugeGForce[3], *m_GaugeAccel[3];
		wxStaticBitmap *m_bmpDotLeftIn[4], *m_bmpDotLeftOut[4], *m_bmpDotRightIn[4], *m_bmpDotRightOut[4],
			*m_bmpDeadZoneLeftIn[4], *m_bmpDeadZoneRightIn[4];
		wxStaticText *m_TextIR;
		bool m_bWaitForRecording, m_bRecording, m_bAllowA;
		int m_iRecordTo;
		void RecordMovement(wxCommandEvent& event);
		void DoRecordMovement(int _x, int _y, int _z, const u8 *_IR, int IRBytes);
		void DoRecordA(bool Pressed);
		void Convert2Box(int &x);
		void ConvertToString();
		void Update(wxTimerEvent& WXUNUSED(event));
		void ShutDown(wxTimerEvent& WXUNUSED(event));
		void UpdateOnce(wxTimerEvent& event);

		// Gamepad configuration
		void OnButtonTimer(wxTimerEvent& WXUNUSED(event)) { DoGetButtons(GetButtonWaitingID); }
		void UpdatePad(wxTimerEvent& WXUNUSED(event));

	private:
		DECLARE_EVENT_TABLE();

		bool ControlsCreated, m_bEnableUseRealWiimote; int Page, BoxW, BoxH, g_Pressed;

		wxNotebook *m_Notebook;
		wxPanel *m_Controller[4], *m_PageRecording;
		wxButton *m_About, *m_Close, *m_Apply;
		wxBoxSizer *m_MainSizer, *m_sMain[4], *m_SizeParent[4], *m_sRecordingMain;

		// Emulated Wiimote key settings		
		wxBoxSizer *m_SizerIRPointerWidth[4], *m_SizerIRPointerHeight[4], *m_SizerIRPointerScreen[4],
			*m_SizeBasicPadding[4], *m_SizeEmuPadding[4], *m_SizeRealPadding[4], *m_SizeExtensionsPadding[4],
			*m_SizeBasicGeneral[4], *m_SizeBasicGeneralLeft[4], *m_SizeBasicGeneralRight[4],
			*m_HorizControllers[4], *m_gC2SDeadZone[4], *m_gCircle2Square[4], *m_gCircle2SquareVert[4], *m_gDeadZone[4], *m_gDeadZoneHoriz[4], *m_HorizControllerTiltParent[4], *m_HorizControllerTilt[4], *m_TiltHoriz[4],
			*m_SizeAnalogLeft[4], *m_SizeAnalogLeftHorizX[4], *m_SizeAnalogLeftHorizY[4], *m_SizeAnalogRight[4], *m_SizeAnalogRightHorizX[4], *m_SizeAnalogRightHorizY[4],
			*m_SizeAnalogTriggerVertLeft[4], *m_SizeAnalogTriggerVertRight[4], *m_SizeAnalogTriggerHorizInput[4],
			// Nunchuck
			*m_SNcShake[4], *m_SNcZ[4], *m_SNcC[4], *m_SNcL[4], *m_SNcR[4], *m_SNcU[4], *m_SNcD[4],
			// Wiimote
			*m_SWmVertLeft[4], *m_SWmVertRight[4], *m_SWmShake[4], *m_SWmPitchL[4], *m_SWmPitchR[4], *m_SWmA[4], *m_SWmB[4], *m_SWm1[4], *m_SWm2[4], *m_SWmP[4], *m_SWmM[4], *m_SWmH[4], *m_SWmL[4], *m_SWmR[4], *m_SWmU[4], *m_SWmD[4],
			*m_HorizControllerMapping[4], *m_NunchuckStick[4],
			// Classic Controller
			*m_SCcVertLeft[4], *m_SCcVertMiddle[4], *m_SCcVertRight[4],
			*m_SCcLeftStick[4], *m_SCcRightStick[4], *m_SCcTriggers[4],
				*m_SCcA[4], *m_SCcB[4], *m_SCcX[4], *m_SCcY[4],
				*m_SCcP[4], *m_SCcM[4], *m_SCcH[4],
				*m_SCcTl[4], *m_SCcZl[4], *m_SCcZr[4], *m_SCcTr[4],
				*m_SCcDl[4], *m_SCcDu[4], *m_SCcDr[4], *m_SCcDd[4],
				*m_SCcLl[4], *m_SCcLu[4], *m_SCcLr[4], *m_SCcLd[4],
				*m_SCcRl[4], *m_SCcRu[4], *m_SCcRr[4], *m_SCcRd[4];
		wxGridBagSizer *m_SizeAnalogTriggerHorizConfig[4], *m_SizeAnalogTriggerStatusBox[4], *m_TiltGrid[4],
			*m_GridLeftStick[4], *m_GridRightStick[4];
		wxStaticBoxSizer *m_SizeBasic[4], *m_SizeEmu[4], *m_SizeReal[4], *m_SizeExtensions[4], *m_SizerIRPointer[4], *m_gTilt[4], *m_gJoyname[4];
		wxTextCtrl *m_AnalogLeftX[4], *m_AnalogLeftY[4], *m_AnalogRightX[4], *m_AnalogRightY[4],
			*m_AnalogTriggerL[4], *m_AnalogTriggerR[4];
		wxButton *m_bAnalogLeftX[4], *m_bAnalogLeftY[4], *m_bAnalogRightX[4], *m_bAnalogRightY[4],
			*m_bAnalogTriggerL[4], *m_bAnalogTriggerR[4],
			// Nunchuck
			*m_bNcShake[4], *m_bNcZ[4], *m_bNcC[4], *m_bNcL[4], *m_bNcR[4], *m_bNcU[4], *m_bNcD[4],
			// Wiimote
			*m_bWmShake[4], *m_bWmPitchL[4], *m_bWmPitchR[4], *m_bWmA[4], *m_bWmB[4], *m_bWm1[4], *m_bWm2[4], *m_bWmP[4], *m_bWmM[4], *m_bWmH[4], *m_bWmD[4], *m_bWmU[4], *m_bWmR[4], *m_bWmL[4],
			// Classic Controller
			*m_bCcA[4], *m_bCcB[4], *m_bCcX[4], *m_bCcY[4],
			*m_bCcP[4], *m_bCcM[4], *m_bCcH[4],
			*m_bCcTl[4], *m_bCcZl[4], *m_bCcZr[4], *m_bCcTr[4],
			*m_bCcDl[4], *m_bCcDu[4], *m_bCcDr[4], *m_bCcDd[4],
			*m_bCcLl[4], *m_bCcLu[4], *m_bCcLr[4], *m_bCcLd[4],
			*m_bCcRl[4], *m_bCcRu[4], *m_bCcRr[4], *m_bCcRd[4];
		wxStaticText *m_TextScreenWidth[4], *m_TextScreenHeight[4], *m_TextScreenLeft[4], *m_TextScreenTop[4], *m_TextAR[4],
			*m_tAnalogX[8], *m_tAnalogY[8], *m_TiltTextRoll[4], *m_TiltTextPitch[4],
			*m_CheckC2SLabel[4], *m_ComboDeadZoneLabel[4], *m_TStatusLeftIn[4], *m_TStatusLeftOut[4], *m_TStatusRightIn[4], *m_TStatusRightOut[4],
			*m_TriggerStatusL[4], *m_TriggerStatusR[4], *m_TriggerStatusLx[4], *m_TriggerStatusRx[4],
			*m_tAnalogTriggerInput[4], *m_tAnalogTriggerL[4], *m_tAnalogTriggerR[4],
			// Nunchuck
			*m_tNcShake[4], *m_tNcZ[4], *m_tNcC[4], *m_tNcL[4], *m_tNcR[4], *m_tNcU[4], *m_tNcD[4],
			// Wiimote
			*m_tWmShake[4], *m_tWmPitchL[4], *m_tWmPitchR[4], *m_tWmA[4], *m_tWmB[4], *m_tWm1[4], *m_tWm2[4], *m_tWmP[4], *m_tWmM[4], *m_tWmH[4], *m_tWmL[4], *m_tWmR[4], *m_tWmU[4],*m_tWmD[4],
			*m_NunchuckTextStick[5],
			// Classic Controller
			*m_tCcA[4], *m_tCcB[4], *m_tCcX[4], *m_tCcY[4],
			*m_tCcP[4], *m_tCcM[4], *m_tCcH[4],
			*m_tCcTl[4], *m_tCcZl[4], *m_tCcZr[4], *m_tCcTr[4],
			*m_tCcDl[4], *m_tCcDu[4], *m_tCcDr[4], *m_tCcDd[4],
			*m_tCcLl[4], *m_tCcLu[4], *m_tCcLr[4], *m_tCcLd[4],
			*m_tCcRl[4], *m_tCcRu[4], *m_tCcRr[4], *m_tCcRd[4],
			*m_CcTextLeftStick[4], *m_CcTextRightStick[4], *m_CcTextTriggers[4];
		wxButton *ClickedButton;
		wxString OldLabel;
		wxSlider *m_SliderWidth[4], *m_SliderHeight[4], *m_SliderLeft[4], *m_SliderTop[4];

		// Emulated Wiimote settings
		wxCheckBox *m_SidewaysDPad[4], *m_WiimoteOnline[4],
			*m_CheckC2S[4], *m_TiltInvertRoll[4], *m_TiltInvertPitch[4],
			*m_WiiMotionPlusConnected[4], *m_NunchuckConnected[4], *m_ClassicControllerConnected[4], *m_BalanceBoardConnected[4], *m_GuitarHeroGuitarConnected[4], *m_GuitarHeroWorldTourDrumsConnected[4],
			*m_CheckAR43[4], *m_CheckAR169[4], *m_Crop[4];
		wxComboBox *m_TiltComboInput[4], *m_TiltComboRangeRoll[4], *m_TiltComboRangePitch[4], *m_Joyname[4], *m_ComboDiagonal[4], *m_ComboDeadZoneLeft[4], *m_ComboDeadZoneRight[4], *m_TriggerType[4],
			*m_NunchuckComboStick[4], *m_CcComboLeftStick[4], *m_CcComboRightStick[4], *m_CcComboTriggers[4];

		// Real Wiimote settings
		wxCheckBox *m_ConnectRealWiimote[4], *m_UseRealWiimote[4], *m_UpdateMeters;

		wxPanel *m_pLeftInStatus[4], *m_pLeftOutStatus[4], *m_pRightInStatus[4], *m_pRightOutStatus[4];
		wxStaticBitmap *m_bmpSquareLeftIn[4], *m_bmpSquareLeftOut[4], *m_bmpSquareRightIn[4], *m_bmpSquareRightOut[4];
		wxStaticBoxSizer *m_gAnalogLeft[4], *m_gAnalogRight[4], *m_gTrigger[4],
			*m_gWiimote[4], *m_gNunchuck[4], *m_gClassicController[4];
		wxBitmap CreateBitmapDot(), CreateBitmap(), CreateBitmapDeadZone(int Radius), CreateBitmapClear();		

		wxButton * m_RecordButton[RECORDING_ROWS + 1];
		wxChoice * m_RecordHotKeySwitch[RECORDING_ROWS + 1];
		wxChoice * m_RecordHotKeyWiimote[RECORDING_ROWS + 1];
		wxChoice * m_RecordHotKeyNunchuck[RECORDING_ROWS + 1];
		wxChoice * m_RecordHotKeyIR[RECORDING_ROWS + 1];
		wxTextCtrl * m_RecordText[RECORDING_ROWS + 1];
		wxTextCtrl * m_RecordGameText[RECORDING_ROWS + 1];
		wxTextCtrl * m_RecordIRBytesText[RECORDING_ROWS + 1];
		wxTextCtrl * m_RecordSpeed[RECORDING_ROWS + 1];
		wxChoice * m_RecordPlayBackSpeed[RECORDING_ROWS + 1];

		/*
		struct m_sRecording
		{
			u8 x;
			u8 y;
			u8 z;
			double Time;
		};
		*/
		std::vector<SRecording> m_vRecording;
		int IRBytes;

		enum
		{
			ID_CLOSE = 1000,
			ID_APPLY,
			ID_ABOUTOGL,
			IDTM_EXIT, IDTM_UPDATE, IDTM_SHUTDOWN, IDTM_UPDATE_ONCE, IDTM_BUTTON, IDTM_UPDATE_PAD, // Timer

			ID_NOTEBOOK, ID_CONTROLLERPAGE1, ID_CONTROLLERPAGE2, ID_CONTROLLERPAGE3, ID_CONTROLLERPAGE4, ID_PAGE_RECORDING,
			
			// Emulated Wiimote
			ID_SIDEWAYSDPAD,
			ID_NUNCHUCKCONNECTED, ID_CLASSICCONTROLLERCONNECTED,
			IDC_WIMOTE_ON,

			// Gamepad <It's important that the internal ordering of these are unchanged>
			IDB_ANALOG_LEFT_X, IDB_ANALOG_LEFT_Y,
			IDB_ANALOG_RIGHT_X, IDB_ANALOG_RIGHT_Y,
			IDB_TRIGGER_L, IDB_TRIGGER_R,

			ID_ANALOG_LEFT_X, ID_ANALOG_LEFT_Y,
			ID_ANALOG_RIGHT_X, ID_ANALOG_RIGHT_Y,
			ID_TRIGGER_L, ID_TRIGGER_R,

			// Wiimote
			IDS_WIDTH, IDS_HEIGHT, IDS_LEFT, IDS_TOP,
			IDB_WM_A, IDB_WM_B,
			IDB_WM_1, IDB_WM_2,
			IDB_WM_P, IDB_WM_M, IDB_WM_H,
			IDB_WM_L, IDB_WM_R, IDB_WM_U, IDB_WM_D,
			IDB_WM_SHAKE, IDB_WM_PITCH_L, IDB_WM_PITCH_R,

			// Nunchuck
			IDB_NC_Z, IDB_NC_C, IDB_NC_L, IDB_NC_R, IDB_NC_U, IDB_NC_D,
			IDB_NC_SHAKE,

			// Classic Controller
			IDB_CC_A, IDB_CC_B,
			IDB_CC_X, IDB_CC_Y,
			IDB_CC_P, IDB_CC_M, IDB_CC_H,
			IDB_CC_TL, IDB_CC_ZL, IDB_CC_ZR, IDB_CC_TR,
			IDB_CC_DL, IDB_CC_DU, IDB_CC_DR, IDB_CC_DD, // Digital pad
			IDB_CC_LL, IDB_CC_LU, IDB_CC_LR, IDB_CC_LD, // Left analog stick
			IDB_CC_RL, IDB_CC_RU, IDB_CC_RR, IDB_CC_RD, // Right analog stick

			// Gamepad settings
			IDC_JOYNAME, IDC_LEFT_C2S, IDCB_LEFT_DIAGONAL, IDCB_DEAD_ZONE_LEFT, IDCB_DEAD_ZONE_RIGHT,
			ID_TRIGGER_TYPE, ID_TILT_INPUT, ID_TILT_RANGE_ROLL, ID_TILT_RANGE_PITCH, ID_TILT_INVERT_ROLL, ID_TILT_INVERT_PITCH,
			IDCB_NUNCHUCK_STICK, IDCB_CC_LEFT_STICK, IDCB_CC_RIGHT_STICK, IDCB_CC_TRIGGERS,

			// Real
			ID_CONNECT_REAL, ID_USE_REAL, ID_UPDATE_REAL, IDT_STATUS,
			IDB_RECORD = 2000,
			IDC_RECORD = 3000,
			IDC_PLAY_WIIMOTE, IDC_PLAY_NUNCHUCK, IDC_PLAY_IR, IDT_RECORD_TEXT, IDT_RECORD_GAMETEXT, IDT_RECORD_IRBYTESTEXT, IDT_RECORD_SPEED, IDT_RECORD_PLAYSPEED
		};

		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
		void CreateGUIControlsRecording();
		void AboutClick(wxCommandEvent& event);
		void GeneralSettingsChanged(wxCommandEvent& event);
		void GeneralSettingsChangedScroll(wxScrollEvent& event);

		void DoConnectReal(); // Real
		void DoUseReal();

		void DoExtensionConnectedDisconnected(int Extension = -1); // Emulated

		// Gamepad configuration
		void SetButtonText(int id, char text[128], int _Page = -1); void SetButtonTextAll(int id, char text[128]);
		wxString GetButtonText(int id, int Page = -1);
		void GetButtons(wxCommandEvent& event); void DoGetButtons(int);
		void SaveButtonMapping(int controller, bool DontChangeId = false, int FromSlot = -1); void SaveButtonMappingAll(int Slot);
		void SaveKeyboardMapping(int Controller, int Id, int Key);
		void ToBlank(bool ToBlank = true);
		void PadGetStatus();
		void DoSave(bool ChangePad = false, int Slot = -1);
		void DoChangeJoystick(); void PadOpen(int Open); void PadClose(int Close); void DoChangeDeadZone(bool Left);
		void OnButtonClick(wxCommandEvent& event);

		// Configure buttons
		int GetButtonWaitingID, GetButtonWaitingTimer;
};

extern ConfigDialog *frame;

#endif