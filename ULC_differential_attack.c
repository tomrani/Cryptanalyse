/******************************************************************************

                Differential Attack on ULC Block Ciphers for IoT
*******************************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
const int N=64;
const int NR=15;

int distribution[16][16]={
{16 ,     0  ,     0   ,    0  ,     0 ,     0    ,   0  ,     0    ,   0    ,   0     ,  0    ,   0    ,   0   ,    0  ,     0  ,     0 },
{0   ,    0    ,   0   ,    2   ,    0     ,  0     ,  4    ,   2    ,   0    ,   0     ,  0   ,    2     ,  0    ,   0   ,    4   ,    2 },
{0    ,   0  ,     0  ,     0      , 0     ,  0      , 2    ,   2     ,  2    ,   0     ,  2    ,   0   ,    2     ,  4   ,    0    ,   2 },
{0     ,  0    ,   0   ,    2   ,    0     ,  0      , 2     ,  0      , 2    ,   4      , 2    ,   2    ,   2      , 0    ,   0     , 0 },
{0     ,  0   ,    0  ,     4    ,   0     ,  0   ,    0    ,   4     ,  0    ,   0     ,  0  ,     4    ,   0    ,   0   ,    0     ,  4 },
{0      , 2   ,    0 ,      0   ,    4     ,  2   ,    0    ,   0     ,  4    ,   2    ,   0   ,    0      , 0    ,   2   ,    0     ,  0 },
{0       ,2   ,    4  ,     0   ,    2     ,  0  ,     0     ,  0     ,  0    ,   0    ,   0   ,    2    ,   2    ,   2    ,   0     ,  2 },
{0      , 0   ,    4 ,      0   ,    2    ,   2  ,     0     ,  0     ,  0    ,   2    ,   0    ,   2    ,   2    ,   0    ,   0      , 2 },
{0      , 2    ,   0  ,     2    ,   0     ,  2  ,     0     ,  2     ,  0    ,   2    ,   0    ,   2    ,   0    ,   2     ,  0     ,  2 },
{0  ,     2    ,   0  ,     0   ,    0    ,   2  ,     4    ,  0     ,  0    ,   2    ,   0    ,   0    ,   0     ,  2     ,  4     ,  0 },
{0  ,     0    ,   0  ,     0   ,    0     ,  4   ,    2     ,  2     ,  2     ,  0    ,   2    ,   0     ,  2     ,  0     ,  0     ,  2 },
{0  ,     4    ,   0    ,   2   ,    0   ,    0   ,    2    ,   0     ,  2    ,   0     ,  2    ,   2     ,  2    ,   0     ,  0     ,  0 },
{0  ,     0     ,  0    ,   0     ,  4   ,    0   ,    0   ,    0  ,     4     ,  0    ,   4    ,   0     ,  0    ,   0     ,  4     ,  0 },
{0    ,   2    ,   0    ,   0   ,    0    ,   2  ,     0 ,      0    ,   0    ,   2   ,    4     ,  0     ,  0   ,    2      , 4     ,  0 },
{0  ,     0    ,   4   ,    2   ,    2  ,     2  ,     0      , 2   ,    0    ,   2  ,     0    ,   0      , 2    ,   0      , 0      , 0 },
{0  ,     2     ,  4  ,     2   ,    2  ,     0  ,     0 ,     2  ,     0  ,     0 ,     0 ,      0   ,    2  ,     2   ,    0   ,    0 }
};


const int permut[64]={63, 59 ,55, 51 ,47 ,43,39 ,35 ,31 ,27 ,23, 19 ,15, 11 ,7 ,3,
62 ,58 ,54 ,50, 46 ,42 ,38 ,34 ,30 ,26 ,22 ,18 ,14 ,10 ,6, 2,
61 ,57 ,53 ,49, 45 ,41, 37 ,33, 29, 25, 21 ,17, 13 ,9 ,5 ,1,
60 ,56, 52 ,48 ,44 ,40, 36 ,32, 28 ,24 ,20 ,16 ,12 ,8 ,4, 0
};

int valmax(int tab[16][16], int j)
{
   int  max = 0; 
   int val, i;
   for (i = 0 ; i < 16 ; i++)
   {
      val = tab[j][i];
      if (abs(max) < abs(val))
         max = val;
   }
   return max;
}

int indicevalmax(int tab[16][16], int max, int j)
{
    int i=0;
    int indice;
    while(i<16 && (tab[j][i]!=abs(max))){
        i++;
    }
    if(i<16){
        indice =i;
    }
    else{
        i=0;
        while(i<16 && (tab[j][i]!=max)){
            i++;
        }
        indice =i;
    }
   return indice;
}

int extractInt(int orig16BitWord, unsigned from, unsigned to) 
{
  unsigned mask = ( (1<<(to-from+1))-1) << from;
  return (orig16BitWord & mask) >> from;
}
     
int main(){
	
    int tab[100000];
    
    int input[64] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 1,1,1,0};
    int input2[N];
    int cpt=0;
    
    int k,iter;
    for(iter=0 ; iter<NR; iter++){
        printf("ronde%d\n",iter);
        	int i=0;
        while(i<N){
         
            int etat=0;
            int j;
            for( j=0;j<4;j++){
                if(input[i+j]!=0) {etat=1;}
            }
            if(etat==1){
                etat=0;
                int val=0;
                for(j=0;j<4;j++){
                    val+=input[i+j]*pow(2,3-j);
                }

                int max=valmax(distribution,val);
                
                int indice=indicevalmax(distribution,max,val);
                printf("(%d,%d)\t",val,indice);

                tab[cpt]=distribution[val][indice];
                printf("biais= %d\t",tab[cpt]);
                cpt++;
                
                printf("\n");
                for(j=0;j<4;j++){
                    input[i+j]= extractInt(indice, 3-j,3-j);

                }
            }
            
            
            i=i+4;
        }
        
        //permut
        for(k=0;k<N;k++)
        input2[k]=input[permut[k]];
        
        for(k=0;k<N;k++){
            input[k]=input2[k];
            if(k%4==0) printf("\n");
            printf("%d\t",input[k]);
        }
        printf("\n");
    }
    
    printf("number sbox active %d\n", cpt);
    return 0;
}
