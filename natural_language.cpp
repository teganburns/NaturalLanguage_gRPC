// Author: Tegan Burns-Berger
#include <iostream>
#include <unistd.h>

#include <grpc++/grpc++.h>
#include "NaturalLanguage.grpc.pb.h"

//using namespace std;
using namespace google::cloud::language::v1;


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


int AnalyzeEntities ( std::string* CONTENT ) {

    return 0;

}

int AnalyzeSentiment ( std::string* CONTENT ) {

    return 0;

}

int AnalyzeSyntax ( std::string* CONTENT ) {

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
    Document *document;
    AnnotateTextRequest_Features *features;
    EncodingType encoding_type;
    AnnotateTextResponse response;
    grpc::Status status;
    grpc::ClientContext context;
    std::cout << "Done!" << std::endl;

    sleep(0.5);

    // Document //
    std::cout << "Setting Document...\n";
    document = request.mutable_document();
    document->set_type( Document_Type::Document_Type_PLAIN_TEXT );
    //*CONTENT = "gs://personal_projects/NaturalLanguage.txt"; // TODO: User defined if you are specifying a gcs URI and not a string//
    //document->set_gcs_content_uri( *CONTENT );
    document->set_content( *CONTENT );
    //std::cout << "Done!" << std::endl;

    sleep(0.5);
     
    // Features //
    std::cout << "Setting Features...";
    features = request.mutable_features();
    features->set_extract_syntax( 1 );
    features->set_extract_entities( 1 );
    features->set_extract_document_sentiment( 1 );
    std::cout << "Done!" << std::endl;

    sleep(0.5);

    // EncodingType //
    std::cout << "Setting Encoding...";
    request.set_encoding_type( EncodingType::UTF8 );
    std::cout << "Done!" << std::endl;

    sleep(0.5);


    // Send Request //
    auto creds = grpc::GoogleDefaultCredentials();
    auto channel = grpc::CreateChannel( SCOPE, creds );
    std::unique_ptr< LanguageService::Stub> stub( LanguageService::NewStub( channel ) );
    status = stub->AnnotateText( &context, request, &response );

    // AnnotateText Response //
    std::cout << "status.ok(): " << status.ok() << std::endl;

    if ( status.ok() ) {
        std::cout << "\n\n------Response------" << std::endl << std::endl;


        std::cout << "----Sentences----" << std::endl; // TODO: sentences have sentiment too //
        std::cout << "Status returned OK\nSentences Size: " << response.sentences_size() << std::endl;
        for( int i = 0; i < response.sentences_size(); i++ ) {
            std::cout << "Sentence " << i << " has text: " << response.sentences( i ).has_text() << std::endl;
            if ( response.sentences( i ).has_text() ) {
                std::cout << "Sentence text: " << response.sentences( i ).text().content() << std::endl;
            }

        }

        std::cout << "\n----Tokens----" << std::endl;
        std::cout << "Tokens Size :" << response.tokens_size() << std::endl;
        for ( int i = 0; i < response.tokens_size(); i++ ) {
            std::cout << "Token " << i << " has text: " << response.tokens( i ).has_text() << std::endl;
            if ( response.tokens( i ).has_text() ) {
                std::cout << "Token text: " << response.tokens( i ).text().content() << std::endl;
            }

        }

        std::cout << "\n----Entities----" << std::endl;
        std::cout << "Entities Size :" << response.entities_size() << std::endl;
        for ( int i = 0; i < response.entities_size(); i++ ) {
            std::cout << "Entity " << i << " name: " << response.entities( i ).name() << std::endl;

        }


        std::cout << "\n----Sentiment----" << std::endl;
        std::cout << "Has Document Sentiment :" << response.has_document_sentiment() << std::endl;
        std::cout << "Document Sentiment: " << response.document_sentiment().magnitude() << std::endl;

        
        std::cout << "\n----Language----" << std::endl;
        std::cout << "Language: " << response.language() << std::endl;


    } else if ( status.ok() ){
        std::cout << "Status Returned Canceled" << std::endl;

    }else {
        std::cout << "gRPC Status Error Code: " << status.error_code() << "\ngRPC Status Error Message: " << status.error_message() << std::endl;
        std::cerr << "RPC failed" << std::endl;;
        return -1;
    }

    std::cout << "\nAll Finished!" << std::endl;





    return 0;

}


int main ( int argc, char* argv[] ) {

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    // VERIFY  ARGS //
    if ( argc < 3 ) {
        std::cerr << "Usage:  " << argv[0] << " [REQUEST] [CONTENT]" << std::endl;
        std::cerr << "\tCheck README.md for more information on usage." << std::endl;
    	return -1;
    }
 
    std::string CONTENT; 
    for ( int i = 2; i < argc; i++ ) {
        CONTENT += argv[i];
        CONTENT += " ";
    }

    std::cout << "\nCONTENT: " << CONTENT << std::endl;

    if ( argv[1] == "AnalyzeEntities " ) { AnalyzeEntities( &CONTENT ); }
    else if ( (std::string)argv[1] == "AnalizeSentiment" ) { AnalyzeSentiment( &CONTENT ); }
    else if ( (std::string)argv[1] == "AnalizeSyntax" ) { AnalyzeSyntax( &CONTENT ); }
    else if ( (std::string)argv[1] == "AnnotateText" ) { AnnotateText( &CONTENT ); }
    else {
        std::cerr << "Error: Argument \"" << argv[1] << "\" is not a recognized REQUEST." << std::endl;
        std::cerr << "\tCheck README.md for more information on usage." << std::endl;
    }

    //::google::protobuf::ShutdownProtobufLibrary();
    return 0;

}

// TODO: In AnnotateText(), document->set_source() currently only accepts "gs://" content, even when document->set_type() is set to PLAIN_TEXT. //
// TODO: In AnnotateText(), finish reading back all posible response paramaters // 
// TODO: In main(), change argv[] to take 2 arguments and get content with cin so bash doesn't mistake the sentece for special commands. //
