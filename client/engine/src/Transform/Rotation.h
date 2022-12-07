#pragma once

namespace LM {

    class Rotation {
    public:
        Rotation(float angle) : m_Angle(angle) { }

        Rotation& operator+=(const Rotation& other) {
            return *this;
        }

        friend Rotation operator+(Rotation left, Rotation right) {
            return left; 
        }

        friend Rotation operator+(Rotation left, float right) {
            return left;
        }

        friend Rotation operator+(float left, Rotation right) {
            return left;
        }

        Rotation& operator-=(const Rotation& other) {
            return *this;
        }

        friend Rotation operator-(Rotation left, Rotation right) {
            return left;
        }

        friend Rotation operator-(Rotation left, float right) {
            return left;
        }

        friend Rotation operator-(float left, Rotation right) {
            return left;
        }

        Rotation& operator/=(const Rotation& other) {
            return *this;
        }

        friend Rotation operator/(Rotation left, Rotation right) {
            return left;
        }

        friend Rotation operator/(Rotation left, float right) {
            return left;
        }

        friend Rotation operator/(float left, Rotation right) {
            return left;
        }

        Rotation& operator*=(const Rotation& other) {
            return *this;
        }

        friend Rotation operator*(Rotation left, Rotation right) {
            return left;
        }

        friend Rotation operator*(Rotation left, float right) {
            return left;
        }

        friend Rotation operator*(float left, Rotation right) {
            return left;
        }

        operator float() const { return m_Angle; }

        float operator()() const { return m_Angle; }
    private:
        float m_Angle;
    };

}
