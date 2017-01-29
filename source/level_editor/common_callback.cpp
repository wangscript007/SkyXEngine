
LRESULT TrueExit(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (MessageBox(0, "�� ������������� ������ �����?", "�����?!", MB_YESNO | MB_ICONWARNING | MB_TASKMODAL) == IDYES)
		DefWindowProc(hwnd, msg, wParam, lParam);

	return 0;
}

LRESULT ComMenuId(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	WORD id = LOWORD(wParam);

	//����
	//�����
	if (id == ID_FILE_NEW)
	{
		SGeom_ModelsClear();
		SGeom_GreenClear();
	}
	//�������
	else if (id == ID_FILE_OPEN)
	{
		char tmppath[1024];
		tmppath[0] = 0;
		char tmpname[1024];
		DialogLoadLevel(tmppath);
		if (def_str_validate(tmppath))
		{
			StrCutNameNEx(tmppath, tmpname);
			LoadLevel(tmpname);
		}

	}
	//���������
	else if (id == ID_FILE_SAVE)
	{
		char tmppath[1024];
		tmppath[0] = 0;
		char tmpname[1024];
		DialogSaveLevel(tmppath);
		if (StrValidate(tmppath))
		{
			StrCutNameNEx(tmppath, tmpname);
			SaveLevel(tmpname);
		}
	}
	//�����
	else if (id == ID_FILE_EXIT)
	{
		return TrueExit(hwnd, msg, wParam, lParam);
	}


	return 0;
}

LRESULT MsgEditSize(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	GData::ReSize = true;
	return 0;
}

///////

LRESULT SXLevelEditor_ButtonGeometryOpen_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	SXLevelEditor::ListBoxList->Clear();
	long tmpcountmodel = SGeom_ModelsGetCount();
	char tmptextvalcountmodel[64];
	sprintf(tmptextvalcountmodel, "%d", tmpcountmodel);
	SXLevelEditor::StaticListValCount->SetText(tmptextvalcountmodel);

	char tmpnamecountpoly[1024];
	for (int i = 0; i < tmpcountmodel;++i)
	{
		sprintf(tmpnamecountpoly, "%s | %d", SGeom_ModelsMGetName(i), SGeom_ModelsMGetCountPoly(i));
		SXLevelEditor::ListBoxList->AddItem(tmpnamecountpoly);
	}

	GCActivateAllElems(false);
	MCActivateAllElems(true);
	MCActivateTrans(false);

	SXLevelEditor::HowActivateType = -1;
	return 0;
}

LRESULT SXLevelEditor_ButtonGreenOpen_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	SXLevelEditor::ListBoxList->Clear();
	long tmpcountmodel = SGeom_GreenGetCount();
	char tmptextvalcountmodel[64];
	sprintf(tmptextvalcountmodel, "%d", tmpcountmodel);
	SXLevelEditor::StaticListValCount->SetText(tmptextvalcountmodel);

	char tmpnamecountpoly[1024];
	for (int i = 0; i < tmpcountmodel; ++i)
	{
		sprintf(tmpnamecountpoly, "%s | %s | %d", 
			SGeom_GreenMGetName(i),
			(SGeom_GreenMGetTypeCountGen(i) == GREEN_TYPE_GRASS ? "grass" : "tree/shrub"),
			SGeom_GreenMGetCountGen(i));
		SXLevelEditor::ListBoxList->AddItem(tmpnamecountpoly);
	}

	MCActivateAllElems(false);
	MCActivateTrans(false);
	GCActivateCreatingElems(true);
	GCActivateAllElems(true);
	
	//MCActivateTrans(false);

	SXLevelEditor::HowActivateType = -2;
	return 0;
}

