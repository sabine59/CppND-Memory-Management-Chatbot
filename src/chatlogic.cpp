#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <tuple>
#include <algorithm>

#include "graphedge.h"
#include "graphnode.h"
#include "chatbot.h"
#include "chatlogic.h"


ChatLogic::ChatLogic()
{
    //// STUDENT CODE
    ////

       std::cout << "ChatLogic constructor is called " <<std::endl; // SCS debug
    // create instance of chatbot
  _chatBot = new ChatBot("../images/chatbot.png");
  std::cout << "_chatBot at: "<< _chatBot <<std::endl; // SCS debug


  // test copy constructor
 //  ChatBot *doubleBot(_chatBot); // SCS 24.09.  - rule of five - debug help
  
    // test move constructor
 //ChatBot *doubleBot(std::move(_chatBot)); // SCS 24.09.  - rule of five - debug help

     // test move assignement operator
  /* ChatBot *doubleBot = new ChatBot("../images/user.png");
  
  std::cout << "doubleBot at: "<< doubleBot <<std::endl; // SCS debug
  doubleBot = std::move(_chatBot); // SCS 24.09.  - rule of five - debug help 
  std::cout << "doubleBot at: "<< doubleBot <<std::endl; // SCS debug
   */

    // add pointer to chatlogic so that chatbot answers can be passed on to the GUI
 //   _chatBot->SetChatLogicHandle(this);
_chatBot->SetChatLogicHandle(this);
    ////
    //// EOF STUDENT CODE
}

ChatLogic::~ChatLogic()
{
    //// STUDENT CODE
    ////

       std::cout << "ChatLogic destructor is called " <<std::endl; // SCS debug
    // delete chatbot instance
/*   if (_chatBot != nullptr) { // SCS 22.09.
        delete _chatBot; // is  not called, because _chatBot already  moved
        _chatBot = nullptr;
    }  */

    // delete all nodes
  // SCS 26.09 - no delete, because unique pointers are deleted automatically
  /*
    for (auto it = std::begin(_nodes); it != std::end(_nodes); ++it)
    {
        delete *it;
    }  */

    // delete all edges
/*    for (auto it = std::begin(_edges); it != std::end(_edges); ++it) // SCS 28.09. task 4
    {
        delete *it;
    } */

    ////
    //// EOF STUDENT CODE
}

template <typename T>
void ChatLogic::AddAllTokensToElement(std::string tokenID, tokenlist &tokens, T &element)
{
  
  std::cout << "AddAllTokensToElement Start "<<std::endl; // SCS debug
    // find all occurences for current node
    auto token = tokens.begin();
    while (true)
    {
        token = std::find_if(token, tokens.end(), [&tokenID](const std::pair<std::string, std::string> &pair) { return pair.first == tokenID;; });
        if (token != tokens.end())
        {
            element.AddToken(token->second); // add new keyword to edge
            token++;                         // increment iterator to next element
        }
        else
        {
            break; // quit infinite while-loop
        }
    }
}


