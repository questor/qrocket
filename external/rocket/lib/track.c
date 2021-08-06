#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "sync.h"
#include "track.h"
#include "base.h"


const double pi = 3.1415926535897932384626433832795;
const double pi2 = 3.1415926535897932384626433832795 / 2;


   double cubicin(double t) { 
      return t*t*t; 
   }
   double cubicout(double t) {
      double f = t - 1;
      return f*f*f+1;
   }
   double cubicinout(double t) {
      if(t < 0.5) 
         return 4*t*t*t;
      else {
         double f = (2*t)-2;
         return 0.5*f*f*f+1;
      }
   }
   double quartin(double t) {
      return t*t*t*t;
   }
   double quartout(double t) {
      double f = t - 1;
      return f*f*f*(1-t)+1;
   }
   double quartinout(double t) {
      if(t < 0.5) 
         return 8 * t*t*t*t;
      else {
         double f = t - 1;
         return -8*f*f*f*f+1;
      }
   }
   double quintin(double t) {
      return t*t*t*t*t;
   }
   double quintout(double t) {
      double f = t - 1;
      return f*f*f*f*f+1;
   }
   double quintinout(double t) {
      if(t < 0.5)
         return 16*t*t*t*t*t;
      else {
         double f = (2*t)-2;
         return 0.5*f*f*f*f*f+1;
      }
   }
   double sinin(double t) {
      return sin((t-1)*pi2)+1;
   }
   double sinout(double t) {
      return sin(t*pi2);
   }
   double sininout(double t) {
      return 0.5*(1-cos(t*pi));
   }
   double expin(double t) {
      return t==0.0 ? t : pow(2,10*(t-1));
   }
   double expout(double t) {
      return t==0.0 ? t : 1-pow(2,-10*t);
   }
   double expinout(double t) {
      if(t != 0.0 && t != 1.0) {
         if(t < 0.5)
            return 0.5*pow(2,(20*t)-10);
         else
            return -0.5*pow(2,(-20*t)+10)+1;
      } else
         return t;
   }
   double circin(double t) {
      return 1-sqrt(1-(t*t));
   }
   double circout(double t) {
      return sqrt((2-t)*t);
   }
   double circinout(double t) {
      if(t < 0.5) 
         return 0.5*(1-sqrt(1-4*(t*t)));
      else
         return 0.5*(sqrt(-((2*t)-3)*((2*t)-1))+1);
   }
   double elasticin(double t) {
      return sin(13*pi2*t)*pow(2,10*(t-1));
   }
   double elasticout(double t) {
      return sin(-13*pi2*(t+1))*pow(2,-10*t)+1;
   }
   double elasticinout(double t) {
      if(t < 0.5)
         return 0.5*sin(13*pi2*(2*t))*pow(2,10*((2*t)-1));
      else
         return 0.5*(sin(-13*pi2*((2*t-1)+1))*pow(2,-10*(2*t-1))+2);
   }
   double backin(double t) {
      double s = 1.70158;
      return t*t*((s+1)*t-s);
   }
   double backout(double t) {
      double s = 1.70158;
      t -= 1;
      return (t*t*((s+1)*t)+s)+1;         //correct?!?
   }
   double backinout(double t) {
      double s = 1.70158 * 1.525;
      if(t<0.5) {
         t *= 2;
         return 0.5*t*t*(t*s+t-s);
      } else {
         t = t*2-2;
         return 0.5*(2+t*t*(t*s+t+s));
      }
   }
   #define tween$bounceout(p) ( \
                   (p) < 4/11.0 ? (121 * (p) * (p))/16.0 : \
                   (p) < 8/11.0 ? (363/40.0 * (p) * (p)) - (99/10.0 * (p)) + 17/5.0 : \
                   (p) < 9/10.0 ? (4356/361.0 * (p) * (p)) - (35442/1805.0 * (p)) + 16061/1805.0 \
                              : (54/5.0 * (p) * (p)) - (513/25.0 * (p)) + 268/25.0 )
   double bouncein(double t) {
      return 1-tween$bounceout(1-t);
   }
   double bounceout(double t) {
      return tween$bounceout(t);
   }
   double bounceinout(double t) {
      if(t < 0.5)
         return 0.5*(1-tween$bounceout(1-t*2));
      else
         return 0.5*tween$bounceout((t*2-1))+0.5;
   }
   #undef tween$bounceout
   double sinesquare(double t) {
      double a = sin(t*pi2);
      return a*a;
   }
   double exponential(double t) {
      return 1/(1+exp(6-12*t));
   }
   double schubring1(double t) {
      return 2*(t+(0.5-t)*abs(0.5-t))-0.5;
   }
   double schubring2(double t) {
      double p1pass = 2*(t+(0.5-t)*abs(0.5-t))-0.5;
      double p2pass = 2*(p1pass+(0.5-p1pass)*abs(0.5-p1pass))-0.5;
      return (p1pass+p2pass)/2;
   }
   double schubring3(double t) {
      double p1pass = 2*(t+(0.5-t)*abs(0.5-t))-0.5;
      return 2*(p1pass+(0.5-p1pass)*abs(0.5-p1pass))-0.5;
   }
   double sinpi2(double t) {
      return sin(t*pi2);
   }
   double swing(double t) {
      return ((-cos(pi*t)*0.5)+0.5);
   }


