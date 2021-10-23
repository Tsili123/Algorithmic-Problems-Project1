#include "LSH.hpp"

using namespace std;

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
    v.resize(k ,vector<double>(dimension));

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

void Calculate_Hash_Value(int L, int k, int item) {}