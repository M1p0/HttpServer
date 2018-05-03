#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/http.h>
#include <evhttp.h>
#include <string>
#include <string.h>
#include <iostream>
#include <CFileIO.h>
#include <stdio.h>
using namespace std;
CFileIO File;
#define BUFFER_SIZE 1024*1024
bool startHttpServer(const char *ip, int port, void(*cb)(struct evhttp_request *, void *), void *arg)
{
    //创建event_base和evhttp
    event_base* base = event_base_new();
    evhttp* http_server = evhttp_new(base);
    if (!http_server) {
        return false;
    }
    //绑定到指定地址上
    int ret = evhttp_bind_socket(http_server, ip, port & 0xFFFF);
    if (ret != 0) {
        return false;
    }
    //设置事件处理函数
    evhttp_set_gencb(http_server, cb, arg);
    //启动事件循环，当有http请求的时候会调用指定的回调
    event_base_dispatch(base);
    evhttp_free(http_server);
    return true;
}
void MyHttpServerHandler(struct evhttp_request* req, void* arg)
{
    //创建要使用的buffer对象
    evbuffer* buf = evbuffer_new();
    char* buffer=new char[BUFFER_SIZE];
    //char buffer[BUFFER_SIZE];
    char local[4096];
    memset(buffer, 0, BUFFER_SIZE);
    memset(local, 0, 4096);
    local[0] = '.';
    //获取请求的URI
    const char* uri = (char*)evhttp_request_get_uri(req);
    strcat(local, uri);
    File.Read(local, buffer, 0, BUFFER_SIZE);
    int64_t uLength;
    File.GetSize(local, &uLength);
    char szLength[32];
    _i64toa(uLength, szLength, 10);
    cout <<"FileSize:"<< uLength << endl;
    evbuffer_expand(buf, uLength);
    //回复给客户端
    evhttp_add_header(req->output_headers,"Content-Length", szLength);
    //evhttp_add_header(req->output_headers, "Content-Type", "application/json");
    //if (strcmp(uri,"/about.html")!=0)
    //{
    //    evhttp_add_header(req->output_headers, "Content-Type", "text/css");
    //}
    evbuffer_add(buf, buffer, uLength);
    //evbuffer_add_printf(buf, buffer);
    evhttp_send_reply(req, HTTP_OK, "OK", buf);
    evbuffer_free(buf);
}
int main()
{
    //Windows 平台套接字库的初始化
#ifdef WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    //启动服务在地址 127.0.0.1:9001 上
    startHttpServer("0.0.0.0", 9001, MyHttpServerHandler, NULL);
#ifdef WIN32
    WSACleanup();
#endif
    return 0;
}