#ifndef ICL_QUICK_H
#define ICL_QUICK_H

#include <Img.h>
#include <string>

/** 
    \mainpage ICLQuick - an ICLPackage for rapid prototyping 
    
    \section sec1 Overview
    In contrast to all other ICLPackages the ICLQuick package
    focuses mainly on the programmers convenience. It should
    be used for rapid prototyping or for test applications.\n
    Consider a default test or benchmark application: The 
    programmer has to do several things that are identical for
    most of this kind of application:
    - including all necessary headers
    - making use of the namespaces "icl" and "std"
    - acquiring source images / creating a set of source images
    - running the tests / benchmarks ( this is the most variable 
      point)
    - visualizing the result image or images 
    
    The ICLQuick package provides the most common functions 
    and operators to create the desired result application 
    in much less time, that is even much better readable!
    
    \section sec2 Example
    The following demo application demonstrates how powerful
    The ICLQuick functions are, if no real-time performance is
    required:
    \code
    
    
    #include <ICLQuick.h>
    int main(){
      ImgQ b;
      for(int i=0;i<10;i++){
        ImgQ a;
        for(int j=0;j<10;j++){
          // right-side concatenation of a scaled pwc-image to a
          a = (a,scale(pwc(),0.1)); 
        }
        // bottom side concatenation of a the "10xa-row" to the current b
        b=(b%a);
      }
      // visualize b using xv
      show(b);    
      return 0;
    }
    \endcode
    
    \section sec3 Essential functions / features
    
    - <b>zeros, ones, load, create, pwc and ieee</b>\n
      creating images from different sources 
    - <b>filter,scaled, cc, levels, copy, flipx, ... </b>\n
      filtering functions, creating a new image from a given source image
    - <b>save, show and print</b>\n
      output functions
    - <b>arithmetical operators +,-,*,/</b>\n
      defined for two images as well as for images and constants
    - <b>arithmetical functions sqr, sqrt, exp, ln, and abs </b>\n
    - <b>logical operators || and && </b>\n
    - <b>concatenation operators "," and "%" </b>\n
      the ","-operator concatenates images horizontally,
      the "%"-operator concatenates images vertically.
    - <b>The roi-access function </b>\n
      for copying into an images ROI just use the roi function\n
      "roi(ImgA) = ImgB;" or "roi(ImgA) = 255;"  
    
 **/

using namespace icl;

/// just used by default
using namespace std;

/// all ICLQuick functions are placed here
namespace icl{

#define ICL_QUICK_DEPTH depth32f
#define ICL_QUICK_TYPE icl32f
  
    
  /// typedef for the quick images type (this time Img<icl32f>)
  typedef Img<ICL_QUICK_TYPE> ImgQ;

  /** @{ @name creator functions **/
  /* {{{ open */
  /// create an empty ImgQ
  /** @param width image width
      @param height image height
      @param channels image channel count
  **/
  ImgQ zeros(int width, int height, int channels=1);
  
  /// create an ImgQ that is pre-initialized with ones
  /** @param width image width
      @param height image height
      @param channels image channel count      
  **/
  ImgQ ones(int width, int height, int channels=1);
  
  /// read file from HD (converted to destination format)
  /** @param filename filename to read (*.jpg, *.ppm, *.pgm)
      @param fmt image format to convert the result to
  **/
  ImgQ load(const std::string &filename, format fmt = formatRGB);
  
  /// create a test image (converted to destination format)
  /** @param name identifier for the image:
                  names are: parrot, windows, flowers, women, house and tree 
      @param fmt image format to convert the result to
  **/
  ImgQ create(const std::string &name, format fmt=formatRGB);
  
  /// read an image for pwc webcam with given size, and format
  /** if releaseGrabber is set to 1, the internal used PWCGrabber is released after this call 
      @param device device for this grabbin call (0,1,2 or 3)
      @param size size of the returned image
      @param fmt format of the returned image
      @param releaseGrabber indicates whether the internal grabber object should be released
                            after this pwc call
  **/
  ImgQ pwc(int device=0, const Size &size=Size(640,480), format fmt=formatRGB, bool releaseGrabber=false);

