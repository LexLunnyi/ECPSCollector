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




void MyFrame::calcGraphPosition(uint32_t index, uint32_t* x, uint32_t* y, uint32_t* w, uint32_t* h) {
    wxSize sz = GetClientSize();
    *w = wxMax(0, sz.GetWidth() - GRAPHS_GAP * 2);
    *h = wxMax(0, sz.GetHeight() - GRAPHS_GAP * 4) / 3;
    *x = GRAPHS_GAP;
    *y = GRAPHS_GAP + (*h + GRAPHS_GAP)*index;
}



void MyFrame::paintTest() {
    uint32_t x, y, w, h;
    
    calcGraphPosition(0, &x, &y, &w, &h);

    MyGraph ECGraph(this, wxBLACK_PEN, wxWHITE_BRUSH);
    ECGraph.render(x, y, w, h);
    
    calcGraphPosition(1, &x, &y, &w, &h);
    MyGraph PhoneGraph(this, wxBLACK_PEN, wxWHITE_BRUSH);
    PhoneGraph.render(x, y, w, h);
    
    calcGraphPosition(2, &x, &y, &w, &h);
    MyGraph PlethysmoGraph(this, wxBLACK_PEN, wxWHITE_BRUSH);
    PlethysmoGraph.render(x, y, w, h);
    
    //wxMessageBox(debug, "DEBUG", wxOK | wxICON_INFORMATION);
}







void MyFrame::OnCOMOpen(wxCommandEvent& event) {
    paintTest();
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
    frame->Maximize(true) ;
    //frame->ShowFullScreen(true, wxSTAY_ON_TOP);
    //frame->Show(true);
    return true;
}