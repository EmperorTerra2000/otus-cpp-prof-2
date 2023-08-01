#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
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

void print(std::vector<std::vector<std::string>> &parameter);
void print_part(const std::vector<std::string> &param);
void filter(std::vector<std::vector<std::string>> &ip_pool, std::string match);
void filter(std::vector<std::vector<std::string>> &ip_pool, std::string match_1, std::string match_2);
void filter_any(std::vector<std::vector<std::string>> &ip_pool, std::string match);

int main()
{
    try
    {
        std::vector<std::vector<std::string>> ip_pool;
        // вектор из ip адресов в hex представлении
        std::vector<unsigned int> ip_pool_hex;

        for (std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort

        // переводим строку с ip адресом в hex формат и пушим в вектор ip_pool_hex
        for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            unsigned int res = std::stoi(ip->at(0)) << 24 |
                               std::stoi(ip->at(1)) << 16 |
                               std::stoi(ip->at(2)) << 8 |
                               std::stoi(ip->at(3));

            ip_pool_hex.push_back(res);
        }

        ip_pool.clear();

        // сортировка ip адресов в hex формате производится лексикографически
        // сортировка по убыванию
        std::sort(ip_pool_hex.begin(), ip_pool_hex.end(), std::greater<unsigned int>());

        // обратно переводим из hex в string и пушим в вектор ip_pool
        for (auto ip = ip_pool_hex.cbegin(); ip != ip_pool_hex.cend(); ++ip)
        {
            ip_pool.push_back({std::to_string((*(ip) >> 24) & 0xFF),
                               std::to_string((*(ip) >> 16) & 0xFF),
                               std::to_string((*(ip) >> 8) & 0xFF),
                               std::to_string((*(ip)) & 0xFF)});
        }

        // выводим результат
        print(ip_pool);

        filter(ip_pool, "1");
        filter(ip_pool, "46", "70");
        filter_any(ip_pool, "46");

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

void print(std::vector<std::vector<std::string>> &parameter)
{
    for (auto ip = parameter.cbegin(); ip != parameter.cend(); ++ip)
    {
        print_part(*ip);
    }
}

void print_part(const std::vector<std::string> &param)
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

void filter(std::vector<std::vector<std::string>> &ip_pool, std::string match)
{
    std::for_each(begin(ip_pool), end(ip_pool), [&match](auto &el)
                  {
		if(el.at(0) == match){
			print_part(el);
		} });
}

void filter(std::vector<std::vector<std::string>> &ip_pool, std::string match_1, std::string match_2)
{
    std::for_each(begin(ip_pool), end(ip_pool), [&match_1, &match_2](auto &el)
                  {
		if(el.at(0) == match_1 && el.at(1) == match_2){
			print_part(el);
		} });
}

void filter_any(std::vector<std::vector<std::string>> &ip_pool, std::string match)
{
    std::for_each(begin(ip_pool), end(ip_pool), [&match](auto &el)
                  {
		if(std::find(el.cbegin(), el.cend(), match) != std::end(el)){
			print_part(el);
		} });
}
