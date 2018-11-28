#ifndef COMDIALOG_H
#define COMDIALOG_H


#include <string>
#include <iostream>
#include <sstream>

#include <wx/wx.h>
#include <wx/combobox.h>

using namespace std;


enum {
    ID_COM_PORT  = 10000,
    ID_SPEED     = 10001
};


inline string to_string(int i) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}


class COMDialog: public wxDialog {
private:
    static const int DIALOG_WIDTH = 250;
    static const int DIALOG_HEIGHT = 210;
    static const int ELEM_HEIGHT = 25;
    static const int ELEM_MARGIN = 10;
    
    wxComboBox* comboBoxCOMPort = NULL;
    wxComboBox* comboBoxSpeed = NULL;
    
    wxSize getDialogSize();
    wxPoint getDialogPos(const wxSize& clientSize);
    
    void ReadValues();
    void OnOk(wxCommandEvent & event);
public:
    string COMport;
    unsigned int speed;
    
    COMDialog(wxWindow* parent, const wxString& caption, const wxSize& clientSize);
};


#endif /* COMDIALOG_H */