  /// read an image for ieee1394 camera with given size, and format (TODO!!!)
  /** if releaseGrabber is set to 1, the internal used FwGrabber is released after this call 
      @param device device for this grabbin call (0,1,2 or 3)
      @param size size of the returned image
      @param fmt format of the returned image
      @param releaseGrabber indicates whether the internal grabber object should be released
                            after this ieee call
  **/
  ImgQ ieee(int device=0,const Size &size=Size(640,480), format fmt=formatRGB, bool releaseGrabber=false);

  /** @} **/
  /* }}} */
  
  /** @{ @name filtering function **/
  /* {{{ open */


  /// applies a filter operation on the source image
  /** @param image source image
      @param filter filter name, possible: sobelx, sobely, gauss, 
                    laplacs, median, dilation,erosion, opening and
                    closing 
  **/
  ImgQ filter(const ImgQ &image, const std::string &filter);
  
  /// applies a color conversion
  /** @param image source image*
      @param fmt destination image format
  **/
  ImgQ cc(const ImgQ& image, format fmt);
  
  /// converts a given image to formatRGB
  /** @param image source image **/
  ImgQ rgb(const ImgQ &image);
  
  /// converts a given image to formatHLS
  /** @param image source image **/
  ImgQ hls(const ImgQ &image);

  /// converts a given image to formatLAB
  /** @param image source image **/
  ImgQ lab(const ImgQ &image);

  /// converts a given image to formatGray
  /** @param image source image **/
  ImgQ gray(const ImgQ &image);
  
  /// scales an image by a given factor
  /** @param image source image
      @param factor scale factor 
  **/
  ImgQ scale(const ImgQ& image, float factor);

  /// scales an image to the given size
  /** @param image source image
      @param width destination image width
      @param height destination image height
  **/
  ImgQ scale(const ImgQ& image, int width, int height);
  
  /// picks a specific image channel
  /** @param image source image
      @param channel channel index to pick
  **/
  ImgQ channel(const ImgQ &image,int channel);

  /// reduces an images quantisation levels
  /** Internally the image is coverted to Img8u and back to
      apply this operation.
      @param image source image
      @param levels gray level count for each channel of the 
                    destination image
  **/
  ImgQ levels(const ImgQ &image, icl8u levels);
  
  /// performs an image binarisation for each channel with given threshold
  /** @param image source image
      @param threshold threshold to compare each pixel with
  **/
  ImgQ thresh(const ImgQ &image, float threshold);
 
  /// deep copy for an image
  /** @param image source image **/
  ImgQ copy(const ImgQ &image);
  
  /// deep copy of an images roi
  /** @param image source image **/
  ImgQ copyroi(const ImgQ &image);
  
  /// normalize an images range to [0,255]
  /** @param image source image **/
  ImgQ norm(const ImgQ &image);
  
  /// horizontal flip of an image
  /** @param image source image **/
  ImgQ flipx(const ImgQ& image);

  /// vertical flip of an image
  /** @param image source image **/
  ImgQ flipy(const ImgQ& image);

  /** @} **/
  /* }}} */
  
  /** @{ @name output functions **/
  /* {{{ open */
  
  /// write an image to HD 
  /** @param image source image
      @param filename filename to write the image to.
  **/
  void save(const ImgQ &image, const std::string &filename);
  
  /// shows an image using TestImages::xv
  /** The image is wrote to disk into a temporary file. Then it
      is shown using system("xv filename"). To ensure xv could
      read the image, sleep(0.5sec) is called before the temporary
      image is deleted using system("rm filename")
      @param image image to show
  **/
  void show(const ImgQ &image);
  
  /// print the images parameters to std::out
  /** @param image image to print to std::out **/
  void print(const ImgQ &image);

  /** @} **/
  /* }}} */
  
  /** @{ @name ImgQ arithmetical operators **/
  /* {{{ open */

  /// adds two images pixel-wise
  /** @param a first source image 
      @param b second source image 
  **/
  ImgQ operator+(const ImgQ &a, const ImgQ &b);
  
