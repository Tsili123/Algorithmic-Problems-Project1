all: lsh cube cluster

CC = g++ #-O2
FLAGS = -std=c++11 -c -g #-Wall

OBJS1 = LSH_main.o functions.o Handling_input.o bucket.o LSH.o 
OBJS2 = CUBE_main.o functions.o Handling_input_cube.o
OBJS3 =  Cluster_main.o functions.o Handling_input_cluster.o Cluster.o LSH.o bucket.o 

Headers = kMeans++/Handling_input/Handling_input.hpp Handling_input/Handling_input.hpp functions/functions.hpp LSH_File/hypercube.hpp LSH_File/LSH.hpp kMeans++/Cluster.hpp

EXEC1 = lsh
EXEC2 = cube
EXEC3 = cluster

$(EXEC1): $(OBJS1) $(Headers) 
	$(CC)  $(OBJS1)  -o $(EXEC1)

$(EXEC2): $(OBJS2) $(Headers) 
	$(CC)  $(OBJS2) -o $(EXEC2)

$(EXEC3): $(OBJS3) $(Headers) 
	$(CC)  $(OBJS3) -o $(EXEC3)

Handling_input_cluster.o: kMeans++/Handling_input/Handling_input.cpp
	$(CC) $(FLAGS) kMeans++/Handling_input/Handling_input.cpp

Handling_input.o: Handling_input/Handling_input.cpp
	$(CC) $(FLAGS) Handling_input/Handling_input.cpp

functions.o: functions/functions.cpp
	$(CC) $(FLAGS) functions/functions.cpp

Handling_input_cube.o: Handling_input/Handling_input_cube.cpp
	$(CC) $(FLAGS) Handling_input/Handling_input_cube.cpp

Cluster.o: Cluster.cpp
	$(CC) $(FLAGS) Cluster.cpp

bucket.o: LSH_File/bucket.cpp
	$(CC) $(FLAGS) LSH_File/bucket.cpp

LSH.o: LSH_File/LSH.cpp
	$(CC) $(FLAGS) LSH_File/LSH.cpp

# hypercube.o: LSH_File/hypercube.cpp
# 	$(CC) $(FLAGS) LSH_File/hypercube.cpp

Cluster_main.o: Cluster_main.cpp
	$(CC) $(FLAGS) Cluster_main.cpp

LSH_main.o: LSH_main.cpp
	$(CC) $(FLAGS) LSH_main.cpp

CUBE_main.o: CUBE_main.cpp
	$(CC) $(FLAGS) CUBE_main.cpp


clean:
	rm -f $(EXEC1) $(EXEC2) $(OBJS1) $(OBJS2)


# run_lsh:
# 	./lsh -i Datasets/small/input_small_id -q Datasets/small/query_small_id  -o output_file_lsh.txt

# run_cube:
# 	./cube -i Datasets/small/input_small_id -q Datasets/small/query_small_id -o output_file_cube.txt 

# run_cluster:
# 	./cluster -i Datasets/small/input_small_id -c cluster.conf -o output_file_cluster.txt -m LSH
