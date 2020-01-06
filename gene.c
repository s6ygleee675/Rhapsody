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

int * gene_count(int i, int j, char arr[]);
// arr[] sequency information from ith to jth position, Y is array which contain the maximum continued sequence number of A, T, G, C.
//For example, it there is a code AAATCGGGC, Y[0]=3, Y[1]=1, Y[2]=3, Y[3]=1

float * func(FILE * out, int j, int linecount, int data_size, int string_size, int error, float frequency, char input[], char data[], int Y1[4], int Y2[4]);
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
	int i, j, n, l, t;

	int linecount=0;
	int Y1[4]={0};
	int Y2[4]={0};
	int * Y;
	
	double total_time;
	clock_t start, end;
	float *r;

	char strTemp[100]={0};
	char *pStr;
	char arr[100][100]={{0}};

	char strTemp2[100]={0};
	char *pStr2;
	char arr2[100]={0};


	char strTemp3[100]={0};
	char *pStr3;
	char arr3[100][100]={{0}};

	char strTemp4[100]={0};
	char *pStr4;
	char arr4[100][100]={{0}};

	char strTemp5[100]={0};
	char *pStr5;
	char arr5[100][100]={{0}};


	char filename[100];
	char input[100]={0};
	float frequency=0;

	float pos0=0, err=0;
	float tmprr[4][100][2]={{{-1}}};

	//initializing
	for(n=0; n<=3; n++)
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
//	ifs = fopen("7496_part1.fastq","r");	
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
	if(cls1 != NULL)
	{
		i=0;
		while(!feof(cls1))
		{
			pStr = fgets( strTemp3, sizeof(strTemp3), cls1);

			for(j = 0; j < 100; j++)
			{
				if(strTemp3[j]!=0)
				{
					arr3[i][j]=strTemp3[j];
				}
				if(strTemp3[j]==0)
				{break;}
			}
			i+=1;
		}
	}
	else
	{
	   fprintf(stderr, "Error opening 'file.txt'; Bailing out!");
	}




//cls2
	if(cls2 != NULL)
	{
		i=0;
		while(!feof(cls2))
		{
			pStr = fgets( strTemp4, sizeof(strTemp4), cls2);

			for(j = 0; j < 100; j++)
			{
				if(strTemp4[j]!=0)
				{
					arr4[i][j]=strTemp4[j];
				}
				if(strTemp4[j]==0)
				{break;}
			}
			i+=1;
		}
	}
	else
	{
	   fprintf(stderr, "Error opening 'file.txt'; Bailing out!");
	}




