#define min(x,y) ( (x<y)?(x):(y) )
#define max(x,y) ( (x>y)?(x):(y) )

int main()
{
  int n,m;
  int i;
  int x = min(n,m);
  int y = max(n,m);
  int r;
  
  if (n<=min(x,y))
    r=0;
  
  for (i=0; i<=max(x,y); i++)
    r=0;
  
  if (n<min(0,1))
    r=0;
  
  for (i=0; i<=max(0,1); i++)
    r=0;
  
  return r;
}
