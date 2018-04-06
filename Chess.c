#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char board[8][8]={0};

typedef struct{
char board_copy[8][8];
int turn;

}arr;

arr undo_redo_array[200];
int num_of_undos=0;
int *p;/*Pointer on turns*/
int *q;/*Pointer on t */
FILE* saveload;
char array_of_whites[16]={0};
char array_of_blacks[16]={0};



void dynamic_lost_arrays()
{int i=0,j=0,z=0,y=0;
char pieces_on_board_black[20],pieces_on_board_white[20];
while(j<8)
{i=0;

    while(i<8)
    {
        if(board[i][j]=='p'||board[i][j]=='r'||board[i][j]=='n'||board[i][j]=='b'||board[i][j]=='k'||board[i][j]=='q')
        {pieces_on_board_white[z]=board[i][j];
        z++;

        }
          else if(board[i][j]=='P'||board[i][j]=='R'||board[i][j]=='N'||board[i][j]=='B'||board[i][j]=='K'||board[i][j]=='Q')
        {pieces_on_board_black[y]=board[i][j];
        y++;

        }


        i++;
    }
    j++;
}
char E;
int t=0;
int counter_pawns=0,counter_rooks=0,counter_knights=0,counter_bishops=0,queen_found=0;
E=pieces_on_board_black[t];
while(E!='\0')
{E=pieces_on_board_black[t];

    switch (E)
    {case 'P':
        counter_pawns+=1;
        break;
        case 'R':
        counter_rooks+=1;
        break;
        case 'N':
        counter_knights+=1;
        break;
        case 'B':
        counter_bishops+=1;
        break;
        case 'Q':
        queen_found=1;
        break;
    }
    t++;
    }
int x=0;
if(counter_pawns<8)
    {int v;
        for(v=0;v<(8-counter_pawns);v++)
        { array_of_blacks[x]='P';
        x++;

        }

    }
    if(counter_bishops<2)
    {int v;
        for(v=0;v<(2-counter_bishops);v++)
        {array_of_blacks[x]='B';
        x++;

        }

    }
    if(counter_rooks<2)
    {int v;
        for(v=0;v<(2-counter_rooks);v++)
        {array_of_blacks[x]='R';
        x++;

        }

    }
    if(counter_knights<2)
    {int v;
        for(v=0;v<(2-counter_knights);v++)
        {array_of_blacks[x]='N';
        x++;

        }
    }
        if(queen_found==0)
    {int v;
        for(v=0;v<(queen_found+1);v++)
        {array_of_blacks[x]='Q';
        x++;

        }

    }
    if(x==0)
    {int v;
    for(v=0;v<16;v++)
        {
            array_of_blacks[v]=0;
        }
    }

 t=0;
counter_pawns=0;counter_rooks=0;counter_knights=0;counter_bishops=0;queen_found=0;
E=pieces_on_board_white[t];
while(E!='\0')
{
E=pieces_on_board_white[t];
    switch (E)
    {case 'p':
        counter_pawns+=1;
        break;
        case 'r':
        counter_rooks+=1;
        break;
        case 'n':
        counter_knights+=1;
        break;
        case 'b':
        counter_bishops+=1;
        break;
        case 'q':
        queen_found=1;
        break;
    }
    t++;
    }
x=0;
if(counter_pawns<8)
    {int v;
        for(v=0;v<(8-counter_pawns);v++)
        {array_of_whites[x]='p';
        x++;

        }

    }
    if(counter_bishops<2)
    {int v;
        for(v=0;v<(2-counter_bishops);v++)
        {array_of_whites[x]='b';
        x++;

        }

    }
    if(counter_rooks<2)
    {int v;
        for(v=0;v<(2-counter_rooks);v++)
        {array_of_whites[x]='r';
        x++;

        }

    }
    if(counter_knights<2)
    {int v;
        for(v=0;v<(2-counter_knights);v++)
        {array_of_whites[x]='n';
        x++;

        }
        }
        if(queen_found==0)
    {int v;
        for(v=0;v<(queen_found+1);v++)
        {array_of_whites[x]='q';
        x++;

        }

    }
    if(x==0)
    {int v;
    for(v=0;v<16;v++)
        {
            array_of_whites[v]=0;
        }
    }



    }



















int CAPTURE(char a ,int b ,char c,int d)
{int player;
 int static i=0,j=0;

int success_flag=0;

player=*p%2;

if(player==1)
{array_of_blacks[i]=board[c][8-d];
    board[c][8-d]=board[a][8-b];
    board[a][8-b]=0;
    i++;
    success_flag=1;
}
if(player==0)
{
    array_of_whites[j]=board[c][8-d];
    board[c][8-d]=board[a][8-b];
    board[a][8-b]=0;
    j++;
    success_flag=1;
}



return success_flag;
}


























void REDO()
{ if(num_of_undos==0)

{printf("redos unavailable");

}
    else
    {*p=*p+1;
    num_of_undos-=1;

             memcpy(board,undo_redo_array[*p-2].board_copy,sizeof(board));



    }








}












void UNDO()
{
    if(*p<=1)
{printf("undo unavailable");

}

else if(*p==2)
{ int i,j;
    *p=*p-1;
    num_of_undos+=1;
    for(j=0;j<8;j++)
    {for(i=0;i<8;i++)
    {
        board[i][j]=0;
    }

    }
    return Turn();
}

    else
    { *p=*p-1;
    num_of_undos+=1;
        if(*p==(undo_redo_array[*p-1].turn))
            { memcpy(board,undo_redo_array[*p-2].board_copy,sizeof(board));

            }
         else
         { printf("The Turns are shifted");

         }
    }







}












void SAVE()
{


    saveload = fopen("saveload.txt","w");

  if(saveload==NULL)
  {
      printf("can`t open file");
  }

  else
    { int i;
    int j;

        for(j=0;j<8;j++)
        {for(i=0;i<8;i++)
            {   fputc(board[i][j],saveload);


            }}
    fprintf(saveload, "\n%d",*p);
    }


    fclose(saveload);



}

void LOAD()

{saveload=fopen("saveload.txt","r");

if(saveload==NULL)
{printf("Can`t open file");

}
else
{int data=0,i,j,z=0,turn;
char psuedo_board[64];
fgets(psuedo_board,64,saveload);
while(fgetc(saveload)!='\n')
    {data++;}
fscanf(saveload,"%d",&turn);
*p=turn;
    for(j=0;j<8;j++)
    {for(i=0;i<8;i++)
    {
    board[i][j]=psuedo_board[z];
     z++;
    }

    }



}
fclose(saveload);

}

