#ifndef UDP_H
#define UDP_H
#ifdef __cplusplus

extern"C"
{
#endif
int socket_send(const char* ip);
int socket_rec();
#ifdef __cplusplus
}
#endif
#endif // UDP_H

