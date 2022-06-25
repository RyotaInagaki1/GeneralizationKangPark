#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>

using namespace std;

long str2long(char*);
void q_print(double*);

long NUM_TERMS;

int main(int argc, char** argv)
{

	// RJLO 2021: 	This code was originally written in May/June of 2009, and was very poorly commented.
	// I've added some comments below with my 12 year later interpretation
	// All such comments are indicated by a (2021) tag and should be taken with a grain of salt
	// Inagaki and Tamura 2022: We have modified this code from Robert J. Lemke Oliver to calculate
	// q_d^{(1)}(m), Q_{d-3}^{(1, -)}(m), q_d^{(1)}(m) -  Q_{d-3}^{(1, -)}(m).
	// For notation of partition functions, see the paper in the repository.
	// (IMPORTANT NOTE:) The variable d used in this code stands for the variable k as used in Section 7 of the attached paper.
	// We avoid using k in comments in order to avoid confusion with the variable k used in the C++ code to index a for loop and other comments blurbs in this file with different meaning.

	if (argc != 3 && argc!=4)
	{
		cout << "Incorrect calling procedure.  Try " << argv[0] << " num_terms d (filename)." << endl;
		return 0;
	}

	ofstream output;
	if (argc==4)
	{
		output.open(argv[3]);
	        output << "n, Q, q, D\n";
	}

	cout << "Computing q_d(n): " << flush;

	NUM_TERMS=str2long(argv[1])+1;

	int d=str2long(argv[2]);

	long double* q=new long double[NUM_TERMS];
	long double** p_nk=new long double*[NUM_TERMS];

	/* (2021) Idea to compute q_d(n):
	*: If we split up q_d(n) based on the number of parts, k, by subtracting off successive multiples of d from each part, we can relate q_d(n) to (sums of) the partition function p_k(m) that counts the partitions of m into exactly k parts.
	*: The function p_k(m) is subject to a simple recurrence relation: p_k(m) = p_{k-1}(m) + p_k(m-k).  (Either 1 is a part, or it's not.)
	*: The basic idea of the code, then, is to run through the allowable values of k (which I guess should go up to to something like n^{1/2}) and compute the array of required values p_k(m).
	*: In using this recurrence relation, we only need to know the values of the sequence at k and at k-1.  Thus, for memory reasons, only those two arrays are stored.  That's the role of the 0/1 "col" parameter: col is to index the current value of k, 1-col is the previous value.
	*/

	long max_k=long(5/2+sqrt(double(2*NUM_TERMS)/(d)+1/4));
	
	for (long i=0; i<NUM_TERMS; ++i)
	{
		p_nk[i]=new long double[2];
		q[i]=1;
	}

	for (long i=0; i<NUM_TERMS; ++i)
		for (int j=0; j<2; ++j)
		{
			p_nk[i][j]=0;
			p_nk[i][j]=0;
		}
	
	for (long i=0; i<NUM_TERMS; ++i)
		p_nk[i][0]=1;

	int col=0;

	for (long i=2; i<max_k; ++i)
	{
		col = 1-col;
		for (long j=0; j<NUM_TERMS; ++j)	
		{
			if (i<=j)
				p_nk[j][col]=p_nk[j-1][1-col]+p_nk[j-i][col];
			else
				p_nk[j][col]=0;
		}
		long kk=i*(i-1)/2*d;
		for (long j=kk; j<NUM_TERMS; ++j)
			q[j]+=p_nk[j-kk][col];
		
	}

	free(p_nk);

	cout << "Done!" << endl << "Computing Q_{d-3}^{(1, -)}(n): " << flush;

	/* (RJLO 2021; modified 2022 by Inagaki and Tamura): Idea to compute Q_{d-3}^{(1, -)}(n):
	  *: Decompose Q_{d-3}^{(1, -)}(n) based on the number of parts; call the relevant function Q_{d-3,k}.  
	  *: Either 1 is a part or not, in which case each part has to have some size.  That gives you a recurrence relation of the type Q_{d-3,k}(n) = Q_{d-3,k-1}(n-1) + Q_{d-3,k}(n - k*size), where size is the right thing to subtract off.  
	  *: This is still memory efficient -- you only need to know the value at k and k-1 --so the col parameter comes back, but it's not super time efficient, since k now has to run up to something like N.  
	  *: In particular, this piece of the algorithm is something like O(N^2).
	  * 
	  * : There's some extra stuff below to account for rounding errors.  The way this is handled is to produce an upper bound on Q_d, since that's what's relevant for our purposes.
	*/
	/* Inagaki and Tamura 2022: Note that on Line 131 of this file, we set  kk2=((k+1)/2)*(d+3)+((k+1)%2)*(d+2)+(1-((k+1)%2)) as opposed to kk2=((k)/2)*(d+3)+((k)%2)*(d+2)+(1-((k)%2)) since
	 (d-3 - 1) cannot be a part of any partition counted by function Q_{d-3}^{(1, -)}; this is due to the single dash.
	 Also, note that we add the line setting d = d-3 (Line 106) due to the d-3 in the subscript of the counting function of interest, Q_{d-3}^{(1, -)}(n)*/
	d = d - 3;
	long max_kQ=2*NUM_TERMS/(d+3)+2;
	long double** Q_k=new long double*[NUM_TERMS];
	for (long i=0; i<NUM_TERMS; ++i)
		Q_k[i]=new long double[2];
	
	for (long i=0; i<NUM_TERMS; ++i)
		for (long j=0; j<2; ++j)
			Q_k[i][j]=0;

	for (long i=0; i<NUM_TERMS; ++i)
		Q_k[i][0] = 1;

	col=0;

	long double* Q=new long double[NUM_TERMS];

	long double round_err = 0;
	long double* last_used = new long double[NUM_TERMS];

	for (long j=0; j<NUM_TERMS; ++j) last_used[j]=0;

	long kk=0;
	long kk2=0;	
	
	for (long k=1; k<max_kQ; ++k)
	{
		col=1-col;
		kk2=((k+1)/2)*(d+3)+((k+1)%2)*(d+2)+(1-((k+1)%2));
		for (long j=kk; j<kk2 && j <NUM_TERMS; ++j)
		{
			Q_k[j][col]=Q_k[j][1-col];
			Q[j]=Q_k[j][col];
			if (j%10000 == 0 && j!=0)
				cout << j << "..." << flush;
		}
		kk=kk2;

		for (long i=kk; i<NUM_TERMS; ++i)	
		{
			Q_k[i][col]=Q_k[i][1-col]+Q_k[i-kk][col];
			round_err=Q_k[i-kk][col]-(Q_k[i][col]-Q_k[i][1-col]);
			if (round_err!=0)
			{
               			if (round_err < 0) round_err*=-1;
//				if (round_err/Q_k[i][col]<1e-16) round_err=Q_k[i][col]*1e-16;
		                if (round_err<last_used[i]) round_err=last_used[i];
		                while (Q_k[i][col]+round_err==Q_k[i][col]) round_err*=2;
				Q_k[i][col]+=round_err;
				last_used[i]=round_err;
			}				
		}
	}
	
	if (argc==4)
		for (long j=1; j<NUM_TERMS; ++j)
			output << j << "," << Q[j] << "," << q[j] << "," << q[j]-Q[j] << endl;

	cout << "Done!" << endl;

	

	if (argc==4)
		output.close();

	free(Q);
	free(q);

	return 0;
}

long str2long(char* str)
{
	long val=0;
	int sign=1;
	int i=0;
	if (str[i]=='-')
	{
		sign=-1;
		++i;
	}
	while (str[i])
		val=10*val+str[i++]-48;
	return val*sign;
}

void q_print(double* q1)
{
	if (q1[0]!=0)
		cout << q1[0] << " + ";
	for (int i=1; i<NUM_TERMS; ++i)
		if (q1[i]!=0)
			cout << q1[i] << " q^" << i << " + ";
	cout << "O(q^" << NUM_TERMS << ")" << endl;
}
