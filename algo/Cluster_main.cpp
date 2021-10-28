#include "./kMeans++/Cluster.hpp"

Cluster *cluster;

int main(int argc, char *argv[]) {
    cluster->data = store_Cluster_data(argc, argv);
    cluster->print();
    return 0;
}