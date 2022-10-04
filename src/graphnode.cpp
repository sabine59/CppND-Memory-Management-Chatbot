#include "graphedge.h"
#include "graphnode.h"
#include "chatlogic.h"

#include<iostream> // SCS debug

GraphNode::GraphNode(int id) { 
  
  std::cout << "GraphNode constructor id: " << id << std::endl;
  _id = id; }

GraphNode::~GraphNode()
{
    //// STUDENT CODE
    ////
   
  std::cout << "GraphNode destructor id: " << _id << std::endl;

  _chatBot.~ChatBot(); // not owned
 
    ////
    //// EOF STUDENT CODE
}

void GraphNode::AddToken(std::string token)
{
   _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(std::unique_ptr <GraphEdge *> edge)
{
   std::shared_ptr <GraphEdge *> parentNodeEdge = std::move(edge);
   _parentEdges.push_back(parentNodeEdge);
    int s = _parentEdges.size();
  std::cout << "AddEdgeToParentNode current id: " << _id << " s: " <<s << std::endl;
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr <GraphEdge *> edge)
{
   _childEdges.push_back(std::move(edge));
  int s = _childEdges.size();
  std::cout << "AddEdgeToChildNode current id: " << _id << " s: " <<s << std::endl;
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere( ChatBot chatBot)
{
   
   this->_chatBot = std::move(chatBot);
   std::cout << "MoveChatBotHere id: " << this->GetID() << std::endl;
   this->_chatBot.SetCurrentNode(this);  
  
   std::cout << "MoveChatBotHere _chatBot._currentNode._id: " << this->_chatBot.GetCurrentNode()->GetID() << std::endl;
  

}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
std::cout << "Move Chatbot to new Node id: " << newNode->GetID() << std::endl;
   this->_chatBot.GetChatLogicHandle()->SetCurrentNode(newNode);
   newNode->MoveChatbotHere(std::move(_chatBot));

  // this->_chatBot.~ChatBot(); // call move assignement operator to invalidate _chatbot after movement

}
////
//// EOF STUDENT CODE

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    ////
    
	GraphEdge  *returnValue =*_childEdges.at(index).get();
    return returnValue;

    ////
    //// EOF STUDENT CODE
}