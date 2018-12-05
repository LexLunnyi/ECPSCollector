#include "mainform.h"



enum {
    ID_COM_OPEN  = 1,
    ID_COM_CLOSE = 2,
    ID_FILE_SAVE = 3
};

wxIMPLEMENT_APP(MyForm);



MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title) {
    wxMenu *menuFile = new wxMenu;
    openItem = menuFile->Append(ID_COM_OPEN, "&Open COM-port\tCtrl-O", "Open COM-port");
    openItem->Enable(true);
    closeItem = menuFile->Append(ID_COM_CLOSE, "&Close COM-port\tCtrl-C", "Close COM-port");
    closeItem->Enable(false);
    menuFile->AppendSeparator();
    saveItem = menuFile->Append(ID_FILE_SAVE, "&Save results ...\tCtrl-S", "Save results");
    saveItem->Enable(false);
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
    
    //Bind(wxEVT_SIZE, &MyFrame::OnResize, this, wxID_RESIZE_FRAME);
    //this->Append(wxID_RESIZE_FRAME);
    //Bind(wxEVT_PAINT, &MyFrame::OnResize, this, wxID_RESIZE_FRAME);
    //string debug = "COM-port: " + dialog.COMport + "; speed: " + to_string(dialog.speed);
    //wxMessageBox(debug, "MENU", wxOK | wxICON_INFORMATION);
}




MyFrame::~MyFrame() {
    if (pCOMReader != NULL) delete pCOMReader;
}





void MyFrame::OnExit(wxCommandEvent& WXUNUSED(event)) {
    Close(true);
}



void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event)) {
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}


void MyFrame::OnResize(wxCommandEvent& WXUNUSED(event)) {
    paintTest();
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




void MyFrame::OnCOMOpen(wxCommandEvent& WXUNUSED(event)) {
    paintTest();
    
    vector<string> COMs;
    COMReader::getList(COMs);
    
    if (COMs.size() < 1) {
        wxMessageBox("No COM-ports found", "Warning", wxOK | wxICON_INFORMATION);
        return;
    }

    wxSize curSize = GetClientSize();
    COMDialog dialog(this, wxT("Open COM-port"), curSize, COMs);
    if (dialog.ShowModal() == wxID_OK) {
        //Try to open COM-port and read data
        string error = "";
        pCOMReader = new COMReader(dialog.COMport, dialog.speed, error);
        if (error.size() < 1) {
            openItem->Enable(false);
            closeItem->Enable(true);
            saveItem->Enable(true);
            SetStatusText("COM-port was opened: " + dialog.COMport + " -> " + to_string(dialog.speed));
        } else {
            string mes = "ERROR open COM-port " + dialog.COMport + " -> " + to_string(dialog.speed) + ": " + error;
            wxMessageBox(mes, "ERROR", wxOK | wxICON_INFORMATION);
            SetStatusText(mes);
        }
    }
}




void MyFrame::OnCOMClose(wxCommandEvent& WXUNUSED(event)) {
    if (pCOMReader != NULL) delete pCOMReader;
    
    //Close COM-port
    openItem->Enable(true);
    closeItem->Enable(false);
    //If there is data, then enable this item
    saveItem->Enable(true);
    
    SetStatusText("COM-port was closed!");
}



void MyFrame::OnFileSave(wxCommandEvent& WXUNUSED(event)) {
    wxMessageBox("File save", "MENU", wxOK | wxICON_INFORMATION);    
    SetStatusText("Results were saved!");
}



bool MyForm::OnInit() {
    MyFrame *frame = new MyFrame(wxT("ECPS Collector"));
    frame->Show(true);
    frame->Maximize(true);
    frame->paintTest();
    return true;
}