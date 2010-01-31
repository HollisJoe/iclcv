#ifndef ICL_CAM_THREAD_H
#define ICL_CAM_THREAD_H

#include <ICLQt/Widget.h>
#include <ICLCore/ImgBase.h>
#include <ICLIO/PWCGrabber.h>

using namespace icl;
using namespace std;
namespace icl{

  /// A utility class ( DEPRECATED! ) \ingroup COMMON 
  class CamThread : public QObject{
    Q_OBJECT
    public:
    inline CamThread(int id, const Size &size=Size(320,240)):
    widget(new ICLWidget(0)),
    grabber(new PWCGrabber(size,30,id)),
    id(id){
      //grabber->setDesiredSize(size);
      widget->setGeometry(10,10,size.width,size.height);
      widget->show();
    } 
    inline CamThread(Grabber *grabber, const Size &size=Size(320,240)):
    widget(new ICLWidget(0)),
    grabber(grabber),
    id(-1){
      //grabber->setDesiredSize(size);
      widget->setGeometry(10,10,size.width,size.height);
      widget->show();
    }
    inline virtual ~CamThread(){
      delete grabber;
      delete widget;
    }
    
    public slots:
    
    void update(){
      widget->setImage(grabber->grab());
      widget->update();
    }

    void setGeomery(const Rect &bounds){
      widget->setGeometry(QRect(bounds.x, bounds.y, bounds.width, bounds.height));
    }
    
    private:
    ICLWidget *widget;
    Grabber *grabber;
    int id;
  };
}


#endif
