#ifndef MATLAB_HPP_
#define MATLAB_HPP_
#include "matlab.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <matlab.hpp>
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>
#include <numeric>
namespace Matlab {
    template <typename  T>
    class Vector{
    public:

        Vector(const Vector<T>&) = default;

        Vector(std::size_t n = 3) {
            for (std::size_t i = 0; i < n; ++i) {
                v_.push_back(0);
            }
        }

        Vector(std::vector<T> v){
    for (T i : v) {
        v_.push_back(i);
    }
}

        T get_elem(std::size_t pos) const { return v_[pos]; }

        void set_elem(std::size_t pos, T val) { v_[pos] = val; }

        const T &operator[](std::size_t pos) const { return v_[pos]; }

        T &operator[](std::size_t pos) { return v_[pos]; }

      typename  std::vector<T>::iterator begin() {
            return v_.begin();
        }
        typename std::vector<T>::iterator end() {

            return v_.end();
        }

        typename  std::vector<T>::const_iterator cbegin() const {
            return v_.cbegin();
        }

        typename  std::vector<T>::const_iterator cend() const {
            return v_.cend();
        }

        std::size_t sum() const{
 std::size_t a=0;
    return std::accumulate(v_.cbegin(),v_.cend(),a);
}

std::size_t norm() const{
        std::size_t sum_of_squares = 0;
        return static_cast<size_t>(sqrt(std::accumulate(v_.cbegin(), v_.cend(), sum_of_squares, [](T temp_value, const auto&v_){return temp_value + pow(v_, 2);})));

}
        std::size_t size() const { return v_.size(); }

    private:
        std::vector<T> v_;


    };
    template<typename T>
    void print_vector(Vector<T>&  v)  {
        for (T i : v) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    template<typename T>
    std::string to_string(const Vector<T>& v){
        std::ostringstream print;
        print<<"[ ";
        for(auto i=v.cbegin();i!=v.cend();++i){
            print<<(*i)<<((i!=v.cend()-1)? ", " :" ");
        }
        print<<"]";
        return print.str();
    }
template<typename T>
    Vector<T>add_vectors(const Vector<T>&v1, const Vector<T>&v2){
        if(v1.size()!=v2.size()){
            throw std::invalid_argument("Different size of vectors: ("+  std::to_string(v1.size()) + " and " +std::to_string(v2.size())+")");
        }
        Vector<T>v_sum= Vector<T>(v1.size());
        std::transform(v1.cbegin(),v1.cend(),v2.cbegin(),v_sum.begin(),std::plus<>());
        return v_sum;
    }






template <typename T>
    class Matrix {
        std::vector<Vector<T>> matrix;
    public:
        std::size_t size() const { return matrix.size(); }

        Matrix(const Matrix &) = default;

        explicit Matrix(const std::vector<std::vector<T>> &m){
            std::copy(m.begin(), m.end(), std::back_inserter(matrix));


        }

        Matrix(std::size_t rows, std::size_t cols){
            for(size_t i=0;i<rows;i++){
                matrix.push_back(Vector<T>(cols));
            }
        }

        const Vector<T>&operator[](std::size_t pos) const { return matrix[pos]; }

        Vector<T>&operator[](std::size_t pos) { return matrix[pos]; }

        typename   std::vector<Vector<T>>::const_iterator cbegin() const { return matrix.cbegin(); }

        typename    std::vector<Vector<T>>::const_iterator cend() const { return matrix.cend(); }

        typename    std::vector<Vector<T>>::iterator begin() { return matrix.begin(); }

        typename    std::vector<Vector<T>>::const_iterator begin() const { return matrix.cbegin(); }

        typename    std::vector<Vector<T>>::iterator end() { return matrix.end(); }

        typename    std::vector<Vector<T>>::const_iterator end() const { return matrix.cend(); }

        std::size_t norm() const{
            std::size_t previous=0;
            return std::accumulate(matrix.cbegin(),matrix.cend(),previous,[](T temp_value,const auto& v){return temp_value+ v.norm();});

        }

        std::size_t sum() const {
            std::size_t sum=0;
            return std::accumulate(matrix.cbegin(),matrix.cend(),sum,[](T i,const auto& v){return i+ v.sum();});
        }

    };




template<typename T>
    std::string to_string(const Matrix<T>& m){
        std::ostringstream print;
        print<<"[\n";

        for (auto i=m.cbegin();i!=m.cend();++i) {
            bool isend=(i!=m.cend()-1);
            print<<to_string(*i)<<((isend)?",\n":"\n");
        }
        print<<"]";
        return  print.str();
    }
    template<typename T>
    Matrix<T> add_matrix(const Matrix<T> &m1, const Matrix<T> &m2){

        Matrix<T> new_matrix(m1);
        std::transform(m2.cbegin(),m2.cend(),m1.cbegin(),new_matrix.begin(),[](const auto& v1,const auto& v2){return add_vectors(v1,v2);});
        return new_matrix;
    }
    template<typename T>
    std::string was_exception_raised_when_adding_vectors(const Vector<T>& v1, const Vector<T>& v2){
        try{
            auto v_sum=Matlab::add_vectors(v1,v2);
        } catch (const std::invalid_argument& error){
            return error.what();
        }
        return"";
    }
}
#endif /* MATLAB_HPP_ */
