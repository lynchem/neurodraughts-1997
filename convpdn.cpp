/******************* Convert PDN to Training Data ************************
	Written by: Mark Lynch
   		  on: April 1997
          for: Final Year Project, University of Limerick, Ireland.

	Description:
	This program simply converts PDN files to training Data for
   NeuroDraughts.
	
	Permission is granted to Andrea Omodeo to modify this source
	for use in a Freeware program as long as the source is not
	distributed.
************************************************************************/

#include "train.h"
#include <time.h>
#include <iostream.h>

void main(int argc, char** argv)
{
   //general bits
	time_t 	s,e;
   int 		ignoredraws;

   //the files
   char 			*pdnfile, *outfile;

   //take time
   s= time(NULL);

   cout<<"\n\tPDN to ND Training Data Converter, (c) 1997 Mark Lynch.\n\n";

   //check input
   if(argc != 4)
   {
   	cerr<<"Incorrect Parameters\n Usage: "<<argv[0]<<" PDN file, output file, ignore draws\n";
      exit(-1);
   }

   //assign pointers
   pdnfile = argv[1];
   outfile  = argv[2];
   ignoredraws  = atoi(argv[3]);

   PDNtoBoards(pdnfile, outfile, ignoredraws);

   //output some info
   e=time(NULL);
   cout<<"************************ Finished *******************************\n";
   cout<<"\tTime elapsed: "<<difftime(e,s)<<endl;
}


