#ifndef SUPERVISORPP_CONFIG_HPP
#define SUPERVISORPP_CONFIG_HPP

#include <string>
#include <staticjson/staticjson.hpp>
#include <fstream>

class Config {
public:
    std::string ssl_certificate;
    std::string ssl_certificate_key;
    std::string temporary_diffie_hellman;
    size_t http_server_port;
    size_t https_server_port;

    void staticjson_init(staticjson::ObjectHandler* h) {
        h->add_property("ssl_certificate", &ssl_certificate);
        h->add_property("ssl_certificate_key", &ssl_certificate_key);
        h->add_property("temporary_diffie_hellman", &temporary_diffie_hellman);
        h->add_property("http_server_port", &http_server_port);
        h->add_property("https_server_port", &https_server_port);
    }

    static Config parseOrDie(const std::string filePath) {
        using namespace staticjson;

        ParseStatus status;
        Config res;

        std::ifstream f(filePath);
        if(!f.is_open()) {
            std::cerr << "Fatal error: cannot open config file." << std::endl;
            exit(1);
        }

        std::string configFileContent((std::istreambuf_iterator<char>(f)),
                        std::istreambuf_iterator<char>());

        from_json_string(configFileContent.c_str(), &res, &status);

        if(status.has_error()) {
            std::cerr << "Fatal error: config parse error." << std::endl
                      << status.description()   << std::endl;
            exit(1);
        }

        return res;
    }
};

#endif //SUPERVISORPP_CONFIG_HPP
