#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/http.h>
#include <evhttp.h>
#include <string>
#include <string.h>
#include <iostream>
#include <CFileIO.h>
#include <stdio.h>
#include <MSocket.h>
using namespace std;
MSocket Sock;
CFileIO File;
#define BUFFER_SIZE 1024*1024
bool startHttpServer(const char *ip, int port, void(*cb)(struct evhttp_request *, void *), void *arg)
{
    //创建event_base和evhttp
    event_base* base = event_base_new();
    evhttp* http_server = evhttp_new(base);
    if (!http_server)
    {
        return false;
    }
    //绑定到指定地址上
    int ret = evhttp_bind_socket(http_server, ip, port & 0xFFFF);
    if (ret != 0)
    {
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
    struct evkeyvalq *Req_Header;
    Req_Header=evhttp_request_get_input_headers(req);  //request头
    evbuffer* buf = evbuffer_new();
    char* buffer=new char[BUFFER_SIZE];
    char local[4096];
    memset(buffer, 0, BUFFER_SIZE);
    memset(local, 0, 4096);
    local[0] = '.';
    const char* uri = (char*)evhttp_request_get_uri(req);   //请求的uri
    cout << "uri:"<<uri << endl;
    strcat(local, uri);
    File.Read(local, buffer, 0, BUFFER_SIZE);
    int64_t uLength;
    File.GetSize(local, &uLength);
    char szLength[32];
    _i64toa(uLength, szLength, 10);
    evbuffer_expand(buf, uLength);   //增大缓冲区
    //回复给客户端

    for (evkeyval* header = Req_Header->tqh_first; header; header = header->next.tqe_next)
    {
        //if (_stricmp(header->key,"content-type")==0)
        //{
            printf(" %s: %s\n", header->key, header->value);
        //}
        
    }

    evhttp_add_header(req->output_headers,"Content-Length", szLength);
    //evhttp_add_header(req->output_headers, "Content-Type", "application/json");
    //if (strcmp(uri,"/about.html")!=0)
    //{
    //    evhttp_add_header(req->output_headers, "Content-Type", "text/css");
    //}
    evbuffer_add(buf, buffer, uLength);
    //evbuffer_add_printf(buf, buffer);
    evhttp_send_reply(req, HTTP_OK, "OK", buf);
    delete[] buffer;
    evbuffer_free(buf);
}


//
//void MyHttpServerHandler(struct evhttp_request* req, void* arg)
//{
//    struct evkeyvalq *Header;
//
//    //创建要使用的buffer对象
//    evbuffer* buf = evbuffer_new();
//    const char* uri = (char*)evhttp_request_get_uri(req);
//    cout << "uri:" << uri << endl;
//    //char Data[2048];
//    //memset(Data, 0, 2048);
//    //evbuffer_copyout(req->input_buffer, Data, 50);    //request header
//    //cout << "Data:" << Data << endl;
//    Header = evhttp_request_get_input_headers(req);
//    for (evkeyval* header = Header->tqh_first; header; header = header->next.tqe_next)
//    {
//        printf(" %s: %s\n", header->key, header->value);
//    }
//    evbuffer_add_printf(buf, "hello");
//    evhttp_send_reply(req, HTTP_OK, "OK", buf);
//    evbuffer_free(buf);
//}

int main()
{
    startHttpServer("0.0.0.0", 9001, MyHttpServerHandler, NULL);
    return 0;
}