#include <wx/filename.h>
#include <wx/colour.h>
#include <wx/image.h>
#include <string>

#include<iostream> // SCS 22.09.

#include "chatbot.h"
#include "chatlogic.h"
#include "chatgui.h"

// size of chatbot window
const int width = 414;
const int height = 736;

// wxWidgets APP
IMPLEMENT_APP(ChatBotApp);

std::string dataPath = "../";
std::string imgBasePath = dataPath + "images/";

bool ChatBotApp::OnInit()
{
    // create window with name and show it
    ChatBotFrame *chatBotFrame = new ChatBotFrame(wxT("Udacity ChatBot"));
    chatBotFrame->Show(true);
    return true;
}

// wxWidgets FRAME
ChatBotFrame::ChatBotFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(width, height))
{
    std::cout << "ChatBotFrame constructor is called " <<std::endl; // SCS debug
    // create panel with background image
    ChatBotFrameImagePanel *ctrlPanel = new ChatBotFrameImagePanel(this);

    // create controls and assign them to control panel
    _panelDialog = new ChatBotPanelDialog(ctrlPanel, wxID_ANY);

    // create text control for user input
    int idTextXtrl = 1;
    _userTextCtrl = new wxTextCtrl(ctrlPanel, idTextXtrl, "", wxDefaultPosition, wxSize(width, 50), wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
    Connect(idTextXtrl, wxEVT_TEXT_ENTER, wxCommandEventHandler(ChatBotFrame::OnEnter));

    // create vertical sizer for panel alignment and add panels
    wxBoxSizer *vertBoxSizer = new wxBoxSizer(wxVERTICAL);
    vertBoxSizer->AddSpacer(90);
    vertBoxSizer->Add(_panelDialog, 6, wxEXPAND | wxALL, 0);
    vertBoxSizer->Add(_userTextCtrl, 1, wxEXPAND | wxALL, 5);
    ctrlPanel->SetSizer(vertBoxSizer);

    // position window in screen center
    this->Centre();
}

ChatBotFrame::~ChatBotFrame() { // SCS 22.09.
   std::cout << "ChatBotFrame destructor is called " <<std::endl; // SCS debug
    if (_panelDialog != NULL) {
      
   std::cout << "ChatBotFrame destructor _panelDialog deleted" <<std::endl; // SCS debug
        delete _panelDialog;
        _panelDialog = NULL;
    }
      if (_userTextCtrl  != NULL) {
        
   std::cout << "ChatBotFrame destructor _userText deleted" <<std::endl; // SCS debug
        delete _userTextCtrl ;
        _userTextCtrl = NULL;
    }
}

void ChatBotFrame::OnEnter(wxCommandEvent &WXUNUSED(event))
{
  
       std::cout << "OnEnter Start " << std::endl; // SCS debug
    // retrieve text from text control
    wxString userText = _userTextCtrl->GetLineText(0);

       std::cout << "OnEnter UserText: " << userText << std::endl; // SCS debug
    // add new user text to dialog
    _panelDialog->AddDialogItem(userText, true);

       std::cout << "OnEnter AddDialogItem" << std::endl; // SCS debug
    // delete text in text control
    _userTextCtrl->Clear();

       std::cout << "OnEnter UserTextCtrl->Clear() " << userText << std::endl; // SCS debug
    // send user text to chatbot 
    _panelDialog->GetChatLogicHandle()->SendMessageToChatbot(std::string(userText.mb_str())); 
  
       std::cout << "OnEnter End " << std::endl; // SCS debug
}

BEGIN_EVENT_TABLE(ChatBotFrameImagePanel, wxPanel)
EVT_PAINT(ChatBotFrameImagePanel::paintEvent) // catch paint events
END_EVENT_TABLE()

ChatBotFrameImagePanel::ChatBotFrameImagePanel(wxFrame *parent) : wxPanel(parent)

{
       std::cout << "ChatBotFrameImagePanel constructor is called " <<std::endl; // SCS debug


}

ChatBotFrameImagePanel::~ChatBotFrameImagePanel() // SCS 22.09.
{
       std::cout << "ChatBotFrameImagePanel destructor is called " <<std::endl; // SCS debug
   
}


void ChatBotFrameImagePanel::paintEvent(wxPaintEvent &evt)
{
    wxPaintDC dc(this);
    render(dc);
}

void ChatBotFrameImagePanel::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

void ChatBotFrameImagePanel::render(wxDC &dc)
{
    // load backgroud image from file
    wxString imgFile = imgBasePath + "sf_bridge.jpg";
    wxImage image;
    image.LoadFile(imgFile);

    // rescale image to fit window dimensions
    wxSize sz = this->GetSize();
    wxImage imgSmall = image.Rescale(sz.GetWidth(), sz.GetHeight(), wxIMAGE_QUALITY_HIGH);
    _image = wxBitmap(imgSmall);
    
    dc.DrawBitmap(_image, 0, 0, false);
}

BEGIN_EVENT_TABLE(ChatBotPanelDialog, wxPanel)
EVT_PAINT(ChatBotPanelDialog::paintEvent) // catch paint events
END_EVENT_TABLE()

ChatBotPanelDialog::ChatBotPanelDialog(wxWindow *parent, wxWindowID id)
    : wxScrolledWindow(parent, id)
{
    std::cout << "ChatBotPanelDialog constructor is called \r\n"; // SCS debug

    // sizer will take care of determining the needed scroll size
    _dialogSizer = new wxBoxSizer(wxVERTICAL);
          std::cout << "ChatBotPanelDialog: got _dialogSizer \r\n";// SCS debug


    this->SetSizer(_dialogSizer);
//    std::cout << "ChatBotPanelDialog: set _dialogSizer \r\n"; // SCS debug


    // allow for PNG images to be handled
    wxInitAllImageHandlers();
 //   std::cout << "ChatBotPanelDialog ImageHandler initialized \r\n";// SCS debug


    //// STUDENT CODE
    ////

    // create chat logic instance
    _chatLogic = std::make_unique<ChatLogic>();  // SCS 24.09 - implementing unique_ptr
  //  std::cout << "ChatBotPanelDialog: new _chatlogic instance \r\n"; // SCS debug


    // pass pointer to chatbot dialog so answers can be displayed in GUI
    _chatLogic->SetPanelDialogHandle(this);
  //  std::cout << "ChatBotPanelDialog SetPanelDialogHandle \r\n"; // SCS debug


    // load answer graph from file
    _chatLogic->LoadAnswerGraphFromFile(dataPath + "src/answergraph.txt");
    std::cout << "ChatBotPanelDialog: LoadAnswerGraph from File \r\n"; // SCS debug 


    ////
    //// EOF STUDENT CODE
}

ChatBotPanelDialog::~ChatBotPanelDialog()
{
       std::cout << "ChatBotPanelDialog destructor is called " <<std::endl; // SCS debug
    //// STUDENT CODE
    ////
 /*   if (_dialogSizer != NULL) { // SCS 22.09.2022
      delete _dialogSizer;
      _dialogSizer = NULL;
    } */
   
 /*  if (_chatLogic != nullptr) { // SCS 24.09 - implementing unique_ptr
        delete _chatLogic;
        _chatLogic = nullptr;
    } */


    ////
    //// EOF STUDENT CODE
}

void ChatBotPanelDialog::AddDialogItem(wxString text, bool isFromUser)
{
  
       std::cout << "AddDialogItem Start" << text << std::endl; // SCS debug
    // add a single dialog element to the sizer
    ChatBotPanelDialogItem *item = new ChatBotPanelDialogItem(this, text, isFromUser);
    _dialogSizer->Add(item, 0, wxALL | (isFromUser == true ? wxALIGN_LEFT : wxALIGN_RIGHT), 8);
    _dialogSizer->Layout();

    // make scrollbar show up
    this->FitInside(); // ask the sizer about the needed size
    this->SetScrollRate(5, 5);
    this->Layout();

    // scroll to bottom to show newest element
    int dx, dy;
    this->GetScrollPixelsPerUnit(&dx, &dy);
    int sy = dy * this->GetScrollLines(wxVERTICAL);
    this->DoScroll(0, sy);
  
       std::cout << "AddDialogItem End " << text << std::endl; // SCS debug
}


void ChatBotPanelDialog::PrintChatbotResponse(std::string response)
{
  
       std::cout << "PrintChatbotResponse: " << response << std::endl; // SCS debug
    // convert string into wxString and add dialog element
    wxString botText(response.c_str(), wxConvUTF8);
    AddDialogItem(botText, false);
}

void ChatBotPanelDialog::paintEvent(wxPaintEvent &evt)
{
    wxPaintDC dc(this);
    render(dc);
}

void ChatBotPanelDialog::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

void ChatBotPanelDialog::render(wxDC &dc)
{
    wxImage image;
    image.LoadFile(imgBasePath + "sf_bridge_inner.jpg");

    wxSize sz = this->GetSize();
    wxImage imgSmall = image.Rescale(sz.GetWidth(), sz.GetHeight(), wxIMAGE_QUALITY_HIGH);

    _image = wxBitmap(imgSmall);
    dc.DrawBitmap(_image, 0, 0, false);
}

ChatBotPanelDialogItem::ChatBotPanelDialogItem(wxPanel *parent, wxString text, bool isFromUser)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_NONE)
{
       std::cout << "ChatBotPanelDialogItem constructor is called " <<std::endl; // SCS debug
    // retrieve image from chatbot
    wxBitmap *bitmap = isFromUser == true ? nullptr : ((ChatBotPanelDialog*)parent)->GetChatLogicHandle()->GetImageFromChatbot(); 

    // create image and text
    _chatBotImg = new wxStaticBitmap(this, wxID_ANY, (isFromUser ? wxBitmap(imgBasePath + "user.png", wxBITMAP_TYPE_PNG) : *bitmap), wxPoint(-1, -1), wxSize(-1, -1));
      
    _chatBotTxt = new wxStaticText(this, wxID_ANY, text, wxPoint(-1, -1), wxSize(150, -1), wxALIGN_CENTRE | wxBORDER_NONE);
      
    _chatBotTxt->SetForegroundColour(isFromUser == true ? wxColor(*wxBLACK) : wxColor(*wxWHITE));

    // create sizer and add elements
    wxBoxSizer *horzBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    horzBoxSizer->Add(_chatBotTxt, 8, wxEXPAND | wxALL, 1);
    horzBoxSizer->Add(_chatBotImg, 2, wxEXPAND | wxALL, 1);
    this->SetSizer(horzBoxSizer);

    // wrap text after 150 pixels
    _chatBotTxt->Wrap(150);

    // set background color
    this->SetBackgroundColour((isFromUser == true ? wxT("YELLOW") : wxT("BLUE")));
}

ChatBotPanelDialogItem::~ChatBotPanelDialogItem() { //SCS 22.09.
   std::cout << "ChatBotPanelDialogItem destructor is called " <<std::endl; // SCS debug
    if (_chatBotImg != NULL) {

   std::cout << "ChatBotPanelDialogItem _image " << _chatBotImg << " "<<std::endl; // SCS debug
        delete _chatBotImg;
        _chatBotImg = NULL;
    } else {

   std::cout << "ChatBotPanelDialogItem _image = nullptr " <<std::endl; // SCS debug
    }
    if (_chatBotTxt != NULL) {

   std::cout << "ChatBotPanelDialogItem _txt " << _chatBotTxt << " "<<std::endl; // SCS debug
        delete _chatBotTxt;
        _chatBotTxt = NULL;
    } else {

   std::cout << "ChatBotPanelDialogItem _txt = nullptr " <<std::endl; // SCS debug
    }
}
