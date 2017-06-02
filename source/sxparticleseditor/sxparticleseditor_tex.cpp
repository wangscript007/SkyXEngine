#define mem_delete(p) if(p) {delete (p);(p) = NULL;}

namespace SXParticlesEditor
{
	ISXGUIBaseWnd* JobWindow;
	ISXGUIBaseWnd* Window1;
	ISXGUIToolBar* ToolBar1;
	ISXGUIListBox* ListBox1;
	ISXGUIListBox* ListBox2;
	ISXGUIStatic* Static1;
	ISXGUIButton* Button1;
	ISXGUIStatic* Static2;
	ISXGUIButton* Button2;
	ISXGUIButton* Button3;
	ISXGUIButton* Button4;
	ISXGUIButton* Button5;
	ISXGUIButton* Button6;
	ISXGUIButton* Button7;
	ISXGUIButton* Button8;
	ISXGUIButton* Button9;
	ISXGUIButton* Button10;
	ISXGUIButton* Button11;
	ISXGUIButton* Button12;
	ISXGUIButton* Button13;
	ISXGUIStatic* StaticTexture;
	ISXGUIEdit* EditTexture;
	ISXGUIButton* ButtonTextureSel;
	ISXGUIStatic* StaticAnimTexCountCadrsX;
	ISXGUIStatic* StaticAnimTexCountCadrsY;
	ISXGUIEdit* EditAnimTexCountCadrsX;
	ISXGUIEdit* EditAnimTexCountCadrsY;
	ISXGUIStatic* StaticAnimTexRate;
	ISXGUIEdit* EditAnimTexRate;
	ISXGUIStatic* StaticAnimTexRateDisp;
	ISXGUIEdit* EditAnimTexRateDisp;
	ISXGUIStatic* StaticAnimTexStartCadr;
	ISXGUIEdit* EditAnimTexStartCadr;
	ISXGUIStatic* StaticAnimTexStartCadrDisp;
	ISXGUIEdit* EditAnimTexStartCadrDisp;

	void InitAllElements();

	void DeleteAllElements();

};

