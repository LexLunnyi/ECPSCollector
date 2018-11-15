#ifndef MAINFORM_H
#define MAINFORM_H

#include <wx/wx.h>


class MyFrame : public wxFrame {
public:
    MyFrame();
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};



class MyForm : public wxApp {
public:
    virtual bool OnInit();
};





#endif /* MAINFORM_H */

