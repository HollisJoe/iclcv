#include <ICLGeom/CoplanarPointPoseEstimator.h>

#include <ICLGeom/Camera.h>
#include <ICLGeom/GeomDefs.h>
#include <ICLUtils/Homography2D.h>
#include <ICLCore/Random.h>
#include <ICLUtils/ProgArg.h>

namespace icl{
  typedef DynMatrix<float> DMat;
  
  static inline void assign_row(float* p, float a, float b, float c, float d, 
                                float e, float f, float g, float h, float i){
    p[0] = a; p[1] = b; p[2] = c; p[3] = d; p[4] = e; 
    p[5] = f; p[6] = g; p[7] = h; p[8] = i;
  }

  static inline FixedMatrix<float,1,3> cross3(const FixedMatrix<float,1,3> &v1,
                                              const FixedMatrix<float,1,3> &v2){
    return FixedMatrix<float,1,3>(v1[1]*v2[2]-v1[2]*v2[1],
                                  v1[2]*v2[0]-v1[0]*v2[2],
                                  v1[0]*v2[1]-v1[1]*v2[0]);
  }
  
  struct CoplanarPointPoseEstimator::Data{
    DMat A,U,s,V;

    FixedMatrix<float,3,3> H,R;
    FixedMatrix<float,1,3> C;
    FixedMatrix<float,4,4> T;
    
    CoplanarPointPoseEstimator::ReferenceFrame referenceFrame;
    CoplanarPointPoseEstimator::PoseEstimationAlgorithm algorithm;
    CoplanarPointPoseEstimator::SamplingDensity density;
  };
  
  inline std::ostream &operator<<(std::ostream &stream, CoplanarPointPoseEstimator::PoseEstimationAlgorithm a){
    static std::string s[4] = {"HomographyBasedOnly","SampleRotationOnly","SampleAllSeparate","SampleAllAtOnce"};

    if((int)a >= 4 || (int)a < 0) throw ICLException("invalid value for CoplanarPointPoseEstimator::PoseEstimationAlgorithm");
    return stream << s[(int)a];
  }

  inline std::istream &operator>>(std::istream &stream, CoplanarPointPoseEstimator::PoseEstimationAlgorithm a){
    std::string s;
    stream >> s;
#define A(x)if(s == #x) { a = CoplanarPointPoseEstimator::x; return stream; }
    A(HomographyBasedOnly);A(SampleRotationOnly);A(SampleAllSeparate);A(SampleAllAtOnce);
#undef A
    throw ICLException("invalid value for CoplanarPointPoseEstimator::PoseEstimationAlgorithm");
    return stream;
  }

  inline std::ostream &operator<<(std::ostream &stream, CoplanarPointPoseEstimator::SamplingDensity a){
    static std::string s[4] = {"SampleCoarse","SampleFine","SampleVeryFine"};

    if((int)a >= 3 || (int)a < 0) throw ICLException("invalid value for CoplanarPointPoseEstimator::SamplingDensity");
    return stream << s[(int)a];
  }

  inline std::istream &operator>>(std::istream &stream, CoplanarPointPoseEstimator::SamplingDensity a){
    std::string s;
    stream >> s;
#define A(x)if(s == #x) { a = CoplanarPointPoseEstimator::x; return stream; }
    A(SampleCoarse);A(SampleFine);A(SampleVeryFine);
#undef A
    throw ICLException("invalid value for CoplanarPointPoseEstimator::SamplingDensity");
    return stream;
  }
  

  
  
  
  CoplanarPointPoseEstimator::CoplanarPointPoseEstimator(ReferenceFrame returnedPoseReferenceFrame,
                                                         PoseEstimationAlgorithm a,
                                                         SamplingDensity d):
    data(new Data){
    std::string as=str(HomographyBasedOnly);
    std::string ds=str(SampleCoarse);
    for(int i=1;i<4;++i) as+=str(',')+str((PoseEstimationAlgorithm)i);
    for(int i=1;i<3;++i) ds+=str(',')+str((SamplingDensity)i);
    
    addProperty("algorithm","menu",as,a);
    addProperty("sampling density","menu",ds,d);
    
    data->referenceFrame = returnedPoseReferenceFrame;
    data->algorithm = a;
    data->density = d;
    
    registerCallback(function(this,&CoplanarPointPoseEstimator::propertyChangedCallback));
  }
  
