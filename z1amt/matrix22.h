//
// Created by eric on 17/10/18.
//

#ifndef Z1DAMT_MATRIX22_H
#define Z1DAMT_MATRIX22_H

#include <boost/io/ios_state.hpp>
#include <complex>
#include <ostream>

namespace boost {
    namespace units {
        template <class Y>
        class matrix22 {
        public:
            typedef matrix22<Y> this_type;
            typedef Y value_type;

            /*constexpr*/ matrix22(
                    const value_type xx_,
                    const value_type xy_,
                    const value_type yx_,
                    const value_type yy_) :
                    xx_(xx_),
                    xy_(xy_),
                    yx_(yx_),
                    yy_(yy_) {}

            /*constexpr*/ matrix22(const this_type& source):
                    xx_(source.xx_),
                    xy_(source.xy_),
                    yx_(source.yx_),
                    yy_(source.yy_) {}

            /*constexpr*/ this_type& operator=(const this_type& source)
            {
                if (this == &source) return *this;

                xx_=source.xx_;
                xy_=source.xy_;
                yx_=source.yx_;
                yy_=source.yy_;

                return *this;
            }

            /*constexpr*/ operator value_type() const {return value_type{};} // ???

            /*constexpr*/ this_type& value() const { return matrix22<value_type >(xx_, xy_, yx_, yy_);}
            /*constexpr*/ value_type xx() const {return xx_;}
            /*constexpr*/ value_type xy() const {return xy_;}
            /*constexpr*/ value_type yx() const {return yx_;}
            /*constexpr*/ value_type yy() const {return yy_;}

            /*constexpr*/ this_type& operator*=(const value_type& val)
            {
                xx_*=val;
                xy_*=val;
                yx_*=val;
                yy_*=val;
                return *this;
            }

            /*constexpr*/ this_type& operator/=(const value_type& val)
            {
                xx_/=val;
                xy_/=val;
                yx_/=val;
                yy_/=val;
                return *this;
            }

            /*constexpr*/ this_type& transpose() const
            {
                return this_type(xx_, yx_, xy_, yy_);
            }

            /*constexpr*/ this_type& adjoint() const
            {
                return std::conj(this_type(xx_, yx_, xy_, yy_));
            }

            /*constexpr*/ value_type det() const
            {
                return (xx_*yy_ - xy_*yx_);
            }



            /*constexpr*/ this_type& operator+=(const this_type& /*source*/);
            /*constexpr*/ this_type& operator-=(const this_type& /*source*/);
            /*constexpr*/ this_type& operator*=(const this_type& /*source*/);
            /*constexpr*/ this_type& operator/=(const this_type& /*source*/);

            friend std::ostream &operator<<(std::ostream &os, const matrix22 &matrix22) {
                boost::io::ios_precision_saver precision_saver(os);
                boost::io::ios_flags_saver flags_saver(os);
                os << "[xx_: " << matrix22.xx_ << " xy_: " << matrix22.xy_ << "\n yx_: " << matrix22.yx_ << " yy_: "
                   << matrix22.yy_ << "]";
                return os;
            }

        private:
            value_type xx_, xy_, yx_, yy_;
        };
    }
}
#if BOOST_UNITS_HAS_BOOST_TYPEOF

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::units::matrix22, 1)

#endif


namespace boost{
    namespace units{
        template<class Y>
        inline
        /*constexpr*/
        matrix22<Y>&
        matrix22<Y>::operator+=(const this_type& source) {
            xx_+=source.xx_;
            xy_+=source.xy_;
            yx_+=source.yx_;
            yy_+=source.yy_;
            return *this;
        }

        template<class Y>
        inline
        /*constexpr*/
        matrix22<Y>&
        matrix22<Y>::operator-=(const this_type& source) {
            xx_-=source.xx_;
            xy_-=source.xy_;
            yx_-=source.yx_;
            yy_-=source.yy_;
            return *this;
        }

        template<class Y>
        inline
        /*constexpr*/
        matrix22<Y>&
        matrix22<Y>::operator*=(const this_type& source) {
            this_type tmp{{xx_*source.xx_ + xy_*source.yx_},
                          {xx_*source.xy_ + xy_*source.yy_},
                          {yx_*source.xx_ + yy_*source.yx_},
                          {yx_*source.xy_ + yy_*source.yy_}};
            xx_=tmp.xx_;
            xy_=tmp.xy_;
            yx_=tmp.yx_;
            yy_=tmp.yy_;
            return *this;
        }

        template<class Y>
        inline
        /*constexpr*/
        matrix22<Y>&
        matrix22<Y>::operator/=(const this_type& source) {

            value_type inv_det{1./(xx_*yy_ - xy_*yx_)};
            this_type inv{ this_type{yy_, -yx_, -xy_, xx_}*=inv_det };

            this_type res{{xx_*inv.xx_ + xy_*inv.yx_},
                          {xx_*inv.xy_ + xy_*inv.yy_},
                          {yx_*inv.xx_ + yy_*inv.yx_},
                          {yx_*inv.xy_ + yy_*inv.yy_}};
            xx_=res.xx_;
            xy_=res.xy_;
            yx_=res.yx_;
            yy_=res.yy_;
            return *this;
        }

        // value_type op matrix22 :: note: product by scalar must be symmetric!!!
        template <class Y>
        inline
        /*constexpr*/
        matrix22<Y> operator*(Y lhs, const matrix22<Y>& rhs)
        {
            return (matrix22<Y>(rhs)*=lhs);
        }

        template <class Y>
        inline
        /*constexpr*/
        matrix22<Y> operator/(Y lhs, const matrix22<Y>& rhs)
        {
            return (matrix22<Y>(rhs)/=lhs);
        }

        // matrix22 op value_type
        template <class Y>
        inline
        /*constexpr*/
        matrix22<Y> operator*(const matrix22<Y>& lhs, Y rhs)
        {
            return (matrix22<Y>(lhs)*=rhs);
        }

        template <class Y>
        inline
        /*constexpr*/
        matrix22<Y> operator/(const matrix22<Y>& lhs, Y rhs)
        {
            return (matrix22<Y>(lhs)/=rhs);
        }

        // matrix22 op matrix22
        template <class Y>
        inline
        /*constexpr*/
        matrix22<Y> operator+(const matrix22<Y>& lhs, const matrix22<Y>& rhs)
        {
            return (matrix22<Y>(lhs)+=rhs);
        }

        template <class Y>
        inline
        /*constexpr*/
        matrix22<Y> operator-(const matrix22<Y>& lhs, const matrix22<Y>& rhs)
        {
            return (matrix22<Y>(lhs)-=rhs);
        }

        template <class Y>
        inline
        /*constexpr*/
        matrix22<Y> operator*(const matrix22<Y>& lhs, const matrix22<Y>& rhs)
        {
            return (matrix22<Y>(lhs)*=rhs);
        }

        template <class Y>
        inline
        /*constexpr*/
        matrix22<Y> operator/(const matrix22<Y>& lhs, const matrix22<Y>& rhs)
        {
            return (matrix22<Y>(lhs)/=rhs);
        }




    }
}
#endif //Z1DAMT_MATRIX22_H
