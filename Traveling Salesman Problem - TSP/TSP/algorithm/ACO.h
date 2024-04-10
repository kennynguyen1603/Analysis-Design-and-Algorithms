// #ifndef ACO_H // Kiểm tra xem ACO_H đã được định nghĩa trước đó hay chưa để tránh định nghĩa lại
// #define ACO_H // Định nghĩa ACO_H nếu nó chưa được định nghĩa

// #include "../models/DistanceMatrix.h" // Bao gồm tiêu đề của lớp DistanceMatrix để sử dụng trong ACO
// #include <vector>                     // Bao gồm thư viện vector của STL để sử dụng container vector

// class ACO // Khai báo lớp ACO
// {
// public:
//     // Constructor của lớp ACO nhận vào các tham số cần thiết cho thuật toán
//     ACO(const DistanceMatrix &matrix, int numAnts, int maxIterations, double alpha, double beta, double evaporationRate, double initialPheromone);
//     void solve(); // Phương thức để bắt đầu giải quyết TSP sử dụng ACO

// private:
//     const DistanceMatrix &matrix;                // Tham chiếu đến ma trận khoảng cách giữa các thành phố
//     int numAnts;                                 // Số lượng kiến sử dụng trong thuật toán
//     int maxIterations;                           // Số lần lặp tối đa cho thuật toán
//     double alpha;                                // Hệ số ảnh hưởng của pheromone
//     double beta;                                 // Hệ số ảnh hưởng của visibility (nghịch đảo của khoảng cách)
//     double evaporationRate;                      // Tỷ lệ bay hơi của pheromone
//     double initialPheromone;                     // Mức pheromone khởi tạo ban đầu trên các cạnh
//     vector<vector<double>> pheromones; // Ma trận chứa mức pheromone trên các cạnh giữa các thành phố

//     // Phương thức khởi tạo ma trận pheromone với mức pheromone ban đầu
//     void initializePheromones();
//     // Chọn thành phố tiếp theo dựa trên xác suất tính từ pheromone và visibility
//     int selectNextCity(int ant, const vector<bool> &visited, int currentCity);
//     // Tính xác suất chọn thành phố tiếp theo
//     double calculateProbability(int ant, int city, const vector<bool> &visited);
//     // Tính tổng độ dài của một lộ trình
//     double calculatePathLength(const vector<int> &path);
//     // Cập nhật mức pheromone dựa trên chất lượng của các lộ trình tìm được
//     void updatePheromones(const vector<vector<int>> &paths);
// };

// #endif // ACO_H  // Kết thúc kiểm tra điều kiện tiền xử lý

// Trong file ACO.h
#ifndef ACO_H
#define ACO_H

#include "../models/DistanceMatrix.h"
#include <vector>

class ACO
{
public:
    ACO(const DistanceMatrix &matrix, int numAnts, int maxIterations, double alpha, double beta, double evaporationRate, double initialPheromone);
    void solve();

private:
    const DistanceMatrix &matrix;
    int numAnts;
    int maxIterations;
    double alpha;
    double beta;
    double evaporationRate;
    double initialPheromone;
    vector<vector<double>> pheromones;

    void initializePheromones();
    int selectNextCity(int ant, const vector<bool> &visited, int currentCity, const vector<vector<int>> &paths);
    double calculateProbability(int ant, int city, const vector<bool> &visited, const vector<vector<int>> &paths);
    double calculatePathLength(const vector<int> &path);
    void updatePheromones(const vector<vector<int>> &paths);
};

#endif // ACO_H
