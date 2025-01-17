#include <iostream>
#include <random>
#include <cmath>

bool is_prime(unsigned n) {
    if (n < 2) return false;

    for (unsigned i = 2; i < sqrt(n); ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int prime() {
    std::random_device dev;
    std::mt19937 rnd(dev());
    std::uniform_int_distribution<unsigned> dist(0, 32767);
    unsigned random = dist(rnd);
    while (!is_prime(random))
    {
        --random;
    }
    return random;
}

int naxozdenie(unsigned d, unsigned phi, unsigned e, unsigned n) {
    for (unsigned long long k = 0; k < n; k++) { 
        if ((1 + k * phi) % e == 0) {
            d = (1 + k * phi) / e;
            return d;
        }
    }
}

unsigned stepen(unsigned e, short m, unsigned n) {
    unsigned long long pred = 1;
    for (int k = 0; k < e; k++) {
        pred = (pred * m) % n;
    }
    return pred;
}

unsigned rashif(unsigned d, unsigned n, unsigned c) {
    unsigned long long pred = 1;
    for (int k = 0; k < d; k++) {
        pred = (pred * c) % n;

    }
    return pred;
}

int main()
{
    setlocale(0, "");
//открытый ключ
    unsigned p = prime(), q = prime();
    unsigned n = p * q;
    unsigned phi = (p - 1) * (q - 1);
    unsigned e = 2707;
    unsigned d = 0;

    std::string str;
    d = naxozdenie(d, phi, e, n);
    union soob {
        char mess[2];
        short m;
    };
    soob s;
    std::cout << "Введите сообщение: ";
    std::cin >> str;
    s.mess[0] = str[0];
    s.mess[1] = str[1];

    unsigned c = stepen(e, s.m, n);
    s.m = rashif(d, n, c);

    std::cout << s.mess[0]<<s.mess[1];

    return 0;
}
