#include "http_server.hh"
#include <vector>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include<bits/stdc++.h>


vector<string> split(const string &s, char delim) {
  vector<string> elems;

  stringstream ss(s);
  string item;

  while (getline(ss, item, delim)) {
    if (!item.empty())
      elems.push_back(item);
  }

  return elems;
}

HTTP_Request::HTTP_Request(string request) {
  vector<string> lines = split(request, '\n');
  vector<string> first_line = split(lines[0], ' ');

  this->HTTP_version = "1.0"; // We'll be using 1.0 irrespective of the request

  /*
   TODO : extract the request method and URL from first_line here
  */
    method = first_line[0];
    url = first_line[1];

  if (this->method != "GET") {
    cerr << "Method '" << this->method << "' not supported" << endl;
    exit(1);
  }
}

HTTP_Response *handle_request(string req) 
{
  HTTP_Request *request = new HTTP_Request(req);

  HTTP_Response *response = new HTTP_Response(); // to be returned finally

  string url = string("html_files") + request->url;
  string url2 = string("html_files/");

  response->HTTP_version = "1.0";

  struct stat sb;
  if (stat(url.c_str(), &sb) == 0) // requested path exists
  {
    //cout<<"Path exists\n";
    response->status_code = "200";
    response->status_text = "OK";
    response->content_type = "text/html";

    string body;

    string f;

    if (S_ISDIR(sb.st_mode)) 
    {
      /*
      In this case, requested path is a directory.
      TODO : find the index.html file in that directory (modify the url
      accordingly)
      */
      if(url[url.length()-1] == '/')
        url=url+string("index.html");
      else
        url = url + string("/index.html");
    }
    struct stat si;
    stat(url.c_str(),&si);

    /*
    TODO : open the file and read its contents
    */
    //FILE *fp = fopen(url.c_str(),"r");
    
    FILE *fp = fopen(url.c_str(),"r");
    int bytes_read = 0;
    int size = si.st_size;
    char buffer[size+1];
    int len = si.st_size;
    string cont_len = to_string(len);
    bytes_read = fread(buffer,si.st_size,1,fp);

    fclose(fp);
    response->content_length = cont_len;

    /*
    TODO : set the remaining fields of response appropriately
    */
    response->body = buffer;
  }

  else 
  {
    /*
    TODO : set the remaining fields of response appropriately
    */
    url2 = url2 + string("404.html");

    struct stat si_nf;
    stat(url2.c_str(),&si_nf);

    response->status_code = "404";
    response->status_text = "Not Found";
    response->content_type = "text/html";
    FILE *fp1 = fopen(url2.c_str(),"r");

    int bytes_read = 0;
    int size = si_nf.st_size;
    char buffer2[size+1];
    int len = si_nf.st_size;
    string cont_len = to_string(len);
    bytes_read = fread(buffer2,si_nf.st_size,1,fp1);

    fclose(fp1);
    response->content_length = cont_len;

    response->body = buffer2;
  }

  delete request;

  return response;
}

string HTTP_Response::get_string() {
  /*
  TODO : implement this function
  */
 string resp = string("HTTP/");
 resp = resp + this->HTTP_version;
 resp = resp + string(" ");
 resp = resp + this->status_code;
 resp = resp + string(" ");
 resp = resp + this->status_text;
 resp = resp + string("\n");
 resp = resp + string("Content-Length: ");
 resp = resp + this->content_length;
 resp = resp + string("\n");
 resp = resp + string("Content-Type: ");
 resp = resp + this->content_type;
 resp = resp + string("\n\n");
 resp = resp + this->body;
 resp = resp + string("\n");

 return resp;
}