//cls3
	if(cls3 != NULL)
	{
		i=0;
		while(!feof(cls3))
		{
			pStr = fgets( strTemp5, sizeof(strTemp5), cls3);

			for(j = 0; j < 100; j++)
			{
				if(strTemp5[j]!=0)
				{
					arr5[i][j]=strTemp5[j];
				}
				if(strTemp5[j]==0)
				{break;}
			}
			i+=1;
		}
	}
	else
	{
	   fprintf(stderr, "Error opening 'file.txt'; Bailing out!");
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
			
				for(n=0; n<=3; n++)
				{
					if(n!=3){
					printf("#########################    CLS%d    ##########################\n",n+1);
					sprintf(filename,"plot_CLS%d_position.txt",n+1);
					out=fopen(filename,"w");
					fprintf(out,"#	#	#\n");
					}
		
					else{
					printf("#########################   SEARCH   ##########################\n");
					out=fopen("plot_list_position.txt","w");
					fprintf(out,"#	#	#\n");
					}
	
					for(j=0; j<100; j++)
					{
						error=0;
						frequency=0;
						while(frequency==0 && error<=2){
			
						if(n==0){
							if(arr3[j][0]==0){break;}
							else{for(i = 0; i < 100; i++){input[i]=0;}}

							for(i = 0; i < 100; i++)
							{if(arr3[j][i]!=0){input[i]=arr3[j][i];}
							if(arr3[j][i]==0){break;}}
							}
						if(n==1){
							if(arr4[j][0]==0){break;}
							else{for(i = 0; i < 100; i++){input[i]=0;}}

							for(i = 0; i < 100; i++)
							{if(arr4[j][i]!=0){input[i]=arr4[j][i];}
							if(arr4[j][i]==0){break;}}
							}
						if(n==2){
							if(arr5[j][0]==0){break;}
							else{for(i = 0; i < 100; i++){input[i]=0;}}

							for(i = 0; i < 100; i++)
							{if(arr5[j][i]!=0){input[i]=arr5[j][i];}
							if(arr5[j][i]==0){break;}}
							}
						if(n==3){
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
							Y = gene_count(0, string_size-1, input);

							for(l = 0; l < 4; l++)
							{
								Y1[l]=*(Y+l);
							}


							//printf("\nTHIS IS INPUT\n");
							//for(l = 0; l < 100; l++){printf("%c", input[l]);}
							//printf(" \nstring_size %d", string_size-1);


							//printf("\nTHIS IS DATA\n");		
							//for(l = 0; l < 100; l++)
							//{
							//	if(arr2[l]=='E'){break;}
							//	else{printf("%c", arr2[l]);}
							//}

					//main code
					r=func(out, j, linecount, data_size[0]-1, string_size, error, frequency, input, arr2, Y1, Y2);
								
					frequency=*r;
					pos0=	  *(r+1);
					err=	  *(r+2);
					fprintf(out, "%d	%.3f	%.3f\n", j+1, pos0, err);
							
					
								tmprr[n][j][0]=tmprr[n][j][0]+frequency;
								tmprr[n][j][1]=error-1;
												
							if(frequency==0){error++;}
						}//while_loop
					}//for_j100_loop
				fclose(out);
				}//for_n_loop
			}//linecount_modular
		}//data_line_reading
	}//file_open
	
	else{fprintf(stderr, "Error opening 'file.txt'; Bailing out!");}

	end = clock();
	total_time = ((double) (end - start)) / CLOCKS_PER_SEC;

	//txt out file
	for(n=0; n<=3; n++)
	{
		if(n!=3){
		sprintf(filename,"plot_CLS%d.txt",n+1);
		out=fopen(filename,"w");
		fprintf(out,"#	#	#\n");

		for(j=0; j<100; j++)
		{
			if(tmprr[n][j][0]!=-1)
			{
				fprintf(out,"%d	%f	%f\n",j+1, tmprr[n][j][0], tmprr[n][j][1]);
				//printf("%d\n", tmprr[n][j][0]);
			}
		}
		fclose(out);
		}

		else{
		out=fopen("plot_list.txt","w");
		fprintf(out,"#	#	#\n");
		for(j=0; j<100; j++)
		{
			if(tmprr[n][j][0]!=-1){
				fprintf(out,"%d	%f	%f\n",j+1, tmprr[n][j][0], tmprr[n][j][1]);
				//printf("%d\n", tmprr[n][j][0]);
			}
		}
		fclose(out);
		}
	}


//print result
	printf("Time taken to analyze : %f \n", total_time);
	
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
	system("read -p 'Press Enter to continue...' var");
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





int * gene_count(int i, int j, char arr[])
{
	int a=0, t=0, g=0, c=0, k;
	static int Y[4];

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
			if(arr[k]=='A' && 1>Y[0])	Y[0]=1;
			if(arr[k]=='T' && 1>Y[1])	Y[1]=1;
			if(arr[k]=='G' && 1>Y[2]) 	Y[2]=1;
			if(arr[k]=='C' && 1>Y[3])	Y[3]=1;

		}
	}
return Y;
}





float * func(FILE * out, int j, int linecount, int data_size, int string_size, int error, float frequency, char input[], char data[], int Y1[4], int Y2[4])
{
	// 'error' is number of error you expect in input string
	// char data[] is the originial data you want to use
	// input string is the string you want to find
	// Y1 & Y2 save the gene count data
	// int data_size: size of the data
	// int b : input string length
	static float r[3];
	static int * Y;
	int t, x, count, pos, l;
	int p, n, ntmp;
	float a1, pos0, err; 
	int q1, q2;
	static float freq;
	
	freq=frequency;
	count=0; pos=0;
	for(t = 0; t < data_size-string_size; t++)
	{
		if(data[t]=='\n')
		{
			count++;
			pos=t;
		}
		p=0; n=0; ntmp=0;
		Y = gene_count(t, t+string_size-1, data);
		for(l = 0; l < 4; l++)
		{
			Y2[l]=*(Y+l);
		}

		for(x = 0; x < 4; x++)
		{
			p+=abs(Y1[x]-Y2[x]);
			Y2[x]=0;
		}
		
		if(p<=error)
		{
			for(x = 0; x < string_size; x++)
			{
				if(input[x]==data[t+x])
					ntmp++;
			}
			if((string_size-ntmp)<=error)
			{
				printf("HERE IS THE POSITION : Line%4d, %2d to %2d, Error: %d\n", linecount, t-pos+1, t-pos+string_size, error-1);
				freq++;

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
	r[0]=freq;
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
