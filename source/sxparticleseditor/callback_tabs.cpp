
LRESULT SXParticlesEditor_ButtonBase_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	SXParticlesEditor::AllInTabsVisible(false);
	SXParticlesEditor::BaseVisible(true);
	if (SXParticlesEditor::SelEmitterID < 0)
		SXParticlesEditor::ButtonEmitterCreate->Visible(true);
	//SXParticlesEditor::BaseNulling();
	return 0;
}

LRESULT SXParticlesEditor_ButtonTextureAnimTex_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	SXParticlesEditor::AllInTabsVisible(false);
	SXParticlesEditor::TexVisible(true);
	if (SXParticlesEditor::SelEmitterID < 0)
		SXParticlesEditor::ButtonEmitterCreate->Visible(true);
	//SXParticlesEditor::TexNulling();
	return 0;
}

LRESULT SXParticlesEditor_ButtonSpawn_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	SXParticlesEditor::AllInTabsVisible(false);
	SXParticlesEditor::SpawnVisible(true);
	if (SXParticlesEditor::SelEmitterID < 0)
		SXParticlesEditor::ButtonEmitterCreate->Visible(true);
	//SXParticlesEditor::SpawnNulling();
	return 0;
}

LRESULT SXParticlesEditor_ButtonBound_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	SXParticlesEditor::AllInTabsVisible(false);
	SXParticlesEditor::BoundVisible(true);
	if (SXParticlesEditor::SelEmitterID < 0)
		SXParticlesEditor::ButtonEmitterCreate->Visible(true);
	//SXParticlesEditor::BoundNulling();
	return 0;
}

LRESULT SXParticlesEditor_ButtonCharacters_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	SXParticlesEditor::AllInTabsVisible(false);
	SXParticlesEditor::CharacterVisible(true);
	if (SXParticlesEditor::SelEmitterID < 0)
		SXParticlesEditor::ButtonEmitterCreate->Visible(true);
	//SXParticlesEditor::CharacterNulling();
	return 0;
}

LRESULT SXParticlesEditor_ButtonVelocityAcceleration_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	SXParticlesEditor::AllInTabsVisible(false);
	SXParticlesEditor::VelocityAccVisible(true);
	if (SXParticlesEditor::SelEmitterID < 0)
		SXParticlesEditor::ButtonEmitterCreate->Visible(true);
	//SXParticlesEditor::VelocityAccNulling();
	return 0;
}