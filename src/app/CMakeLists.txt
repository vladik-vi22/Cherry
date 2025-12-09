# Cherry Main Application

set(QML_SOURCES
    qml/main.qml
    qml/BigIntLibrary/BigIntCalculator.qml
    qml/EDHcryptor/EDHcryptorMenu.qml
    qml/EDHcryptor/EDHcryptorAffine.qml
    qml/EDHcryptor/EDHcryptorVizhener.qml
    qml/PRBgenerators/PRBgeneratorsNtests.qml
)

qt_add_executable(Cherry
    main.cpp
)

qt_add_qml_module(Cherry
    URI Cherry
    VERSION 2.0
    QML_FILES ${QML_SOURCES}
)

target_include_directories(Cherry
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Cherry
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        Qt6::Widgets
        Cherry::BigInt
        Cherry::Generators
        Cherry::RPN
        Cherry::Ciphers
        Cherry::Crypto
        cherry_warnings
)

# Windows-specific settings
if(WIN32)
    set_target_properties(Cherry PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# macOS-specific settings
if(APPLE)
    set_target_properties(Cherry PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.cherry.app"
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    )
endif()

