#include "bucket.hpp"

void Bucket::add(int point_id,unsigned int g_i,long int hash_id)
{
    points.push_back(make_pair(point_id,g_i,hash_id));
}

//Fill hashtables with Points (data structure initialization) for LSH.
void LSH_Insert_Points_To_Buckets(LSH* info){
    //Allocate memory so as to store temporarily g_i values
    long long int points_num = info->get_pointsnum();
    int L_var = info->get_L();
    unsigned int** g_i = new unsigned int*[points_num];
    for(int i=0;i<points_num;i++) {
        g_i[i] = new unsigned int[L_var];
        for(int j=0;j<L_var;j++)  
            g_i[i][j]=0;
    }

    //Call function so as to compute all g_i values
    gi_values_of_train(info,g_i);
    
    //Fill buckets of Hash_Table
    for(int i=0;i<points_num;i++){
        for(int j=0;j<L_var;j++){
            if(info->get_hashtables()[j][g_i[i][j]]==NULL)  
                info->get_hashtables()[j][g_i[i][j]] = new Bucket();
            info->get_hashtables()[j][g_i[i][j]]->add([info->data[i][0],g_i[i][j]);    
        }
    }
    //Deallocation of memory
    for(int i=0;i<points_num;i++)  
        delete [] g_i[i];
    delete [] g_i;
}
// InfoLSH
// get_L();
// get_PointsNum
// get_HashTables()
// get_PointsArray()[i]

// //Search exhaustively for each query distance with each image of dataset so as to find best for LSH.
// void ExhaustingNN(LSH* info)
// {   
//     for(int i=0;i<info->get_Num_of_Queries();i++)
//     {
//         auto start = chrono::high_resolution_clock::now(); 
//         priority_queue<int, vector<int>, greater<int>> pq;

//         for(int j=0;j<info->get_Num_of_Images();j++)
//             pq.push(ManhattanDistance(info->get_Queries_Array()[i],info->get_Images_Array()[j],info->get_dimensions()));
        
//         auto end = chrono::high_resolution_clock::now(); 
//         for(int k=0;k<info->get_N();k++)
//         {
//             info->get_True_Distances()[i][k] = pq.top();
//             pq.pop();
//         }
//         info->get_tTrue()[i] = chrono::duration_cast<chrono::microseconds>(end - start).count();  
//     }
// }