void White_king_check()
{  int i=0;/*Columns*/
   int j=0;/*Rows*/
   int king_row=0;
   int king_Col=0;
   int check_is = 0;/*Is the sum of right left up and down*/
   int right=0,left=0,up=0,down=0,first_quad=0,sec_quad=0,third_quad=0,fourth_quad=0;
   int n1=0,n2=0,n3=0,n4=0,n5=0,n6=0,n7=0,n8=0;
   int kc1=0,kr1=0,kc2=0,kr2=0,kc3=0,kr3=0,kc4=0,kr4=0,kc5=0,kr5=0,kc6=0,kr6=0,kc7=0,kr7=0,kc8=0,kr8=0;/*For the knight-like validations*/


          if ((*p%2 != 0)&&(*p!=1))
            {

              for (j = 0; j < 8; j++)/*Locating the black king position*/
                {
                 for (i = 0; i < 8; i++)
                  {
                     if(board[i][j]=='k')
                      {
                       king_Col=i;
                       king_row=j;
                      }
                  }/*End of Internal for loop*/
                }/*End of the external for loop*/

/*#1 Rook-like check for Rook and queen*/

/*Rook-like right check*/

for (i=king_Col+1;(i<8 && (right == 0));i++)/* if valid == 1 the loop won't be done*/
       {
           if ((board[i][king_row]=='-') || (board[i][king_row]=='.'))
               {
                  right=0; /*Continue without doing any thing*/
               }

           else if((board[i][king_row]=='R') || (board[i][king_row]=='Q'))
              {
                  right = right+1;/*Just a flag*/
                  check_is = check_is + right;
              }
           else
             {

                i=10; /*Not checked from this side - Exits the loop without changing the value of right */
             }


       }/*End of right checking for loop*/

/*Rook-like left check*/

for (i=king_Col-1;(i>=0 && (left == 0));i--)/* if valid == 1 the loop won't be done*/
       {
            if ((board[i][king_row]=='-') || (board[i][king_row]=='.'))
               {
                  left=0; /*Continue without doing any thing*/
               }

            else if((board[i][king_row]=='R') || (board[i][king_row]=='Q'))
              {
                  left=left+1;/*Just a flag*/
                  check_is = check_is + left;
              }
            else
            {
               i=-2;/*Not checked from this side - Exits the loop without changing the value of left */
            }
       }/*End of left checking for loop*/

/*Rook-like up check*/


for (j=king_row-1;(j>=0 && (up == 0));j--)
       {
            if ((board[king_Col][j]=='-') || (board[king_Col][j]=='.'))
               {
                   up=0;  /*Continue without doing any thing*/
               }

            else if((board[king_Col][j] == 'R') || (board[king_Col][j] == 'Q'))
              {
                  up=up+1;/*Just a flag*/
                  check_is = check_is + up;
              }
            else
            {

               j=-2;/*Not checked from this side - Exits the loop without changing the value of left */
            }
       }/*End of left checking for loop*/

/*Rook-like down check*/

for (j=king_row+1;(j<8 && (down == 0));j++)
       {
           if ((board[king_Col][j]=='-') || (board[king_Col][j]=='.'))
               {
                  down=0; /*Continue without doing any thing*/
               }

           else if ((board[king_Col][j]=='R') || (board[king_Col][j] == 'Q'))
              {
                  down=down+1;/*Just a flag*/
                  check_is = check_is + down;
              }
           else
             {

                j=10; /*Not checked from this side - Exits the loop without changing the value of right */
             }


       }/*End of right checking for loop*/

/*Bishop-like check 1st-quad*/
for (i=king_Col+1,j=(king_row-1);((i<=7 && j>=0) && (first_quad ==0));i++,j--)
{
          if(board[king_Col+1][king_row-1] == 'P')
               {
                 first_quad=first_quad+1;/*Just a flag*/
                 check_is = check_is + first_quad;
               }

          else if ((board[i][j]=='-') || (board[i][j]=='.'))
               {
                  first_quad =0; /*Continue without doing any thing*/
               }

           else if ((board[i][j]=='B') || (board[i][j] == 'Q'))
              {
                  first_quad=first_quad+1;/*Just a flag*/
                  check_is = check_is + first_quad;
              }
           else
             {

                j=-2;
                i=10; /*Not checked from this side - Exits the loop without changing the value of right */
             }

}/*End of 1st quad*/


/*Bishop-like check 2nd-quad*/

for (i=king_Col-1,j=(king_row-1);((i>=0 && j>=0) && (sec_quad == 0));i--,j--)
{
           if(board[king_Col-1][king_row-1] == 'P')
               {
                 sec_quad=sec_quad+1;/*Just a flag*/
                 check_is = check_is + sec_quad;
               }
           else if ((board[i][j]=='-') || (board[i][j]=='.'))
               {
                  sec_quad=0; /*Continue without doing any thing*/
               }

           else if ((board[i][j]=='B') || (board[i][j] == 'Q'))
              {
                  sec_quad=sec_quad+1;/*Just a flag*/
                  check_is = check_is + sec_quad;
              }
           else
             {
                j=-2;
                i=-2; /*Not checked from this side - Exits the loop without changing the value of right */
             }
}/*End of 2nd quadrant*/



/*Bishop-like check 3rd-quad*/

for ((i=king_Col-1),j=(king_row+1);((i>=0 && j<=7) && (third_quad == 0));i--,j++)
{

            if ((board[i][j]=='-') || (board[i][j]=='.'))
               {
                   third_quad=0;/*Continue without doing any thing*/
               }

           else if ((board[i][j]=='B') || (board[i][j] == 'Q'))
              {
                  third_quad=third_quad+1;/*Just a flag*/
                  check_is = check_is + third_quad;
              }
           else
             {
                j=10;
                i=-2; /*Not checked from this side - Exits the loop without changing the value of right */
             }
}/*End of third quadrant*/



/*Bishop-like check 4th-quad*/
for (i=king_Col+1,j=(king_row+1);((i<=7 && j<=7) && (fourth_quad == 0));i++,j++)
{
            if ((board[i][j]=='-') || (board[i][j]=='.'))
               {
                  fourth_quad=0; /*Continue without doing any thing*/
               }

           else if ((board[i][j]=='B') || (board[i][j] == 'Q'))
              {
                  fourth_quad=fourth_quad+1;/*Just a flag*/
                  check_is = check_is + fourth_quad;
              }
           else
             {
                j=10;
                i=10; /*Not checked from this side - Exits the loop without changing the value of right */
             }
}/*End of */

/*The knight-like Checking*/

kc1=((king_Col+2)<8)&&((king_Col+2)>=0);

kr1=((king_row-1)<8)&&((king_row-1)>=0);

kc2=((king_Col+1)<8)&&((king_Col+1)>=0);

kr2=((king_row-2)<8)&&((king_row-2)>=0);

kc3=((king_Col-1)<8)&&((king_Col-1)>=0);

kr3=((king_row-2)<8)&&((king_row-2)>=0);

kc4=((king_Col-2)<8)&&((king_Col-2)>=0);

kr4=((king_row-1)<8)&&((king_row-1)>=0);

kc5=((king_Col-2)<8)&&((king_Col-2)>=0);

kr5=((king_row+1)<8)&&((king_row+1)>=0);

kc6=((king_Col-1)<8)&&((king_Col-1)>=0);

kr6=((king_row+2)<8)&&((king_row+2)>=0);

kc7=((king_Col+1)<8)&&((king_Col+1)>=0);

kr7=((king_row+2)<8)&&((king_row+2)>=0);

kc8=((king_Col+2)<8)&&((king_Col+2)>=0);

kr8=((king_row+1)<8)&&((king_row+1)>=0);




if ((board[king_Col+2][king_row-1]=='N')&&(kc1&&kr1))
        {

            n1=n1+1;
            check_is=check_is+n1;
        }



else if ((board[king_Col+1][king_row-2]=='N')&&(kc2&&kr2))
        {

            n2=n2+1;
            check_is=check_is+n2;
        }


else if ((board[king_Col-1][king_row-2]=='N')&&(kc3&&kr3))
        {

            n3=n3+1;
            check_is=check_is+n3;
        }



else if ((board[king_Col-2][king_row-1]=='N')&&(kc4&&kr4))
        {

            n4=n4+1;
            check_is=check_is+n4;
        }


else if ((board[king_Col-2][king_row+1]=='N')&&(kc5&&kr5))
        {

            n5=n5+1;
            check_is=check_is+n5;
        }


else if ((board[king_Col-1][king_row+2]=='N')&&(kc6&&kr6))
        {

            n6=n6+1;
            check_is=check_is+n6;
        }



else if ((board[king_Col+1][king_row+2]=='N')&&(kc7&&kr7))
        {

            n7=n7+1;
            check_is=check_is+n7;
        }



else if ((board[king_Col+2][king_row+1]=='N')&&(kc8&&kr8))
        {

            n8=n8+1;
            check_is=check_is+n8;
        }







if (check_is != 0)
{
    printf("The White king is checked\n");
}


       }/*End of if *p%2!=2*/



}/*End of king check fn*/

