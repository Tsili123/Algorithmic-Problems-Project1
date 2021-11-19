# Algorithmic-Problems

Assignment for the first part of the project "Software development for algorithmic problems"

# LSH
Typing... :)

# Hypercube 

## The theory that implementation is based on

![alt text](https://github.com/NizarDarwish/Algorithmic-Problems-Project1/blob/main/algo1.PNG)

![alt text](https://github.com/NizarDarwish/Algorithmic-Problems-Project1/blob/main/algo2.PNG)

![alt text](https://github.com/NizarDarwish/Algorithmic-Problems-Project1/blob/main/algo3.PNG)

### Technical details
Our task was to create a hash function that maps vectors to buckets in a randomized way.The algorithm is based on the Locality Sensitivity Hashing , as it is using its methods to find solution .Firstly, I have created a  [```Euclidean_H_i class```](https://github.com/NizarDarwish/Algorithmic-Problems-Project1/blob/main/algo/Hypercube/hypercube.hpp#L23) which computes all the random parameters euclidean hash function is using.Secondly , I store an array of k  [```euclidean hash values```](https://github.com/NizarDarwish/Algorithmic-Problems-Project1/blob/main/algo/Hypercube/hypercube.cpp#L29)  that our algorithm needs to calculate the random f_i values.Basically , every h_i has precomputed all of its parameters and with the  [```Euclidean class function "specific hash value" ```](https://github.com/NizarDarwish/Algorithmic-Problems-Project1/blob/main/algo/Hypercube/hypercube.hpp#L71) we calculate the final value.The aforementioned function takes the coordinates of every point vector p as a variable to find the result.
  
Let's have a look at the next step of the algorthm , which is to find the f_i values which project every vector point p to {0,1} aggregation.On that stage,  [```f_i random function```](https://github.com/NizarDarwish/Algorithmic-Problems-Project1/blob/main/algo/Hypercube/hypercube.cpp#L34) gets every h_i(vector_p) value as a parameter to calculate the first bit of the bitstring.You might be wondering what is that bitstring and that's logical because I haven't mentioned anything about that yet.As we said previously,the goal is to map vector points to buckets in a new randomized way.As a result, the role of f_i's is to produce k 0 and 1 values to form a bitstring with 0,1.That string is then be transformed to decimal number in order to place the point to the bucket with the desired id.Becasue we want to save memory space,for every f_i that takes an h_i value already computed , we store the pair {h_i,f_i} in an H_i_map array [```H_i_map array```](https://github.com/NizarDarwish/Algorithmic-Problems-Project1/blob/main/algo/Hypercube/hypercube.cpp#L36).In that way if we come across the same h_i for the respective h_i, we don't have to calculate and store that value but we extract it from the data structure .I will present you an example to make that more clear. For a point_x h_1(point_x) = 3 and f_1(h_1(point_x)) = 0 .We save the pair {3,0} on the H(1) vector of pairs.As a result , we have a dictionary that tell us whether we have computed that value or not.That work is being done k times(the number of the f_i's) so as to create the binary bitstring {f1(h1(p)),f2(h2(p)) . . . , fd'(hd'(p)) }, d' = k that forms the final result.That solution can be found on that [```link```](https://github.com/NizarDarwish/Algorithmic-Problems-Project1/blob/main/algo/Hypercube/hypercube.cpp#L71)

The  [```third```](https://github.com/NizarDarwish/Algorithmic-Problems-Project1/blob/main/algo/Hypercube/hypercube.cpp#L102) and final part of the algorithm consists of creating a searching function to solve querys.It means that we hash a given vector and find its position on the hashtable.The logic behind this , as shown on the images above, can be explained in 3 steps :

1. Hash the point and find the cube id(the bucket id of the hypercube)
2. Then , find the neighbour buckets of the found bucket based on the hamming distance of them(the different number of zeroes and aces)
3. Finally , search points in the same vertex(bucket) and nearbly vertices in order to find points in the given radius (R)

Same logic is applied on the nearest neighbour search , but this time we save a specific number of neighbours and not all of them in a given radius.


### The files of the implementation can be found on the path ./algo/Hypercube
### The structure of the progeam can be reviewed on the [```header file```](https://github.com/NizarDarwish/Algorithmic-Problems-Project1/blob/main/algo/Hypercube/hypercube.hpp)

### Run 
Just type ```make``` in the algo directory of the assignment, because makefile is included .
Then  type on that path in terminal :

```./cube -i ./files/input_small_id -q ./files/query_small_id -k 14 -M 10 -probes 2 -o output -N 5 -R 350``` 

Note: k is the number of f_i's . M is a threshold to how many points we are searching each time. Probes means how many buckets are we cheking based on hamming distance.Output is the file that will store the result and will be created in algo directory.Finally , N is the number of nearest neighbours to a given point and R is the radius that we want to search around a given point

# Clustering
Typing... :)
