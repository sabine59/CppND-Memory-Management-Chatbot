#include "graphedge.h"
#include "graphnode.h"

#include<iostream> // SCS debug

GraphNode::GraphNode(int id) { _id = id; }

GraphNode::~GraphNode()
{
    //// STUDENT CODE
    ////
   
    _chatBot.~ChatBot();
  
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
   _parentEdges().push_back(parentNodeEdge);
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr <GraphEdge *> edge)
{
   _childEdges().push_back(std::move(edge));
  int s = _childEdges().size();
  std::cout << "AddEdgeToChildNode s " << s << std::endl;
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere( ChatBot chatBot)
{
    std::cout << "MoveChatBotHere " << std::endl;
   this->_chatBot = std::move(chatBot);
   std::cout << "MoveChatBotHere " << std::endl;
   this->_chatBot.SetCurrentNode(this);  
    

}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
std::cout << "Move Chatbot to new Node " << std::endl;
   newNode->MoveChatbotHere(_chatBot);

   this->_chatBot.~ChatBot(); // call move assignement operator to invalidate _chatbot after movement
}
////
//// EOF STUDENT CODE

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    ////
    
	GraphEdge  *returnValue =*_childEdges().at(index).get();
    return returnValue;

    ////
    //// EOF STUDENT CODE
}