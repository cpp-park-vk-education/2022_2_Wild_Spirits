#pragma once

namespace LM {

    class Rotation {
    public:
        Rotation(float angle) : m_Angle(angle) { }

        Rotation& operator+=(const Rotation& other) {
            m_Angle += other.m_Angle;
            return *this;
        }

        friend Rotation operator+(Rotation left, Rotation right) {
            left += right;
            return left; 
        }

        friend Rotation operator+(Rotation left, float right) {
            left.m_Angle += right;
            return left;
        }

        friend Rotation operator+(float left, Rotation right) {
            return Rotation(left + right.m_Angle);
        }

        Rotation& operator-=(const Rotation& other) {
            m_Angle -= other.m_Angle;
            return *this;
        }

        friend Rotation operator-(Rotation left, Rotation right) {
            left -= right;
            return left;
        }

        friend Rotation operator-(Rotation left, float right) {
            left.m_Angle -= right;
            return left;
        }

        friend Rotation operator-(float left, Rotation right) {
            return Rotation(left - right.m_Angle);
        }

        Rotation& operator/=(const Rotation& other) {
            m_Angle /= other.m_Angle;
            return *this;
        }

        friend Rotation operator/(Rotation left, Rotation right) {
            left /= right;
            return left;
        }

        friend Rotation operator/(Rotation left, float right) {
            left.m_Angle /= right;
            return left;
        }

        friend Rotation operator/(float left, Rotation right) {
            
            return Rotation(left / right.m_Angle);
        }

        Rotation& operator*=(const Rotation& other) {
            m_Angle *= other.m_Angle;
            return *this;
        }

        friend Rotation operator*(Rotation left, Rotation right) {
            left *= right;
            return left;
        }

        friend Rotation operator*(Rotation left, float right) {
            left.m_Angle *= right;
            return left;
        }

        friend Rotation operator*(float left, Rotation right) {

            return Rotation(left / right.m_Angle);
        }

        operator float() const { return m_Angle; }

        float operator()() const { return m_Angle; }
    private:
        float m_Angle;
    };

}
