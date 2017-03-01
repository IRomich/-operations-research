#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>

struct vertex{
	int parent;
	int tier;
};

float graf[100][100]; 

int main()
{
      int i, j; 
      int size;        
      int first;      
      int second;      
      FILE *fin;   // Input file
      float temp[100][100];
      fin = fopen ("in.txt", "r");   
      if ( fin == NULL ) 
      {
           printf("File not found. Press anykey to exit...");
           getchar();
           return 0;
      } 
      if ( ( fscanf(fin, "%d", &size) != 1 ) || ( size <= 0 ) )
              {
                   printf("Input incorrect data. Press anykey to exit...");
                   getchar();
                   return 0;
              } 
      for (i = 0; i < size; i++)
          for (j = i + 1; j < size; j++)
              if ( ( fscanf(fin, "%f", &graf[i][j]) != 1 ) || ( graf[i][j] < 0 ) )
              {
                   printf("Input incorrect data. Press anykey to exit...");
                   getchar();
                   return 0;
              }
      fclose(fin); 
      printf("   ");
      for (i = 0; i < size; i++) 
          printf("| X%-2d", i+1);
      printf("\n");
      for (i = 0; i < size; i++)
      {
          printf("X%-2d", i+1);
          for (j = 0; j < size; j++)
          {
              graf[j][i] = graf[i][j];
              temp[i][j] = temp[j][i] = graf[i][j];
              printf("|%4.1f", graf[i][j]);
          }
          printf("\n\n");
      }
      int count = size * size;
      int t;
      while (count != size){
      	count = size * size;
      	for (i = 0; i < size; i++){
      		for (j = i + 1; j < size; j++)
      		if (temp[i][j] != 0){
      			count -= 2;
      		}
      		else{
      			for (t = 0; t < size; t++){
      				if ( ( temp[i][t] !=0 ) && ( temp[t][j] != 0 ) ){
      					temp[i][j] = temp[j][i] = temp[i][t] + temp[t][j];
      				}
      			}
      		}
      		
      	}
      }   
      printf("   ");
      for (i = 0; i < size; i++) 
          printf("| X%-2d", i+1);
      printf("\n");
      int sum = 0;
      int root = 0;
      t = 1000;
      for (i = 0; i < size; i++)
      {
      	  sum = 0;
          printf("X%-2d", i+1);
          for (j = 0; j < size; j++)
          {
          	  sum += temp[i][j];
              printf("|%4.1f", temp[i][j]);
          }
          if (sum < t){
          	root = i;
          	t = sum;
          }
          printf("\n\n");
      }
      printf("Root is: %d\n", root + 1);  
      printf("Input first vertex: ");
      scanf("%d", &first);
      if ( ( first < 1) || ( first > size ) )
      {
           printf("Input incorrect first vertex. Press any key to exit...");
           getchar();
           return 0;
      }
      first--;
      printf("Input second vertex: ");
      scanf("%d", &second);
      if ( ( second < 1) || ( second > size ) )
      {
           printf("Input incorrect second vertex. Press any key to exit...");
           getchar();
           return 0;
      }
      second--;
      count = 0;
      struct vertex vertexs[size];
      vertexs[root].parent = -1;
      vertexs[root].tier = 0;
      while (count != size){
      	count = 0;
      	for (i = 0; i < size; i++){
      		sum = 0;
      		for (j = 0; j < size;j++){
      			sum += graf[i][j];
      			if (graf[i][j] != 0){
      				t = j;
      			} 
      		}
      		if (sum != 0){
      			if (sum == 1){
      				vertexs[i].parent = t;
      				graf[i][t] = graf[t][i] = 0;
      			}
      		}
      		else{
      			count++;
      		}
      	}
      }
      for (i = 0; i < size; i++){
      	t = i;
      	count = 0;
      	while (t != root){
      		count++;
      		t = vertexs[t].parent;
      	}
      	vertexs[i].tier = count;
      }
      int temp1 = 0;
      int temp2 = 0;
      int path1[size], path2[size];
      path1[temp1] = first;
      path2[temp2] = second;
      int t1 = vertexs[first].tier;
      int t2 = vertexs[second].tier;
      while ( path2[temp2] != path1[temp1] ){
      	if (t1 > t2){
      		temp1++;
      		path1[temp1] = vertexs[path1[temp1 - 1]].parent; 
      		t1--;
      	}
      	else{
      		temp2++;
      		path2[temp2] = vertexs[path2[temp2 - 1]].parent;
      		t2--;
      	}
      }
      for (i = temp2 - 1; i >= 0; i--){
      	temp1++;
      	path1[temp1] = path2[i];
      }
      printf("Path:");
      for (i = 0; i < temp1 + temp2; i++)
      {
      	printf("%d ", path1[i] + 1);
      }
      printf("\n");
      return 0;
}