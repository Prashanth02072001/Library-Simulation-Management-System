#pragma once
#include "CSVParser.h"
#include <iostream>
#include <limits>
#include <regex>
#include <random>

#define log(x) std::cout << x

class Userinfo{
private:
    unsigned int m_next_position = 0;

    std::string_view m_ID;
    std::string m_user_name = "";

    std::string m_path_userinfo {fm::init_workingdir() + "Data\\Userinfo.txt"};
    csv::Header m_bookheader{"BID,DATE,POSITION"};
    std::vector<csv::Row> mvec_books;
    std::vector<csv::Row> mvec_owned;
    std::vector<csv::Row> mvec_published;

    std::fstream m_userinfo_txt;
public:
    Userinfo();
    ~Userinfo();
    
    bool create_user_info(std::string_view);
    bool load_userinfo(std::string_view);

    std::string_view get_name();
};

class User { //holds the user and is responsible for login, logout and activity log -> gets automatically deleted with logout
private: 
    bool m_login_flag;          //flag to indicate wheather user is logged in or not
    std::string *mptr_username = nullptr; //username of the current user gets deleted after loggin
    std::string *mptr_password = nullptr; //password entered by user also gets deleted after authenticating login
    std::string m_ID; //User ID UXXXXXX

    csv::Header m_userfile_header{"USERNAME,PASSWORD,UID"};
    std::string m_path_userfile {fm::init_workingdir() + "Data\\Userfile.csv"};
    csv::CSVParser *mptr_csv_parser = nullptr; 
    Userinfo* mptr_userinfo = nullptr;            

protected:
    bool m_user_request(); //deals with authentification of the user
    bool m_create_user(); //deals with creating a new user 
    std::string_view m_create_ID(int,int);
public:
    User();
    ~User();
    Userinfo& login();
    bool is_logged();
    void logout();               
};