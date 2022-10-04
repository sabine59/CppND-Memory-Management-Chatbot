#include "graphedge.h"
#include "graphnode.h"
#include "chatlogic.h"

#include<iostream> // SCS debug

GraphNode::GraphNode(int id) { 
  
  //std::cout << "GraphNode constructor id: " << id << std::endl;
  _id = id; }

GraphNode::~GraphNode()
{
    //// STUDENT CODE
    ////
   
    // _chatBot is not owned.
    // All the other members are vecotors, which are destroyed automatically
 
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
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr <GraphEdge *> edge)
{
   _childEdges.push_back(std::move(edge));
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere( ChatBot chatBot)
{
   
   this->_chatBot = std::move(chatBot);
   this->_chatBot.SetCurrentNode(this);  
  
   std::cout << "MoveChatBotHere _chatBot._currentNode._id: " << this->_chatBot.GetCurrentNode()->GetID() << std::endl;
  

}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
   newNode->MoveChatbotHere(std::move(_chatBot));


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