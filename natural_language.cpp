// Author: Tegan Burns-Berger
#include <iostream>

#include <grpc++/grpc++.h>
#include "NaturalLanguage.grpc.pb.h"


std::string SCOPE = "";

int main () {


    GOOGLE_PROTOBUF_VERIFY_VERSION;



    ::google::protobuf::ShutdownProtobufLibrary();
    return 0;

}
