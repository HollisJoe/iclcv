/********************************************************************
 **                Image Component Library (ICL)                    **
 **                                                                 **
 ** Copyright (C) 2006-2010 CITEC, University of Bielefeld          **
 **                         Neuroinformatics Group                  **
 ** Website: www.iclcv.org and                                      **
 **          http://opensource.cit-ec.de/projects/icl               **
 **                                                                 **
 ** File   : ICLGeom/examples/intrinsic-calibrator-demo.cpp         **
 ** Module : ICLGeom                                                **
 ** Authors: Christian Groszewski                                   **
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
#include <ICLIO/IntrinsicCalibrator.h>

using namespace icl;

//world coordinates (x,y,z), columnwise beginning from last column
double ar[3*156] = {
		0.0000000e+000 , 3.0000000e+001 , 6.0000000e+001 , 9.0000000e+001 , 1.2000000e+002 , 1.5000000e+002 , 1.8000000e+002 , 2.1000000e+002 , 2.4000000e+002 , 2.7000000e+002 , 3.0000000e+002 , 3.3000000e+002 , 0.0000000e+000 , 3.0000000e+001 , 6.0000000e+001 , 9.0000000e+001 , 1.2000000e+002 , 1.5000000e+002 , 1.8000000e+002 , 2.1000000e+002 , 2.4000000e+002 , 2.7000000e+002 , 3.0000000e+002 , 3.3000000e+002 , 0.0000000e+000 , 3.0000000e+001 , 6.0000000e+001 , 9.0000000e+001 , 1.2000000e+002 , 1.5000000e+002 , 1.8000000e+002 , 2.1000000e+002 , 2.4000000e+002 , 2.7000000e+002 , 3.0000000e+002 , 3.3000000e+002 , 0.0000000e+000 , 3.0000000e+001 , 6.0000000e+001 , 9.0000000e+001 , 1.2000000e+002 , 1.5000000e+002 , 1.8000000e+002 , 2.1000000e+002 , 2.4000000e+002 , 2.7000000e+002 , 3.0000000e+002 , 3.3000000e+002 , 0.0000000e+000 , 3.0000000e+001 , 6.0000000e+001 , 9.0000000e+001 , 1.2000000e+002 , 1.5000000e+002 , 1.8000000e+002 , 2.1000000e+002 , 2.4000000e+002 , 2.7000000e+002 , 3.0000000e+002 , 3.3000000e+002 , 0.0000000e+000 , 3.0000000e+001 , 6.0000000e+001 , 9.0000000e+001 , 1.2000000e+002 , 1.5000000e+002 , 1.8000000e+002 , 2.1000000e+002 , 2.4000000e+002 , 2.7000000e+002 , 3.0000000e+002 , 3.3000000e+002 , 0.0000000e+000 , 3.0000000e+001 , 6.0000000e+001 , 9.0000000e+001 , 1.2000000e+002 , 1.5000000e+002 , 1.8000000e+002 , 2.1000000e+002 , 2.4000000e+002 , 2.7000000e+002 , 3.0000000e+002 , 3.3000000e+002 , 0.0000000e+000 , 3.0000000e+001 , 6.0000000e+001 , 9.0000000e+001 , 1.2000000e+002 , 1.5000000e+002 , 1.8000000e+002 , 2.1000000e+002 , 2.4000000e+002 , 2.7000000e+002 , 3.0000000e+002 , 3.3000000e+002 , 0.0000000e+000 , 3.0000000e+001 , 6.0000000e+001 , 9.0000000e+001 , 1.2000000e+002 , 1.5000000e+002 , 1.8000000e+002 , 2.1000000e+002 , 2.4000000e+002 , 2.7000000e+002 , 3.0000000e+002 , 3.3000000e+002 , 0.0000000e+000 , 3.0000000e+001 , 6.0000000e+001 , 9.0000000e+001 , 1.2000000e+002 , 1.5000000e+002 , 1.8000000e+002 , 2.1000000e+002 , 2.4000000e+002 , 2.7000000e+002 , 3.0000000e+002 , 3.3000000e+002 , 0.0000000e+000 , 3.0000000e+001 , 6.0000000e+001 , 9.0000000e+001 , 1.2000000e+002 , 1.5000000e+002 , 1.8000000e+002 , 2.1000000e+002 , 2.4000000e+002 , 2.7000000e+002 , 3.0000000e+002 , 3.3000000e+002 , 0.0000000e+000 , 3.0000000e+001 , 6.0000000e+001 , 9.0000000e+001 , 1.2000000e+002 , 1.5000000e+002 , 1.8000000e+002 , 2.1000000e+002 , 2.4000000e+002 , 2.7000000e+002 , 3.0000000e+002 , 3.3000000e+002 , 0.0000000e+000 , 3.0000000e+001 , 6.0000000e+001 , 9.0000000e+001 , 1.2000000e+002 , 1.5000000e+002 , 1.8000000e+002 , 2.1000000e+002 , 2.4000000e+002 , 2.7000000e+002 , 3.0000000e+002 , 3.3000000e+002,
		3.6000000e+002 , 3.6000000e+002 , 3.6000000e+002 , 3.6000000e+002 , 3.6000000e+002 , 3.6000000e+002 , 3.6000000e+002 , 3.6000000e+002 , 3.6000000e+002 , 3.6000000e+002 , 3.6000000e+002 , 3.6000000e+002 , 3.3000000e+002 , 3.3000000e+002 , 3.3000000e+002 , 3.3000000e+002 , 3.3000000e+002 , 3.3000000e+002 , 3.3000000e+002 , 3.3000000e+002 , 3.3000000e+002 , 3.3000000e+002 , 3.3000000e+002 , 3.3000000e+002 , 3.0000000e+002 , 3.0000000e+002 , 3.0000000e+002 , 3.0000000e+002 , 3.0000000e+002 , 3.0000000e+002 , 3.0000000e+002 , 3.0000000e+002 , 3.0000000e+002 , 3.0000000e+002 , 3.0000000e+002 , 3.0000000e+002 , 2.7000000e+002 , 2.7000000e+002 , 2.7000000e+002 , 2.7000000e+002 , 2.7000000e+002 , 2.7000000e+002 , 2.7000000e+002 , 2.7000000e+002 , 2.7000000e+002 , 2.7000000e+002 , 2.7000000e+002 , 2.7000000e+002 , 2.4000000e+002 , 2.4000000e+002 , 2.4000000e+002 , 2.4000000e+002 , 2.4000000e+002 , 2.4000000e+002 , 2.4000000e+002 , 2.4000000e+002 , 2.4000000e+002 , 2.4000000e+002 , 2.4000000e+002 , 2.4000000e+002 , 2.1000000e+002 , 2.1000000e+002 , 2.1000000e+002 , 2.1000000e+002 , 2.1000000e+002 , 2.1000000e+002 , 2.1000000e+002 , 2.1000000e+002 , 2.1000000e+002 , 2.1000000e+002 , 2.1000000e+002 , 2.1000000e+002 , 1.8000000e+002 , 1.8000000e+002 , 1.8000000e+002 , 1.8000000e+002 , 1.8000000e+002 , 1.8000000e+002 , 1.8000000e+002 , 1.8000000e+002 , 1.8000000e+002 , 1.8000000e+002 , 1.8000000e+002 , 1.8000000e+002 , 1.5000000e+002 , 1.5000000e+002 , 1.5000000e+002 , 1.5000000e+002 , 1.5000000e+002 , 1.5000000e+002 , 1.5000000e+002 , 1.5000000e+002 , 1.5000000e+002 , 1.5000000e+002 , 1.5000000e+002 , 1.5000000e+002 , 1.2000000e+002 , 1.2000000e+002 , 1.2000000e+002 , 1.2000000e+002 , 1.2000000e+002 , 1.2000000e+002 , 1.2000000e+002 , 1.2000000e+002 , 1.2000000e+002 , 1.2000000e+002 , 1.2000000e+002 , 1.2000000e+002 , 9.0000000e+001 , 9.0000000e+001 , 9.0000000e+001 , 9.0000000e+001 , 9.0000000e+001 , 9.0000000e+001 , 9.0000000e+001 , 9.0000000e+001 , 9.0000000e+001 , 9.0000000e+001 , 9.0000000e+001 , 9.0000000e+001 , 6.0000000e+001 , 6.0000000e+001 , 6.0000000e+001 , 6.0000000e+001 , 6.0000000e+001 , 6.0000000e+001 , 6.0000000e+001 , 6.0000000e+001 , 6.0000000e+001 , 6.0000000e+001 , 6.0000000e+001 , 6.0000000e+001 , 3.0000000e+001 , 3.0000000e+001 , 3.0000000e+001 , 3.0000000e+001 , 3.0000000e+001 , 3.0000000e+001 , 3.0000000e+001 , 3.0000000e+001 , 3.0000000e+001 , 3.0000000e+001 , 3.0000000e+001 , 3.0000000e+001 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000,
		0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000 , 0.0000000e+000
};
//world coordiantes
DynMatrix<icl64f> X(156,3,ar);

double br2[5*2*156] = {
		//x for pic1
		4.3365534e+002 , 4.3843528e+002 , 4.4331428e+002 , 4.4847617e+002 , 4.5352824e+002 , 4.5945321e+002 , 4.6495320e+002 , 4.7154880e+002 , 4.7769446e+002 , 4.8479567e+002 , 4.9161997e+002 , 4.9958974e+002 , 4.1283196e+002 , 4.1669073e+002 , 4.2140114e+002 , 4.2570868e+002 , 4.3065216e+002 , 4.3543313e+002 , 4.4096109e+002 , 4.4640474e+002 , 4.5250035e+002 , 4.5831738e+002 , 4.6504969e+002 , 4.7139663e+002 , 3.9152723e+002 , 3.9527098e+002 , 3.9892822e+002 , 4.0308824e+002 , 4.0717621e+002 , 4.1164959e+002 , 4.1605225e+002 , 4.2129253e+002 , 4.2607652e+002 , 4.3189473e+002 , 4.3715477e+002 , 4.4359334e+002 , 3.7014094e+002 , 3.7289723e+002 , 3.7629073e+002 , 3.7960943e+002 , 3.8326692e+002 , 3.8676698e+002 , 3.9100134e+002 , 3.9495338e+002 , 3.9971671e+002 , 4.0403017e+002 , 4.0917831e+002 , 4.1397347e+002 , 3.4814389e+002 , 3.5059639e+002 , 3.5312232e+002 , 3.5615560e+002 , 3.5874901e+002 , 3.6216303e+002 , 3.6504624e+002 , 3.6878192e+002 , 3.7214887e+002 , 3.7637913e+002 , 3.8008284e+002 , 3.8460403e+002 , 3.2616477e+002 , 3.2797973e+002 , 3.2995967e+002 , 3.3214409e+002 , 3.3447993e+002 , 3.3662959e+002 , 3.3927129e+002 , 3.4166825e+002 , 3.4478295e+002 , 3.4754605e+002 , 3.5088215e+002 , 3.5374686e+002 , 3.0360011e+002 , 3.0508973e+002 , 3.0632687e+002 , 3.0793595e+002 , 3.0933473e+002 , 3.1109714e+002 , 3.1260350e+002 , 3.1456730e+002 , 3.1642789e+002 , 3.1880302e+002 , 3.2075663e+002 , 3.2336644e+002 , 2.8137107e+002 , 2.8185342e+002 , 2.8263893e+002 , 2.8341631e+002 , 2.8434614e+002 , 2.8511167e+002 , 2.8605615e+002 , 2.8692739e+002 , 2.8834370e+002 , 2.8925971e+002 , 2.9073513e+002 , 2.9169484e+002 , 2.5854825e+002 , 2.5877908e+002 , 2.5867182e+002 , 2.5897239e+002 , 2.5883172e+002 , 2.5913211e+002 , 2.5906359e+002 , 2.5927129e+002 , 2.5944940e+002 , 2.5986515e+002 , 2.5990954e+002 , 2.6044664e+002 , 2.3604825e+002 , 2.3544519e+002 , 2.3487482e+002 , 2.3422021e+002 , 2.3358752e+002 , 2.3274913e+002 , 2.3219581e+002 , 2.3126047e+002 , 2.3086897e+002 , 2.2982535e+002 , 2.2944816e+002 , 2.2837909e+002 , 2.1309384e+002 , 2.1216501e+002 , 2.1060482e+002 , 2.0947933e+002 , 2.0778511e+002 , 2.0653628e+002 , 2.0476984e+002 , 2.0334187e+002 , 2.0165413e+002 , 2.0005094e+002 , 1.9831032e+002 , 1.9662336e+002 , 1.9055508e+002 , 1.8868589e+002 , 1.8672825e+002 , 1.8462462e+002 , 1.8257562e+002 , 1.8027619e+002 , 1.7794662e+002 , 1.7535848e+002 , 1.7311164e+002 , 1.7001295e+002 , 1.6770017e+002 , 1.6462919e+002 , 1.6768838e+002 , 1.6551535e+002 , 1.6264102e+002 , 1.6011227e+002 , 1.5695377e+002 , 1.5426718e+002 , 1.5066966e+002 , 1.4747855e+002 , 1.4408309e+002 , 1.4038593e+002 , 1.3659864e+002 , 1.3293151e+002
		//y for pic1
		, 1.9548176e+002 , 2.0853158e+002 , 2.2219236e+002 , 2.3654326e+002 , 2.5169311e+002 , 2.6786612e+002 , 2.8451641e+002 , 3.0273921e+002 , 3.2168202e+002 , 3.4185020e+002 , 3.6319077e+002 , 3.8584096e+002 , 1.9397430e+002 , 2.0697488e+002 , 2.2076688e+002 , 2.3528114e+002 , 2.5050814e+002 , 2.6653761e+002 , 2.8371608e+002 , 3.0179883e+002 , 3.2116101e+002 , 3.4139476e+002 , 3.6296748e+002 , 3.8579213e+002 , 1.9239145e+002 , 2.0563457e+002 , 2.1945670e+002 , 2.3387786e+002 , 2.4934669e+002 , 2.6559600e+002 , 2.8246663e+002 , 3.0105004e+002 , 3.2017744e+002 , 3.4075032e+002 , 3.6245908e+002 , 3.8580364e+002 , 1.9100416e+002 , 2.0400259e+002 , 2.1796065e+002 , 2.3241709e+002 , 2.4793369e+002 , 2.6418270e+002 , 2.8163283e+002 , 2.9994175e+002 , 3.1952492e+002 , 3.4012081e+002 , 3.6213641e+002 , 3.8556127e+002 , 1.8948591e+002 , 2.0259895e+002 , 2.1651760e+002 , 2.3133797e+002 , 2.4657345e+002 , 2.6323481e+002 , 2.8031698e+002 , 2.9907641e+002 , 3.1846739e+002 , 3.3951247e+002 , 3.6162576e+002 , 3.8528682e+002 , 1.8793736e+002 , 2.0136940e+002 , 2.1535620e+002 , 2.2982269e+002 , 2.4545323e+002 , 2.6180269e+002 , 2.7938416e+002 , 2.9785009e+002 , 3.1767243e+002 , 3.3847976e+002 , 3.6091888e+002 , 3.8460131e+002 , 1.8653770e+002 , 1.9982367e+002 , 2.1373764e+002 , 2.2842750e+002 , 2.4395517e+002 , 2.6048721e+002 , 2.7795582e+002 , 2.9670590e+002 , 3.1645127e+002 , 3.3768382e+002 , 3.5995652e+002 , 3.8399232e+002 , 1.8533495e+002 , 1.9838596e+002 , 2.1235258e+002 , 2.2720214e+002 , 2.4261693e+002 , 2.5938245e+002 , 2.7668443e+002 , 2.9564896e+002 , 3.1552862e+002 , 3.3646003e+002 , 3.5924620e+002 , 3.8322079e+002 , 1.8385145e+002 , 1.9723679e+002 , 2.1114497e+002 , 2.2577670e+002 , 2.4148653e+002 , 2.5792873e+002 , 2.7555910e+002 , 2.9430041e+002 , 3.1417988e+002 , 3.3553324e+002 , 3.5803762e+002 , 3.8225332e+002 , 1.8253664e+002 , 1.9576020e+002 , 2.0977409e+002 , 2.2444832e+002 , 2.3997192e+002 , 2.5657763e+002 , 2.7405463e+002 , 2.9302103e+002 , 3.1299528e+002 , 3.3415725e+002 , 3.5684139e+002 , 3.8117268e+002 , 1.8137013e+002 , 1.9445101e+002 , 2.0841511e+002 , 2.2327301e+002 , 2.3865810e+002 , 2.5540114e+002 , 2.7273997e+002 , 2.9169472e+002 , 3.1169026e+002 , 3.3280300e+002 , 3.5561161e+002 , 3.7978329e+002 , 1.7999538e+002 , 1.9334244e+002 , 2.0726091e+002 , 2.2186052e+002 , 2.3748262e+002 , 2.5393218e+002 , 2.7150835e+002 , 2.9017783e+002 , 3.1005818e+002 , 3.3149880e+002 , 3.5397811e+002 , 3.7831497e+002 , 1.7893294e+002 , 1.9193703e+002 , 2.0589103e+002 , 2.2046064e+002 , 2.3605003e+002 , 2.5250452e+002 , 2.7002907e+002 , 2.8868263e+002 , 3.0868022e+002 , 3.2981261e+002 , 3.5239600e+002 , 3.7665823e+002
		//x for pic2
		, 4.6615688e+002 , 4.7006936e+002 , 4.7332479e+002 , 4.7749976e+002 , 4.8085874e+002 , 4.8509659e+002 , 4.8867804e+002 , 4.9284737e+002 , 4.9658977e+002 , 5.0078475e+002 , 5.0450449e+002 , 5.0896782e+002 , 4.4342638e+002 , 4.4638265e+002 , 4.4960735e+002 , 4.5325008e+002 , 4.5648470e+002 , 4.5978175e+002 , 4.6326834e+002 , 4.6652566e+002 , 4.7027684e+002 , 4.7326521e+002 , 4.7737823e+002 , 4.8053083e+002 , 4.1997513e+002 , 4.2280275e+002 , 4.2537783e+002 , 4.2854380e+002 , 4.3115907e+002 , 4.3420617e+002 , 4.3689328e+002 , 4.4016008e+002 , 4.4296924e+002 , 4.4602707e+002 , 4.4886335e+002 , 4.5244431e+002 , 3.9623444e+002 , 3.9843526e+002 , 4.0057213e+002 , 4.0296549e+002 , 4.0547053e+002 , 4.0762986e+002 , 4.1017702e+002 , 4.1247819e+002 , 4.1529290e+002 , 4.1718966e+002 , 4.2023149e+002 , 4.2241933e+002 , 3.7201572e+002 , 3.7393207e+002 , 3.7519656e+002 , 3.7738152e+002 , 3.7904237e+002 , 3.8116319e+002 , 3.8266411e+002 , 3.8467699e+002 , 3.8647539e+002 , 3.8842721e+002 , 3.9031107e+002 , 3.9257907e+002 , 3.4764920e+002 , 3.4875506e+002 , 3.4981198e+002 , 3.5109804e+002 , 3.5256486e+002 , 3.5381976e+002 , 3.5492328e+002 , 3.5611261e+002 , 3.5764371e+002 , 3.5853559e+002 , 3.6045611e+002 , 3.6146400e+002 , 3.2281538e+002 , 3.2351246e+002 , 3.2377006e+002 , 3.2466606e+002 , 3.2536278e+002 , 3.2628196e+002 , 3.2659846e+002 , 3.2740785e+002 , 3.2789286e+002 , 3.2868787e+002 , 3.2947110e+002 , 3.3050746e+002 , 2.9785994e+002 , 2.9779115e+002 , 2.9792507e+002 , 2.9781343e+002 , 2.9819918e+002 , 2.9814964e+002 , 2.9812121e+002 , 2.9805486e+002 , 2.9830747e+002 , 2.9814483e+002 , 2.9861473e+002 , 2.9844162e+002 , 2.7254175e+002 , 2.7216058e+002 , 2.7155092e+002 , 2.7093199e+002 , 2.7041837e+002 , 2.6999199e+002 , 2.6916676e+002 , 2.6870412e+002 , 2.6792310e+002 , 2.6765482e+002 , 2.6691024e+002 , 2.6660363e+002 , 2.4750248e+002 , 2.4624497e+002 , 2.4527015e+002 , 2.4389838e+002 , 2.4291931e+002 , 2.4157789e+002 , 2.4034793e+002 , 2.3886060e+002 , 2.3779779e+002 , 2.3658529e+002 , 2.3551783e+002 , 2.3406203e+002 , 2.2183874e+002 , 2.2029686e+002 , 2.1845409e+002 , 2.1662169e+002 , 2.1483383e+002 , 2.1314549e+002 , 2.1101108e+002 , 2.0927622e+002 , 2.0718896e+002 , 2.0560327e+002 , 2.0348074e+002 , 2.0174627e+002 , 1.9667831e+002 , 1.9433524e+002 , 1.9213837e+002 , 1.8946506e+002 , 1.8733465e+002 , 1.8457434e+002 , 1.8221220e+002 , 1.7948231e+002 , 1.7706154e+002 , 1.7440649e+002 , 1.7213384e+002 , 1.6928984e+002 , 1.7133738e+002 , 1.6842921e+002 , 1.6544299e+002 , 1.6245724e+002 , 1.5952814e+002 , 1.5651858e+002 , 1.5290922e+002 , 1.4992494e+002 , 1.4650837e+002 , 1.4361157e+002 , 1.4014702e+002 , 1.3719256e+002
		//y for pic2
		, 1.3043323e+002 , 1.4971680e+002 , 1.6919087e+002 , 1.9010007e+002 , 2.1138017e+002 , 2.3400234e+002 , 2.5714760e+002 , 2.8175941e+002 , 3.0692118e+002 , 3.3350671e+002 , 3.6050536e+002 , 3.8911300e+002 , 1.2835887e+002 , 1.4718742e+002 , 1.6744102e+002 , 1.8797828e+002 , 2.0968029e+002 , 2.3235510e+002 , 2.5586670e+002 , 2.8039504e+002 , 3.0612911e+002 , 3.3242677e+002 , 3.6034320e+002 , 3.8888107e+002 , 1.2591282e+002 , 1.4529273e+002 , 1.6514621e+002 , 1.8606635e+002 , 2.0777283e+002 , 2.3060816e+002 , 2.5425811e+002 , 2.7942190e+002 , 3.0507664e+002 , 3.3192668e+002 , 3.5977059e+002 , 3.8874845e+002 , 1.2372215e+002 , 1.4281067e+002 , 1.6319887e+002 , 1.8406164e+002 , 2.0591657e+002 , 2.2883465e+002 , 2.5279128e+002 , 2.7785767e+002 , 3.0386916e+002 , 3.3096236e+002 , 3.5932607e+002 , 3.8835916e+002 , 1.2142236e+002 , 1.4079136e+002 , 1.6099297e+002 , 1.8209764e+002 , 2.0414949e+002 , 2.2733610e+002 , 2.5125733e+002 , 2.7650157e+002 , 3.0261343e+002 , 3.3005950e+002 , 3.5835680e+002 , 3.8795909e+002 , 1.1944580e+002 , 1.3877423e+002 , 1.5916639e+002 , 1.8020878e+002 , 2.0231865e+002 , 2.2558214e+002 , 2.4973988e+002 , 2.7520181e+002 , 3.0153091e+002 , 3.2894414e+002 , 3.5764298e+002 , 3.8747719e+002 , 1.1731603e+002 , 1.3669768e+002 , 1.5708993e+002 , 1.7830680e+002 , 2.0049799e+002 , 2.2381108e+002 , 2.4808471e+002 , 2.7369191e+002 , 3.0016372e+002 , 3.2781337e+002 , 3.5644954e+002 , 3.8653871e+002 , 1.1542882e+002 , 1.3476016e+002 , 1.5526804e+002 , 1.7647659e+002 , 1.9869638e+002 , 2.2217008e+002 , 2.4644511e+002 , 2.7209378e+002 , 2.9869660e+002 , 3.2646939e+002 , 3.5555171e+002 , 3.8564094e+002 , 1.1353346e+002 , 1.3301497e+002 , 1.5350036e+002 , 1.7466946e+002 , 1.9701165e+002 , 2.2041579e+002 , 2.4477059e+002 , 2.7047105e+002 , 2.9740460e+002 , 3.2531718e+002 , 3.5423060e+002 , 3.8443617e+002 , 1.1177556e+002 , 1.3136968e+002 , 1.5170998e+002 , 1.7312717e+002 , 1.9546168e+002 , 2.1876310e+002 , 2.4334384e+002 , 2.6889746e+002 , 2.9579679e+002 , 3.2371549e+002 , 3.5283554e+002 , 3.8330696e+002 , 1.1023098e+002 , 1.2965986e+002 , 1.5010390e+002 , 1.7142807e+002 , 1.9372375e+002 , 2.1722454e+002 , 2.4163290e+002 , 2.6740653e+002 , 2.9420068e+002 , 3.2198456e+002 , 3.5138116e+002 , 3.8172544e+002 , 1.0857214e+002 , 1.2811661e+002 , 1.4842184e+002 , 1.6980056e+002 , 1.9202133e+002 , 2.1554599e+002 , 2.3984602e+002 , 2.6566948e+002 , 2.9242849e+002 , 3.2035304e+002 , 3.4966438e+002 , 3.8000665e+002 , 1.0728341e+002 , 1.2656822e+002 , 1.4698797e+002 , 1.6813574e+002 , 1.9049742e+002 , 2.1385151e+002 , 2.3824594e+002 , 2.6386552e+002 , 2.9069916e+002 , 3.1856292e+002 , 3.4780579e+002 , 3.7815281e+002
		, 4.9501472e+002 , 4.9527459e+002 , 4.9543935e+002 , 4.9553896e+002 , 4.9527903e+002 , 4.9522556e+002 , 4.9459880e+002 , 4.9440267e+002 , 4.9317955e+002 , 4.9280294e+002 , 4.9151710e+002 , 4.9055606e+002 , 4.7095614e+002 , 4.7031359e+002 , 4.7029025e+002 , 4.6964303e+002 , 4.6916242e+002 , 4.6820298e+002 , 4.6730729e+002 , 4.6604066e+002 , 4.6491691e+002 , 4.6325066e+002 , 4.6198400e+002 , 4.5968751e+002 , 4.4657850e+002 , 4.4553504e+002 , 4.4468284e+002 , 4.4372255e+002 , 4.4243629e+002 , 4.4115951e+002 , 4.3950423e+002 , 4.3791703e+002 , 4.3588003e+002 , 4.3426933e+002 , 4.3150243e+002 , 4.2954881e+002 , 4.2185179e+002 , 4.2050317e+002 , 4.1886417e+002 , 4.1736173e+002 , 4.1560806e+002 , 4.1347344e+002 , 4.1146614e+002 , 4.0888649e+002 , 4.0677216e+002 , 4.0374109e+002 , 4.0121879e+002 , 3.9776240e+002 , 3.9703122e+002 , 3.9514148e+002 , 3.9281568e+002 , 3.9088908e+002 , 3.8837495e+002 , 3.8581697e+002 , 3.8287145e+002 , 3.8015321e+002 , 3.7692549e+002 , 3.7388049e+002 , 3.7004553e+002 , 3.6652235e+002 , 3.7221989e+002 , 3.6955237e+002 , 3.6672844e+002 , 3.6415336e+002 , 3.6121716e+002 , 3.5792211e+002 , 3.5447540e+002 , 3.5073512e+002 , 3.4737337e+002 , 3.4320901e+002 , 3.3929852e+002 , 3.3457602e+002 , 3.4699750e+002 , 3.4403500e+002 , 3.4044111e+002 , 3.3736475e+002 , 3.3360047e+002 , 3.3008529e+002 , 3.2575345e+002 , 3.2172746e+002 , 3.1733787e+002 , 3.1261342e+002 , 3.0783659e+002 , 3.0317733e+002 , 3.2203330e+002 , 3.1839700e+002 , 3.1453085e+002 , 3.1046891e+002 , 3.0648230e+002 , 3.0193142e+002 , 2.9733256e+002 , 2.9233007e+002 , 2.8745808e+002 , 2.8212363e+002 , 2.7702184e+002 , 2.7104446e+002 , 2.9692629e+002 , 2.9280988e+002 , 2.8841207e+002 , 2.8381337e+002 , 2.7907238e+002 , 2.7412835e+002 , 2.6865875e+002 , 2.6340994e+002 , 2.5750298e+002 , 2.5191921e+002 , 2.4573151e+002 , 2.3972549e+002 , 2.7228922e+002 , 2.6740535e+002 , 2.6252221e+002 , 2.5719922e+002 , 2.5213033e+002 , 2.4637193e+002 , 2.4048462e+002 , 2.3435236e+002 , 2.2822468e+002 , 2.2169911e+002 , 2.1536841e+002 , 2.0815158e+002 , 2.4742984e+002 , 2.4209608e+002 , 2.3655761e+002 , 2.3068751e+002 , 2.2497948e+002 , 2.1882152e+002 , 2.1231957e+002 , 2.0567456e+002 , 1.9870464e+002 , 1.9207839e+002 , 1.8463873e+002 , 1.7741935e+002 , 2.2312158e+002 , 2.1719342e+002 , 2.1116003e+002 , 2.0455559e+002 , 1.9843166e+002 , 1.9162967e+002 , 1.8478467e+002 , 1.7737643e+002 , 1.7014699e+002 , 1.6248509e+002 , 1.5461104e+002 , 1.4664222e+002 , 1.9868441e+002 , 1.9242144e+002 , 1.8579982e+002 , 1.7910531e+002 , 1.7192759e+002 , 1.6509322e+002 , 1.5726739e+002 , 1.4954197e+002 , 1.4153993e+002 , 1.3356798e+002 , 1.2512382e+002 , 1.1680247e+002
		, 1.4648170e+002 , 1.6645910e+002 , 1.8673282e+002 , 2.0851635e+002 , 2.3067526e+002 , 2.5442851e+002 , 2.7854013e+002 , 3.0437671e+002 , 3.3078792e+002 , 3.5876131e+002 , 3.8744799e+002 , 4.1754217e+002 , 1.4223596e+002 , 1.6161782e+002 , 1.8235978e+002 , 2.0374448e+002 , 2.2617464e+002 , 2.4967829e+002 , 2.7411565e+002 , 2.9981919e+002 , 3.2643403e+002 , 3.5406954e+002 , 3.8334283e+002 , 4.1286601e+002 , 1.3734265e+002 , 1.5737071e+002 , 1.7760779e+002 , 1.9930939e+002 , 2.2145949e+002 , 2.4521581e+002 , 2.6935651e+002 , 2.9540477e+002 , 3.2179746e+002 , 3.4962849e+002 , 3.7838824e+002 , 4.0849899e+002 , 1.3311756e+002 , 1.5255846e+002 , 1.7325963e+002 , 1.9447441e+002 , 2.1684836e+002 , 2.4028492e+002 , 2.6463240e+002 , 2.9031848e+002 , 3.1712014e+002 , 3.4467162e+002 , 3.7370218e+002 , 4.0377616e+002 , 1.2855833e+002 , 1.4813483e+002 , 1.6854348e+002 , 1.8980660e+002 , 2.1216108e+002 , 2.3559984e+002 , 2.5989381e+002 , 2.8560149e+002 , 3.1216102e+002 , 3.3980522e+002 , 3.6866753e+002 , 3.9883779e+002 , 1.2435703e+002 , 1.4372526e+002 , 1.6401551e+002 , 1.8522783e+002 , 2.0758464e+002 , 2.3077396e+002 , 2.5521260e+002 , 2.8057530e+002 , 3.0732321e+002 , 3.3477592e+002 , 3.6368816e+002 , 3.9369913e+002 , 1.2005975e+002 , 1.3946104e+002 , 1.5953610e+002 , 1.8072603e+002 , 2.0279151e+002 , 2.2600719e+002 , 2.5027778e+002 , 2.7574587e+002 , 3.0218008e+002 , 3.2977745e+002 , 3.5830812e+002 , 3.8822348e+002 , 1.1591994e+002 , 1.3512452e+002 , 1.5535617e+002 , 1.7637461e+002 , 1.9819622e+002 , 2.2141601e+002 , 2.4553869e+002 , 2.7065517e+002 , 2.9715922e+002 , 3.2441828e+002 , 3.5315712e+002 , 3.8270791e+002 , 1.1199309e+002 , 1.3110421e+002 , 1.5106209e+002 , 1.7188801e+002 , 1.9380153e+002 , 2.1667972e+002 , 2.4053156e+002 , 2.6577534e+002 , 2.9192843e+002 , 3.1929947e+002 , 3.4766273e+002 , 3.7725627e+002 , 1.0811232e+002 , 1.2705304e+002 , 1.4694321e+002 , 1.6772924e+002 , 1.8946034e+002 , 2.1219320e+002 , 2.3579694e+002 , 2.6073030e+002 , 2.8674192e+002 , 3.1384602e+002 , 3.4195882e+002 , 3.7139324e+002 , 1.0441946e+002 , 1.2330124e+002 , 1.4293664e+002 , 1.6354894e+002 , 1.8504100e+002 , 2.0761520e+002 , 2.3098799e+002 , 2.5580711e+002 , 2.8164370e+002 , 3.0835166e+002 , 3.3638072e+002 , 3.6556467e+002 , 1.0071848e+002 , 1.1951803e+002 , 1.3896180e+002 , 1.5942791e+002 , 1.8068937e+002 , 2.0314588e+002 , 2.2627310e+002 , 2.5083943e+002 , 2.7640632e+002 , 3.0292507e+002 , 3.3070858e+002 , 3.5956494e+002 , 9.7337939e+001 , 1.1585490e+002 , 1.3525123e+002 , 1.5546662e+002 , 1.7656798e+002 , 1.9872551e+002 , 2.2179024e+002 , 2.4589875e+002 , 2.7132975e+002 , 2.9761543e+002 , 3.2493450e+002 , 3.5359463e+002
		, 5.6274468e+002 , 5.6278940e+002 , 5.6258316e+002 , 5.6247492e+002 , 5.6171087e+002 , 5.6126753e+002 , 5.6000053e+002 , 5.5888345e+002 , 5.5714394e+002 , 5.5542912e+002 , 5.5271444e+002 , 5.5009813e+002 , 5.3307860e+002 , 5.3203895e+002 , 5.3093362e+002 , 5.2977408e+002 , 5.2836712e+002 , 5.2654340e+002 , 5.2442362e+002 , 5.2195135e+002 , 5.1941360e+002 , 5.1595980e+002 , 5.1259323e+002 , 5.0816490e+002 , 5.0388939e+002 , 5.0218583e+002 , 5.0016951e+002 , 4.9789412e+002 , 4.9563164e+002 , 4.9286151e+002 , 4.8967232e+002 , 4.8637414e+002 , 4.8236561e+002 , 4.7841584e+002 , 4.7327514e+002 , 4.6841817e+002 , 4.7523854e+002 , 4.7257461e+002 , 4.6979064e+002 , 4.6661318e+002 , 4.6355869e+002 , 4.5963699e+002 , 4.5559539e+002 , 4.5111555e+002 , 4.4647094e+002 , 4.4079839e+002 , 4.3525164e+002 , 4.2872197e+002 , 4.4726158e+002 , 4.4369213e+002 , 4.4031444e+002 , 4.3618355e+002 , 4.3220394e+002 , 4.2763952e+002 , 4.2237676e+002 , 4.1727980e+002 , 4.1132882e+002 , 4.0526322e+002 , 3.9825192e+002 , 3.9124591e+002 , 4.1977315e+002 , 4.1561524e+002 , 4.1146989e+002 , 4.0651481e+002 , 4.0183072e+002 , 3.9634148e+002 , 3.9041272e+002 , 3.8405319e+002 , 3.7766528e+002 , 3.7041126e+002 , 3.6307176e+002 , 3.5454339e+002 , 3.9306560e+002 , 3.8831045e+002 , 3.8331730e+002 , 3.7764507e+002 , 3.7228107e+002 , 3.6613706e+002 , 3.5927506e+002 , 3.5251755e+002 , 3.4490673e+002 , 3.3733777e+002 , 3.2869538e+002 , 3.2014615e+002 , 3.6714088e+002 , 3.6173460e+002 , 3.5619137e+002 , 3.4969751e+002 , 3.4375728e+002 , 3.3671647e+002 , 3.2949343e+002 , 3.2171719e+002 , 3.1381525e+002 , 3.0514899e+002 , 2.9638096e+002 , 2.8664905e+002 , 3.4188272e+002 , 3.3593221e+002 , 3.2965237e+002 , 3.2292687e+002 , 3.1606294e+002 , 3.0867094e+002 , 3.0060619e+002 , 2.9260154e+002 , 2.8367903e+002 , 2.7480709e+002 , 2.6516866e+002 , 2.5536591e+002 , 3.1763179e+002 , 3.1106499e+002 , 3.0441642e+002 , 2.9697154e+002 , 2.8972261e+002 , 2.8162968e+002 , 2.7316263e+002 , 2.6436678e+002 , 2.5536354e+002 , 2.4560213e+002 , 2.3578189e+002 , 2.2506760e+002 , 2.9394408e+002 , 2.8691041e+002 , 2.7963024e+002 , 2.7188567e+002 , 2.6397193e+002 , 2.5563292e+002 , 2.4663406e+002 , 2.3758065e+002 , 2.2778068e+002 , 2.1799785e+002 , 2.0749415e+002 , 1.9681284e+002 , 2.7132863e+002 , 2.6380227e+002 , 2.5620170e+002 , 2.4789132e+002 , 2.3973951e+002 , 2.3079907e+002 , 2.2155671e+002 , 2.1199609e+002 , 2.0199490e+002 , 1.9158604e+002 , 1.8089708e+002 , 1.6961710e+002 , 2.4925346e+002 , 2.4151114e+002 , 2.3337484e+002 , 2.2482751e+002 , 2.1619170e+002 , 2.0733188e+002 , 1.9731238e+002 , 1.8746781e+002 , 1.7721438e+002 , 1.6673178e+002 , 1.5532634e+002 , 1.4436555e+002
		, 8.6364943e+001 , 1.0699293e+002 , 1.2795406e+002 , 1.5113879e+002 , 1.7471912e+002 , 2.0132630e+002 , 2.2797095e+002 , 2.5815092e+002 , 2.8889280e+002 , 3.2255062e+002 , 3.5758338e+002 , 3.9547546e+002 , 8.8679462e+001 , 1.0820995e+002 , 1.2986443e+002 , 1.5195775e+002 , 1.7629493e+002 , 2.0143792e+002 , 2.2882781e+002 , 2.5761991e+002 , 2.8870335e+002 , 3.2115429e+002 , 3.5609718e+002 , 3.9263925e+002 , 9.0189014e+001 , 1.1036868e+002 , 1.3105092e+002 , 1.5361762e+002 , 1.7696147e+002 , 2.0246468e+002 , 2.2880046e+002 , 2.5774691e+002 , 2.8780605e+002 , 3.1995950e+002 , 3.5400584e+002 , 3.9019345e+002 , 9.2513543e+001 , 1.1184849e+002 , 1.3288209e+002 , 1.5464220e+002 , 1.7830454e+002 , 2.0285481e+002 , 2.2944659e+002 , 2.5752697e+002 , 2.8730329e+002 , 3.1861873e+002 , 3.5218567e+002 , 3.8745767e+002 , 9.4387205e+001 , 1.1405695e+002 , 1.3444143e+002 , 1.5637095e+002 , 1.7931974e+002 , 2.0382976e+002 , 2.2961320e+002 , 2.5744836e+002 , 2.8642409e+002 , 3.1747541e+002 , 3.4995784e+002 , 3.8451942e+002 , 9.6753676e+001 , 1.1585371e+002 , 1.3628817e+002 , 1.5764337e+002 , 1.8043992e+002 , 2.0450718e+002 , 2.3003042e+002 , 2.5728875e+002 , 2.8577169e+002 , 3.1591420e+002 , 3.4792021e+002 , 3.8163239e+002 , 9.8867665e+001 , 1.1810228e+002 , 1.3796957e+002 , 1.5932830e+002 , 1.8165656e+002 , 2.0544496e+002 , 2.3034961e+002 , 2.5719199e+002 , 2.8509511e+002 , 3.1459107e+002 , 3.4569924e+002 , 3.7854635e+002 , 1.0132205e+002 , 1.2004024e+002 , 1.3990812e+002 , 1.6075478e+002 , 1.8285281e+002 , 2.0621131e+002 , 2.3070235e+002 , 2.5688767e+002 , 2.8429557e+002 , 3.1320049e+002 , 3.4364028e+002 , 3.7553512e+002 , 1.0368818e+002 , 1.2230246e+002 , 1.4182394e+002 , 1.6237295e+002 , 1.8403375e+002 , 2.0715459e+002 , 2.3121687e+002 , 2.5674272e+002 , 2.8364588e+002 , 3.1179056e+002 , 3.4145919e+002 , 3.7242224e+002 , 1.0610786e+002 , 1.2446142e+002 , 1.4377530e+002 , 1.6404937e+002 , 1.8545248e+002 , 2.0784548e+002 , 2.3158549e+002 , 2.5651241e+002 , 2.8282759e+002 , 3.1022915e+002 , 3.3934544e+002 , 3.6950525e+002 , 1.0856287e+002 , 1.2666729e+002 , 1.4568805e+002 , 1.6570981e+002 , 1.8663836e+002 , 2.0868753e+002 , 2.3182164e+002 , 2.5635638e+002 , 2.8202227e+002 , 3.0885981e+002 , 3.3698365e+002 , 3.6639345e+002 , 1.1089749e+002 , 1.2879301e+002 , 1.4762028e+002 , 1.6734756e+002 , 1.8786726e+002 , 2.0964265e+002 , 2.3214464e+002 , 2.5622021e+002 , 2.8142586e+002 , 3.0750640e+002 , 3.3479004e+002 , 3.6348212e+002 , 1.1340985e+002 , 1.3105515e+002 , 1.4957061e+002 , 1.6882159e+002 , 1.8921064e+002 , 2.1036915e+002 , 2.3255432e+002 , 2.5594626e+002 , 2.8050921e+002 , 3.0590879e+002 , 3.3262454e+002 , 3.6048305e+002
		, 4.4864019e+002 , 4.4745211e+002 , 4.4611043e+002 , 4.4461347e+002 , 4.4305107e+002 , 4.4138080e+002 , 4.3958147e+002 , 4.3747957e+002 , 4.3505672e+002 , 4.3267145e+002 , 4.2960235e+002 , 4.2677182e+002 , 4.3178991e+002 , 4.3008435e+002 , 4.2824099e+002 , 4.2627275e+002 , 4.2410991e+002 , 4.2165679e+002 , 4.1932752e+002 , 4.1643791e+002 , 4.1353975e+002 , 4.1004127e+002 , 4.0663565e+002 , 4.0252618e+002 , 4.1457362e+002 , 4.1240334e+002 , 4.0988898e+002 , 4.0742840e+002 , 4.0456411e+002 , 4.0165836e+002 , 3.9848351e+002 , 3.9491090e+002 , 3.9109101e+002 , 3.8707383e+002 , 3.8245053e+002 , 3.7777618e+002 , 3.9682675e+002 , 3.9412681e+002 , 3.9113919e+002 , 3.8786116e+002 , 3.8452771e+002 , 3.8077716e+002 , 3.7680314e+002 , 3.7245184e+002 , 3.6787398e+002 , 3.6275646e+002 , 3.5748552e+002 , 3.5143686e+002 , 3.7872664e+002 , 3.7540335e+002 , 3.7177441e+002 , 3.6794604e+002 , 3.6381828e+002 , 3.5947218e+002 , 3.5466395e+002 , 3.4945050e+002 , 3.4385314e+002 , 3.3805875e+002 , 3.3143852e+002 , 3.2453295e+002 , 3.6015667e+002 , 3.5615430e+002 , 3.5206661e+002 , 3.4753785e+002 , 3.4265509e+002 , 3.3752877e+002 , 3.3191220e+002 , 3.2565832e+002 , 3.1928158e+002 , 3.1217424e+002 , 3.0469953e+002 , 2.9626543e+002 , 3.4139543e+002 , 3.3675020e+002 , 3.3166366e+002 , 3.2659832e+002 , 3.2102526e+002 , 3.1506235e+002 , 3.0850922e+002 , 3.0148164e+002 , 2.9384448e+002 , 2.8573979e+002 , 2.7691704e+002 , 2.6757438e+002 , 3.2232918e+002 , 3.1696930e+002 , 3.1137275e+002 , 3.0511857e+002 , 2.9906427e+002 , 2.9203319e+002 , 2.8463530e+002 , 2.7658579e+002 , 2.6796866e+002 , 2.5857101e+002 , 2.4862520e+002 , 2.3763727e+002 , 3.0276568e+002 , 2.9676310e+002 , 2.9045436e+002 , 2.8368666e+002 , 2.7628448e+002 , 2.6857927e+002 , 2.6033221e+002 , 2.5118243e+002 , 2.4148334e+002 , 2.3107241e+002 , 2.1951120e+002 , 2.0737461e+002 , 2.8314585e+002 , 2.7647022e+002 , 2.6934098e+002 , 2.6171962e+002 , 2.5365914e+002 , 2.4491666e+002 , 2.3548954e+002 , 2.2546750e+002 , 2.1460190e+002 , 2.0287631e+002 , 1.9017719e+002 , 1.7625084e+002 , 2.6315017e+002 , 2.5566394e+002 , 2.4777635e+002 , 2.3947428e+002 , 2.3050775e+002 , 2.2104550e+002 , 2.1048449e+002 , 1.9917021e+002 , 1.8725644e+002 , 1.7434061e+002 , 1.6025288e+002 , 1.4499802e+002 , 2.4306248e+002 , 2.3484554e+002 , 2.2634527e+002 , 2.1711014e+002 , 2.0740789e+002 , 1.9663656e+002 , 1.8551271e+002 , 1.7299494e+002 , 1.5964641e+002 , 1.4560752e+002 , 1.3028744e+002 , 1.1339147e+002 , 2.2263554e+002 , 2.1395581e+002 , 2.0450582e+002 , 1.9466914e+002 , 1.8377333e+002 , 1.7266199e+002 , 1.5994264e+002 , 1.4657041e+002 , 1.3216208e+002 , 1.1672312e+002 , 9.9751967e+001 , 8.1769264e+001
		, 2.3247275e+002 , 2.4645544e+002 , 2.6143638e+002 , 2.7701905e+002 , 2.9371354e+002 , 3.1169083e+002 , 3.3039493e+002 , 3.5079438e+002 , 3.7218548e+002 , 3.9539896e+002 , 4.1971377e+002 , 4.4644737e+002 , 2.1762216e+002 , 2.3155505e+002 , 2.4606333e+002 , 2.6160861e+002 , 2.7814014e+002 , 2.9554066e+002 , 3.1433325e+002 , 3.3426441e+002 , 3.5583178e+002 , 3.7841861e+002 , 4.0320328e+002 , 4.2919025e+002 , 2.0300953e+002 , 2.1631240e+002 , 2.3065967e+002 , 2.4572861e+002 , 2.6199535e+002 , 2.7931915e+002 , 2.9756147e+002 , 3.1754366e+002 , 3.3864481e+002 , 3.6128738e+002 , 3.8549250e+002 , 4.1192055e+002 , 1.8754716e+002 , 2.0089134e+002 , 2.1471223e+002 , 2.2959595e+002 , 2.4539942e+002 , 2.6234581e+002 , 2.8044158e+002 , 2.9990398e+002 , 3.2075860e+002 , 3.4312582e+002 , 3.6734664e+002 , 3.9316400e+002 , 1.7228546e+002 , 1.8487805e+002 , 1.9871594e+002 , 2.1305546e+002 , 2.2854058e+002 , 2.4503667e+002 , 2.6273422e+002 , 2.8188169e+002 , 3.0236090e+002 , 3.2454780e+002 , 3.4820920e+002 , 3.7410713e+002 , 1.5654499e+002 , 1.6905130e+002 , 1.8217809e+002 , 1.9629702e+002 , 2.1120792e+002 , 2.2740914e+002 , 2.4461624e+002 , 2.6329446e+002 , 2.8338048e+002 , 3.0507416e+002 , 3.2856086e+002 , 3.5377785e+002 , 1.4074843e+002 , 1.5253199e+002 , 1.6554233e+002 , 1.7894593e+002 , 1.9369733e+002 , 2.0928261e+002 , 2.2607186e+002 , 2.4432755e+002 , 2.6388554e+002 , 2.8507442e+002 , 3.0796218e+002 , 3.3290874e+002 , 1.2460892e+002 , 1.3628963e+002 , 1.4849609e+002 , 1.6171702e+002 , 1.7558087e+002 , 1.9105471e+002 , 2.0698388e+002 , 2.2485440e+002 , 2.4382637e+002 , 2.6446736e+002 , 2.8682260e+002 , 3.1125291e+002 , 1.0868092e+002 , 1.1957569e+002 , 1.3160868e+002 , 1.4402566e+002 , 1.5767716e+002 , 1.7223554e+002 , 1.8783976e+002 , 2.0491493e+002 , 2.2339469e+002 , 2.4339853e+002 , 2.6520395e+002 , 2.8891071e+002 , 9.2360932e+001 , 1.0317104e+002 , 1.1424382e+002 , 1.2652357e+002 , 1.3930413e+002 , 1.5345740e+002 , 1.6829243e+002 , 1.8499172e+002 , 2.0262861e+002 , 2.2201949e+002 , 2.4295514e+002 , 2.6596819e+002 , 7.6279317e+001 , 8.6101198e+001 , 9.7142250e+001 , 1.0841824e+002 , 1.2104929e+002 , 1.3428821e+002 , 1.4865520e+002 , 1.6442427e+002 , 1.8157006e+002 , 2.0003827e+002 , 2.2042330e+002 , 2.4261004e+002 , 5.9774752e+001 , 6.9573583e+001 , 7.9536555e+001 , 9.0774590e+001 , 1.0239907e+002 , 1.1529150e+002 , 1.2877533e+002 , 1.4403684e+002 , 1.6024692e+002 , 1.7809538e+002 , 1.9744414e+002 , 2.1885849e+002 , 4.3647440e+001 , 5.2470320e+001 , 6.2490765e+001 , 7.2531538e+001 , 8.4023424e+001 , 9.5990747e+001 , 1.0914727e+002 , 1.2321477e+002 , 1.3898235e+002 , 1.5575133e+002 , 1.7440801e+002 , 1.9469867e+002
};
//image coordinates, 156 points per image, 2 coordinate x- and y-direction, 5images
//order of data is columnwise, starting with the last column, where each line contains x or y coords for the whole pic
DynMatrix<icl64f> x(156,2*5,br2);

///simple example how to use IntrinsicCalibrator
int main(int n, char **args){
	//first example:
	IntrinsicCalibrator *camc = new IntrinsicCalibrator(13,12,5);
	DynMatrix<icl64f> dst;
	//undo scaling from given data (not necessary)
	X.mult(1.0/30.0,dst);
	//main calibration call
	ImageUndistortion iu =
			camc->calibrate(x,dst);
	DynMatrix<icl64f> res(10,1);
	for(unsigned int i=0;i<(iu.params).size();++i)
		res[i] = iu.params[i];
	SHOW(res)
	camc->saveIntrinsics("bsp.xml");
	delete camc;

	//second example:
	IntrinsicCalibrator::CalibrationData cb;
	cb.imageSize = Size(640,480);
	DynMatrix<icl64f> x_coords(12,13);
	DynMatrix<icl64f> y_coords(12,13);
	for(int k=0;k<5;++k){
		cb.data.push_back(IntrinsicCalibrator::DetectedGrid(13,12));
		//copy data the right way (rowwise layout), worldcoordinates are generated
		//automatically in the right layout
		for(unsigned int i=0;i<x.cols();++i){
			//copy x coordinates for one pic
			x_coords[i] = x(i,2*k);
			//copy y coordinates for one pic
			y_coords[i] = x(i,2*k+1);
		}
		//relayout from columnwise starting at last column
		//to rowwise starting in first column
		for(int i=0;i<13;++i){
			for(int j=0;j<12;++j){
				cb.data[k](i,j)[0] = x_coords(j,12-i);
				cb.data[k](i,j)[1] = y_coords(j,12-i);
			}
		}
	}
	//main calibration call
	iu =IntrinsicCalibrator::optimize(cb);
	for(unsigned int i=0;i<(iu.params).size();++i)
		res[i] = iu.params[i];
	SHOW(res)
	return 0;
}