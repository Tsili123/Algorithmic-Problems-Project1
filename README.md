# Algorithmic-Problems

Assignment for the first part of the project "Software development for algorithmic problems"

# Hypercube 

## The theory that implementation is based on

![alt text](https://github.com/NizarDarwish/Algorithmic-Problems-Project1/blob/main/algo1.PNG)

![alt text](https://github.com/NizarDarwish/Algorithmic-Problems-Project1/blob/main/algo2.PNG)

### Technical details
Our task was to create a hash function that maps vectors to buckets in a randomized way.The algorithm is based on the Locality Sensitivity Hashing , as it is using its methods to find solution .Firstly, I have created a  [```Euclidean_H_i class```](https://github.com/NizarDarwish/Algorithmic-Problems-Project1/blob/main/algo/Hypercube/hypercube.hpp#L23) which computes all the random parameters euclidean hash function is using.Secondly , I store an array of k  [```euclidean hash values```](https://github.com/NizarDarwish/Algorithmic-Problems-Project1/blob/main/algo/Hypercube/hypercube.cpp#L29)  that our algorithm needs to calculate the random f_i values.Basically , every h_i has precomputed all of its parameters and with the  [```Euclidean class function "specific hash value" ```](https://github.com/NizarDarwish/Algorithmic-Problems-Project1/blob/main/algo/Hypercube/hypercube.hpp#L71) we calculate the final value.The aforementioned function takes the coordinates of every point vector p as a variable to find the result.
  
Let's have a look at the next step of the algorthm , which is to find the f_i values which project every vector point p to {0,1} aggregation.


### The files of the implementation can be found on the path ./algo/Hypercube

