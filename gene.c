/*
Updated : August 5th
Author : Youngik Lee
code : Visual studio, C, finding the particular pattern in gene codes
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

//function declaration

int length(char arr[]);
// length calculation othe arr[]

void gene_count(int i, int j, char arr[], int Y[4]);
// arr[] sequency information from ith to jth position, Y is array which contain the maximum continued sequence number of A, T, G, C.
//For example, it there is a code AAATCGGGC, Y[0]=3, Y[1]=1, Y[2]=3, Y[3]=1

void func(int data_size, int string_size, int error, char input[], char data[], int Y1[4], int Y2[4]);
//main fuction, find the position of the input array on the char data[]

char** datacopy(int n, FILE* fp);


int main(void){
//variables	
	FILE * ifs;
	FILE * cls1;
	FILE * cls2;
	FILE * cls3;
	FILE * list;
	int data_size[4]={0}, string_size=0, error=0;
	int i, j, n, t, x;
	int k=9;
	int Y1[4]={0};
	int Y2[4]={0};
	double cycle=0;
	double total_time;
	clock_t start, end;
	char data[50000]={0};
	
	//p,p1, q,q1, w,w1, r are also data saving variables
	char p[50000]={0};
	char p1[100][9] = {{0}};
	char q[50000]={0};
	char q1[100][9] = {{0}};
	char w[50000]={0};
	char w1[100][9] = {{0}};
	char** r;

	char input[100]={0};
	char *buffer;
	char *buffer1;
	char *buffer2;
	char *buffer3;
	int size, count;


//open file
	ifs = fopen("short.fastq","r");
	if (ifs == NULL)
	{
		printf("Cannot open the file.\n");
		return 1;
	}

	cls1 = fopen("CLS1.txt","r");
	if (cls1 == NULL)
	{
		printf("Cannot open the file.\n");
		return 1;
	}

	cls2 = fopen("CLS2.txt","r");
	if (cls2 == NULL)
	{
		printf("Cannot open the file.\n");
		return 1;
	}

	cls3 = fopen("CLS3.txt","r");
	if (cls3 == NULL)
	{
		printf("Cannot open the file.\n");
		return 1;
	}

	list = fopen("list.txt","r");
	if (list == NULL)
	{
		printf("Cannot open the file.\n");
		return 1;
	}




//copy data from file, data copy
//data	
    	fseek(ifs, 0, SEEK_END);
    	size = ftell(ifs);         
    	buffer = malloc(size + 1);
		memset(buffer, 0, size + 1);  
    	fseek(ifs, 0, SEEK_SET);                
    	count = fread(buffer, size, 1, ifs);  
		data_size[0]=size;
		
		for(x = 0; x < data_size[0]; x++)
		{
			data[x]=buffer[x];
		}

//cls1
    	fseek(cls1, 0, SEEK_END);
    	size = ftell(cls1);         
    	buffer1 = malloc(size + 1);    
		memset(buffer1, 0, size + 1);  
    	fseek(cls1, 0, SEEK_SET);                
    	count = fread(buffer1, size, 1, cls1);  		
		data_size[1]=size;
		
		for(x = 0; x < data_size[1]; x++)
		{
			p[x]=buffer1[x];
		}
		
		for(j = 0; j < 100; j++)
		{
		
			for(i = 0; i < k; i++)
			{
			p1[j][i]=p[k*j+i];
			}
		}

//cls2
    	fseek(cls2, 0, SEEK_END);
    	size = ftell(cls2);         
    	buffer2 = malloc(size + 1);    
		memset(buffer2, 0, size + 1);  
    	fseek(cls2, 0, SEEK_SET);                
    	count = fread(buffer2, size, 1, cls2);  
		data_size[2]=size;
		
		for(x = 0; x < data_size[2]; x++)
		{
			q[x]=buffer2[x];
		}
		
		for(j = 0; j < 100; j++)
		{
		for(i = 0; i < k; i++)
			{
			q1[j][i]=q[k*j+i];
			}
		}

//cls3
    	fseek(cls3, 0, SEEK_END);
    	size = ftell(cls3);         
    	buffer3 = malloc(size + 1);    
		memset(buffer3, 0, size + 1);  
    	fseek(cls3, 0, SEEK_SET);                
    	count = fread(buffer3, size, 1, cls3);
		data_size[3]=size;
		
		for(x = 0; x < data_size[3]; x++)
		{
			w[x]=buffer3[x];
		}
		
		for(j = 0; j < 100; j++)
		{
			for(i = 0; i < k; i++)
			{
			w1[j][i]=w[k*j+i];
			}
		}

//list
	n=50;
	//r=datacopy(n, list);

	
//input data
 printf("Which pattern you want to find? : ");
 scanf("%s", input);
	printf("How many errors you expect in your pattern? : ");
	scanf("%d", &error);


//calculate input array length
//	for(i = 0; i < k; i++)
//	{
//		input[i]=p1[0][i];
//	}

	string_size=length(input);
	printf("length of p : %d \n", string_size);

//get sequence data of input array
	gene_count(0, string_size-1, input, Y1);

//time calculate
	start = clock(); 
	srand(time(NULL));

//main code
	func(data_size[0], string_size, error, input, data, Y1, Y2);
	end = clock();
	total_time = ((double) (end - start)) / CLK_TCK;

//print result
// printf("Complexity(executed algorithm/size of data) : %.0f/%d \n", cycle, a);
	printf("Time taken to analyze : %f \n", total_time);


// closing
    for(t = 0; t < 50000; t++)
    {
	    data[t]=0;
	    p[t]=0;
	    q[t]=0;
	    w[t]=0;
    }

	for(t = 0; t < 4; t++)
    {
		Y1[t]=0;
		Y2[t]=0;
    }

	fclose(ifs);   
	fclose(cls1);   
	fclose(cls2);   
	fclose(cls3); 
	fclose(list); 
	free(buffer);
        free(buffer1);
        free(buffer2);
        free(buffer3);  
	system("pause");
    return 0;
}




/*================================================================================*/
int length(char arr[])
{
	int t, length=0;
	for(t = 0; t < 100; t++)
    {
	    if(arr[t]==0)
			{length = t;
		break;}
    }
	return length;
}



