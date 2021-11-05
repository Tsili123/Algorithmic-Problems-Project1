#include "LSH.hpp"

using namespace std;

extern LSH *Lsh; /* LSH Object */

int W;

/* Initialize the variables used by the hash function */
LSH::LSH(string input, string query, string output, int L_,int N_,int k_,int R_, long long int n, int dim, vector<vector<int>> Data)
        :input_file(input), query_file(query), output_file(output), L(L_), N(N_), k(k_), R(R_), points_num(n), dimension(dim)
    {
        data = Data;
        W = Calculate_w();

        hashtable_size = n/4;
        Hash_Funs = new Euclidean_Hash_Function[L];
         //Declaration of hash tables...
        hashtables = new Bucket**[L];
        for(int i=0;i<L;i++) {
            Hash_Funs[i] = Euclidean_Hash_Function(k, dim);
            hashtables[i] = new Bucket*[hashtable_size];
            for(int j=0;j<hashtable_size;j++)   hashtables[i][j] = NULL;                
        }

        // Every hash function uses a vector r length k

        int j=0;

        do {
            int r_value = rand();
            r.push_back(r_value);
            j++;
        }while(j < k);
    }

void LSH::print_buckets() {
    for(int j=0; j < this->L; j++) {
        for(long int i=0; i < this->hashtable_size - 2498; i++){
            cout << "Table " << j << " in Bucket " << i << endl;
            int counter = 0;
            if (hashtables[j][i] != NULL) {
                for (auto point: hashtables[j][i]->points) {
                    if (counter == 5) break;
                    cout << "Item id: " << point.first.first << endl;
                    cout << "Hash id: " << point.first.second << endl;
                    cout << "Hash value: " << point.second << endl;
                    counter++;
                }
            }
        }
    }
}

long long int mod(long long int value, long int Mod) {
    if ((value % Mod) < 0) 
        return (unsigned int) (value % Mod + Mod);
    else
        return (unsigned int) (value % Mod);
}

// Return the hash value for a specific query in a table
vector<long long int> LSH::Specific_Hash_Value(int g, vector<int> item) {
    int L = this->get_L();
    int k = this->get_k();
    long long int ID = -1;

    Euclidean_Hash_Function Hash_Fun = this->get_hash_functions()[g];

    long long int hash_value = 0;
    for (int h = 0; h < k; h++) {
        int sum = 0;
        vector <double> v = Hash_Fun.get_vector_v()[h];
        vector <double> t = Hash_Fun.get_vector_t();
        /* The inner product is calculated by multiplying all the coordinates of 2 vectors and summing them*/
        for (int dim = 1; dim < this->get_dimension(); dim++) {
            sum += item[dim] * v[dim];
        }

        sum += t[h];
        sum = floor(sum / (double) this->get_w());
        hash_value += sum * r[h];
        hash_value = mod(hash_value, M);
    }

    ID = hash_value;

    return {mod(hash_value, this->get_hashtablesize()), ID};
}


void Print_values() {
    cout << "L: " << Lsh->get_L() << endl << "k: " << Lsh->get_k() << endl;
    cout << "dimensions: " << Lsh->get_dimension() << endl << "number of items: " << Lsh->get_pointsnum() << endl;
    cout << "Range-R: " << Lsh->get_R() << endl << "N: " << Lsh->get_N() << endl;
    cout << "W: " << Lsh->get_w() << endl;

    /* Print vector v */
    // for (auto vec: v) {
    //     cout << "vector v: ";
    //     for (auto i: vec)
    //         cout << i << ", ";
    //     cout << endl;
    // }

    /* Print vector t */
    // cout << "vector t: ";
    // for (auto vec: t)
    //     cout << vec << ", ";  
    // cout << endl;

    // Lsh->print_buckets();
}