void Black_king_check()
{  int i=0;/*Columns*/
   int j=0;/*Rows*/
   int king_row=0;
   int king_Col=0;
   int check_is = 0;/*Is the sum of right left up and down*/
   int right=0,left=0,up=0,down=0,first_quad=0,sec_quad=0,third_quad=0,fourth_quad=0;
   int n1=0,n2=0,n3=0,n4=0,n5=0,n6=0,n7=0,n8=0;
   int kc1=0,kr1=0,kc2=0,kr2=0,kc3=0,kr3=0,kc4=0,kr4=0,kc5=0,kr5=0,kc6=0,kr6=0,kc7=0,kr7=0,kc8=0,kr8=0;/*For the knight-like validations*/


          if ((*p%2 == 0)&&(*p!=2))
            {

              for (j = 0; j < 8; j++)/*Locating the black king position*/
                {
                 for (i = 0; i < 8; i++)
                  {
                     if(board[i][j]=='K')
                      {
                       king_Col=i;
                       king_row=j;
                      }
                  }/*End of Internal for loop*/
                }/*End of the external for loop*/

/*#1 Rook-like check for Rook and queen*/

/*Rook-like right check*/

for (i=king_Col+1;(i<8 && (right == 0));i++)/* if valid == 1 the loop won't be done*/
       {
           if ((board[i][king_row]=='-') || (board[i][king_row]=='.'))
               {
                  right=0; /*Continue without doing any thing*/
               }

           else if((board[i][king_row]=='r') || (board[i][king_row]=='q'))
              {
                  right=right+1;/*Just a flag*/
                  check_is = check_is + right;
              }
           else
             {

                i=10; /*Not checked from this side - Exits the loop without changing the value of right */
             }


       }/*End of right checking for loop*/

/*Rook-like left check*/

for (i=king_Col-1;(i>=0 && (left == 0));i--)/* if valid == 1 the loop won't be done*/
       {
            if ((board[i][king_row]=='-') || (board[i][king_row]=='.'))
               {
                  left=0; /*Continue without doing any thing*/
               }

            else if((board[i][king_row]=='r') || (board[i][king_row]=='q'))
              {
                  left=left+1;/*Just a flag*/
                  check_is = check_is + left;
              }
            else
            {
               i=-2;/*Not checked from this side - Exits the loop without changing the value of left */
            }
       }/*End of left checking for loop*/

/*Rook-like up check*/


for (j=king_row-1;(j>=0 && (up == 0));j--)
       {
            if ((board[king_Col][j]=='-') || (board[king_Col][j]=='.'))
               {
                   up=0;  /*Continue without doing any thing*/
               }

            else if((board[king_Col][j] == 'r') || (board[king_Col][j] == 'q'))
              {
                  up=up+1;/*Just a flag*/
                  check_is = check_is + up;
              }
            else
            {

               j=-2;/*Not checked from this side - Exits the loop without changing the value of left */
            }
       }/*End of left checking for loop*/

/*Rook-like down check*/

for (j=king_row+1;(j<8 && (down == 0));j++)
       {
           if ((board[king_Col][j]=='-') || (board[king_Col][j]=='.'))
               {
                  down=0; /*Continue without doing any thing*/
               }

           else if ((board[king_Col][j]=='r') || (board[king_Col][j] == 'q'))
              {
                  down=down+1;/*Just a flag*/
                  check_is = check_is + down;
              }
           else
             {

                j=10; /*Not checked from this side - Exits the loop without changing the value of right */
             }


       }/*End of right checking for loop*/

/*Bishop-like check 1st-quad*/
for (i=king_Col+1,j=(king_row-1);((i<=7 && j>=0) && (first_quad ==0));i++,j--)
{
          if ((board[i][j]=='-') || (board[i][j]=='.'))
               {
                  first_quad =0; /*Continue without doing any thing*/
               }

           else if ((board[i][j]=='b') || (board[i][j] == 'q'))
              {
                  first_quad=first_quad+1;/*Just a flag*/
                  check_is = check_is + first_quad;
              }
           else
             {

                j=-2;
                i=10; /*Not checked from this side - Exits the loop without changing the value of right */
             }

}/*End of 1st quad*/


/*Bishop-like check 2nd-quad*/

for (i=king_Col-1,j=(king_row-1);((i>=0 && j>=0) && (sec_quad == 0));i--,j--)
{
           if ((board[i][j]=='-') || (board[i][j]=='.'))
               {
                  sec_quad=0; /*Continue without doing any thing*/
               }

           else if ((board[i][j]=='b') || (board[i][j] == 'q'))
              {
                  sec_quad=sec_quad+1;/*Just a flag*/
                  check_is = check_is + sec_quad;
              }
           else
             {
                j=-2;
                i=-2; /*Not checked from this side - Exits the loop without changing the value of right */
             }
}/*End of 2nd quadrant*/



/*Bishop-like check 3rd-quad*/

for ((i=king_Col-1),j=(king_row+1);((i>=0 && j<=7) && (third_quad == 0));i--,j++)
{
           if(board[king_Col-1][king_row+1] == 'p')
               {
                 third_quad=third_quad+1;/*Just a flag*/
                 check_is = check_is + third_quad;
               }
           else if ((board[i][j]=='-') || (board[i][j]=='.'))
               {
                   third_quad=0;/*Continue without doing any thing*/
               }

           else if ((board[i][j]=='b') || (board[i][j] == 'q'))
              {
                  third_quad=third_quad+1;/*Just a flag*/
                  check_is = check_is + third_quad;
              }
           else
             {
                j=10;
                i=-2; /*Not checked from this side - Exits the loop without changing the value of right */
             }
}/*End of third quadrant*/



/*Bishop-like check 4th-quad*/
for (i=king_Col+1,j=(king_row+1);((i<=7 && j<=7) && (fourth_quad == 0));i++,j++)
{
           if(board[king_Col+1][king_row+1] == 'p')
               {
                 fourth_quad=fourth_quad+1;/*Just a flag*/
                 check_is = check_is + fourth_quad;
               }
           else if ((board[i][j]=='-') || (board[i][j]=='.'))
               {
                  fourth_quad=0; /*Continue without doing any thing*/
               }

           else if ((board[i][j]=='b') || (board[i][j] == 'q'))
              {
                  fourth_quad=fourth_quad+1;/*Just a flag*/
                  check_is = check_is + fourth_quad;
              }
           else
             {
                j=10;
                i=10; /*Not checked from this side - Exits the loop without changing the value of right */
             }
}/*End of */

/*The knight-like Checking*/

kc1=((king_Col+2)<8)&&((king_Col+2)>=0);

kr1=((king_row-1)<8)&&((king_row-1)>=0);

kc2=((king_Col+1)<8)&&((king_Col+1)>=0);

kr2=((king_row-2)<8)&&((king_row-2)>=0);

kc3=((king_Col-1)<8)&&((king_Col-1)>=0);

kr3=((king_row-2)<8)&&((king_row-2)>=0);

kc4=((king_Col-2)<8)&&((king_Col-2)>=0);

kr4=((king_row-1)<8)&&((king_row-1)>=0);

kc5=((king_Col-2)<8)&&((king_Col-2)>=0);

kr5=((king_row+1)<8)&&((king_row+1)>=0);

kc6=((king_Col-1)<8)&&((king_Col-1)>=0);

kr6=((king_row+2)<8)&&((king_row+2)>=0);

kc7=((king_Col+1)<8)&&((king_Col+1)>=0);

kr7=((king_row+2)<8)&&((king_row+2)>=0);

kc8=((king_Col+2)<8)&&((king_Col+2)>=0);

kr8=((king_row+1)<8)&&((king_row+1)>=0);




if ((board[king_Col+2][king_row-1]=='n')&&(kc1&&kr1))
        {

            n1=n1+1;
            check_is=check_is+n1;
        }



else if ((board[king_Col+1][king_row-2]=='n')&&(kc2&&kr2))
        {

            n2=n2+1;
            check_is=check_is+n2;
        }


else if ((board[king_Col-1][king_row-2]=='n')&&(kc3&&kr3))
        {

            n3=n3+1;
            check_is=check_is+n3;
        }



else if ((board[king_Col-2][king_row-1]=='n')&&(kc4&&kr4))
        {

            n4=n4+1;
            check_is=check_is+n4;
        }


else if ((board[king_Col-2][king_row+1]=='n')&&(kc5&&kr5))
        {

            n5=n5+1;
            check_is=check_is+n5;
        }


else if ((board[king_Col-1][king_row+2]=='n')&&(kc6&&kr6))
        {

            n6=n6+1;
            check_is=check_is+n6;
        }



else if ((board[king_Col+1][king_row+2]=='n')&&(kc7&&kr7))
        {

            n7=n7+1;
            check_is=check_is+n7;
        }



else if ((board[king_Col+2][king_row+1]=='n')&&(kc8&&kr8))
        {

            n8=n8+1;
            check_is=check_is+n8;
        }







if (check_is != 0)
{
    printf("The Black king is checked\n");
}


       }/*End of if *p%2!=2*/



}/*End of king check fn*/

void check()
{
   Black_king_check();
   White_king_check();
}



