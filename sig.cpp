#include <stdlib.h>
#include <math.h>
#include <iostream.h>

void main(int argc, char* argv[])
{
	float f, res;

	if (argc != 2)
   {
   	cout<<"Error!\n";
   	exit(-1);
   }

   f=atof(argv[1]);
   res = 1.0 / (1.0 + exp(-f));

   cout<<"The Sigmoid of"<<f<<" is: "<<res<<endl;

   res = tanh(f);
   cout<<"The Hyper of"<<f<<" is: "<<res<<endl;

}
