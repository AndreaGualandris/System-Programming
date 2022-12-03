#include <string>
#include <vector>
#include <iostream>
#include <dirent.h>
#include <map>

#include "musicstore.h"

struct artist
{
    std::string name;
};

struct album
{
    std::string name;
};

struct song
{
    std::string name;
    int trackNumber;
};

struct musicstore
{
    std::vector<artist> artists;
    std::vector<album> albums;
    std::vector<song> songs;

    // std::map <artist, album> aa;
    // std::map <album, song> as;
};

struct musicstore *ms_create()
{
    struct musicstore *ms = new struct musicstore;
    return ms;
};

void ms_destroy(struct musicstore *ms)
{
    delete ms;
};

int check_univoque_artist(struct musicstore *ms, const char *artist)
{
    for (int i = 0; i < ms->artists.size(); i++)
    {
        if (ms->artists[i].name == artist)
        {
            return i;
        }
    }
    return -1;
}

int ms_read_from_directory(struct musicstore *s, const char *path)
{

    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(path)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {

            std::string filename = ent->d_name;
            std::string delimiter = " - ";

            // check the name of the extension of the file is flac, mp3, mpc, ogg, or wma
            if (filename.find(".flac") != std::string::npos || 
                filename.find(".mp3") != std::string::npos || 
                filename.find(".mpc") != std::string::npos || 
                filename.find(".ogg") != std::string::npos || 
                filename.find(".wma") != std::string::npos) {

                std::string artist = filename.substr(0, filename.find(delimiter));
                filename.erase(0, filename.find(delimiter) + delimiter.length());

                std::string album = filename.substr(0, filename.find(delimiter));
                filename.erase(0, filename.find(delimiter) + delimiter.length());

                std::string trackNumber = filename.substr(0, filename.find(delimiter));
                filename.erase(0, filename.find(delimiter) + delimiter.length());

                std::string title = filename.substr(0, filename.find("."));
                filename.erase(0, filename.find(delimiter) + delimiter.length());

                std::cout << "artist: " << artist << std::endl;
                std::cout << "album: " << album << std::endl;
                std::cout << "trackNumber: " << trackNumber << std::endl;
                std::cout << "title: " << title << std::endl;

                if (check_univoque_artist(s, artist.c_str()) == -1)
                {
                    struct artist a;
                    a.name = artist;
                    s->artists.push_back(a);
                }
            }
        }
    }
}
