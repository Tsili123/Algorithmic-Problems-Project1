#include "LSH.hpp"

using namespace std;

void Print_values(int L, int k) {
    cout << "L: " << L << endl << "k: " << k << endl;
    cout << "dimensions: " << dimension << endl << "number of items: " << n << endl;

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

void Initialize_Hash_parameters() {
    dimension = dim_data();
    n = num_of_points();
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
    v.resize(k, vector<double>(dimension));

    for(int i=0; i < k; i++) {
        v[i].clear();

		for(int j=0; j < dimension; j++){
			v[i].push_back(Normal_distribution());
		}
    }

    // Initialize w (change it to your liking)
    w = 400;

    srand(time(0));

    // Initialize vector t
    // Inspired from https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
    t.clear();

	random_device generator;
	uniform_real_distribution<float> dis(0.0, (float) w);

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

			if(find(Hash_Functions[i].begin(), Hash_Functions[i].end(), r_value) == Hash_Functions[i].end()){
				j++;
				Hash_Functions[i].push_back(r_value);
			}
		}while(j < k);
	}
}

void Calculate_Hash_Value(int L, int k, vector<int> item) {
    for (int g = 0; g < L; g++) {
        long long int hash_value = 0;
        long int ID = -1;
        for (int h = 0; h < k; h++) {
            int sum = 0;
            /* The inner product is calculated by multiplying all the coordinates of 2 vectors and summing them*/
            for (int dim = 1; dim < dimension; dim++) {
                sum += item[dim] * v[h][dim];
            }

            sum += t[h];
            sum = floor(sum / (double) w);
            hash_value += sum * Hash_Functions[g][h];
            hash_value = mod(hash_value, M);
        }

        ID = hash_value;

        hash_value = mod(hash_value, n/4);
        // cout << "for table " << g << " hash value is " << hash_value << endl;
    }
}

long long int euclidean_dis(vector<int> vec1, vector<int> vec2) {
    long long int dist=0;

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

	return dist;
}