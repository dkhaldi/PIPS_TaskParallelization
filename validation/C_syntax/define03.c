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
  
  i=0;
  while(i<=max(x,y)) {
    r=0;
    i++;
  }
  
  if (n<min(0,1))
    r=0;
  
  i=0; 
  while(i<=max(0,1)) {
    r=0;
    i++;
  }

  return r;
}
