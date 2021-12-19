#include "MayhemUtil.hpp"

Mayhem::Utils::UUID::UUID() {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<int> dist(0, 15);

    const char *v = "0123456789abcdef";
    const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

    for (int i = 0; i < 16; i++) {
        if (dash[i]) m_id += "-";
        m_id += v[dist(rng)];
        m_id += v[dist(rng)];
    }
}

