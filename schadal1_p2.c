
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
FILE *input_file;
FILE *output_file;
int n,m,sizeC,flag=0,mflag=1,nflag=0;
double timediff(struct timeval x , struct timeval y);
struct timeval before , after;
//Caalling time difference function to calculate accurate milli seconds
double timediff(struct timeval x , struct timeval y)
{
    double x_ms , y_ms , diff;
     
    x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
    y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;
     
    diff = (double)y_ms - (double)x_ms;
    diff = diff / 1000;
    return diff;
}
//Calling exit function to terminate the program
void exit1()
{
	gettimeofday(&after,NULL);
//Printing the run time
	fprintf(output_file,"\nThe Run time is %.01f milli seconds\n",timediff(before,after));

	fclose(input_file);
        fclose(output_file);
	exit(0);
}

void dfscompute(int depth,int x[],int y[])
{	
	int i,j,temp[n],t1,t2,k=n;
	if (depth==n)
	{
	/*To check all clauses are satisfied with current assignment of variables*/
//Flow of logic
		rewind(input_file);
		fscanf(input_file,"%d",&n);
		fscanf(input_file,"%d",&m);
		fscanf(input_file,"%d",&sizeC);
		mflag =1;
                for(j=0;j<m;j++)
                {
			if(mflag!=0)
			{
				flag =0;
                		for(i=0;i<sizeC;i++)
                        	{
                        		fscanf(input_file,"%d",&y[i]);
                               		if(y[i]<0)
                                	{
                                		t1 = -1*y[i];
                                		if(x[t1-1]==1)
                                		{
                                			t1=0;
                                		}
                                		else
                                		{
                                			t1=1;
                                		}
                                		flag = flag | t1;
                        		}
                                	else
                                	{
                                		t1 = y[i];
                                		flag = flag | x[t1-1];
                                	}
                        	}
				if(flag == 0)
				{
					return;
				}
			}
			mflag = mflag & flag;
			if(mflag==0)
			{
				return;
			}
		}
                if(mflag!=0)
                {
                //Write to file the appropriate output
			if(n<=5)
			{

			fprintf(output_file,"Sollution is: \n");
				while(k>0)
				{
					fprintf(output_file," x[%d] = %d\n",depth-k+1,x[depth-k]);
					k--;
				}
			}
			else if(n>5 && m<=30 && nflag == 0)
			{
				fprintf(output_file,"Sollution is: \n");
				while(k>0)
				{
					fprintf(output_file," x[%d] = %d\n",depth-k+1,x[depth-k]);
					k--;
				}
				fprintf(output_file,"There is a satisfying assignment \n");

				exit1();
			}
			else if(n>5 && m>30)
			{
				fprintf(output_file,"There is a satisfying assignment \n");
				exit1();

			}
			nflag =1;
                }		
       		return;
	}//end if depth ==n
	x[depth]=1;
	dfscompute(depth+1,x,y);
	x[depth]=0;
	dfscompute(depth +1,x,y);
}//end dfsCompute
int main(int argc,char *argv[])
{
//Taking input file from command line argument 
	input_file = fopen(argv[1],"r");
        output_file = fopen(argv[2],"w");
	if(!input_file)
	{
		fprintf(output_file,"\n Error while proccesing input file\n Please give input file.txt\n");
		return 0;
	}
	fscanf(input_file,"%d",&n);
	int x[n],y[n];
	fscanf(input_file,"%d",&m);
	fscanf(input_file,"%d",&sizeC);
	gettimeofday(&before,NULL);
	if(n==0)
	{
		fprintf(output_file,"\nEMPTY INPUT FILE ERROR\n");
		exit1();
	}
//calling Recursive dfs function
	dfscompute(0,x,y);
	gettimeofday(&after,NULL);
	if(mflag== 0 && nflag == 0)
	{
		fprintf(output_file,"\nNo satisfying assignment\n");
	}
//Printing the run time
	fprintf(output_file,"\nThe Run time is %.01f milli seconds\n",timediff(before,after));
	fclose(input_file);
        fclose(output_file);

	return 0;

}

