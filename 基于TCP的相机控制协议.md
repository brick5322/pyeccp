# 基于TCP的嵌入式相机控制协议

- Embedded camera control protocol

## 协议包含的内容

报文长度
报文功能码
报文数据

## 协议传输的方式

同步通讯：上位机发送功能，下位机对应执行该功能的过程，并在完成后返回。
异步通讯：由某上位机发送特定的功能后，下位机持续的发送某设定功能的过程。

也就是说上位机发送的一定要收到回复，下位机发送的不需要回复。

## 报文功能码

`0x1`：心跳包
主机：发送时间
从机：设定时间，返回原时间、设定后时间、相机基本信息

`0x1`：获取相机详细数据
主机：无数据
从机：相机详细数据

`0x3`：照相
主机：无数据
从机：拍照，发送24位RGB数据

`0x4`：开启从机定时发送
主机：发送定时器时间
从机：无数据响应，开始按定时器时间间隔拍照返回

`0x5`：从机定时传输数据
主机：非法
从机：拍照，发送24位RGB数据

`0x6`：结束从机定时发送
主机：无数据
从机：无数据

## 协议的格式

6字节+动态容量（完整的报文至多8192字节）

2字节：报文功能码
4字节：报文长度
动态：报文内容

## 服务端和客户端的API设计

基于UDP
上位机使用C做底层，Python做接口的设计，优先实现Linux环境。

#### 0、上位机Python接口设计

```Python
#module name: eccp
class Camera_info:
    pic_list = []
    
    def get_ID(self) -> str: ...

    def get_filePath(self) -> str: ...

    def set_filePath(self, filePath: str) -> bool: ...

    def getPic(self) -> None: ...

    def startPicStream(self, interval: int) -> None: ...

    def finishPicStream(self) -> None: ...

listen_list = []
#这里保存Camera列表，listenCamera会轮询这个列表中的Camera元素以接收并存储照片
def listenCamera(IP_address: str, port: int, maxnb: int, callback) -> None: ...
#这里的callback用作接入后的操作，形如def func(var:Camera_info) -> None
```

#### -1、（CPython API层面）设计

```c
typedef struct PyCameraObject
{
    PyObject_HEAD
	camera_info info;
}PyCameraObject
    
//PyListObject List

//PyCamera_Type 内封装的函数
PyObject* wrong_alloc(); //通过报异常来封掉构造、形成工厂模式
PyObject* get_ID(PyCameraObject*);
PyObject* get_filePath(PyCameraObject*);
PyObject* set_filePath(PyCameraObject*,PyObject** args);

PyObject* getPic(PyCameraObject*);
PyObject* startPicStream(PyCameraObject*,PyObject**args);
PyObject* finishPicStream(PyCameraObject*);

void CameraTCPservise(PyCameraObject*);
//会调用List轮询各socket
PyObject* listenCamera(PyModuleObject* module,PyObject** args);
```

#### -2、（C层面）协议解析

```C
typedef struct ECCP_message
{
	short func_code;
	unsigned int length;
	char* data;
}ECCP_message;

typedef void (*FUNC_Code)(const char*,camera_info*);
FUNC_Code ECCP_func_Code[6];

ECCP_message* ECCP_message_alloc();
void ECCP_message_realloc(ECCP_message*);
void ECCP_message_free(ECCP_message*);
void ECCP_message_exec(ECCP_message*,camera_info*);
```

#### -3、（C层面）相机信息结构体

```C
typedef struct camera_info
{
	char filepath[256];
	char ID[32];//这个需要设计成为定长 COMPANY-yyyy-mm-dd-hh-mm-ss-8B_number-防伪标识位（模运算）
	int width;
	int height;
    //其他的生成bmp的基本信息
} camera_info
    
int Camera_save_picture(camera_info* camera,clock_t time,const char* data);
```