void SXParticlesEditor::InitAllElements()
{
	SXParticlesEditor::JobWindow = SXGUICrBaseWnd("JobWindow","JobWindow",0,0,237,74,820,650,0,0,CreateSolidBrush(RGB(220,220,220)),0,CS_HREDRAW | CS_VREDRAW,WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION,0,WndProcAllDefault);
	SXGUIBaseHandlers::InitHandlerMsg(SXParticlesEditor::JobWindow);

	SXParticlesEditor::Window1 = SXGUICrBaseWnd("Window1","Window1",0,0,0,25,600,400,0,0,CreateSolidBrush(RGB(200,200,200)),0,CS_HREDRAW | CS_VREDRAW,WS_CHILD | WS_VISIBLE | WS_BORDER,SXParticlesEditor::JobWindow->GetHWND(),0);
	SXParticlesEditor::ToolBar1 = SXGUICrToolBar("",0,1,804,24,804,24,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::ListBox1 = SXGUICrListBox("",602,50,200,145,SXParticlesEditor::JobWindow->GetHWND(),0,0,true);
	SXParticlesEditor::ListBox1->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::ListBox1->SetColorText(0,0,0);
	SXParticlesEditor::ListBox1->SetColorTextBk(255,255,255);
	SXParticlesEditor::ListBox1->SetTransparentTextBk(true);
	SXParticlesEditor::ListBox1->SetColorBrush(255,255,255);
	SXParticlesEditor::ListBox2 = SXGUICrListBox("",602,300,200,54,SXParticlesEditor::JobWindow->GetHWND(),0,0,true);
	SXParticlesEditor::ListBox2->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::ListBox2->SetColorText(0,0,0);
	SXParticlesEditor::ListBox2->SetColorTextBk(255,255,255);
	SXParticlesEditor::ListBox2->SetTransparentTextBk(true);
	SXParticlesEditor::ListBox2->SetColorBrush(255,255,255);
	SXParticlesEditor::Static1 = SXGUICrStatic("Effects:",610,30,50,15,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::Static1->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::Static1->SetColorText(0,0,0);
	SXParticlesEditor::Static1->SetColorTextBk(255,255,255);
	SXParticlesEditor::Static1->SetTransparentTextBk(true);
	SXParticlesEditor::Static1->SetColorBrush(220,220,220);
	SXParticlesEditor::Button1 = SXGUICrButton("Create",605,245,60,15,0,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::Button1->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::Static2 = SXGUICrStatic("Particles:",610,275,50,15,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::Static2->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::Static2->SetColorText(0,0,0);
	SXParticlesEditor::Static2->SetColorTextBk(255,255,255);
	SXParticlesEditor::Static2->SetTransparentTextBk(true);
	SXParticlesEditor::Static2->SetColorBrush(220,220,220);
	SXParticlesEditor::Button2 = SXGUICrButton("Edit",670,245,60,15,0,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::Button2->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::Button3 = SXGUICrButton("Delete",735,245,60,15,0,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::Button3->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::Button4 = SXGUICrButton("Create",605,410,60,15,0,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::Button4->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::Button5 = SXGUICrButton("Edit",670,410,60,15,0,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::Button5->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::Button6 = SXGUICrButton("Delete",735,410,60,15,0,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::Button6->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::Button7 = SXGUICrButton("Base",25,435,100,15,0,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::Button7->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::Button8 = SXGUICrButton("TextureAnimTex",130,435,100,15,0,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::Button8->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::Button9 = SXGUICrButton("Spawn",235,435,100,15,0,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::Button9->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::Button10 = SXGUICrButton("Bound",340,435,100,15,0,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::Button10->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::Button11 = SXGUICrButton("Graphics",665,435,100,15,0,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::Button11->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::Button12 = SXGUICrButton("Charaters",560,435,100,15,0,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::Button12->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::Button13 = SXGUICrButton("VelocityAcceleration",445,434,110,15,0,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::Button13->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::StaticTexture = SXGUICrStatic("Texture:",5,460,50,15,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::StaticTexture->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::StaticTexture->SetColorText(0,0,0);
	SXParticlesEditor::StaticTexture->SetColorTextBk(255,255,255);
	SXParticlesEditor::StaticTexture->SetTransparentTextBk(true);
	SXParticlesEditor::StaticTexture->SetColorBrush(220,220,220);
	SXParticlesEditor::EditTexture = SXGUICrEdit("0",60,460,290,15,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::EditTexture->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::EditTexture->SetColorText(0,0,0);
	SXParticlesEditor::EditTexture->SetColorTextBk(255,255,255);
	SXParticlesEditor::EditTexture->SetTransparentTextBk(true);
	SXParticlesEditor::EditTexture->SetColorBrush(255,255,255);
	SXParticlesEditor::ButtonTextureSel = SXGUICrButton("...",355,460,25,15,0,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::ButtonTextureSel->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::StaticAnimTexCountCadrsX = SXGUICrStatic("AnimTexCountCadrsX:",5,485,110,15,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::StaticAnimTexCountCadrsX->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::StaticAnimTexCountCadrsX->SetColorText(0,0,0);
	SXParticlesEditor::StaticAnimTexCountCadrsX->SetColorTextBk(255,255,255);
	SXParticlesEditor::StaticAnimTexCountCadrsX->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAnimTexCountCadrsX->SetColorBrush(220,220,220);
	SXParticlesEditor::StaticAnimTexCountCadrsY = SXGUICrStatic("AnimTexCountCadrsY:",200,485,110,15,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::StaticAnimTexCountCadrsY->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::StaticAnimTexCountCadrsY->SetColorText(0,0,0);
	SXParticlesEditor::StaticAnimTexCountCadrsY->SetColorTextBk(255,255,255);
	SXParticlesEditor::StaticAnimTexCountCadrsY->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAnimTexCountCadrsY->SetColorBrush(220,220,220);
	SXParticlesEditor::EditAnimTexCountCadrsX = SXGUICrEdit("0",115,485,70,15,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::EditAnimTexCountCadrsX->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::EditAnimTexCountCadrsX->SetColorText(0,0,0);
	SXParticlesEditor::EditAnimTexCountCadrsX->SetColorTextBk(255,255,255);
	SXParticlesEditor::EditAnimTexCountCadrsX->SetTransparentTextBk(true);
	SXParticlesEditor::EditAnimTexCountCadrsX->SetColorBrush(255,255,255);
	SXParticlesEditor::EditAnimTexCountCadrsY = SXGUICrEdit("0",310,485,70,15,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::EditAnimTexCountCadrsY->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::EditAnimTexCountCadrsY->SetColorText(0,0,0);
	SXParticlesEditor::EditAnimTexCountCadrsY->SetColorTextBk(255,255,255);
	SXParticlesEditor::EditAnimTexCountCadrsY->SetTransparentTextBk(true);
	SXParticlesEditor::EditAnimTexCountCadrsY->SetColorBrush(255,255,255);
	SXParticlesEditor::StaticAnimTexRate = SXGUICrStatic("AnimTexRate:",5,505,100,15,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::StaticAnimTexRate->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::StaticAnimTexRate->SetColorText(0,0,0);
	SXParticlesEditor::StaticAnimTexRate->SetColorTextBk(255,255,255);
	SXParticlesEditor::StaticAnimTexRate->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAnimTexRate->SetColorBrush(220,220,220);
	SXParticlesEditor::EditAnimTexRate = SXGUICrEdit("0",115,505,70,15,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::EditAnimTexRate->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::EditAnimTexRate->SetColorText(0,0,0);
	SXParticlesEditor::EditAnimTexRate->SetColorTextBk(255,255,255);
	SXParticlesEditor::EditAnimTexRate->SetTransparentTextBk(true);
	SXParticlesEditor::EditAnimTexRate->SetColorBrush(255,255,255);
	SXParticlesEditor::StaticAnimTexRateDisp = SXGUICrStatic("AnimTexRateDisp:",200,505,100,15,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::StaticAnimTexRateDisp->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::StaticAnimTexRateDisp->SetColorText(0,0,0);
	SXParticlesEditor::StaticAnimTexRateDisp->SetColorTextBk(255,255,255);
	SXParticlesEditor::StaticAnimTexRateDisp->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAnimTexRateDisp->SetColorBrush(220,220,220);
	SXParticlesEditor::EditAnimTexRateDisp = SXGUICrEdit("0",310,505,70,15,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::EditAnimTexRateDisp->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::EditAnimTexRateDisp->SetColorText(0,0,0);
	SXParticlesEditor::EditAnimTexRateDisp->SetColorTextBk(255,255,255);
	SXParticlesEditor::EditAnimTexRateDisp->SetTransparentTextBk(true);
	SXParticlesEditor::EditAnimTexRateDisp->SetColorBrush(255,255,255);
	SXParticlesEditor::StaticAnimTexStartCadr = SXGUICrStatic("AnimTexStartCadr:",5,525,100,15,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::StaticAnimTexStartCadr->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::StaticAnimTexStartCadr->SetColorText(0,0,0);
	SXParticlesEditor::StaticAnimTexStartCadr->SetColorTextBk(255,255,255);
	SXParticlesEditor::StaticAnimTexStartCadr->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAnimTexStartCadr->SetColorBrush(220,220,220);
	SXParticlesEditor::EditAnimTexStartCadr = SXGUICrEdit("0",115,525,70,15,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::EditAnimTexStartCadr->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::EditAnimTexStartCadr->SetColorText(0,0,0);
	SXParticlesEditor::EditAnimTexStartCadr->SetColorTextBk(255,255,255);
	SXParticlesEditor::EditAnimTexStartCadr->SetTransparentTextBk(true);
	SXParticlesEditor::EditAnimTexStartCadr->SetColorBrush(255,255,255);
	SXParticlesEditor::StaticAnimTexStartCadrDisp = SXGUICrStatic("AnimTexStartCadrDisp:",200,525,110,15,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::StaticAnimTexStartCadrDisp->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::StaticAnimTexStartCadrDisp->SetColorText(0,0,0);
	SXParticlesEditor::StaticAnimTexStartCadrDisp->SetColorTextBk(255,255,255);
	SXParticlesEditor::StaticAnimTexStartCadrDisp->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAnimTexStartCadrDisp->SetColorBrush(220,220,220);
	SXParticlesEditor::EditAnimTexStartCadrDisp = SXGUICrEdit("0",310,525,70,15,SXParticlesEditor::JobWindow->GetHWND(),0,0);
	SXParticlesEditor::EditAnimTexStartCadrDisp->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::EditAnimTexStartCadrDisp->SetColorText(0,0,0);
	SXParticlesEditor::EditAnimTexStartCadrDisp->SetColorTextBk(255,255,255);
	SXParticlesEditor::EditAnimTexStartCadrDisp->SetTransparentTextBk(true);
	SXParticlesEditor::EditAnimTexStartCadrDisp->SetColorBrush(255,255,255);
}
void SXParticlesEditor::DeleteAllElements()
{
	mem_delete(SXParticlesEditor::Window1);
	mem_delete(SXParticlesEditor::ToolBar1);
	mem_delete(SXParticlesEditor::ListBox1);
	mem_delete(SXParticlesEditor::ListBox2);
	mem_delete(SXParticlesEditor::Static1);
	mem_delete(SXParticlesEditor::Button1);
	mem_delete(SXParticlesEditor::Static2);
	mem_delete(SXParticlesEditor::Button2);
	mem_delete(SXParticlesEditor::Button3);
	mem_delete(SXParticlesEditor::Button4);
	mem_delete(SXParticlesEditor::Button5);
	mem_delete(SXParticlesEditor::Button6);
	mem_delete(SXParticlesEditor::Button7);
	mem_delete(SXParticlesEditor::Button8);
	mem_delete(SXParticlesEditor::Button9);
	mem_delete(SXParticlesEditor::Button10);
	mem_delete(SXParticlesEditor::Button11);
	mem_delete(SXParticlesEditor::Button12);
	mem_delete(SXParticlesEditor::Button13);
	mem_delete(SXParticlesEditor::StaticTexture);
	mem_delete(SXParticlesEditor::EditTexture);
	mem_delete(SXParticlesEditor::ButtonTextureSel);
	mem_delete(SXParticlesEditor::StaticAnimTexCountCadrsX);
	mem_delete(SXParticlesEditor::StaticAnimTexCountCadrsY);
	mem_delete(SXParticlesEditor::EditAnimTexCountCadrsX);
	mem_delete(SXParticlesEditor::EditAnimTexCountCadrsY);
	mem_delete(SXParticlesEditor::StaticAnimTexRate);
	mem_delete(SXParticlesEditor::EditAnimTexRate);
	mem_delete(SXParticlesEditor::StaticAnimTexRateDisp);
	mem_delete(SXParticlesEditor::EditAnimTexRateDisp);
	mem_delete(SXParticlesEditor::StaticAnimTexStartCadr);
	mem_delete(SXParticlesEditor::EditAnimTexStartCadr);
	mem_delete(SXParticlesEditor::StaticAnimTexStartCadrDisp);
	mem_delete(SXParticlesEditor::EditAnimTexStartCadrDisp);
	mem_delete(SXParticlesEditor::JobWindow);
}
