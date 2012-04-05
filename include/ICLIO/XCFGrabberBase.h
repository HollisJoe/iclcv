/********************************************************************
**                Image Component Library (ICL)                    **
**                                                                 **
** Copyright (C) 2006-2012 CITEC, University of Bielefeld          **
**                         Neuroinformatics Group                  **
** Website: www.iclcv.org and                                      **
**          http://opensource.cit-ec.de/projects/icl               **
**                                                                 **
** File   : include/ICLIO/XCFGrabberBase.h                         **
** Module : ICLIO                                                  **
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

#ifdef HAVE_XCF
#ifndef ICL_XCF_GRABBER_BASE_H
#define ICL_XCF_GRABBER_BASE_H

#include <ICLIO/Grabber.h>
#include <string>
#include <xmltio/Location.hpp>
#include <xcf/CTU.hpp>

namespace icl {

  

   /// Grabber to access XCF Image Server and XCF Publisher \ingroup GRABBER_G
   /** XCFGrabberBase serves as a base class to XCFServerGrabber and 
       XCFPublisherGrabber. 
                  1GBit           100MBit
       Server     48 Hz           10 Hz
       Publisher  69 Hz           12 Hz
   */
  
   class XCFGrabberBase : public Grabber {
   public:
    
      /// Base constructor
    XCFGrabberBase();

    /// Destructor
    ~XCFGrabberBase();
    
    /// grabbing function  
    /** \copydoc icl::Grabber::grab(ImgBase**)*/
    virtual const ImgBase* acquireImage();

    protected:   
    /// retrieve most current image set in provided composite transport unit
    virtual void receive (XCF::CTUPtr& result) = 0;
    
    private:
      
    XCF::CTUPtr          m_result;
    ImgBase*             m_poSource;
  };
  
}

#endif
#endif // HAVE_XCF
