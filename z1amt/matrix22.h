//
// Created by eric on 17/10/18.
//

#ifndef Z1DAMT_MATRIX22_H
#define Z1DAMT_MATRIX22_H

#include <boost/io/ios_state.hpp>
namespace boost {
    namespace units {
        template <class Y>
        class matrix22 {
        public:
            typedef matrix22<Y> this_type;
            typedef Y value_type;

            constexpr matrix22(
                    const value_type xx_,
                    const value_type xy_,
                    const value_type yx_,
                    const value_type yy_) :
            xx_(xx_),
            xy_(xy_),
            yx_(yx_),
            yy_(yy_) {}

            constexpr matrix22(const this_type& source):
            xx_(source.xx_),
            xy_(source.xy_),
            yx_(source.yx_),
            yy_(source.yy_) {}

            constexpr this_type& operator=(const this_type& source)
            {
                if (this == &source) return *this;

                xx_=source.xx_;
                xy_=source.xy_;
                yx_=source.yx_;
                yy_=source.yy_;

                return *this;
            }

            constexpr value_type xx() const {return xx_;}
            constexpr value_type xy() const {return xy_;}
            constexpr value_type yx() const {return yx_;}
            constexpr value_type yy() const {return yy_;}


        private:
            value_type xx_, xy_, yx_, yy_;
        };
    }
}
#if BOOST_UNITS_HAS_BOOST_TYPEOF

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::units::matrix22, 1)

#endif

#endif //Z1DAMT_MATRIX22_H
