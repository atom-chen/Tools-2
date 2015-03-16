#include "ExportDialog.h"
#include  "Version.h"

namespace EasyOgreExporter
{
	/**
	* Configuration interface
	**/
	INT_PTR CALLBACK IGameExporterOptionsDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		ParamList* exp = DLGetWindowLongPtr<ParamList*>(hWnd);
		ISpinnerControl* spin;

		switch (message)
		{
		case WM_INITDIALOG:
		{
			exp = (ParamList*)lParam;
			DLSetWindowLongPtr(hWnd, lParam);
			CenterWindow(hWnd, GetParent(hWnd));

			//fill Ogre version combo box
#ifdef UNICODE
			SendDlgItemMessage(hWnd, IDC_OGREVERSION, CB_SETMINVISIBLE, 30, 0);
			SendDlgItemMessage(hWnd, IDC_OGREVERSION, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(hWnd, IDC_OGREVERSION, CB_ADDSTRING, 0, (LPARAM)L"Ogre Latest");
			SendDlgItemMessage(hWnd, IDC_OGREVERSION, CB_ADDSTRING, 0, (LPARAM)L"Ogre 1.8");
			SendDlgItemMessage(hWnd, IDC_OGREVERSION, CB_ADDSTRING, 0, (LPARAM)L"Ogre 1.7");
			SendDlgItemMessage(hWnd, IDC_OGREVERSION, CB_ADDSTRING, 0, (LPARAM)L"Ogre 1.4");
			SendDlgItemMessage(hWnd, IDC_OGREVERSION, CB_ADDSTRING, 0, (LPARAM)L"Ogre 1.0");
			SendDlgItemMessage(hWnd, IDC_OGREVERSION, CB_SETCURSEL, (int)exp->meshVersion, 0);

			//fill material prefix
			std::wstring resPrefix_w;
			resPrefix_w.assign(exp->resPrefix.begin(), exp->resPrefix.end());
			SendDlgItemMessage(hWnd, IDC_RESPREFIX, WM_SETTEXT, 0, (LPARAM)resPrefix_w.data());

			//fill material sub dir
			std::wstring materialOutputDir_w;
			materialOutputDir_w.assign(exp->materialOutputDir.begin(), exp->materialOutputDir.end());
			SendDlgItemMessage(hWnd, IDC_MATDIR, WM_SETTEXT, 0, (LPARAM)materialOutputDir_w.data());

			//fill texture sub dir
			std::wstring texOutputDir_w;
			texOutputDir_w.assign(exp->texOutputDir.begin(), exp->texOutputDir.end());
			SendDlgItemMessage(hWnd, IDC_TEXDIR, WM_SETTEXT, 0, (LPARAM)texOutputDir_w.data());

			//fill mesh subdir
			std::wstring meshOutputDir_w;
			meshOutputDir_w.assign(exp->meshOutputDir.begin(), exp->meshOutputDir.end());
			SendDlgItemMessage(hWnd, IDC_MESHDIR, WM_SETTEXT, 0, (LPARAM)meshOutputDir_w.data());

			//fill prog subdir
			std::wstring programOutputDir_w;
			programOutputDir_w.assign(exp->programOutputDir.begin(), exp->programOutputDir.end());
			SendDlgItemMessage(hWnd, IDC_PROGDIR, WM_SETTEXT, 0, (LPARAM)programOutputDir_w.data());
#else
			SendDlgItemMessage(hWnd, IDC_OGREVERSION, CB_SETMINVISIBLE, 30, 0);
			SendDlgItemMessage(hWnd, IDC_OGREVERSION, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(hWnd, IDC_OGREVERSION, CB_ADDSTRING, 0, (LPARAM)"Ogre Latest");
			SendDlgItemMessage(hWnd, IDC_OGREVERSION, CB_ADDSTRING, 0, (LPARAM)"Ogre 1.8");
			SendDlgItemMessage(hWnd, IDC_OGREVERSION, CB_ADDSTRING, 0, (LPARAM)"Ogre 1.7");
			SendDlgItemMessage(hWnd, IDC_OGREVERSION, CB_ADDSTRING, 0, (LPARAM)"Ogre 1.4");
			SendDlgItemMessage(hWnd, IDC_OGREVERSION, CB_ADDSTRING, 0, (LPARAM)"Ogre 1.0");
			SendDlgItemMessage(hWnd, IDC_OGREVERSION, CB_SETCURSEL, (int)exp->meshVersion, 0);

			//fill material prefix
			SendDlgItemMessage(hWnd, IDC_RESPREFIX, WM_SETTEXT, 0, (LPARAM)(char*)exp->resPrefix.c_str());

			//fill material sub dir
			SendDlgItemMessage(hWnd, IDC_MATDIR, WM_SETTEXT, 0, (LPARAM)(char*)exp->materialOutputDir.c_str());

			//fill texture sub dir
			SendDlgItemMessage(hWnd, IDC_TEXDIR, WM_SETTEXT, 0, (LPARAM)(char*)exp->texOutputDir.c_str());

			//fill mesh subdir
			SendDlgItemMessage(hWnd, IDC_MESHDIR, WM_SETTEXT, 0, (LPARAM)(char*)exp->meshOutputDir.c_str());

			//fill prog subdir
			SendDlgItemMessage(hWnd, IDC_PROGDIR, WM_SETTEXT, 0, (LPARAM)(char*)exp->programOutputDir.c_str());
#endif
			spin = GetISpinner(GetDlgItem(hWnd, IDC_RESAMPLE_SPIN));
			spin->LinkToEdit(GetDlgItem(hWnd, IDC_RESAMPLE_STEP), EDITTYPE_INT);
			spin->SetLimits(1, 100, TRUE);
			spin->SetScale(1.0f);
			spin->SetValue(exp->resampleStep, FALSE);
			ReleaseISpinner(spin);

			//advanced config
			CheckDlgButton(hWnd, IDC_YUPAXIS, exp->yUpAxis);
			CheckDlgButton(hWnd, IDC_SHAREDGEOM, exp->useSharedGeom);
			CheckDlgButton(hWnd, IDC_GENLOD, exp->generateLOD);
			CheckDlgButton(hWnd, IDC_EDGELIST, exp->buildEdges);
			CheckDlgButton(hWnd, IDC_TANGENT, exp->buildTangents);
			CheckDlgButton(hWnd, IDC_SPLITMIRROR, exp->tangentsSplitMirrored);
			CheckDlgButton(hWnd, IDC_SPLITROT, exp->tangentsSplitRotated);
			CheckDlgButton(hWnd, IDC_STOREPARITY, exp->tangentsUseParity);

			CheckDlgButton(hWnd, IDC_CONVDDS, exp->convertToDDS);
			CheckDlgButton(hWnd, IDC_RESAMPLE_ANIMS, exp->resampleAnims);
			CheckDlgButton(hWnd, IDC_LOGS, exp->enableLogs);

#ifdef UNICODE
			//fill Shader mode combo box
			SendDlgItemMessage(hWnd, IDC_SHADERMODE, CB_SETMINVISIBLE, 30, 0);
			SendDlgItemMessage(hWnd, IDC_SHADERMODE, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(hWnd, IDC_SHADERMODE, CB_ADDSTRING, 0, (LPARAM)L"None");
			SendDlgItemMessage(hWnd, IDC_SHADERMODE, CB_ADDSTRING, 0, (LPARAM)L"Only for Normal/Specular");
			SendDlgItemMessage(hWnd, IDC_SHADERMODE, CB_ADDSTRING, 0, (LPARAM)L"All materials (3 lights)");
			SendDlgItemMessage(hWnd, IDC_SHADERMODE, CB_ADDSTRING, 0, (LPARAM)L"All materials (multi pass)");

			SendDlgItemMessage(hWnd, IDC_SHADERMODE, CB_SETCURSEL, (int)exp->exportProgram, 0);

			//fill Max texture size combo box
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_SETMINVISIBLE, 30, 0);
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_ADDSTRING, 0, (LPARAM)L"64");
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_ADDSTRING, 0, (LPARAM)L"128");
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_ADDSTRING, 0, (LPARAM)L"256");
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_ADDSTRING, 0, (LPARAM)L"512");
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_ADDSTRING, 0, (LPARAM)L"1024");
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_ADDSTRING, 0, (LPARAM)L"2048");
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_ADDSTRING, 0, (LPARAM)L"4096");

			//fill Mipmaps combo box
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_SETMINVISIBLE, 30, 0);
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_ADDSTRING, 0, (LPARAM)L"Max");
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_ADDSTRING, 0, (LPARAM)L"None");
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_ADDSTRING, 0, (LPARAM)L"2");
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_ADDSTRING, 0, (LPARAM)L"4");
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_ADDSTRING, 0, (LPARAM)L"8");
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_ADDSTRING, 0, (LPARAM)L"16");
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_ADDSTRING, 0, (LPARAM)L"32");
#else
			//fill Shader mode combo box
			SendDlgItemMessage(hWnd, IDC_SHADERMODE, CB_SETMINVISIBLE, 30, 0);
			SendDlgItemMessage(hWnd, IDC_SHADERMODE, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(hWnd, IDC_SHADERMODE, CB_ADDSTRING, 0, (LPARAM)"None");
			SendDlgItemMessage(hWnd, IDC_SHADERMODE, CB_ADDSTRING, 0, (LPARAM)"Only for Normal/Specular");
			SendDlgItemMessage(hWnd, IDC_SHADERMODE, CB_ADDSTRING, 0, (LPARAM)"All materials");

			SendDlgItemMessage(hWnd, IDC_SHADERMODE, CB_SETCURSEL, (int)exp->exportProgram, 0);

			//fill Max texture size combo box
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_SETMINVISIBLE, 30, 0);
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_ADDSTRING, 0, (LPARAM)"64");
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_ADDSTRING, 0, (LPARAM)"128");
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_ADDSTRING, 0, (LPARAM)"256");
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_ADDSTRING, 0, (LPARAM)"512");
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_ADDSTRING, 0, (LPARAM)"1024");
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_ADDSTRING, 0, (LPARAM)"2048");
			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_ADDSTRING, 0, (LPARAM)"4096");

			//fill Max texture size combo box
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_SETMINVISIBLE, 30, 0);
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_ADDSTRING, 0, (LPARAM)"Max");
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_ADDSTRING, 0, (LPARAM)"None");
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_ADDSTRING, 0, (LPARAM)"2");
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_ADDSTRING, 0, (LPARAM)"4");
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_ADDSTRING, 0, (LPARAM)"8");
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_ADDSTRING, 0, (LPARAM)"16");
			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_ADDSTRING, 0, (LPARAM)"32");
