#include <string>
#include <vector>
#include <iostream>
#include <dirent.h>
#include <map>
#include <string.h>

#include "musicstore.h"

using namespace std;

struct musicstore
{
    map<string, map<string, map<int, string>>> musicstoremap;
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

int ms_read_from_directory(struct musicstore *ms, const char *path)
{
    // command read ./tests/acdc
    // path ./tests/acdc

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            string filename = ent->d_name;

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
                if (filename.find(".mp3") != string::npos ||
                    filename.find(".ogg") != string::npos ||
                    filename.find(".flac") != string::npos ||
                    filename.find(".wma") != string::npos ||
                    filename.find(".mpc") != string::npos)
                {
                    string artist = filename.substr(0, filename.find(" - "));
                    filename = filename.substr(filename.find(" - ") + 3);
                    string album = filename.substr(0, filename.find(" - "));
                    filename = filename.substr(filename.find(" - ") + 3);
                    string tracknumber = filename.substr(0, filename.find(" - "));
                    filename = filename.substr(filename.find(" - ") + 3);

                    string songname;

                    if (filename.find(".mp3") != string::npos)
                    {
                        songname = filename.substr(0, filename.find(".mp3"));
                    }
                    else if (filename.find(".ogg") != string::npos)
                    {
                        songname = filename.substr(0, filename.find(".ogg"));
                    }
                    else if (filename.find(".flac") != string::npos)
                    {
                        songname = filename.substr(0, filename.find(".flac"));
                    }
                    else if (filename.find(".wma") != string::npos)
                    {
                        songname = filename.substr(0, filename.find(".wma"));
                    }
                    else if (filename.find(".mpc") != string::npos)
                    {
                        songname = filename.substr(0, filename.find(".mpc"));
                    }

                    ms->musicstoremap[artist][album][stoi(tracknumber)] = songname;
                    printf("artist: %s, album: %s, tracknumber: %s, songname: %s\n", artist.c_str(), album.c_str(), tracknumber.c_str(), songname.c_str());
                }
            }
        }
        closedir(dir);
    }
    else
    {
        return 0;
    }
    return 1;
}

void ms_get_artist(const struct musicstore *s, const char *artist, artist_callback cb)
{
    map<string, map<string, map<int, string>>>::const_iterator it;
    int songcount = 0;
    map<string, map<int, string>>::const_iterator it2;

    if (artist != NULL)
    {
        it = s->musicstoremap.find(artist);
        if (it != s->musicstoremap.end())
        {
            for (it2 = it->second.begin(); it2 != it->second.end(); it2++)
            {
                songcount += it2->second.size();
            }

            cb(artist, it->second.size(), songcount);
        }
    }
    else
    {
        for (it = s->musicstoremap.begin(); it != s->musicstoremap.end(); it++)
        {
            songcount = 0;
            for (it2 = it->second.begin(); it2 != it->second.end(); it2++)
            {
                songcount += it2->second.size();
            }
            cb(it->first.c_str(), it->second.size(), songcount);
        }
    }
};

void ms_get_albums(const struct musicstore *s, const char *artist, const char *album, album_callback cb)
{
    map<string, map<string, map<int, string>>>::const_iterator it;
    map<string, map<int, string>>::const_iterator it2;
    map<int, string>::const_iterator it3;

    if (artist != NULL)
    {
        it = s->musicstoremap.find(artist);
        if (it != s->musicstoremap.end())
        {
            if (album != NULL)
            {
                it2 = it->second.find(album);
                if (it2 != it->second.end())
                {
                    cb(artist, album, it2->second.size());
                }
            }
            else
            {
                for (it2 = it->second.begin(); it2 != it->second.end(); it2++)
                {
                    cb(artist, it2->first.c_str(), it2->second.size());
                }
            }
        }
    }
    else
    {
        if (album != NULL)
        {
            for (it = s->musicstoremap.begin(); it != s->musicstoremap.end(); it++)
            {
                it2 = it->second.find(album);
                if (it2 != it->second.end())
                {
                    cb(it->first.c_str(), album, it2->second.size());
                }
            }
        }
        else
        {
            for (it = s->musicstoremap.begin(); it != s->musicstoremap.end(); it++)
            {
                for (it2 = it->second.begin(); it2 != it->second.end(); it2++)
                {
                    cb(it->first.c_str(), it2->first.c_str(), it2->second.size());
                }
            }
        }
    }
}

