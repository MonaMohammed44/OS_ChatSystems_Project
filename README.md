# OS Chat Systems Project

مشروع شات (OS Project) فيه جزئين:

- **`ChatSystem_SharedMemory`**: شات باستخدام Shared Memory (على نفس الجهاز فقط).
- **`ChatSystem_Sockets`**: شات باستخدام TCP Sockets (ينفع بين جهازين).

## تشغيل `ChatSystem_Sockets` (Server / Client)

البرنامج واحد (GUI)، وبيشتغل بطريقتين من خلال arguments:
- **Server mode**: يشغل السيرفر + يفتح الـGUI.
- **Client mode**: يفتح الـGUI ويتصل على host/port.

### Server (على جهاز السيرفر)

شغّل من فولدر الـRelease:

```bat
cd /d d:\OS_ChatSystems_Project\x64\Release
.\ChatSystem_Sockets.exe --server --port 1234
```

### Client (على جهاز الكلينت)

1) هات IP جهاز السيرفر (على جهاز السيرفر):

```bat
ipconfig
```

2) على جهاز الكلينت شغّل (غير الـIP):

```bat
.\ChatSystem_Sockets.exe --host 192.168.1.50 --port 1234
```

### Test على نفس الجهاز (بدون جهاز تاني)

افتح 3 نوافذ PowerShell:

- نافذة 1 (Server):

```bat
.\ChatSystem_Sockets.exe --server --port 1234
```

- نافذة 2 (Client 1):

```bat
.\ChatSystem_Sockets.exe --host 127.0.0.1 --port 1234
```

- نافذة 3 (Client 2):

```bat
.\ChatSystem_Sockets.exe --host 127.0.0.1 --port 1234
```

## ملاحظات مهمة للتشغيل على جهازين

- **Firewall**: على جهاز السيرفر افتح **TCP Inbound** على البورت `1234` أو اسمح للـ`ChatSystem_Sockets.exe`.
- لازم الجهازين على نفس الشبكة أو يكون فيه Routing صحيح.



