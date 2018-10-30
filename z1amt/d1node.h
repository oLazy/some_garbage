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
    double r_;
    angle beta_;
public:
    d1node(length z, conductivity sigma_mean, double ratio, angle beta) :
    z_(z),
    sigma_(sigma_mean),
    r_(ratio),
    beta_ (beta) {}

    // relational operators will allow to put these in a std::set
    bool operator<(const d1node &rhs) const {
        return z_ < rhs.z_;
    }

    bool operator<=(const d1node &rhs) const {
        return !(rhs < *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const d1node &node) {
        os << "z_: " << node.z_ << " sigma_: " << node.sigma_ << " r_: " << node.r_ << " beta_: " << node.beta_;
        return os;
    }

};


#endif //Z1DAMT_D1NODE_H
