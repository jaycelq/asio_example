//
// Created by qiang.li on 2017/4/10.
//
#include <iostream>
#include <boost/filesystem.hpp>

#define MAX_FILE_PATH_LEN   512
#define LOG_FILE_NAME_FORMAT    "%[a-z.]%04d%02d%02d.%02d%02d"

int main()
{
    time_t cur_timestamp;
    time(&cur_timestamp);

    boost::filesystem::path log_path("log/gameserver.packet.log");
    boost::filesystem::path dir = log_path.parent_path();
    std::string log_conf_filename = log_path.filename().string();

    if (!boost::filesystem::is_directory(dir))
    {
        return 0;
    }

    boost::filesystem::recursive_directory_iterator end;
    for (boost::filesystem::recursive_directory_iterator it(dir); it != end; it++)
    {
        std::string log_file_name = it->path().filename().string();
        char filename[MAX_FILE_PATH_LEN + 1];
        uint32_t year = 0, mon = 0, day = 0, hour = 0, min = 0;
        int32_t count = sscanf(log_file_name.c_str(), LOG_FILE_NAME_FORMAT, filename, &year, &mon, &day, &hour, &min);
        if (count == 6)
        {
            std::string log_file_level(filename);
            if (log_file_level.back() == '.')
            {
                log_file_level.pop_back();
            }
            if (log_file_level.compare(log_conf_filename) == 0)
            {
                struct tm log_file_tm;
                log_file_tm.tm_year = year - 1900;
                log_file_tm.tm_mon = mon - 1;
                log_file_tm.tm_mday = day;
                log_file_tm.tm_hour = hour;
                log_file_tm.tm_min = min;
                log_file_tm.tm_sec = 0;

                time_t log_file_timestamp = mktime(&log_file_tm);
                std::cout << log_file_timestamp << std::endl;
                if (log_file_timestamp > 0)
                {
                    if (log_file_timestamp < cur_timestamp - 2*60)
                    {
                        boost::filesystem::remove(it->path());
                    }
                }
            }
        }
    }


    return 0;
}
