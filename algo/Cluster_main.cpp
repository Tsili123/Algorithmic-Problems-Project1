#include "./kMeans++/Cluster.hpp"

Cluster *cluster;

int main(int argc, char *argv[]) {
    cluster->data = store_Cluster_data(argc, argv);
    cluster->kMeanspp_Initialization();
    cluster->Lloyd_method();
    cluster->Silhouette();
    cluster->print();
    return 0;
}