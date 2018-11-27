#include "comdialog.h"


wxSize COMDialog::getDialogSize() {
    wxSize dialogSize(DIALOG_WIDTH, DIALOG_HEIGHT);
    return dialogSize;
}


wxPoint COMDialog::getDialogPos(const wxSize& clientSize) {
    wxPoint dialogPos((clientSize.GetWidth() - DIALOG_WIDTH)/2, (clientSize.GetHeight() - DIALOG_HEIGHT)/2);
    return dialogPos;
}



COMDialog::COMDialog(wxWindow* parent, 
                     const wxString& caption, 
                     const wxSize& clientSize) : wxDialog(parent, wxID_ANY, caption, getDialogPos(clientSize), getDialogSize(), wxDEFAULT_DIALOG_STYLE) {
    wxPoint p;
    wxSize sz(DIALOG_WIDTH - ELEM_MARGIN*2, ELEM_MARGIN*2);
    
    //Output COM-port checking combobox
    p.x = ELEM_MARGIN;
    p.y = ELEM_MARGIN;
    wxStaticText* COMNumberText = new wxStaticText(this, wxID_ANY, wxT("COM-port:"), p, sz, 0 );
    p.y += ELEM_HEIGHT;
    wxArrayString COMstrings;
    COMstrings.Add(wxT("COM1"));
    COMstrings.Add(wxT("COM2"));
    wxComboBox* COMPortCombo = new wxComboBox(this, wxID_ANY, wxT("COM1"), p, sz, COMstrings, wxCB_READONLY);
    
    //Output COM-port speed checking combobox
    p.y += ELEM_MARGIN;
    wxStaticText* SpeedText = new wxStaticText(this, wxID_ANY, wxT("Speed:"), p, sz, 0 );
    p.y += ELEM_HEIGHT;
    wxArrayString SpeedStrings;
    SpeedStrings.Add(wxT("1200"));
    SpeedStrings.Add(wxT("2400"));
    SpeedStrings.Add(wxT("4800"));
    SpeedStrings.Add(wxT("9600"));
    SpeedStrings.Add(wxT("19200"));
    SpeedStrings.Add(wxT("38400"));
    SpeedStrings.Add(wxT("57600"));
    SpeedStrings.Add(wxT("115200"));
    wxComboBox* SpeedCombo = new wxComboBox(this, wxID_ANY, wxT("COM1"), p, sz, SpeedStrings, wxCB_READONLY);    

    p.y += ELEM_MARGIN;
    wxButton* okButton = new wxButton(this, wxID_OK, _("OK"), p, wxDefaultSize);
    p.x += 110;
    wxButton* cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"), p, wxDefaultSize);
    
    //string debug = "Dialog pos: " + to_string(dialogPos.x) + ", height: " + to_string(dialogPos.y);
    //wxMessageBox(debug, "MENU", wxOK | wxICON_INFORMATION);
}