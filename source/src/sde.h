#pragma once
#include <memory>
#include <Eigen/Core>


namespace sde {

template <typename T, std::size_t Size>
using vector_type = Eigen::Matrix<T, Size, 1>;

template <typename T, std::size_t Size>
using lifted_type = vector_type<T, Size + Size * Size>;
 
template <typename T, typename U = T>
using function_type = std::function<U (const T&)>;

template <typename T, typename U = T>
using func_ptr_type = std::shared_ptr<const function_type<T, U>>;


                      
template <typename T, std::size_t Size>
class Tensor {
    /// gamma(i,j,k) = gamma_{i, j}^k
public:
    Tensor() {
        for (int i = 0; i < Size; ++i) {
            Eigen::Matrix<T, Size, Size> mat;
            for (int i = 0; i < Size; ++i) {
                for (int j = 0; j < Size; ++j) {
                    mat(i, j) = T{0};
                }
            }
            _data.emplace_back(mat);
        }
    }
    T& operator()(int i, int j, int k) {
        return _data[k](i, j);
    }
    const T& operator()(int i, int j, int k) const {
        return _data[k](i, j);
    }

    Tensor operator +(const Tensor& other) const {
        Tensor<T, Size> ret = *this;
        for (int k = 0; k < Size; ++k) {
            ret._data[k] += other._data[k];
        }
        return ret;
    }
    Tensor operator -(const Tensor& other) const {
        Tensor<T, Size> ret = *this;
        for (int k = 0; k < Size; ++k) {
            ret._data[k] -= other._data[k];
        }
        return ret;
    }

    Tensor operator /(const double& other) const {
        Tensor<T, Size> ret = *this;
        for (int k = 0; k < Size; ++k) {
            ret._data[k] /= other;
        }
        return ret;
    }



private:
    std::vector<Eigen::Matrix<T, Size, Size>> _data;
};


}