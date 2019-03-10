#ifndef MAINFORM_H
#define MAINFORM_H

#include <wx/wx.h>
#include <list>
#include <wx/event.h>

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
    wxStaticText* ECGLabel = NULL;
    PMyGraph SpiroGraph = NULL;
    wxStaticText* SpiroLabel = NULL;
    PMyGraph PlethysmoGraph = NULL;
    wxStaticText* PlethysmoLabel = NULL;
    
    wxPen* pCustomPen = NULL;
    wxBrush* pCustomBrush = NULL;
    
    void emptyGraphs();
    void calcGraphPosition(uint32_t index, GraphSize & size);
    
    void OnCOMOpen(wxCommandEvent& event);
    void OnCOMClose(wxCommandEvent& event);
    void OnFileSave(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnResize(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    void OnTimerEx(wxTimerEvent& event);
    void OnCreate(wxWindowCreateEvent& event);
    void OnShow(wxShowEvent& event);
    void OnPaint(wxPaintEvent& event);
};



class MyForm : public wxApp {
public:
    virtual bool OnInit();
};





#endif /* MAINFORM_H */

