#include <boost/xpressive/xpressive.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "App.h"

const int port = 3000;
const std::filesystem::path publicDir{"./public"};  //location where html files to be served are stored

const std::string default404 = R"(<!DOCTYPE html><html lang="en"><head><meta charset="UTF-8"><meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0"><title>404 Not Found</title></head><body><h1>404: Page Not Found!</h1>
    </body></html>)";

int loadFilesIntoMemory(std::map<std::string, std::string> &fileBufferMap, std::filesystem::path publicDir)
{
    for (auto const &dir_entry : std::filesystem::directory_iterator{publicDir})
    {
        // Load file into memory
        std::ifstream file(dir_entry.path(), std::ios::binary);
        if (!file.is_open())
        {
            std::cout << "Error: Unable to open file: " << dir_entry.path() << "!" << std::endl;
            return 1;
        }
        else
        {
            using namespace boost::xpressive;

            std::string fileStr(static_cast<std::stringstream const &>(std::stringstream() << file.rdbuf()).str());
            mark_tag path(1);
            smatch pathMatch;
            sregex expr = "./public" >> (path = '/' >> +_w >> '.' >> +_w);
            std::string filepathStr = static_cast<std::string>(dir_entry.path());
            if (regex_match(filepathStr, pathMatch, expr))
            {
                std::cout << "Loading file: " << pathMatch[path] << std::endl;
                fileBufferMap.insert(std::pair<std::string, std::string>(pathMatch[path], fileStr));
            }
        }
        file.close();
    }
    return 0;
}

int main()
{
    std::map<std::string, std::string> fileBufferMap;
    int loadFilesReturnCode = loadFilesIntoMemory(fileBufferMap, publicDir);
    if (loadFilesReturnCode != 0)
    {
        return loadFilesReturnCode;
    }

    // Setup web server
    uWS::App().get("/*", [&fileBufferMap](auto *res, auto *req)
                   {
                    std::string path = static_cast<std::string>(req->getUrl());
                    if(fileBufferMap.count(path) == 1){
                        res->writeStatus(uWS::HTTP_200_OK);
                        res->writeHeader("Content-Type", "text/html; charset=utf-8");
                        res->end(fileBufferMap.at(path).data()); // Don't do this with large files; need to manage backpressure
                    }
                    else{
                        res->writeStatus("404 Not Found");
                        res->writeHeader("Content-Type", "text/html; charset=utf-8");
                        std::cout << "Page: " << path << " not found!" << std::endl;
                        if(fileBufferMap.count("/404.html") == 1){
                            res->end(fileBufferMap.at("/404.html").data());
                        }
                        else{
                            res->end(default404);
                        }
                    }
                    res->end(); })
        .listen(port, [](auto *listenSocket)
                {
        if (listenSocket) {
            std::cout << "Listening for connections on port " << port << "..." << std::endl;
        } })
        .run();

    std::cout << "Shoot! We failed to listen and the App fell through, exiting now!" << std::endl;
    return 1;
}