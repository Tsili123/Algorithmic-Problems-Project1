#include "LSH.hpp"

using namespace std;

extern LSH *Lsh; /* LSH Object */

void Print_values() {
    cout << "L: " << Lsh->get_L() << endl << "k: " << Lsh->get_k() << endl;
    cout << "dimensions: " << Lsh->get_dimension() << endl << "number of items: " << Lsh->get_PointsNum() << endl;
    cout << "Range-R: " << Lsh->get_R() << endl << "N: " << Lsh->get_N() << endl;;

    /* Print vector v */
    // for (auto vec: v) {
    //     cout << "vector v: ";
    //     for (auto i: vec)
    //         cout << i << ", ";
    //     cout << endl;
    // }

    /* Print vector t */
    cout << "vector t: ";
    for (auto vec: t)
        cout << vec << ", ";  
    cout << endl;
}

long long int mod(long long int value, long long int Mod) {
    if ((value % Mod) < 0) 
        return (unsigned int) (value % Mod + Mod);
    else
        return (unsigned int) (value % Mod);
}

double Normal_distribution() {
    // Inspired from https://en.cppreference.com/w/cpp/numeric/random/normal_distribution
    random_device rd{};
    mt19937 gen{rd()};
 
    normal_distribution<float> d{0, 1};
 
    map<int, int> hist{};
    return round(d(gen));
}

void Euclidean_Hash_Function(int L, int k) {
    // Initialize the vectors used for hashing
    v.resize(k, vector<double>(Lsh->get_dimension()));

    for(int i=0; i < k; i++) {
        v[i].clear();

		for(int j=0; j < Lsh->get_dimension(); j++){
			v[i].push_back(Normal_distribution());
		}
    }

    // Initialize w (change it to your liking)
    Lsh->set_w(400);

    srand(time(0));

    // Initialize vector t
    // Inspired from https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
    t.clear();

	random_device generator;
	uniform_real_distribution<float> dis(0.0, (float) Lsh->get_w());

	for(int i=0; i<k; i++){ 	// For every hash function
		float random = dis(generator);
		t.push_back(random);
	}

    // Every hash function has a vector length k (otherwise known as r)
    Hash_Functions.resize(L, vector<int> (k));

    for(int i = 0; i < L; i++){
		Hash_Functions[i].clear();

        int j=0;

        do{
			int r_value = rand() % k;

            // auto itA = Hash_Functions[i].begin();

            // while(itA != Hash_Functions[i].end()) {
            //     if (r_value == itA[0]) break;
            //     if (itA != Hash_Functions[i].end()) ++itA;
            //     else {
            //         Hash_Functions[i].push_back(r_value);
            //         j++;
            //         break;
            //     }
            // }
            Hash_Functions[i].push_back(r_value);
            j++;
		}while(j < k);
	}
}

// Place the vector from the input file to a bucket
void Calculate_Hash_Value(int L, int k, vector<int> item) {
    for (int g = 0; g < L; g++) {
        long long int hash_value = 0;
        long int ID = -1;
        for (int h = 0; h < k; h++) {
            int sum = 0;
            /* The inner product is calculated by multiplying all the coordinates of 2 vectors and summing them*/
            for (int dim = 1; dim < Lsh->get_dimension(); dim++) {
                sum += item[dim] * v[h][dim];
            }

            sum += t[h];
            sum = floor(sum / (double) Lsh->get_w());
            hash_value += sum * Hash_Functions[g][h];
            hash_value = mod(hash_value, M);
        }

        ID = hash_value;

        hash_value = mod(hash_value, Lsh->get_PointsNum()/4);
        cout << "for table " << g << " hash value is " << hash_value << endl;
    }
}

// Calculate Euclidean Distance
long double euclidean_dis(vector<int> vec1, vector<int> vec2) {
    long double dist=0.0;

    auto itA = vec1.begin();
    auto itB = vec2.begin();
    ++itA;
    ++itB;

    while(itA != vec1.end() || itB != vec2.end())
    {
        dist = dist + (itA[0]-itB[0])*(itA[0]-itB[0]);
        if(itA != vec1.end()) {
            ++itA;
        }
        if(itB != vec2.end()) {
            ++itB;
        }
    }

	return sqrt(dist);
}

