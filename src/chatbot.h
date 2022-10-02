#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <string>
#include <iostream>

class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot
{
   
private:
    // data handles (owned)
    wxBitmap *_image; // avatar image

    // data handles (not owned)
    GraphNode *_currentNode;
    GraphNode *_rootNode;
    ChatLogic *_chatLogic;


 
    // proprietary functions
    int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
    // constructors / destructors
    ChatBot();                     // constructor WITHOUT memory allocation
    ChatBot(std::string filename); // constructor WITH memory allocation
    ~ChatBot();                    // destructor

    //// STUDENT CODE
    ChatBot(const ChatBot &source); // SCS 01.10. rule of five - copy constructor
    ChatBot & operator=(const ChatBot &source); // SCS 01.10. rule of five - copy assignment operator
    ChatBot(ChatBot &&source); // SCS 01.10. rule of five - move constructor
    ChatBot &operator=(ChatBot &&source); // SCS 01.10. rule of five - move assignment operator

    //// EOF STUDENT CODE

    // getters / setters
    void SetCurrentNode(GraphNode *node);
    void SetRootNode(GraphNode *rootNode) {  std::cout << "SetRootNode ChatBot still alive ?  " << std::endl; _rootNode = rootNode; }
    void SetChatLogicHandle(ChatLogic *chatLogic)
    {
     std::cout << "ChatLogicHandle: ChatBot still alive ?  " << std::endl;
        _chatLogic = chatLogic;
    }
    ChatLogic *GetChatLogicHandle() { return _chatLogic; }
    wxBitmap *GetImageHandle() { return _image; }

    // communication
    void ReceiveMessageFromUser(std::string message);
};

#endif /* CHATBOT_H_ */
