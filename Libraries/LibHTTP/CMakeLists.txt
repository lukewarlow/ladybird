set(SOURCES
    HttpRequest.cpp
    HttpResponse.cpp
)

ladybird_lib(LibHTTP http)
target_link_libraries(LibHTTP PRIVATE LibCompress LibCore LibTLS LibURL)
