#ifndef MAINFORM_H
#define MAINFORM_H

#include <wx/wx.h>


class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);
private:
    void OnCOMOpen(wxCommandEvent& event);
    void OnCOMClose(wxCommandEvent& event);
    void OnFileSave(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};



class MyForm : public wxApp {
public:
    virtual bool OnInit();
};





#endif /* MAINFORM_H */

