#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

template <typename T>
void print(const T &parameter);
template <typename T>
void print_part(const T &param);
void filter(std::vector<std::array<int, 4>> &ip_pool, int match);
void filter(std::vector<std::array<int, 4>> &ip_pool, int match_1, int match_2);
void filter_any(std::vector<std::array<int, 4>> &ip_pool, int match);

int main()
{
    try
    {
        std::vector<std::vector<std::string>> ip_pool;
        // вектор из ip адресов в hex представлении
        std::vector<std::array<int, 4>> ip_pool_int;

        for (std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort

        // переводим строку с ip адресом в числовое представление
        for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            std::array<int, 4> ip_array{
                std::stoi(ip->at(0)),
                std::stoi(ip->at(1)),
                std::stoi(ip->at(2)),
                std::stoi(ip->at(3))};

            ip_array.size();

            ip_pool_int.push_back(std::move(ip_array));
        }

        ip_pool.clear();

        // сортировка ip адресов в hex формате производится лексикографически
        // сортировка по убыванию
        std::sort(ip_pool_int.begin(), ip_pool_int.end(), [](std::array<int, 4> a, std::array<int, 4> b)
                  { return a > b; });

        // выводим результат
        print(ip_pool_int);

        filter(ip_pool_int, 1);
        filter(ip_pool_int, 46, 70);
        filter_any(ip_pool_int, 46);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

template <typename T>
void print(const T &parameter)
{
    for (auto ip = parameter.cbegin(); ip != parameter.cend(); ++ip)
    {
        print_part(*ip);
    }
}

template <typename T>
void print_part(const T &param)
{
    for (auto ip_part = param.cbegin(); ip_part != param.cend(); ++ip_part)
    {
        if (ip_part != param.cbegin())
        {
            std::cout << ".";
        }
        std::cout << *ip_part;
    }
    std::cout << std::endl;
}

void filter(std::vector<std::array<int, 4>> &ip_pool, int match)
{
    std::for_each(begin(ip_pool), end(ip_pool), [&match](auto &el)
                  {
		if(el.at(0) == match){
			print_part(el);
		} });
}

void filter(std::vector<std::array<int, 4>> &ip_pool, int match_1, int match_2)
{
    std::for_each(begin(ip_pool), end(ip_pool), [&match_1, &match_2](auto &el)
                  {
		if(el.at(0) == match_1 && el.at(1) == match_2){
			print_part(el);
		} });
}

void filter_any(std::vector<std::array<int, 4>> &ip_pool, int match)
{
    std::for_each(begin(ip_pool), end(ip_pool), [&match](auto &el)
                  {
		if(std::find(el.cbegin(), el.cend(), match) != std::end(el)){
			print_part(el);
		} });
}