  void CoplanarPointPoseEstimator::propertyChangedCallback(const Property &p){
    if(p.name == "algorithm") data->algorithm = parse<PoseEstimationAlgorithm>(p.value);
    if(p.name == "sampling density") data->density = parse<SamplingDensity>(p.value);
  }
    
  
  CoplanarPointPoseEstimator::~CoplanarPointPoseEstimator(){
    delete data;
  }

  CoplanarPointPoseEstimator::CoplanarPointPoseEstimator(const CoplanarPointPoseEstimator &other):
    data(new Data){
    *this = other;
  }



  CoplanarPointPoseEstimator &CoplanarPointPoseEstimator::operator=(const CoplanarPointPoseEstimator &other){
    *data = *other.data;
    return *this;
  }


  CoplanarPointPoseEstimator::ReferenceFrame CoplanarPointPoseEstimator::getReferenceFrame() const{
    return data->referenceFrame;;
  }
  
  void CoplanarPointPoseEstimator::setReferenceFrame(CoplanarPointPoseEstimator::ReferenceFrame f){
    data->referenceFrame = f;
  }

  static float compute_error(const Mat &P, const Mat &T, const Point32f *M, const Point32f *I, int n){
    float error2 = 0;
    for(int i=0;i<n;++i){
      Vec tmp = homogenize( P * T * Vec(M[i].x,M[i].y,0,1) );
      error2 += Point32f(tmp[0],tmp[1]).distanceTo(I[i]);
    }
    return error2;
  }

  static float compute_error(const Mat &P, const FixedMatrix<float,1,6> &p, const Point32f *M, const Point32f *I, int n){
    const Mat T = create_hom_4x4<float>(p[0],p[1],p[2],p[3],p[4],p[5]);
    float error = 0;
    for(int i=0;i<n;++i){
      Vec tmp = homogenize( P * T * Vec(M[i].x,M[i].y,0,1) );
      error += Point32f(tmp[0],tmp[1]).distanceTo(I[i]);
    }
    return error;
  }
#if 0  
  inline void get_3x3_rot_data(T rx, T ry, T rz,T *p){
    T cx = cos(rx);
    T cy = cos(-ry);
    T cz = cos(-rz);
    T sx = sin(rx);
    T sy = sin(-ry);
    T sz = sin(-rz);
    *p++=cy*cz-sx*sy*sz; *p++=-sz*cx; *p++=cz*sy+sz*sx*cy; if(skip4th) p++;
    *p++=cy*sz+cz*sx*sy; *p++=cz*cx;  *p++=sz*sy-sx*cy*cz; if(skip4th) p++;
    *p++=-sy*cx;         *p++=sx;     *p++=cx*cy;       
  }
#endif
  
  static float compute_error_opt(const Mat &P, 
                                 FixedMatrix<float,1,3> &r,
                                 FixedMatrix<float,1,3> &t, 
                                 const Point32f *_M, 
                                 const Point32f *_I, 
                                 int n){
    const float &A = P(0,0), &B = P(1,0), &C = P(2,0), &D = P(1,1), &E = P(2,1);
    const float &rx = r[0], &ry = r[1], &rz = r[2], &tx = t[0], &ty=t[1], &tz = t[2];
    const float cx = cos(rx), cy = cos(-ry), cz = cos(-rz), sx = sin(rx), sy = sin(-ry), sz = sin(-rz);
    const float Rx0 = cy*cz-sx*sy*sz, Rx1 = cy*sz+cz*sx*sy, Rx2 = -sy*cx;
    const float Ry0 = -sz*cx, Ry1 = cz*cx, Ry2 = sx;
    const float F = Rx0*A + Rx1*B + Rx2*C;
    const float G = Ry0*A + Ry1*B + Ry2*C;

    const float J = Rx1*D + Rx2*E;
    const float K = Ry1*D + Ry2*E;
    const float &N = Rx2;
    const float &O = Ry2;
    const float I = tx*A + ty*B + tz*C;
    const float M = ty*D + tz*E;
    const float &Q = tz;
    
    float error = 0;
    for(int i=0;i<n;++i){
      const float &Mix = _M[i].x, Miy = _M[i].y, Iix = _I[i].x, Iiy = _I[i].y;
      const float R = F*Mix + G*Miy + I;
      const float S = J*Mix + K*Miy + M;
      const float T_inv = 1.0/(N*Mix + O*Miy + Q);
      error += sqrt( sqr(R*T_inv - Iix) + sqr(S*T_inv - Iiy) );
    }
    return error;
  }
  

