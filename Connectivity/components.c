#include <stdlib.h>
#include <stdio.h>

#define END -1      // end of massive

// connectivity matrix
int graf[100][100];
// reachable vertexes matrix
int a[100][100];

// function for copying prototype 
void cpy(int*, int*);
// algorithm of Dijkstra function prototypa
void dijkstra(int, int);
//  array string comparison function prototype 
int compar(int*, int*);

int main(void){
	int i, j; 
    int size; // vertexs number
    int last, cur;
    int count = 0; // connectivity components number      
	FILE *fin;   // input file
    int comp[100][100]; // connectivity components array
    /* input */
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
    	for (j = 0; j < size; j++)
        	if ( ( fscanf(fin, "%d", &graf[i][j]) != 1 ) || ( graf[i][j] < 0 ) )
            {
            	printf("Input incorrect data. Press anykey to exit...");
                getchar();
                return 0;
            }
    fclose(fin); 
    for (i = 0; i < 100; i++){
    	for (j = 0; j < 100; j++){
    		a[i][j] = comp[i][j] = END;
    	}
    }
    /* connectivity matrix output */
    printf("   ");
    for (i = 0; i < size; i++) 
    	printf("| X%-2d", i + 1);
    printf("\n");
    for (i = 0; i < size; i++)
    {
    	printf("X%-2d", i+1);
        for (j = 0; j < size; j++)
        {
            printf("|%3d ", graf[i][j]);
        }
        printf("\n");
    }
    /*
    printf("OLD\n");
    printf("   ");
    for (i = 0; i < size; i++) 
    	printf("| X%-2d", i+1);
    printf("\n");
    for (i = 0; i < size; i++)
    {
    	printf("X%-2d", i+1);
    	dijkstra(i, size);
        for (j = 0; j < size; j++)
        {
            printf("|%3d ", a[i][j]);
        }
        printf("\n");
    }*/
	for (i = 0; i < size; i++){
		dijkstra(i, size);
	}
    for (i = 0; i < size; i++){
    	for (j = 0; j < size; j++){
    		if (a[i][j] != a[j][i]){
    			a[i][j] = 0;
    			a[j][i] = 0;
    		}
    	}
    }
    /*
    printf("NEW\n");
    printf("   ");
    for (i = 0; i < size; i++) 
    	printf("| X%-2d", i+1);
    printf("\n");
    for (i = 0; i < size; i++)
    {
    	printf("X%-2d", i+1);
        for (j = 0; j < size; j++)
        {
            printf("|%3d ", a[i][j]);
        }
        printf("\n");
    }
    */
    /* duplicate deleting */
    for (i = 0; i < size; i++){
    	if (count == 0){
    		for (j = 0; j < size; j++){
    			comp[count][j] = a[i][j];	
    		}
    		count++;
    	}
    	else{
    		int flag = 1;
    		for (j = 0; j < count; j++){
    			if ( compar(a[i], comp[j]) ){
    				flag = 0;
    				break;
    			}
    		}
    		if ( flag ){
    			cpy(a[i], comp[count]);
    			count++;
    		}
    	}
    }
    /* connectivity components output */
    for (i = 0; i < count; i++){
    	printf("%d*: ", i + 1);
    	j = 0;
    	while (comp[i][j++] != END ){
    		//printf("%d ", comp[i][j++]);
    	}
    	//printf("\n");
    	j = 0;
    	while (!comp[i][j++]) ;
    	printf("(%d", j);
    	j--;
    	last = j;
    	do{
    		cur = 0;
    		while ( !( (graf[last][cur]) && (comp[i][cur]) && (cur != last) ) && ( ++cur != size ) ) ;
    		last = cur;
    		if ( (last != j) && (last != size) ){
    			printf(", %d", last + 1);
    		}
    	}while ( (cur != j) && ( cur != size ) );
    	if (cur != size){
    		printf(", %d)\n", j + 1);
    	}
    	else{
    		printf(")\n");
    	} 
    }

	return 0;
}

void cpy(int *source, int *destination)
{
     while ( ( *destination++ = *source++ ) != END) ;
}

int compar(int *vec1, int *vec2)
{
    while ( ( *vec2 != END ) && ( *vec1 != END) && ( *vec1++ == *vec2++ ) ) ;       
    if (*vec1 == *vec2){
    	return 1;
    }
    else{
    	return 0;
    }
}

void dijkstra(int st, int SIZE)
{
  	int d[100]; // минимальное расстояние
  	int v[100]; // посещенные вершины
  	int temp;
  	int minindex, min;
  	//Инициализация вершин и расстояний
  	for (int i = 0; i<SIZE; i++) 
  	{
    	d[i] = 10000;
    	v[i] = 1;
  	}
  	d[st] = 0;
  	// Шаг алгоритма
  	do {
    	minindex = 10000;
    	min = 10000;
    	for (int i = 0; i<SIZE; i++) 
    	{ // Если вершину ещё не обошли и вес меньше min
	      if ((v[i] == 1) && (d[i]<min)) 
	      { // Переприсваиваем значения
	        min = d[i];
	        minindex = i;
	      }
	    }
	    // Добавляем найденный минимальный вес
	    // к текущему весу вершины
	    // и сравниваем с текущим минимальным весом вершины
	    if (minindex != 10000) 
	    {
	      for (int i = 0; i<SIZE; i++) 
	      {
	        if (graf[minindex][i] > 0)
	        {
	          temp = min + graf[minindex][i];
	          if (temp < d[i])
	            d[i] = temp;
	        }
	      }
	      v[minindex] = 0;
	    }
  	} while (minindex < 10000);
  // Вывод матрицы связей
  for (int i = 0; i < SIZE; i++)
  {
  		//printf("%d: %5d \n", i+1, d[i]);
		if (d[i] == 10000){
  			a[st][i] = 0;
  		}
  		else{
  			a[st][i] = 1;
  		}
  }  
}