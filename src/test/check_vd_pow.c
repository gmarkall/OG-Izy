#ifdef HAVE_CONFIG
#include "libizy/config.h"
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "libizy/izy.h"
#include "izymakecheck.h"

// pow has large range
#ifdef IZY_DBL_EPSILON
#undef IZY_DBL_EPSILON
#define IZY_DBL_EPSILON  (100 * DBL_EPSILON)
#endif

int main()
{
#include "vd_pow_c.inc"
  int i;
  double * results_data = NULL;
  results_data = (double * ) malloc(n_expected*sizeof(double));
  if(!results_data)
    {
      return _MALLOCERROR;
    }

  const int offsetin0 = 0;
  const int offsetin1 = 0;
  const int offsetout0 = 0;
  const int count = n_in;
  memset(results_data,0x0,count*sizeof(double));

  /* make izy call */
  vd_pow(&count,in_data0,&offsetin0,in_data1,&offsetin1,results_data,&offsetout0);

  /* check */
  for(i=0; i<n_expected; i++)
    {
      if(fabs(results_data[i]-expected_data[i])>=IZY_DBL_EPSILON)
        {
          return _INCORRECTRESULT;
        }

    }

  /* stage offset call */
  const int offsetin_used0 = (int)0.2*count;
  const int offsetin_used1 = (int)0.2*count;
  const int offsetout_used0 = (int)0.4*count;
  const int count_used = count - offsetout_used0;

  /* make izy call */
  vd_pow(&count_used,in_data0,&offsetin_used0,in_data1,&offsetin_used1,results_data,&offsetout_used0);

  /* check */
  for(i=offsetout_used0; i < offsetout_used0+count_used; i++)
    {
      if(fabs(results_data[i]-expected_data[i])>=IZY_DBL_EPSILON)
        {
          return _INCORRECTRESULT;
        }

    }

  /* stage calls to saturation */
  double IVAL0 =  0.e0;
  double IVAL1 =  0.e0;
  double RVAL =  0.e0;
  const int one = 1;


  /* test NaN arg0 */
  IVAL0 = NAN;
  IVAL1 =  0.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(RVAL==1.e0))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = NAN;
  IVAL1 = INFINITY;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!isnan(RVAL))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = NAN;
  IVAL1 = -INFINITY;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!isnan(RVAL))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = NAN;
  IVAL1 = NAN;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!isnan(RVAL))
    {
      return _INCORRECTRESULT;
    }

  /* test +INF */
  IVAL0 = INFINITY;
  IVAL1 =  0.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(RVAL==1.e0))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = INFINITY;
  IVAL1 =  2.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(isinf(RVAL)&&!signbit(RVAL)))
    {
      return _INCORRECTRESULT;
    }


  IVAL0 = INFINITY;
  IVAL1 =  -12.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(RVAL==0.e0)&&!signbit(RVAL))
    {
      return _INCORRECTRESULT;
    }


  IVAL0 = INFINITY;
  IVAL1 = INFINITY;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(isinf(RVAL)&&!signbit(RVAL)))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = INFINITY;
  IVAL1 = -INFINITY;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(RVAL==0.e0)&&!signbit(RVAL))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = INFINITY;
  IVAL1 = NAN;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!isnan(RVAL))
    {
      return _INCORRECTRESULT;
    }

  /* test -INF */
  IVAL0 = -INFINITY;
  IVAL1 =  -3.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!((RVAL==0.e0)&&signbit(RVAL)))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = -INFINITY;
  IVAL1 =  -4.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!((RVAL==0.e0)&&!signbit(RVAL)))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = -INFINITY;
  IVAL1 =  3.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(isinf(RVAL)&&signbit(RVAL)))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = -INFINITY;
  IVAL1 =  4.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(isinf(RVAL)&&!signbit(RVAL)))
    {
      return _INCORRECTRESULT;
    }


  IVAL0 = -INFINITY;
  IVAL1 =  0.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(RVAL==1.e0))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = -INFINITY;
  IVAL1 = INFINITY;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(isinf(RVAL)&&!signbit(RVAL)))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = -INFINITY;
  IVAL1 = -INFINITY;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!((RVAL==0.e0)&&!signbit(RVAL)))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = -INFINITY;
  IVAL1 = NAN;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(isnan(RVAL)))
    {
      return _INCORRECTRESULT;
    }

  /* overflow */
  IVAL0 = 1.e308;
  IVAL1 = 1.e308;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!isinf(RVAL))
    {
      return _INCORRECTRESULT;
    }

  /* more exceptions */
  IVAL0 = -2.e0;
  IVAL1 = 1.2e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(isnan(RVAL)))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = 1.e0;
  IVAL1 = NAN;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(RVAL==1.e0))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = +0.e0;
  IVAL1 = 3.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(RVAL==0.e0&&!signbit(RVAL)))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = -0.e0;
  IVAL1 = 3.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(RVAL==0.e0&&signbit(RVAL)))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = 0.e0;
  IVAL1 = 4.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(RVAL==0.e0&&!signbit(RVAL)))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = -1.e0;
  IVAL1 = INFINITY;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(RVAL==1.e0))
    {
      return _INCORRECTRESULT;
    }

  IVAL0 = -1.e0;
  IVAL1 = -INFINITY;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  if(!(RVAL==1.e0))
    {
      return _INCORRECTRESULT;
    }


  free(results_data);
  return 0;
}

