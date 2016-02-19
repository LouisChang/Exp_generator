/* -------------------------------------------------------------------------  
 * This program reads a (text) data file and computes the mean, minimum, 
 * maximum, and standard deviation.   The one-pass algorithm used is due to 
 * B.P. Welford (Technometrics, vol. 4, no 3, August 1962.) 
 *
 * NOTE: the text data file is assumed to be in a one-value-per-line format
 * with NO blank lines in the file.   The data can be either fixed point 
 * (integer valued), or floating point (real valued). 
 *
 * To use the program, compile it to disk to produce uvs.  Then at a command 
 * line prompt, uvs can be used in three ways. 
 *
 * (1) To have uvs read a disk data file, say uvs.dat (in the format above),
 * at a command line prompt use '<' redirection as: 
 *
 *     uvs < uvs.dat
 *
 * (2) To have uvs filter the numerical output of a program, say test, at a
 * command line prompt use '|' pipe as: 
 *
 *     test | uvs
 *
 * (3) To use uvs with keyboard input, at a command line prompt enter:
 *
 *      uvs
 *
 * Then enter the data -- one value per line -- being sure to remember to
 * signify an end-of-file.  In Unix/Linux, signify an end-of-file by
 * entering ^d (Ctrl-d) as the last line of input.
 * 
 * Name              : uvs.c  (Univariate Statistics)
 * Authors           : Steve Park & Dave Geyer 
 * Language          : ANSI C 
 * Latest Revision   : 9-28-98
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>                             
#include <math.h>                                

#define FILENAME "/Users/sidichang/Documents/Data Analysis/Exp_generator/uvs.dat"
double GetData(FILE *fp)
{
    double s;
    fscanf(fp, "%lf\n", &s);
    return (s);
}

  int main(void)
{
    FILE *fp;
    FILE *fp_w;
  long    index;
  double  data;
  double  sum = 0.0;
  double  mean;
  double  stdev;
  double  min;
  double  max;
  double  diff;

    fp=fopen(FILENAME,"r");
  //scanf("%lf\n", &data);
    //data = GetData(fp);
  if (!feof(fp)) {
    index  = 1;
    mean   = data;
    min    = data;
    max    = data;
  }
  else 
    index = 0;
   
    fp_w=fopen("Walford_out","w");
  while (!feof(fp)) {   //!feof(stdin)
    //scanf("%lf\n", &data);
      data = GetData(fp);
     // printf("%lf",data);
      fprintf(fp_w,"%ld %lf %lf\n", index, sum, mean);
    index++;
    diff  = data - mean;
    sum  += diff * diff * (index - 1.0) / index;
    mean += diff / index;
    
      
    if (data > max)
      max = data;
    else if (data < min)
      min = data;
  }

  if (index > 0) {
    stdev = sqrt(sum / index);
    printf("\nfor a sample of size %ld\n", index);
    printf("mean ................. = %7.3f\n", mean);
    printf("standard deviation ... = %7.3f\n", stdev);
    printf("minimum .............. = %7.3f\n", min);
    printf("maximum .............. = %7.3f\n", max);
  }
    fclose(fp_w);
    fp_w=NULL;
    fclose(fp);
    fp=NULL;
  return (0);
}