void ChatLogic::LoadAnswerGraphFromFile(std::string filename)
{
  
  std::cout << "ChatLogic::LoadAnswerGraphFromFile Start " <<std::endl; // SCS debug
    // load file with answer graph elements
    std::ifstream file(filename);

    // check for file availability and process it line by line
    if (file)
    {
        // loop over all lines in the file
        std::string lineStr;
        while (getline(file, lineStr))
        {
            // extract all tokens from current line
            tokenlist tokens;
            while (lineStr.size() > 0)
            {
                // extract next token
                int posTokenFront = lineStr.find("<");
                int posTokenBack = lineStr.find(">");
                if (posTokenFront < 0 || posTokenBack < 0)
                    break; // quit loop if no complete token has been found
                std::string tokenStr = lineStr.substr(posTokenFront + 1, posTokenBack - 1);

                // extract token type and info
                int posTokenInfo = tokenStr.find(":");
                if (posTokenInfo != std::string::npos)
                {
                    std::string tokenType = tokenStr.substr(0, posTokenInfo);
                    std::string tokenInfo = tokenStr.substr(posTokenInfo + 1, tokenStr.size() - 1);

                    // add token to vector
                    tokens.push_back(std::make_pair(tokenType, tokenInfo));
                }

                // remove token from current line
                lineStr = lineStr.substr(posTokenBack + 1, lineStr.size());
            }

            // process tokens for current line
            auto type = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair) { return pair.first == "TYPE"; });
            if (type != tokens.end())
            {
                // check for id
                auto idToken = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair) { return pair.first == "ID"; });
                if (idToken != tokens.end())
                {
                  
  std::cout << "ChatLogic::LoadAnswerGraphFromFile idToken!=tokens.end()" <<std::endl; // SCS debug
                    // extract id from token
                    int id = std::stoi(idToken->second);
					std::vector <GraphNode *> _rawNodes {};   // SCS 26.09 task 3: exclusive ownership
                        for (int k=0; k<_nodes.size(); k++) {     // SCS 26.09 task 3: exclusive ownership
                          GraphNode * actualNode = *_nodes[k].get();
                          _rawNodes.emplace_back(actualNode);   // SCS 26.09 task 3: exclusive ownership
                      
                        }                     // SCS 26.09 task 3: exclusive ownership
                  
  std::cout << "ChatLogic::LoadAnswerGraphFromFile vector _rawNodes created, size: " <<_rawNodes.size() <<std::endl; // SCS debug
                    // node-based processing
                    if (type->second == "NODE")
                    {
                        //// STUDENT CODE
                        ////
	                    // SCS 26.09 task 3: exclusive ownership
                        // check if node with this ID exists already
                        auto newNode = std::find_if(_rawNodes.begin(), _rawNodes.end(),  [&id](GraphNode *node) { return node->GetID() == id;}); // SCS 26.09 task 3: exclusive ownership
                      
                       if (newNode == _rawNodes.end()) 
 							 std::cout << "ChatLogic::LoadAnswerGraphFromFile newNode = find_if, newNode = _rawNodes.end() "  << std::endl; // SCS debug
                        // create new element if ID does not yet exist
                         //GraphNode* endOfNode (new GraphNode(0));
                         //endOfNode = *_rawNodes.end();   // SCS 26.09 task 3: exclusive ownership
std::cout << "ChatLogic::LoadAnswerGraphFromFile *endOfNodes = &*(_nodes.end())->get(); " <<std::endl; // SCS debug
                        if (newNode ==_rawNodes.end())   // SCS 26.09 task 3: exclusive ownership
                        {
                          
  std::cout << "ChatLogic::LoadAnswerGraphFromFile if enewNode == _rawNodes.end()" <<std::endl; // SCS debug
                            //GraphNode* newLast = new GraphNode(id);
                         // std::make_unique<std::string>("Learn ");
                            //std::unique_ptr <GraphNode*>  newEndNode = std::make_unique<GraphNode*>(new GraphNode(id));
                            _nodes.emplace_back(std::make_unique<GraphNode*>(new GraphNode(id))); // SCS 26.09 task 3: exclusive ownership
                          
  std::cout << "ChatLogic::LoadAnswerGraphFromFile _nodes.emplace_back()" <<std::endl; // SCS debug
                            auto newNodeRawPtr =  *(_nodes.end() - 1)->get(); // SCS 26.09 task 3: exclusive ownership // get iterator to last element
					        
  std::cout << "ChatLogic::LoadAnswerGraphFromFile newNode = _rawNodes.end()-1" <<std::endl; // SCS debug
                            // add all answers to current node
                            AddAllTokensToElement("ANSWER", tokens, *newNodeRawPtr); // SCS 26.09 task 3: exclusive ownership
                          
  std::cout << "ChatLogic::LoadAnswerGraphFromFile AddAllTokensToElement " <<std::endl; // SCS debug
                        }

                        ////
                        //// EOF STUDENT CODE
                    }

                    // edge-based processing
                    if (type->second == "EDGE")
                    {
                        //// STUDENT CODE
                        ////

                        // find tokens for incoming (parent) and outgoing (child) node
                        auto parentToken = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair) { return pair.first == "PARENT"; });
                        auto childToken = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair) { return pair.first == "CHILD"; });

                        if (parentToken != tokens.end() && childToken != tokens.end())
                        {
                            // get iterator on incoming and outgoing node via ID search
                          auto parentNode = std::find_if(_rawNodes.begin(), _rawNodes.end(), [&parentToken](auto node) { return node->GetID() == std::stoi(parentToken->second); }); // SCS 26.09 task 3: exclusive ownership
                          auto childNode = std::find_if(_rawNodes.begin(), _rawNodes.end(), [&childToken](auto node) { return node->GetID() == std::stoi(childToken->second); }); // SCS 26.09 task 3: exclusive ownership

                            // create new edge
                           GraphEdge * edge = new GraphEdge(id);
                           edge->SetChildNode(*childNode); // SCS 28.09 task 4:
                           edge->SetParentNode(*parentNode); // SCS 28.09 task 4:
                           _edges.push_back(std::make_shared <GraphEdge *> (edge));

                            // find all keywords for current node
                            AddAllTokensToElement("KEYWORD", tokens, *edge);
							std::shared_ptr<GraphEdge *> nodesEdge = std::make_shared <GraphEdge *> (edge);
                          
                            // store reference in child node and parent node
                           (*childNode)->AddEdgeToParentNode(nodesEdge);
                          
                           (*parentNode)->AddEdgeToChildNode(std::move(nodesEdge));
                        }

                        ////
                        //// EOF STUDENT CODE
                    }
               
                }
                else
                {
                    std::cout << "Error: ID missing. Line is ignored!" << std::endl;
                }
            }
        } // eof loop over all lines in the file

        file.close();

    } // eof check for file availability
    else
    {
        std::cout << "File could not be opened!" << std::endl;
        return;
    }

    //// STUDENT CODE
    ////

    // identify root node
    GraphNode *rootNode = nullptr;
    for (auto it = std::begin(_nodes); it != std::end(_nodes); ++it)
    {
        // search for nodes which have no incoming edges
      GraphNode* myTest = *it->get();
        if (myTest->GetNumberOfParents() == 0)
        {

            if (rootNode == nullptr)
            {
                rootNode = *it->get(); // SCS 26.09 task 3: exclusive ownership // assign current node to root
            }
            else
            {
                std::cout << "ERROR : Multiple root nodes detected" << std::endl;
            }
        }
    }

    // add chatbot to graph root node
    _chatBot->SetRootNode(rootNode);
    rootNode->MoveChatbotHere(_chatBot);
    //_chatBot = nullptr;  // SCS 22.09.
    
    ////
    //// EOF STUDENT CODE
}