  static Mat optimize_error_old(const Mat &P, const Mat &T_initial, const Point32f *M, const Point32f *I, int n){
    const float E_initial = compute_error(P,T_initial,M,I,n);
    FixedMatrix<float,1,3> r = extract_euler_angles(T_initial);
    FixedMatrix<float,1,3> t = T_initial.part<3,0,1,3>();
    URandI ridx(5);
    GRand rR(0,0.1),rT(0,1);
    FixedMatrix<float,1,3> rBest = r, tBest = t;
    float E_best = E_initial;
    DEBUG_LOG("---\ninitial error is " << E_initial);
    static const std::string what[] = {"rx","ry","rz","tx","ty","tz"};
    for(int i=0;i<10000;++i){
      int idx = ridx;

      float *change = idx > 2 ? &tBest[idx-3] : &rBest[idx];
      float save = *change;
      *change += idx > 2 ? rT : rR;
      Mat T = create_hom_4x4<float>(rBest[0],rBest[1],rBest[2],tBest[0],tBest[1],tBest[2]);
      float E_curr = compute_error(P,T,M,I,n);
      if(E_curr < E_best){
        DEBUG_LOG("new best error:" << E_curr);
        E_best = E_curr;
      }else{
        *change = save;
      }
    }
    return create_hom_4x4<float>(rBest[0],rBest[1],rBest[2],tBest[0],tBest[1],tBest[2]);
  }

  static Mat optimize_error_2(const Mat &P, const Mat &T_initial, const Point32f *M, const Point32f *I, int n){
    const float E_initial = compute_error(P,T_initial,M,I,n);
    FixedMatrix<float,1,3> r = extract_euler_angles(T_initial);
    FixedMatrix<float,1,3> t = T_initial.part<3,0,1,3>();
    FixedMatrix<float,1,3> rBest = r, tBest = t, tInit = t, rInit = r;;
    float E_best = E_initial;
    

    const int N_steps = 4;//, N_tsteps = 2;
    const float limitsR[N_steps] = {0.8, 0.4, 0.2, 0.1};//, 0.05};
    const float stepsR[N_steps] = {0.4, 0.2, 0.1, 0.025};//, 0.025};
    
    //    const float limitsT[N_tsteps] = {10, 2.5};
    //const float stepsT[N_tsteps] = {2.5, 0.5};

    Time ttt = Time::now();
    for(int s = 0;s< N_steps;++s){
      for(float drx=-limitsR[s]; drx <= limitsR[s]; drx += stepsR[s]){
        for(float dry=-limitsR[s]; dry <= limitsR[s]; dry += stepsR[s]){
          for(float drz=-limitsR[s]; drz <= limitsR[s]; drz += stepsR[s]){
            //for(float dx=-limitsT[s]; dx <= limitsT[s]; dx += stepsT[s]){
            //  for(float dy=-limitsT[s]; dy <= limitsT[s]; dy += stepsT[s]){
            //    for(float dz=-limitsT[s]; dz <= limitsT[s]; dz += stepsT[s]){
                  static const float dx=0,dy=0,dz=0;
                  Mat T = create_hom_4x4<float>(r[0]+drx,r[1]+dry,r[2]+drz,t[0]+dx,t[1]+dy,t[2]+dz);
                  float E_curr = compute_error(P,T,M,I,n);
                  if(E_curr < E_best){
                    DEBUG_LOG("new best error:" << E_curr << " s=" << s);
                    E_best = E_curr;
                    rBest = r + FixedMatrix<float,1,3>(drx,dry,drz);
                    tBest = t + FixedMatrix<float,1,3>(dx,dy,dz);
                  }
                  //     }
          //  }
          //  }
          }
        }
      }
      r = rBest;
      t = tBest;
    }
    std::cout << "dt: "<<(Time::now()-ttt).toMilliSecondsDouble() << "\n";

    FixedMatrix<float,1,6> A(tInit[0],tInit[1],tInit[2],rInit[0],rInit[1],rInit[2]);
    FixedMatrix<float,1,6> B(tBest[0],tBest[1],tBest[2],rBest[0],rBest[1],rBest[2]);
    FixedMatrix<float,1,6> delta = (B-A)*0.1;
    for(int i=0;i<10;++i){
      FixedMatrix<float,1,6> C = A + delta * float(i);
      Mat T = create_hom_4x4<float>(C[3],C[4],C[5],C[0],C[1],C[2]);
      float e = compute_error(P,T,M,I,n);
      std::cout << e << " ";
    }
    

    DEBUG_LOG("optimization deltas dr:" << (rInit-rBest).transp() << " dt:" << (tInit-tBest).transp());
    
    return create_hom_4x4<float>(rBest[0],rBest[1],rBest[2],tBest[0],tBest[1],tBest[2]);
  }

