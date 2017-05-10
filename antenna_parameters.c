//A short antenna parameters program
//libraries
#include <stdio.h>
#include <math.h>

//constants initialization
float h       = 1.6;
float whmf    = 1.0;
float er      = 4.6;
float tanloss = 0.023;
float pi      = 3.14159;
float c       = 299792458.0;

//variables initialization
float wmf    = 0.0;
float want   = 0.0;
float hant   = 0.0;
float whant  = 0.0;
float lmf    = 0.0;
float lant   = 0.0;
float eef    = 0.0;
float eefant = 0.0;
float deltal = 0.0;
float zo     = 0.0;
float zcarac = 0.0;
float lamb   = 0.0;
float fr     = 0.0;
int k        = 0;

//main program

intmain(){

  //defined parameters input
  printf("Insert parameters:\n");
  printf("Er = ");
  scanf("%f", &er);
  printf("Loss tangent = ");
  scanf("%f", &tanloss);
  printf("Thickness = ");
  scanf("%f", &h);
  printf("Characteristic impedance = ");
  scanf("%f", &zcarac);
  printf("Operation frequency = ");
  scanf("%f", &fr);
  
  //adjust other parameters
  fr=fr*1000000000.0;
  wmf=h;

//transmission line parameters
//zo founder value loop

  while(k==0)
  {
    //calculation of zo value using w value
    zo=(120.0*pi)/(sqrt(((er+1.0)/2.0)+
    ((er-1.0)/2.0)*(1.0/(sqrt(1.0+12.0*(1.0/(wmf/h)))))))/
    ((wmf/h)+1.393+0.667*log((wmf/h)+1.444));
    if((zo-zcarac)<0.001) //stop condition
      k=1;
    else //continuity condition
    {
      wmf=wmf+0.0001;
      k=0;
    }
  }

  //ef
  eef=((er+1.0)/2.0)+((er-1.0)/2.0)*(1.0/(sqrt(1.0+12.0*(1.0/(wmf/h)))));

  //zo
  zo=((120.0*pi)/(sqrt(eef)))/((wmf/h)+1.393+0.667*log((wmf/h)+1.444));

  whmf = wmf/h;
  
  printf("\n");
  printf("Microstrip parameter (mf): \n\n");
  printf("Eef     = %.4f\n", eef);
  printf("Z0      = %.4f [ohms]\n", zo);
  printf("Wmf     = %.4f mm\n", wmf);
  printf("hmf     = %.4f mm\n", h);
  printf("Wmf/hmf = %.4f\n", whmf);

  //unmatched antenna parameters

  //guided lambda
  lamb = c/(fr*sqrt(eef));

  printf("\n");
  printf("Antenna parameters:\n");
  printf("Lambda = %.4f mm\n", lamb);

  //microstrip lenght
  hant=lamb/2.0;

  printf("hantena = %.4f mm\n", hant*1000.0);

  //antenna dimensions
  //antenna width
  want = (c/(2.0*fr))*sqrt(2.0/(er+1.0));

  printf("Wantena= %.4f mm\n", want*1000.0);

  //antenna eef
  eefant=((er+1.0)/2.0)+((er-1.0)/2.0)*(1.0/(sqrt(1.0+12.0*(1.0/(want/hant)))));

  printf("Eefantena = %.4f\n", eefant);

  //antenna lenght
  whant = want/hant;

  printf("Want/hant = %.4f\n", whant);

  h=h/1000;
  deltal=0.412*h*(((eefant+0.3)*((want/h)+0.264))/((eefant-0.258)*((want/h)+0.8)));
  lant=(c/(2*fr*sqrt(eefant)))-2.0*deltal;
  
  printf("Lantena=%.4fmm\n",lant*1000);
  printf("DeltaL=%.4f\n",deltal);
  
  return 0;
}
