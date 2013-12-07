//
//  TNode.h
//  Tuneline
//
//  Created by Daniel Vasquez on 2013-11-24.
//  Adapted from Koffman & Wolfgang
//

#ifndef __Tuneline__TNode__
#define __Tuneline__TNode__

#include <iostream>
#include <sstream>
/** A node for a Binary Tree. */
template<typename Level>
struct TNode
{
    // Data Fields
    Level data;
    TNode<Level>* left;
    TNode<Level>* right;
    
    // Constructor
    TNode(const Level& the_data,
           TNode<Level>* left_val = NULL,
           TNode<Level>* right_val = NULL) :
    data(the_data), left(left_val),  right(right_val) {}
    // Destructor (to avoid warning message)
    virtual ~TNode() {}
    // to_string
    virtual std::string to_string() const {
        std::ostringstream os;
        os << data;
        return os.str();
    }
};


// Overloading the ostream insertion operator
template<typename Level>
std::ostream& operator<<(std::ostream& out,
                         const TNode<Level>& node) {
    return out << node.to_string();
}
#endif /* defined(__Tuneline__TNode__) */
