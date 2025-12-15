cmake_minimum_required(VERSION 3.16)
project(ChatSystem_Sockets)

# تفعيل MOC تلقائياً
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# البحث عن Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Network)

# إضافة الملفات المصدر
set(SOURCES
    main.cpp
    client.cpp
    server.cpp
    gui.cpp
)

# إضافة ملفات الرأس
set(HEADERS
    client.h
    server.h
    gui.h
)

# إنشاء البرنامج التنفيذي
add_executable(ChatSystem_Sockets ${SOURCES} ${HEADERS})

# ربط مكتبات Qt
target_link_libraries(ChatSystem_Sockets
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
)

# نسخ ملفات DLL تلقائياً (للويندوز)
if(WIN32)
    add_custom_command(TARGET ChatSystem_Sockets POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:Qt5::Core>" "$<TARGET_FILE_DIR:ChatSystem_Sockets>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:Qt5::Widgets>" "$<TARGET_FILE_DIR:ChatSystem_Sockets>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:Qt5::Network>" "$<TARGET_FILE_DIR:ChatSystem_Sockets>"
    )
endif()