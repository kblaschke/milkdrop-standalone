#include "ns-eel.h"

#include <iostream>
#include <string>

void NSEEL_HOSTSTUB_EnterMutex() {}
void NSEEL_HOSTSTUB_LeaveMutex() {}

int main()
{
    NSEEL_VMCTX ctx = NSEEL_VM_alloc();

    EEL_F* test = NSEEL_VM_regvar(ctx, "test");

    std::string code = R"(dt = min (1/fps,0.1) ;
 dec_m = 1 - 4*dt;
 dec_s = 1 - 1.25*dt;
vol =  max(0.5,bass+mid);
 vol_ = vol_*dec_m + (1-dec_m)*vol;
 excite = (vol-vol_)/vol_;
index=0;
 ratio = log(maxbpm/minbpm);
 sum_res = 0.01;
loop (num_res,
  n = index*8;
  omega      =   megabuf(n) * 6.2832/60;
  megabuf (n+1) *= 1-0.25*dt;
   EC_Steps = int (10*omega*dt)+1;
   loop (EC_Steps,
     megabuf (n+1) += (excite - sqr(omega)*megabuf(n + 2)) * dt/EC_Steps;
    megabuf (n+2) += megabuf(n+1) * dt/EC_Steps);
  beatcos  = megabuf(n+1);
  beatsin = megabuf(n+2)*omega;
   quad     = sqrt (pow(beatsin,2) + pow(beatcos,2)) ;
  megabuf (n+3) = megabuf(n+3) *dec_s +  quad* (1-dec_s);
  megabuf (n+4) = megabuf(n+3);
  stage = 2;
   loop (2,
    ind2     = int (0.5 + index + (num_res-1)/ratio*log(stage));
    if ((ind2 <= num_res),
       n2 = ind2*8;
       A2     = max(max(megabuf(n2+3),megabuf(n2-8+3)),megabuf(n2+8+3));
      megabuf(n+4) *= 1 + 2/(stage*stage)*A2/(A2+megabuf(n+3)),0);
    stage *= 2;
  );
  Hyst = 1 + min (0.25, abs (index-maxind)*0.02);
  if (megabuf(n+4) > megabuf (maxind*8+4)*Hyst, maxind = index,0);
  sum_res += megabuf (n+3);
  index += 1;
);
certain = megabuf(maxind*8+3)/(sum_res/num_res);
maxind2     = int (0.5 + maxind + (num_res-1)/ratio*log(2));
if (maxind2 > num_res, maxind2 = int (0.5 + maxind + (num_res-1)/ratio*log(0.5)),0);
sig1 = (sig1 + megabuf(maxind*8+1))/2 + excite * 0;
 is_beat1  = (sig1 > 0) && (sig1_ <= 0);
 sig2 = (sig2 + megabuf(maxind2*8+1))/2 + excite * 0;
 is_beat2  = (sig2 > 0) && (sig2_ <= 0);
 fastpace = if (maxind > maxind2, sig1 * sig1_ < 0, sig2 * sig2_ < 0);
sig1_ = sig1;
sig2_ = sig2;
tog1 = sig1 > 0;
tog2 = sig2 > 0;
sbeat1 = (sbeat1 + is_beat1)/2;
sbeat2 = (sbeat2 + is_beat2)/2;
prog1 = (prog1 + is_beat1) %512;
prog2 = (prog2 + is_beat2) %512;
prog3 = (prog3 + fastpace) %512;
maxi = min (maxind, maxind2);
trunner = trunner + dt*megabuf (maxi*8)/60*2*pi;
corr = if (push, 0.5*corr + 0.5*cos (trunner), corr*dec_s);
trunner -= corr * dt;
trunner_ = dec_s * trunner_ + (1-dec_s)*trunner/2;
q14 = trunner_;
q15 = cos(trunner_);
q16 = sin(trunner_);
q32 = aspecty;
change  = is_beat1 && (prog1%20 == 0);
schange = bnot (oldind == maxind) * (t1 > 8) || (t1>15);
t1 = if (schange, 0, t1+dt);
oldind = maxind;
if (start || schange,
       ran1 = rand (100)/100;
      ran2 = rand (100)/100;
      ran3 = rand (100)/100;
      ran4 = rand (100)/100;
      ran5 = rand (100)/100;
      ran6 = rand (100)/100;
      ran7 = rand (100)/100;
, 0);
ran1_ = ran1_ + max(min(ran1-ran1_,0.02),-0.02)*dt*12;
ran2_ = ran2_ + max(min(ran2-ran2_,0.02),-0.02)*dt*12;
ran3_ = ran3_ + max(min(ran3-ran3_,0.02),-0.02)*dt*12;
ran4_ = ran4_ + max(min(ran4-ran4_,0.02),-0.02)*dt*12;
scale = sqrt (certain/4);
q1 = prog1;
q2 = prog2;
q3 = prog3;
q4 = 1;
scheme = if (schange, int (rand(3)), scheme);
if (scheme == 2, scheme = if (schange, int (rand(3)), scheme), 0) ;
sc = if (ran1 > 0.5, q14/pi/1, q14/pi/2);
sc = 1*(sc - int (sc));
blank = sc > sc_;
sc_ = sc;
m = 0;
loop (num_shapes * (vol_> 0.7),
  n = m*recsize;
  if (scheme ==0,
    k1 = m/num_shapes-0.5;
    x0 = k1*3;
    lim = pi/8*pow (2,int (ran4*2));
    ang = max(min(ran3*3*sin(ran1_*pi+q14),lim),-lim) + ran2*3;
         arg = q14/pi/(1 + pow(2, int(ran4*3))) ;
    y0 =  (abs(arg-int(arg)-0.5)-0.25)*4;
    delta = int((x0+1)*4)/4;
    if (ran5 > 0.7, y0 *= sin(pi*ran1*delta) ,0);
        if (ran7 > 0.7, x0 -= delta/2-0.5,0);
    sa = sin (ang); ca = cos (ang);
     x = x0*ca  + y0*sa;
    y = x0*-sa + y0*ca;
    if (ran6 > 0.6, x *=  ((m%2==0)-0.5)*2+(0*q15), 0);
         gmegabuf (n+3) = 0.015 * q32 ;;
    gmegabuf (n+4) = bnot(schange);
  ,0);
   if (scheme ==1,
    k1 = m/num_shapes-0.5;
    x0 = k1*3;
    ang = (q14-q15*q16*2*(ran4_-0.5))/4;
     arg = ang/pi;
    y0 = (abs(arg-int(arg)-0.5)-0.25) ;
        y0 *= (m%2-.5)*8;
    delta = int((x0+1)*4)/4;
    if (ran5 > 0.7, y0 *= sin(pi*ran1*delta) ,0);
        sa = sin (ang);
 ca = cos (ang/2 * pow(2,int(3*ran3_)));
     sa = sign (sa) * pow (abs(sa),ran1*4);
     ca = sign (ca) * pow (abs(ca),ran1*4);
    x = x0*ca  + y0*sa;
    y = x0*-sa + y0*ca;
    if (ran6 > 0.7, y *=  ((m%2==0)-0.5)*(2+q15),0);
        gmegabuf (n+3) = 0.015 * q32;;
    gmegabuf (n+4) = bnot(schange);;
  ,0);
   if (scheme == 2,
    k1 = m/num_shapes-0.5;
    x0 = min (max( cos(k1*pi*2)*1.4,-1),1)*sc;
    y0 = min (max( sin(k1*pi*2)*1.4,-1),1)*sc;
    ind = int (k1*4-0.5 +prog3) %4;
    ang = 0;
    sa = sin (ang); ca = cos (ang*3);
     x = x0*ca  + y0*sa;
    y = x0*-sa + y0*ca;
    gmegabuf (n+3) = 0.015 * q32;
    gmegabuf (n+4) = bnot(schange) * blank;;* (fastpace);;
  ,0);
  gmegabuf (n) =   x * 0.48 + 0.5;
 gmegabuf (n+1) = y * 0.48 + 0.5;m += 1);
q10 = ran6-ran5;
monitor = q10;
start = 0;
)";

    NSEEL_CODEHANDLE codeHandle = NSEEL_code_compile(ctx, const_cast<char*>(code.c_str()));
    if (!codeHandle)
    {
        std::cout << NSEEL_code_getcodeerror(ctx);
        return 1;
    }

    NSEEL_code_execute(codeHandle);

    std::cout << "test = " << *test <<std::endl;

    NSEEL_code_free(codeHandle);
    NSEEL_VM_free(ctx);

    return 0;
}