  /// subtracts two images pixel-wise
  /** @param a first source image 
      @param b second source image 
  **/
  ImgQ operator-(const ImgQ &a, const ImgQ &b);
  
  /// multiplies two images pixel-wise
  /** @param a first source image 
      @param b second source image 
  **/
  ImgQ operator*(const ImgQ &a, const ImgQ &b);

  /// divides two images pixel-wise
  /** @param a first source image 
      @param b second source image 
  **/
  ImgQ operator/(const ImgQ &a, const ImgQ &b);

  /// adds a constant to each pixel value
  /** @param image source image 
      @param val const addition value
  **/
  ImgQ operator+(const ImgQ &image, float val);

  /// subtracts a constant to each pixel value
  /** @param image source image 
      @param val const subtraction value
  **/
  ImgQ operator-(const ImgQ &image, float val);

  /// multiplies each pixel value with a constant
  /** @param image source image 
      @param val const multiplication value
  **/
  ImgQ operator*(const ImgQ &image, float val);

  /// divides each pixel value by a constant
    /** @param image source image 
      @param val const division value
  **/
  ImgQ operator/(const ImgQ &image, float val);

  /// adds a constant to each pixel value
  /** @param image source image 
      @param val const addition value
  **/
  ImgQ operator+(float val, const ImgQ &image);

  /// subtracts each pixel value from a constant
  /** @param image source image 
      @param val const left value for subtraction
  **/
  ImgQ operator-(float val, const ImgQ &image);
  
  /// multiplies each pixel value with a constant
    /** @param image source image 
      @param val const multiplication value
  **/
  ImgQ operator*(float val, const ImgQ &image);
  
  /// divides a constant by each pixel value
  /** @param image source image 
      @param val nominator for the division operation
  **/
  ImgQ operator/(float val, const ImgQ &image);

  /// returns image*(-1)
  /** @param image source image **/
  ImgQ operator-(const ImgQ &image);

  /** @} **/
  /* }}} */
  
  /** @{ @name ImgQ arithmetical functions **/
  /* {{{ open */

  /// calls exp( each pixel )
  /** @param image source image **/
  ImgQ exp(const ImgQ &image);

  /// calls ln( each pixel )  
  /** @param image source image **/
  ImgQ ln(const ImgQ &image);

  /// calls ( each pixel )²
  /** @param image source image **/
  ImgQ sqr(const ImgQ &image);
  
  /// calls sqrt( each pixel)
  /** @param image source image **/
  ImgQ sqrt(const ImgQ &image);
  
  /// calls abs ( each pixel)
  /** @param image source image **/
  ImgQ abs(const ImgQ &image);
  
  /** @} **/
  /* }}} */
  
  /** @{ @name ImgQ logical operators **/
  /* {{{ open */

  
  /// pixel-wise logical or
  /** @param a first source image 
      @param b second source image
  **/
  ImgQ operator||(const ImgQ &a, const ImgQ &b);

  /// pixel-wise logical and
  /** @param a first source image 
      @param b second source image
  **/
  ImgQ operator&&(const ImgQ &a, const ImgQ &b);

  /** @} **/
  /* }}} */
  
  /** @{ @name ImgQ concatenation operators **/
  /* {{{ open */

  /// horizontal image concatenation
  /** <pre>
      example: ImgQ a,b,c;
      a=aaa  b = bbbbb   
        aaa      bbbbb
        aaa
      
      c = a,b,a;
      
      c = aaabbbbbaaa
          aaabbbbbaaa
          aaa00000aaa
      </pre>
      empty spaces are set to 0;
      
      @param a left image
      @param b right image
  **/
  ImgQ operator,(const ImgQ &a, const ImgQ &b);
  
  /// vertical image combination (as ,-operator)
  /** @param a upper image
      @param b lower image
  **/
  ImgQ operator%(const ImgQ &a, const ImgQ &b);

  /** @} **/
  /* }}} */
  
  /** @{ @name ImgQ roi copy **/
  /* {{{ open */


  /// internal stuct, used for deep image copies
  /** @see icl::roi(Img<icl32f> &)*/
  struct ImgROI{
    /// image data
    ImgQ image;
    
