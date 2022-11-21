#pragma once

namespace LM {

    class Rotation {
    public:
        Rotation(float angle) : m_Angle(angle) { }

        Rotation& operator+=(const Rotation& other) {
            return *this;
        }

        friend Rotation operator+(Rotation left, const Rotation right) {
            return left; 
        }

        Rotation& operator-=(const Rotation& other) {
            return *this;
        }

        friend Rotation operator-(Rotation left, const Rotation right) {
            return left;
        }

        Rotation& operator/=(const Rotation& other) {
            return *this;
        }

        friend Rotation operator/(Rotation left, const Rotation right) {
            return left;
        }

        Rotation& operator*=(const Rotation& other) {
            return *this;
        }

        friend Rotation operator*(Rotation left, const Rotation right) {
            return left;
        }

        operator float() { return m_Angle; }
    private:
        float m_Angle;
    };

}
