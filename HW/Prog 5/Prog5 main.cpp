#include "YOUR_FILE"
int main()
{
  int x[] = {0,0,0,0,0,0,1,1,
             0,0,0,0,0,0,0,0,
             0,0,0,1,1,1,0,0,
             0,0,1,0,1,1,0,0,
             0,0,1,1,0,1,0,0,
             0,0,1,1,1,0,0,0,
             1,0,0,0,0,0,0,1,
             1,0,0,0,0,0,1,0};
  MyGraph G(8, x);
  G.CC();
  system("pause");
  return 0;
}
