//
// Created by Eric Mandolesi on 30/10/2018.
//

#ifndef Z1DAMT_D1NODE_H
#define Z1DAMT_D1NODE_H

#include <UnitsSetup.h>
#include <ostream>

class d1node {
public:

private:
    length z_;
    conductivity sigma_; // sigma mean (s_h + s_l)/2
    double logr_; // log10(sigma_low/sigma_high) -3<r_<=0
    angle beta_;
public:
    d1node(length z, conductivity sigma_mean, double ratio, angle beta) :
    z_(z),
    sigma_(sigma_mean),
    logr_(log10(ratio)), // the interface asks for ratio but the internal representation deals with log10(ratio)
    beta_ (beta) {}

    conductivity sigma_h() const {
return sigma_;
    }

    // relational operators will allow to put these in a std::set
    bool operator<(const d1node &rhs) const {
        return z_ < rhs.z_;
    }

    bool operator<=(const d1node &rhs) const {
        return !(rhs < *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const d1node &node) {
        os << "z_: " << node.z_ << " sigma_: " << node.sigma_ << " r_: " << pow(10.,node.logr_) << " beta_: " << node.beta_;
        return os;
    }

};


#endif //Z1DAMT_D1NODE_H
