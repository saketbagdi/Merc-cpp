#include<iostream>
#include<map>
#include<forward_list>
using namespace std;

/* ============================= Validator class ========================== */
class Validator
{
private:
Validator(){}
public:
static bool isValidMIMEType(string &mimeType)
{
//right now do nothing
return true;
}
static bool isValidPath(string &path)
{
//right now do nothing
return true;
}
static bool isValidURLFormat(string &url)
{
//right now do nothing 
return true;
}
};

/* ============================= Error class ================================ */

class Error
{
public:
bool hasError()
{
return false;
}
string getError()
{
return "";
}
};

/* ============================== Request class ============================= */

class Request
{
};



/* ============================== Response class ================================ */


class Response
{
private:

//introduced a property here

string contentType;
forward_list<string> content;
forward_list<string>::iterator contentIterator;
unsigned long contentLength;

public:
Response()
{
this->contentLength=0;
this->contentIterator=this->content.before_begin();
}
~Response()
{
// not yet decided
}
void setContentType(string contentType)
{

//introduced a method which was already available there just introduced the necessary code

if(Validator::isValidMIMEType(contentType))
{
this->contentType=contentType;
}

}
Response & operator<<(string content)
{
this->contentLength+=content.length();
this->contentIterator=this->content.insert_after(this->contentIterator,content);


return *this;
}
};




/* ================================ Merc class =============================== */

class Merc
{
private:
//introducing properties

string staticResourcesFolder;
map<string,void(*)(Request &, Response &)> urlMappings;

public:
Merc()
{
//not yet decided
}
~Merc()
{
//not yet decide
}
void setStaticResourcesFolder(string staticResourcesFolder)
{
if(Validator::isValidPath(staticResourcesFolder))
{
this->staticResourcesFolder=staticResourcesFolder;
}
else
{
//not yet decided
}
}
void get(string url ,void (*callBack)(Request &, Response &))
{
if(Validator::isValidURLFormat(url))
{
urlMappings.insert(pair< string, void (*) (Request &, Response &) >(url,callBack));
}
}
void listen(int portNumber,void(*callBack)(Error &))
{
//do nothing right now
}
};





/* =========================================== main class ============================== */


int main()
{
Merc merc;
merc.setStaticResourcesFolder("whatever");

merc.get("/",[](Request &request, Response &response)-> void {
const char *html=R""""(
<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title>Whatever</title>
</head>
<body>
<h1>Welcome</h1>
<h3>Administrator</h3>
<a href='getCustomers'>Customers List</a>
</body>
</html>
)"""";
response.setContentType("text/html");
response<<html;
});

merc.get("/getCustomers",[](Request &request, Response &response)->void{
const char *html=R""""(
<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title>Whatever</title>
</head>
<body>
<h1>List of Customers</h1>
<ul>
<li>Ramesh</li>
<li>Suresh</li>
<li>Mohan</li>
</ul>
<a href='/'>Home</a>
</body>
</html>
)"""";
response.setContentType("text/html");
response<<html;
});

merc.listen(6060,[](Error &error)->void{
if(error.hasError())
{
cout<<error.getError();
return;
}
cout<<"Merc HTTP Server is ready to accept request at port 6060"<<endl;
});
return 0;
}