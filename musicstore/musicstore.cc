#include <string>
#include <vector>
#include <iostream>
#include <dirent.h>
#include <map>
#include <string.h>

#include "musicstore.h"

// struct song
// {
//     std::string name;
// };

// struct album
// {
//     std::string name;
//     std::map<unsigned int, song> songs;
// };

// struct artist
// {
//     std::string name;
//     std::map<unsigned int, album> albums;
// };

// struct musicstore
// {
//     std::map<unsigned int, artist> artists;
// };
using namespace std;

struct musicstore
{
    map<string, map<string, map<int, string>>> musicstoremap;
};

struct musicstore * ms_create (){
    struct musicstore * ms = new struct musicstore;
    return ms;
};

void ms_destroy (struct musicstore *ms){
    delete ms;
};

// find all files in directory and subdirectories formatted as follow: artisr - album - tracknumber - songname.extension
int ms_read_from_directory(struct musicstore *ms, const char *path)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_name[0] == '.')
                continue;

            if (ent->d_type == DT_DIR)
            {
                string newpath = path;
                newpath += ent->d_name;
                newpath += "/";
                ms_read_from_directory(ms, newpath.c_str());
            }
            else
            {
                string filename = ent->d_name;

                if (filename.find(".mp3") != string::npos ||
                    filename.find(".ogg") != string::npos ||
                    filename.find(".flac") != string::npos ||
                    filename.find(".wma") != string::npos ||
                    filename.find(".mpc") != string::npos)
                {
                    string artist = filename.substr(0, filename.find(" - ") - 1);
                    filename = filename.substr(filename.find(" - ") + 2);
                    string album = filename.substr(0, filename.find("-") - 1);
                    filename = filename.substr(filename.find(" - ") + 2);
                    string tracknumber = filename.substr(0, filename.find(" - ") - 1);
                    filename = filename.substr(filename.find(" - ") + 2);
                    string songname = filename.substr(0, filename.find("."));
                    ms->musicstoremap[artist][album][stoi(tracknumber)] = songname;
                }
            }
        }
        closedir(dir);
    }
    else
    {
        return 1;
    }
    return 0;
}

typedef void (*song_callback)(const char *artist, const char *album,
                              unsigned sequence, const char *title);

typedef void (*album_callback)(const char *artist, const char *album,
                               unsigned songs_count);

typedef void (*artist_callback)(const char *artist, unsigned albums_count,
                                unsigned songs_count);

void ms_get_artist(const struct musicstore *s,
                   const char *artist, artist_callback cb)
                
{
// error: passing ‘const std::map<std::__cxx11::basic_string<char>, std::map<std::__cxx11::basic_string<char>, std::map<int, std::__cxx11::basic_string<char> > > >’ as ‘this’ argument discards qualifiers [-fpermissive]
//   110 |         unsigned  albums_count = s->musicstoremap[artist].size();

    

    if (artist != NULL)
    {
        unsigned int albums_count = s->musicstoremap.size();
        unsigned int songs_count = 0;
        for (auto album : s->musicstoremap[artist])
        {
            songs_count += album.second.size();
        }
        cb(artist, albums_count, songs_count);
    }
    else
    {
        for (auto artist : s->musicstoremap)
        {
            unsigned int albums_count = artist.second.size();
            unsigned int songs_count = 0;
            for (auto album : artist.second)
            {
                songs_count += album.second.size();
            }
            cb(artist.first.c_str(), albums_count, songs_count);
        }
    }
};

// void ms_get_albums(const struct musicstore *s,
//                    const char *artist, const char *album, album_callback cb)
// {
//     if (artist != NULL && album != NULL)
//     {
//         unsigned int songs_count = s->musicstoremap[artist][album].size();
//         cb(artist, album, songs_count);
//     }
//     else if (artist != NULL && album == NULL)
//     {
//         for (auto album : s->musicstoremap[artist])
//         {
//             unsigned int songs_count = album.second.size();
//             cb(artist, album.first.c_str(), songs_count);
//         }
//     }
//     else if (artist == NULL && album != NULL)
//     {
//         for (auto artist : s->musicstoremap)
//         {
//             for (auto album : artist.second)
//             {
//                 if (album.first == album)
//                 {
//                     unsigned int songs_count = album.second.size();
//                     cb(artist.first.c_str(), album.first.c_str(), songs_count);
//                 }
//             }
//         }
//     }
//     else
//     {
//         for (auto artist : s->musicstoremap)
//         {
//             for (auto album : artist.second)
//             {
//                 unsigned int songs_count = album.second.size();
//                 cb(artist.first.c_str(), album.first.c_str(), songs_count);
//             }
//         }
//     }

// };

// void ms_get_songs(const struct musicstore *s,
//                   const char *artist, const char *album, const char *title,
//                   song_callback cb)
// {

void ms_get_albums (const struct musicstore * s,
		    const char * artist, const char * album, album_callback cb){};

void ms_get_songs (const struct musicstore * s,
		   const char * artist, const char * album, const char * title,
		   song_callback cb){};


    
// };