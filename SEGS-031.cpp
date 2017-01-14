#include <fstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <random>
#include <iterator>
#include "functions/species.hpp"
#include "functions/nodes_1.5.hpp"
#include "functions/generic_set_out.hpp"
#include "functions/species_set_out.hpp"
#include "functions/vector_out.hpp"
#include "functions/vector_int_out.hpp"
#include <Eigen/Eigenvalues>
#include <Eigen/SVD>
#include <unsupported/Eigen/MatrixFunctions>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>

using namespace std;
using Eigen::MatrixXd;
using Eigen::SelfAdjointEigenSolver;
using Eigen::ComplexEigenSolver;

typedef set<intptr_t, less<intptr_t> > int_set1;
typedef vector <intptr_t> vecint;
typedef vector <double> vecdouble;
typedef pair<int,int> Edge;

typedef boost::mt19937                     ENG;    // Mersenne Twister
typedef boost::normal_distribution<double> DIST;   // Normal Distribution
typedef boost::variate_generator<ENG,DIST> GEN;    // Variate generator

//***************************************************************
//custom random no. generator for vectors
class MyRand
{
public:
  unsigned long operator() (unsigned long n_ );
};

unsigned long
MyRand::operator() (unsigned long n_ )
{
  return rand() % n_;
}
//***************************************************************

//***************************************************************
int main(int argc, char *argv[])
{

  //initialize random number generators
  srand(time(0));
  //***************************************************************

  //format for matrix output
  IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");

  //get user input and parameterize guilds
  intptr_t no_nodes;
  no_nodes = atoi(argv[1]);
  //read metanetwork matrix
  ifstream matrix_file;
  double matrix_num;
  //open existing matrix file specified by user
  do
    {
      //filename
      const char *matrix_name = argv[2];
      matrix_file.open(matrix_name);
    }
  while(!matrix_file.is_open());
  intptr_t array_size1 = no_nodes;
  double temp_matrix[array_size1];
  intptr_t temp_counter1 = 0;
  //read in values into temp. array
  while( matrix_file >> matrix_num )
    {
      temp_matrix[temp_counter1] = matrix_num;
      temp_counter1++;
    }
  //now write into proper matrix and display
  std::cout << "\n";
  double network_matrix[no_nodes][3];
  temp_counter1 = 0;
  for(intptr_t i = 0; i < no_nodes; i++)
    {
      for(intptr_t j = 0; j < 3; j++)
	{
	  network_matrix[i][j] = temp_matrix[temp_counter1];
	  temp_counter1++;
	  std::cout << network_matrix[i][j] << " ";
	}
      std::cout << endl;
    }
 

  //read metanetwork adjacency matrix
  ifstream matrix2_file;
  double matrix2_num;
  //open existing matrix file specified by user
  do
    {
      const char *matrix2_name = argv[3];
      matrix2_file.open(matrix2_name);
    }
  while(!matrix2_file.is_open());
  intptr_t temp_matrix1b[no_nodes*no_nodes];
  intptr_t temp_counter2 = 0;
  while( matrix2_file >> matrix2_num )
    {
      temp_matrix1b[temp_counter2] = static_cast<intptr_t>(matrix2_num);
      temp_counter2++;
    }
  //now write into proper matrix and display
  MatrixXd M(no_nodes,no_nodes);
  intptr_t temp_counter3 = 0;
  for(intptr_t i = 0; i < no_nodes; i++)
    for(intptr_t j = 0; j < no_nodes; j++)
      {
	M(i,j) = temp_matrix1b[temp_counter3];
	temp_counter3++;
      }
  std::cout << M.format(CleanFmt) << "\n";
 

}//close main()