void pieces_check (int a, int b, int c, int d , char Piece , char piece , int* valid, int* complete_valid, int* capture)
{
  if (board[a][8-b] == Piece)
                  {

                          if ((*p%2)==0)
                          {

                            if ((board[c][8-d] >= 'A') && (board[c][8-d] <= 'Z') && ((*valid == 1) &&(*complete_valid == 1)) ) /* if there is a friend piece */
                             {
                                 *complete_valid = 0;
                             }

                             else if ((board[c][8-d] >= 'a') && (board[c][8-d] <= 'z') &&  ((*valid == 1) &&(*complete_valid == 1)) ) /*if there is an enemy piece */
                             {
                                *capture = 2; /* 2 means that the move validation fn must return that the black piece (upper case) captured a white piece */

                             }

                             else if  ((*valid == 1) &&(*complete_valid == 1))  /*if the square is empty*/
                             {
                                 *capture = 0;
                             }

                          }/*End of (if)of the turn check*/


                          else
                          {
                             *q=0;/*Means t=0*/
                          }


                 } /*End of if that has an else if*/

               else if (board[a][8-b] == piece)
                 {

                          if ((*p%2)!=0)
                          {
                            if (((board[c][8-d] >= 'a') && (board[c][8-d] <= 'z')) && ((*valid == 1) &&(*complete_valid == 1)))  /* if there is a friend piece */
                             {
                                 *complete_valid = 0;
                             }

                             else if (((board[c][8-d] >= 'A') && (board[c][8-d] <= 'Z')) &&  ((*valid == 1) &&(*complete_valid == 1))) /*if there is an enemy piece */
                             {
                                *capture = 1; /* 1 means that the move validation fn must return that a white piece(lower case) captured a black piece */

                             }

                             else if ((*valid == 1) &&(*complete_valid == 1))/*if the square is empty*/
                             {
                                *capture = 0;
                             }

                          } /* End of (if) that checks the turn */

                          else
                          {
                             *q=0;
                          }


                 }/* The end of interior else if */


} /* End of pieces_check fn */


