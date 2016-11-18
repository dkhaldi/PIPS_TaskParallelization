typedef struct {
	int var2;
} sub;

typedef struct {
	sub *s1;
	sub *s2;
} content;


void update1(content* a);
void update2(content* a);
void compute1(sub s, int b[100]);
void compute2(sub* s, int b[100], int c[100]);