LRESULT SXLevelEditor_ListBoxList_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int sel = SXLevelEditor::ListBoxList->GetSel();

	if (sel < 0)
		return 0;

	if (SXLevelEditor::HowActivateType == -1 || SXLevelEditor::HowActivateType == 1)
	{
		if (SGeom_ModelsGetCount() > 0 && sel < SGeom_ModelsGetCount())
		{
			MCInitElemsSelModel(sel);
			SXLevelEditor::HowActivateType = 1;
		}
	}
	else if (SXLevelEditor::HowActivateType == -2 || SXLevelEditor::HowActivateType == 2)
	{
		if (SGeom_GreenGetCount() > 0 && sel < SGeom_GreenGetCount())
		{
			GCInitElemsSelModel(sel);
			SXLevelEditor::HowActivateType = 2;
		}
	}

	return 0;
}

LRESULT SXLevelEditor_EditName_Enter(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int sel = SXLevelEditor::ListBoxList->GetSel();
	if (SXLevelEditor::HowActivateType == 1)
	{
		SXLevelEditor::EditName->GetText(SGeom_ModelsMGetName(sel), 64);
	}
	else if (SXLevelEditor::HowActivateType == 2)
	{
		SXLevelEditor::EditName->GetText(SGeom_GreenMGetName(sel), 64);
	}

	return 0;
}

LRESULT SXLevelEditor_ButtonDelete_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int sel = SXLevelEditor::ListBoxList->GetSel();

	if (sel < 0)
		return 0;

	if (SXLevelEditor::HowActivateType == 1)
	{
		if (SGeom_ModelsGetCount() > 0 && sel < SGeom_ModelsGetCount())
		{
			SGeom_ModelsDelModel(sel);
			SXLevelEditor::ListBoxList->DeleteItem(sel);
			if (SGeom_ModelsGetCount() > 0)
			{
				if (sel > 0)
				{
					if (SGeom_ModelsGetCount() <= sel)
						sel -= 1;
				}
				SXLevelEditor::ListBoxList->SetSel(sel);
				MCInitElemsSelModel(sel);
			}
			else
			{
				SXLevelEditor_ButtonGeometryOpen_Click(hwnd, msg, wParam, lParam);
			}
		}
	}
	else if (SXLevelEditor::HowActivateType == 2)
	{
		if (SGeom_GreenGetCount() > 0 && sel < SGeom_GreenGetCount())
		{
			SGeom_GreenDelGreen(sel);
			SXLevelEditor::ListBoxList->DeleteItem(sel);
			if (SGeom_GreenGetCount() > 0)
			{
				if (sel > 0)
				{
					if (SGeom_GreenGetCount() <= sel)
						sel -= 1;
				}
				SXLevelEditor::ListBoxList->SetSel(sel);
				GCInitElemsSelModel(sel);
			}
			else
			{
				SXLevelEditor_ButtonGreenOpen_Click(hwnd, msg, wParam, lParam);
			}
		}
	}

	return 0;
}

LRESULT SXLevelEditor_ButtonModel_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char tmppath[1024];
	tmppath[0] = 0;
	char tmpname[1024];
	DialogLoadMesh(tmppath);
	if (def_str_validate(tmppath))
	{
		StrCutMesh(tmppath, tmpname);
		SXLevelEditor::EditModel->SetText(tmpname);
		int sel = SXLevelEditor::ListBoxList->GetSel();
		if (SXLevelEditor::HowActivateType == 2)
		{
			if (sel >= 0 && sel < SGeom_GreenGetCount())
				SGeom_GreenMSetLod(sel, 0, tmpname);
		}
	}
	return 0;
}

LRESULT SXLevelEditor_ButtonLod1_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char tmppath[1024];
	tmppath[0] = 0;
	char tmpname[1024];
	DialogLoadMesh(tmppath);
	if (def_str_validate(tmppath))
	{
		StrCutMesh(tmppath, tmpname);
		SXLevelEditor::EditLod1->SetText(tmpname);
		int sel = SXLevelEditor::ListBoxList->GetSel();
		if (SXLevelEditor::HowActivateType == 1)
		{
			if (sel >= 0 && sel < SGeom_ModelsGetCount())
				SGeom_ModelsMSetLodPath(sel, tmpname);
		}
		else if (SXLevelEditor::HowActivateType == 2)
		{
			if (sel >= 0 && sel < SGeom_GreenGetCount())
				SGeom_GreenMSetLod(sel, 1, tmpname);
		}
	}
	return 0;
}