int LSH::Calculate_w() {
    long double sum = 0;
    long int subpoints = this->points_num * 5/100;
    for (int point = 1; point < subpoints - 1; point++) {
        for (int second_point = point; second_point < subpoints; second_point++) {
            sum += euclidean_dis(this->data[point], this->data[second_point]);
        }
        sum /= (subpoints - point);
    }
    set_w(sum);
    return this->get_w();
}

Euclidean_Hash_Function::Euclidean_Hash_Function(int k, int dim) {
    // Initialize the vectors used for hashing
    v.resize(k, vector<double>(dim));

    for(int i=0; i < k; i++) {
        v[i].clear();

		for(int j=0; j < dim; j++){
			v[i].push_back(Normal_distribution());
		}
    }

    srand(time(0));

    // Initialize vector t
    // Inspired from https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
    t.clear();

	random_device generator;
	uniform_real_distribution<float> dis(0.0, (float) W);

	for(int i=0; i<k; i++){ 	// For every hash function
		float random = dis(generator);
		t.push_back(random);
	}
}

Euclidean_Hash_Function::~Euclidean_Hash_Function() {
    v.clear();
    t.clear();
}

vector<pair<long double, int>> Nearest_N_search(vector<int> query) {
    long double d = M; // Minimum distance
    long int b = -1; // Closest item so far

    int L = Lsh->get_L();
    int N = Lsh->get_N();

    vector<pair<long double, int>> near_items;

    Bucket *** buckets = Lsh->get_hashtables();

    for (int g = 0; g < L; g++) {
        vector<long long int> hash_value = Lsh->Specific_Hash_Value(g, query);
        if (buckets[g][hash_value[0]] == NULL) continue;

        for (auto Points: buckets[g][hash_value[0]]->points) {
            int index = Points.first.first;
            long double euc_dist = euclidean_dis(Lsh->data[index], query);

            if (euc_dist < d) {
                b = index + 1;
                if (none_of(near_items.begin(), near_items.end(), [b](pair<long double, int> item) { return b == item.second; })) {
                    if (near_items.size() >= N) {
                        near_items.pop_back();
                    }

                    near_items.push_back(make_pair(euc_dist, b));
                    sort(near_items.begin(), near_items.end());
                    d = near_items.back().first;
                }
            }
        }
    }

    return near_items;
}

vector<int> Search_by_range(vector<int> query) {
    long int iterations = 0; // When it reaches 100L stop
    int L = Lsh->get_L();
    int k = Lsh->get_k();
    int R = Lsh->get_R();

    vector<int> near_items;

    Bucket *** buckets = Lsh->get_hashtables();

    for (int g = 0; g < L; g++) {
        vector<long long int> hash_value = Lsh->Specific_Hash_Value(g, query);

        if (buckets[g][hash_value[0]] == NULL) continue;
        for (auto Points: buckets[g][hash_value[0]]->points) {
            iterations++;
            int index = Points.first.first;
            long double euc_dist = euclidean_dis(Lsh->data[index], query);
            index += 1; // In input file the index starts from 1

            if (euc_dist <= R) {
                if (none_of(near_items.begin(), near_items.end(), [index](int item) { return index == item; })) {
                    near_items.insert(near_items.begin(), index);
                }
            }
            if (iterations >= 100*L) break;
        }
    }

    return near_items;
}

vector<int> Brute_by_range(vector<int> query) {
    int L = Lsh->get_L();
    int k = Lsh->get_k();
    int R = Lsh->get_R();

    vector<int> near_items;

    auto begin = high_resolution_clock::now();

    for (auto Item: Lsh->data) {
        if (Item == query) continue;
        long double euc_dist = euclidean_dis(Item, query);

        if (euc_dist <= R) {
            int index = Item.front();
            near_items.push_back(index);
        }
    }

    auto end = high_resolution_clock::now();

    duration<double, std::milli> BSBR_time = end - begin;

    cout << "BSBR TIME: " << BSBR_time.count() << endl;

    return near_items;
}