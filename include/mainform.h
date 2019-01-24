#ifndef MAINFORM_H
#define MAINFORM_H

#include <wx/wx.h>
#include <list>

#include "graph.h"
#include "comdialog.h"
#include "comreader.h"
#include "functions.h"
#include "chunk.h"


using namespace ecps;


class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);
    ~MyFrame();
    
    void paintTest();
private:
    bool test = false;
    static const uint32_t GRAPHS_GAP = 50;
    wxTimer readTimer;
    list<PChunk> graphsData;
    uint16_t maxSpiro = 0;
    
    bool fDebug = true;
    
    wxMenuItem* openItem = NULL;
    wxMenuItem* closeItem = NULL;
    wxMenuItem* saveItem = NULL;
    
    PCOMReader pCOMReader = NULL;
    
    PMyGraph ECGGraph = NULL;
    PMyGraph SpiroGraph = NULL;
    PMyGraph PhotoGraph = NULL;
    
    void calcGraphPosition(uint32_t index, uint32_t* x, uint32_t* y, uint32_t* w, uint32_t* h);
    
    void OnCOMOpen(wxCommandEvent& event);
    void OnCOMClose(wxCommandEvent& event);
    void OnFileSave(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnResize(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    void emptyGraphs();
};



class MyForm : public wxApp {
public:
    virtual bool OnInit();
};





#endif /* MAINFORM_H */