#endif

			// Enable or disable the DDS options
			EnableWindow(GetDlgItem(hWnd, IDC_TEXSIZE), exp->convertToDDS ? TRUE : FALSE);
			EnableWindow(GetDlgItem(hWnd, IDC_NUMMIPS), exp->convertToDDS ? TRUE : FALSE);

			int texSel = 0;
			if (exp->maxTextureSize == 128)
				texSel = 1;
			else if (exp->maxTextureSize == 256)
				texSel = 2;
			else if (exp->maxTextureSize == 512)
				texSel = 3;
			else if (exp->maxTextureSize == 1024)
				texSel = 4;
			else if (exp->maxTextureSize == 2048)
				texSel = 5;
			else if (exp->maxTextureSize == 4096)
				texSel = 6;

			SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_SETCURSEL, texSel, 0);

			int mipsSel = 0;
			if (exp->maxMipmaps == -1)
				mipsSel = 0;
			else if (exp->maxMipmaps == 0)
				mipsSel = 1;
			else if (exp->maxMipmaps == 2)
				mipsSel = 2;
			else if (exp->maxMipmaps == 4)
				mipsSel = 3;
			else if (exp->maxMipmaps == 8)
				mipsSel = 4;
			else if (exp->maxMipmaps == 16)
				mipsSel = 5;
			else if (exp->maxMipmaps == 32)
				mipsSel = 6;

			SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_SETCURSEL, mipsSel, 0);

			//Versioning
			TCHAR Title[256];
			_stprintf(Title, _T("Easy Ogre Exporter version %.2f"), EXVERSION);
			SetWindowText(hWnd, Title);
			return TRUE;
		}
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case IDC_CONVDDS:
			{
				// Enable or disable the DDS options
				exp->convertToDDS = IsDlgButtonChecked(hWnd, IDC_CONVDDS) ? true : false;
				EnableWindow(GetDlgItem(hWnd, IDC_TEXSIZE), exp->convertToDDS ? TRUE : FALSE);
				EnableWindow(GetDlgItem(hWnd, IDC_NUMMIPS), exp->convertToDDS ? TRUE : FALSE);
			}
			break;
			case IDOK:
			{
				// LRESULT 在 64 位机器上是 _int64 
				int ogreVerIdx = (int)SendDlgItemMessage(hWnd, IDC_OGREVERSION, CB_GETCURSEL, 0, 0);
				if (ogreVerIdx != CB_ERR)
				{
					switch (ogreVerIdx)
					{
					case 0:
						exp->meshVersion = TOGRE_LASTEST;
						break;
					case 1:
						exp->meshVersion = TOGRE_1_8;
						break;
					case 2:
						exp->meshVersion = TOGRE_1_7;
						break;
					case 3:
						exp->meshVersion = TOGRE_1_4;
						break;
					case 4:
						exp->meshVersion = TOGRE_1_0;
						break;

					default:
						exp->meshVersion = TOGRE_1_8;
					}
				}

				TSTR temp;
				int len = 0;

				len = (int)SendDlgItemMessage(hWnd, IDC_RESPREFIX, WM_GETTEXTLENGTH, 0, 0);
				temp.Resize(len + 1);
				SendDlgItemMessage(hWnd, IDC_RESPREFIX, WM_GETTEXT, len + 1, (LPARAM)temp.data());
#ifdef UNICODE
				std::wstring temp_w = temp.data();
				std::string temp_s;
				temp_s.assign(temp_w.begin(), temp_w.end());
				exp->resPrefix = temp_s;
#else
				exp->resPrefix = temp;
#endif

				len = (int)SendDlgItemMessage(hWnd, IDC_MATDIR, WM_GETTEXTLENGTH, 0, 0);
				temp.Resize(len + 1);
				SendDlgItemMessage(hWnd, IDC_MATDIR, WM_GETTEXT, len + 1, (LPARAM)temp.data());
#ifdef UNICODE
				temp_w = temp.data();
				temp_s.assign(temp_w.begin(), temp_w.end());
				exp->materialOutputDir = temp_s;
#else
				exp->materialOutputDir = temp;
#endif

				len = (int)SendDlgItemMessage(hWnd, IDC_TEXDIR, WM_GETTEXTLENGTH, 0, 0);
				temp.Resize(len + 1);
				SendDlgItemMessage(hWnd, IDC_TEXDIR, WM_GETTEXT, len + 1, (LPARAM)temp.data());
#ifdef UNICODE
				temp_w = temp.data();
				temp_s.assign(temp_w.begin(), temp_w.end());
				exp->texOutputDir = temp_s;
#else
				exp->texOutputDir = temp;
#endif

				len = (int)SendDlgItemMessage(hWnd, IDC_MESHDIR, WM_GETTEXTLENGTH, 0, 0);
				temp.Resize(len + 1);
				SendDlgItemMessage(hWnd, IDC_MESHDIR, WM_GETTEXT, len + 1, (LPARAM)temp.data());
#ifdef UNICODE
				temp_w = temp.data();
				temp_s.assign(temp_w.begin(), temp_w.end());
				exp->meshOutputDir = temp_s;
#else
				exp->meshOutputDir = temp;
#endif
				len = (int)SendDlgItemMessage(hWnd, IDC_PROGDIR, WM_GETTEXTLENGTH, 0, 0);
				temp.Resize(len + 1);
				SendDlgItemMessage(hWnd, IDC_PROGDIR, WM_GETTEXT, len + 1, (LPARAM)temp.data());
#ifdef UNICODE
				temp_w = temp.data();
				temp_s.assign(temp_w.begin(), temp_w.end());
				exp->programOutputDir = temp_s;
#else
				exp->programOutputDir = temp;
#endif

				spin = GetISpinner(GetDlgItem(hWnd, IDC_RESAMPLE_SPIN));
				exp->resampleStep = spin->GetIVal();
				ReleaseISpinner(spin);

				exp->yUpAxis = IsDlgButtonChecked(hWnd, IDC_YUPAXIS) ? true : false;
				exp->useSharedGeom = IsDlgButtonChecked(hWnd, IDC_SHAREDGEOM) ? true : false;
				exp->generateLOD = IsDlgButtonChecked(hWnd, IDC_GENLOD) ? true : false;
				exp->buildEdges = IsDlgButtonChecked(hWnd, IDC_EDGELIST) ? true : false;
				exp->buildTangents = IsDlgButtonChecked(hWnd, IDC_TANGENT) ? true : false;
				exp->tangentsSplitMirrored = IsDlgButtonChecked(hWnd, IDC_SPLITMIRROR) ? true : false;
				exp->tangentsSplitRotated = IsDlgButtonChecked(hWnd, IDC_SPLITROT) ? true : false;
				exp->tangentsUseParity = IsDlgButtonChecked(hWnd, IDC_STOREPARITY) ? true : false;
				exp->convertToDDS = IsDlgButtonChecked(hWnd, IDC_CONVDDS) ? true : false;
				exp->resampleAnims = IsDlgButtonChecked(hWnd, IDC_RESAMPLE_ANIMS) ? true : false;
				exp->enableLogs = IsDlgButtonChecked(hWnd, IDC_LOGS) ? true : false;

				int shaderIdx = (int)SendDlgItemMessage(hWnd, IDC_SHADERMODE, CB_GETCURSEL, 0, 0);
				if (shaderIdx != CB_ERR)
				{
					switch (shaderIdx)
					{
					case 0:
						exp->exportProgram = SHADER_NONE;
						break;
					case 1:
						exp->exportProgram = SHADER_BUMP;
						break;
					case 2:
						exp->exportProgram = SHADER_ALL;
						break;
					case 3:
						exp->exportProgram = SHADER_ALL_MULTI;
						break;

					default:
						exp->exportProgram = SHADER_BUMP;
					}
				}

				int texIdx = (int)SendDlgItemMessage(hWnd, IDC_TEXSIZE, CB_GETCURSEL, 0, 0);
				if (texIdx != CB_ERR)
				{
					switch (texIdx)
					{
					case 0:
						exp->maxTextureSize = 64;
						break;
					case 1:
						exp->maxTextureSize = 128;
						break;
					case 2:
						exp->maxTextureSize = 256;
						break;
					case 3:
						exp->maxTextureSize = 512;
						break;
					case 4:
						exp->maxTextureSize = 1024;
						break;
					case 5:
						exp->maxTextureSize = 2048;
						break;
					case 6:
						exp->maxTextureSize = 4096;
						break;

					default:
						exp->maxTextureSize = 2048;
					}
				}

				int mipsIdx = (int)SendDlgItemMessage(hWnd, IDC_NUMMIPS, CB_GETCURSEL, 0, 0);
				if (mipsIdx != CB_ERR)
				{
					switch (mipsIdx)
					{
					case 0:
						exp->maxMipmaps = -1;
						break;
					case 1:
						exp->maxMipmaps = 0;
						break;
					case 2:
						exp->maxMipmaps = 2;
						break;
					case 3:
						exp->maxMipmaps = 4;
						break;
					case 4:
						exp->maxMipmaps = 8;
						break;
					case 5:
						exp->maxMipmaps = 16;
						break;
					case 6:
						exp->maxMipmaps = 32;
						break;

					default:
						exp->maxMipmaps = -1;
					}
				}

				EndDialog(hWnd, 1);
			}
			break;
			case IDCANCEL:
				EndDialog(hWnd, 0);
				break;
			}

		default:
			return FALSE;

		}
		return TRUE;
	}

	// Dummy function for progress bar
	DWORD WINAPI progressCb(LPVOID arg)
	{
		return(0);
	}
}