int MoveValidation(int a,int b,int c,int d)
{int i=0,j=0,valid=0,complete_valid,k,s,capture=13,t=1;/*t=1 is a default */
 q=&t;

/*1st the Black pawn*/


   if ((board[a][8-b] == '-')||(board[a][8-b] == '.'))/*If the user enters an empty cell*/
   {
      /* *p=*p-1;*/
   }
  else if (board[a][8-b] == 'P')/*The next else if is of the white pawn*/
  {
        /*#1*/    if ((*p%2) == 0)
              {

                   int D = 8-d; /* Only to use it in the check */
                   valid = 0;


                     for (i=0;(i<8 && (valid == 0));i++)/* For loop made for the pawns first move check */
                          {
                               if ((a == i) && (8-b == 1))
                                 {
                                    if ((c==a)&&((D == 8-b+1) || (D == 8-b+2)))
                                       {
                                         valid =1;/*Final Destination is in range*/
                                       }
                                 }
                          }/* End of the for loop */


                     if((valid == 0) && (c==a) && (D==8-b+1)) /*When the first postion is not the first move to the pawn*/
                        {
                        valid =1;/*Final Destination is in range*/
                        }



                     if ((((c==a-1)&&(8-d==8-b+1)) || ((c==a+1)&&(8-d==8-b+1))) && (valid==0))
                        {
                          if ((board[c][8-d]>='a')&&(board[c][8-d]<='z'))

                              {
                                    capture =2;
                                    valid=1;
                              }
                        }


                    if (valid == 1) /*Checking the complete valid*/

                       {

                          if (capture==2)
                               {
                                   complete_valid=1;
                               }

                          else if (((board[c][8-d]>='A') && (board[c][8-d]<='Z')) || ((board[c][8-d]>='a') && (board[c][8-d]<='z')))/*To check that there is no enemy or friend in the destination */
                               {
                                 complete_valid=0;

                               }

                          else
                               {

                                 capture = 0;
                                 complete_valid=1;

                               }

                        } /* End of (if valid ==1) */



                   }/*End of if(*p%2=2)*/

           else /*The turn is wrong*/
           {
             t=0;
           }

    /*#2*/
            if (t==0)
            {
                printf("Invalid input\n");
               /* *p=*p-1;*/
            }
            else if ((valid==1) && (complete_valid==0))
            {
               printf("Invalid move\n");
              /* *p=*p-1;*/
            }
            else if (valid==0)
            {
                printf("Invalid move\n");
               /* *p=*p-1;*/
            }
            else if (capture==0)
            {
              board[c][8-d] = board[a][8-b];
              board[a][8-b] = 0;

            }




    } /*The end of the BLACK pawn's else if*/









  /*2nd the White pawn*/



  else if (board[a][8-b] == 'p')/*The next else if is of the Rook */
  {
    /*#1*/     if ((*p%2) != 0)
                  {

                        int D = 8-d; /*Only to use it in the check */
                        valid = 0;


                       for (i=0;(i<8 && (valid == 0));i++)/* For loop made for the pawns first move check */
                           {
                               if ((a == i) && (8-b == 6))
                                  {
                                    if ((c==a)&&((D == 8-b-1) || (D == 8-b-2)))
                                        {
                                           valid =1;/*Final Destination is in range*/
                                        } /* End of (if) */
                                   }/* End of (if) */
                            }/* End of the for loop */


                      if((valid == 0) && (c==a) && (D==8-b-1)) /*When the first postion is not the first move to the pawn*/
                        {
                           valid =1;/*Final Destination is in range*/
                        }

                       if ((((c==a+1)&&(8-d==8-b-1)) || ((c==a-1)&&(8-d==8-b-1)))&& (valid==0))
                         {
                           if ((board[c][8-d]>='A')&&(board[c][8-d]<='Z'))

                                  {
                                       capture =1;
                                       valid=1;

                                  }
                         }/*End*/



                       if (valid == 1)

                          {
                               if (capture==1)
                                {
                                   complete_valid=1;
                                }

                              else if (((board[c][8-d]>='A') && (board[c][8-d]<='Z')) || ((board[c][8-d]>='a') && (board[c][8-d]<='z')))/*To check that there is no enemy or friend in the destination */
                                {
                                   complete_valid=0;
                                }

                               else
                                {

                                  capture = 0;
                                  complete_valid=1;

                                 }

                          } /* End of (if valid ==1) */



                      }/*End of if(*p%2=2)*/

                  else /*The turn is wrong*/
                      {
                         t=0;
                      }

    /*#2*/
                if (t==0)
                     {
                      printf("Invalid input\n");
                      /* *p=*p-1;*/
                     }
                else if ((valid==1) && (complete_valid==0))
                    {
                      printf("Invalid move\n");
                      /* *p=*p-1;*/
                     }
               else if (valid==0)
                    {
                     printf("Invalid move\n");
                     /* *p=*p-1;*/
                    }
               else if (capture==0)
                   {
                     board[c][8-d] = board[a][8-b];
                     board[a][8-b] = 0;

                   }




    } /*The end of the White pawn's else if*/









/*3rd the rook*/



  else if (board[a][8-b] == 'R' || board[a][8-b] == 'r') /*White and Black are like each other*/
   {

    valid=0;
    complete_valid=0;/*If these two variable remain zeros until all the 4 cases are checked it means that (capture = 13) (invalid)*/

    /*Rook's Right side check*/



     for (i=a+1;(i<8 && (valid ==0));i++)/* if valid == 1 the loop won't be done*/
       {
          int D = 8-d;/*Only to use it in the check */
          int B = 8-b;/*Only to use it in the check */
          if((c == i) && (D == B))
           {
              valid=1; /*Final Destination is in range*/
              complete_valid = 1; /* By default ,the piece can move (if there is a constraint the value will be 0) */

/* ** Checking the emptiness of the way leading to the final destination** */

              for (k=a+1;(k<i && (complete_valid == 1));k++)/*Final destination won't be checked here, will be checked later*/
               {
                   if (((board[k][8-b] >= 'A') && (board[k][8-b] <= 'Z')) || ((board[k][8-b]>='a') && (board[k][8-b]<='z'))) /*To check that there is no enemy or friend in the way to destination */
                   {
                       complete_valid =0; /* Means that there is a constraint */

                   }
                   else {complete_valid = 1;}
               }/*End of the interior for loop */



            } /*End of if */

       }/*End of for loop of the right side*/



    /*Rook's left side*/


     for (i=a-1;(i>=0 && (valid ==0));i--)/* if valid == 1 the loop won't be done*/
       {
          int D = 8-d;/*Only to use it in the check */
          int B = 8-b;/*Only to use it in the check */
          if((c==i) && (D==B))
           {
              valid=1;/*Final Destination is in range*/
              complete_valid = 1; /* By default ,the piece can move (if there is a constraint the value will be 0) */

/* ** Checking the emptiness of the way leading to the final destination** */

              for (k=a-1;(k>i && (complete_valid == 1));k--)/*Final destination won't be checked here, will be checked later*/
               {
                   if (((board[k][8-b]>='A') && (board[k][8-b]<='Z')) || ((board[k][8-b]>='a') && (board[k][8-b]<='z'))) /*To check that there is no enemy or friend in the way to destination */
                   {
                       complete_valid =0; /* Means that there is a constraint */

                   }

                   else {complete_valid = 1;} /* There is no pieces by its way */
               }/*End of the interior for loop */



           } /*End of if */

       }/*End of for loop of the left side*/




    /*Rook's upper side*/



     for (j=8-b-1;(j>=0 && (valid == 0));j--)/* if valid == 1 the loop won't be done*/
       {
          int D = 8-d;/*Only to use it in the check */

          if((c==a)&&(D==j))
           {
             valid=1;/*Final Destination is in range*/
             complete_valid = 1; /* By default ,the piece can move (if there is a constraint the value will be 0) */


/* ** Checking the emptiness of the way leading to the final destination** */

              for (k=8-b-1 ; ((k>j) && (complete_valid == 1)); k--)/*Final destination won't be checked here, will be checked later*/
               {
                   if (((board[a][k]>='A') && (board[a][k]<='Z')) || ((board[a][k]>='a') && (board[a][k]<='z'))) /*To check that there is no enemy or friend in the way to destination */
                   {
                       complete_valid =0; /* Means that there is a constraint */

                   }

                   else {complete_valid = 1;} /* There is no pieces by its way */
               }/*End of the interior for loop */


           } /*End of if */

       }/*End of for loop of the upper side*/


    /* Rook's Lower Side */

    for (j=8-b+1;(j<8 && (valid ==0));j++)/* if valid == 1 the loop won't be done*/
       {
          int D=8-d;/*Only to use it in the check */

          if((c==a)&&(D==j))
           {
              valid=1;/*Final Destination is in range*/
              complete_valid = 1; /* By default ,the piece can move (if there is a constraint the value will be 0) */


/* ** Checking the emptiness of the way leading to the final destination** */

              for (k=8-b+1 ; (k<j && (complete_valid == 1)) ; k++)/*Final destination won't be checked here, will be checked later*/
               {
                   if (((board[a][k]>='A') && (board[a][k]<='Z')) || ((board[a][k]>='a') && (board[a][k]<='z'))) /*To check that there is no enemy or friend in the way to destination */
                   {
                       complete_valid =0; /* Means that there is a constraint */

                   }

                   else {complete_valid = 1;} /* There is no pieces by its way */
               }/*End of the interior for loop */



           } /*End of if */

       }/*End of for loop of the lower side*/

       pieces_check (a, b, c, d ,'R', 'r', &valid, &complete_valid, &capture);

         if (t==0)
            {
                printf("Invalid input\n");
               /* *p=*p-1;*/
            }
            else if ((valid==1) && (complete_valid==0))
            {
               printf("Invalid move\n");
               /* *p=*p-1;*/
            }
            else if (valid==0)
            {
                printf("Invalid move\n");
               /* *p=*p-1;*/
            }
            else if (capture==0)
            {
              board[c][8-d] = board[a][8-b];
              board[a][8-b] = 0;

            }


    }/*The end of the rook's else if */



    /* 4th the Knight */


  else if (board[a][8-b] == 'N'||board[a][8-b] == 'n')/*The next (else if) is of the Bishop*/
  {  /* Anti clockwise check from +ve x direction */

      int D=8-d;/*Only to use it in the check */
      valid =0;
      complete_valid=1;/*The knight and the king only as the have no complete validation*/


     if ((c == a+2) && (D == 8-b-1))
        {

            valid=1;/*Final Destination is in range*/
        }


    else if ((c==a+1) && (D==8-b-2))
        {

              valid=1;/*Final Destination is in range*/
        }

    else if ((c==a-1) && (D == 8-b-2))
        {

              valid=1;/*Final Destination is in range*/
        }

     else if ((c==a-2) && (D == 8-b-1))
        {

              valid=1;/*Final Destination is in range*/
        }

     else if ((c == a-2) && (D == 8-b+1))
        {

              valid=1;/*Final Destination is in range*/
        }

     else if ((c==a-1) && (D==8-b+2))
        {
              valid=1;/*Final Destination is in range*/
        }

     else if ((c==a+1) && (D==8-b+2))
        {

              valid=1;/*Final Destination is in range*/
        }

     else if ((c==a+2) && (D==8-b+1))
        {

              valid=1;/*Final Destination is in range*/
        }

        if ((board[a][8-b] == 'N'))
        {
                if ((*p%2)==0)

                          {
                            if (((board[c][8-d] >= 'A') && (board[c][8-d] <= 'Z'))&& ((valid==1)&&(complete_valid==1))) /* if there is a friend piece */
                             {
                                complete_valid=0;
                             }

                             else if (((board[c][8-d] >= 'a') && (board[c][8-d] <= 'z')) && ((valid==1)&&(complete_valid==1)))/*if there is an enemy piece */
                             {
                                capture = 2; /* 2 means that the move validation fn must return that the black piece (upper case) captured a white piece */

                             }

                             else if ((valid == 1)&&(complete_valid == 1))/*if the square is empty*/
                             {
                                 capture = 0;


                             }

                          }/*End of (if) that checks the turn*/

                          else
                          {
                              t=0;
                          }


        } //End of 'N''s (if)

    else if ((board[a][8-b] == 'n'))
        {
                         if ((*p%2) != 0)
                           {

                            if (((board[c][8-d] >= 'a') && (board[c][8-d] <= 'z')) && ((valid==1)&&(complete_valid==1)))  /* if there is a friend piece */
                             {

                                 complete_valid=0;
                             }

                             else if (((board[c][8-d] >= 'A') && (board[c][8-d] <= 'Z'))&& ((valid==1)&&(complete_valid==1))) /*if there is an enemy piece */
                             {
                                capture = 1; /* 1 means that the move validation fn must return that a white piece(lower case) captured a black piece */

                             }

                             else if ((valid==1) && (complete_valid==1))/*if the square is empty*/
                             {
                                capture = 0;

                             }

                           }/*End of (if) of the turn check*/

                           else
                           {
                              t=0;
                           }
        }//End of 'n''s (if)

            if (t==0)
            {
                printf("Invalid input\n");
                /* *p=*p-1;*/
            }
            else if ((valid==1) && (complete_valid==0))
            {
               printf("Invalid move\n");
               /* *p=*p-1;*/
            }
            else if (valid==0)
            {
                printf("Invalid move\n");
               /* *p=*p-1;*/
            }
            else if (capture==0)
            {
              board[c][8-d] = board[a][8-b];
              board[a][8-b] = 0;

            }









     }/*The end of the knight's else if*/



     /* 5th The Bishop */


  else if (board[a][8-b] == 'B' || board[a][8-b] == 'b')

   {

     valid = 0;
     complete_valid = 0; /*If these two variable remain zeros until all the 4 cases are checked it means that (capture = 13) (invalid)*/



     /* 45 degree 1st quadrant */

     for (i=a+1,j=(8-b-1);((i<=7 && j>=0) && (valid ==0));i++,j--)/* if valid == 1 the loop won't be done*/
       {
          int D=8-d;/*Only to use it in the check */

          if((c==i)&&(D==j))
           {
              valid=1;/*Final Destination is in range*/
              complete_valid = 1; /* By default ,the piece can move (if there is a constraint the value will be 0) */


/* ** Checking the emptiness of the way leading to the final destination** */

           for (k=a+1,s=(8-b-1);((k<i && s>j) && (complete_valid ==1));k++,s--) /*Final destination won't be checked here, will be checked later*/
             {
               if (((board[k][s]>='A') && (board[k][s]<='Z')) || ((board[k][s]>='a') && (board[k][s]<='z'))) /*To check that there is no enemy or friend in the way to destination */
                   {
                       complete_valid =0; /* Means that there is a constraint */
                   }

                   else {complete_valid = 1;} /* There is no pieces by its way */
             }/*End of the interior for loop */



           } /*End of if */

       }/*End of for*/





       /* 45 degree 2nd quadrant */

       for (i=a-1,j=(8-b-1);((i>=0 && j>=0) && (valid ==0));i--,j--)/* if valid == 1 the loop won't be done*/
       {
          int D=8-d;/*Only to use it in the check */

          if((c==i)&&(D==j))
           {
              valid=1;/*Final Destination is in range*/
              complete_valid = 1; /* By default ,the piece can move (if there is a constraint the value will be 0) */

/* ** Checking the emptiness of the way leading to the final destination** */

           for (k=a-1,s=(8-b-1);((k>i && s>j) && (complete_valid ==1));k--,s--) /*Final destination won't be checked here, will be checked later*/
             {
               if (((board[k][s]>='A') && (board[k][s]<='Z')) || ((board[k][s]>='a') && (board[k][s]<='z'))) /*To check that there is no enemy or friend in the way to destination */
                   {
                       complete_valid =0; /* Means that there is a constraint */

                   }

                   else {complete_valid = 1;} /* There is no pieces by its way */
             }/*End of the interior for loop */


           }/*End of if */

       }/*End of for*/





       /* 45 degree 3rd quadrant */



      for (i=a-1,j=(8-b+1);((i>=0 && j<=7) && (valid ==0));i--,j++)/* if valid == 1 the loop won't be done*/
       {
          int D=8-d;/*Only to use it in the check */

          if((c==i)&&(D==j))
           {

              valid=1;/*Final Destination is in range*/
              complete_valid = 1; /* By default ,the piece can move (if there is a constraint the value will be 0) */

/* ** Checking the emptiness of the way leading to the final destination** */

           for (k=a-1,s=(8-b+1);((k>i && s<j) && (complete_valid ==1));k--,s++) /*Final destination won't be checked here, will be checked later*/
             {
               if (((board[k][s]>='A') && (board[k][s]<='Z')) || ((board[k][s]>='a') && (board[k][s]<='z'))) /*To check that there is no enemy or friend in the way to destination */
                   {
                       complete_valid =0; /* Means that there is a constraint */

                   }

                   else {complete_valid = 1;} /* There is no pieces by its way */
             }/*End of the interior for loop */


           }/*End of if */

       }/*End of for*/






       /* 45 degree 4th quadrant */


       for (i=a+1,j=(8-b+1);((i<=7 && j<=7) && (valid ==0));i++,j++)/* if valid == 1 the loop won't be done*/
       {
          int D=8-d;/*Only to use it in the check */

          if((c==i)&&(D==j))
           {
              valid=1;/*Final Destination is in range*/
              complete_valid = 1; /* By default ,the piece can move (if there is a constraint the value will be 0) */

/* ** Checking the emptiness of the way leading to the final destination** */


      for (k=a+1,s=(8-b+1);((k<i && s<j) && (complete_valid ==1));k++,s++) /*Final destination won't be checked here, will be checked later*/
             {
               if (((board[k][s]>='A') && (board[k][s]<='Z')) || ((board[k][s]>='a') && (board[k][s]<='z'))) /*To check that there is no enemy or friend in the way to destination */
                   {
                       complete_valid =0; /* Means that there is a constraint */

                   }

                   else {complete_valid = 1;} /* There is no pieces by its way */
             }/*End of the interior for loop */





           }/*End of if */

       }/*End of for*/

       pieces_check (a, b, c, d ,'B', 'b', &valid, &complete_valid, &capture);


                if (t==0)
                     {
                      printf("Invalid input\n");
                      /* *p=*p-1;*/
                     }
                else if ((valid==1) && (complete_valid==0))
                    {
                      printf("Invalid move\n");
                      /* *p=*p-1;*/
                     }
               else if (valid==0)
                    {
                     printf("Invalid move\n");
                     /* *p=*p-1;*/
                    }
               else if (capture==0)
                   {
                     board[c][8-d] = board[a][8-b];
                     board[a][8-b] = 0;

                   }



   } /*The end of Bishop's else if*/



   /* 6th the Queen */

   else if (board[a][8-b] == 'Q' || board[a][8-b] == 'q')/*The next else if is of the King*/
   {
    valid = 0;
    complete_valid = 0;

   /*Queen's rook-like move Right side check*/



for (i=a+1;(i<8 && (valid ==0));i++)/* if valid == 1 the loop won't be done*/
       {
          int D = 8-d;/*Only to use it in the check */
          int B = 8-b;/*Only to use it in the check */
          if((c == i) && (D == B))
           {
              valid=1; /*Final Destination is in range*/
              complete_valid = 1; /* By default ,the piece can move (if there is a constraint the value will be 0) */

/* ** Checking the emptiness of the way leading to the final destination** */

              for (k=a+1;(k<i && (complete_valid == 1));k++)/*Final destination won't be checked here, will be checked later*/
               {
                   if (((board[k][8-b] >= 'A') && (board[k][8-b] <= 'Z')) || ((board[k][8-b]>='a') && (board[k][8-b]<='z'))) /*To check that there is no enemy or friend in the way to destination */
                   {
                       complete_valid =0; /* Means that there is a constraint */

                   }
                   else {complete_valid = 1;}
               }/*End of the interior for loop */




            } /*End of if */

       }/*End of for loop of the right side*/



    /*Queen's rook-like move left side*/



    for (i=a-1;(i>=0 && (valid ==0));i--)/* if valid == 1 the loop won't be done*/
       {
          int D = 8-d;/*Only to use it in the check */
          int B = 8-b;/*Only to use it in the check */
          if((c==i) && (D==B))
           {
              valid=1;/*Final Destination is in range*/
              complete_valid = 1; /* By default ,the piece can move (if there is a constraint the value will be 0) */

/* ** Checking the emptiness of the way leading to the final destination** */

              for (k=a-1;(k>i && (complete_valid == 1));k--)/*Final destination won't be checked here, will be checked later*/
               {
                   if (((board[k][8-b]>='A') && (board[k][8-b]<='Z')) || ((board[k][8-b]>='a') && (board[k][8-b]<='z'))) /*To check that there is no enemy or friend in the way to destination */
                   {
                       complete_valid =0; /* Means that there is a constraint */

                   }

                   else {complete_valid = 1;} /* There is no pieces by its way */
               }/*End of the interior for loop */



           } /*End of if */

       }/*End of for loop of the left side*/






    /*Queen's rook-like move upper side*/



    for (j=8-b-1;(j>=0 && (valid == 0));j--)/* if valid == 1 the loop won't be done*/
       {
          int D = 8-d;/*Only to use it in the check */

          if((c==a)&&(D==j))
           {
             valid=1;/*Final Destination is in range*/
             complete_valid = 1; /* By default ,the piece can move (if there is a constraint the value will be 0) */


/* ** Checking the emptiness of the way leading to the final destination** */

              for (k=8-b-1 ; ((k>j) && (complete_valid == 1)); k--)/*Final destination won't be checked here, will be checked later*/
               {
                   if (((board[a][k]>='A') && (board[a][k]<='Z')) || ((board[a][k]>='a') && (board[a][k]<='z'))) /*To check that there is no enemy or friend in the way to destination */
                   {
                       complete_valid =0; /* Means that there is a constraint */

                   }

                   else {complete_valid = 1;} /* There is no pieces by its way */
               }/*End of the interior for loop */



           } /*End of if */

       }/*End of for loop of the upper side*/



    /* Queen's rook-like move Lower Side */

     for (j=8-b+1;(j<8 && (valid ==0));j++)/* if valid == 1 the loop won't be done*/
       {
          int D=8-d;/*Only to use it in the check */

          if((c==a)&&(D==j))
           {
              valid=1;/*Final Destination is in range*/
              complete_valid = 1; /* By default ,the piece can move (if there is a constraint the value will be 0) */


/* ** Checking the emptiness of the way leading to the final destination** */

              for (k=8-b+1 ; (k<j && (complete_valid == 1)) ; k++)/*Final destination won't be checked here, will be checked later*/
               {
                   if (((board[a][k]>='A') && (board[a][k]<='Z')) || ((board[a][k]>='a') && (board[a][k]<='z'))) /*To check that there is no enemy or friend in the way to destination */
                   {
                       complete_valid =0; /* Means that there is a constraint */

                   }

                   else {complete_valid = 1;} /* There is no pieces by its way */
               }/*End of the interior for loop */




           } /*End of if */

       }/*End of for loop of the lower side*/




         /* Queen's bishop-like move 45 degree 1st quadrant */

     for (i=a+1,j=(8-b-1);((i<=7 && j>=0) && (valid ==0));i++,j--)/* if valid == 1 the loop won't be done*/
       {
          int D=8-d;/*Only to use it in the check */

          if((c==i)&&(D==j))
           {
              valid=1;/*Final Destination is in range*/
              complete_valid = 1; /* By default ,the piece can move (if there is a constraint the value will be 0) */


/* ** Checking the emptiness of the way leading to the final destination** */

           for (k=a+1,s=(8-b-1);((k<i && s>j) && (complete_valid ==1));k++,s--) /*Final destination won't be checked here, will be checked later*/
             {
               if (((board[k][s]>='A') && (board[k][s]<='Z')) || ((board[k][s]>='a') && (board[k][s]<='z'))) /*To check that there is no enemy or friend in the way to destination */
                   {
                       complete_valid =0; /* Means that there is a constraint */

                   }

                   else {complete_valid = 1;} /* There is no pieces by its way */
             }/*End of the interior for loop */



           } /*End of if */

       }/*End of for*/



       /* Queen's bishop-like move 45 degree 2nd quadrant */

       for (i=a-1,j=(8-b-1);((i>=0 && j>=0) && (valid ==0));i--,j--)/* if valid == 1 the loop won't be done*/
       {
          int D=8-d;/*Only to use it in the check */

          if((c==i)&&(D==j))
           {
              valid=1;/*Final Destination is in range*/
              complete_valid = 1; /* By default ,the piece can move (if there is a constraint the value will be 0) */

/* ** Checking the emptiness of the way leading to the final destination** */

           for (k=a-1,s=(8-b-1);((k>i && s>j) && (complete_valid ==1));k--,s--) /*Final destination won't be checked here, will be checked later*/
             {
               if (((board[k][s]>='A') && (board[k][s]<='Z')) || ((board[k][s]>='a') && (board[k][s]<='z'))) /*To check that there is no enemy or friend in the way to destination */
                   {
                       complete_valid =0; /* Means that there is a constraint */

                   }

                   else {complete_valid = 1;} /* There is no pieces by its way */
             }/*End of the interior for loop */



           }/*End of if */

       }/*End of for*/


       /* Queen's bishop-like move 45 degree 3rd quadrant */



      for (i=a-1,j=(8-b+1);((i>=0 && j<=7) && (valid ==0));i--,j++)/* if valid == 1 the loop won't be done*/
       {
          int D=8-d;/*Only to use it in the check */

          if((c==i)&&(D==j))
           {

              valid=1;/*Final Destination is in range*/
              complete_valid = 1; /* By default ,the piece can move (if there is a constraint the value will be 0) */

/* ** Checking the emptiness of the way leading to the final destination** */

           for (k=a-1,s=(8-b+1);((k>i && s<j) && (complete_valid ==1));k--,s++) /*Final destination won't be checked here, will be checked later*/
             {
               if (((board[k][s]>='A') && (board[k][s]<='Z')) || ((board[k][s]>='a') && (board[k][s]<='z'))) /*To check that there is no enemy or friend in the way to destination */
                   {
                       complete_valid =0; /* Means that there is a constraint */

                   }

                   else {complete_valid = 1;} /* There is no pieces by its way */
             }/*End of the interior for loop */



           }/*End of if */

       }/*End of for*/



       /* Queen's bishop-like move 45 degree 4th quadrant */


       for (i=a+1,j=(8-b+1);((i<=7 && j<=7) && (valid ==0));i++,j++)/* if valid == 1 the loop won't be done*/
       {
          int D=8-d;/*Only to use it in the check */

          if((c==i)&&(D==j))
           {
              valid=1;/*Final Destination is in range*/
              complete_valid = 1; /* By default ,the piece can move (if there is a constraint the value will be 0) */

/* ** Checking the emptiness of the way leading to the final destination** */


      for (k=a+1,s=(8-b+1);((k<i && s<j) && (complete_valid ==1));k++,s++) /*Final destination won't be checked here, will be checked later*/
             {
               if (((board[k][s]>='A') && (board[k][s]<='Z')) || ((board[k][s]>='a') && (board[k][s]<='z'))) /*To check that there is no enemy or friend in the way to destination */
                   {
                       complete_valid =0; /* Means that there is a constraint */

                   }

                   else {complete_valid = 1;} /* There is no pieces by its way */
             }/*End of the interior for loop */





           }/*End of if */

       }/*End of for*/


       pieces_check (a, b, c, d ,'Q', 'q', &valid, &complete_valid, &capture);

                if (t==0)
                     {
                      printf("Invalid input\n");
                      /* *p=*p-1;*/
                     }
                else if ((valid==1) && (complete_valid==0))
                    {
                      printf("Invalid move\n");
                      /* *p=*p-1;*/
                     }
               else if (valid==0)
                    {
                     printf("Invalid move\n");
                     /* *p=*p-1;*/
                    }
               else if (capture==0)
                   {
                     board[c][8-d] = board[a][8-b];
                     board[a][8-b] = 0;
                   }


   }/*The end of the Queen's else if*/

   /* 7th the King */

  else if (board[a][8-b] == 'K'||board[a][8-b] == 'k')/* The Last else if */
  {
      /* Anti clockwise check from +ve x direction*/

      int D=8-d;/*Only to use it in the check */
      valid =0;
      complete_valid=1;/*Special case for the king as it dosn't need complete validation*/

     if ((c == a+1) && (D == 8-b))
        {

            valid=1;/*Final Destination is in range*/
        }


    else if ((c==a+1) && (D==8-b-1))
        {
              valid=1;/*Final Destination is in range*/
        }

    else if ((c==a) && (D == 8-b-1))
        {
            valid=1;/*Final Destination is in range*/
        }

     else if ((c==a-1) && (D == 8-b-1))
        {
               valid=1;/*Final Destination is in range*/
        }

     else if ((c==a-1) && (D==8-b))
        {
               valid=1;/*Final Destination is in range*/
        }

     else if ((c==a-1) && (D==8-b+1))
        {
              valid=1;/*Final Destination is in range*/
        }

     else if ((c==a) && (D==8-b+1))
        {
            valid=1;/*Final Destination is in range*/
        }

     else if ((c==a+1) && (D==8-b+1))
        {
              valid=1;/*Final Destination is in range*/
        }
     if ((board[a][8-b] == 'K'))
        {            if ((*p%2)==0)
                           {

                            if (((board[c][8-d] >= 'A') && (board[c][8-d] <= 'Z')) && ((valid == 1) &&(complete_valid == 1)))  /* if there is a friend piece */
                             {
                                complete_valid=0;
                             }

                             else if (((board[c][8-d] >= 'a') && (board[c][8-d] <= 'z')) && ((valid == 1) &&(complete_valid == 1)) ) /*if there is an enemy piece */
                             {
                                capture = 2; /* 2 means that the move validation fn must return that the black piece (upper case) captured a white piece */

                             }

                             else if ((valid == 1) &&(complete_valid == 1))/*if the square is empty*/
                             {
                                 capture = 0;

                             }

                           }/*End of if of the turn check */

                           else
                           {
                               t=0;

                           }

        } //End of 'K''s (if)

    else if ((board[a][8-b] == 'k'))
        {              if ((*p%2)!=0)
                           {
                            if (((board[c][8-d] >= 'a') && (board[c][8-d] <= 'z'))&& ((valid == 1) &&(complete_valid == 1)))  /* if there is a friend piece */
                             {

                                 complete_valid=0;

                             }

                             else if (((board[c][8-d] >= 'A') && (board[c][8-d] <= 'Z')) && ((valid == 1) &&(complete_valid == 1))) /*if there is an enemy piece */
                             {
                                capture = 1; /* 1 means that the move validation fn must return that a white piece(lower case) captured a black piece */

                             }

                             else if ((valid == 1) &&(complete_valid == 1))/*if the square is empty*/
                             {
                                capture = 0;

                             }

                           } /*End of if of the turn check */

                              else
                           {

                             t=0;
                           }
        }//End of 'k''s (if)

/*King-King Check*/

if ( ((*p%2)==0) && (board[a][8-b]=='K') && (capture == 0 || capture == 1 || capture == 2) )
{
     if (board[c+1][8-d]=='k')
       {

          valid=0;
          capture=13;

       }

      else if (board[c+1][8-d-1]=='k')
       {

          valid=0;
          capture=13;

       }

      else if (board[c][8-d-1]=='k')
       {

          valid=0;
          capture=13;

       }

       else if (board[c-1][8-d-1]=='k')
       {

          valid=0;
          capture=13;

       }

       else if (board[c-1][8-d]=='k')
       {

          valid=0;
          capture=13;

       }

       else if (board[c-1][8-d+1]=='k')
       {

          valid=0;
          capture=13;

       }

       else if (board[c][8-d+1]=='k')
       {

          valid=0;
          capture=13;

       }

       else if (board[c+1][8-d+1]=='k')
       {

          valid=0;
          capture=13;

       }


}/*End of KingKing check1*/

if ( ((*p%2)!=0) && (board[a][8-b]=='k') && (capture == 0 || capture == 1 || capture == 2) )
{
     if (board[c+1][8-d]=='K')
       {

          valid=0;
          capture=13;

       }

      else if (board[c+1][8-d-1]=='K')
       {

          valid=0;
          capture=13;

       }

      else if (board[c][8-d-1]=='K')
       {

          valid=0;
          capture=13;

       }

       else if (board[c-1][8-d-1]=='K')
       {

          valid=0;
          capture=13;

       }

       else if (board[c-1][8-d]=='K')
       {

          valid=0;
          capture=13;

       }

       else if (board[c-1][8-d+1]=='K')
       {

          valid=0;
          capture=13;

       }

       else if (board[c][8-d+1]=='K')
       {

          valid=0;
          capture=13;

       }

       else if (board[c+1][8-d+1]=='K')
       {

          valid=0;
          capture=13;

       }


}/*End of KingKing check*/

                if (t==0)
                     {
                      printf("Invalid input\n");
                      /* *p=*p-1;*/
                     }
                else if ((valid==1) && (complete_valid==0))
                    {
                      printf("Invalid move\n");
                      /* *p=*p-1;*/
                     }
               else if (valid==0)
                    {
                     printf("Invalid move\n");
                     /* *p=*p-1;*/
                    }
               else if (capture==0)
                   {
                     board[c][8-d] = board[a][8-b];
                     board[a][8-b] = 0;
                   }

     }/*The end of the King's's else if (AND THE LAST) */


    return capture;
}/*End of move validation fn */


