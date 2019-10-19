/*
Updated : October 18th
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

float * func(FILE * out, int j, int linecount, int data_size, int string_size, int error, int frequency, char input[], char data[], int Y1[4], int Y2[4]);
//main fuction, find the position of the input array on the char data[]

float change2decimal(float X);


int main(void){
//variables	
	FILE * ifs;
	FILE * cls1;
	FILE * cls2;
	FILE * cls3;
	FILE * list;
	FILE * out;


	int data_size[4]={0}, string_size=0, error=0;
	int i, j, n, l, t, x;

	int linecount=0;
	int k=9;
	int Y1[4]={0};
	int Y2[4]={0};
	
//	double cycle=0;
	double total_time;
	clock_t start, end;
//	char data[500000]={0};
	
	//p,p1, q,q1, w,w1, r are also data saving variables
	char p[50000]={0};
	char p1[100][9] = {{0}};
	char q[50000]={0};
	char q1[100][9] = {{0}};
	char w[50000]={0};
	char w1[100][9] = {{0}};
	char strTemp[100]={0};
	char *pStr;
	char arr[100][100]={{0}};

	char strTemp2[100]={0};
	char *pStr2;
	char arr2[100]={0};

	char tmp[3][100][9]={{{0}}};
	char filename[100];
	char input[100]={0};
	char *buffer;
	char *buffer1;
	char *buffer2;
	char *buffer3;
	int size, count;
	int frequency=0;

	float pos0=0, err=0;
	int tmprr[3][100][2]={{{-1}}};
	int tmprr2[100][2]={{-1}};

	//initializing
	for(j=0; j<100; j++)
	{
		for(i=0; i<2; i++)
		{
			tmprr2[j][i]=-1;
		}
	}

	for(n=0; n<3; n++)
	{
		for(j=0; j<100; j++)
		{
			for(i=0; i<2; i++)
			{
				tmprr[n][j][i]=-1;
			}
		}
	}
	
//open file
	ifs = fopen("1000_from_middle.fastq","r");	
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
	if(list != NULL)
	{
		i=0;
		while(!feof(list))
		{
			pStr = fgets( strTemp, sizeof(strTemp), list);

			for(j = 0; j < 100; j++)
			{
				if(strTemp[j]!=0)
				{
					arr[i][j]=strTemp[j];
				}
				if(strTemp[j]==0)
				{break;}
			}
			i+=1;
		}
	}
	else
	{
	   fprintf(stderr, "Error opening 'file.txt'; Bailing out!");
	}


//copy data to tmp
	for(n=0; n<3; n++)
	{
		for(j=0; j<100; j++)
		{
			for(i = 0; i < k; i++)
			{
				if (n==0){tmp[n][j][i]=p1[j][i];}
				if (n==1){tmp[n][j][i]=q1[j][i];}
				if (n==2){tmp[n][j][i]=w1[j][i];}

			}
		}
	}
	

//time calculate
	start = clock(); 
	srand(time(NULL));

	linecount=0;
	for(l = 0; l < 100; l++)
	{
		arr2[l]='E';
	}

	if(ifs != NULL)
	{
		while(!feof(ifs))
		{
			linecount++;
			pStr2 = fgets( strTemp2, sizeof(strTemp2), ifs);
			data_size[0]=sizeof(strTemp2);
			if(linecount%4==2)
			{
				for(l = 0; l < 100; l++)
				{
					if(strTemp2[l]!=0)
					{
						arr2[l]=strTemp2[l];
					}
					if(strTemp2[l]==0)
					{break;}
				}
			
				for(l = 0; l < 100; l++)
				{
					if(arr2[l]=='E'){break;}
					else{printf("%c", arr2[l]);}
				}

				for(n=0; n<=3; n++)
				{
					if(n!=3){
					printf("#########################    CLS%d    ##########################\n",n+1);
					sprintf(filename,"plot_CLS%d_position.txt",n+1);
					out=fopen(filename,"w");
					fprintf(out,"#	#	#\n");
					}
		
					else{
					printf("#########################   SEARCH   #########################\n");
					out=fopen("plot_list_position.txt","w");
					fprintf(out,"#	#	#\n");
					}
	
					for(j=0; j<100; j++)
					{
						error=0;
						frequency=0;
						if(n!=3){if(tmp[n][j][0]==0){break;}}
						while(frequency==0){
							if(n!=3)
							{for(i = 0; i < k; i++){input[i]=tmp[n][j][i];}
							}
			
							else
							{
								if(arr[j][0]==0){break;}
								else{for(i = 0; i < 100; i++){input[i]=0;}}

								for(i = 0; i < 100; i++)
								{if(arr[j][i]!=0){input[i]=arr[j][i];}
								if(arr[j][i]==0){break;}}
							}

							//calculate input array length
							string_size=length(input);
							//printf("length of p : %d \n", string_size);
	
							//get sequence data of input array
							gene_count(0, string_size-1, input, Y1);

							//main code			
							frequency=func(out, j, linecount, data_size[0], string_size, error, frequency, input, arr2, Y1, Y2)[0];
							pos0=	func(out, j, linecount, data_size[0], string_size, error, frequency, input, arr2, Y1, Y2)[1];
							err=	func(out, j, linecount, data_size[0], string_size, error, frequency, input, arr2, Y1, Y2)[2];
							fprintf(out, "%d	%.3f	%.3f\n", j+1, pos0, err);
							
							if(n!=3){
								tmprr[n][j][0]=frequency;
								tmprr[n][j][1]=error;
							}
							else{	
								tmprr2[j][0]=frequency;
								tmprr2[j][1]=error;
							}
							
							if(frequency==0){error++;}
						}//while_loop
					}//for_j100_loop
				fclose(out);
				}//for_loop
			}//linecount_modular
		}//data_line_reading
	}//file_open
	
	else{fprintf(stderr, "Error opening 'file.txt'; Bailing out!");}

	end = clock();
	total_time = ((double) (end - start)) / CLOCKS_PER_SEC;

	//txt out file
	for(n=0; n<3; n++)
	{
		sprintf(filename,"plot_CLS%d.txt",n+1);
		out=fopen(filename,"w");
		fprintf(out,"#	#	#\n");

		for(j=0; j<100; j++)
		{
			if(tmprr[n][j][0]!=-1)
			{
				fprintf(out,"%d	%d	%d\n",j+1, tmprr[n][j][0], tmprr[n][j][1]);
				//printf("%d\n", tmprr[n][j][0]);
			}
		}
		fclose(out);
	}

	out=fopen("plot_list.txt","w");
	fprintf(out,"#	#	#\n");
	for(j=0; j<100; j++)
	{
		if(tmprr2[j][0]!=-1){
			fprintf(out,"%d	%d	%d\n",j+1, tmprr2[j][0], tmprr2[j][1]);
			//printf("%d\n", tmprr[n][j][0]);
		}
	}
	fclose(out);

//print result
	printf("Time taken to analyze : %f \n", total_time);
	

// closing
    for(t = 0; t < 50000; t++)
    {
	    //data[t]=0;
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
//	free(buffer);
	free(buffer1);
	free(buffer2);
	free(buffer3);  

	system("read -p 'Press Enter to continue...' var");
//	system("pause");
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
			if(arr[k]=='G' && 1>Y[2]) 	    Y[2]=1;
			if(arr[k]=='C' && 1>Y[3])		Y[3]=1;

		}
	}
}





float * func(FILE * out, int j, int linecount, int data_size, int string_size, int error, int frequency, char input[], char data[], int Y1[4], int Y2[4])
{
	// 'error' is number of error you expect in input string
	// char data[] is the originial data you want to use
	// input string is the string you want to find
	// Y1 & Y2 save the gene count data
	// int data_size: size of the data
	// int b : input string length
	static float r[3];
	int t, x, count, pos;
	int p,n;
	float a1, pos0, err; 
	int q1, q2;

	

	count=0; pos=0;
	for(t = 0; t < data_size; t++)
	{
		if(data[t]=='\n')
		{
			count++;
			pos=t;
		}
		p=0; n=0;
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
				printf("HERE IS THE POSITION : Line%4d, %2d to %2d, Error: %d\n", linecount, t-pos+1, t-pos+string_size, error);
				frequency++;

				pos0=0; q1=0; q2=0; a1=0;
				q1=t-pos+1;
				q2=t-pos+string_size;
				a1=((float)(q1+q2)/200);
				pos0=linecount+a1;
				err=((float)(q2-q1)/200);

				r[1]=pos0;
				r[2]=err;
			}
		}
	}
	r[0]=frequency;
	return r;
}


float change2decimal(float X)
{
	float Y, k, x;
	x=0;
	k=1;
	Y=X;
	while(Y>0)
	{
		k=10*k;
		Y=X-k;
	}
	x=X/k;
	return x;
}
