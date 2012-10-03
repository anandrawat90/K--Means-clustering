#include <iostream>
#include "k_means.h"


int main(int argc, char *argv[])
{
    if(argc==1)
    {
        std::cout<<"Improper usage!\nUsage: "<<argv[0]<<" [FILENAME]"<<std::endl;
        return 0;
    }

    k_means obj(argv[1]);
    //Initialize the clustering of the data set
    obj.clusterize();

    return 0;
}
