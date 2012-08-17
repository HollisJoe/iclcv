/********************************************************************
**                Image Component Library (ICL)                    **
**                                                                 **
** Copyright (C) 2006-2012 CITEC, University of Bielefeld          **
**                         Neuroinformatics Group                  **
** Website: www.iclcv.org and                                      **
**          http://opensource.cit-ec.de/projects/icl               **
**                                                                 **
** File   : include/ICLGeom/PointCloudCreator.h                    **
** Module : ICLGeom                                                **
** Authors: Christof Elbrechter, Patrick Nobou                     **
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

#ifndef ICL_POINT_CLOUD_CREATOR_H
#define ICL_POINT_CLOUD_CREATOR_H

#include <ICLGeom/RGBDImageSceneObject.h>
#include <ICLGeom/PointCloudObjectBase.h>

namespace icl{
  
  /// Utility class that allows to create 3D (optionally colored) point clouds from given 2D depth images
  /** The PointCloudCreator utility class can be used to two differenct modes.
      It's basic functionality is to transform a depth-image into a 3D point cloud. 
      For this, a Camera instances is needed, which can be obtained from ICL's
      camera calibration tool icl-cam-calib-2 for real depth cameras such as Kinect.
      
      If also a second camera file is provided for the color camera, then
      the PointCloudCreator class can also be used for mapping optionally given
      RGB-byte images to the contained point's colors.

      \section _SPEED_ Benchmarks
      For VGA point clouds, creation with RGBD mapping takes about 8ms on a 2.5 GHz Core2Duo machine.
      If RGBD-mapping is not performed, the simple point cloud creation is performed in about 6 ms.
      For futher speed optimizations, we plan to add openmp optimization in the future.
  */
  class PointCloudCreator{
    struct Data;  // !< pimpl type
    Data *m_data; // !< pimpl pointer
    public:
    
    /// Representation of the given depth images
    /** Depth image values can either be understood as distance values
        to the the camera center or as distances from the camera's viewing
        plane */
    enum DepthImageMode{
      DistanceToCamCenter, //!< distances are given w.r.t. the camera center
      DistanceToCamPlane   //!< distances are given w.r.t. the camera plance
    };

    /// creates a null instance
    PointCloudCreator();
    
    /// creates a new instance with given depth camera (no rgbd mapping is available then)
    PointCloudCreator(const Camera &depthCam, DepthImageMode mode=DistanceToCamPlane);

    /// creates a new instance with given depth camera and color camera for rgbd mapping
    PointCloudCreator(const Camera &depthCam, const Camera &colorCam, DepthImageMode mode=DistanceToCamPlane);

    /// deep copy constructor
    PointCloudCreator(const PointCloudCreator &other);

    /// deep copy assginment operator
    PointCloudCreator &operator=(const PointCloudCreator &other);
    
    /// initializes with given depth camera (no rgbd mapping is available then)
    void init(const Camera &depthCam, DepthImageMode mode=DistanceToCamPlane);
    
    /// initializes with given depth camera and color camera for rgbd mapping
    void init(const Camera &depthCam, const Camera &colorCam, DepthImageMode mode=DistanceToCamPlane);
    
    /// creates a point cloud
    void create(const Img32f &depthImageMM, PointCloudObjectBase &destination, const Img8u *rgbImage = 0);

    /// returns the current depth camera
    const Camera &getDepthCamera() const;
    
    /// returns the current camera camera (if this was not given, an exception is thrown)
    const Camera &getColorCamera() const throw (ICLException);
    
    /// returns whether a color camera was given (and therefore whether RGBD-mapping is supported)
    bool hasColorCamera() const;

  };

}

#endif