    /// sets up the member images ROI to the i's ROI
    /** @param i source image **/
    ImgROI &operator=(const ImgQ &i);
    
    /// sets up the member images ROI to val
    /** @param val value to set up each pixel with **/
    ImgROI &operator=(float val);
    
    /// sets up the member images ROI to the given ROI
    /** @param r source roi**/
    ImgROI &operator=(const ImgROI &r);
    
    /// implicit cast operator
    operator ImgQ();
  };
  
  /// creates a ROI-struct from an image
  /** This function helps to copy images ROIs:
      <pre>
      ImgQ a,b;
      
      a = aaaaa (A = ROI pixel)
          aaAAA (a = no ROI pixel)
          aaAAA
      
      b = bbb
          bbb
      
      roi(a) = b;
      
      a = aaaaa
          aabbb
          aabbb
      
      also possible: roi(a) = roi(b);
      </pre>
      @param r image to wrap
  **/
  ImgROI roi(ImgQ &r);
  
  /// creates full ROI ROI-struct
  /** this can also be used for deep copies
      <pre>
      ImgQ a,b;
      
      a = aaa    b = bBBBb ( B = ROI pixel )
          aaa        bBBBb ( b = no ROI pixel )
          aaa        bBBBb
                     bbbbb
      
      data(a) = roi(b)
      
      a = BBB
          BBB
          BBB

      equal to:
      or a = copyroi(b) // this will release a and reallocate its data 
      </pre>
      @param r image to wrap
  **/
  ImgROI data(ImgQ &r);

  /** @} **/
  /* }}} */
  
  /** @{ @name drawing functions **/
  /* {{{ open */

  /// sets the current color to given r,g,b,alpha value
  /** @param r red value 
      @param g green value (if < 0, g is set to r) 
      @param b blue value (if < 0, b is set to r) 
      @param alpha alpha value 255 = no transparency, 0 = full transparency
  **/
  void color(float r, float g=-1, float b=-1, float alpha=255);

  /// sets the current fill color to given r,g,b,alpha value
  /** @param r red value 
      @param g green value (if < 0, g is set to r) 
      @param b blue value (if < 0, b is set to r) 
      @param alpha alpha value 255 = no transparency, 0 = full transparency
  **/
  void fill(float r, float g=-1, float b=-1, float alpha=255);

  /// draws a 6x6-cross into an image
  /** @param image destination image 
      @param x x-pos of the cross
      @param y y-pos of the cross
  **/
  void cross(ImgQ &image, int x, int y);

  /// draws a rect into an image
  /** @param image destination image
      @param x x-pos of the rect
      @param y x-pos of the rect
      @param w width of the rect
      @param h height of the rect
  **/
  void rect(ImgQ &image, int x, int y, int w, int h);
  
  /// draws a line into an image
  /** @param image destination image 
      @param x1 fist point x coord 
      @param y1 fist point y coord 
      @param x2 second point x coord 
      @param y2 second point y coord      
  **/
  void line(ImgQ &image, int x1, int y1, int x2, int y2);

  /// renders a text into an image (slow)
  /** This functin renders a text into an 3 or 1 channel image
      using the a QPainter internally. This functino is very 
      slow, as has to convert the hold image into a QImage
      internally and back. 
      <b>NOTE: the text rendering is performed in depth8u,
      so information is lost!</b>
      @param image destination image
      @param x xpos of the lower left corner of the text
      @param y ypos of the lower left corner of the text
      @param text text to render
  **/
  void text(ImgQ &image, int x, int y,const string &text);

  /// sets up the current font
  /** @param size new font size 12 by default 
      @param family font family string "Arial" by default
  **/
  void font(int size, const string &family="Arial");
  
  /// sets up current fontsize
  /** @param size new font size (default is 12) **/
  void fontsize(int size);
  /** @} **/
  /* }}} */

  /** @{ @name timer and benchmarking **/
  /* {{{ open */

  /// starts a timer
  void tic();
  
  /// stops a timer started with tic()
  void toc();
  /** @} **/
  /* }}} */



}


#endif