void gene_count(int i, int j, char arr[], int Y[4])
{
	int a=0, t=0, g=0, c=0, k;
	for(k = 0; k < 4; k++)
    {
		Y[t]=0;
    }
	for(k = i; k < j; k++)
	{
		if(arr[k]==arr[k+1])
		{
			if(arr[k]=='A')
			{a++;
			if(a>Y[0])
				Y[0]=a;
			}

			if(arr[k]=='T')
			{t++;
			if(t>Y[1])
				Y[1]=t;
			}

			if(arr[k]=='G')
			{g++;
			if(g>Y[2])
				Y[2]=g;
			}

			if(arr[k]=='C')
			{c++;
			if(c>Y[3])
				Y[3]=c;
			}

		}

		else
		{
			a=1; t=1; g=1; c=1;
			if(arr[k]=='A' && 1>Y[0])		Y[0]=1;
			if(arr[k]=='T' && 1>Y[1])		Y[1]=1;
			if(arr[k]=='G' && 1>Y[2]) 	        Y[2]=1;
			if(arr[k]=='C' && 1>Y[3])		Y[3]=1;

		}
	}
}





void func(int data_size, int string_size, int error, char input[], char data[], int Y1[4], int Y2[4])
{
	//'error' is number of error you expect in input string
	//char data[] is the originial data you want to use
	//input string is the string you want to find
	//Y1 & Y2 save the gene count data
	// int data_size: size of the data
	// int b : input string length
	
	int t, x;
	for(t = 0; t < data_size; t++)
	{
		int p=0; int n=0;
		gene_count(t, t+string_size-1, data, Y2);
		for(x = 0; x < 4; x++)
		{
			p+=abs(Y1[x]-Y2[x]);
			Y2[x]=0;
		}
		
		if(p<=error)
		{
			for(x = 0; x < string_size; x++)
			{
				if(input[x]!=data[t+x])
					n++;
			}
			if(n<=error)
			{
				printf("HERE IS THE POSITION : %d to %d \n", t+1, t+string_size);
				// break; 
				// Can be added when you want to one position in the data.
			}
		}
	}
}





/*================================================================================*/
char** datacopy(int n, FILE* fp)
{
	int i, j;
	int max = 1;
	int count=1;
	char** array;
	array = malloc(n * sizeof(*array)); /* Assuming `n` is the number of rows */

	if(!array) /* If `malloc` failed */
	{
	    fprintf(stderr, "Error allocating memory; Bailing out!");
	    exit(-1);
	}

	for(i = 0; i < n; i++)
	{
	    array[i] = malloc(count * sizeof(**array));
	    if(!array[i]) /* If `malloc` failed */
	    {
	        for(j = 0; j < i; j++) /* free previously allocated memory */
	        {
	            free(array[j]); 
	        }
	        free(array);
	        fprintf(stderr, "Error allocating memory; Bailing out!");
	        exit(-1);
	    }
	    count++;
	}

	if(!fp)
	{
	   for(i = 0; i < n; i++) /* free previously allocated memory */
	   {
	      free(array[i]); 
	   }
	   free(array);
	   fprintf(stderr, "Error opening 'file.txt'; Bailing out!");
	   exit(-1);
	}
	
	for(i = 0; i < n; i++)
	{
	    for(count = 0; count < max; count++)
	    {
	        fscanf(fp, "%s", &array[i][count]);
	    }
	    max++;
	}
	

	max = 1;
	for(i = 0; i < n; i++)
	{
	    for(count = 0; count < max; count++)
	    {
	        printf("array[%d][%d] = %s", i, count, array[i][count]);
	    }
	    max++;
	}

	return array;
}
