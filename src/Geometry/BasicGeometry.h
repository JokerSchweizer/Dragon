#ifndef POINT_H
#define POINT_H
#include <vector>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/StdVector>
#include <Eigen/Eigenvalues> 
#include <Eigen/Eigen>
#include "sophus/se3.hpp"
#include "IO/ConsoleColor.h"
#include <iostream>
#define EPS 1e-6
namespace dragon
{
namespace geometry
{
#ifdef USING_FLOAT64
    typedef double scalar;
#else
    typedef float scalar;
#endif

    typedef Eigen::Matrix<scalar, 2, 1> Point2;
    typedef Eigen::Matrix<scalar, 3, 1> Point3;
    typedef Eigen::Matrix<scalar, 2, 1> Vector2;
    typedef Eigen::Matrix<scalar, 3, 1> Vector3;
    typedef Eigen::Matrix<scalar, 4, 1> Vector4;
    typedef Eigen::Matrix<scalar, 6, 1> Vector6;

    typedef Eigen::Matrix<scalar, 2, 2> Matrix2;
    typedef Eigen::Matrix<scalar, 3, 3> Matrix3;
    typedef Eigen::Matrix<scalar, 4, 4> Matrix4;
    typedef Eigen::Matrix<scalar, 6, 6> Matrix6;
    typedef Eigen::Matrix<scalar, 3, 6> Matrix3X6;
    template <int T>
        using Vector = Eigen::Matrix<scalar, T, 1>;

    typedef Eigen::Matrix<int, 2, 1> Point2i;
    typedef Eigen::Matrix<int, 3, 1> Point3i;
    typedef Eigen::Matrix<unsigned int, 2, 1> Point2ui;
    typedef Eigen::Matrix<unsigned int, 3, 1> Point3ui;

    typedef std::vector<Point3i, Eigen::aligned_allocator<Point3i> > Point3iList;
    typedef std::vector<Point3ui, Eigen::aligned_allocator<Point3ui> > Point3uiList;

    typedef std::vector<Point2, Eigen::aligned_allocator<Point2> > Point2List;
    typedef std::vector<Point3, Eigen::aligned_allocator<Point3> > Point3List; 
    template <int T>
        using PointList = std::vector<Eigen::Matrix<scalar, T, 1>, 
            Eigen::aligned_allocator<Eigen::Matrix<scalar, T, 1>>>;

    typedef std::vector<Matrix4, Eigen::aligned_allocator<Matrix4> > Mat4List;
    typedef Matrix4 TransformationMatrix;
    //lie group and lie algebra
    //SE3 and se3
    typedef Vector6 Se3;
    typedef Vector3 So3;
    typedef Matrix4 SE3;
    typedef Matrix3 SO3;
    typedef Mat4List SE3List;
    Vector6 SE3ToSe3(const Matrix4 &input);
    Matrix4 Se3ToSE3(const Vector6 &input);
    void TransformPoints(const Matrix4 &T, Point3List &points);
    Point3 TransformPoint(const Matrix4 &T, const Point3 &point);
    void TransformNormals(const Matrix4 &T, Point3List &normals);
    double ComputeTriangleArea(const Point3 &a, const Point3 &b, const Point3 &c);
    double inline cot(double a) {return 1 / std::tan(a);}
    // compute the circum center of triangle
    Point3 CircumCenter(const Point3 &a, const Point3 &b, const Point3 &c);
    int TriangleType(const Point3 &a, const Point3 &b, const Point3 &c);
    double AngleOfVector(const Vector3 &a, const Vector3 &b);
    struct PairHasher
    {
        template<class T1, class T2>
        std::size_t operator() (const std::pair<T1, T2>& p) const
        {
            // auto h1 = std::hash<T1>{}(p.first);
            // auto h2 = std::hash<T2>{}(p.second);
            // return h1 ^ h2;
            static constexpr size_t p1 = 73856093;
            static constexpr size_t p2 = 19349663;
            return ( p.first * p1 ^ p.second * p2 );
        }
    };
}
}
#endif