LRESULT SXLevelEditor_ButtonLod2_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char tmppath[1024];
	tmppath[0] = 0;
	char tmpname[1024];
	DialogLoadMesh(tmppath);
	if (def_str_validate(tmppath))
	{
		StrCutMesh(tmppath, tmpname);
		SXLevelEditor::EditLod2->SetText(tmpname);
		int sel = SXLevelEditor::ListBoxList->GetSel();
		if (SXLevelEditor::HowActivateType == 2)
		{
			if (sel >= 0 && sel < SGeom_GreenGetCount())
				SGeom_GreenMSetLod(sel, 2, tmpname);
		}
	}
	return 0;
}

void SXLevelEditor_Transform(DWORD timeDelta)
{
	static bool IsSFirstLBMTransform = false;
	static bool IsSFirstRBMTransform = false;
	static int CoordinateTransformation = -1;

	if (SXLevelEditor::RadioButtonPosX->GetCheck() || SXLevelEditor::RadioButtonRotX->GetCheck() || SXLevelEditor::RadioButtonScaleX->GetCheck())
		CoordinateTransformation = 0;
	else if (SXLevelEditor::RadioButtonPosY->GetCheck() || SXLevelEditor::RadioButtonRotY->GetCheck() || SXLevelEditor::RadioButtonScaleY->GetCheck())
		CoordinateTransformation = 1;
	else if (SXLevelEditor::RadioButtonPosZ->GetCheck() || SXLevelEditor::RadioButtonRotZ->GetCheck() || SXLevelEditor::RadioButtonScaleZ->GetCheck())
		CoordinateTransformation = 2;

	if (SXLevelEditor::HowActivateType == 1)
	{
		if (::GetAsyncKeyState(VK_LSHIFT) && SGeom_ModelsGetCount() > 0)
		{
			DWORD selmodel = SXLevelEditor::ListBoxList->GetSel();
			if (SXLevelEditor::RadioButtonPosX->GetCheck() || SXLevelEditor::RadioButtonPosY->GetCheck() || SXLevelEditor::RadioButtonPosZ->GetCheck())
			{
				float3& pos = *(SGeom_ModelsMGetPosition(selmodel));

				if (::GetAsyncKeyState(VK_UP) & 0x8000f)
					pos[CoordinateTransformation] += timeDelta * 0.001f;
				if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
					pos[CoordinateTransformation] -= timeDelta * 0.001f;
				if (::GetAsyncKeyState(VK_LBUTTON) & 0x8000f)
				{
					if (IsSFirstRBMTransform)
					{
						UINT cx = GetSystemMetrics(SM_CXSCREEN) / 2;
						UINT cy = GetSystemMetrics(SM_CYSCREEN) / 2;
						POINT p;
						GetCursorPos(&p);
						POINT centr;
						centr.x = cx; centr.y = cy;

						if (cy != UINT(p.y))
							pos[CoordinateTransformation] += timeDelta * 0.001f * float(-int(p.y - cy));
					}
					else
						IsSFirstRBMTransform = true;
					CameraUpdate::CentererCursor();
				}
				else
				{
					IsSFirstLBMTransform = false;
					IsSFirstRBMTransform = false;
				}

				char tmpPosX[32];
				char tmpPosY[32];
				char tmpPosZ[32];

				sprintf(tmpPosX, "%f", pos.x);
				sprintf(tmpPosY, "%f", pos.y);
				sprintf(tmpPosZ, "%f", pos.z);

				SXLevelEditor::EditPosX->SetText(tmpPosX);
				SXLevelEditor::EditPosY->SetText(tmpPosY);
				SXLevelEditor::EditPosZ->SetText(tmpPosZ);

				SGeom_ModelsMApplyTransform(selmodel);
			}

			else if (SXLevelEditor::RadioButtonRotX->GetCheck() || SXLevelEditor::RadioButtonRotY->GetCheck() || SXLevelEditor::RadioButtonRotZ->GetCheck())
			{
				float3& pos = *(SGeom_ModelsMGetRotation(selmodel));

				if (::GetAsyncKeyState(VK_UP) & 0x8000f)
					pos[CoordinateTransformation] += timeDelta * 0.001f;
				if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
					pos[CoordinateTransformation] -= timeDelta * 0.001f;
				if (::GetAsyncKeyState(VK_LBUTTON) & 0x8000f)
				{
					if (IsSFirstRBMTransform)
					{
						UINT cx = GetSystemMetrics(SM_CXSCREEN) / 2;
						UINT cy = GetSystemMetrics(SM_CYSCREEN) / 2;
						POINT p;
						GetCursorPos(&p);
						POINT centr;
						centr.x = cx; centr.y = cy;

						if (cy != UINT(p.y))
							pos[CoordinateTransformation] += timeDelta * 0.001f * float(-int(p.y - cy));
					}
					else
						IsSFirstRBMTransform = true;
					CameraUpdate::CentererCursor();
				}
				else
				{
					IsSFirstLBMTransform = false;
					IsSFirstRBMTransform = false;
				}

				char tmpPosX[32];
				char tmpPosY[32];
				char tmpPosZ[32];

				sprintf(tmpPosX, "%f", pos.x);
				sprintf(tmpPosY, "%f", pos.y);
				sprintf(tmpPosZ, "%f", pos.z);

				SXLevelEditor::EditRotX->SetText(tmpPosX);
				SXLevelEditor::EditRotY->SetText(tmpPosY);
				SXLevelEditor::EditRotZ->SetText(tmpPosZ);

				SGeom_ModelsMApplyTransform(selmodel);
			}

			else if (SXLevelEditor::RadioButtonScaleX->GetCheck() || SXLevelEditor::RadioButtonScaleY->GetCheck() || SXLevelEditor::RadioButtonScaleZ->GetCheck())
			{
				float3& pos = *(SGeom_ModelsMGetScale(selmodel));

				if (::GetAsyncKeyState(VK_UP) & 0x8000f)
					pos[CoordinateTransformation] += timeDelta * 0.001f;
				if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
					pos[CoordinateTransformation] -= timeDelta * 0.001f;
				if (::GetAsyncKeyState(VK_LBUTTON) & 0x8000f)
				{
					if (IsSFirstRBMTransform)
					{
						UINT cx = GetSystemMetrics(SM_CXSCREEN) / 2;
						UINT cy = GetSystemMetrics(SM_CYSCREEN) / 2;
						POINT p;
						GetCursorPos(&p);
						POINT centr;
						centr.x = cx; centr.y = cy;

						if (cy != UINT(p.y))
							pos[CoordinateTransformation] += timeDelta * 0.001f * float(-int(p.y - cy));
					}
					else
						IsSFirstRBMTransform = true;
					CameraUpdate::CentererCursor();
				}
				else
				{
					IsSFirstLBMTransform = false;
					IsSFirstRBMTransform = false;
				}

				char tmpPosX[32];
				char tmpPosY[32];
				char tmpPosZ[32];

				sprintf(tmpPosX, "%f", pos.x);
				sprintf(tmpPosY, "%f", pos.y);
				sprintf(tmpPosZ, "%f", pos.z);

				SXLevelEditor::EditScaleX->SetText(tmpPosX);
				SXLevelEditor::EditScaleY->SetText(tmpPosY);
				SXLevelEditor::EditScaleZ->SetText(tmpPosZ);

				SGeom_ModelsMApplyTransform(selmodel);
			}
		}
	}
}