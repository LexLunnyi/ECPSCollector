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
                     const wxSize& clientSize) : wxDialog(parent, wxID_ANY, caption, getDialogPos(clientSize), getDialogSize(), wxDEFAULT_DIALOG_STYLE), 
                     COMport("COM1"), speed(115200) {
    wxPoint p;
    wxSize sz(DIALOG_WIDTH - ELEM_MARGIN*3, ELEM_HEIGHT);
    
    //Output COM-port checking combobox
    p.x = ELEM_MARGIN;
    p.y = ELEM_MARGIN;
    wxStaticText* COMNumberText = new wxStaticText(this, wxID_ANY, wxT("COM-port:"), p, sz, 0 );
    p.y += ELEM_HEIGHT;
    wxArrayString COMstrings;
    COMstrings.Add(wxT("COM1"));
    COMstrings.Add(wxT("COM2"));
    comboBoxCOMPort = new wxComboBox(this, ID_COM_PORT, _(COMport.c_str()), p, sz, COMstrings, wxCB_READONLY);
    p.y += ELEM_HEIGHT;
    
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
    comboBoxSpeed = new wxComboBox(this, ID_SPEED, _(to_string(speed).c_str()), p, sz, SpeedStrings, wxCB_READONLY);    
    p.y += ELEM_HEIGHT;

    p.y += ELEM_MARGIN*2;
    sz.SetWidth((DIALOG_WIDTH - ELEM_MARGIN*4) / 2);
    wxButton* okButton = new wxButton(this, wxID_OK, _("OK"), p, sz);
    p.x += sz.GetWidth() + ELEM_MARGIN;
    wxButton* cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"), p, sz);
    
    //string debug = "Dialog pos: " + to_string(dialogPos.x) + ", height: " + to_string(dialogPos.y);
    //wxMessageBox(debug, "MENU", wxOK | wxICON_INFORMATION);
    
    Bind(wxEVT_BUTTON, &COMDialog::OnOk, this, wxID_OK);
}



void COMDialog::ReadValues() {
    wxString COMportValue = comboBoxCOMPort->GetValue();
    COMport.clear();
    COMport.assign(COMportValue.mb_str());
    
    wxString speedValue = comboBoxSpeed->GetValue();
    unsigned long tmp = 0;
    speedValue.ToULong(&tmp);
    speed = tmp;
}




void COMDialog::OnOk(wxCommandEvent & WXUNUSED(event)) {
    ReadValues();
    EndModal(wxID_OK);
}