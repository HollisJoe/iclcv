/********************************************************************
**                Image Component Library (ICL)                    **
**                                                                 **
** Copyright (C) 2006-2010 CITEC, University of Bielefeld          **
**                         Neuroinformatics Group                  **
** Website: www.iclcv.org and                                      **
**          http://opensource.cit-ec.de/projects/icl               **
**                                                                 **
** File   : include/ICLUtils/XMLNodeIterator.h                     **
** Module : ICLUtils                                               **
** Authors: Christof Elbrechter                                    **
**                                                                 **
**                                                                 **
** Commercial License                                              **
** ICL can be used commercially, please refer to our website       **
** www.iclcv.org for more details.                                 **
**                                                                 **
** GNU General Public License Usage                                **
** Alternatively, this file may be used under the terms of the     **
** GNU General Public License version 3.0 as published by the      **
** Free Software Foundation and appearing in the file LICENSE.GPL  **
** included in the packaging of this file.  Please review the      **
** following information to ensure the GNU General Public License  **
** version 3.0 requirements will be met:                           **
** http://www.gnu.org/copyleft/gpl.html.                           **
**                                                                 **
** The development of this software was supported by the           **
** Excellence Cluster EXC 277 Cognitive Interaction Technology.    **
** The Excellence Cluster EXC 277 is a grant of the Deutsche       **
** Forschungsgemeinschaft (DFG) in the context of the German       **
** Excellence Initiative.                                          **
**                                                                 **
*********************************************************************/

#ifndef ICL_XML_NODE_ITERATOR_H
#define ICL_XML_NODE_ITERATOR_H

#include <ICLUtils/XML.h>
#include <ICLUtils/XMLNodeFilter.h>
#include <iterator>

namespace icl{
  
  /// Utility structure that serves as recursive iterator type \ingroup XML
  /** Unlike the XMLNode::node_iterator type, the XMLNode::recursive_node_iterator, which 
      is a typedef to XMLNodeIterator can be used to iterate recursively though
      all subnodes of a node, that optionally have to match given conditions represented
      by an instance of XMLNodeFilter.
      
      \section Constness
      The XMLNodeIterator is also available in it's const version: XMLNodeConstIterator.
      The Iterator implements all necessary functions for an std::forward_iterator type, that is 
      it can be incremented using pre- and post-scrip ++ operator and it can be compared with
      other iterators using == and != operators. Furthermore, the -> operator provides access
      to the current XMLNode* and the * operator can be used to get a reference to
      that node.
      
      \section Creation
      The XMLNodeIterator class uses a private constructor, so it can only be
      copied or initialized without referencing a node. Use XMLNode::recursive_begin(...) 
      and XMLNode::recursive_end to get valid instances of XMLNodeIterator.

      \section Complexity
      <b>Please Note</b> That creation of a recursive iterator must descend the whole
      document tree originating from the source node. This may take some time especially for
      huge XML documents.
  */
  class XMLNodeIterator :  public std::iterator<std::forward_iterator_tag,XMLNode>{

    /// Internal hidden implementation type
    class XMLNodeIteratorImpl;

    /// Internal hidden implementation data
    XMLNodeIteratorImpl *impl;
    
    /// Main constructor only available by the friend class XMLNode
    XMLNodeIterator(const XMLNode &origin, const XMLNodeFilter &filter);
    public:
    
    /// Tight integration with XMLNode class
    friend class XMLNode;

    /// Tight integration with XMLNodeConstIterator wrapper for const node access
    friend class XMLNodeConstIterator;

    /// Empty constructor (creates an end-iterator)
    XMLNodeIterator();
    
    /// Copy constructor
    XMLNodeIterator(const XMLNodeIterator &other);

    /// Destructor
    ~XMLNodeIterator();

    /// Assignment operator
    XMLNodeIterator &operator=(const XMLNodeIterator &other);
    
    /// post-increment operator
    XMLNodeIterator operator++(int);

    /// pre-increment operator
    XMLNodeIterator &operator++();

    /// dereference operator (providing access to current node)
    XMLNode &operator*();
    
    /// dereference operator (providing access to current node) (const)
    const XMLNode &operator*() const;

    /// pointer operator (providing access to current node)
    XMLNode* operator->();

    /// pointer operator (providing access to current node) (const)
    const XMLNode* operator->() const;

    /// inequality comparison operator
    bool operator!=(const XMLNodeIterator &other) const;

    /// equality comparison operator
    bool operator==(const XMLNodeIterator &other) const;
  };
  
 
  
}


#endif
