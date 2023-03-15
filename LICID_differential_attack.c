/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
const int N=64;
const int NR=14;
int distribution[16][16]={
{16, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	},
{0, 	0, 	0, 	0, 	2, 	2, 	0, 	4, 	2, 	0, 	0, 	2, 	2, 	0, 	2, 	0, 	},
{0, 	2, 	2, 	0, 	0, 	0, 	2, 	2, 	0, 	2, 	2, 	0, 	2, 	2, 	0, 	0, 	},
{0, 	2, 	0, 	0, 	0, 	0, 	0, 	2, 	0, 	4, 	2, 	0, 	0, 	2, 	2, 	2, 	},
{0, 	0, 	0, 	4, 	2, 	0, 	2, 	0, 	0, 	2, 	0, 	2, 	4, 	0, 	0, 	0, 	},
{0, 	2, 	0, 	2, 	2, 	2, 	0, 	4, 	2, 	0, 	0, 	2, 	0, 	0, 	0, 	0, 	},
{0, 	0, 	0, 	0, 	2, 	0, 	2, 	0, 	0, 	0, 	4, 	0, 	0, 	2, 	4, 	2, 	},
{0, 	2, 	2, 	2, 	0, 	0, 	2, 	0, 	0, 	0, 	4, 	2, 	0, 	2, 	0, 	0, 	},
{0, 	2, 	2, 	2, 	0, 	2, 	0, 	0, 	2, 	0, 	0, 	0, 	0, 	2, 	4, 	0, 	},
{0, 	0, 	2, 	0, 	0, 	4, 	6, 	0, 	0, 	2, 	0, 	0, 	0, 	2, 	0, 	0, 	},
{0, 	0, 	2, 	0, 	0, 	0, 	0, 	2, 	4, 	0, 	2, 	0, 	0, 	0, 	0, 	6, 	},
{0, 	2, 	0, 	2, 	2, 	0, 	0, 	2, 	0, 	0, 	2, 	2, 	0, 	0, 	0, 	4, 	},
{0, 	4, 	2, 	0, 	0, 	2, 	0, 	0, 	2, 	0, 	0, 	0, 	2, 	2, 	2, 	0, 	},
{0, 	0, 	2, 	0, 	2, 	4, 	0, 	0, 	0, 	4, 	0, 	2, 	0, 	2, 	0, 	0, 	},
{0, 	0, 	0, 	2, 	4, 	0, 	2, 	0, 	0, 	0, 	0, 	2, 	4, 	0, 	2, 	0, 	},
{0, 	0, 	2, 	2, 	0, 	0, 	0, 	0, 	4, 	2, 	0, 	2, 	2, 	0, 	0, 	2, 	},
};


const int permut[64]={2, 63,8 ,5, 62, 59, 4 ,1, 58, 55, 0, 61, 54, 51, 60, 57,
18, 15 ,24 ,21 ,14 ,11, 20, 17, 10, 7 ,16, 13, 6, 3, 12 ,9,
34 ,31, 40 ,37, 30 ,27, 36 ,33, 26, 23 ,32 ,29 ,22 ,19 ,28 ,25,
50, 47 ,56 ,53 ,46 ,43 ,52, 49 ,42 ,39, 48 ,45 ,38 ,35 ,44 ,41
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
    
    int input[64] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,1,0,1, 0,0,0,0, 0,0,0,0, 0,0,0,0};
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
                //printf("%d\t",val);
                int max=valmax(distribution,val);
                
                int indice=indicevalmax(distribution,max,val);
                printf("(%d,%d)\t",val,indice);
                //printf("output= %d\t",indice);
                tab[cpt]=distribution[val][indice];
                printf("biais= %d\t",tab[cpt]);
                cpt++;
                
                printf("\n");
                for(j=0;j<4;j++){
                    input[i+j]= extractInt(indice, 3-j,3-j);
                //printf("%d\t",input[i+j]);
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
