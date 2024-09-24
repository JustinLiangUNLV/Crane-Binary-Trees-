#include "binaryTreeClasses.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

binTreeNode* buildTree(); // create the three functions that were given in the pdf
double getObjectsWeight(binTreeNode* r);
void deallocateTree(binTreeNode* r);

int main()
{
    binTreeNode* root = buildTree(); // create a root with the buildTree function
    if(getObjectsWeight(root) != -1.0) // if the returned weight of the root is not -1.0
    {
        cout << "Crane can lift the items" << endl; // output that it can lift all the items
    }
    else
    {
        cout << "Well this is awkward" << endl; // otherwise it cannot lift all the items
    }
    deallocateTree(root); // deallocate the tree
    return 0; // return 0
}

binTreeNode* buildTree()
{
    string s; // temp string variable to hold the line
    string type; // temp variable to hold the first string of the line
    getline(cin, s); // get the entire line
    istringstream stringObject(s); // create a string object and give it the line that was read
    stringObject >> type; // store the first string of the line into type
    if(type == "Joint") // if the first string is joint
    {
        binTreeNode* r = new binTreeNode; // create a new binTreeNode
        int leftLength = 0; // temp variables to hold left length
        int rightLength = 0; // hold right length
        stringObject >> leftLength >> rightLength; // store it into these variables froms tring object
        binTreeNode* left = buildTree(); // create a left pointer
        binTreeNode* right = buildTree(); // create a right pointer
        r->setLeft(left); // set the left child to left of r
        r->setRight(right); // set the right child to right of r
        if(left != nullptr) // if there is a left node created
        {
            left->setArmLength(leftLength); // set the left child to hold the leftLength
        }
        if(right != nullptr)
        {
            right->setArmLength(rightLength); // set the right child to hold the rightLength
        }
        return r; // return the pointer
    }
    else if(type == "Bike") // if first string is bike
    {
        double w,f; // create temp double variables
        stringObject >> w >> f; // populate them
        bike* b = new bike(w,f); // bike pointer has new bike set with the constructor
        b->setLeft(nullptr); // set bike's left and right to null
        b->setRight(nullptr);
        return b; // return the pointer
    }
    else if(type == "Goped")
    {
        double w,e,t; // create temp double variables
        stringObject >> w >> e >> t; // populate them
        goped* g = new goped(w,e,t); // goped pointer has new goped set with the constructor
        g->setLeft(nullptr); // set goped's left and right to null
        g->setRight(nullptr);
        return g; // return pointer
    }
    else if(type == "Car") // if first string is car
    {
        double w,e,t,b; // create temp double variables
        stringObject >> w >> e >> t >> b; // populate them
        car* c = new car(w,e,t,b); // car pointer has new car set with the constructor
        c->setLeft(nullptr); // set car's left and right to null
        c->setRight(nullptr);
        return c; // return pointer
    }
    return nullptr; // return nullpointer
}

double getObjectsWeight(binTreeNode* r)
{
    if(r == nullptr) // if r is nullpointer
    {
        return 0; // return 0
    }
    if(r->getLeft() == nullptr && r->getRight() == nullptr) // if this is not a binTreeNode
    {
        return r->getWeight(); // return the weight
    }
    else
    {
        double leftWeight, rightWeight, leftTorque, rightTorque; // temp double variables
        leftWeight = getObjectsWeight(r->getLeft()); // get all of the left weights
        rightWeight = getObjectsWeight(r->getRight()); // get all of the right weights
        leftTorque = leftWeight * r->getLeft()->getArmLength(); // calculate left torque
        rightTorque = rightWeight *  r->getRight()->getArmLength(); // calculate right torque
        if(leftTorque == rightTorque) // if the left and right torque equals each other
        {
            return leftWeight + rightWeight; // return the combined weights
        }
        else
        {
            return -1.0; // return -1.0
        }
    }
}

void deallocateTree(binTreeNode* r)
{
    if(r == nullptr) // if r is nullpointer
    {
        return; // return
    }
    deallocateTree(r->getLeft()); // postorder recursive call to leftside
    deallocateTree(r->getRight()); // postorder recursive call to rightside
    delete r; // delete pointer
    return; // return
}