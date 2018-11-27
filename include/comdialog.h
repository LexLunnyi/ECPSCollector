#ifndef COMDIALOG_H
#define COMDIALOG_H


#include <string>
#include <iostream>
#include <sstream>

#include <wx/wx.h>
#include <wx/combobox.h>

using namespace std;



inline string to_string(int i) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}


class COMDialog: public wxDialog {
private:
    static const int DIALOG_WIDTH = 400;
    static const int DIALOG_HEIGHT = 200;
    static const int ELEM_HEIGHT = 25;
    static const int ELEM_MARGIN = 10;
    
    wxSize getDialogSize();
    wxPoint getDialogPos(const wxSize& clientSize);    
public:
    COMDialog(wxWindow* parent, const wxString& caption, const wxSize& clientSize);
};


#endif /* COMDIALOG_H */

