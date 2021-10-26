#include "LSH.hpp"

void Bucket::add(long long int point_id,long int g_i,long long int hash_id)
{
    points.push_back(make_pair(make_pair(point_id, hash_id), g_i));
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

    //Fill buckets of Hash_Table
    for(int i=0;i<points_num;i++){
        for(int j=0;j<L_var;j++){
            //Call function so as to compute all g_i values
            vector<long long int> hash_values = info->Specific_Hash_Value(j, info->data[i]);
            g_i[i][j] = hash_values[0];
            if(info->get_hashtables()[j][g_i[i][j]]==NULL)  
                info->get_hashtables()[j][g_i[i][j]] = new Bucket();
            info->get_hashtables()[j][g_i[i][j]]->add((long long int) i , g_i[i][j], hash_values[1]); 
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