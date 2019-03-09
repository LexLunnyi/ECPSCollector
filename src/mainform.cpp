#include "mainform.h"



enum {
    ID_COM_OPEN  = 1,
    ID_COM_CLOSE = 2,
    ID_FILE_SAVE = 3,
    ID_TIMER     = 4,
    ID_CREATE    = 5,
    ID_ECG_GRAPH_LABEL       = 20000,
    ID_SPIRO_GRAPH_LABEL     = 20001,
    ID_PLETHYSMO_GRAPH_LABEL = 20002
};

wxIMPLEMENT_APP(MyForm);



MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title), readTimer(this, ID_TIMER) {
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
    Bind(wxEVT_TIMER, &MyFrame::OnTimer, this, ID_TIMER);
    
    //Bind(wxEVT_CREATE, &MyFrame::OnCreate, this, wxID_ANY);
    //Connect(wxEVT_CREATE, wxWindowCreateEventHandler(MyFrame::OnCreate));
    //Connect(wxEVT_SHOW, wxShowEventHandler(MyFrame::OnShow));
    
    wxPoint p(-100, -100);
    wxSize sz(100, 25);
    ECGLabel = new wxStaticText(this, wxID_ANY, wxT("Electrocardiogram:"), p, sz, 0 );
    SpiroLabel = new wxStaticText(this, wxID_ANY, wxT("Spirogram:"), p, sz, 0 );
    PlethysmoLabel = new wxStaticText(this, wxID_ANY, wxT("Plethysmogram:"), p, sz, 0 );
    ECGGraph = new MyGraph(this, wxBLACK_PEN, wxWHITE_BRUSH);
    SpiroGraph = new MyGraph(this, wxBLACK_PEN, wxWHITE_BRUSH);
    PlethysmoGraph = new MyGraph(this, wxBLACK_PEN, wxWHITE_BRUSH);
    
    Connect(wxEVT_PAINT, wxPaintEventHandler(MyFrame::OnPaint));
// wxWindowCreateEvent

    readTimer.Start(1000);
}





void MyFrame::createGraphs() {
    wxPoint p;
    GraphSize ecgSize, spiroSize, plethysmoSize;

    this->ClearBackground();
    
    calcGraphPosition(0, ecgSize);
    p.x = ecgSize.x; p.y = ecgSize.y - 30; 
    ECGLabel->SetPosition(p);
    calcGraphPosition(1, spiroSize);
    p.x = spiroSize.x; p.y = spiroSize.y - 30;
    SpiroLabel->SetPosition(p);
    calcGraphPosition(2, plethysmoSize);
    p.x = plethysmoSize.x; p.y = plethysmoSize.y - 30;
    PlethysmoLabel->SetPosition(p);
  
    ECGGraph->render(ecgSize);
    SpiroGraph->render(spiroSize);
    PlethysmoGraph->render(plethysmoSize);
}


void MyFrame::OnCreate(wxWindowCreateEvent& WXUNUSED(event)) {
    wxMessageBox("Creating window test", "Test", wxOK | wxICON_INFORMATION);
    createGraphs();
}



void MyFrame::OnShow(wxShowEvent& WXUNUSED(event)) {
    wxMessageBox("Show window test", "Test", wxOK | wxICON_INFORMATION);
    createGraphs();
}


void MyFrame::OnPaint(wxPaintEvent& WXUNUSED(event)) {
    //wxMessageBox("Paint window test", "Test", wxOK | wxICON_INFORMATION);
    createGraphs();
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
    //paintTest();
}




void MyFrame::calcGraphPosition(uint32_t index, GraphSize & size) {
    wxSize sz = GetClientSize();
    size.width = wxMax(0, sz.GetWidth() - GRAPHS_GAP * 2);
    size.height = wxMax(0, sz.GetHeight() - GRAPHS_GAP * 4) / 3;
    size.x = GRAPHS_GAP;
    size.y = GRAPHS_GAP + (size.height + GRAPHS_GAP)*index;
}