static double key_linear(const struct track_key k[2], double row)
{
	double t = (row - k[0].row) / (k[1].row - k[0].row);
	return k[0].value + (k[1].value - k[0].value) * t;
}

static double key_smooth(const struct track_key k[2], double row)
{
	double t = (row - k[0].row) / (k[1].row - k[0].row);
	t = t * t * (3 - 2 * t);
	return k[0].value + (k[1].value - k[0].value) * t;
}

static double key_ramp(const struct track_key k[2], double row)
{
	double t = (row - k[0].row) / (k[1].row - k[0].row);
	t = pow(t, 2.0);
	return k[0].value + (k[1].value - k[0].value) * t;
}

static double key_generic(const struct track_key k[2], double row, enum key_type keytype)
{
	double t = (row - k[0].row) / (k[1].row - k[0].row);
	double mult;
	switch(keytype) {
	case KEY_QUADIN:
		mult = t*t;
		break;
	case KEY_QUADOUT:
		mult = -(t*(t-2));
		break;
	case KEY_QUADINOUT:
      	if(t < 0.5) 
        	mult = 2*t*t;
      	else 
        	mult = (-2*t*t)+(4*t)-1;
     	break;	
	}
	return k[0].value + (k[1].value - k[0].value) * mult;
}


double sync_get_val(const struct sync_track *t, double row)
{
	int idx, irow;

	/* If we have no keys at all, return a constant 0 */
	if (!t->num_keys)
		return 0.0f;

	irow = (int)floor(row);
	idx = key_idx_floor(t, irow);

	/* at the edges, return the first/last value */
	if (idx < 0)
		return t->keys[0].value;
	if (idx > (int)t->num_keys - 2)
		return t->keys[t->num_keys - 1].value;

	/* interpolate according to key-type */
	switch (t->keys[idx].type) {
	case KEY_STEP:
		return t->keys[idx].value;
	case KEY_LINEAR:
		return key_linear(t->keys + idx, row);
	case KEY_SMOOTH:
		return key_smooth(t->keys + idx, row);
	case KEY_RAMP:
		return key_ramp(t->keys + idx, row);
	case KEY_QUADIN:
	case KEY_QUADOUT:
	case KEY_QUADINOUT:
		return key_generic(t->keys + idx, row, t->keys[idx].type);
	default:
		assert(0);
		return 0.0f;
	}
}

int sync_find_key(const struct sync_track *t, int row)
{
	int lo = 0, hi = t->num_keys;

	/* binary search, t->keys is sorted by row */
	while (lo < hi) {
		int mi = (lo + hi) / 2;
		assert(mi != hi);

		if (t->keys[mi].row < row)
			lo = mi + 1;
		else if (t->keys[mi].row > row)
			hi = mi;
		else
			return mi; /* exact hit */
	}
	assert(lo == hi);

	/* return first key after row, negated and biased (to allow -0) */
	return -lo - 1;
}

#ifndef SYNC_PLAYER
int sync_set_key(struct sync_track *t, const struct track_key *k)
{
	int idx = sync_find_key(t, k->row);
	if (idx < 0) {
		/* no exact hit, we need to allocate a new key */
		void *tmp;
		idx = -idx - 1;
		tmp = realloc(t->keys, sizeof(struct track_key) *
		    (t->num_keys + 1));
		if (!tmp)
			return -1;
		t->num_keys++;
		t->keys = tmp;
		memmove(t->keys + idx + 1, t->keys + idx,
		    sizeof(struct track_key) * (t->num_keys - idx - 1));
	}
	t->keys[idx] = *k;
	return 0;
}

int sync_del_key(struct sync_track *t, int pos)
{
	void *tmp;
	int idx = sync_find_key(t, pos);
	assert(idx >= 0);
	memmove(t->keys + idx, t->keys + idx + 1,
	    sizeof(struct track_key) * (t->num_keys - idx - 1));
	assert(t->keys);
	tmp = realloc(t->keys, sizeof(struct track_key) *
	    (t->num_keys - 1));
	if (t->num_keys != 1 && !tmp)
		return -1;
	t->num_keys--;
	t->keys = tmp;
	return 0;
}
#endif
