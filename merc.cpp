#include<iostream>
using namespace std;
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
class Request
{
};
class Response
{
public:
void setContentType(string contentType)
{
//do nothing right now
}
Response & operator<<(string content)
{
//right now do nothing
return *this;
}
};
class Merc
{
public:
void setStaticResourcesFolder(string staticResourcesFolder)
{
//do nothing right now
}
void get(string urlPattern,void (*callBack)(Request &, Response &))
{
//do nothing right now
}
void listen(int portNumber,void(*callBack)(Error &))
{
//do nothing right now
}
};








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