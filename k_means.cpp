#include "k_means.h"
#include <cstdlib>
#include <iostream>
#include <fstream>


using namespace std;

k_means::k_means(char fp[])
{
    FLAG=true;
    fstream file(fp);
    file>>no_of_points>>no_of_clusters;
    int index,i;

    cluster= new double*[no_of_points];
    for(i=0;i<no_of_points;i++)
    {
        cluster[i]=new double[no_of_clusters+1];
    }


    points = new double *[no_of_points];
    for(i=0;i<no_of_points;i++)
    {
        points[i]=new double[2];
        //Read the data set
        file>>points[i][0]>>points[i][1];
    }

    int arindex[no_of_clusters];
    fill_n(arindex,no_of_clusters,0);

    srand(time(0));
    centroids=new double*[no_of_clusters];
    for(i=0;i<no_of_clusters;i++)
    {
        centroids[i]=new double[2];

        //Picking random index for the inital centroids
        index=(rand()%no_of_points);

        //making sure the no centroid is picked twice
        while(arindex[(index%no_of_clusters)]!=0)
        index++;
        arindex[(index%no_of_clusters)]++;

        //Assign x co-ordinate
        centroids[i][0]=points[index][0];

        //Assign y co-ordinate
        centroids[i][1]=points[index][1];
    }
    /*
    centroids[0][0] = 2;
    centroids[0][1] = 10;
    centroids[1][0] = 5;
    centroids[1][1] = 8;
    centroids[2][0] = 1;
    centroids[2][1] = 2;
    */

    file.close();
}

k_means::~k_means()
{
    int i=0;
    for(i=0;i<=no_of_clusters;i++)
    delete [] cluster[i];
    delete []cluster;

    for(i=0;i<2;i++)
    delete [] points[i];
    delete [] points;


    for(i=0;i<2;i++)
    delete [] centroids[i];
    delete [] centroids;

}

double k_means::euclidean_distance(double x1, double y1, double x2, double y2)
{
    double z= x1>x2?x1-x2:x2-x1;
    z+= (y1>y2?y1-y2:y2-y1);
    //Returns the distance between the two points
    return z;
}

void k_means::clusterize()
{
    int steps=1;
    int old;
    bool newFLAG,flag1;
    while(FLAG)
    {
        flag1=true;
        newFLAG=true;

        for(int i=0;i<no_of_points;i++)
        {
            old=int(cluster[i][no_of_clusters]);

            for(int j=0;j<no_of_clusters;j++)
            {
                //Write the distance data for each centroid
                cluster[i][j]=euclidean_distance(points[i][0],points[i][1],centroids[j][0],centroids[j][1]);
            }
            //Set the respective centroid id
            minimum_of(cluster[i]);

            // Mark if the centroid has changed
            if(old==int(cluster[i][no_of_clusters]))
            newFLAG=true;
            else
            newFLAG=false;

            flag1 = flag1 & newFLAG;
        }

        //Print step wise
        print(steps);
        getchar();
        //Get the new centroids
        set_centroids();

        steps++;

        //loop till there is no change in centroids
        FLAG = !flag1;
    }
    for(int i=0;i<no_of_clusters;i++)
    {
        cout<<"\nCluster "<<i+1<<" :"<<endl;
        for(int j=0;j<no_of_points;j++)
        {
            if(cluster[j][no_of_clusters]==i)
            cout<<points[j][0]<<","<<points[j][1]<<endl;
        }
        cout<<"\n************************"<<endl;
    }
}

void k_means::minimum_of(double temp[])
{
    double min=temp[0];
    temp[no_of_clusters]=0;
    for(int j=1;j<no_of_clusters;j++)
    {
        if(min>temp[j])
        {
            //Set the minimum value
            min=temp[j];

            //Set the respective centroid id
            temp[no_of_clusters]=j;
        }
    }
}
 void k_means::print(int step)
 {
     int i,j;
     cout<<"STEP NO: "<<step<<endl;
     for(i=0;i<no_of_points;i++)
     {
         cout<<"Point "<<i<<":  ";
         for(j=0;j<no_of_clusters;j++)
         {
             cout<<cluster[i][j]<<"   ";
         }
         cout<<cluster[i][j]+1<<" ";
         cout<<endl;
     }

    cout<<"The centroids are:"<<endl;
    for(i=0;i<no_of_clusters;i++)
    cout<<centroids[i][0]<<"   "<<centroids[i][1]<<endl;
    cout<<"------------------------\n"<<endl;
 }

void k_means::set_centroids()
{
    int *total_points=new int[no_of_clusters];
    int i,j;

    //Fill total_points with 0
    fill_n(total_points,no_of_clusters,0);

    for(i=0;i<no_of_points;i++)
    {
        //Count the number of points in a cluster
        total_points[int(cluster[i][no_of_clusters])]++;
    }

    for(i=0;i<no_of_clusters;i++)
    {
        double total_x=0,total_y=0;
        for(j=0;j<no_of_points;j++)
        {
            //for the centroid id == cluster id
            if(cluster[j][no_of_clusters]==i)
            {
                //Total x co-ordinate
                total_x+=points[j][0];

                //Total y co-ordinate
                total_y+=points[j][1];
            }
        }

        //Finding the mean on x and y co-ordinate
        centroids[i][0]=total_x/total_points[i];
        centroids[i][1]=total_y/total_points[i];
    }

    delete []total_points;
}
