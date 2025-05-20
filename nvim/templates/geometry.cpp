struct Point {
  int x,y;
  Point(int x, int y) : x(x), y(y) {}
};


bool intersects(Point A, Point B, Point C, Point D) {
  // for a line ax + by + c = 0 divides the plane into two regions.
  // Plug in (x,y). Positive results are on one side, and negative results on the other
  // Check intersection by checking that C and D are on opposite sides of AB
  // and that A and B are on opposite sides of CD
  // y*(x2-x1) - x*(y2-y1) -y1x2+y2x1 = 0
  int s = C.y * (B.x - A.x) - C.x * (B.y - A.y) - A.y*B.x + B.y*A.x;
  int t = D.y * (B.x - A.x) - D.x * (B.y - A.y) - A.y*B.x + B.y*A.x;
  // BEWARE OVERFLOW IF DOING s*t
  if ( ((s > 0) and (t > 0)) or ((s < 0) and (t < 0))) return false;

  s = A.y * (D.x - C.x) - A.x * (D.y - C.y) - C.y*D.x + D.y*C.x;
  t = B.y * (D.x - C.x) - B.x * (D.y - C.y) - C.y*D.x + D.y*C.x;
  if ( ((s > 0) and (t > 0)) or ((s < 0) and (t < 0))) return false;

  return true;
}