void MyFrame::OnCOMOpen(wxCommandEvent& WXUNUSED(event)) {
    //wxWindowCreateEvent evt;
    //OnCreate(evt);
    
    vector<string> COMs;
    COMReader::getList(COMs);
    
    if (COMs.size() < 1) {
        wxMessageBox("No COM-ports found", "Warning", wxOK | wxICON_INFORMATION);
        return;
    }

    wxSize curSize = GetClientSize();
    COMDialog dialog(this, wxT("Open COM-port"), curSize, COMs);
    if (dialog.ShowModal() == wxID_OK) {
        fDebug = true;
        //Try to open COM-port and read data
        string error = "";
        pCOMReader = new COMReader(dialog.COMport, dialog.speed, error);
        if (error.size() < 1) {
            openItem->Enable(false);
            closeItem->Enable(true);
            saveItem->Enable(true);
            SetStatusText("COM-port was opened: " + dialog.COMport + " -> " + to_string(dialog.speed));
            graphsData.clear();
            Chunk::initValue = true;
        } else {
            string mes = "ERROR open COM-port " + dialog.COMport + " -> " + to_string(dialog.speed) + ": " + error;
            wxMessageBox(mes, "ERROR", wxOK | wxICON_INFORMATION);
            SetStatusText(mes);
        }
    }
}




void MyFrame::OnCOMClose(wxCommandEvent& WXUNUSED(event)) {
    if (pCOMReader != NULL) {
        delete pCOMReader;
        pCOMReader = NULL;
    }
    
    delete ECGGraph;
    delete SpiroGraph;
    delete PlethysmoGraph;
    
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
    return true;
}



void MyFrame::OnTimer(wxTimerEvent& WXUNUSED(event)) {
    if (pCOMReader == NULL) return;
    
    bool updated = false;
    unsigned int size = pCOMReader->getChunks(graphsData, updated);
    if (size < 1) return;

    //string debug = "Queue size -> " + ecps::to_string((int)size) + "; ";
    if (updated) createGraphs();
    int cnt = 0;
    bool first = true;

    uint16_t minSpiro = 0; uint16_t maxSpiro = 0;
    double spiroScale = (double)(Chunk::maxSpiro - Chunk::minSpiro) / (double)SpiroGraph->getHeight();
    uint16_t curSpiroY = 0; uint16_t nextSpiroY = 0;
    
    int16_t minPhoto = 0; int16_t maxPhoto = 0;
    double photoScale = (double)(Chunk::maxPhoto - Chunk::minPhoto) / (double)PlethysmoGraph->getHeight();
    uint16_t curPhotoY = 0; uint16_t nextPhotoY = 0;
    
    uint16_t minECG = 0; uint16_t maxECG = 0;
    double ecgScale = (double)(Chunk::maxECG - Chunk::minECG) / (double)ECGGraph->getHeight();
    uint16_t curECGY = 0; uint16_t nextECGY = 0;
    
    
    for(auto& data: graphsData) {
        cnt++;
        uint16_t spiro = data->spiro;
        int16_t photo = data->photo;
        uint16_t ecg = data->ecg;
        
        if (first) {
            maxSpiro = spiro; minSpiro = spiro;
            maxPhoto = photo; minPhoto = photo;
            maxECG = ecg;     minECG = ecg;
            first = false;
        } else {
            if (spiro < minSpiro) minSpiro = spiro; if (spiro > maxSpiro) maxSpiro = spiro;
            if (photo < minPhoto) minPhoto = photo; if (photo > maxPhoto) maxPhoto = photo;
            if (ecg < minECG) minECG = ecg;         if (ecg > maxECG) maxECG = ecg;
        }
        nextSpiroY = (spiro - Chunk::minSpiro)/spiroScale;
        nextPhotoY = (photo - Chunk::minPhoto)/photoScale;
        nextECGY = (ecg - Chunk::minECG)/ecgScale;

        //Paint line from cur to next
        SpiroGraph->line(cnt-1, curSpiroY, cnt, nextSpiroY);
        PlethysmoGraph->line(cnt-1, curPhotoY, cnt, nextPhotoY);
        ECGGraph->line(cnt-1, curECGY, cnt, nextECGY);
        
        curSpiroY = nextSpiroY;
        curPhotoY = nextPhotoY;
        curECGY = nextECGY;
    }
    
    Chunk::setSpiroBorders(minSpiro, maxSpiro);
    Chunk::setPhotoBorders(minPhoto, maxPhoto);
    Chunk::setECGBorders(minECG, maxECG);
    
    /*
    if (fDebug) {
        fDebug = false;
        string debug = "max: " + ecps::to_string(Chunk::maxSpiro) + "; min: " + ecps::to_string(Chunk::minSpiro) + "; h: " + ecps::to_string(SpiroGraph->getHeight());
        wxMessageBox(debug, "MENU", wxOK | wxICON_INFORMATION);
    }
    */
}