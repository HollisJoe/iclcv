#include <iclCannyOp.h>
#include <iclCommon.h>
#include <iclConvolutionOp.h>
//#include <iclUnaryOpPipe.h>
GUI gui;

void init(){
  gui << "image[@handle=image@minsize=32x24]";
  gui << "fslider(0,2000,10)[@out=low@label=low@maxsize=100x2@handle=low-handle]";
  gui << "fslider(0,2000,100)[@out=high@label=high@maxsize=100x2@handle=high-handle]";
  gui << "togglebutton(off,on)[@out=pre-gauss@handle=pre-gauss-handle@label=gaussian PP])";
  gui << "label(time)[@handle=dt@label=filter time in ms]";
  gui.show();
}


void update(){
  static GenericGrabber grabber(FROM_PROGARG("-input"));
  grabber.setIgnoreDesiredParams(true);
  static ImageHandle image = gui.getValue<ImageHandle>("image");
  static LabelHandle dt = gui.getValue<LabelHandle>("dt");
  float &low = gui.getValue<float>("low");
  float &high = gui.getValue<float>("high");
  bool &preGauss = gui.getValue<bool>("pre-gauss");
  
  CannyOp canny(low,high,preGauss);
  static ImgBase *dst = 0;

  Time t = Time::now();
  canny.apply(grabber.grab(),&dst);
  dt = (Time::now()-t).toMilliSecondsDouble();
  
  image = dst;
  image.update();
}


int main(int n, char **ppc){
  pa_init(n,ppc,"-input(2)");
  QApplication app(n,ppc);
  
  init();
  update();
  gui.registerCallback(new GUI::Callback(update),"low-handle,high-handle,pre-gauss-handle");
  
  return app.exec();
  
}
