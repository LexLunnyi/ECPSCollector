#include "mainform.h"


enum {
    ID_COM_OPEN = 1,
    ID_COM_CLOSE = 2,
    ID_FILE_SAVE = 3
};

wxIMPLEMENT_APP(MyForm);



MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title) {
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_COM_OPEN, "&Open COM-port\tCtrl-O", "Open COM-port");
    menuFile->Append(ID_COM_CLOSE, "&Close COM-port\tCtrl-C", "Close COM-port");
    menuFile->AppendSeparator();
    menuFile->Append(ID_FILE_SAVE, "&Save results ...\tCtrl-S", "Save results");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("COM-port is closed!");
    
    Bind(wxEVT_MENU, &MyFrame::OnCOMOpen, this, ID_COM_OPEN);
    Bind(wxEVT_MENU, &MyFrame::OnCOMClose, this, ID_COM_CLOSE);
    Bind(wxEVT_MENU, &MyFrame::OnFileSave, this, ID_FILE_SAVE);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}


void MyFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}



void MyFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}




void MyFrame::OnCOMOpen(wxCommandEvent& event) {
    wxMessageBox("COM Open", "MENU", wxOK | wxICON_INFORMATION);
    
    SetStatusText("COM-port was opened!");
}


void MyFrame::OnCOMClose(wxCommandEvent& event) {
    wxMessageBox("COM Close", "MENU", wxOK | wxICON_INFORMATION);
    
    SetStatusText("COM-port was closed!");
}


void MyFrame::OnFileSave(wxCommandEvent& event) {
    wxMessageBox("File save", "MENU", wxOK | wxICON_INFORMATION);
    
    SetStatusText("Results were saved!");
}



bool MyForm::OnInit() {
    MyFrame *frame = new MyFrame(wxT("ECPS Collector"));
    frame->Show(true);
    return true;
}