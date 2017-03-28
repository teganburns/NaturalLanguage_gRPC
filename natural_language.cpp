// Author: Tegan Burns-Berger
#include <iostream>
#include <unistd.h>

#include <grpc++/grpc++.h>
#include "NaturalLanguage.grpc.pb.h"

using namespace std;
using namespace google_cloud_natural_language;


using grpc::CompletionQueue;
using grpc::Channel;
using grpc::RpcService;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;

using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

std::string SCOPE = "language.googleapis.com";


int AnalyzeEntities () {

    return 0;

}

int AnalyzeSentiment () {

    return 0;

}

int AnalyzeSyntax () {

    //----------------------//
    // AnnotateText Request //
    //----------------------//

    std::cout << "\n\n------AnalyzeSyntax------" << std::endl;

    // Init Objects //
    
    // Document //
    
    // EncodingType // 


    return 0;
}

int AnnotateText ( std::string* CONTENT ) {

    //----------------------//
    // AnnotateText Request //
    //----------------------//

    std::cout << "\n\n------AnnotateText------" << std::endl;

    // Init Objects //
    std::cout << "Init Objects...";
    AnnotateTextRequest request;
    Document document;
    AnnotateTextRequest_Features *features;
    EncodingType encoding_type;
    std::cout << "Done!" << std::endl;

    sleep(0.5);

    // Document //
    std::cout << "Setting Document...";
    document.set_type( Document_Type::Document_Type_PLAIN_TEXT );
    document.set_language("English");
    document.set_content( *CONTENT );
    std::cout << "Done!" << std::endl;

    sleep(0.5);
     
    // Features //
    std::cout << "Setting Features...";
    features = request.mutable_features();
    features->set_extract_syntax( 1 );
    features->set_extract_entities( 1 );
    features->set_extract_document_sentiment( 1 );
    request.set_allocated_features( features );
    std::cout << "Done!" << std::endl;

    sleep(0.5);

    // EncodingType //
    cout << "Setting Encoding...";
    request.set_encoding_type( EncodingType::UTF8 );
    cout << "Done!" << endl;

    sleep(0.5);


    // Send Request //



    //-----------------------//
    // AnnotateText Response //
    //-----------------------//





    return 0;

}


int main () {


    GOOGLE_PROTOBUF_VERIFY_VERSION;

    std::string CONTENT = "Hello, this is a test!";
    AnnotateText( &CONTENT );

    //::google::protobuf::ShutdownProtobufLibrary();
    return 0;

}

// TODO: There is a seg fault that I belive is cause by not using the pointers incorrectly for mutable_xxxx() or set_allocated_xxxx()
//
