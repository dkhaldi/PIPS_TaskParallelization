#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // M_PI

#ifdef USE_FLOAT
typedef float data_t;
#define INPUT_FORMAT "%f%*[ \t]%f%*[ \t]%f"
#define OUTPUT_FORMAT "%f %f %f\n"
#else
typedef double data_t;
#define INPUT_FORMAT "%lf%*[ \t]%lf%*[ \t]%lf"
#define OUTPUT_FORMAT "%lf %lf %lf\n"
#endif

typedef data_t town[3];
typedef struct {
    size_t nb;
    town *data;
} towns;

towns read_towns(const char fname[])
{
    FILE * fd = fopen(fname,"r");
    size_t curr=0;
    char c;
    towns the_towns = { 1 , malloc(sizeof(town)) };
    fprintf(stderr,"begin parsing ...\n");

    while(!feof(fd))
    {
        if(the_towns.nb==curr)
        {
            the_towns.nb*=2;
            the_towns.data=realloc(the_towns.data,the_towns.nb*sizeof(town));
        }
        if(fscanf(fd,INPUT_FORMAT,&the_towns.data[curr][0],&the_towns.data[curr][1],&the_towns.data[curr][2]) !=3 )
        {
            while(!feof(fd))
            {
                c=(char)fgetc(fd);
                if(c=='\n' || c=='\r') break;
            }
        }
        else
        {
            the_towns.data[curr][0]*=M_PI/180;
            the_towns.data[curr][1]*=M_PI/180;
            ++curr;
        }
    }
    fclose(fd);
    the_towns.data=realloc(the_towns.data,curr*sizeof(town));
    the_towns.nb=curr;
    fprintf(stderr,"parsed %d towns\n",curr);
    /*
    for(curr=0;curr<the_towns.nb;curr++)
        fprintf(stderr,OUTPUT_FORMAT,the_towns.data[curr][0],the_towns.data[curr][1],the_towns.data[curr][2]);
    */
    return the_towns;
}


void run(data_t xmin, data_t ymin, data_t xmax, data_t ymax, data_t step,data_t range, size_t rangex, size_t rangey, int nb, town pt[rangex][rangey], town t[nb])
{
    size_t i,j,k;

    fprintf(stderr,"begin computation ...\n");

    for(i=0;i<rangex;i++)
        for(j=0;j<rangey;j++) {
            pt[i][j][0]=(xmin+step*i)*180/M_PI;
            pt[i][j][1]=(ymin+step*j)*180/M_PI;
            pt[i][j][2]=0.;
            for(k=0;k<nb;k++) {
                data_t tmp =
                    6368.* acos(cos(xmin+step*i)*cos( t[k][0] ) * cos((ymin+step*j)-t[k][1]) + sin(xmin+step*i)*sin(t[k][0]));
                if( tmp < range )
                    pt[i][j][2]+= t[k][2]  / (1 + tmp) ;
            }
        }
    fprintf(stderr,"end computation ...\n");
}

void display(size_t rangex, size_t rangey, town pt[rangex][rangey])
{
    size_t i,j;
    for(i=0;i<rangex;i++)
    {
        for(j=0;j<rangey;j++)
            printf(OUTPUT_FORMAT,pt[i][j][0],pt[i][j][1],pt[i][j][2]);
        printf("\n");
    }
}

int main(int argc, char * argv[])
{
    if(argc != 8) return 1;
    {
        int nb;
        towns t = read_towns(argv[1]);
        data_t xmin = atof(argv[2])*M_PI/180.,
               ymin =atof(argv[3])*M_PI/180.,
               xmax=atof(argv[4])*M_PI/180.,
               ymax=atof(argv[5])*M_PI/180.,
               step=atof(argv[6])*M_PI/180.,
               range=atof(argv[7]);
        size_t rangex=( (xmax - xmin )/step ),
               rangey=( (ymax - ymin )/step );
        town (*pt)[rangex][rangey];
        town (*pi)[t.nb];
        pi=(void*)t.data;
        nb = rangex*rangey;
        pt = malloc(sizeof(town)*nb);
        run(xmin,ymin,xmax,ymax,step,range, rangex, rangey, t.nb, *pt, *pi);
        display(rangex, rangey, *pt);
    }
    return 0;
}
