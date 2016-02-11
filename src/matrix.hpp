#ifndef __MATRIX2D_HPP__
#define __MATRIX2D_HPP__
#include <vector>

template<typename T>
class Matrix2D {
    
    public: 
        Matrix2D(int h, int w):                         vec_(w*h), width_(w), height_(h){};
        Matrix2D(const std::vector<T> &v,int w, int h): vec_(v), width_(w), height_(h){}; 
        Matrix2D(const Matrix2D<T> &m):                 vec_(m.vec_),width_(m.width_), height_(m.height_){};
        Matrix2D(Matrix2D&& m):                         vec_(std::move(m.vec_)), width_(m.width_), height_(m.height_){};
        Matrix2D(std::vector<T> &&v,int w, int h):      vec_(v), width_(w), height_(h){}; 
        Matrix2D():vec_(),width_(0),height_(0){};

        Matrix2D<T>& operator=(const Matrix2D<T>& mat){
            vec_    = mat.vec_;
            width_  = mat.width_;
            height_ = mat.height_;
            return *this;
        }   
        Matrix2D<T>& operator=(Matrix2D<T>&& mat){
            vec_    = std::move(mat.vec_);
            width_  = mat.width_;
            height_ = mat.height_;
            return *this;
        }   
    
        T&  operator()(int i, int j) {return vec_[i*width_+j];}
        T  operator()(int i, int j) const {return vec_[i*width_+j];}
    
        
        int width()  const {return width_;}
        int height() const {return height_;}
        int size()   const {return vec_.size();}        

    private:
        std::vector<T> vec_;
        int width_;
        int height_;
};

#endif /*__MATRIX2D_HPP__*/
