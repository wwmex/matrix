#include <iostream>
#include <cstddef>

void remove_matrix(int** matrix, size_t rows){
  for(size_t i =0; i < rows; i++){
    delete[] matrix[i];
  }
  delete[] matrix;
}

int** create_matrix(size_t rows, size_t columns){
  int** matrix = nullptr;
  size_t a = 0;
  try{
    matrix = new int*[rows];
    for(; a < rows; a++){
      matrix[a] = new int[columns];
    }
    return matrix;
  } catch(...){
      remove_matrix(matrix, a);
      return nullptr;
  }
}

int main(){
  size_t n = 0;
  size_t m = 0;

  std::cout << "колличество сток матрицы: \n";
  std::cin >> n;
  if(std::cin.fail()){
    std::cerr << "не удалось ввести\n";
    return 1;
  }

  std::cout << "колличество столбцов матрицы: \n";
  std::cin >> m;
  if(std::cin.fail()){
    std::cerr << "не удалось ввести\n";
    return 1;
  }

  int** matrix = create_matrix(n, m);
  if(matrix == nullptr){
    std::cerr << "не удалось выделить память\n";
    return 2;
  }

  std::cout << "ввод элементов: \n";
  for(size_t i = 0; i <n; i++){
    for(size_t j = 0; j < m; j++){
      std::cin >> matrix[i][j];
      if(std::cin.fail()){
        std::cerr << "не удалось записать данные\n";
        remove_matrix(matrix, n);
        return 1;
      }
    }
  }

  int** b = create_matrix(m,n);
  if(b == nullptr){
    std::cerr << "ошибка распределения памяти\n";
    remove_matrix(matrix, n);
    return 2;
  }

  for(size_t i = 0; i < n; i++){
    for(size_t j = 0; j < m; j++){
      b[j][i] = matrix[i][j];
    }
  }

  std::cout << "транспонированная матрица: \n";
  for(size_t i = 0; i < m; i++){
    for(size_t j = 0; j < n; j++){
      std::cout << b[i][j] << " ";
    }
    std::cout << "\n";
  }

  remove_matrix(matrix, n);
  remove_matrix(b, m);
  return 0;
}
