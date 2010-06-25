/********************************************************************
**                Image Component Library (ICL)                    **
**                                                                 **
** Copyright (C) 2006-2010 CITEC, University of Bielefeld          **
**                         Neuroinformatics Group                  **
** Website: www.iclcv.org and                                      **
**          http://opensource.cit-ec.de/projects/icl               **
**                                                                 **
** File   : include/ICLIO/XCFPublisher.h                           **
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

#ifndef ICL_XCF_PUBLISHER_H
#define ICL_XCF_PUBLISHER_H

#include <ICLCore/ImgBase.h>
#include <xcf/Publisher.hpp>
#include <xcf/CTU.hpp>
#include <xcf/TransportObject.hpp>

namespace icl{
  class XCFPublisher{
    public:
    XCFPublisher();
    XCFPublisher(const std::string &streamName, const std::string &imageURI);
    
    ~XCFPublisher();
    
    void createPublisher(const std::string &streamName, 
                         const std::string &imageURI);
    
    void publish(const ImgBase *image);

    const std::string &getImageURI() const { return m_uri; }
    const std::string &getStreamName() const { return m_streamName; }
    
    private:
    XCF::PublisherPtr m_publisher;
    XCF::Binary::TransportUnitPtr m_btu;
    XCF::CTUPtr m_ctu;
    std::string m_uri;
    std::string m_streamName;
  };
}

#endif

#endif