void ChatLogic::SetPanelDialogHandle(ChatBotPanelDialog *panelDialog)
{
  
       std::cout << "ChatLogic:SetPanelDialogHandle"<< std::endl; // SCS debug
    _panelDialog = panelDialog;
}

void ChatLogic::SetChatbotHandle(ChatBot *chatbot)
{
  
       std::cout << "ChatLogic:SetChatbotHandle "<< std::endl; // SCS debug
    _chatBot = chatbot;
}

void ChatLogic::SendMessageToChatbot(std::string message)
{
  
       std::cout << "ChatLogic:SendMessageToChatBot _chatBot: "<< _chatBot << std::endl; // SCS debug
    _chatBot->ReceiveMessageFromUser(message);
}

void ChatLogic::SendMessageToUser(std::string message)
{
  
       std::cout << "ChatLogic:SendMessageToUser "<< std::endl; // SCS debug
       std::cout << "ChatLogic:SendMessageToUser message:  " << message<< std::endl; // SCS debug
    _panelDialog->PrintChatbotResponse(message);
  
       std::cout << "ChatLogic:SendMessageToUser printChatbotRTesponse " <<  std::endl; // SCS debug
}

wxBitmap *ChatLogic::GetImageFromChatbot()
{
    return _chatBot->GetImageHandle();
}
