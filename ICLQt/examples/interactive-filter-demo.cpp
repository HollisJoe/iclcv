#include <iclCommon.h>
#include <iclConvolutionOp.h>


ICLDrawWidget *widget = 0;
GenericGrabber *grabber = 0;
int x,y;
int r,g,b;
ConvolutionKernel::fixedType k;
string sKernel;


struct Mouse :  public MouseInteractionReceiver{
  virtual void processMouseInteraction(MouseInteractionInfo *info){
    x=info->imageX;
    y=info->imageY;
    if(info->color.size() == 3){
      r=(int)info->color[0];
      g=(int)info->color[1];
      b=(int)info->color[2];
    }
    if(info->type==MouseInteractionInfo::pressEvent){
      if(k==ConvolutionKernel::gauss3x3){
        k = ConvolutionKernel::sobelX3x3;
        sKernel = "sobelx";
      }else if(k == ConvolutionKernel::sobelX3x3){
        k = ConvolutionKernel::sobelY3x3;
        sKernel = "sobel-y";
      }else if(k == ConvolutionKernel::sobelY3x3){
        k = ConvolutionKernel::laplace3x3;
        sKernel = "laplace";
      }else if(k == ConvolutionKernel::laplace3x3){
        k = ConvolutionKernel::gauss3x3;
        sKernel = "gauss";
      }
    }
  }
} MouseIO;

void run(){
  const ImgBase *grabbedImage = grabber->grab();
  widget->setImage(grabbedImage);
  
  if(x>0){ // else no mouse event has been recognized yet
    widget->lock();
    widget->reset();
    
    Rect roi(x-101,y-101,202,202);
    
    if(Rect(Point::null,grabbedImage->getSize()).contains(roi)){
      // drawing smooth dropshadow
      widget->nocolor();
      widget->fill(0,0,0,20);
      for(int d=0;d<5;d++){
        widget->rect(x-95-d,y-95-d,200+2*d,200+2*d);
      }
      // drawing filter result for the roi image
      const ImgBase *image = grabbedImage->shallowCopy(roi);
      ConvolutionOp conv(ConvolutionKernel(k),false); 
      ImgBase *dst = 0;
      conv.apply(image,&dst);   
      dst->normalizeAllChannels(Range<icl64f>(0,255));
      widget->image(dst,x-100,y-100,200,200);
      
      if(dst) delete dst;
      widget->nofill();
      widget->color(0,0,0);
      widget->rect(x-100,y-100,200,200);
    }
    
    // drawing image info
    widget->color(255,255,255);
    widget->fill(r,g,b,200);
    char ac[100];
    sprintf(ac,"color(%d,%d,%d)",r,g,b);
    widget->text(ac,x-90,y+120,-1,-1,8);
    sprintf(ac,"pos(%d,%d)",x,y);
    widget->text(ac,x-90,y+110,-1,-1,8);
    widget->text(sKernel,x-90,y+100,-1,-1,8);
    widget->text("(click!)",x+60,y+120,-1,-1,8);
    
    widget->unlock();
  }
  widget->update();
}


void init(){
  widget = new ICLDrawWidget;
  grabber = new GenericGrabber;
  grabber->resetBus();
  grabber->setDesiredSize(Size(640,480));
  widget->setGeometry(200,200,640,480);
  widget->show();
  widget->add(&MouseIO);
}




int main(int n, char **ppc){
  ExecThread x(run);

  QApplication a(n,ppc);
  init();

  x.run();

  return a.exec();
}
