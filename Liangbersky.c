#define DEFINE_LIANG_BARSKY_GLOBALS
#include "liang-barsky.h"
#undef DEFINE_LIANG_BARSKY_GLOBALS

static int is_zero(float v)
{
 return (v > -0.000001f && v < 0.000001f);
}

static inline int point_inside(struct liang_barsky_clip_window *c, int x, int y)
{
 return (x >= c->x1 && x <= c->x2 &&
  y >= c->y1 && y <= c->y2);
}

static int clipT(float num, float denom, float *tE, float *tL)
{
 float t;

 if (is_zero(denom))
  return num < 0.0;

 t = num / denom;

 if (denom > 0) {
  if (t > *tL)
   return 0;
  if (t > *tE)
   *tE = t;
 } else {
  if (t < *tE)
   return 0;
  if (t < *tL)
   *tL = t;
 }
 return 1;
}

int clip_line(struct liang_barsky_clip_window *c,
  int *x1, int *y1, int *x2,  int *y2)
{
 float dx, dy, tE, tL;

 dx = *x2 - *x1;
 dy = *y2 - *y1;

 if (is_zero(dx) && is_zero(dy) && point_inside(c, *x1, *y1))
  return 1;

 tE = 0;
 tL = 1;

 if (clipT(c->x1 - (float) *x1,  dx, &tE, &tL) &&
  clipT((float) *x1 - c->x2, -dx, &tE, &tL) &&
  clipT(c->y1 - (float) *y1,  dy, &tE, &tL) &&
  clipT((float) *y1 - c->y2, -dy, &tE, &tL)) {
  if (tL < 1) {
   *x2 = (int) ((float) *x1 + tL * dx);
   *y2 = (int) ((float) *y1 + tL * dy);
  }
  if (tE > 0) {
   *x1 += tE * dx;
   *y1 += tE * dy;
  }
  return 1;
 }
 return 0;
}

int clip_line_copy(struct liang_barsky_clip_window *c,
  int x1, int y1, int x2,  int y2,
  int *ox1, int *oy1, int *ox2, int *oy2)
{
 *ox1 = x1;
 *oy1 = y1;
 *ox2 = x2;
 *oy2 = y2;

 return clip_line(c, ox1, ox2, oy1, oy2);
}
