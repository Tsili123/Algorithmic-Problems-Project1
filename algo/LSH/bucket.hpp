#ifndef BUCKET_H
#define BUCKET_H

// #include "../headers/read_binary_file.h"
#include "LSH.hpp"
#include "Bucket.hpp"

class Bucket
{
    public:
        vector<pair<int*,unsigned int>> points;     

        void add(int*,unsigned int);
};

void LSH_Insert_Points_To_Buckets(LSH* info);

#endif