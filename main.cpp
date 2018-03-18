#include <memory>
#include <restbed>
#include <args.hxx>
#include <iostream>
#include "Config.hpp"

using namespace std;
using namespace restbed;

void get_method(const shared_ptr<Session> session) {
    const auto request = session->get_request( );
    int content_length = request->get_header( "Content-Length", 0 );
    session->close( OK, "Hello, World!", { { "Content-Length", "13" } } );
}

int main(const int argc, const char** argv) {
    args::ArgumentParser parser("TrustKey Supervisor");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    args::ValueFlag<string> configPath(parser, "config", "Config file path", {'c', "config"}, "config.json");

    try
    {
        parser.ParseCLI(argc, argv);
    }
    catch (args::Help)
    {
        std::cout << parser;
        return 0;
    }
    catch (args::ParseError e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    Config config = Config::parseOrDie("config.json");

    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler("GET", get_method);

    auto settings = make_shared< Settings >( );
    settings->set_port(config.http_server_port);
    settings->set_default_header( "Connection", "close" );

    auto ssl_settings = make_shared< SSLSettings >( );
    ssl_settings->set_http_disabled(false);
    ssl_settings->set_port(config.https_server_port);
    ssl_settings->set_certificate(Uri(string("file://") + config.ssl_certificate));
    ssl_settings->set_private_key(Uri(string("file://") + config.ssl_certificate_key));
    ssl_settings->set_temporary_diffie_hellman(Uri(string("file://") + config.temporary_diffie_hellman));

    settings->set_ssl_settings( ssl_settings );

    Service service;
    service.publish( resource );
    service.start( settings );

    return EXIT_SUCCESS;
}