/*
Updated : January 21th
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

	//Y is array for record the number of the frequency of Nucleobase(A, T, G, C)
	int linecount=0;
	int Y1[4]={0};
	int Y2[4]={0};
	int * Y;
	
	double total_time;
	clock_t start, end;
	float *output_result;

	char strTemp[100]={0};
	char *pStr;
	char extract_data_line[100]={0};

	char list_Temp[100]={0};
	char *list_pointer;
	char list_data[100][100]={{0}};

	char cls1_Temp[100]={0};
	char *cls1_pointer;
	char cls1_data[100][100]={{0}};

	char cls2_Temp[100]={0};
	char *cls2_pointer;
	char cls2_data[100][100]={{0}};

	char cls3_Temp[100]={0};
	char *cls3_pointer;
	char cls3_data[100][100]={{0}};

	char filename[100];
	char input[100]={0};
	float frequency=0;

	float pos0=0, err=0;
	float output[4][100][2]={{{-1}}};

	//initializing
	for(n=0; n<=3; n++)
	{
		for(j=0; j<100; j++)
		{
			for(i=0; i<2; i++)
			{
				output[n][j][i]=-1;
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
			cls1_pointer = fgets( cls1_Temp, sizeof(cls1_Temp), cls1);

			for(j = 0; j < 100; j++)
			{
				if(cls1_Temp[j]!=0)
				{
					cls1_data[i][j]=cls1_Temp[j];
				}
				if(cls1_Temp[j]==0)
				{break;}
			}
			i+=1;
		}
	}
	else
	{
	   fprintf(stderr, "Error opening 'cls1.txt'; Bailing out!");
	}


//cls2
	if(cls2 != NULL)
	{
		i=0;
		while(!feof(cls2))
		{
			cls2_pointer = fgets( cls2_Temp, sizeof(cls2_Temp), cls2);

			for(j = 0; j < 100; j++)
			{
				if(cls2_Temp[j]!=0)
				{
					cls2_data[i][j]=cls2_Temp[j];
				}
				if(cls2_Temp[j]==0)
				{break;}
			}
			i+=1;
		}
	}
	else
	{
	   fprintf(stderr, "Error opening 'cls2.txt'; Bailing out!");
	}


//cls3
	if(cls3 != NULL)
	{
		i=0;
		while(!feof(cls3))
		{
			cls3_pointer = fgets( cls3_Temp, sizeof(cls3_Temp), cls3);

			for(j = 0; j < 100; j++)
			{
				if(cls3_Temp[j]!=0)
				{
					cls3_data[i][j]=cls3_Temp[j];
				}
				if(cls3_Temp[j]==0)
				{break;}
			}
			i+=1;
		}
	}
	else
	{
	   fprintf(stderr, "Error opening 'cls3.txt'; Bailing out!");
	}


//list (the base code list for the sequence which want to detect on the data)
	if(list != NULL)
	{
		i=0;
		while(!feof(list))
		{
			list_pointer = fgets( list_Temp, sizeof(list_Temp), list);

			for(j = 0; j < 100; j++)
			{
				if(list_Temp[j]!=0)
				{
					list_data[i][j]=list_Temp[j];
				}
				if(list_Temp[j]==0)
				{break;}
			}
			i+=1;
		}
	}
	else
	{
	   fprintf(stderr, "Error opening 'list.txt'; Bailing out!");
	}


//time calculate
	start = clock(); 
	srand(time(NULL));

	//initailizing
	linecount=0;
	for(l = 0; l < 100; l++)
	{
		extract_data_line[l]='E';
	}

	if(ifs != NULL)
	{
		while(!feof(ifs))
		{
			linecount++;
			pStr = fgets( strTemp, sizeof(strTemp), ifs);
			data_size[0]=sizeof(strTemp);
			if(linecount%4==2)
			{
				for(l = 0; l < 100; l++)
				{
					if(strTemp[l]!=0)
					{
						extract_data_line[l]=strTemp[l];
					}
					if(strTemp[l]==0)
					{break;}
				}
			
				for(n=0; n<=3; n++)
				{
					if(n!=3){
					printf("#########################    CLS%d    ##########################\n",n+1);
					sprintf(filename,"plot_CLS%d_position.txt",n+1);
					out=fopen(filename,"w");
					fprintf(out,"#	#position	#input_code_size\n");
					}
		
					else{
					printf("#########################   SEARCH   ##########################\n");
					out=fopen("plot_list_position.txt","w");
					fprintf(out,"#	#position	#input_code_size\n");
					}
	
					for(j=0; j<100; j++)
					{
						error=0;
						frequency=0;
						while(frequency==0 && error<=2){
			
						if(n==0){
							//initialization
							if(cls1_data[j][0]==0){break;}
							else{for(i = 0; i < 100; i++){input[i]=0;}}

							for(i = 0; i < 100; i++)
							{if(cls1_data[j][i]!=0){input[i]=cls1_data[j][i];}
							if(cls1_data[j][i]==0){break;}}
						}
						if(n==1){
							//initialization
							if(cls2_data[j][0]==0){break;}
							else{for(i = 0; i < 100; i++){input[i]=0;}}

							for(i = 0; i < 100; i++)
							{if(cls2_data[j][i]!=0){input[i]=cls2_data[j][i];}
							if(cls2_data[j][i]==0){break;}}
						}
						if(n==2){
							//initialization
							if(cls3_data[j][0]==0){break;}
							else{for(i = 0; i < 100; i++){input[i]=0;}}

							for(i = 0; i < 100; i++)
							{if(cls3_data[j][i]!=0){input[i]=cls3_data[j][i];}
							if(cls3_data[j][i]==0){break;}}
						}
						if(n==3){
							//initialization
							if(list_data[j][0]==0){break;}
							else{for(i = 0; i < 100; i++){input[i]=0;}}

							for(i = 0; i < 100; i++)
							{if(list_data[j][i]!=0){input[i]=list_data[j][i];}
							if(list_data[j][i]==0){break;}}
						}
	
						//calculate input array length
						string_size=length(input);
	
						//get sequence data of input array
						Y = gene_count(0, string_size-1, input);

						//data copy from pointer to array
						for(l = 0; l < 4; l++)
						{
							Y1[l]=*(Y+l);
						}

						//main code
						output_result=func(out, j, linecount, data_size[0]-1, string_size, error, frequency, input, extract_data_line, Y1, Y2);
						frequency=*output_result;
						pos0=	  *(output_result+1);
						err=	  *(output_result+2);
						fprintf(out, "%d	%.3f	%.3f\n", j+1, pos0, err);
											
						output[n][j][0]=output[n][j][0]+frequency;
						output[n][j][1]=error;
												
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
		fprintf(out,"#	#frequency	#error\n");

		for(j=0; j<100; j++)
		{
			if(output[n][j][0]!=-1)
			{
				fprintf(out,"%d	%f	%f\n",j+1, output[n][j][0], output[n][j][1]);
				//printf("%d\n", output[n][j][0]);
			}
		}
		fclose(out);
		}

		else{
		out=fopen("plot_list.txt","w");
		fprintf(out,"#	#frequency	#error\n");
		for(j=0; j<100; j++)
		{
			if(output[n][j][0]!=-1){
				fprintf(out,"%d	%f	%f\n",j+1, output[n][j][0], output[n][j][1]);
				//printf("%d\n", output[n][j][0]);
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




//function define
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
	static float output_result[3];
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
				printf("HERE IS THE POSITION : Line%4d, %2d to %2d, Error: %d\n", linecount, t-pos+1, t-pos+string_size, error);
				freq++;

				pos0=0; q1=0; q2=0; a1=0;
				q1=t-pos+1;
				q2=t-pos+string_size;
				a1=((float)(q1+q2)/200);
				pos0=linecount+a1;
				err=((float)(q2-q1)/200);

				output_result[1]=pos0;
				output_result[2]=err;
			}
		}
	}
	output_result[0]=freq;
	return output_result;
}