  static Mat optimize_error_3(const Mat &P, const Mat &T_initial, const Point32f *M, const Point32f *I, int n){
    const float E_initial = compute_error(P,T_initial,M,I,n);
    typedef FixedMatrix<float,1,3> V3;
    typedef FixedMatrix<float,1,6> V6;
    
    V3 r = extract_euler_angles(T_initial);
    V3 t = T_initial.part<3,0,1,3>();
    V6 s(r[0],r[1],r[2],t[0],t[1],t[2]);
    //    V6 sInit = s, sBest = s;
    //    float E_best = E_initial;
    
    float gStep = 0.1;
    float dx = 0.0001;
    //float e[3];
    float eBest = E_initial;

    for(int i=0;i<30;++i){
      std::cout << "step " << i << " eBest:" << eBest << " gStep:" << gStep << std::endl;
      for(int f=0;f<6;++f){
        std::cout << "  f:" << f << std::endl;
        V6 sTmp = s;
        sTmp[f]+=dx;
        float ePlus = compute_error(P,sTmp,M,I,n);
        std::cout << "    d+ : " << (ePlus-eBest) << std::endl;
        if(ePlus < eBest){
          eBest = ePlus;
          s[f] += gStep;
          continue;
        }
        sTmp[f] -= 2*dx;
        float eMinus = compute_error(P,sTmp,M,I,n);
        std::cout << "    d- : " << ePlus-eBest << std::endl;
        if(eMinus < eBest){
          eBest = eMinus;
          s[f] -= gStep;;
        }
      }
      gStep *= 0.95;
    }
    std::terminate();
    return create_hom_4x4<float>(s[0],s[1],s[2],s[3],s[4],s[5]);
  }

  static Mat optimize_error_4(const Mat &P, const Mat &T_initial, const Point32f *M, const Point32f *I, int n){
    const float E_initial = compute_error(P,T_initial,M,I,n);
    FixedMatrix<float,1,3> r = extract_euler_angles(T_initial);
    FixedMatrix<float,1,3> t = T_initial.part<3,0,1,3>();
    FixedMatrix<float,1,3> rBest = r, tBest = t, tInit = t, rInit = r;;
    float E_best = E_initial;
    

    /*
        float interval = 1.2;
        const float posFactor = 5;
        const int steps = 30;
        const float decreaseFactor = 0.9;
    */
    float interval = pa("-interval");
    const float posFactor = pa("-posFactor");
    const int steps = pa("-steps");
    const float decreaseFactor = pa("-decreaseFactor");

    std::cout << "interval: " << interval << "   pos factor:" << posFactor 
              << "   steps:" << steps <<  "  decrease:" << decreaseFactor << "\t";

    Time ttt = Time::now();
    for(int s=0;s<steps;++s){
      
      for(int rx=-1;rx<=1;++rx){
        float drx = rx*interval;
        for(int ry=-1;ry<=1;++ry){
          float dry = ry*interval;
          for(int rz=-1;rz<=1;++rz){
            float drz = rz*interval;
            /// todo: optimize position as well (perhaps : opt pos -> rot -> pos -> rot im wechsel ...
            Mat T = create_hom_4x4<float>(r[0]+drx,r[1]+dry,r[2]+drz,t[0],t[1],t[2]);
            float E_curr = compute_error(P,T,M,I,n);
            if(E_curr < E_best){
              E_best = E_curr;
              rBest = r + FixedMatrix<float,1,3>(drx,dry,drz);
            }
          }
        }
      }
      
      for(int tx=-1;tx<=1;++tx){
        float dtx = tx*interval*posFactor;
        for(int ty=-1;ty<=1;++ty){
          float dty = ty*interval*posFactor;
          for(int tz=-1;tz<=1;++tz){
            float dtz = tz*interval*posFactor;
            Mat T = create_hom_4x4<float>(r[0],r[1],r[2],t[0]+dtx,t[1]+dty,t[2]+dtz);
            float E_curr = compute_error(P,T,M,I,n);
            if(E_curr < E_best){
              E_best = E_curr;
              tBest = t + FixedMatrix<float,1,3>(dtx,dty,dtz);
            }
          }
        }
      }


      interval *= decreaseFactor;
      r = rBest;
      t = tBest;
    }

#if 0
    FixedMatrix<float,1,6> A(tInit[0],tInit[1],tInit[2],rInit[0],rInit[1],rInit[2]);
    FixedMatrix<float,1,6> B(tBest[0],tBest[1],tBest[2],rBest[0],rBest[1],rBest[2]);
    FixedMatrix<float,1,6> delta = (B-A)*0.1;
    for(int i=0;i<10;++i){
      FixedMatrix<float,1,6> C = A + delta * float(i);
      Mat T = create_hom_4x4<float>(C[3],C[4],C[5],C[0],C[1],C[2]);
      float e = compute_error(P,T,M,I,n);
      std::cout << e << " ";
    }
#endif
    std::cout << "dt: "<<(Time::now()-ttt).toMilliSecondsDouble() << ":::" <<E_initial << " --> " << E_best << std::endl;
    //    DEBUG_LOG("optimization deltas dr:" << (rInit-rBest).transp() << " dt:" 
    //          << (tInit-tBest).transp() << " dE:" << E_initial-E_best 
    //          << " (abs end error: " << E_best <<")");
    
    return create_hom_4x4<float>(rBest[0],rBest[1],rBest[2],tBest[0],tBest[1],tBest[2]);
  }

