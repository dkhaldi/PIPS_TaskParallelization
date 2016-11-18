typedef struct {
	int var2;
} sub;

typedef struct {
	int var1;
	sub s;
} content;


void update1(content* a);
void update2(sub* s);
void compute1(content* a, int b[100]);
void compute2(sub s, int b[100], int c[100]);