void ms_get_songs(const struct musicstore *s, const char *artist, const char *album, const char *title, song_callback cb)
{

    if (artist != NULL)
    {
        map<string, map<string, map<int, string>>>::const_iterator it;
        map<string, map<int, string>>::const_iterator it2;
        map<int, string>::const_iterator it3;

        it = s->musicstoremap.find(artist);
        if (it != s->musicstoremap.end())
        {
            if (album != NULL)
            {
                it2 = it->second.find(album);
                if (it2 != it->second.end())
                {
                    if (title != NULL)
                    {
                        for (it3 = it2->second.begin(); it3 != it2->second.end(); it3++)
                        {
                            if (it3->second == title)
                            {
                                cb(artist, album, it3->first, it3->second.c_str());
                            }
                        }
                    }
                    else
                    {
                        for (it3 = it2->second.begin(); it3 != it2->second.end(); it3++)
                        {
                            cb(artist, album, it3->first, it3->second.c_str());
                        }
                    }
                }
            }
            else
            {
                if (title != NULL)
                {
                    for (it2 = it->second.begin(); it2 != it->second.end(); it2++)
                    {
                        for (it3 = it2->second.begin(); it3 != it2->second.end(); it3++)
                        {
                            if (it3->second == title)
                            {
                                cb(artist, it2->first.c_str(), it3->first, it3->second.c_str());
                            }
                        }
                    }
                }
                else
                {
                    for (it2 = it->second.begin(); it2 != it->second.end(); it2++)
                    {
                        for (it3 = it2->second.begin(); it3 != it2->second.end(); it3++)
                        {
                            cb(artist, it2->first.c_str(), it3->first, it3->second.c_str());
                        }
                    }
                }
            }
        }
    }
    else
    {
        map<string, map<string, map<int, string>>>::const_iterator it;
        map<string, map<int, string>>::const_iterator it2;
        map<int, string>::const_iterator it3;

        if (album != NULL)
        {
            for (it = s->musicstoremap.begin(); it != s->musicstoremap.end(); it++)
            {
                it2 = it->second.find(album);
                if (it2 != it->second.end())
                {
                    if (title != NULL)
                    {
                        for (it3 = it2->second.begin(); it3 != it2->second.end(); it3++)
                        {
                            if (it3->second == title)
                            {
                                cb(it->first.c_str(), album, it3->first, it3->second.c_str());
                            }
                        }
                    }
                    else
                    {
                        for (it3 = it2->second.begin(); it3 != it2->second.end(); it3++)
                        {
                            cb(it->first.c_str(), album, it3->first, it3->second.c_str());
                        }
                    }
                }
            }
        }
        else
        {

            if (title != NULL)
            {
                for (it = s->musicstoremap.begin(); it != s->musicstoremap.end(); it++)
                {
                    for (it2 = it->second.begin(); it2 != it->second.end(); it2++)
                    {
                        for (it3 = it2->second.begin(); it3 != it2->second.end(); it3++)
                        {
                            if (it3->second == title)
                            {
                                cb(it->first.c_str(), it2->first.c_str(), it3->first, it3->second.c_str());
                            }
                        }
                    }
                }
            }
            else
            {
                for (it = s->musicstoremap.begin(); it != s->musicstoremap.end(); it++)
                {
                    for (it2 = it->second.begin(); it2 != it->second.end(); it2++)
                    {
                        for (it3 = it2->second.begin(); it3 != it2->second.end(); it3++)
                        {
                            cb(it->first.c_str(), it2->first.c_str(), it3->first, it3->second.c_str());
                        }
                    }
                }
            }
        }
    }
};