int checking(char a)
{ int valid;
    if((a>=65&&a<=72)||(a>=97&&a<=104))
    {
        valid=1;
    }
    else
    {
        valid=0;
    }
    return valid;
}

void input()
{char a,c,E;
int b,d,check=0,valid=0,breaker=0;
do{
     check=0;
     valid=0;
     int player;
     player=(*p)%2;
     if(player==0)
     {player=2;

     }
        printf("\nInsert your move player %d: ",player);
scanf(" %c",&a);
if(a=='U'||a=='u')
{char l,k,z;
scanf("%c",&l);
scanf("%c",&c);
scanf("%c",&k);
z=getchar();
while(z!='\n')
{z=getchar();
    l='v';
}
    if((l=='n'||l=='N')&&(c=='d'||c=='D')&&(k=='o'||k=='O'))
    {UNDO();
    breaker=1;
    break;

    }
    else
    {
        return input();
    }
}


if(a=='R'||a=='r')
{char l,k,z;
scanf("%c",&l);
scanf("%c",&c);
scanf("%c",&k);
z=getchar();
while(z!='\n')
{z=getchar();
    l='v';
}
    if((l=='e'||l=='E')&&(c=='d'||c=='D')&&(k=='o'||k=='O'))
    {REDO();
    breaker=1;
    break;

    }
    else
    {
        return input();
    }
}






/*if(a=='U'||a=='u')//Undo check function
{
   if(UNDO()==1)
   {break;}
   else
   { return input();
   }

}*/
if(a=='s'||a=='S')
{char l,k,z;
    scanf("%c",&l);
scanf(" %c",&c);
scanf("%c",&k);
z=getchar();
while(z!='\n')
{z=getchar();
    l='f';
}
    if((l=='a'||l=='A')&&(c=='v'||c=='V')&&(k=='e'||k=='E'))
     {SAVE();
        breaker=1;
        break;
     }
     else
     {return input();

     }

}



if(a=='l'||a=='L')
{char l,k,z;
    scanf("%c",&l);
    scanf(" %c",&c);
    scanf("%c",&k);
    z=getchar();
while(z!='\n')
{   z=getchar();
    l='f';
}
    if((l=='o'||l=='O')&&(c=='a'||c=='A')&&(k=='d'||k=='D'))
     {LOAD();
        breaker=1;
        break;
     }
     else
     {return input();

     }


}


valid+=scanf("%1d",&b); //Valid checks for letters inputed instead of numbers
scanf(" %c",&c);
valid+=scanf("%1d",&d);
E=getchar();
if(E!='\n')
{
    valid=0;
    while(E!='\n')
    {
        E=getchar();
    }
}

check+=checking(a); //check performs a function that checks whether the input is in the correct range
check+=checking(c);

if(a>=97&&a<=104)
{a=toupper(a);
}
if(c>=97&&c<=104)
{c=toupper(c);
}
a=a-'A';
c=c-'A';
if(valid==2)
   {
    check+=MoveValidation(a,b,c,d);


    }}
while(valid!=2||(check!=3&&check!=2&&check!=4)||b>8||b<0||d>8||d<0);
if(breaker==1)
{ dynamic_lost_arrays();

}

if(breaker==0)
{ if(check==3||check==4)
    {CAPTURE(a,b,c,d);

    }

    memcpy(undo_redo_array[*p-1].board_copy,board,sizeof(board));
undo_redo_array[*p-1].turn=*p;

num_of_undos=0;





    *p=*p+1;

}
}