// Return the hash value for a specific query in a table
int Specific_Hash_Value(int g, vector<int> item) {
    int L = Lsh->get_L();
    int k = Lsh->get_k();

    long long int hash_value = 0;
    long int ID = -1;
    for (int h = 0; h < k; h++) {
        int sum = 0;
        /* The inner product is calculated by multiplying all the coordinates of 2 vectors and summing them*/
        for (int dim = 1; dim < Lsh->get_dimension(); dim++) {
            sum += item[dim] * v[h][dim];
        }

        sum += t[h];
        sum = floor(sum / (double) Lsh->get_w());
        hash_value += sum * Hash_Functions[g][h];
        hash_value = mod(hash_value, M);
    }

    return mod(hash_value, Lsh->get_PointsNum()/4);
}

vector<int> Nearest_N_search(vector<int> query) {
    long double d = M; // Minimum distance
    long int iterations = 0; // When it reaches 10L stop
    long int b = -1; // Closest item so far

    int L = Lsh->get_L();
    int N = Lsh->get_N();

    vector<int> near_items;

    for (int g = 0; g < L; g++) {
        int hash_value = Specific_Hash_Value(g, query);
        // For every item in the bucket {
        iterations++;
        long double euc_dist; // = euclidean_dis(item_from_bucket, query);

        if (euc_dist < d && near_items.size() == N) {
            d = euc_dist;
            // b = item_from_bucket.front();
            if (none_of(near_items.begin(), near_items.end(), [b](int item) { return b == item; })) {
                near_items.erase(near_items.begin());
                near_items.push_back(b);
            }
        } else {
            // b = item_from_bucket.front();
            near_items.push_back(b);
            sort(near_items.begin(), near_items.end(), greater<int>());
        }
        if (iterations == 10*L) break;
        // }
    }

    return near_items;
}

vector<int> Search_by_range(vector<int> query) {
    int L = Lsh->get_L();
    int k = Lsh->get_k();
    int R = Lsh->get_R();

    vector<int> near_items;

    for (int g = 0; g < L; g++) {
        int hash_value = Specific_Hash_Value(g, query);
        // For every item in the bucket
        long double euc_dist; // = euclidean_dis(item_from_bucket, query);

        if (euc_dist < R) {
            // int index = item_from_bucket.front();
            // if (none_of(near_items.begin(), near_items.end(), [index](int item) { return index == item; })) {
            //     near_items.push_back(index);
            // }
        }
    }

    return near_items;
}

int Nearest_N_brute(vector<int> query) {
    long double d = (double) M; // Minimum distance
    long int b = -1; // Closest item so far

    for (auto Item: Lsh->data) {
        if (Item == query) continue;
        long double euc_dist = euclidean_dis(Item, query);

        if (euc_dist < d) {
            d = euc_dist;
            b = Item.front();
        }
    }

    cout << d << endl;

    return b;
}

vector<int> Brute_by_range(vector<int> query) {
    int L = Lsh->get_L();
    int k = Lsh->get_k();
    int R = Lsh->get_R();

    vector<int> near_items;

    for (auto Item: Lsh->data) {
        if (Item == query) continue;
        long double euc_dist = euclidean_dis(Item, query);

        if (euc_dist < R) {
            int index = Item.front();
            near_items.push_back(index);
        }
    }

    return near_items;
}

/* Initialize the variables used by the hash function */
LSH::LSH(string input, string query, string output, int L_,int N_,int k_,int R_, long long int n, int dim)
        :input_file(input), query_file(query), output_file(output), L(L_), N(N_), k(k_), R(R_), points_num(n), dimension(dim)
    {}


// int* LSH::get_modulars()
// {
//     return modulars;
// }

// int** LSH::get_s_i()
// {
//     return s_i;
// }

// double* LSH::get_tTrue()
// {
//     return tTrue;
// }

// int** LSH::get_True_Distances()
// {
//     return True_Distances;
// }

// int** LSH::get_PointsArray()
// {
//     return points_array;
// }

// int** LSH::get_QueriesArray()
// {
//     return queries_array;
// }

// Bucket*** LSH::get_HashTables()
// {
//     return hashtables;
// }