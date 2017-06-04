
LRESULT SXMaterialEditor_TrackBarPenetration_MouseMove(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char thickness[64];
	thickness[0] = '0';

	int pos = SXMaterialEditor::TrackBarPenetration->GetPos();
	sprintf(thickness, "%.2f", float(pos)*0.01f);
	SXMaterialEditor::EditPenetration->SetText(thickness);

	SML_MtlSetPenetration(SXMaterialEditor::IDMat, float(pos)*0.01f);

	return 0;
}

LRESULT SXMaterialEditor_TrackBarRoughness_MouseMove(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char roughness[64];
	roughness[0] = '0';

	int pos = SXMaterialEditor::TrackBarRoughness->GetPos();
	sprintf(roughness, "%.2f", float(pos)*0.01f);
	SXMaterialEditor::EditRoughness->SetText(roughness);

	SML_MtlSetRoughness(SXMaterialEditor::IDMat, float(pos)*0.01f);

	return 0;
}

LRESULT SXMaterialEditor_TrackBarThickness_MouseMove(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char thickness[64];
	thickness[0] = '0';

	int pos = SXMaterialEditor::TrackBarThickness->GetPos();
	sprintf(thickness, "%.2f", float(pos)*0.01f);
	SXMaterialEditor::EditThickness->SetText(thickness);

	SML_MtlSetThickness(SXMaterialEditor::IDMat, float(pos)*0.01f);

	return 0;
}

LRESULT SXMaterialEditor_TrackBarF0_MouseMove(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char roughness[64];
	roughness[0] = '0';

	int pos = SXMaterialEditor::TrackBarF0->GetPos();
	sprintf(roughness, "%.2f", float(pos)*0.01f);
	SXMaterialEditor::EditF0->SetText(roughness);

	SML_MtlSetF0(SXMaterialEditor::IDMat, float(pos)*0.01f);

	return 0;
}

//////////

LRESULT SXMaterialEditor_TrackBarUDVSX_MouseMove(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char roughness[64];
	roughness[0] = '0';

	int pos = SXMaterialEditor::TrackBarUDVSX->GetPos();
	sprintf(roughness, "%.2f", float(pos)*0.01f);
	SXMaterialEditor::EditUDVSX->SetText(roughness);

	SML_MtlSetUDVS(SXMaterialEditor::IDMat, 0, float(pos)*0.01f);

	return 0;
}

LRESULT SXMaterialEditor_TrackBarUDVSY_MouseMove(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char roughness[64];
	roughness[0] = '0';

	int pos = SXMaterialEditor::TrackBarUDVSY->GetPos();
	sprintf(roughness, "%.2f", float(pos)*0.01f);
	SXMaterialEditor::EditUDVSY->SetText(roughness);

	SML_MtlSetUDVS(SXMaterialEditor::IDMat, 1, float(pos)*0.01f);

	return 0;
}

LRESULT SXMaterialEditor_TrackBarUDVSZ_MouseMove(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char roughness[64];
	roughness[0] = '0';

	int pos = SXMaterialEditor::TrackBarUDVSZ->GetPos();
	sprintf(roughness, "%.2f", float(pos)*0.01f);
	SXMaterialEditor::EditUDVSZ->SetText(roughness);

	SML_MtlSetUDVS(SXMaterialEditor::IDMat, 2, float(pos)*0.01f);

	return 0;
}

LRESULT SXMaterialEditor_TrackBarUDVSW_MouseMove(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char roughness[64];
	roughness[0] = '0';

	int pos = SXMaterialEditor::TrackBarUDVSW->GetPos();
	sprintf(roughness, "%.2f", float(pos)*0.01f);
	SXMaterialEditor::EditUDVSW->SetText(roughness);

	SML_MtlSetUDVS(SXMaterialEditor::IDMat, 3, float(pos)*0.01f);

	return 0;
}

///////

LRESULT SXMaterialEditor_TrackBarUDPSX_MouseMove(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char roughness[64];
	roughness[0] = '0';

	int pos = SXMaterialEditor::TrackBarUDPSX->GetPos();
	sprintf(roughness, "%.2f", float(pos)*0.01f);
	SXMaterialEditor::EditUDPSX->SetText(roughness);

	SML_MtlSetUDPS(SXMaterialEditor::IDMat, 0, float(pos)*0.01f);

	return 0;
}

LRESULT SXMaterialEditor_TrackBarUDPSY_MouseMove(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char roughness[64];
	roughness[0] = '0';

	int pos = SXMaterialEditor::TrackBarUDPSY->GetPos();
	sprintf(roughness, "%.2f", float(pos)*0.01f);
	SXMaterialEditor::EditUDPSY->SetText(roughness);

	SML_MtlSetUDPS(SXMaterialEditor::IDMat, 1, float(pos)*0.01f);

	return 0;
}

LRESULT SXMaterialEditor_TrackBarUDPSZ_MouseMove(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char roughness[64];
	roughness[0] = '0';

	int pos = SXMaterialEditor::TrackBarUDPSZ->GetPos();
	sprintf(roughness, "%.2f", float(pos)*0.01f);
	SXMaterialEditor::EditUDPSZ->SetText(roughness);

	SML_MtlSetUDPS(SXMaterialEditor::IDMat, 2, float(pos)*0.01f);

	return 0;
}

LRESULT SXMaterialEditor_TrackBarUDPSW_MouseMove(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char roughness[64];
	roughness[0] = '0';

	int pos = SXMaterialEditor::TrackBarUDPSW->GetPos();
	sprintf(roughness, "%.2f", float(pos)*0.01f);
	SXMaterialEditor::EditUDPSW->SetText(roughness);

	SML_MtlSetUDPS(SXMaterialEditor::IDMat, 3, float(pos)*0.01f);

	return 0;
}