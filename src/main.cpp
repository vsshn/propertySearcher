#include <iostream>
#include <gflags/gflags.h>

#include "fetcher/CurlWrapper.h"

DEFINE_string(url_to_fetch, "https://www.york.ac.uk/teaching/cws/wws/webpage1.html", "The URL to fetch");

int main(int argc, char **argv)
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    gflags::ShowUsageWithFlags(argv[0]);
    ps::CurlWrapper curlWrapper;
    auto response = curlWrapper.getHtmlFrom(FLAGS_url_to_fetch);
    if (response)
    {
        std::cout << response.value() << std::endl;
    }
}