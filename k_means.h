#ifndef K_MEANS_H
#define K_MEANS_H

class k_means
{
    public:
        k_means(char[]); //Also initializes the the centroids to some random points from the given data set

        ~k_means();

        void clusterize(); //To start clusterising the data set

        void minimum_of(double[]); // To find the minimum of the euclidian distance

        void print(int); //Print the clusters step by step

        void set_centroids(); // To set the new centroids the according the average of the points in the cluster

    private:

    int no_of_clusters, no_of_points, means;


    double **points; //To store the points in co-ordinates

    double **centroids; //To store the centroids of each cluster

    double **cluster; //To store the cluster data along with the distance

    double euclidean_distance(double x1,double y1, double x2, double y2); //To calculate the euclidean distance
};

#endif // K_MEANS_H
