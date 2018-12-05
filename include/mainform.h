#ifndef MAINFORM_H
#define MAINFORM_H

#include <wx/wx.h>

#include "graph.h"
#include "comdialog.h"
#include "comreader.h"

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);
    ~MyFrame();
    
    void paintTest();
private:
    static const uint32_t GRAPHS_GAP = 50;
    
    wxMenuItem* openItem = NULL;
    wxMenuItem* closeItem = NULL;
    wxMenuItem* saveItem = NULL;
    
    PCOMReader pCOMReader = NULL;
    
    void calcGraphPosition(uint32_t index, uint32_t* x, uint32_t* y, uint32_t* w, uint32_t* h);
    
    void OnCOMOpen(wxCommandEvent& event);
    void OnCOMClose(wxCommandEvent& event);
    void OnFileSave(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnResize(wxCommandEvent& event);
};



class MyForm : public wxApp {
public:
    virtual bool OnInit();
};





#endif /* MAINFORM_H */

