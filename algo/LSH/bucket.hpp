#ifndef BUCKET_H
#define BUCKET_H

#include "../headers/read_binary_file.h"

class Bucket
{
    public:
        vector<pair<int*,unsigned int>> points;     

        void add(int*,unsigned int);
};


void Bucket::add(int* point,unsigned int g_i);

void LSH_Insert_Points_To_Buckets(LSH* info);

#endif