int Turn()
{ int i=0,j,checkmate=0,stalemate=0,validate;
static int turn=1;
p=&turn;
    char head[]="ABCDEFGH";
if (turn==1)
{for(i=0;i<8;i++)
 {board[i][6]='p';}
 board[0][7]='r';
 board[1][7]='n';
 board[2][7]='b';
 board[3][7]='q';
 board[4][7]='k';
 board[5][7]='b';
 board[6][7]='n';
 board[7][7]='r';
 for(i=0;i<8;i++)
 {board[i][1]='P';}
 board[0][0]='R';
 board[1][0]='N';
 board[2][0]='B';
 board[3][0]='Q';
 board[4][0]='K';
 board[5][0]='B';
 board[6][0]='N';
 board[7][0]='R';

}



    for(j=0;j<8;j++)
    {
        for(i=0;i<8;i++)
        { if(board[i][j]==0)
        {
            if((j+i)%2==1)
        { board[i][j]='.';
        }
        else{
                board[i][j]='-';

        }
        }
    }}




//Display function
    printf("   %c",head[0]);
    for(i=1;i<8;i++)
    {printf(" %c",head[i]);

    }
    printf("\n");
    for(j=0;j<8;j++)
    {printf(" %d",8-j);
        for(i=0;i<8;i++)
        {
          printf(" %c",board[i][j]);
        }
        printf(" %d",8-j);
        printf("\n");
    }
    printf("   %c",head[0]);
    for(i=1;i<8;i++)
    {printf(" %c",head[i]);

    }


int L_A_C=0;

printf("\n\nBlack Lost Pieces:");
while(array_of_blacks[L_A_C]!='\0')
{printf(" %c",array_of_blacks[L_A_C]);
L_A_C++;

}
L_A_C=0;
printf("\nWhite Lost Pieces:");
while(array_of_whites[L_A_C]!='\0')
{printf(" %c",array_of_whites[L_A_C]);
L_A_C++;

}

    return 0;
}



int main()
{ int counterofturns=0;
   for(counterofturns=0;counterofturns<200;counterofturns++)
  {Turn();
  printf("\n");
  check();
  input();
  system("cls");
  }

  return 0;

}