  static Mat optimize_error_5(const Mat &P, const Mat &T_initial, const Point32f *M, const Point32f *I, int n){
    const float E_initial = compute_error(P,T_initial,M,I,n);
    FixedMatrix<float,1,3> r = extract_euler_angles(T_initial);
    FixedMatrix<float,1,3> t = T_initial.part<3,0,1,3>();
    FixedMatrix<float,1,3> rBest = r, tBest = t, tInit = t, rInit = r;;
    float E_best = E_initial;
    
    /*
        float interval = 1.2;
        const float posFactor = 5;
        const int steps = 30;
        const float decreaseFactor = 0.9;
    */
    float interval = pa("-interval");
    const float posFactor = pa("-posFactor");
    const int steps = pa("-steps");
    const float decreaseFactor = pa("-decreaseFactor");

    std::cout << "interval: " << interval << "   pos factor:" << posFactor 
              << "   steps:" << steps <<  "  decrease:" << decreaseFactor << "\t";

    Time ttt = Time::now();
    FixedMatrix<float,1,3> rCurr, tCurr;
    for(int s=0;s<steps;++s){
      
      for(int rx=-1;rx<=1;++rx){
        rCurr[0] = r[0]+rx*interval;
        for(int ry=-1;ry<=1;++ry){
          rCurr[1] = r[1]+ry*interval;
          for(int rz=-1;rz<=1;++rz){
            rCurr[2] = r[2]+rz*interval;
            float E_curr = compute_error_opt(P,rCurr,t,M,I,n);
            if(E_curr < E_best){
              E_best = E_curr;
              rBest = rCurr;
            }
          }
        }
      }
      
      for(int tx=-1;tx<=1;++tx){
        tCurr[0] = t[0] + tx*interval*posFactor;
        for(int ty=-1;ty<=1;++ty){
          tCurr[1] = t[1] + ty*interval*posFactor;
          for(int tz=-1;tz<=1;++tz){
            tCurr[2] = t[2] + tz*interval*posFactor;
            float E_curr = compute_error_opt(P,r,tCurr,M,I,n);
            if(E_curr < E_best){
              E_best = E_curr;
              tBest = tCurr;
            }
          }
        }
      }


      interval *= decreaseFactor;
      r = rBest;
      t = tBest;
    }


    std::cout << "dt: "<<(Time::now()-ttt).toMilliSecondsDouble() << ":::" <<E_initial << " --> " << E_best << std::endl;
  
    
    return create_hom_4x4<float>(rBest[0],rBest[1],rBest[2],tBest[0],tBest[1],tBest[2]);
  }


    
  Mat CoplanarPointPoseEstimator::getPose(int n, 
                                          const Point32f *modelPoints, 
                                          const Point32f *imagePoints, 
                                          const Camera &cam){
    float ifx = 1.0f/(cam.getFocalLength()*cam.getSamplingResolutionX());
    float ify = 1.0f/(cam.getFocalLength()*cam.getSamplingResolutionY());
    float icx = -ifx * cam.getPrincipalPointOffset().x;
    float icy = -ify * cam.getPrincipalPointOffset().y;

    // please note, the old implementation can be found in svn rev. 2753
    std::vector<Point32f> ips(n);//, pbs(n);
    for(int i=0;i<n;++i){
      ips[i] = Point32f(ifx*imagePoints[i].x+icx, ify * imagePoints[i].y+icy);
    }
  
    Homography2D H(ips.data(),modelPoints,n);
    
    // homography error, which is always 0
    //float err = 0;
    // for(int i=0;i<n;++i){
    //  err += H.apply(modelPoints[i]).distanceTo(ips[i]);
    //}
    //DEBUG_LOG("the error is " << err);

    H *= 1.0/sqrt( pow(H(0,0),2) + pow(H(0,1),2) + pow(H(0,2),2) ); 
    
    // if H solves Ax=0 then also -H solves it, therefore, we always
    // take the solution, where z is positive (object is in front of the camera)
    
    if(H(2,2) < 0){
      H *= -1;
    }

    FixedColVector<float,3> R1 = H.col(0);
    FixedColVector<float,3> R2 = H.col(1);
    R2 -= R1*(R1.transp()*R2)[0];  
    R2.normalize();
    FixedColVector<float,3> R3 = cross3(R1,R2);
    
    data->T.part<0,0,3,3>() = data->R = (R1,R2,R3);

    // -R * t -> provides translation part in 'clear-text'
    data->T.part<3,0,1,3>() = data->R.transp()*FixedColVector<float,3>( -H(2,0),-H(2,1),-H(2,2) ); 
    
    // this provides the original camera CS-Transformation Matrix
    data->T.part<3,0,1,3>() = FixedColVector<float,3>( H(2,0),H(2,1),H(2,2) );
    
    data->T(0,3) = data->T(1,3) = data->T(2,3) = 0;
    data->T(3,3) = 1;

    data->T = optimize_error_5(cam.getProjectionMatrix(), data->T, modelPoints, imagePoints, n);
    
#if 0
    Mat M = cam.getCSTransformationMatrix().inv()*data->T;
    float error = 0;
    for(int i=0;i<n;++i){
      Vec tmp = M * Vec(modelPoints[i].x,modelPoints[i].y,0,1);
      Point32f p = cam.project(tmp);
      error += p.distanceTo(imagePoints[i]);
    }

    Mat P = cam.getProjectionMatrix();    
    float error2 = 0;
    for(int i=0;i<n;++i){
      Vec tmp = homogenize( P * data->T * Vec(modelPoints[i].x,modelPoints[i].y,0,1) );
      error2 += Point32f(tmp[0],tmp[1]).distanceTo(imagePoints[i]);
    }
    std::cout << "error: " << error <<  "  error2:" << error2 << std::endl;

    /* explanation: 
                  ||                                     ||  where, I: imagePoints
       E(T) = sum || I[i] - project(C⁻1 * T * vec4(M[i]) ||         M: modelPoints
               i  ||                                     ||       C⁻1: inverse cam transform

        but since, project(x) p2(hom(P*C*x)), where P: projection matrix and C: camera matrix,
        and p2: extracts x and y from a 4D homogenious vector,
        
                  ||                                   ||  where,   P: cam projection matrix
       E(T) = sum || I[i] - p2(hom(P * T * vec4(M[i])) ||         hom: homogenization
               i  ||                                   ||          p2(x,y,z,w) = (x,y)
        
        The question, that remains is, how this function is minimized and, if we assume a 
        closed solution in least sqaure scene, if the initial T does already minimize E(T)
        if T is a homogeneous transform [R|t]

        * first approach: try to use stochastic search (perhaps coarse to fine) to find
          better solutions for T iteratively
        * 2nd approach: try to derivate E(T) wrt. T in order to implement gradient descent
          to optimize T
        * find out whether a closed form solution for E(T) is already found with the method
          above 
    */
#endif
    if(data->referenceFrame == cameraFrame){
      return data->T;
    }else{
      return cam.getCSTransformationMatrix().inv()*data->T;
    }
  }

}
